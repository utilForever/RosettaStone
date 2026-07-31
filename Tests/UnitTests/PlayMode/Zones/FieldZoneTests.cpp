// Copyright (c) 2017-2024 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Utils/TestUtils.hpp>

#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Conditions/SelfCondition.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/PlayCardTask.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>

using namespace RosettaStone;
using namespace PlayMode;
using namespace PlayerTasks;

TEST_CASE("[FieldZone] - GetAll")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    auto& curField = *(curPlayer->GetFieldZone());

    Playable* playable1 =
        Entity::GetFromCard(curPlayer, Cards::FindCardByName("Flame Imp"),
                            std::nullopt, curPlayer->GetFieldZone());
    curField.Add(playable1);

    Playable* playable2 =
        Entity::GetFromCard(curPlayer, Cards::FindCardByName("Wisp"),
                            std::nullopt, curPlayer->GetFieldZone());
    curField.Add(playable2);

    auto minions = curField.GetMinions();

    CHECK_EQ(minions[0]->card->name, "Flame Imp");
    CHECK_EQ(minions[1]->card->name, "Wisp");

    auto untouchableCard = TestUtils::GenerateMinionCard("untouchable", 0, 1);
    auto replacementCard = TestUtils::GenerateMinionCard("replacement", 1, 1);

    untouchableCard.gameTags[GameTag::UNTOUCHABLE] = 1;

    auto* untouchable =
        dynamic_cast<Minion*>(Entity::GetFromCard(curPlayer, &untouchableCard));
    auto* replacement =
        dynamic_cast<Minion*>(Entity::GetFromCard(curPlayer, &replacementCard));

    curField.Add(untouchable);
    CHECK_EQ(curField.GetCountExceptUntouchables(), 2);
    curField.Remove(untouchable);
    CHECK_EQ(curField.GetCountExceptUntouchables(), 2);

    curField.Add(untouchable);
    curField.Replace(untouchable, replacement);
    CHECK_EQ(curField.GetCountExceptUntouchables(), 3);
}

TEST_CASE("[FieldZone] - Location is a character, not a minion")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* player = game.GetCurrentPlayer();
    Playable* location =
        Entity::GetFromCard(player, Cards::FindCardByName("Great Hall"));

    CHECK(dynamic_cast<Character*>(location));
    CHECK_FALSE(dynamic_cast<Minion*>(location));
}

TEST_CASE("[FieldZone] - Location does not satisfy minion presence condition")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* player = game.GetCurrentPlayer();
    player->SetTotalMana(10);
    player->SetUsedMana(0);

    Playable* location =
        Generic::DrawCard(player, Cards::FindCardByName("Great Hall"));
    Playable* minion = Generic::DrawCard(player, Cards::FindCardByName("Wisp"));

    game.Process(player, PlayCardTask::Location(location));
    CHECK_EQ(player->GetFieldZone()->GetLocations().size(), 1u);
    CHECK_FALSE(SelfCondition::IsFieldNotEmpty().Evaluate(location));

    game.Process(player, PlayCardTask::Minion(minion));
    CHECK(SelfCondition::IsFieldNotEmpty().Evaluate(location));
}
