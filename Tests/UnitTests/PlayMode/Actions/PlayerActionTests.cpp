// Copyright (c) 2026 Chris Ohk

#include "doctest_proxy.hpp"

#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Actions/PlayerAction.hpp>
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

#include <algorithm>
#include <memory>

using namespace RosettaStone;
using namespace PlayMode;
using namespace PlayerTasks;

namespace
{
int ID(const Entity* entity)
{
    return entity->GetGameTag(GameTag::ENTITY_ID);
}

std::unique_ptr<Game> ActionGame(CardClass heroClass = CardClass::MAGE)
{
    GameConfig config;
    config.formatType = FormatType::WILD;
    config.player1Class = heroClass;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
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

std::unique_ptr<Game> MixedActions()
{
    auto game = ActionGame();
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
}  // namespace

TEST_CASE("[PlayerAction] - Complete deterministic main actions")
{
    auto game = MixedActions();
    auto* player = game->GetCurrentPlayer();
    const auto actions = EnumerateActions(*game);

    CHECK(std::ranges::is_sorted(actions));
    CHECK(std::ranges::adjacent_find(actions) == actions.end());
    CHECK(actions == EnumerateActions(*game));
    CHECK_EQ(std::ranges::count(actions, PlayerAction{}), 1);

    for (auto* card : player->GetHandZone()->GetAll())
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
    auto* fireball = Draw(player, "CS2_029");

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
    auto* execute = Draw(empty->GetCurrentPlayer(), "CS2_108");
    const auto noTargets = EnumerateActions(*empty);

    CHECK_FALSE(std::ranges::any_of(noTargets, [execute](const auto& action) {
        return action.sourceID == ID(execute);
    }));
}

TEST_CASE("[PlayerAction] - Attack restrictions")
{
    auto game = MixedActions();
    auto* player = game->GetCurrentPlayer();
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
        auto* player = game->GetCurrentPlayer();
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

            auto* target = (*player->GetFieldZone())[0];
            auto* wrath = Draw(player, "EX1_154");

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
        auto* roots = Draw(player, "AT_037");
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

        auto* location = Draw(player, "REV_983");
        auto* renovator = Draw(player, "REV_023");
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
