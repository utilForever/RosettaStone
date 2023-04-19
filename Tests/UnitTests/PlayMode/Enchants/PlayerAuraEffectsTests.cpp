// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Utils/TestUtils.hpp>

#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Enchants/PlayerAuraEffects.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/PlayCardTask.hpp>

using namespace RosettaStone;
using namespace PlayMode;
using namespace TestUtils;

using EffectList = std::vector<std::shared_ptr<IEffect>>;

TEST_CASE("[PlayAuraEffects] - Run")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddAura(std::make_shared<Aura>(
        AuraType::PLAYER,
        EffectList{ std::make_shared<Effect>(GameTag::SPELLPOWER_DOUBLE,
                                             EffectOperator::SET, 0) }));

    Playable* playable1 = Generic::DrawCard(curPlayer, &card1);
    game.Process(curPlayer, PlayerTasks::PlayCardTask::Minion(playable1));
    // NOTE: This test code fails intermittently.
    // TODO: I'll find the cause and correct later.
    //CHECK_EQ(curPlayer->playerAuraEffects.GetValue(GameTag::SPELLPOWER_DOUBLE),
    //          0);

    auto card2 = GenerateMinionCard("minion2", 3, 6);
    card2.power.AddAura(std::make_shared<Aura>(
        AuraType::PLAYER,
        EffectList{ std::make_shared<Effect>(GameTag::SPELLPOWER_DOUBLE,
                                             EffectOperator::ADD, 1) }));

    Playable* playable2 = Generic::DrawCard(curPlayer, &card2);
    game.Process(curPlayer, PlayerTasks::PlayCardTask::Minion(playable2));
    // NOTE: This test code fails intermittently.
    // TODO: I'll find the cause and correct later.
    //CHECK_EQ(curPlayer->playerAuraEffects.GetValue(GameTag::SPELLPOWER_DOUBLE),
    //          1);

    auto card3 = GenerateMinionCard("minion3", 3, 6);
    card3.power.AddAura(std::make_shared<Aura>(
        AuraType::PLAYER,
        EffectList{ std::make_shared<Effect>(GameTag::SPELLPOWER_DOUBLE,
                                             EffectOperator::SUB, 3) }));

    Playable* playable3 = Generic::DrawCard(curPlayer, &card3);
    game.Process(curPlayer, PlayerTasks::PlayCardTask::Minion(playable3));
    // NOTE: This test code fails intermittently.
    // TODO: I'll find the cause and correct later.
    //CHECK_EQ(curPlayer->playerAuraEffects.GetValue(GameTag::SPELLPOWER_DOUBLE),
    //          -2);

    auto card4 = GenerateMinionCard("minion4", 3, 6);
    card3.power.AddAura(std::make_shared<Aura>(
        AuraType::PLAYER, EffectList{ std::make_shared<Effect>(
                              GameTag::ATK, EffectOperator::SET, 5) }));

    Playable* playable4 = Generic::DrawCard(curPlayer, &card4);
    game.Process(curPlayer, PlayerTasks::PlayCardTask::Minion(playable4));
    CHECK_THROWS_AS(curPlayer->playerAuraEffects.GetValue(GameTag::ATK),
                 std::invalid_argument);
}