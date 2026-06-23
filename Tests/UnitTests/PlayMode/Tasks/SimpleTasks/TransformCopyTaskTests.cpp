// Copyright (c) 2017-2024 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Enchantment.hpp>
#include <Rosetta/PlayMode/Models/Minion.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/TransformCopyTask.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>

#include <map>

using namespace RosettaStone;
using namespace PlayMode;
using namespace SimpleTasks;

TEST_CASE("[TransformCopyTask] - Invalid source stops")
{
    TransformCopyTask task;

    CHECK_EQ(task.Run(), TaskStatus::STOP);
}

TEST_CASE("[TransformCopyTask] - Source outside play stops")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    const std::map<GameTag, int> tags;

    Minion source(curPlayer, Cards::FindCardByName("Wisp"), tags, -1);
    Minion target(curPlayer, Cards::FindCardByName("Wisp"), tags, -1);

    TransformCopyTask task;
    task.SetPlayer(curPlayer);
    task.SetSource(&source);
    task.SetTarget(&target);

    CHECK_EQ(task.Run(), TaskStatus::STOP);
}

TEST_CASE("[TransformCopyTask] - Non-minion copied card stops")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    const std::map<GameTag, int> tags;

    Minion source(curPlayer, Cards::FindCardByName("Wisp"), tags, -1);
    Minion target(curPlayer, Cards::FindCardByName("Fireball"), tags, -1);
    source.SetZoneType(ZoneType::PLAY);

    TransformCopyTask task;
    task.SetPlayer(curPlayer);
    task.SetSource(&source);
    task.SetTarget(&target);

    CHECK_EQ(task.Run(), TaskStatus::STOP);
}

TEST_CASE("[TransformCopyTask] - Copies enchantment script tags")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    const std::map<GameTag, int> tags;

    const auto source =
        new Minion(curPlayer, Cards::FindCardByName("Murloc Raider"), tags, -1);
    Minion target(curPlayer, Cards::FindCardByName("Wisp"), tags, -1);

    FieldZone& field = *(curPlayer->GetFieldZone());
    field.Add(source);

    Card enchantmentCard;
    Enchantment::GetInstance(&target, &enchantmentCard, &target, 1, 2);

    TransformCopyTask task;
    task.SetPlayer(curPlayer);
    task.SetSource(source);
    task.SetTarget(&target);

    CHECK_EQ(task.Run(), TaskStatus::COMPLETE);
    CHECK_EQ(field.GetCount(), 1);
    CHECK_EQ(field[0]->appliedEnchantments.size(), 1u);
    CHECK_EQ(field[0]->appliedEnchantments[0]->GetScriptTag1(), 1);
    CHECK_EQ(field[0]->appliedEnchantments[0]->GetScriptTag2(), 2);
}
