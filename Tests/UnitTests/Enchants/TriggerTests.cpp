// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Enchants/Trigger.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Games/GameConfig.hpp>
#include <Rosetta/Zones/FieldZone.hpp>
#include <Rosetta/Zones/GraveyardZone.hpp>

using namespace RosettaStone;
using namespace TestUtils;

TEST(Trigger, None)
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(new Trigger(TriggerType::NONE));

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST(Trigger, TurnStart)
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(new Trigger(TriggerType::TURN_START));

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST(Trigger, TurnEnd)
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(new Trigger(TriggerType::TURN_END));

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST(Trigger, PlayCard)
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(new Trigger(TriggerType::PLAY_CARD));

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST(Trigger, PlayMinion)
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(new Trigger(TriggerType::PLAY_MINION));

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST(Trigger, CastSpell)
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(new Trigger(TriggerType::CAST_SPELL));

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST(Trigger, AfterCast)
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(new Trigger(TriggerType::AFTER_CAST));

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST(Trigger, Heal)
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(new Trigger(TriggerType::HEAL));

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST(Trigger, Attack)
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(new Trigger(TriggerType::ATTACK));

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST(Trigger, AfterAttack_None)
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(new Trigger(TriggerType::AFTER_ATTACK));
    card1.power.GetTrigger()->triggerSource = TriggerSource::NONE;

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST(Trigger, AfterAttack_Hero)
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(new Trigger(TriggerType::AFTER_ATTACK));
    card1.power.GetTrigger()->triggerSource = TriggerSource::HERO;

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST(Trigger, AfterAttack_Self)
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(new Trigger(TriggerType::AFTER_ATTACK));
    card1.power.GetTrigger()->triggerSource = TriggerSource::SELF;

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST(Trigger, AfterAttack_EnchantmentTarget)
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curGraveyard = *(curPlayer->GetGraveyardZone());

    auto card1 = GenerateEnchantmentCard("enchant1");
    auto card2 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(new Trigger(TriggerType::AFTER_ATTACK));
    card1.power.GetTrigger()->triggerSource = TriggerSource::ENCHANTMENT_TARGET;

    PlayMinionCard(curPlayer, &card2);
    PlayEnchantmentCard(curPlayer, &card1, curField[0]);

    curGraveyard[0]->card->power.GetTrigger()->Activate(curGraveyard[0]);
    curGraveyard[0]->activatedTrigger->Remove();

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST(Trigger, Summon)
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(new Trigger(TriggerType::SUMMON));

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST(Trigger, AfterSummon)
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(new Trigger(TriggerType::AFTER_SUMMON));

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST(Trigger, DealDamage)
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(new Trigger(TriggerType::DEAL_DAMAGE));
    card1.power.GetTrigger()->triggerSource = TriggerSource::SELF;

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST(Trigger, TakeDamage)
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(new Trigger(TriggerType::TAKE_DAMAGE));

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST(Trigger, Predamage_None)
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(new Trigger(TriggerType::PREDAMAGE));
    card1.power.GetTrigger()->triggerSource = TriggerSource::NONE;

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST(Trigger, Predamage_Hero)
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curGraveyard = *(curPlayer->GetGraveyardZone());

    auto card1 = GenerateEnchantmentCard("enchant1");
    auto card2 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(new Trigger(TriggerType::PREDAMAGE));
    card1.power.GetTrigger()->triggerSource = TriggerSource::HERO;

    PlayMinionCard(curPlayer, &card2);
    PlayEnchantmentCard(curPlayer, &card1, curField[0]);

    curGraveyard[0]->card->power.GetTrigger()->Activate(curGraveyard[0]);
    curGraveyard[0]->activatedTrigger->Remove();

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST(Trigger, Predamage_Self)
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(new Trigger(TriggerType::PREDAMAGE));
    card1.power.GetTrigger()->triggerSource = TriggerSource::SELF;

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST(Trigger, Predamage_EnchantmentTarget)
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curGraveyard = *(curPlayer->GetGraveyardZone());

    auto card1 = GenerateEnchantmentCard("enchant1");
    auto card2 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(new Trigger(TriggerType::PREDAMAGE));
    card1.power.GetTrigger()->triggerSource = TriggerSource::ENCHANTMENT_TARGET;

    PlayMinionCard(curPlayer, &card2);
    PlayEnchantmentCard(curPlayer, &card1, curField[0]);

    curGraveyard[0]->card->power.GetTrigger()->Activate(curGraveyard[0]);
    curGraveyard[0]->activatedTrigger->Remove();

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST(Trigger, Target)
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(new Trigger(TriggerType::TARGET));

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}