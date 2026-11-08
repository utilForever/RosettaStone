// Copyright (c) 2026 Chris Ohk

#include "doctest_proxy.hpp"

#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Actions/PolicyActions.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/EndTurnTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/HeroPowerTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/PlayCardTask.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

#include <fstream>
#include <iterator>
#include <locale>
#include <map>
#include <memory>
#include <sstream>
#include <string_view>
#include <type_traits>

using namespace RosettaStone;
using namespace PlayMode;
using namespace PlayerTasks;

namespace
{
// Changing a golden contract requires the version decision documented in
// Documents/ObservationSchema.md; never silently regenerate v1 fixtures.
static_assert(ObservationSchema::VERSION == 1 && PolicySchema::VERSION == 1 &&
              PolicySchema::OBSERVATION_VERSION == 1);
static_assert(
    std::is_same_v<PolicySchema::LegalMask, std::array<std::uint8_t, 4846>>);

std::unique_ptr<Game> GoldenGame(PlayerType actor)
{
    GameConfig config;
    config.formatType = FormatType::WILD;
    config.startPlayer = actor;
    config.player1Class =
        actor == PlayerType::PLAYER1 ? CardClass::MAGE : CardClass::WARRIOR;
    config.player2Class =
        actor == PlayerType::PLAYER2 ? CardClass::MAGE : CardClass::WARRIOR;
    config.doShuffle = false;
    config.player1Deck.fill(
        Cards::FindCardByID("CS2_200"));  // Boulderfist Ogre
    config.player2Deck = config.player1Deck;

    auto game = std::make_unique<Game>(config);
    game->Start();

    return game;
}

Playable* Draw(Player* player, const char* cardID)
{
    return Generic::DrawCard(player, Cards::FindCardByID(cardID));
}

void SetUpBoard(Game& game)
{
    auto* actor = game.GetCurrentPlayer();
    actor->SetTotalMana(4);

    game.Process(actor, PlayCardTask(Draw(actor, "CS2_120")));  // Crocolisk
    game.Process(actor, PlayCardTask(Draw(actor, "CS2_172")));  // Raptor
    game.Process(actor, EndTurnTask());

    auto* opponent = game.GetCurrentPlayer();
    opponent->SetTotalMana(4);

    game.Process(opponent, PlayCardTask(Draw(opponent, "CS2_179")));  // Sen'jin
    game.Process(opponent, EndTurnTask());

    REQUIRE(game.GetCurrentPlayer() == actor);
}

template <typename T, std::size_t N>
void WriteTensor(std::ostream& out, const std::string& name,
                 const std::array<T, N>& values)
{
    if constexpr (std::is_arithmetic_v<T>)
    {
        static_assert(std::is_same_v<T, std::int32_t>);

        out << name << ':';

        for (const auto value : values)
        {
            out << ' ' << value;
        }

        out << '\n';
    }
    else
    {
        for (std::size_t slot = 0; slot < N; ++slot)
        {
            WriteTensor(out, name + '[' + std::to_string(slot) + ']',
                        values[slot]);
        }
    }
}

std::string Snapshot(const Game& game)
{
    std::ostringstream out;
    out.imbue(std::locale::classic());

    if (game.state == State::RUNNING)
    {
        const auto observation = EncodeObservation(game);
        // Decomposition makes adding or removing a tensor a compile failure.
        const auto& [schemaVersion, turn, players, heroes, heroPowers, weapons,
                     board, hand, secrets, chooseOne, choices] = observation;

        out << "observationVersion: " << schemaVersion << '\n';

        WriteTensor(out, "turn", turn);
        WriteTensor(out, "players", players);
        WriteTensor(out, "heroes", heroes);
        WriteTensor(out, "heroPowers", heroPowers);
        WriteTensor(out, "weapons", weapons);
        WriteTensor(out, "board", board);
        WriteTensor(out, "hand", hand);
        WriteTensor(out, "secrets", secrets);
        WriteTensor(out, "chooseOne", chooseOne);
        WriteTensor(out, "choices", choices);
    }
    else
    {
        CHECK_THROWS_AS(EncodeObservation(game), std::invalid_argument);
        out << "observation: rejected (terminal)\n";
    }

    // Name visible slots instead of persisting game-local entity IDs.
    std::map<int, std::string> names{ { -1, "-" } };
    const auto nameEntity = [&names](const Entity* entity, std::string name) {
        names.emplace(entity->GetGameTag(GameTag::ENTITY_ID), std::move(name));
    };
    const auto* actor = game.GetCurrentPlayer();
    std::size_t owner = 0;

    for (const auto* player :
         { actor, static_cast<const Player*>(actor->opponent) })
    {
        const auto suffix = '[' + std::to_string(owner) + ']';

        nameEntity(player->GetHero(), "heroes" + suffix);
        nameEntity(player->GetHero()->heroPower, "heroPowers" + suffix);

        std::size_t slot = 0;

        for (const auto* minion : player->GetFieldZone()->GetAll())
        {
            nameEntity(minion,
                       "board" + suffix + '[' + std::to_string(slot++) + ']');
        }

        ++owner;
    }

    std::size_t slot = 0;

    for (const auto* card : actor->GetHandZone()->GetAll())
    {
        nameEntity(card, "hand[" + std::to_string(slot++) + ']');
    }

    const PolicyActions policy(game);
    PolicySchema::LegalMask mask{};
    std::map<std::size_t, PlayerAction> actions;

    for (const auto& action : EnumerateActions(game))
    {
        const auto index = policy.Encode(action);

        REQUIRE(index < mask.size());
        CHECK_EQ(mask[index], 0);

        mask[index] = 1;

        CHECK(policy.Decode(index) == action);
        CHECK_EQ(policy.Encode(policy.Decode(index)), index);

        actions.emplace(index, action);
    }

    CHECK(policy.GetLegalMask() == mask);

    out << "policyVersion: " << PolicySchema::VERSION << '\n';
    out << "mask: uint8[" << mask.size() << "] default=0; listed indices=1\n";
    out << "actions: index type source target fieldPos chooseOne choice\n";

    constexpr std::array<std::string_view, 5> types{ "END_TURN", "PLAY_CARD",
                                                     "ATTACK", "HERO_POWER",
                                                     "CHOOSE" };

    for (const auto& [index, action] : actions)
    {
        out << index << ' ' << types.at(static_cast<std::size_t>(action.type))
            << ' ' << names.at(action.sourceID) << ' '
            << names.at(action.targetID) << ' ' << action.fieldPos << ' '
            << action.chooseOne << ' ' << names.at(action.choiceID) << '\n';
    }

    return out.str();
}
}  // namespace

TEST_CASE("[SchemaGolden] - Version one observation and policy fixtures")
{
    for (const auto* scenario : { "opening", "normal-turn", "targeted-play",
                                  "attack", "hero-power", "terminal-adjacent" })
    {
        const std::string name = scenario;

        CAPTURE(name);

        std::ifstream file(
            std::string(RESOURCES_DIR) + "SchemaGolden/v1/" + name + ".txt",
            std::ios::binary);

        REQUIRE(file.is_open());

        const std::string expected{ std::istreambuf_iterator<char>(file),
                                    std::istreambuf_iterator<char>() };

        for (const auto seat : { PlayerType::PLAYER1, PlayerType::PLAYER2 })
        {
            CAPTURE(static_cast<int>(seat));

            auto game = GoldenGame(seat);
            auto* actor = game->GetCurrentPlayer();

            if (name != "opening")
            {
                SetUpBoard(*game);
            }

            if (name == "normal-turn")
            {
                Draw(actor, "CS2_231");  // Wisp
                Draw(actor, "CS2_120");  // River Crocolisk
            }
            else if (name == "targeted-play")
            {
                Draw(actor, "CS2_029");  // Fireball
            }
            else if (name == "attack")
            {
                game->Process(actor, PlayCardTask(Draw(actor, "CS2_106")));
            }
            else if (name == "hero-power")
            {
                game->Process(actor, HeroPowerTask(actor->opponent->GetHero()));
            }
            else if (name == "terminal-adjacent")
            {
                actor->opponent->GetHero()->SetDamage(29);
            }

            auto actual = Snapshot(*game);

            if (name == "terminal-adjacent")
            {
                game->Process(actor, HeroPowerTask(actor->opponent->GetHero()));

                CHECK_EQ(actor->playState, PlayState::WON);
                CHECK_EQ(actor->opponent->playState, PlayState::LOST);

                actual += "after lethal:\n" + Snapshot(*game);
            }

            CHECK_EQ(actual, expected);
        }
    }
}
