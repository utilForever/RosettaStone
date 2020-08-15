// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.hpp>
#include <Utils/TestUtils.hpp>

#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

using namespace RosettaStone;
using namespace PlayMode;
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
    CHECK_EQ(opField[0]->HasRush(), true);
    CHECK_EQ(opField[1]->card->name, "Illidari Initiate");
    CHECK_EQ(opField[1]->GetAttack(), 1);
    CHECK_EQ(opField[1]->GetHealth(), 1);
    CHECK_EQ(opField[1]->HasRush(), true);
    CHECK_EQ(opField[2]->card->name, "Illidari Initiate");
    CHECK_EQ(opField[2]->GetAttack(), 1);
    CHECK_EQ(opField[2]->GetHealth(), 1);
    CHECK_EQ(opField[2]->HasRush(), true);
    CHECK_EQ(opField[3]->card->name, "Illidari Initiate");
    CHECK_EQ(opField[3]->GetAttack(), 1);
    CHECK_EQ(opField[3]->GetHealth(), 1);
    CHECK_EQ(opField[3]->HasRush(), true);
    CHECK_EQ(opField[4]->card->name, "Illidari Initiate");
    CHECK_EQ(opField[4]->GetAttack(), 1);
    CHECK_EQ(opField[4]->GetHealth(), 1);
    CHECK_EQ(opField[4]->HasRush(), true);
    CHECK_EQ(opField[5]->card->name, "Illidari Initiate");
    CHECK_EQ(opField[5]->GetAttack(), 1);
    CHECK_EQ(opField[5]->GetHealth(), 1);
    CHECK_EQ(opField[5]->HasRush(), true);

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
// [BT_175] Twin Slice - COST:1
// - Set: Demon Hunter Initiate, Rarity: Common
// --------------------------------------------------------
// Text: Give your hero +2 Attack this turn.
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
    CHECK_EQ(curPlayer->GetRemainingMana(), 8);
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 3);
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Second Slice");

    game.Process(curPlayer, PlayCardTask::Spell(curHand[4]));
    CHECK_EQ(curPlayer->GetRemainingMana(), 7);
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 5);

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
// [BT_351] Battlefiend (*) - COST:1 [ATK:1/HP:2]
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
    CHECK_EQ(curField[0]->GetAttack(), 1);

    game.Process(curPlayer, HeroPowerTask());
    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(curField[0]->GetAttack(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask());
    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(curField[0]->GetAttack(), 3);
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

// ----------------------------------- MINION - DEMONHUNTER
// [BT_355] Wrathscale Naga (*) - COST:3 [ATK:3/HP:1]
// - Set: Demon Hunter Initiate, Rarity: Epic
// --------------------------------------------------------
// Text: After a friendly minion dies,
//       deal 3 damage to a random enemy.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - BT_355 : Wrathscale Naga")
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

    auto curHero = curPlayer->GetHero();
    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wrathscale Naga"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Coordinated Strike"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 12);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Spell(card3));

    game.Process(opPlayer, AttackTask(opField[1], card1));
    int totalHealth = curHero->GetHealth() + curField[0]->GetHealth();
    CHECK_EQ(totalHealth, 38);

    game.Process(opPlayer, AttackTask(opField[1], card1));
    totalHealth = curHero->GetHealth() + curField[0]->GetHealth();
    CHECK_EQ(totalHealth, 34);

    game.Process(opPlayer, AttackTask(opField[1], card1));
    totalHealth = curField.GetCount() == 0
                      ? curHero->GetHealth()
                      : curHero->GetHealth() + curField[0]->GetHealth();
    CHECK_EQ(totalHealth, 30);
}

// ----------------------------------- MINION - DEMONHUNTER
// [BT_407] Ur'zul Horror (*) - COST:1 [ATK:2/HP:1]
// - Race: Demon, Set: Demon Hunter Initiate, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Add a 2/1 Lost Soul to your hand.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - BT_407 : Ur'zul Horror")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
    config.player2Class = CardClass::MAGE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ur'zul Horror"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Lost Soul");
}

// ----------------------------------- MINION - DEMONHUNTER
// [BT_416] Raging Felscreamer (*) - COST:4 [ATK:4/HP:4]
// - Set: Demon Hunter Initiate, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> The next Demon you play costs (2) less.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - BT_416 : Raging Felscreamer")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
    config.player2Class = CardClass::MAGE;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Raging Felscreamer"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Satyr Overseer"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Shadowhoof Slayer"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Battlefiend"));
    const auto card5 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Glaivebound Adept"));

    CHECK_EQ(card2->GetCost(), 3);
    CHECK_EQ(card3->GetCost(), 1);
    CHECK_EQ(card4->GetCost(), 1);
    CHECK_EQ(card5->GetCost(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetRemainingMana(), 6);
    CHECK_EQ(card2->GetCost(), 1);
    CHECK_EQ(card3->GetCost(), 0);
    CHECK_EQ(card4->GetCost(), 0);
    CHECK_EQ(card5->GetCost(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curPlayer->GetRemainingMana(), 6);
    CHECK_EQ(card2->GetCost(), 3);
    CHECK_EQ(card4->GetCost(), 1);
    CHECK_EQ(card5->GetCost(), 5);
}

// ------------------------------------ SPELL - DEMONHUNTER
// [BT_427] Feast of Souls - COST:2
// - Set: Demon Hunter Initiate, Rarity: Rare
// --------------------------------------------------------
// Text: Draw a card for each friendly minion that died this turn.
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - BT_427 : Feast of Souls")
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

    auto& opField = *(opPlayer->GetFieldZone());
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Feast of Souls"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Coordinated Strike"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(opHand.GetCount(), 7);

    game.Process(opPlayer, AttackTask(opField[0], card1));
    game.Process(opPlayer, AttackTask(opField[0], card1));
    game.Process(opPlayer, AttackTask(opField[0], card1));

    game.Process(opPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(opHand.GetCount(), 9);
}

// ----------------------------------- MINION - DEMONHUNTER
// [BT_481] Nethrandamus (*) - COST:9 [ATK:8/HP:8]
// - Race: Dragon, Set: Demon Hunter Initiate, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon two random 0-Cost minions.
//       <i>(Upgrades each time a friendly minion dies!)</i>.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - BT_481 : Nethrandamus")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
    config.player2Class = CardClass::MAGE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Nethrandamus"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Command the Illidari"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Blizzard"));

    game.Process(curPlayer, PlayCardTask::Spell(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card3));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->GetCost(), 6);
    CHECK_EQ(curField[1]->card->name, "Nethrandamus");
    CHECK_EQ(curField[2]->GetCost(), 6);
}

// ----------------------------------- MINION - DEMONHUNTER
// [BT_487] Hulking Overfiend (*) - COST:8 [ATK:5/HP:10]
// - Race: Demon, Set: Demon Hunter Initiate, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Rush</b>. After this attacks and kills a minion,
//       it may attack again.
// --------------------------------------------------------
// GameTag:
// - RUSH = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - BT_487 : Hulking Overfiend")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Oasis Snapjaw"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Hulking Overfiend"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(card3->IsExhausted(), false);

    game.Process(opPlayer, AttackTask(card3, card1));
    CHECK_EQ(card3->IsExhausted(), false);

    game.Process(opPlayer, AttackTask(card3, card2));
    CHECK_EQ(card3->IsExhausted(), true);
}

// ------------------------------------ SPELL - DEMONHUNTER
// [BT_488] Soul Split (*) - COST:4
// - Set: Demon Hunter Initiate, Rarity: Rare
// --------------------------------------------------------
// Text: Choose a friendly Demon. Summon a copy of it.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_FRIENDLY_TARGET = 0
// - REQ_TARGET_WITH_RACE = 15
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - BT_488 : Soul Split")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::DEMONHUNTER;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Soul Split"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Oasis Snapjaw"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ur'zul Horror"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(curHand.GetCount(), 0);
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[2]->card->name, "Ur'zul Horror");
}

// ------------------------------------ SPELL - DEMONHUNTER
// [BT_490] Consume Magic - COST:1
// - Set: Demon Hunter Initiate, Rarity: Common
// --------------------------------------------------------
// Text: <b>Silence</b> an enemy minion.
//       <b>Outcast:</b> Draw a card.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_ENEMY_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - SILENCE = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - BT_490 : Consume Magic")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Leper Gnome"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Leper Gnome"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->HasDeathrattle(), true);
    CHECK_EQ(curField[1]->HasDeathrattle(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Consume Magic"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Consume Magic"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Dalaran Mage"));

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(opHand.GetCount(), 8);
    CHECK_EQ(opField[0]->GetSpellPower(), 1);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card2));
    CHECK_EQ(opHand.GetCount(), 7);
    CHECK_EQ(curField[1]->HasDeathrattle(), false);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card5));
    CHECK_EQ(opHand.GetCount(), 7);
    CHECK_EQ(opField[0]->GetSpellPower(), 1);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card1));
    CHECK_EQ(curField[0]->HasDeathrattle(), false);
    CHECK_EQ(opHand.GetCount(), 7);
}

// ----------------------------------- MINION - DEMONHUNTER
// [BT_510] Wrathspike Brute - COST:5 [ATK:2/HP:6]
// - Race: Demon, Set: Demon Hunter Initiate, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Taunt</b> After this is attacked,
//       deal 1 damage to all enemies.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - BT_510 : Wrathspike Brute")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
    config.player2Class = CardClass::MAGE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wrathspike Brute"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Oasis Snapjaw"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fiery War Axe"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, AttackTask(card2, card1));
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 6);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 29);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(opField.GetCount(), 2);
    CHECK_EQ(opField[0]->GetHealth(), 6);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 29);

    opPlayer->SetUsedMana(0);

    game.Process(opPlayer, PlayCardTask::Weapon(card5));
    game.Process(opPlayer, AttackTask(opPlayer->GetHero(), card1));
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 5);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 26);
}

// ------------------------------------ SPELL - DEMONHUNTER
// [BT_752] Blur - COST:0
// - Set: Demon Hunter Initiate, Rarity: Common
// --------------------------------------------------------
// Text: Your hero can't take damage this turn.
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - BT_752 : Blur")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Blur"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opPlayer->GetHero()->IsImmune(), true);

    game.Process(opPlayer, HeroPowerTask());
    game.Process(opPlayer, AttackTask(opPlayer->GetHero(), card1));
    CHECK_EQ(card1->isDestroyed, true);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opPlayer->GetHero()->IsImmune(), false);
}

// ------------------------------------ SPELL - DEMONHUNTER
// [BT_753] Mana Burn - COST:1
// - Set: Demon Hunter Initiate, Rarity: Common
// --------------------------------------------------------
// Text: Your opponent has 2 fewer Mana Crystals next turn.
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - BT_753 : Mana Burn")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
    config.player2Class = CardClass::MAGE;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mana Burn"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opPlayer->GetRemainingMana(), 8);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opPlayer->GetRemainingMana(), 10);
}

// ------------------------------------ SPELL - DEMONHUNTER
// [BT_801] Eye Beam - COST:3
// - Set: Demon Hunter Initiate, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Lifesteal</b>. Deal 3 damage to a minion.
//       <b>Outcast:</b> This costs (1).
// --------------------------------------------------------
// GameTag:
// - LIFESTEAL = 1
// - OUTCAST = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - BT_801 : Eye Beam")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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
    opPlayer->GetHero()->SetDamage(15);

    auto opHero = opPlayer->GetHero();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Eye Beam"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Eye Beam"));

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(opPlayer->GetRemainingMana(), 7);
    CHECK_EQ(opHero->GetHealth(), 18);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(opPlayer->GetRemainingMana(), 6);
    CHECK_EQ(opHero->GetHealth(), 21);
}

// ----------------------------------- MINION - DEMONHUNTER
// [BT_814] Illidari Felblade - COST:4 [ATK:5/HP:3]
// - Race: Demon, Set: Demon Hunter Initiate, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Rush</b> <b>Outcast:</b> Gain <b>Immune</b> this turn.
// --------------------------------------------------------
// GameTag:
// - OUTCAST = 1
// - RUSH = 1
// --------------------------------------------------------
// RefTag:
// - IMMUNE = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - BT_814 : Illidari Felblade")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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
    opPlayer->GetHero()->SetDamage(15);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Illidari Felblade"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Illidari Felblade"));

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, AttackTask(card2, card1));
    CHECK_EQ(curField[0]->GetHealth(), 7);
    CHECK_EQ(opField.GetCount(), 0);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, AttackTask(card3, card1));
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->IsImmune(), true);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opField[0]->IsImmune(), false);
}

// ----------------------------------- WEAPON - DEMONHUNTER
// [BT_922] Umberwing - COST:2 [ATK:1/HP:0]
// - Set: Demon Hunter Initiate, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon two 1/1 Felwings.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - DURABILITY = 2
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Weapon] - BT_922 : Umberwing")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
    config.player2Class = CardClass::PALADIN;
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
    opPlayer->GetHero()->SetDamage(15);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Umberwing"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Felwing");
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->card->name, "Felwing");
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
}

// ----------------------------------- MINION - DEMONHUNTER
// [BT_937] Altruis the Outcast - COST:4 [ATK:4/HP:2]
// - Set: Demon Hunter Initiate, Rarity: Legendary
// --------------------------------------------------------
// Text: After you play the left- or right-most card in your hand,
//       deal 1 damage to all enemies.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - BT_937 : Altruis the Outcast")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::DEMONHUNTER;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
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
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Altruis the Outcast"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    curPlayer->GetHero()->SetDamage(0);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(curField[0]->GetHealth(), 12);

    game.Process(opPlayer, PlayCardTask::Spell(opHand[0]));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 29);
    CHECK_EQ(curField[0]->GetHealth(), 11);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 29);
    CHECK_EQ(curField[0]->GetHealth(), 11);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 28);
    CHECK_EQ(curField[0]->GetHealth(), 10);

    game.Process(opPlayer, PlayCardTask::Minion(card6));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 27);
    CHECK_EQ(curField[0]->GetHealth(), 9);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 26);
    CHECK_EQ(curField[0]->GetHealth(), 8);
}