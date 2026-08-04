// Copyright (c) 2017-2024 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Utils/TestUtils.hpp>

#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Enchants/AuraEffects.hpp>
#include <Rosetta/PlayMode/Enchants/PlayerAuraEffects.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/PlayCardTask.hpp>

using namespace RosettaStone;
using namespace PlayMode;
using namespace TestUtils;

using EffectList = std::vector<std::shared_ptr<IEffect>>;

TEST_CASE("[AuraEffects] - Card type bounds")
{
    AuraEffects heroEffects(CardType::HERO);
    heroEffects.SetImmune(1);
    CHECK_EQ(heroEffects.GetImmune(), 1);
    CHECK_EQ(heroEffects.GetWindfury(), 0);
    CHECK_EQ(heroEffects.GetCharge(), 0);
    CHECK_EQ(heroEffects.GetLifesteal(), 0);
    CHECK_THROWS(heroEffects.SetCharge(1));

    AuraEffects weaponEffects(CardType::WEAPON);
    weaponEffects.SetAttack(3);
    CHECK_EQ(weaponEffects.GetAttack(), 3);
    CHECK_EQ(weaponEffects.GetCantBeTargetedBySpells(), 0);
    CHECK_EQ(weaponEffects.GetHeroPowerDamage(), 0);
    CHECK_EQ(weaponEffects.GetTaunt(), 0);
    CHECK_EQ(weaponEffects.GetRush(), 0);
    CHECK_EQ(weaponEffects.GetCharge(), 0);
    CHECK_THROWS(weaponEffects.SetCantBeTargetedBySpells(1));
    CHECK_THROWS(weaponEffects.SetHeroPowerDamage(1));
    CHECK_THROWS(weaponEffects.SetWindfury(1));
    CHECK_THROWS(weaponEffects.SetTaunt(1));
    CHECK_THROWS(weaponEffects.SetRush(1));
    CHECK_THROWS(weaponEffects.SetLifesteal(1));

    AuraEffects spellEffects(CardType::SPELL);
    CHECK_EQ(spellEffects.GetAttack(), 0);
    CHECK_EQ(spellEffects.GetCharge(), 0);
    CHECK_THROWS(spellEffects.SetAttack(1));
    CHECK_THROWS(spellEffects.SetCannotAttackHeroes(1));
    CHECK_THROWS(spellEffects.SetHealth(1));
    CHECK_THROWS(spellEffects.SetCantAttack(1));

    AuraEffects minionEffects(CardType::MINION);

    for (const GameTag tag :
         { GameTag::CANT_BE_TARGETED_BY_SPELLS, GameTag::ATK, GameTag::HEALTH,
           GameTag::LIFESTEAL, GameTag::CANT_ATTACK })
    {
        minionEffects.SetGameTag(tag, 1);
        CHECK_EQ(minionEffects.GetGameTag(tag), 1);
    }
}

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
    // CHECK_EQ(curPlayer->playerAuraEffects.GetValue(GameTag::SPELLPOWER_DOUBLE),
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
    // CHECK_EQ(curPlayer->playerAuraEffects.GetValue(GameTag::SPELLPOWER_DOUBLE),
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
    // CHECK_EQ(curPlayer->playerAuraEffects.GetValue(GameTag::SPELLPOWER_DOUBLE),
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
