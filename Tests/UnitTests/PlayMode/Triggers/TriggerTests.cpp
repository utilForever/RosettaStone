// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Utils/TestUtils.hpp>

#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Games/GameConfig.hpp>
#include <Rosetta/PlayMode/Triggers/Trigger.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>

using namespace RosettaStone;
using namespace PlayMode;
using namespace TestUtils;

TEST_CASE("[Trigger] - None")
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(std::make_shared<Trigger>(TriggerType::NONE));

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST_CASE("[Trigger] - TurnStart")
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_START));

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST_CASE("[Trigger] - TurnEnd")
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST_CASE("[Trigger] - PlayCard")
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(std::make_shared<Trigger>(TriggerType::PLAY_CARD));

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST_CASE("[Trigger] - PlayMinion")
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(std::make_shared<Trigger>(TriggerType::PLAY_MINION));

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST_CASE("[Trigger] - CastSpell")
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(std::make_shared<Trigger>(TriggerType::CAST_SPELL));

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST_CASE("[Trigger] - AfterCast")
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(std::make_shared<Trigger>(TriggerType::AFTER_CAST));

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST_CASE("[Trigger] - GiveHeal")
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(std::make_shared<Trigger>(TriggerType::GIVE_HEAL));

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST_CASE("[Trigger] - TakeHeal")
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TAKE_HEAL));

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST_CASE("[Trigger] - Attack")
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST_CASE("[Trigger] - AfterAttack_None")
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    card1.power.GetTrigger()->triggerSource = TriggerSource::NONE;

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST_CASE("[Trigger] - AfterAttack_Hero")
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    card1.power.GetTrigger()->triggerSource = TriggerSource::HERO;

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST_CASE("[Trigger] - AfterAttack_Self")
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    card1.power.GetTrigger()->triggerSource = TriggerSource::SELF;

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST_CASE("[Trigger] - AfterAttack_EnchantmentTarget")
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curGraveyard = *(curPlayer->GetGraveyardZone());

    auto card1 = GenerateEnchantmentCard("enchant1");
    auto card2 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    card1.power.GetTrigger()->triggerSource = TriggerSource::ENCHANTMENT_TARGET;

    PlayMinionCard(curPlayer, &card2);
    PlayEnchantmentCard(curPlayer, &card1, curField[0]);

    curGraveyard[0]->card->power.GetTrigger()->Activate(curGraveyard[0]);
    curGraveyard[0]->activatedTrigger->Remove();

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST_CASE("[Trigger] - Summon")
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(std::make_shared<Trigger>(TriggerType::SUMMON));

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST_CASE("[Trigger] - AfterSummon")
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_SUMMON));

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST_CASE("[Trigger] - DealDamage")
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(std::make_shared<Trigger>(TriggerType::DEAL_DAMAGE));
    card1.power.GetTrigger()->triggerSource = TriggerSource::SELF;

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST_CASE("[Trigger] - TakeDamage")
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TAKE_DAMAGE));

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST_CASE("[Trigger] - Predamage_None")
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(std::make_shared<Trigger>(TriggerType::PREDAMAGE));
    card1.power.GetTrigger()->triggerSource = TriggerSource::NONE;

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST_CASE("[Trigger] - Predamage_Hero")
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curGraveyard = *(curPlayer->GetGraveyardZone());

    auto card1 = GenerateEnchantmentCard("enchant1");
    auto card2 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(std::make_shared<Trigger>(TriggerType::PREDAMAGE));
    card1.power.GetTrigger()->triggerSource = TriggerSource::HERO;

    PlayMinionCard(curPlayer, &card2);
    PlayEnchantmentCard(curPlayer, &card1, curField[0]);

    curGraveyard[0]->card->power.GetTrigger()->Activate(curGraveyard[0]);
    curGraveyard[0]->activatedTrigger->Remove();

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST_CASE("[Trigger] - Predamage_Self")
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(std::make_shared<Trigger>(TriggerType::PREDAMAGE));
    card1.power.GetTrigger()->triggerSource = TriggerSource::SELF;

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST_CASE("[Trigger] - Predamage_EnchantmentTarget")
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curGraveyard = *(curPlayer->GetGraveyardZone());

    auto card1 = GenerateEnchantmentCard("enchant1");
    auto card2 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(std::make_shared<Trigger>(TriggerType::PREDAMAGE));
    card1.power.GetTrigger()->triggerSource = TriggerSource::ENCHANTMENT_TARGET;

    PlayMinionCard(curPlayer, &card2);
    PlayEnchantmentCard(curPlayer, &card1, curField[0]);

    curGraveyard[0]->card->power.GetTrigger()->Activate(curGraveyard[0]);
    curGraveyard[0]->activatedTrigger->Remove();

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}

TEST_CASE("[Trigger] - Target")
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

    auto& curField = *(curPlayer->GetFieldZone());

    auto card1 = GenerateMinionCard("minion1", 3, 6);
    card1.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TARGET));

    PlayMinionCard(curPlayer, &card1);

    curField[0]->Destroy();
    game.ProcessDestroyAndUpdateAura();
}