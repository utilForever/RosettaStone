// Copyright (c) 2026 Chris Ohk

#include "doctest_proxy.hpp"

#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Actions/PlayerAction.hpp>
#include <Rosetta/PlayMode/Actions/PolicyActions.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Weapon.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/AttackTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/ChooseTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/EndTurnTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/HeroPowerTask.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/PlayCardTask.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>
#include <Rosetta/PlayMode/Zones/SetasideZone.hpp>

#include <effolkronium/random.hpp>

#include <algorithm>
#include <limits>
#include <memory>
#include <type_traits>

using namespace RosettaStone;
using namespace PlayMode;
using namespace PlayerTasks;

namespace
{
int ID(const Entity* entity)
{
    return entity->GetGameTag(GameTag::ENTITY_ID);
}

std::unique_ptr<Game> ActionGame(CardClass heroClass = CardClass::MAGE,
                                 PlayerType startPlayer = PlayerType::PLAYER1)
{
    GameConfig config;
    config.formatType = FormatType::WILD;
    config.player1Class =
        startPlayer == PlayerType::PLAYER1 ? heroClass : CardClass::WARRIOR;
    config.player2Class =
        startPlayer == PlayerType::PLAYER2 ? heroClass : CardClass::WARRIOR;
    config.startPlayer = startPlayer;
    config.doShuffle = false;
    config.player1Deck.fill(Cards::FindCardByID("CS2_231"));
    config.player2Deck.fill(Cards::FindCardByID("CS2_231"));

    auto game = std::make_unique<Game>(config);
    game->Start();
    game->GetCurrentPlayer()->SetTotalMana(10);

    return game;
}

Playable* Draw(Player* player, const char* cardID)
{
    return Generic::DrawCard(player, Cards::FindCardByID(cardID));
}

std::unique_ptr<Game> MixedActions(PlayerType startPlayer = PlayerType::PLAYER1)
{
    auto game = ActionGame(CardClass::MAGE, startPlayer);
    auto* player = game->GetCurrentPlayer();

    game->Process(player, PlayCardTask(player->GetHandZone()->GetAll()[0]));
    game->Process(player, EndTurnTask());

    auto* opponent = game->GetCurrentPlayer();

    game->Process(opponent, PlayCardTask(opponent->GetHandZone()->GetAll()[0]));
    game->Process(opponent, EndTurnTask());

    player->SetTotalMana(10);

    game->Process(player, PlayCardTask(Draw(player, "CS2_106")));

    Draw(player, "CS2_029");  // Fireball
    Draw(player, "CS2_023");  // Arcane Intellect
    Draw(player, "CS2_182");  // Chillwind Yeti

    return game;
}

void ProcessAndCheck(Game& game, const PlayerAction& action)
{
    auto* player = game.GetCurrentPlayer();
    auto* source =
        action.sourceID < 0 ? nullptr : game.entityList.at(action.sourceID);
    auto* target =
        action.targetID < 0 ? nullptr : game.entityList.at(action.targetID);

    switch (action.type)
    {
        case PlayerActionType::END_TURN:
            game.Process(player, EndTurnTask());

            CHECK_NE(game.GetCurrentPlayer(), player);
            break;
        case PlayerActionType::PLAY_CARD:
        {
            const int played = player->GetNumCardsPlayedThisTurn();

            game.Process(player, PlayCardTask(source, target, action.fieldPos,
                                              action.chooseOne));

            CHECK_EQ(player->GetNumCardsPlayedThisTurn(), played + 1);
            CHECK_NE(source->GetZoneType(), ZoneType::HAND);

            if (action.fieldPos >= 0)
            {
                CHECK_EQ(player->GetFieldZone()->GetAll()[action.fieldPos],
                         source);
            }
            break;
        }
        case PlayerActionType::ATTACK:
        {
            auto* attacker = dynamic_cast<Character*>(source);

            REQUIRE(attacker);

            const int attacks = attacker->GetNumAttacksThisTurn();

            game.Process(player, AttackTask(source, target));

            CHECK_EQ(attacker->GetNumAttacksThisTurn(), attacks + 1);
            break;
        }
        case PlayerActionType::HERO_POWER:
            game.Process(player, HeroPowerTask(target));

            CHECK(player->GetHeroPower().IsExhausted());
            break;
        case PlayerActionType::CHOOSE:
            game.Process(player, ChooseTask({ action.choiceID }));

            CHECK_FALSE(player->choice);
            break;
    }
}

void CheckPolicyRoundTrips(const Game& game, const PolicyActions& policy)
{
    PolicySchema::LegalMask expected{};

    for (const auto& action : EnumerateActions(game))
    {
        const auto index = policy.Encode(action);

        REQUIRE(index < expected.size());
        CHECK_EQ(expected[index], 0);

        expected[index] = 1;

        CHECK(policy.Decode(index) == action);
    }

    CHECK(policy.GetLegalMask() == expected);

    for (std::size_t index = 0; index < expected.size(); ++index)
    {
        if (expected[index] == 0)
        {
            CHECK_THROWS_AS(policy.Decode(index), std::invalid_argument);
        }
    }
}
}  // namespace

TEST_CASE("[PlayerAction] - Complete deterministic main actions")
{
    auto game = MixedActions();
    const auto* player = game->GetCurrentPlayer();
    const auto actions = EnumerateActions(*game);

    CHECK(std::ranges::is_sorted(actions));
    CHECK(std::ranges::adjacent_find(actions) == actions.end());
    CHECK(actions == EnumerateActions(*game));
    CHECK_EQ(std::ranges::count(actions, PlayerAction{}), 1);

    for (const auto* card : player->GetHandZone()->GetAll())
    {
        const auto count =
            std::ranges::count_if(actions, [card](const auto& a) {
                return a.type == PlayerActionType::PLAY_CARD &&
                       a.sourceID == ID(card);
            });

        if (card->card->id == "CS2_029")
        {
            CHECK_EQ(count, 4);
        }
        else if (card->card->id == "CS2_023")
        {
            CHECK_EQ(count, 1);
        }
        else
        {
            CHECK_EQ(count, 2);
            CHECK(std::ranges::find(actions,
                                    PlayerAction{ PlayerActionType::PLAY_CARD,
                                                  ID(card), -1, 0 }) !=
                  actions.end());
            CHECK(std::ranges::find(actions,
                                    PlayerAction{ PlayerActionType::PLAY_CARD,
                                                  ID(card), -1, 1 }) !=
                  actions.end());
        }
    }

    CHECK_EQ(std::ranges::count_if(actions,
                                   [](const auto& action) {
                                       return action.type ==
                                              PlayerActionType::ATTACK;
                                   }),
             4);
    CHECK_EQ(std::ranges::count_if(actions,
                                   [](const auto& action) {
                                       return action.type ==
                                              PlayerActionType::HERO_POWER;
                                   }),
             4);

    // Replay each value against the same fixture, proving the normal task
    // path actually applies it rather than silently rejecting the action.
    for (const auto& action : actions)
    {
        auto independent = MixedActions();

        REQUIRE(EnumerateActions(*independent) == actions);
        ProcessAndCheck(*independent, action);
    }
}

TEST_CASE("[PlayerAction] - Mana board capacity and unavailable targets")
{
    auto game = ActionGame();
    auto* player = game->GetCurrentPlayer();
    const auto* fireball = Draw(player, "CS2_029");

    player->SetTotalMana(0);

    auto actions = EnumerateActions(*game);

    CHECK_FALSE(std::ranges::any_of(actions, [fireball](const auto& action) {
        return action.sourceID == ID(fireball) ||
               action.type == PlayerActionType::HERO_POWER;
    }));

    player->SetTotalMana(10);
    game->Process(player, PlayCardTask(Draw(player, "REV_983")));

    Draw(player, "REV_983");

    for (int i = 0; i < 6; ++i)
    {
        game->Process(player, PlayCardTask(Draw(player, "CS2_231")));
    }

    actions = EnumerateActions(*game);

    CHECK_FALSE(std::ranges::any_of(actions, [&game](const auto& action) {
        if (action.type != PlayerActionType::PLAY_CARD)
        {
            return false;
        }

        const auto type =
            game->entityList.at(action.sourceID)->card->GetCardType();
        return type == CardType::MINION || type == CardType::LOCATION;
    }));

    auto empty = ActionGame();
    const auto* execute = Draw(empty->GetCurrentPlayer(), "CS2_108");
    const auto noTargets = EnumerateActions(*empty);

    CHECK_FALSE(std::ranges::any_of(noTargets, [execute](const auto& action) {
        return action.sourceID == ID(execute);
    }));
}

TEST_CASE("[PlayerAction] - Attack restrictions")
{
    auto game = MixedActions();
    const auto* player = game->GetCurrentPlayer();
    auto* minion = (*player->GetFieldZone())[0];
    auto* defender = (*player->opponent->GetFieldZone())[0];

    defender->SetGameTag(GameTag::TAUNT, 1);

    auto actions = EnumerateActions(*game);
    int attacks = 0;

    for (const auto& action : actions)
    {
        if (action.type == PlayerActionType::ATTACK)
        {
            ++attacks;
            CHECK_EQ(action.targetID, ID(defender));
        }
    }

    CHECK_EQ(attacks, 2);

    defender->SetGameTag(GameTag::TAUNT, 0);
    minion->SetAttackableByRush(true);
    actions = EnumerateActions(*game);

    CHECK_FALSE(std::ranges::any_of(actions, [player, minion](const auto& a) {
        return a.type == PlayerActionType::ATTACK && a.sourceID == ID(minion) &&
               a.targetID == ID(player->opponent->GetHero());
    }));
    CHECK(std::ranges::any_of(actions, [defender, minion](const auto& a) {
        return a.type == PlayerActionType::ATTACK && a.sourceID == ID(minion) &&
               a.targetID == ID(defender);
    }));

    minion->SetGameTag(GameTag::FROZEN, 1);
    player->GetHero()->SetExhausted(true);
    actions = EnumerateActions(*game);

    CHECK_FALSE(std::ranges::any_of(actions, [](const auto& action) {
        return action.type == PlayerActionType::ATTACK;
    }));
}

TEST_CASE("[PlayerAction] - Untargeted hero powers")
{
    for (const auto heroClass : { CardClass::WARRIOR, CardClass::HUNTER })
    {
        auto game = ActionGame(heroClass);
        const auto* player = game->GetCurrentPlayer();
        const auto actions = EnumerateActions(*game);
        const auto powers = std::ranges::count_if(actions, [](const auto& a) {
            return a.type == PlayerActionType::HERO_POWER;
        });

        REQUIRE_EQ(powers, 1);

        const auto power = std::ranges::find_if(actions, [](const auto& a) {
            return a.type == PlayerActionType::HERO_POWER;
        });

        CHECK_EQ(power->sourceID, ID(&player->GetHeroPower()));
        ProcessAndCheck(*game, *power);

        if (heroClass == CardClass::WARRIOR)
        {
            CHECK_EQ(player->GetHero()->GetArmor(), 2);
        }
        else
        {
            CHECK_EQ(player->opponent->GetHero()->GetHealth(), 28);
        }

        const auto exhausted = EnumerateActions(*game);

        CHECK_FALSE(std::ranges::any_of(exhausted, [](const auto& action) {
            return action.type == PlayerActionType::HERO_POWER;
        }));
    }
}

TEST_CASE("[PlayerAction] - Choose One and Choose Both")
{
    for (const bool chooseBoth : { false, true })
    {
        for (int option = chooseBoth ? 0 : 1; option <= (chooseBoth ? 0 : 2);
             ++option)
        {
            auto game = ActionGame(CardClass::DRUID);
            auto* player = game->GetCurrentPlayer();

            game->Process(player, PlayCardTask(Draw(player, "CS2_182")));

            const auto* target = (*player->GetFieldZone())[0];
            const auto* wrath = Draw(player, "EX1_154");

            player->playerAuraEffects.SetValue(GameTag::CHOOSE_BOTH,
                                               chooseBoth ? 1 : 0);

            const auto actions = EnumerateActions(*game);

            CHECK_EQ(std::ranges::count_if(actions,
                                           [wrath](const auto& a) {
                                               return a.sourceID == ID(wrath);
                                           }),
                     chooseBoth ? 1 : 2);

            const PlayerAction action{ PlayerActionType::PLAY_CARD, ID(wrath),
                                       ID(target), -1, option };

            REQUIRE(std::ranges::find(actions, action) != actions.end());
            ProcessAndCheck(*game, action);
            CHECK_EQ(target->GetHealth(), chooseBoth ? 1 : option == 1 ? 2 : 4);
        }
    }
}

TEST_CASE("[PlayerAction] - Choose One options have independent targets")
{
    for (int option = 1; option <= 2; ++option)
    {
        auto game = ActionGame(CardClass::DRUID);
        auto* player = game->GetCurrentPlayer();
        const auto* roots = Draw(player, "AT_037");
        const auto actions = EnumerateActions(*game);

        CHECK_EQ(std::ranges::count_if(actions,
                                       [roots](const auto& a) {
                                           return a.sourceID == ID(roots);
                                       }),
                 3);

        for (const auto& action : actions)
        {
            if (action.sourceID == ID(roots))
            {
                CHECK_EQ(action.targetID == -1, action.chooseOne == 2);
            }
        }

        const PlayerAction action{ PlayerActionType::PLAY_CARD, ID(roots),
                                   option == 1 ? ID(player->opponent->GetHero())
                                               : -1,
                                   -1, option };

        REQUIRE(std::ranges::find(actions, action) != actions.end());
        ProcessAndCheck(*game, action);
        CHECK_EQ(player->opponent->GetHero()->GetHealth(),
                 option == 1 ? 28 : 30);
        CHECK_EQ(player->GetFieldZone()->GetCount(), option == 2 ? 2 : 0);
    }
}

TEST_CASE("[PlayerAction] - Locations share placement slots and can be targets")
{
    for (int scenario = 0; scenario < 6; ++scenario)
    {
        const int position = scenario % 3;
        auto game = ActionGame();
        auto* player = game->GetCurrentPlayer();
        auto* enemyLocation = Draw(player, "REV_983");

        game->Process(player, PlayCardTask(enemyLocation));
        game->Process(player, EndTurnTask());

        player = game->GetCurrentPlayer();
        player->SetTotalMana(10);

        game->Process(player, PlayCardTask(Draw(player, "CS2_231")));
        game->Process(player, PlayCardTask(Draw(player, "REV_983")));

        const auto* location = Draw(player, "REV_983");
        const auto* renovator = Draw(player, "REV_023");
        const auto actions = EnumerateActions(*game);

        CHECK_EQ(std::ranges::count_if(actions,
                                       [location](const auto& a) {
                                           return a.sourceID == ID(location);
                                       }),
                 3);
        CHECK_EQ(std::ranges::count_if(actions,
                                       [renovator](const auto& a) {
                                           return a.sourceID == ID(renovator);
                                       }),
                 3);

        const PlayerAction place{ PlayerActionType::PLAY_CARD, ID(location), -1,
                                  position };
        const PlayerAction destroy{ PlayerActionType::PLAY_CARD, ID(renovator),
                                    ID(enemyLocation), position };

        REQUIRE(std::ranges::find(actions, place) != actions.end());
        REQUIRE(std::ranges::find(actions, destroy) != actions.end());

        if (scenario < 3)
        {
            ProcessAndCheck(*game, place);
            CHECK_EQ(player->GetFieldZone()->GetCount(), 3);
            CHECK_EQ(player->GetFieldZone()->GetLocations().size(), 2u);
        }
        else
        {
            ProcessAndCheck(*game, destroy);
            CHECK_EQ(enemyLocation->GetZoneType(), ZoneType::GRAVEYARD);
        }
    }
}

TEST_CASE("[PlayerAction] - Pending choices and unavailable game states")
{
    for (int option = 0; option < 3; ++option)
    {
        auto game = ActionGame();
        auto* player = game->GetCurrentPlayer();

        game->Process(player, PlayCardTask(Draw(player, "LOE_023")));

        REQUIRE(player->choice);

        const auto actions = EnumerateActions(*game);

        REQUIRE_EQ(actions.size(), player->choice->choices.size());

        for (const auto& action : actions)
        {
            CHECK(action.type == PlayerActionType::CHOOSE);
            CHECK(std::ranges::find(player->choice->choices, action.choiceID) !=
                  player->choice->choices.end());
        }

        REQUIRE(actions.size() > static_cast<std::size_t>(option));
        ProcessAndCheck(*game, actions[option]);
    }

    auto game = ActionGame();
    game->step = Step::MAIN_COMBAT;

    CHECK(EnumerateActions(*game).empty());

    game->step = Step::MAIN_ACTION;
    game->state = State::COMPLETE;

    CHECK(EnumerateActions(*game).empty());
}

TEST_CASE("[PolicyActions] - Version one layout and complete main actions")
{
    namespace Schema = PolicySchema;

    static_assert(
        std::is_same_v<Schema::LegalMask, std::array<std::uint8_t, 4846>>);

    CHECK_EQ(Schema::VERSION, 1);
    CHECK_EQ(Schema::OBSERVATION_VERSION, ObservationSchema::VERSION);
    CHECK_EQ(Schema::END_TURN, 0);
    CHECK_EQ(Schema::PLAY_CARD, 1);
    CHECK_EQ(Schema::ATTACK, 4761);
    CHECK_EQ(Schema::HERO_POWER, 4825);
    CHECK_EQ(Schema::CHOOSE, 4842);
    CHECK_EQ(Schema::NUM_ACTIONS, 4846);

    auto game = MixedActions();
    const auto* player = game->GetCurrentPlayer();
    const auto hand = player->GetHandZone()->GetAll();
    const auto before = EncodeObservation(*game);
    const auto randomBefore = effolkronium::random_static::get_engine();
    const PolicyActions policy(*game);

    CheckPolicyRoundTrips(*game, policy);
    CHECK(PolicyActions(*game).GetLegalMask() == policy.GetLegalMask());
    CHECK(EncodeObservation(*game) == before);
    CHECK(effolkronium::random_static::get_engine() == randomBefore);

    CHECK(policy.Decode(0) == PlayerAction{});
    CHECK(policy.Decode(1) ==
          PlayerAction{ PlayerActionType::PLAY_CARD, ID(hand[0]), -1, 0 });
    CHECK(policy.Decode(5) ==
          PlayerAction{ PlayerActionType::PLAY_CARD, ID(hand[0]), -1, 1 });
    CHECK(policy.Decode(477) ==
          PlayerAction{ PlayerActionType::PLAY_CARD, ID(hand[1]), -1, 0 });
    CHECK(policy.Decode(4761) ==
          PlayerAction{ PlayerActionType::ATTACK, ID(player->GetHero()),
                        ID(player->opponent->GetHero()) });
    CHECK(policy.Decode(4770) ==
          PlayerAction{ PlayerActionType::ATTACK,
                        ID((*player->GetFieldZone())[0]),
                        ID((*player->opponent->GetFieldZone())[0]) });
    CHECK(policy.Decode(4826) == PlayerAction{ PlayerActionType::HERO_POWER,
                                               ID(&player->GetHeroPower()),
                                               ID(player->GetHero()) });
    CHECK(policy.Decode(4834) ==
          PlayerAction{ PlayerActionType::HERO_POWER,
                        ID(&player->GetHeroPower()),
                        ID(player->opponent->GetHero()) });

    // Even ignored fields must match the canonical semantic action exactly.
    for (const auto invalid :
         { PlayerAction{ PlayerActionType::END_TURN, ID(hand[0]) },
           PlayerAction{ PlayerActionType::END_TURN, -1,
                         ID(player->GetHero()) },
           PlayerAction{ PlayerActionType::END_TURN, -1, -1, 0 },
           PlayerAction{ PlayerActionType::END_TURN, -1, -1, -1, 1 },
           PlayerAction{ PlayerActionType::END_TURN, -1, -1, -1, 0, 42 },
           PlayerAction{ static_cast<PlayerActionType>(99) },
           PlayerAction{ PlayerActionType::PLAY_CARD, ID(hand[0]), -1, -1 },
           PlayerAction{ PlayerActionType::PLAY_CARD, ID(hand[0]), -1, 0, 1 },
           PlayerAction{ PlayerActionType::HERO_POWER, -1,
                         ID(player->opponent->GetHero()) } })
    {
        CHECK_THROWS_AS(policy.Encode(invalid), std::invalid_argument);
    }

    CHECK_THROWS_AS(policy.Decode(Schema::NUM_ACTIONS), std::invalid_argument);
    CHECK_THROWS_AS(policy.Decode(std::numeric_limits<std::size_t>::max()),
                    std::invalid_argument);
}

TEST_CASE("[PolicyActions] - Untargeted and implicit-target hero powers")
{
    for (const auto heroClass : { CardClass::WARRIOR, CardClass::HUNTER })
    {
        auto game = ActionGame(heroClass);
        const PolicyActions policy(*game);
        const auto index = heroClass == CardClass::WARRIOR ? 4825 : 4834;

        CheckPolicyRoundTrips(*game, policy);
        CHECK_EQ(policy.Decode(index).targetID,
                 heroClass == CardClass::WARRIOR
                     ? -1
                     : ID(game->GetCurrentPlayer()->opponent->GetHero()));
        ProcessAndCheck(*game, policy.Decode(index));
        CHECK_EQ(PolicyActions(*game).GetLegalMask()[index], 0);
    }
}

TEST_CASE("[PolicyActions] - Choose One and Choose Both retain all fields")
{
    for (const bool chooseBoth : { false, true })
    {
        auto game = ActionGame(CardClass::DRUID);
        auto* player = game->GetCurrentPlayer();

        game->Process(player, PlayCardTask(Draw(player, "CS2_182")));

        const auto* keeper = Draw(player, "EX1_166");

        Draw(player, "AT_037");  // Options with different targeting rules.
        player->playerAuraEffects.SetValue(GameTag::CHOOSE_BOTH, chooseBoth);

        const PolicyActions policy(*game);

        CheckPolicyRoundTrips(*game, policy);

        for (int position = 0; position < 2; ++position)
        {
            for (int option = chooseBoth ? 0 : 1;
                 option <= (chooseBoth ? 0 : 2); ++option)
            {
                const PlayerAction action{ PlayerActionType::PLAY_CARD,
                                           ID(keeper),
                                           ID((*player->GetFieldZone())[0]),
                                           position, option };
                CHECK(policy.Decode(policy.Encode(action)) == action);
            }
        }
    }
}

TEST_CASE("[PolicyActions] - General choices use offered order")
{
    auto game = ActionGame();
    auto* player = game->GetCurrentPlayer();
    std::vector<int> offers;

    for (int slot = 0; slot < 4; ++slot)
    {
        auto* offer =
            Entity::GetFromCard(player, Cards::FindCardByID("CS2_182"));

        player->GetSetasideZone()->Add(offer);
        offers.push_back(ID(offer));
    }

    std::ranges::reverse(offers);

    player->choice = std::make_unique<Choice>(player);
    player->choice->choiceType = ChoiceType::GENERAL;
    player->choice->choiceAction = ChoiceAction::HAND;
    player->choice->choices = offers;

    const PolicyActions policy(*game);

    CheckPolicyRoundTrips(*game, policy);
    CHECK_EQ(policy.GetLegalMask()[PolicySchema::END_TURN], 0);

    for (std::size_t slot = 0; slot < offers.size(); ++slot)
    {
        CHECK(policy.Decode(4842 + slot) ==
              PlayerAction{ PlayerActionType::CHOOSE, -1, -1, -1, 0,
                            offers[slot] });
    }

    // Repeated IDs are one semantic action; only their first offer is active.
    player->choice->choices = { offers[0], offers[0], offers[1] };

    const PolicyActions repeated(*game);

    CheckPolicyRoundTrips(*game, repeated);
    CHECK_EQ(repeated.GetLegalMask()[4843], 0);
    CHECK_EQ(repeated.Decode(4844).choiceID, offers[1]);
    ProcessAndCheck(*game, repeated.Decode(4842));
    CHECK_EQ(PolicyActions(*game).GetLegalMask()[4842], 0);
}

TEST_CASE("[PolicyActions] - Slots are independent of IDs and absolute seats")
{
    auto first = MixedActions();
    auto second = MixedActions(PlayerType::PLAYER2);
    std::map<int, Playable*> renamed;

    for (const auto& [id, entity] : second->entityList)
    {
        entity->SetGameTag(GameTag::ENTITY_ID, 10000 - id);
        renamed.emplace(10000 - id, entity);
    }

    second->entityList = std::move(renamed);

    REQUIRE(EncodeObservation(*first) == EncodeObservation(*second));
    REQUIRE(EnumerateActions(*first) != EnumerateActions(*second));

    const PolicyActions firstPolicy(*first);
    const PolicyActions secondPolicy(*second);

    CheckPolicyRoundTrips(*second, secondPolicy);
    CHECK(firstPolicy.GetLegalMask() == secondPolicy.GetLegalMask());
    CHECK_EQ(secondPolicy.Decode(1).sourceID,
             ID(second->GetCurrentPlayer()->GetHandZone()->GetAll()[0]));
    CHECK_EQ(secondPolicy.Decode(4761).sourceID,
             ID(second->GetCurrentPlayer()->GetHero()));
    CHECK_EQ(secondPolicy.Decode(4834).targetID,
             ID(second->GetCurrentPlayer()->opponent->GetHero()));
}

TEST_CASE("[PolicyActions] - Masks follow legality and decision availability")
{
    auto game = MixedActions();
    auto* player = game->GetCurrentPlayer();

    SUBCASE("No mana")
    {
        player->SetTotalMana(0);
    }
    SUBCASE("Full board")
    {
        for (int slot = 1; slot < 7; ++slot)
        {
            game->Process(player, PlayCardTask(Draw(player, "CS2_231")));
        }

        REQUIRE_EQ(player->GetFieldZone()->GetCount(), 7);
        CHECK_EQ(PolicyActions(*game).GetLegalMask()[1], 0);
    }
    SUBCASE("Taunt")
    {
        (*player->opponent->GetFieldZone())[0]->SetGameTag(GameTag::TAUNT, 1);

        CHECK_EQ(PolicyActions(*game).GetLegalMask()[4761], 0);
        CHECK_EQ(PolicyActions(*game).GetLegalMask()[4762], 1);
    }
    SUBCASE("Exhausted and frozen attackers")
    {
        player->GetHero()->SetExhausted(true);
        (*player->GetFieldZone())[0]->SetGameTag(GameTag::FROZEN, 1);
    }
    SUBCASE("Terminal")
    {
        game->state = State::COMPLETE;
    }
    SUBCASE("Intermediate step")
    {
        game->step = Step::MAIN_COMBAT;
    }
    SUBCASE("Open task event")
    {
        game->taskQueue.StartEvent();
    }
    SUBCASE("Mulligan")
    {
        player->choice = std::make_unique<Choice>(player);
        player->choice->choiceType = ChoiceType::MULLIGAN;
    }
    SUBCASE("Opponent choice")
    {
        player->opponent->choice = std::make_unique<Choice>(player->opponent);
    }

    CheckPolicyRoundTrips(*game, PolicyActions(*game));
}

TEST_CASE("[PolicyActions] - Layout ceilings and location placement")
{
    auto game = ActionGame();
    auto* player = game->GetCurrentPlayer();

    SUBCASE("Last hand slot and insertion position")
    {
        for (int slot = 0; slot < 6; ++slot)
        {
            game->Process(player, PlayCardTask(Draw(player, "CS2_231")));
        }

        while (player->GetHandZone()->GetCount() < 10)
        {
            Draw(player, "CS2_231");
        }

        const PolicyActions policy(*game);

        CheckPolicyRoundTrips(*game, policy);
        CHECK(policy.Decode(4309) ==
              PlayerAction{ PlayerActionType::PLAY_CARD,
                            ID(player->GetHandZone()->GetAll()[9]), -1, 6 });
    }
    SUBCASE("Four Choose One options and overflow")
    {
        auto* card = Draw(player, "EX1_166");
        auto* original = card->card;
        Card metadata = *original;

        metadata.chooseCardIDs.resize(4, metadata.chooseCardIDs[0]);
        card->card = &metadata;

        const PolicyActions policy(*game);

        CheckPolicyRoundTrips(*game, policy);

        const PlayerAction last{ PlayerActionType::PLAY_CARD, ID(card),
                                 ID(player->opponent->GetHero()), 0, 4 };

        CHECK(policy.Decode(policy.Encode(last)) == last);

        metadata.chooseCardIDs.push_back(metadata.chooseCardIDs[0]);
        CHECK_THROWS_AS(PolicyActions{ *game }, std::invalid_argument);
        card->card = original;
    }
    SUBCASE("Hand overflow")
    {
        player->GetHandZone()->Expand(11);

        while (player->GetHandZone()->GetCount() < 11)
        {
            Draw(player, "CS2_231");
        }

        CHECK_THROWS_AS(PolicyActions{ *game }, std::invalid_argument);
    }
    SUBCASE("Offer overflow")
    {
        player->choice = std::make_unique<Choice>(player);
        player->choice->choiceType = ChoiceType::GENERAL;
        player->choice->choices.assign(5,
                                       ID(player->GetHandZone()->GetAll()[0]));

        CHECK_THROWS_AS(PolicyActions{ *game }, std::invalid_argument);
    }
    SUBCASE("Phase 1 locations still use board and target slots")
    {
        auto* location = Draw(player, "REV_983");

        game->Process(player, PlayCardTask(location));
        game->Process(player, EndTurnTask());

        player = game->GetCurrentPlayer();
        player->SetTotalMana(10);

        game->Process(player, PlayCardTask(Draw(player, "CS2_231")));

        Draw(player, "REV_983");

        const auto* renovator = Draw(player, "REV_023");
        const PolicyActions policy(*game);

        CheckPolicyRoundTrips(*game, policy);

        const PlayerAction action{ PlayerActionType::PLAY_CARD, ID(renovator),
                                   ID(location), 1 };

        ProcessAndCheck(*game, policy.Decode(policy.Encode(action)));
        CHECK_EQ(location->GetZoneType(), ZoneType::GRAVEYARD);
    }
}
