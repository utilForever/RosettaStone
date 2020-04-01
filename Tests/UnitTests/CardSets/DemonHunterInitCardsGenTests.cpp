// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.hpp>
#include <Utils/TestUtils.hpp>

#include <Rosetta/Actions/Draw.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Zones/FieldZone.hpp>
#include <Rosetta/Zones/HandZone.hpp>

using namespace RosettaStone;
using namespace PlayerTasks;
using namespace SimpleTasks;

// ------------------------------------ SPELL - DEMONHUNTER
// [BT_173] Command the Illidari - COST:5
// - Set: Demon Hunter Initiate, Rarity: Common
// --------------------------------------------------------
// Text: Summon six 1/1 Illidari with <b>Rush</b>.
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - BT_173 : Command the Illidari")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::DEMONHUNTER;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Command the Illidari"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(opField.GetCount(), 6);
    CHECK_EQ(opField[0]->card->name, "Illidari Initiate");
    CHECK_EQ(opField[0]->GetAttack(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 1);
    CHECK_EQ(opField[0]->IsRush(), true);
    CHECK_EQ(opField[1]->card->name, "Illidari Initiate");
    CHECK_EQ(opField[1]->GetAttack(), 1);
    CHECK_EQ(opField[1]->GetHealth(), 1);
    CHECK_EQ(opField[1]->IsRush(), true);
    CHECK_EQ(opField[2]->card->name, "Illidari Initiate");
    CHECK_EQ(opField[2]->GetAttack(), 1);
    CHECK_EQ(opField[2]->GetHealth(), 1);
    CHECK_EQ(opField[2]->IsRush(), true);
    CHECK_EQ(opField[3]->card->name, "Illidari Initiate");
    CHECK_EQ(opField[3]->GetAttack(), 1);
    CHECK_EQ(opField[3]->GetHealth(), 1);
    CHECK_EQ(opField[3]->IsRush(), true);
    CHECK_EQ(opField[4]->card->name, "Illidari Initiate");
    CHECK_EQ(opField[4]->GetAttack(), 1);
    CHECK_EQ(opField[4]->GetHealth(), 1);
    CHECK_EQ(opField[4]->IsRush(), true);
    CHECK_EQ(opField[5]->card->name, "Illidari Initiate");
    CHECK_EQ(opField[5]->GetAttack(), 1);
    CHECK_EQ(opField[5]->GetHealth(), 1);
    CHECK_EQ(opField[5]->IsRush(), true);

    game.Process(opPlayer, AttackTask(opField[0], card1));
    game.Process(opPlayer, AttackTask(opField[0], card1));
    game.Process(opPlayer, AttackTask(opField[0], card1));
    game.Process(opPlayer, AttackTask(opField[0], card1));
    game.Process(opPlayer, AttackTask(opField[0], card1));
    game.Process(opPlayer, AttackTask(opField[0], card1));
    CHECK_EQ(curField[0]->GetHealth(), 6);
    CHECK_EQ(opField.GetCount(), 0);
}

// ------------------------------------ SPELL - DEMONHUNTER
// [BT_175] Twin Slice - COST:0
// - Set: Demon Hunter Initiate, Rarity: Common
// --------------------------------------------------------
// Text: Give your hero +1 Attack this turn.
//       Add 'Second Slice' to your hand.
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - BT_175 : Twin Slice")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Twin Slice"));

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 2);
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Second Slice");

    game.Process(curPlayer, PlayCardTask::Spell(curHand[4]));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
}

// ----------------------------------- WEAPON - DEMONHUNTER
// [BT_271] Flamereaper - COST:7 [ATK:4/HP:0]
// - Set: Demon Hunter Initiate, Rarity: Epic
// --------------------------------------------------------
// Text: Also damages the minions next to whomever your hero attacks.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// - DURABILITY = 3
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Weapon] - BT_271 : Flamereaper")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flamereaper"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Dalaran Mage"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Dalaran Mage"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Dalaran Mage"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), true);
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 4);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 3);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 5);

    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 25);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField.GetCount(), 3);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(curPlayer->GetHero(), card3));
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 1);
    CHECK_EQ(opField.GetCount(), 0);
}

// ----------------------------------- MINION - DEMONHUNTER
// [BT_351] Battlefiend (*) - COST:1 [ATK:2/HP:2]
// - Race: Demon, Set: Demon Hunter Initiate, Rarity: Common
// --------------------------------------------------------
// Text: After your hero attacks, gain +1 Attack.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - BT_351 : Battlefiend")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Battlefiend"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 2);

    game.Process(curPlayer, HeroPowerTask());
    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(curField[0]->GetAttack(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask());
    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(curField[0]->GetAttack(), 4);
}

// ------------------------------------ SPELL - DEMONHUNTER
// [BT_354] Blade Dance - COST:2
// - Set: Demon Hunter Initiate, Rarity: Rare
// --------------------------------------------------------
// Text: Deal damage equal to your hero's Attack
//       to 3 random enemy minions.
// --------------------------------------------------------
// GameTag:
// - AFFECTED_BY_SPELL_POWER = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_MINIMUM_ENEMY_MINIONS = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - BT_354 : Blade Dance")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::DEMONHUNTER;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dalaran Mage"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dalaran Mage"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Blade Dance"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField.GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask());
    CHECK_EQ(opPlayer->GetHero()->GetAttack(), 1);

    game.Process(opPlayer, PlayCardTask::Spell(card5));
    bool check1 = curField.GetCount() == 2 && (curField[0]->GetHealth() == 3 ||
                                               curField[1]->GetHealth() == 3);
    bool check2 =
        curField.GetCount() == 3 &&
        ((curField[0]->GetHealth() == 1 && curField[1]->GetHealth() == 3 &&
          curField[2]->GetHealth() == 3) ||
         (curField[0]->GetHealth() == 3 && curField[1]->GetHealth() == 3 &&
          curField[2]->GetHealth() == 1));
    bool check = check1 || check2;
    CHECK_EQ(check, true);
}