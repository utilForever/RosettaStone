// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.hpp>

#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>
#include <Rosetta/PlayMode/Zones/SecretZone.hpp>

using namespace RosettaStone;
using namespace PlayMode;
using namespace PlayerTasks;
using namespace SimpleTasks;

// ------------------------------------------ SPELL - DRUID
// [BT_130] Overgrowth - COST:4
// - Faction: Neutral, Set: Core, Rarity: Common
// --------------------------------------------------------
// Text: Gain two empty Mana Crystals.
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - BT_130 : Overgrowth")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(8);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Overgrowth"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Overgrowth"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetRemainingMana(), 4);
    CHECK_EQ(curPlayer->GetTotalMana(), 10);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curPlayer->GetRemainingMana(), 0);
    CHECK_EQ(curPlayer->GetTotalMana(), 10);
}

// ---------------------------------------- MINION - PRIEST
// [BT_258] Imprisoned Homunculus - COST:1 [ATK:2/HP:5]
// - Race: Demon, Set: Black Temple, Rarity: Common
// --------------------------------------------------------
// Text: <b>Dormant</b> for 2 turns.
//       <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - BT_258 : Imprisoned Homunculus")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Imprisoned Homunculus"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1), 2);
    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2), 0);
    CHECK_EQ(curField[0]->IsUntouchable(), true);
    CHECK_EQ(curField[0]->CanAttack(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2), 1);
    CHECK_EQ(curField[0]->IsUntouchable(), true);
    CHECK_EQ(curField[0]->CanAttack(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2), 2);
    CHECK_EQ(curField[0]->IsUntouchable(), false);
    CHECK_EQ(curField[0]->CanAttack(), false);
    CHECK_EQ(curField[0]->HasTaunt(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->CanAttack(), true);

    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);
}

// ----------------------------------------- MINION - WARRIOR
// [BT_123] Kargath Bladefist - COST:4 [ATK:4/HP:4]
// - Set: BLACK_TEMPLE, Rarity: LEGENDARY
// --------------------------------------------------------
// Text: <b>Rush</b>
//       <b>Deathrattle:</b> Shuffle
//       'Kargath Prime'
//       into your deck.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - RUSH = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - BT_123 : Kargath Bladefist")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;
    config.doShuffle = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curDeck = *(curPlayer->GetDeckZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Kargath Bladefist"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Reckless Rocketeer"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    // Player1 summon 'Kargath Bladefist'
    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    // Player2 summon minions and attack player1's 'Kargath Bladefist'
    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, AttackTask(card2, card1));

    // Player1's 'Kargath Prime' move to top of the deck
    auto curCards = curDeck.GetAll();
    auto iter = std::find_if(
        curCards.begin(), curCards.end(),
        [](const Playable* dc) { return (dc->card->name) == "Kargath Prime"; });
    CHECK(iter != curCards.end());
    const auto card5 = *iter;
    curDeck.Swap(card5, curDeck.GetTopCard());

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    // Player1 summon 'Kargath Prime' and 'Kargath Prime' kill a minion
    game.Process(curPlayer, PlayCardTask::Minion(card5));
    game.Process(curPlayer, AttackTask(card5, card3));

    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 10);
    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    // 'Kargath Prime' kill a minion
    game.Process(curPlayer, AttackTask(card5, card4));

    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 20);
    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    // 'Kargath Prime' kill a hero
    opPlayer->GetHero()->SetHealth(10);
    game.Process(curPlayer, AttackTask(card5, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 20);
}

// ----------------------------------------- SPELL - WARRIOR
// [BT_124] Corsair Cache - COST:2
// - Set: BLACK_TEMPLE, Rarity: Rare
// --------------------------------------------------------
// Text: Draw a weapon.
//       Give it +1 Durability.
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - BT_124 : Corsair Cache")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.doShuffle = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Fiery War Axe");
    }

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    HandZone& curHand = *(curPlayer->GetHandZone());

    const auto card = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Corsair Cache"));

    game.Process(curPlayer, PlayCardTask::Spell(card));
    CHECK_EQ(curPlayer->GetRemainingMana(), 8);
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(dynamic_cast<Weapon*>(curHand[3])->GetDurability(), 2);
    CHECK_EQ(dynamic_cast<Weapon*>(curHand[4])->GetDurability(), 3);
}