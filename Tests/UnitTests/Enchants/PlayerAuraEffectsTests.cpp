// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <Rosetta/Actions/Draw.hpp>
#include <Rosetta/Enchants/PlayerAuraEffects.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/PlayerTasks/PlayCardTask.hpp>

using namespace RosettaStone;
using namespace TestUtils;

TEST(PlayAuraEffects, Run)
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddAura(new Aura(
        AuraType::PLAYER,
        { new Effect(GameTag::SPELLPOWER_DOUBLE, EffectOperator::SET, 0) }));

    Playable* playable1 = Generic::DrawCard(curPlayer, &card1);
    game.Process(curPlayer, PlayerTasks::PlayCardTask::Minion(playable1));
    EXPECT_EQ(curPlayer->playerAuraEffects.GetValue(GameTag::SPELLPOWER_DOUBLE),
              0);

    auto card2 = GenerateMinionCard("minion2", 3, 6);
    card2.power.AddAura(new Aura(
        AuraType::PLAYER,
        { new Effect(GameTag::SPELLPOWER_DOUBLE, EffectOperator::ADD, 1) }));

    Playable* playable2 = Generic::DrawCard(curPlayer, &card2);
    game.Process(curPlayer, PlayerTasks::PlayCardTask::Minion(playable2));
    EXPECT_EQ(curPlayer->playerAuraEffects.GetValue(GameTag::SPELLPOWER_DOUBLE),
              1);

    auto card3 = GenerateMinionCard("minion3", 3, 6);
    card3.power.AddAura(new Aura(
        AuraType::PLAYER,
        { new Effect(GameTag::SPELLPOWER_DOUBLE, EffectOperator::SUB, 3) }));

    Playable* playable3 = Generic::DrawCard(curPlayer, &card3);
    game.Process(curPlayer, PlayerTasks::PlayCardTask::Minion(playable3));
    EXPECT_EQ(curPlayer->playerAuraEffects.GetValue(GameTag::SPELLPOWER_DOUBLE),
              -2);
}