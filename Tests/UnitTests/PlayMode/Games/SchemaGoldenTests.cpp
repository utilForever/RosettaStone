// Copyright (c) 2026 Chris Ohk

#include "doctest_proxy.hpp"

#include <Rosetta/Common/DefaultFloatEnvScope.hpp>
#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Actions/PolicyActions.hpp>
#include <Rosetta/PlayMode/Agents/PUCTSearch.hpp>
#include <Rosetta/PlayMode/Agents/SelfPlaySample.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/EndTurnTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/HeroPowerTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/PlayCardTask.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

#include <bit>
#include <cfenv>
#include <cmath>
#include <fstream>
#include <iterator>
#include <limits>
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

TEST_CASE("[SelfPlaySample] - Normal turn matches the shared binary fixture")
{
    std::ifstream file(
        std::string(RESOURCES_DIR) + "SchemaGolden/v1/self-play.rssp",
        std::ios::binary);

    REQUIRE(file.is_open());

    const std::string golden{ std::istreambuf_iterator<char>(file), {} };
    const auto decoded = SelfPlaySample::Deserialize(golden);

    auto game = GoldenGame(PlayerType::PLAYER2);

    SetUpBoard(*game);
    Draw(game->GetCurrentPlayer(), "CS2_231");
    Draw(game->GetCurrentPlayer(), "CS2_120");

    const auto mask = PolicyActions(*game).GetLegalMask();

    std::array<PUCTNode, 2> actions;
    actions[0].actionIndex = PolicySchema::END_TURN;
    actions[0].visitCount = 1;
    actions[1].actionIndex = 2857;  // River Crocolisk at position zero.
    actions[1].visitCount = 3;

    SelfPlaySample sample{ FlattenObservation(EncodeObservation(*game)), mask,
                           NormalizeVisitCounts(mask, actions) };

    CHECK_THROWS_AS(sample.Serialize(), std::invalid_argument);

    sample.outcome = -1;

    CHECK(sample.observation == decoded.observation);
    CHECK(sample.legalMask == decoded.legalMask);
    CHECK(sample.policyTarget == decoded.policyTarget);
    CHECK_EQ(decoded.outcome, -1);
    CHECK(sample.Serialize() == golden);
    CHECK(decoded.Serialize() == golden);
    CHECK_THROWS_AS(
        SelfPlaySample::Deserialize(std::string_view(golden).substr(1)),
        std::invalid_argument);
}

TEST_CASE("[SelfPlaySample] - Invalid root action counts")
{
    PolicySchema::LegalMask mask{};
    mask[0] = mask[1] = 1;

    std::array<PUCTNode, 2> actions;
    actions[0].actionIndex = 0;
    actions[1].actionIndex = 1;

    CHECK_THROWS_AS(NormalizeVisitCounts(mask, actions), std::invalid_argument);

    actions[0].visitCount = 1;

    CHECK_EQ(NormalizeVisitCounts(mask, actions)[1], 0);

    for (auto index :
         { std::size_t{ 0 }, std::size_t{ 2 }, PolicySchema::NUM_ACTIONS })
    {
        actions[1].actionIndex = index;
        CHECK_THROWS_AS(NormalizeVisitCounts(mask, actions),
                        std::invalid_argument);
    }
}

TEST_CASE("[SelfPlaySample] - Exact upper and lower visit-policy sum bounds")
{
    // Adding one more small legal probability crosses the upper bound.
    VisitPolicy policy{ 1.0f, 1e-5f, 1137 * 0x1p-52f, 0x1p-54f, 0x1p-54f };

    CHECK(IsNormalizedVisitPolicy(policy));

    policy.back() = 0x1p-54f;

    CHECK_FALSE(IsNormalizedVisitPolicy(policy));

    // These adjacent binary32 tails straddle the exact lower bound.
    policy = { 0.99999f, 0x1.d29dc6p-27f };

    CHECK_FALSE(IsNormalizedVisitPolicy(policy));

    policy[1] = std::nextafter(policy[1], 1.0f);

    CHECK(IsNormalizedVisitPolicy(policy));

    // Adjacent doubles narrow to the same float but straddle the upper bound.
    std::array<double, PolicySchema::NUM_ACTIONS> precise{ 1.0, 1e-5 };

    CHECK_FALSE(IsNormalizedVisitPolicy(precise));

    precise[1] = std::nextafter(precise[1], 0.0);

    CHECK(IsNormalizedVisitPolicy(precise));
}

TEST_CASE(
    "[SelfPlaySample] - Visit ratios use the same bytes in every rounding mode")
{
    const DefaultFloatEnvScope restoreOnExit;

    SelfPlaySample sample;
    sample.observation.front() = ObservationSchema::VERSION;
    sample.outcome = -1;
    sample.legalMask[0] = sample.legalMask[2857] = 1;

    std::array<PUCTNode, 2> actions;
    actions[0].actionIndex = 0;
    actions[0].visitCount = 1;
    actions[1].actionIndex = 2857;
    actions[1].visitCount = 2;

    sample.policyTarget[0] = std::bit_cast<float>(0x3eaaaaabu);     // 1/3
    sample.policyTarget[2857] = std::bit_cast<float>(0x3f2aaaabu);  // 2/3

    const auto expected = sample.Serialize();

    for (const int mode :
         { FE_TONEAREST, FE_DOWNWARD, FE_UPWARD, FE_TOWARDZERO })
    {
        REQUIRE_EQ(std::fesetround(mode), 0);

        sample.policyTarget = NormalizeVisitCounts(sample.legalMask, actions);

        CHECK_EQ(std::fegetround(), mode);
        CHECK(sample.Serialize() == expected);
        CHECK_THROWS_AS(NormalizeVisitCounts(sample.legalMask, {}),
                        std::invalid_argument);
        CHECK_EQ(std::fegetround(), mode);
    }
}

TEST_CASE("[SelfPlaySample] - Visit counts round the exact ratio to binary32")
{
    const auto firstBits = [](const std::array<std::size_t, 3>& counts) {
        PolicySchema::LegalMask mask{};
        std::array<PUCTNode, 3> actions;

        for (std::size_t i = 0; i < counts.size(); ++i)
        {
            mask[i] = 1;
            actions[i].actionIndex = i;
            actions[i].visitCount = counts[i];
        }

        return std::bit_cast<std::uint32_t>(
            NormalizeVisitCounts(mask, actions)[0]);
    };

    // On opposite sides of two midpoints. Binary64 rounds both onto the tie.
    CHECK_EQ(firstBits({ 276'824'080, 276'824'047 }), 0x3f000001u);
    CHECK_EQ(firstBits({ 282'416'520, 282'416'419 }), 0x3f000001u);
    CHECK_EQ(firstBits({ 16'777'217, 16'777'215 }), 0x3f000000u);
    CHECK_EQ(firstBits({ 16'777'219, 16'777'213 }), 0x3f000002u);

    const auto maximum = std::numeric_limits<std::size_t>::max();
    const auto half = maximum / 2 + 1;
    const auto gap = half >> 24;

    CHECK_EQ(firstBits({ half + gap + 1, half - gap - 1 }), 0x3f000001u);
    CHECK_EQ(firstBits({ 1, maximum, maximum }),
             std::bit_cast<std::uint32_t>(
                 std::ldexp(0.5f, -std::numeric_limits<std::size_t>::digits)));
}
