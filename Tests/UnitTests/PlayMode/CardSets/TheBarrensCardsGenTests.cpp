// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetHeaders.hpp>

// ------------------------------------------ SPELL - DRUID
// [BAR_533] Thorngrowth Sentries - COST:2
// - Set: THE_BARRENS, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: Summon two 1/2 Turtles with <b>Taunt</b>.
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - BAR_533 : Thorngrowth Sentries")
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
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Thorngrowth Sentries"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Thornguard Turtle");
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[1]->card->name, "Thornguard Turtle");
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(curField[1]->HasTaunt(), true);
}

// ------------------------------------------ SPELL - DRUID
// [BAR_534] Pride's Fury - COST:4
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: Give your minions +1/+3.
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - BAR_534 : Pride's Fury")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::PRIEST;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pride's Fury"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 4);
}

// ----------------------------------------- MINION - DRUID
// [BAR_535] Thickhide Kodo - COST:4 [ATK:3/HP:5]
// - Race: Beast, Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Deathrattle:</b> Gain 5 Armor.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - BAR_535 : Thickhide Kodo")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Thickhide Kodo"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 5);
}

// ------------------------------------------ SPELL - DRUID
// [BAR_536] Living Seed (Rank 1) - COST:2
// - Set: THE_BARRENS, Rarity: Rare
// - Spell School: Nature
// --------------------------------------------------------
// Text: Draw a Beast. Reduce its Cost by (1).
//       <i>(Upgrades when you have 5 Mana.)</i>
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - BAR_536 : Living Seed (Rank 1)")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Savannah Highmane");
        config.player1Deck[i + 1] = Cards::FindCardByName("Malygos");
        config.player1Deck[i + 2] = Cards::FindCardByName("Wisp");
    }

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(4);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(4);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Living Seed (Rank 1)"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Living Seed (Rank 1)"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Living Seed (Rank 1)"));

    CHECK_EQ(curHand.GetCount(), 7);
    CHECK_EQ(card1->card->name, "Living Seed (Rank 1)");
    CHECK_EQ(card2->card->name, "Living Seed (Rank 1)");
    CHECK_EQ(card3->card->name, "Living Seed (Rank 1)");

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 7);
    CHECK_EQ(curHand[6]->GetCost(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->card->name, "Living Seed (Rank 1)");
    CHECK_EQ(card3->card->name, "Living Seed (Rank 1)");

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 8);
    CHECK_EQ(card2->card->name, "Living Seed (Rank 2)");
    CHECK_EQ(card3->card->name, "Living Seed (Rank 2)");

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curHand.GetCount(), 8);
    CHECK_EQ(curHand[7]->GetCost(), 4);

    curPlayer->SetTotalMana(9);
    opPlayer->SetTotalMana(9);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card3->card->name, "Living Seed (Rank 2)");

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 9);
    CHECK_EQ(card3->card->name, "Living Seed (Rank 3)");

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curHand.GetCount(), 9);
    CHECK_EQ(curHand[8]->GetCost(), 3);
}

// ----------------------------------------- MINION - DRUID
// [BAR_537] Razormane Battleguard - COST:2 [ATK:2/HP:2]
// - Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: The first <b>Taunt</b> minion you play each turn
//       costs (2) less.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - BAR_537 : Razormane Battleguard")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
        curPlayer, Cards::FindCardByName("Razormane Battleguard"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Rock Rager"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Rock Rager"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("River Crocolisk"));

    CHECK_EQ(card2->GetCost(), 2);
    CHECK_EQ(card3->GetCost(), 2);
    CHECK_EQ(card4->GetCost(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetRemainingMana(), 8);
    CHECK_EQ(card2->GetCost(), 0);
    CHECK_EQ(card3->GetCost(), 0);
    CHECK_EQ(card4->GetCost(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetRemainingMana(), 8);
    CHECK_EQ(card3->GetCost(), 2);
    CHECK_EQ(card4->GetCost(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card3->GetCost(), 0);
    CHECK_EQ(card4->GetCost(), 2);
}

// ----------------------------------------- MINION - DRUID
// [BAR_538] Druid of the Plains - COST:7 [ATK:7/HP:6]
// - Race: Beast, Set: THE_BARRENS, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Rush</b>
//       <b>Frenzy:</b> Transform into a 6/7 Kodo with <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - FRENZY = 1
// - RUSH = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - BAR_538 : Druid of the Plains")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Druid of the Plains"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 7);
    CHECK_EQ(curField[0]->GetHealth(), 6);
    CHECK_EQ(curField[0]->HasRush(), true);
    CHECK_EQ(curField[0]->HasTaunt(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 7);
    CHECK_EQ(curField[0]->HasRush(), false);
    CHECK_EQ(curField[0]->HasTaunt(), true);
}

// ------------------------------------------ SPELL - DRUID
// [BAR_539] Celestial Alignment - COST:8
// - Set: THE_BARRENS, Rarity: Epic
// - Spell School: Arcane
// --------------------------------------------------------
// Text: Set your Mana Crystals to 0.
//       Set the cost of all cards in your hand and deck to (1).
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - BAR_539 : Celestial Alignment")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Fireball");
        config.player1Deck[i + 1] = Cards::FindCardByName("Wisp");
        config.player1Deck[i + 2] = Cards::FindCardByName("Doomhammer");
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

    auto& curHand = *(curPlayer->GetHandZone());
    auto& curDeck = *(curPlayer->GetDeckZone());
    auto& opHand = *(opPlayer->GetHandZone());
    auto& opDeck = *(opPlayer->GetDeckZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Celestial Alignment"));

    CHECK_EQ(curPlayer->GetTotalMana(), 10);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetTotalMana(), 0);
    for (auto& card : curHand.GetAll())
    {
        CHECK_EQ(card->GetCost(), 1);
    }
    for (auto& card : curDeck.GetAll())
    {
        CHECK_EQ(card->GetCost(), 1);
    }

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetTotalMana(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetTotalMana(), 1);
}

// ----------------------------------------- MINION - DRUID
// [BAR_540] Plaguemaw the Rotting - COST:4 [ATK:3/HP:4]
// - Set: THE_BARRENS, Rarity: Legendary
// --------------------------------------------------------
// Text: After a friendly minion with <b>Taunt</b> dies,
//       summon a new copy of it without <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - BAR_540 : Plaguemaw the Rotting")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::MAGE;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Plaguemaw the Rotting"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Rock Rager"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("River Crocolisk"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card3));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card5, card2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->name, "Rock Rager");
    CHECK_EQ(curField[1]->HasTaunt(), false);
}

// ------------------------------------------ SPELL - DRUID
// [BAR_549] Mark of the Spikeshell - COST:2
// - Set: THE_BARRENS, Rarity: Rare
// - Spell School: Nature
// --------------------------------------------------------
// Text: Give a minion +2/+2.
//       If it has <b>Taunt</b>, add a copy of it to your hand.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - BAR_549 : Mark of the Spikeshell")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::MAGE;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mark of the Spikeshell"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mark of the Spikeshell"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Rock Rager"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("River Crocolisk"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curHand.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card4));
    CHECK_EQ(curHand.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->name, "Rock Rager");
}

// ----------------------------------------- MINION - DRUID
// [BAR_720] Guff Runetotem - COST:3 [ATK:2/HP:4]
// - Set: THE_BARRENS, Rarity: Legendary
// --------------------------------------------------------
// Text: After you cast a Nature spell,
//       give another friendly minion +2/+2.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - BAR_720 : Guff Runetotem")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Guff Runetotem"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Innervate"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Holy Light"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 3);
}

// ----------------------------------------- MINION - DRUID
// [WC_004] Fangbound Druid - COST:3 [ATK:4/HP:3]
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Deathrattle:</b> Reduce the Cost of a Beast
//       in your hand by (2).
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - WC_004 : Fangbound Druid")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fangbound Druid"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Jungle Panther"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Murloc Tidehunter"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card2->GetCost(), 3);
    CHECK_EQ(card3->GetCost(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card1));
    CHECK_EQ(card2->GetCost(), 1);
    CHECK_EQ(card3->GetCost(), 2);
}

// ----------------------------------------- MINION - DRUID
// [WC_006] Lady Anacondra - COST:6 [ATK:3/HP:7]
// - Set: THE_BARRENS, Rarity: Legendary
// --------------------------------------------------------
// Text: Your Nature spells cost (2) less.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - WC_006 : Lady Anacondra")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lady Anacondra"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Force of Nature"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Holy Light"));

    CHECK_EQ(card2->GetCost(), 5);
    CHECK_EQ(card3->GetCost(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card2->GetCost(), 3);
    CHECK_EQ(card3->GetCost(), 2);
}

// ----------------------------------------- MINION - DRUID
// [WC_036] Deviate Dreadfang - COST:8 [ATK:4/HP:9]
// - Race: Beast, Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: After you cast a Nature spell,
//       summon a 4/2 Viper with <b>Rush</b>.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - WC_036 : Deviate Dreadfang")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Deviate Dreadfang"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Innervate"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Holy Light"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->name, "Deviate Viper");
    CHECK_EQ(curField[1]->GetAttack(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(curField[1]->HasRush(), true);
}

// ----------------------------------------- SPELL - HUNTER
// [BAR_032] Piercing Shot - COST:4
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: Deal 6 damage to a minion.
//       Excess damage hits the enemy hero.
// --------------------------------------------------------
// GameTag:
// - ImmuneToSpellpower = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - BAR_032 : Piercing Shot")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Piercing Shot"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Piercing Shot"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Kobold Geomancer"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card4));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 25);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card5));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card5));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 19);
}

// ---------------------------------------- MINION - HUNTER
// [BAR_033] Prospector's Caravan - COST:2 [ATK:1/HP:3]
// - Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: At the start of your turn,
//       give all minions in your hand +1/+1.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - BAR_033 : Prospector's Caravan")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Prospector's Caravan"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Prospector's Caravan"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(dynamic_cast<Minion*>(card3)->GetAttack(), 1);
    CHECK_EQ(dynamic_cast<Minion*>(card3)->GetHealth(), 1);
    CHECK_EQ(dynamic_cast<Minion*>(card4)->GetAttack(), 4);
    CHECK_EQ(dynamic_cast<Minion*>(card4)->GetHealth(), 12);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(dynamic_cast<Minion*>(card3)->GetAttack(), 3);
    CHECK_EQ(dynamic_cast<Minion*>(card3)->GetHealth(), 3);
    CHECK_EQ(dynamic_cast<Minion*>(card4)->GetAttack(), 6);
    CHECK_EQ(dynamic_cast<Minion*>(card4)->GetHealth(), 14);
}

// ----------------------------------------- SPELL - HUNTER
// [BAR_034] Tame Beast (Rank 1) - COST:2
// - Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: Summon a 2/2 Beast with <b>Rush</b>.
//       <i>(Upgrades when you have 5 Mana.)</i>
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - BAR_034 : Tame Beast (Rank 1)")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(4);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(4);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Tame Beast (Rank 1)"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Tame Beast (Rank 1)"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Tame Beast (Rank 1)"));

    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(card1->card->name, "Tame Beast (Rank 1)");
    CHECK_EQ(card2->card->name, "Tame Beast (Rank 1)");
    CHECK_EQ(card3->card->name, "Tame Beast (Rank 1)");

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Tamed Crab");
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[0]->HasRush(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->card->name, "Tame Beast (Rank 1)");
    CHECK_EQ(card3->card->name, "Tame Beast (Rank 1)");

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->card->name, "Tame Beast (Rank 2)");
    CHECK_EQ(card3->card->name, "Tame Beast (Rank 2)");

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->name, "Tamed Scorpid");
    CHECK_EQ(curField[1]->GetAttack(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 4);
    CHECK_EQ(curField[1]->HasRush(), true);

    curPlayer->SetTotalMana(9);
    opPlayer->SetTotalMana(9);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card3->card->name, "Tame Beast (Rank 2)");

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card3->card->name, "Tame Beast (Rank 3)");

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[2]->card->name, "Tamed Thunder Lizard");
    CHECK_EQ(curField[2]->GetAttack(), 6);
    CHECK_EQ(curField[2]->GetHealth(), 6);
    CHECK_EQ(curField[2]->HasRush(), true);
}

// ---------------------------------------- MINION - HUNTER
// [BAR_035] Kolkar Pack Runner - COST:3 [ATK:3/HP:4]
// - Set: THE_BARRENS, Rarity: Epic
// --------------------------------------------------------
// Text: After you cast a spell,
//       summon a 1/1 Hyena with <b>Rush</b>.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - BAR_035 : Kolkar Pack Runner")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Kolkar Pack Runner"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Holy Light"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[1]->card->name, "Swift Hyena");
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[1]->HasRush(), true);
}

// ----------------------------------------- SPELL - HUNTER
// [BAR_801] Wound Prey - COST:1
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: Deal 1 damage. Summon a 1/1 Hyena with <b>Rush</b>.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - BAR_801 : Wound Prey")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wound Prey"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 6);
    CHECK_EQ(curField[1]->card->name, "Swift Hyena");
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[1]->HasRush(), true);
}

// ----------------------------------------- SPELL - HUNTER
// [WC_007] Serpentbloom - COST:0
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: Give a friendly Beast <b>Poisonous</b>.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_TARGET_WITH_RACE = 20
// - REQ_MINION_TARGET = 0
// - REQ_FRIENDLY_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - POISONOUS = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - WC_007 : Serpentbloom")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Serpentbloom"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Enchanted Raven"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->HasPoisonous(), false);
    CHECK_EQ(curField[1]->HasPoisonous(), false);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField[0]->HasPoisonous(), false);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(curField[1]->HasPoisonous(), true);
}

// ---------------------------------------- MINION - HUNTER
// [WC_008] Sin'dorei Scentfinder - COST:4 [ATK:1/HP:6]
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Frenzy:</b> Summon four 1/1 Hyenas with <b>Rush</b>.
// --------------------------------------------------------
// GameTag:
// - FRENZY = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - WC_008 : Sin'dorei Scentfinder")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Sin'dorei Scentfinder"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField.GetCount(), 5);
    CHECK_EQ(curField[1]->card->name, "Swift Hyena");
    CHECK_EQ(curField[2]->card->name, "Swift Hyena");
    CHECK_EQ(curField[3]->card->name, "Swift Hyena");
    CHECK_EQ(curField[4]->card->name, "Swift Hyena");
}

// ---------------------------------------- WEAPON - HUNTER
// [WC_037] Venomstrike Bow - COST:4
// - Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Poisonous</b>
// --------------------------------------------------------
// GameTag:
// - POISONOUS = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Weapon] - WC_037 : Venomstrike Bow")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Venomstrike Bow"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), true);
    CHECK_EQ(curPlayer->GetHero()->weapon->HasPoisonous(), true);

    game.Process(curPlayer, AttackTask(curPlayer->GetHero(), card2));
    CHECK_EQ(opField.GetCount(), 0);
}

// ------------------------------------------- SPELL - MAGE
// [BAR_305] Flurry (Rank 1) - COST:0
// - Set: THE_BARRENS, Rarity: Rare
// - Spell School: Frost
// --------------------------------------------------------
// Text: <b>Freeze</b> a random enemy minion.
//       <i>(Upgrades when you have 5 Mana.)</i>
// --------------------------------------------------------
// PlayReq:
// - REQ_MINIMUM_ENEMY_MINIONS = 1
// --------------------------------------------------------
// RefTag:
// - FREEZE = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - BAR_305 : Flurry (Rank 1)")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(3);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(3);
    opPlayer->SetUsedMana(0);

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flurry (Rank 1)"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flurry (Rank 1)"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flurry (Rank 1)"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    auto NumFrozenMinions = [&](FieldZone& field) -> int {
        int count = 0;

        for (const auto& minion : field.GetAll())
        {
            if (minion->IsFrozen())
            {
                ++count;
            }
        }

        return count;
    };

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, PlayCardTask::Minion(card6));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card1->card->name, "Flurry (Rank 1)");
    CHECK_EQ(card2->card->name, "Flurry (Rank 1)");
    CHECK_EQ(card3->card->name, "Flurry (Rank 1)");

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(NumFrozenMinions(opField), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->card->name, "Flurry (Rank 1)");
    CHECK_EQ(card3->card->name, "Flurry (Rank 1)");

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->card->name, "Flurry (Rank 2)");
    CHECK_EQ(card3->card->name, "Flurry (Rank 2)");

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(NumFrozenMinions(opField), 2);

    curPlayer->SetTotalMana(9);
    opPlayer->SetTotalMana(9);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card3->card->name, "Flurry (Rank 2)");

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card3->card->name, "Flurry (Rank 3)");

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(NumFrozenMinions(opField), 3);
}

// ------------------------------------------- SPELL - MAGE
// [BAR_541] Runed Orb - COST:2
// - Set: THE_BARRENS, Rarity: Common
// - Spell School: Arcane
// --------------------------------------------------------
// Text: Deal 2 damage. <b>Discover</b> a spell.
// --------------------------------------------------------
// GameTag:
// - DISCOVER = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - BAR_541 : Runed Orb")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Runed Orb"));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK(curPlayer->choice);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::SPELL);
        CHECK(card->IsCardClass(CardClass::MAGE));
    }
}

// ------------------------------------------ MINION - MAGE
// [BAR_748] Varden Dawngrasp - COST:4 [ATK:3/HP:3]
// - Set: THE_BARRENS, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> <b>Freeze</b> all enemy minions.
//       If any are already <b>Frozen</b>, deal 4 damage
//       to them instead.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - FREEZE = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - BAR_748 : Varden Dawngrasp")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Varden Dawngrasp"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3));
    CHECK_EQ(opField[0]->IsFrozen(), true);
    CHECK_EQ(opField[0]->GetHealth(), 9);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opField[0]->GetHealth(), 5);
    CHECK_EQ(opField[1]->IsFrozen(), true);
}

// ------------------------------------------- SPELL - MAGE
// [BAR_812] Oasis Ally - COST:3
// - Set: THE_BARRENS, Rarity: Common
// - Spell School: Frost
// --------------------------------------------------------
// Text: <b>Secret:</b> When a friendly minion is attacked,
//       summon a 3/6 Water Elemental.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - BAR_812 : Oasis Ally")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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
    auto curSecret = curPlayer->GetSecretZone();
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Oasis Ally"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, AttackTask(card3, card2));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Water Elemental");
    CHECK_EQ(opField.GetCount(), 0);
}

// ------------------------------------------ MINION - MAGE
// [BAR_888] Rimetongue - COST:3 [ATK:3/HP:4]
// - Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: After you cast a Frost spell,
//       summon a 1/1 Elemental that <b><b>Freeze</b>s</b>.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
// RefTag:
// - FREEZE = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - BAR_888 : Rimetongue")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::WARRIOR;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Rimetongue"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Bumper Car"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->name, "Frosted Elemental");

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, AttackTask(card4, curField[1]));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->IsFrozen(), true);
}

// ------------------------------------------- SPELL - MAGE
// [WC_041] Shattering Blast - COST:3
// - Set: THE_BARRENS, Rarity: Rare
// - Spell School: Frost
// --------------------------------------------------------
// Text: Destroy all <b>Frozen</b> minions.
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - WC_041 : Shattering Blast")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shattering Blast"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frost Nova"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(opField[0]->IsFrozen(), true);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(opField.GetCount(), 0);
}

// ------------------------------------------ MINION - MAGE
// [WC_805] Frostweave Dungeoneer - COST:3 [ATK:2/HP:3]
// - Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Draw a spell.
//       If it's a Frost spell,
//       summon two 1/1 Elementals that <b>Freeze</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - FREEZE = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - WC_805 : Frostweave Dungeoneer")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Ice Barrier");
        config.player1Deck[i + 1] = Cards::FindCardByName("Malygos");
        config.player1Deck[i + 2] = Cards::FindCardByName("Wisp");
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Frostweave Dungeoneer"));

    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Ice Barrier");
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->card->name, "Frosted Elemental");
    CHECK_EQ(curField[1]->card->name, "Frostweave Dungeoneer");
    CHECK_EQ(curField[2]->card->name, "Frosted Elemental");
}

// ------------------------------------------ MINION - MAGE
// [WC_806] Floecaster - COST:6 [ATK:5/HP:5]
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: Costs (2) less for each <b>Frozen</b> enemy.
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - WC_806 : Floecaster")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::WARRIOR;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Floecaster"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flurry (Rank 1)"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flurry (Rank 1)"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    CHECK_EQ(card1->GetCost(), 6);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card1->GetCost(), 6);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(card1->GetCost(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card6));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card1->GetCost(), 6);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(card1->GetCost(), 0);
}

// ---------------------------------------- SPELL - PALADIN
// [BAR_550] Galloping Savior - COST:1
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Secret:</b> After your opponent plays three
//       cards in a turn, summon a 3/4 Steed with <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - BAR_550 : Galloping Savior")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::HUNTER;
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
    auto curSecret = curPlayer->GetSecretZone();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Galloping Savior"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card7 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card8 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card9 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card10 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curSecret->GetCount(), 1);
    CHECK_EQ(curField.GetCount(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card6));
    game.Process(opPlayer, PlayCardTask::Minion(card7));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card8));
    game.Process(opPlayer, PlayCardTask::Minion(card9));
    game.Process(opPlayer, PlayCardTask::Minion(card10));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[3]->card->name, "Holy Steed");
    CHECK_EQ(curField[3]->GetAttack(), 3);
    CHECK_EQ(curField[3]->GetHealth(), 4);
    CHECK_EQ(curField[3]->HasTaunt(), true);
}

// --------------------------------------- MINION - PALADIN
// [BAR_871] Soldier's Caravan - COST:2 [ATK:1/HP:3]
// - Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: At the start of your turn,
//       summon two 1/1 Silver Hand Recruits.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - BAR_871 : Soldier's Caravan")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::HUNTER;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Soldier's Caravan"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->card->name, "Silver Hand Recruit");
    CHECK_EQ(curField[1]->card->name, "Soldier's Caravan");
    CHECK_EQ(curField[2]->card->name, "Silver Hand Recruit");
}

// --------------------------------------- MINION - PALADIN
// [BAR_873] Knight of Anointment - COST:1 [ATK:1/HP:1]
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Draw a Holy spell.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - BAR_873 : Knight of Anointment")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Ice Barrier");
        config.player1Deck[i + 1] = Cards::FindCardByName("Holy Light");
        config.player1Deck[i + 2] = Cards::FindCardByName("Wisp");
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Knight of Anointment"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Holy Light");
}

// --------------------------------------- WEAPON - PALADIN
// [BAR_875] Sword of the Fallen - COST:2
// - Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: After your hero attacks,
//       cast a <b>Secret</b> from your deck.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Weapon] - BAR_875 : Sword of the Fallen")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 7; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Noble Sacrifice");
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

    auto& curDeck = *(curPlayer->GetDeckZone());
    auto& curSecret = *(curPlayer->GetSecretZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Sword of the Fallen"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Stonetusk Boar"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curDeck.GetCount(), 3);

    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(curDeck.GetCount(), 2);
    CHECK_EQ(curSecret.GetCount(), 1);
    CHECK_EQ(curSecret[0]->card->name, "Noble Sacrifice");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curDeck.GetCount(), 1);

    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(curDeck.GetCount(), 1);
    CHECK_EQ(curSecret.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, AttackTask(card2, curPlayer->GetHero()));
    CHECK_EQ(curSecret.GetCount(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curDeck.GetCount(), 0);

    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(curSecret.GetCount(), 0);
}

// --------------------------------------- MINION - PALADIN
// [BAR_876] Northwatch Commander - COST:3 [ATK:3/HP:4]
// - Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you control a <b>Secret</b>,
//       draw a minion.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - BAR_876 : Northwatch Commander")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Ice Barrier");
        config.player1Deck[i + 1] = Cards::FindCardByName("Holy Light");
        config.player1Deck[i + 2] = Cards::FindCardByName("Wisp");
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Northwatch Commander"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Northwatch Commander"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Noble Sacrifice"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 6);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Wisp");
}

// --------------------------------------- MINION - PALADIN
// [BAR_878] Veteran Warmedic - COST:4 [ATK:3/HP:5]
// - Set: THE_BARRENS, Rarity: Epic
// --------------------------------------------------------
// Text: After you cast a Holy spell,
//       summon a 2/2 Medic with <b>Lifesteal</b>.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
// RefTag:
// - LIFESTEAL = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - BAR_878 : Veteran Warmedic")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Veteran Warmedic"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Holy Light"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ice Barrier"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->name, "Battlefield Medic");
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(curField[1]->HasLifesteal(), true);
}

// ---------------------------------------- SPELL - PALADIN
// [BAR_880] Conviction (Rank 1) - COST:2
// - Set: THE_BARRENS, Rarity: Epic
// - Spell School: Holy
// --------------------------------------------------------
// Text: Give a random friendly minion +3 Attack.
//       <i>(Upgrades when you have 5 Mana.)</i>
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - BAR_880 : Conviction (Rank 1)")
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

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(4);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(4);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Conviction (Rank 1)"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Conviction (Rank 1)"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Conviction (Rank 1)"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    CHECK_EQ(card1->card->name, "Conviction (Rank 1)");
    CHECK_EQ(card2->card->name, "Conviction (Rank 1)");
    CHECK_EQ(card3->card->name, "Conviction (Rank 1)");

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::Minion(card5));
    game.Process(curPlayer, PlayCardTask::Minion(card6));
    CHECK_EQ(curField.GetCount(), 3);
    int totalAttack = curField[0]->GetAttack() + curField[1]->GetAttack() +
                      curField[2]->GetAttack();
    CHECK_EQ(totalAttack, 3);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    totalAttack = curField[0]->GetAttack() + curField[1]->GetAttack() +
                  curField[2]->GetAttack();
    CHECK_EQ(totalAttack, 6);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->card->name, "Conviction (Rank 1)");
    CHECK_EQ(card3->card->name, "Conviction (Rank 1)");

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->card->name, "Conviction (Rank 2)");
    CHECK_EQ(card3->card->name, "Conviction (Rank 2)");

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    totalAttack = curField[0]->GetAttack() + curField[1]->GetAttack() +
                  curField[2]->GetAttack();
    CHECK_EQ(totalAttack, 12);

    curPlayer->SetTotalMana(9);
    opPlayer->SetTotalMana(9);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card3->card->name, "Conviction (Rank 2)");

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card3->card->name, "Conviction (Rank 3)");

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    totalAttack = curField[0]->GetAttack() + curField[1]->GetAttack() +
                  curField[2]->GetAttack();
    CHECK_EQ(totalAttack, 21);
}

// ---------------------------------------- SPELL - PALADIN
// [BAR_881] Invigorating Sermon - COST:4
// - Set: THE_BARRENS, Rarity: Common
// - Spell School: Holy
// --------------------------------------------------------
// Text: Give +1/+1 to all minions in your hand, deck,
//       and battlefield.
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - BAR_881 : Invigorating Sermon")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 2)
    {
        config.player1Deck[i] = Cards::FindCardByName("Malygos");
        config.player1Deck[i + 1] = Cards::FindCardByName("Wisp");
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

    auto& curDeck = *(curPlayer->GetDeckZone());
    auto& curField = *(curPlayer->GetFieldZone());
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Invigorating Sermon"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    for (auto& card : curHand.GetAll())
    {
        if (auto minion = dynamic_cast<Minion*>(card); minion)
        {
            if (minion->card->name == "Malygos")
            {
                CHECK_EQ(minion->GetAttack(), 4);
                CHECK_EQ(minion->GetHealth(), 12);
            }
            else if (minion->card->name == "Wisp")
            {
                CHECK_EQ(minion->GetAttack(), 1);
                CHECK_EQ(minion->GetHealth(), 1);
            }
        }
    }
    for (auto& card : curDeck.GetAll())
    {
        if (auto minion = dynamic_cast<Minion*>(card); minion)
        {
            if (minion->card->name == "Malygos")
            {
                CHECK_EQ(minion->GetAttack(), 4);
                CHECK_EQ(minion->GetHealth(), 12);
            }
            else if (minion->card->name == "Wisp")
            {
                CHECK_EQ(minion->GetAttack(), 1);
                CHECK_EQ(minion->GetHealth(), 1);
            }
        }
    }
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    for (auto& card : curHand.GetAll())
    {
        if (auto minion = dynamic_cast<Minion*>(card); minion)
        {
            if (minion->card->name == "Malygos")
            {
                CHECK_EQ(minion->GetAttack(), 5);
                CHECK_EQ(minion->GetHealth(), 13);
            }
            else if (minion->card->name == "Wisp")
            {
                CHECK_EQ(minion->GetAttack(), 2);
                CHECK_EQ(minion->GetHealth(), 2);
            }
        }
    }
    for (auto& card : curDeck.GetAll())
    {
        if (auto minion = dynamic_cast<Minion*>(card); minion)
        {
            if (minion->card->name == "Malygos")
            {
                CHECK_EQ(minion->GetAttack(), 5);
                CHECK_EQ(minion->GetHealth(), 13);
            }
            else if (minion->card->name == "Wisp")
            {
                CHECK_EQ(minion->GetAttack(), 2);
                CHECK_EQ(minion->GetHealth(), 2);
            }
        }
    }
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 2);
}

// --------------------------------------- MINION - PALADIN
// [BAR_902] Cariel Roame - COST:4 [ATK:4/HP:3]
// - Set: THE_BARRENS, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Rush</b>, <b>Divine Shield</b>
//       Whenever this attacks, reduce the Cost of Holy spells
//       in your hand by (1).
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - DIVINE_SHIELD = 1
// - RUSH = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - BAR_902 : Cariel Roame")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cariel Roame"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Holy Light"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Equality"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Humility"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    CHECK_EQ(card2->GetCost(), 2);
    CHECK_EQ(card3->GetCost(), 2);
    CHECK_EQ(card4->GetCost(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, AttackTask(card1, card5));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(opField.GetCount(), 0);
    CHECK_EQ(card2->GetCost(), 1);
    CHECK_EQ(card3->GetCost(), 1);
    CHECK_EQ(card4->GetCost(), 1);
}

// --------------------------------------- WEAPON - PALADIN
// [WC_032] Seedcloud Buckler - COST:3
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Give your minions
//       <b>Divine Shield</b>.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
// RefTag:
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Weapon] - WC_032 : Seedcloud Buckler")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::WARRIOR;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Seedcloud Buckler"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Seedcloud Buckler"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->HasDivineShield(), false);
    CHECK_EQ(curField[1]->HasDivineShield(), false);

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curField[0]->HasDivineShield(), false);
    CHECK_EQ(curField[1]->HasDivineShield(), false);

    game.Process(curPlayer, PlayCardTask::Weapon(card2));
    CHECK_EQ(curField[0]->HasDivineShield(), true);
    CHECK_EQ(curField[1]->HasDivineShield(), true);
}

// ---------------------------------------- SPELL - PALADIN
// [WC_033] Judgment of Justice - COST:1
// - Set: THE_BARRENS, Rarity: Common
// - Spell School: Holy
// --------------------------------------------------------
// Text: <b>Secret:</b> When an enemy minion attacks,
//       set its Attack and Health to 1.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - WC_033 : Judgment of Justice")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
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

    auto curSecret = curPlayer->GetSecretZone();
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Judgment of Justice"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetAttack(), 3);
    CHECK_EQ(opField[0]->GetHealth(), 1);

    game.Process(opPlayer, AttackTask(card2, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 29);
    CHECK_EQ(opField[0]->GetAttack(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 1);
}

// ---------------------------------------- SPELL - PALADIN
// [WC_034] Party Up! - COST:7
// - Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: Summon five 2/2 Adventurers with random bonus effects.
// --------------------------------------------------------
// Entourage: WC_034t,  WC_034t2, WC_034t3, WC_034t4
//            WC_034t5, WC_034t6, WC_034t7, WC_034t8
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - WC_034 : Party Up!")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Party Up!"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 5);
    CHECK_EQ(curField[0]->card->IsAdventurer(), true);
    CHECK_EQ(curField[1]->card->IsAdventurer(), true);
    CHECK_EQ(curField[2]->card->IsAdventurer(), true);
    CHECK_EQ(curField[3]->card->IsAdventurer(), true);
    CHECK_EQ(curField[4]->card->IsAdventurer(), true);
}

// ---------------------------------------- MINION - PRIEST
// [BAR_307] Void Flayer - COST:4 [ATK:3/HP:4]
// - Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> For each spell in your hand,
//       deal 1 damage to a random enemy minion.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - BAR_307 : Void Flayer")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Void Flayer"));
    [[maybe_unused]] const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    [[maybe_unused]] const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Holy Smite"));
    [[maybe_unused]] const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Holy Nova"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 12);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(curField[0]->GetHealth(), 9);
}

// ----------------------------------------- SPELL - PRIEST
// [BAR_308] Power Word: Fortitude - COST:8
// - Set: THE_BARRENS, Rarity: Common
// - Spell School: Holy
// --------------------------------------------------------
// Text: Give a minion +3/+5.
//       Costs (1) less for each spell in your hand.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - BAR_308 : Power Word: Fortitude")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Power Word: Fortitude"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    [[maybe_unused]] const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Holy Smite"));
    [[maybe_unused]] const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Holy Nova"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(card1->GetCost(), 6);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 6);
}

// ----------------------------------------- SPELL - PRIEST
// [BAR_309] Desperate Prayer - COST:0
// - Set: THE_BARRENS, Rarity: Common
// - Spell School: Holy
// --------------------------------------------------------
// Text: Restore 5 Health to each hero.
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - BAR_309 : Desperate Prayer")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Desperate Prayer"));

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 20);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 25);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 25);
}

// ---------------------------------------- MINION - PRIEST
// [BAR_310] Lightshower Elemental - COST:6 [ATK:6/HP:6]
// - Race: Elemental, Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Deathrattle:</b> Restore 8 Health
//       to all friendly characters.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - BAR_310 : Lightshower Elemental")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Lightshower Elemental"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetHealth(), 12);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card2));
    CHECK_EQ(curField[0]->GetHealth(), 6);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 15);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 15);
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 23);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 15);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 12);
}

// ----------------------------------------- SPELL - PRIEST
// [BAR_311] Devouring Plague - COST:3
// - Set: THE_BARRENS, Rarity: Common
// - Spell School: Shadow
// --------------------------------------------------------
// Text: <b>Lifesteal</b>
//       Deal 4 damage randomly split among all enemy minions.
// --------------------------------------------------------
// GameTag:
// - LIFESTEAL = 1
// - ImmuneToSpellpower = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - BAR_311 : Devouring Plague")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::PALADIN;
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Devouring Plague"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField[0]->GetHealth(), 7);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 15);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(opField[0]->GetHealth(), 3);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 19);
}

// ---------------------------------------- MINION - PRIEST
// [BAR_313] Priest of An'she - COST:5 [ATK:5/HP:5]
// - Set: THE_BARRENS, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Taunt</b>. <b>Battlecry:</b> If you've restored
//       Health this turn, gain +3/+3.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - BAR_313 : Priest of An'she")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::PALADIN;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Priest of An'she"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Priest of An'she"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Desperate Prayer"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 8);
    CHECK_EQ(curField[1]->GetHealth(), 8);
}

// ----------------------------------------- SPELL - PRIEST
// [BAR_314] Condemn (Rank 1) - COST:2
// - Set: THE_BARRENS, Rarity: Epic
// - Spell School: Holy
// --------------------------------------------------------
// Text: Deal 1 damage to all enemy minions.
//       <i>(Upgrades when you have 5 Mana.)</i>
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - BAR_314 : Condemn (Rank 1)")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(3);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(9);
    opPlayer->SetUsedMana(0);

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Condemn (Rank 1)"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Condemn (Rank 1)"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Condemn (Rank 1)"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card1->card->name, "Condemn (Rank 1)");
    CHECK_EQ(card2->card->name, "Condemn (Rank 1)");
    CHECK_EQ(card3->card->name, "Condemn (Rank 1)");

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(opField[0]->GetHealth(), 11);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->card->name, "Condemn (Rank 1)");
    CHECK_EQ(card3->card->name, "Condemn (Rank 1)");

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->card->name, "Condemn (Rank 2)");
    CHECK_EQ(card3->card->name, "Condemn (Rank 2)");

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(opField[0]->GetHealth(), 9);

    curPlayer->SetTotalMana(9);
    opPlayer->SetTotalMana(9);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card3->card->name, "Condemn (Rank 2)");

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card3->card->name, "Condemn (Rank 3)");

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(opField[0]->GetHealth(), 6);
}

// ---------------------------------------- MINION - PRIEST
// [BAR_735] Xyrella - COST:4 [ATK:4/HP:4]
// - Set: THE_BARRENS, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you've restored Health this turn,
//       deal that much damage to all enemy minions.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - BAR_735 : Xyrella")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Xyrella"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Desperate Prayer"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField.GetCount(), 2);
    CHECK_EQ(opField[0]->GetHealth(), 12);
    CHECK_EQ(opField[1]->GetHealth(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 7);
}

// ---------------------------------------- MINION - PRIEST
// [WC_013] Devout Dungeoneer - COST:3 [ATK:2/HP:3]
// - Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Draw a spell.
//       If it's a Holy spell, reduce its Cost by (2).
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - WC_013 : Devout Dungeoneer")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Malygos");
        config.player1Deck[i + 1] = Cards::FindCardByName("Consecration");
        config.player1Deck[i + 2] = Cards::FindCardByName("Wisp");
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Devout Dungeoneer"));

    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Consecration");
    CHECK_EQ(curHand[4]->GetCost(), 2);
}

// ----------------------------------------- SPELL - PRIEST
// [WC_014] Against All Odds - COST:5
// - Set: THE_BARRENS, Rarity: Epic
// - Spell School: Holy
// --------------------------------------------------------
// Text: Destroy all odd-Attack minions.
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - WC_014 : Against All Odds")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Against All Odds"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Malygos");
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->card->name, "Malygos");
}

// ---------------------------------------- MINION - PRIEST
// [WC_803] Cleric of An'she - COST:1 [ATK:1/HP:2]
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you've restored Health this turn,
//       <b>Discover</b> a spell from your deck.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - WC_803 : Cleric of An'she")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Ice Barrier");
        config.player1Deck[i + 1] = Cards::FindCardByName("Holy Light");
        config.player1Deck[i + 2] = Cards::FindCardByName("Wisp");
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cleric of An'she"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cleric of An'she"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Desperate Prayer"));

    curPlayer->GetHero()->SetDamage(10);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(!curPlayer->choice);

    CHECK_EQ(curPlayer->GetDeckZone()->GetCount(), 26);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 2u);

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(curPlayer->GetDeckZone()->GetCount(), 25);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
}

// ----------------------------------------- MINION - ROGUE
// [BAR_317] Field Contact - COST:3 [ATK:3/HP:2]
// - Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: After you play a <b>Battlecry</b>
//       or <b>Combo</b> card, draw a card.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
// RefTag:
// - BATTLECRY = 1
// - COMBO = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - BAR_317 : Field Contact")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::ROGUE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Field Contact"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bladed Cultist"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Murloc Tidehunter"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 7);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHand.GetCount(), 7);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curHand.GetCount(), 7);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curHand.GetCount(), 6);
}

// ------------------------------------------ SPELL - ROGUE
// [BAR_318] Silverleaf Poison - COST:1
// - Set: THE_BARRENS, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: Give your weapon "After your hero attacks, draw a card."
// --------------------------------------------------------
// PlayReq:
// - REQ_WEAPON_EQUIPPED = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - BAR_318 : Silverleaf Poison")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::ROGUE;
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

    const auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Silverleaf Poison"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, HeroPowerTask());
    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 4);

    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(curHand.GetCount(), 5);
}

// ------------------------------------------ SPELL - ROGUE
// [BAR_319] Wicked Stab (Rank 1) - COST:2
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: Deal 2 damage. <i>(Upgrades when you have 5 Mana.)</i>
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - BAR_319 : Wicked Stab (Rank 1)")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::HUNTER;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(4);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(4);
    opPlayer->SetUsedMana(0);

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wicked Stab (Rank 1)"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wicked Stab (Rank 1)"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wicked Stab (Rank 1)"));

    CHECK_EQ(card1->card->name, "Wicked Stab (Rank 1)");
    CHECK_EQ(card2->card->name, "Wicked Stab (Rank 1)");
    CHECK_EQ(card3->card->name, "Wicked Stab (Rank 1)");

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->card->name, "Wicked Stab (Rank 1)");
    CHECK_EQ(card3->card->name, "Wicked Stab (Rank 1)");

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->card->name, "Wicked Stab (Rank 2)");
    CHECK_EQ(card3->card->name, "Wicked Stab (Rank 2)");

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 24);

    curPlayer->SetTotalMana(9);
    opPlayer->SetTotalMana(9);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card3->card->name, "Wicked Stab (Rank 2)");

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card3->card->name, "Wicked Stab (Rank 3)");

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 18);
}

// ----------------------------------------- MINION - ROGUE
// [BAR_320] Efficient Octo-bot - COST:3 [ATK:1/HP:4]
// - Race: Mechanical, Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Frenzy:</b> Reduce the cost of cards in your hand by (1).
// --------------------------------------------------------
// GameTag:
// - FRENZY = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - BAR_320 : Efficient Octo-bot")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
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
        curPlayer, Cards::FindCardByName("Efficient Octo-bot"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Murloc Tidehunter"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card2->GetCost(), 9);
    CHECK_EQ(card3->GetCost(), 2);
    CHECK_EQ(card4->GetCost(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(card2->GetCost(), 8);
    CHECK_EQ(card3->GetCost(), 1);
    CHECK_EQ(card4->GetCost(), 3);
}

// ------------------------------------------ SPELL - ROGUE
// [BAR_321] Paralytic Poison - COST:1
// - Set: THE_BARRENS, Rarity: Rare
// - Spell School: Nature
// --------------------------------------------------------
// Text: Give your weapon +1 Attack and "Your hero is
//       <b>Immune</b> while attacking."
// --------------------------------------------------------
// PlayReq:
// - REQ_WEAPON_EQUIPPED = 0
// --------------------------------------------------------
// RefTag:
// - IMMUNE = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - BAR_321 : Paralytic Poison")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::ROGUE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Paralytic Poison"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 2);

    game.Process(curPlayer, AttackTask(curPlayer->GetHero(), card2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(opField[0]->GetHealth(), 10);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, AttackTask(card2, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 26);
}

// ----------------------------------------- WEAPON - ROGUE
// [BAR_322] Swinetusk Shank - COST:3
// - Set: THE_BARRENS, Rarity: Epic
// --------------------------------------------------------
// Text: After you play a Poison, gain +1 Durability.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Weapon] - BAR_322 : Swinetusk Shank")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::ROGUE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Swinetusk Shank"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Paralytic Poison"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Deadly Poison"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 2);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 2);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 3);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 3);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 5);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 4);
}

// ----------------------------------------- MINION - ROGUE
// [BAR_324] Apothecary Helbrim - COST:4 [ATK:3/HP:2]
// - Set: THE_BARRENS, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry and Deathrattle:</b>
//       Add a random Poison to your hand.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - BAR_324 : Apothecary Helbrim")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::MAGE;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Apothecary Helbrim"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->IsPoison(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curHand.GetCount(), 2);
    CHECK_EQ(curHand[1]->card->IsPoison(), true);
}

// ---------------------------------------- MINION - SHAMAN
// [BAR_040] South Coast Chieftain - COST:2 [ATK:3/HP:2]
// - Race: Murloc, Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you control another Murloc,
//       deal 2 damage.
// --------------------------------------------------------
// RefTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - BAR_040 : South Coast Chieftain")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::SHAMAN;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("South Coast Chieftain"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("South Coast Chieftain"));

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(curHand.GetCount(), 4);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);
}

// ----------------------------------------- SPELL - SHAMAN
// [BAR_041] Nofin Can Stop Us - COST:3
// - Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: Give your minions +1/+1.
//       Give your Murlocs an extra +1/+1.
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - BAR_041 : Nofin Can Stop Us")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::SHAMAN;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Nofin Can Stop Us"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Tinyfin"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 2);
}

// ---------------------------------------- MINION - SHAMAN
// [BAR_043] Tinyfin's Caravan - COST:2 [ATK:1/HP:3]
// - Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: At the start of your turn, draw a Murloc.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - BAR_043 : Tinyfin's Caravan")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Murloc Tinyfin");
        config.player1Deck[i + 1] = Cards::FindCardByName("Malygos");
        config.player1Deck[i + 2] = Cards::FindCardByName("Wisp");
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Tinyfin's Caravan"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curHand[4]->card->GetRace(), Race::MURLOC);
}

// ---------------------------------------- MINION - SHAMAN
// [BAR_045] Arid Stormer - COST:3 [ATK:2/HP:5]
// - Race: Elemental, Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you played an Elemental last turn,
//       gain <b>Rush</b> and <b>Windfury</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// - WINDFURY = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - BAR_045 : Arid Stormer")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::SHAMAN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arid Stormer"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arid Stormer"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasRush(), false);
    CHECK_EQ(curField[0]->HasWindfury(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->HasRush(), true);
    CHECK_EQ(curField[1]->HasWindfury(), true);
}

// ---------------------------------------- MINION - SHAMAN
// [BAR_048] Bru'kan - COST:4 [ATK:5/HP:4]
// - Set: THE_BARRENS, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Nature Spell Damage +3</b>
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - BAR_048 : Bru'kan")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::PRIEST;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(20);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bru'kan"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Bloodmage Thalnos"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lightning Bolt"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lightning Bolt"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Silence"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetCurrentSpellPower(), 1);
    CHECK_EQ(curField[0]->GetSpellPowerNature(), 3);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 23);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card5, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 16);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card6, card1));
    CHECK_EQ(curPlayer->GetCurrentSpellPower(), 1);
    CHECK_EQ(curField[0]->GetSpellPowerNature(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 12);
}

// ---------------------------------------- MINION - SHAMAN
// [BAR_750] Earth Revenant - COST:4 [ATK:2/HP:6]
// - Race: Elemental, Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Battlecry:</b> Deal 1 damage to all enemy minions.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - BAR_750 : Earth Revenant")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::SHAMAN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Earth Revenant"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField.GetCount(), 2);
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 11);
}

// ---------------------------------------- MINION - SHAMAN
// [BAR_751] Spawnpool Forager - COST:1 [ATK:1/HP:2]
// - Race: Murloc, Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a 1/1 Tinyfin.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - BAR_751 : Spawnpool Forager")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::SHAMAN;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Spawnpool Forager"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Diremuck Tinyfin");
}

// ---------------------------------------- MINION - SHAMAN
// [BAR_848] Lilypad Lurker - COST:5 [ATK:5/HP:6]
// - Race: Elemental, Set: THE_BARRENS, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you played an Elemental
//       last turn, transform an enemy minion into a
//       0/1 Frog with <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_ENEMY_TARGET = 0
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_IF_AVAILABLE_AND_ELEMENTAL_PLAYED_LAST_TURN = 0
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - BAR_848 : Lilypad Lurker")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::SHAMAN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lilypad Lurker"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lilypad Lurker"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opField.GetCount(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card3));
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->card->name, "Frog");
    CHECK_EQ(opField[0]->GetAttack(), 0);
    CHECK_EQ(opField[0]->GetHealth(), 1);
    CHECK_EQ(opField[0]->HasTaunt(), true);
}

// ---------------------------------------- MINION - SHAMAN
// [BAR_860] Firemancer Flurgl - COST:2 [ATK:2/HP:3]
// - Race: Murloc, Set: THE_BARRENS, Rarity: Legendary
// --------------------------------------------------------
// Text: After you play a Murloc, deal 1 damage to all enemies.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - BAR_860 : Firemancer Flurgl")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::SHAMAN;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Firemancer Flurgl"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Tinyfin"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 29);
    CHECK_EQ(opField[0]->GetHealth(), 11);
}

// ---------------------------------------- MINION - SHAMAN
// [WC_005] Primal Dungeoneer - COST:3 [ATK:2/HP:3]
// - Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Draw a spell.
//       If it's a Nature spell, also draw an Elemental.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - WC_005 : Primal Dungeoneer")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Ice Rager");
        config.player1Deck[i + 1] = Cards::FindCardByName("Malygos");
        config.player1Deck[i + 2] = Cards::FindCardByName("Lightning Bolt");
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Primal Dungeoneer"));

    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curHand[4]->card->GetSpellSchool(), SpellSchool::NATURE);
    CHECK_EQ(curHand[5]->card->GetRace(), Race::ELEMENTAL);
}

// ---------------------------------------- MINION - SHAMAN
// [WC_042] Wailing Vapor - COST:1 [ATK:1/HP:3]
// - Race: Elemental, Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: After you play an Elemental, gain +1 Attack.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - WC_042 : Wailing Vapor")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::SHAMAN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wailing Vapor"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Tinyfin"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ice Rager"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 3);
}

// ---------------------------------------- SPELL - WARLOCK
// [BAR_910] Grimoire of Sacrifice - COST:1
// - Set: THE_BARRENS, Rarity: Common
// - Spell School: Shadow
// --------------------------------------------------------
// Text: Destroy a friendly minion.
//       Deal 2 damage to all enemy minions.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_FRIENDLY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - BAR_910 : Grimoire of Sacrifice")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::DRUID;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Grimoire of Sacrifice"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opField[0]->GetHealth(), 10);
}

// --------------------------------------- MINION - WARLOCK
// [BAR_912] Apothecary's Caravan - COST:2 [ATK:1/HP:3]
// - Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: At the start of your turn,
//       summon a 1-Cost minion from your deck.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - BAR_912 : Apothecary's Caravan")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Worgen Infiltrator");
        config.player1Deck[i + 1] = Cards::FindCardByName("Malygos");
        config.player1Deck[i + 2] = Cards::FindCardByName("Wisp");
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Apothecary's Caravan"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->GetCost(), 1);
}

// ---------------------------------------- SPELL - WARLOCK
// [BAR_913] Altar of Fire - COST:1
// - Set: THE_BARRENS, Rarity: Epic
// - Spell School: Fire
// --------------------------------------------------------
// Text: Destroy the top 3 cards of each deck.
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - BAR_913 : Altar of Fire")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Worgen Infiltrator");
        config.player1Deck[i + 1] = Cards::FindCardByName("Malygos");
        config.player1Deck[i + 2] = Cards::FindCardByName("Wisp");

        config.player2Deck[i] = Cards::FindCardByName("Worgen Infiltrator");
        config.player2Deck[i + 1] = Cards::FindCardByName("Malygos");
        config.player2Deck[i + 2] = Cards::FindCardByName("Wisp");
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

    auto& curDeck = *(curPlayer->GetDeckZone());
    auto& opDeck = *(opPlayer->GetDeckZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Altar of Fire"));

    CHECK_EQ(curDeck.GetCount(), 26);
    CHECK_EQ(opDeck.GetCount(), 26);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curDeck.GetCount(), 23);
    CHECK_EQ(opDeck.GetCount(), 23);
}

// ---------------------------------------- SPELL - WARLOCK
// [BAR_914] Imp Swarm (Rank 1) - COST:2
// - Set: THE_BARRENS, Rarity: Common
// - Spell School: Fel
// --------------------------------------------------------
// Text: Summon a 3/2 Imp.
//       <i>(Upgrades when you have 5 Mana.)</i>
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - BAR_914 : Imp Swarm (Rank 1)")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(4);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(4);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Imp Swarm (Rank 1)"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Imp Swarm (Rank 1)"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Imp Swarm (Rank 1)"));

    CHECK_EQ(card1->card->name, "Imp Swarm (Rank 1)");
    CHECK_EQ(card2->card->name, "Imp Swarm (Rank 1)");
    CHECK_EQ(card3->card->name, "Imp Swarm (Rank 1)");

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Imp Familiar");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->card->name, "Imp Swarm (Rank 1)");
    CHECK_EQ(card3->card->name, "Imp Swarm (Rank 1)");

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->card->name, "Imp Swarm (Rank 2)");
    CHECK_EQ(card3->card->name, "Imp Swarm (Rank 2)");

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[1]->card->name, "Imp Familiar");
    CHECK_EQ(curField[2]->card->name, "Imp Familiar");

    curPlayer->SetTotalMana(9);
    opPlayer->SetTotalMana(9);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card3->card->name, "Imp Swarm (Rank 2)");

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card3->card->name, "Imp Swarm (Rank 3)");

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curField.GetCount(), 6);
    CHECK_EQ(curField[3]->card->name, "Imp Familiar");
    CHECK_EQ(curField[4]->card->name, "Imp Familiar");
    CHECK_EQ(curField[5]->card->name, "Imp Familiar");
}

// --------------------------------------- MINION - WARLOCK
// [BAR_915] Kabal Outfitter - COST:3 [ATK:3/HP:3]
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry and Deathrattle:</b>
//       Give another random friendly minion +1/+1.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - BAR_915 : Kabal Outfitter")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARLOCK;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Kabal Outfitter"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 3);
}

// --------------------------------------- MINION - WARLOCK
// [BAR_916] Blood Shard Bristleback - COST:3 [ATK:3/HP:3]
// - Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Lifesteal</b>. <b>Battlecry:</b>
//       If your deck contains 10 or fewer cards,
//       deal 6 damage to a minion.
// --------------------------------------------------------
// GameTag:
// - LIFESTEAL = 1
// --------------------------------------------------------
// RefTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_ENEMY_TARGET = 0
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_IF_AVAILABLE_AND_MAXIMUM_CARDS_IN_DECK = 10
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - BAR_916 : Blood Shard Bristleback")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 16; i += 4)
    {
        config.player1Deck[i] = Cards::FindCardByName("Worgen Infiltrator");
        config.player1Deck[i + 1] = Cards::FindCardByName("Malygos");
        config.player1Deck[i + 2] = Cards::FindCardByName("Wisp");
        config.player1Deck[i + 3] = Cards::FindCardByName("Wolfrider");
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Blood Shard Bristleback"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Blood Shard Bristleback"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card3));
    CHECK_EQ(opField[0]->GetHealth(), 6);
}

// --------------------------------------- MINION - WARLOCK
// [BAR_917] Barrens Scavenger - COST:6 [ATK:6/HP:6]
// - Set: THE_BARRENS, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       Costs (1) while your deck has 10 or fewer cards.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - BAR_917 : Barrens Scavenger")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 15; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Worgen Infiltrator");
        config.player1Deck[i + 1] = Cards::FindCardByName("Malygos");
        config.player1Deck[i + 2] = Cards::FindCardByName("Wisp");
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Barrens Scavenger"));

    CHECK_EQ(card1->GetCost(), 6);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card1->GetCost(), 1);
}

// ---------------------------------------- SPELL - WARLOCK
// [WC_021] Unstable Shadow Blast - COST:2
// - Set: THE_BARRENS, Rarity: Common
// - Spell School: Shadow
// --------------------------------------------------------
// Text: Deal 6 damage to a minion.
//       Excess damage hits your hero.
// --------------------------------------------------------
// GameTag:
// - ImmuneToSpellpower = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - WC_021 : Unstable Shadow Blast")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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
        curPlayer, Cards::FindCardByName("Unstable Shadow Blast"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Unstable Shadow Blast"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Kobold Geomancer"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card4));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 25);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card5));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card5));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 19);
}

// ---------------------------------------- SPELL - WARLOCK
// [WC_022] Final Gasp - COST:1
// - Set: THE_BARRENS, Rarity: Common
// - Spell School: Shadow
// --------------------------------------------------------
// Text: Deal 1 damage to a minion. If it dies,
//       summon a 2/2 Adventurer with a random bonus effect.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// Entourage: WC_034t,  WC_034t2, WC_034t3, WC_034t4
//            WC_034t5, WC_034t6, WC_034t7, WC_034t8
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - WC_022 : Final Gasp")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::ROGUE;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Final Gasp"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Final Gasp"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Kobold Geomancer"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->GetHealth(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->IsAdventurer(), true);
}

// --------------------------------------- MINION - WARRIOR
// [BAR_334] Overlord Saurfang - COST:7 [ATK:5/HP:4]
// - Set: THE_BARRENS, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Resurrect 2 friendly <b>Frenzy</b>
//       minions. Deal 1 damage to all other minions.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - FRENZY = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - BAR_334 : Overlord Saurfang")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARRIOR;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Overlord Saurfang"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Stonemaul Anchorman"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Stonemaul Anchorman"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField.GetCount(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card5, card2));
    game.Process(opPlayer, PlayCardTask::SpellTarget(card6, card3));
    game.Process(opPlayer, HeroPowerTask(card4));
    CHECK_EQ(curField.GetCount(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 6);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curHand.GetCount(), 7);
    CHECK_EQ(curField[1]->GetHealth(), 5);
    CHECK_EQ(curField[2]->GetHealth(), 5);
}

// --------------------------------------- MINION - WARRIOR
// [BAR_840] Whirling Combatant - COST:4 [ATK:3/HP:6]
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry and Frenzy:</b>
//       Deal 1 damage to all other minions.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - FRENZY = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - BAR_840 : Whirling Combatant")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::MAGE;
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Whirling Combatant"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField.GetCount(), 2);
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 11);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(opField[0]->GetHealth(), 10);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card1));
    CHECK_EQ(opField[0]->GetHealth(), 10);
}

// ---------------------------------------- SPELL - WARRIOR
// [BAR_841] Bulk Up - COST:2
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: Give a random <b>Taunt</b> minion in your hand +1/+1
//       and copy it.
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - BAR_841 : Bulk Up")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::MAGE;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bulk Up"));
    [[maybe_unused]] const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    [[maybe_unused]] const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Sen'jin Shieldmasta"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 3);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[0])->GetAttack(), 4);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[0])->GetHealth(), 12);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[1])->GetAttack(), 4);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[1])->GetHealth(), 6);
    CHECK_EQ(curHand[2]->card->name, "Sen'jin Shieldmasta");
    CHECK_EQ(dynamic_cast<Minion*>(curHand[2])->GetAttack(), 4);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[2])->GetHealth(), 6);
}

// ---------------------------------------- SPELL - WARRIOR
// [BAR_842] Conditioning (Rank 1) - COST:2
// - Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: Give minions in your hand +1/+1.
//       <i>(Upgrades when you have 5 Mana.)</i>
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - BAR_842 : Conditioning (Rank 1)")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(4);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(4);
    opPlayer->SetUsedMana(0);

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Conditioning (Rank 1)"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Conditioning (Rank 1)"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Conditioning (Rank 1)"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));

    const auto minion4 = dynamic_cast<Minion*>(card4);
    const auto minion5 = dynamic_cast<Minion*>(card5);
    const auto minion6 = dynamic_cast<Minion*>(card6);

    CHECK_EQ(card1->card->name, "Conditioning (Rank 1)");
    CHECK_EQ(card2->card->name, "Conditioning (Rank 1)");
    CHECK_EQ(card3->card->name, "Conditioning (Rank 1)");

    CHECK_EQ(minion4->GetAttack(), 1);
    CHECK_EQ(minion4->GetHealth(), 1);
    CHECK_EQ(minion5->GetAttack(), 3);
    CHECK_EQ(minion5->GetHealth(), 1);
    CHECK_EQ(minion6->GetAttack(), 4);
    CHECK_EQ(minion6->GetHealth(), 12);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(minion4->GetAttack(), 2);
    CHECK_EQ(minion4->GetHealth(), 2);
    CHECK_EQ(minion5->GetAttack(), 4);
    CHECK_EQ(minion5->GetHealth(), 2);
    CHECK_EQ(minion6->GetAttack(), 5);
    CHECK_EQ(minion6->GetHealth(), 13);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->card->name, "Conditioning (Rank 1)");
    CHECK_EQ(card3->card->name, "Conditioning (Rank 1)");

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->card->name, "Conditioning (Rank 2)");
    CHECK_EQ(card3->card->name, "Conditioning (Rank 2)");

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(minion4->GetAttack(), 4);
    CHECK_EQ(minion4->GetHealth(), 4);
    CHECK_EQ(minion5->GetAttack(), 6);
    CHECK_EQ(minion5->GetHealth(), 4);
    CHECK_EQ(minion6->GetAttack(), 7);
    CHECK_EQ(minion6->GetHealth(), 15);

    curPlayer->SetTotalMana(9);
    opPlayer->SetTotalMana(9);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card3->card->name, "Conditioning (Rank 2)");

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card3->card->name, "Conditioning (Rank 3)");

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(minion4->GetAttack(), 7);
    CHECK_EQ(minion4->GetHealth(), 7);
    CHECK_EQ(minion5->GetAttack(), 9);
    CHECK_EQ(minion5->GetHealth(), 7);
    CHECK_EQ(minion6->GetAttack(), 10);
    CHECK_EQ(minion6->GetHealth(), 18);
}

// --------------------------------------- MINION - WARRIOR
// [BAR_843] Warsong Envoy - COST:1 [ATK:1/HP:3]
// - Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Frenzy:</b> Gain +1 Attack
//       for each damaged character.
// --------------------------------------------------------
// GameTag:
// - FRENZY = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - BAR_843 : Warsong Envoy")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::MAGE;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Warsong Envoy"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 2);
}

// --------------------------------------- WEAPON - WARRIOR
// [BAR_844] Outrider's Axe - COST:4
// - Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: After your hero attacks and kills a minion, draw a card.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Weapon] - BAR_844 : Outrider's Axe")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARRIOR;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Outrider's Axe"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, AttackTask(curPlayer->GetHero(), card2));
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(curPlayer->GetHero(), card3));
    CHECK_EQ(curHand.GetCount(), 7);
    CHECK_EQ(opField.GetCount(), 1);
}

// ---------------------------------------- SPELL - WARRIOR
// [BAR_845] Rancor - COST:4
// - Set: THE_BARRENS, Rarity: Epic
// --------------------------------------------------------
// Text: Deal 2 damage to all minions.
//       Gain 2 Armor for each destroyed.
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - BAR_845 : Rancor")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARRIOR;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Rancor"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 5);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 5);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 4);
}

// --------------------------------------- MINION - WARRIOR
// [BAR_846] Mor'shan Elite - COST:5 [ATK:4/HP:4]
// - Set: THE_BARRENS, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Taunt</b>. <b>Battlecry:</b> If your hero
//       attacked this turn, summon a copy of this.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - BAR_846 : Mor'shan Elite")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARRIOR;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mor'shan Elite"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mor'shan Elite"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Outrider's Axe"));

    game.Process(curPlayer, PlayCardTask::Weapon(card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[2]->card->name, "Mor'shan Elite");
}

// --------------------------------------- MINION - WARRIOR
// [BAR_847] Rokara - COST:3 [ATK:2/HP:3]
// - Set: THE_BARRENS, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Rush</b>
//       After a friendly minion attacks and survives,
//       give it +1/+1.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - RUSH = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - BAR_847 : Rokara")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARRIOR;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Rokara"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Rokara"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Stonemaul Anchorman"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(curField[1]->GetAttack(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 6);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 4);

    game.Process(curPlayer, AttackTask(card3, opPlayer->GetHero()));
    CHECK_EQ(curField[1]->GetAttack(), 5);
    CHECK_EQ(curField[1]->GetHealth(), 7);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, AttackTask(card2, card4));
    CHECK_EQ(curField[2]->GetAttack(), 4);
    CHECK_EQ(curField[2]->GetHealth(), 4);
}

// --------------------------------------- MINION - WARRIOR
// [BAR_896] Stonemaul Anchorman - COST:5 [ATK:4/HP:6]
// - Race: Pirate, Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Rush</b>
//       <b>Frenzy:</b> Draw a card.
// --------------------------------------------------------
// GameTag:
// - FRENZY = 1
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - BAR_896 : Stonemaul Anchorman")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARRIOR;
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

    const auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Stonemaul Anchorman"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curHand.GetCount(), 5);
}

// --------------------------------------- MINION - WARRIOR
// [WC_024] Man-at-Arms - COST:2 [ATK:2/HP:3]
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you have a weapon equipped,
//       gain +1/+1.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - WC_024 : Man-at-Arms")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARRIOR;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Man-at-Arms"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Man-at-Arms"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Outrider's Axe"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, PlayCardTask::Weapon(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 4);
}

// --------------------------------------- WEAPON - WARRIOR
// [WC_025] Whetstone Hatchet - COST:1
// - Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: After your hero attacks,
//       give a minion in your hand +1 Attack.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Weapon] - WC_025 : Whetstone Hatchet")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARRIOR;
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
        curPlayer, Cards::FindCardByName("Whetstone Hatchet"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(dynamic_cast<Minion*>(card2)->GetAttack(), 2);
    CHECK_EQ(dynamic_cast<Minion*>(card2)->GetHealth(), 1);
}

// --------------------------------------- MINION - WARRIOR
// [WC_026] Kresh, Lord of Turtling - COST:6 [ATK:3/HP:9]
// - Race: Beast, Set: THE_BARRENS, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Frenzy:</b> Gain 8 Armor.
//       <b>Deathrattle:</b> Equip a 2/5 Turtle Spike.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - DEATHRATTLE = 1
// - FRENZY = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - WC_026 : Kresh, Lord of Turtling")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARRIOR;
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

    auto& curHero = *(curPlayer->GetHero());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Kresh, Lord of Turtling"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHero.GetArmor(), 0);
    CHECK_EQ(curHero.HasWeapon(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curHero.GetArmor(), 8);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(curHero.HasWeapon(), true);
    CHECK_EQ(curHero.weapon->card->name, "Turtle Spike");
    CHECK_EQ(curHero.weapon->GetAttack(), 2);
    CHECK_EQ(curHero.weapon->GetDurability(), 5);
}

// ------------------------------------ SPELL - DEMONHUNTER
// [BAR_306] Sigil of Flame - COST:2
// - Set: THE_BARRENS, Rarity: Epic
// - Spell School: Fel
// --------------------------------------------------------
// Text: At the start of your next turn,
//       deal 3 damage to all minions.
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - BAR_306 : Sigil of Flame")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sigil of Flame"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Kresh, Lord of Turtling"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Kresh, Lord of Turtling"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetHealth(), 9);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->GetHealth(), 9);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetHealth(), 6);
    CHECK_EQ(opField[0]->GetHealth(), 6);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetHealth(), 6);
    CHECK_EQ(opField[0]->GetHealth(), 6);
}

// ----------------------------------- MINION - DEMONHUNTER
// [BAR_325] Razorboar - COST:2 [ATK:3/HP:2]
// - Race: Beast, Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a <b>Deathrattle</b>
//       minion that costs (3) or less from your hand.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - BAR_325 : Razorboar")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Razorboar"));
    [[maybe_unused]] const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Razorfen Beastmaster"));
    [[maybe_unused]] const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Plagued Protodrake"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 6);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Razorfen Beastmaster");
    CHECK_EQ(curHand.GetCount(), 5);
}

// ----------------------------------- MINION - DEMONHUNTER
// [BAR_326] Razorfen Beastmaster - COST:3 [ATK:3/HP:3]
// - Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a <b>Deathrattle</b>
//       minion that costs (4) or less from your hand.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - BAR_326 : Razorfen Beastmaster")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Razorfen Beastmaster"));
    [[maybe_unused]] const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Razorfen Beastmaster"));
    [[maybe_unused]] const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Plagued Protodrake"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 6);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Razorfen Beastmaster");
    CHECK_EQ(curHand.GetCount(), 5);
}

// ------------------------------------ SPELL - DEMONHUNTER
// [BAR_327] Vile Call - COST:3
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: Summon two 2/2 Demons with <b>Lifesteal</b>.
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
// RefTag:
// - LIFESTEAL = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - BAR_327 : Vile Call")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Vile Call"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Ravenous Vilefiend");
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[0]->HasLifesteal(), true);
    CHECK_EQ(curField[1]->card->name, "Ravenous Vilefiend");
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(curField[1]->HasLifesteal(), true);
}

// ----------------------------------- MINION - DEMONHUNTER
// [BAR_328] Vengeful Spirit - COST:4 [ATK:4/HP:4]
// - Set: THE_BARRENS, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Outcast:</b> Draw 2 <b>Deathrattle</b> minions.
// --------------------------------------------------------
// GameTag:
// - OUTCAST = 1
// --------------------------------------------------------
// RefTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - BAR_328 : Vengeful Spirit")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Savannah Highmane");
        config.player1Deck[i + 1] = Cards::FindCardByName("Malygos");
        config.player1Deck[i + 2] = Cards::FindCardByName("Wisp");
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Vengeful Spirit"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Vengeful Spirit"));

    CHECK_EQ(curHand.GetCount(), 6);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[4])->HasDeathrattle(), true);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[5])->HasDeathrattle(), true);
}

// ----------------------------------- MINION - DEMONHUNTER
// [BAR_329] Death Speaker Blackthorn - COST:7 [ATK:3/HP:6]
// - Set: THE_BARRENS, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon 3 <b>Deathrattle</b>
//       minions that cost (5) or less from your deck.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - BAR_329 : Death Speaker Blackthorn")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Savannah Highmane");
        config.player1Deck[i + 1] = Cards::FindCardByName("Malygos");
        config.player1Deck[i + 2] = Cards::FindCardByName("Teacher's Pet");
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

    auto& curDeck = *(curPlayer->GetDeckZone());
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Death Speaker Blackthorn"));

    CHECK_EQ(curDeck.GetCount(), 26);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curDeck.GetCount(), 23);
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[1]->HasDeathrattle(), true);
    CHECK_LE(curField[1]->GetCost(), 5);
    CHECK_EQ(curField[2]->HasDeathrattle(), true);
    CHECK_LE(curField[2]->GetCost(), 5);
    CHECK_EQ(curField[3]->HasDeathrattle(), true);
    CHECK_LE(curField[3]->GetCost(), 5);
}

// ----------------------------------- WEAPON - DEMONHUNTER
// [BAR_330] Tuskpiercer - COST:1
// - Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Draw a <b>Deathrattle</b> minion.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Weapon] - BAR_330 : Tuskpiercer")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Savannah Highmane");
        config.player1Deck[i + 1] = Cards::FindCardByName("Malygos");
        config.player1Deck[i + 2] = Cards::FindCardByName("Wisp");
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Tuskpiercer"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Tuskpiercer"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 1);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 2);

    game.Process(curPlayer, PlayCardTask::Weapon(card2));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[4])->HasDeathrattle(), true);
}

// ----------------------------------- MINION - DEMONHUNTER
// [BAR_333] Kurtrus Ashfallen - COST:4 [ATK:3/HP:4]
// - Set: THE_BARRENS, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Attack the left and right-most
//       enemy minions.
//       <b>Outcast:</b> <b>Immune</b> this turn.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// - OUTCAST = 1
// --------------------------------------------------------
// RefTag:
// - IMMUNE = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - BAR_333 : Kurtrus Ashfallen")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
    config.player2Class = CardClass::MAGE;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Kurtrus Ashfallen"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Kurtrus Ashfallen"));
    [[maybe_unused]] const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opField[0]->GetHealth(), 9);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->IsImmune(), true);
    CHECK_EQ(opField[0]->GetHealth(), 6);
    CHECK_EQ(opField[1]->GetHealth(), 9);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->IsImmune(), false);
}

// ------------------------------------ SPELL - DEMONHUNTER
// [BAR_705] Sigil of Silence - COST:0
// - Set: THE_BARRENS, Rarity: Rare
// - Spell School: Shadow
// --------------------------------------------------------
// Text: At the start of your next turn,
//       <b>Silence</b> all enemy minions.
// --------------------------------------------------------
// RefTag:
// - SILENCE = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - BAR_705 : Sigil of Silence")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sigil of Silence"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Kresh, Lord of Turtling"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Teacher's Pet"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->HasFrenzy(), true);
    CHECK_EQ(curField[0]->HasDeathrattle(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->HasTaunt(), true);
    CHECK_EQ(opField[0]->HasDeathrattle(), true);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->HasFrenzy(), true);
    CHECK_EQ(curField[0]->HasDeathrattle(), true);
    CHECK_EQ(opField[0]->HasTaunt(), false);
    CHECK_EQ(opField[0]->HasDeathrattle(), false);
}

// ------------------------------------ SPELL - DEMONHUNTER
// [BAR_891] Fury (Rank 1) - COST:1
// - Set: THE_BARRENS, Rarity: Common
// - Spell School: Fel
// --------------------------------------------------------
// Text: Give your hero +2 Attack this turn.
//       <i>(Upgrades when you have 5 Mana.)</i>
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - BAR_891 : Fury (Rank 1)")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(4);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(4);
    opPlayer->SetUsedMana(0);

    auto& curHero = *(curPlayer->GetHero());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fury (Rank 1)"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fury (Rank 1)"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fury (Rank 1)"));

    CHECK_EQ(card1->card->name, "Fury (Rank 1)");
    CHECK_EQ(card2->card->name, "Fury (Rank 1)");
    CHECK_EQ(card3->card->name, "Fury (Rank 1)");

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHero.GetAttack(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->card->name, "Fury (Rank 1)");
    CHECK_EQ(card3->card->name, "Fury (Rank 1)");

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->card->name, "Fury (Rank 2)");
    CHECK_EQ(card3->card->name, "Fury (Rank 2)");

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curHero.GetAttack(), 3);

    curPlayer->SetTotalMana(9);
    opPlayer->SetTotalMana(9);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card3->card->name, "Fury (Rank 2)");

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card3->card->name, "Fury (Rank 3)");

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curHero.GetAttack(), 4);
}

// ------------------------------------ SPELL - DEMONHUNTER
// [WC_003] Sigil of Summoning - COST:2
// - Set: THE_BARRENS, Rarity: Rare
// - Spell School: Shadow
// --------------------------------------------------------
// Text: At the start of your next turn,
//       summon two 2/2 Demons with <b>Taunt</b>.
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - WC_003 : Sigil of Summoning")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Sigil of Summoning"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Wailing Demon");
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[1]->card->name, "Wailing Demon");
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(curField[1]->HasTaunt(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 2);
}

// ----------------------------------- MINION - DEMONHUNTER
// [WC_040] Taintheart Tormenter - COST:8 [ATK:8/HP:8]
// - Race: Demon, Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       Your opponent's spells cost (2) more.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - WC_040 : Taintheart Tormenter")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
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
        curPlayer, Cards::FindCardByName("Taintheart Tormenter"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Frostbolt"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Pyroblast"));

    CHECK_EQ(card2->GetCost(), 0);
    CHECK_EQ(card3->GetCost(), 2);
    CHECK_EQ(card4->GetCost(), 4);
    CHECK_EQ(card5->GetCost(), 10);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card2->GetCost(), 0);
    CHECK_EQ(card3->GetCost(), 4);
    CHECK_EQ(card4->GetCost(), 6);
    CHECK_EQ(card5->GetCost(), 12);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(card2->GetCost(), 0);
    CHECK_EQ(card4->GetCost(), 6);
    CHECK_EQ(card5->GetCost(), 12);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card1));
    CHECK_EQ(card2->GetCost(), 0);
    CHECK_EQ(card5->GetCost(), 10);
}

// ----------------------------------- MINION - DEMONHUNTER
// [WC_701] Felrattler - COST:3 [ATK:3/HP:2]
// - Race: Beast, Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Rush</b>
//       <b>Deathrattle:</b> Deal 1 damage to all enemy minions.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - WC_701 : Felrattler")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Felrattler"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, AttackTask(card1, card2));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opField[0]->GetHealth(), 8);
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_020] Razormane Raider - COST:5 [ATK:5/HP:6]
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Frenzy:</b> Attack a random enemy.
// --------------------------------------------------------
// GameTag:
// - FRENZY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_020 : Razormane Raider")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARRIOR;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Razormane Raider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 25);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 25);
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_021] Gold Road Grunt - COST:5 [ATK:3/HP:7]
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Frenzy:</b> Gain Armor equal to the damage taken.
// --------------------------------------------------------
// GameTag:
// - FRENZY = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_021 : Gold Road Grunt")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARRIOR;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Gold Road Grunt"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 6);
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_022] Peon - COST:2 [ATK:2/HP:3]
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Frenzy:</b> Add a random spell from your class
//       to your hand.
// --------------------------------------------------------
// GameTag:
// - FRENZY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_022 : Peon")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::HUNTER;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Peon"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->GetCardType(), CardType::SPELL);
    CHECK_EQ(curHand[4]->card->IsCardClass(CardClass::HUNTER), true);
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_024] Oasis Thrasher - COST:2 [ATK:2/HP:3]
// - Race: Beast, Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Frenzy:</b> Deal 3 damage to the enemy Hero.
// --------------------------------------------------------
// GameTag:
// - FRENZY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_024 : Oasis Thrasher")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::HUNTER;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Oasis Thrasher"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_025] Sunwell Initiate - COST:3 [ATK:3/HP:4]
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Frenzy:</b> Gain <b>Divine Shield</b>.
// --------------------------------------------------------
// GameTag:
// - FRENZY = 1
// --------------------------------------------------------
// RefTag:
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_025 : Sunwell Initiate")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::HUNTER;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sunwell Initiate"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasDivineShield(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->HasDivineShield(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_026] Death's Head Cultist - COST:3 [ATK:2/HP:4]
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Deathrattle:</b> Restore 4 Health to your hero.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_026 : Death's Head Cultist")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Death's Head Cultist"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 24);
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_027] Darkspear Berserker - COST:4 [ATK:5/HP:7]
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Deal 5 damage to your hero.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_027 : Darkspear Berserker")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::HUNTER;
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
        curPlayer, Cards::FindCardByName("Darkspear Berserker"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Pyroblast"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 25);
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_042] Primordial Protector - COST:8 [ATK:6/HP:6]
// - Race: Elemental, Set: THE_BARRENS, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Draw your highest Cost spell.
//       Summon a random minion with the same Cost.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_042 : Primordial Protector")
{
    GameConfig config;
    config.player1Class = CardClass::DEMONHUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Pyroblast");
        config.player1Deck[i + 1] = Cards::FindCardByName("Fireball");
        config.player1Deck[i + 2] = Cards::FindCardByName("Wisp");
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Primordial Protector"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Pyroblast");
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->GetCost(), 10);
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_060] Hog Rancher - COST:3 [ATK:3/HP:2]
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a 2/1 Hog with <b>Rush</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_060 : Hog Rancher")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::HUNTER;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hog Rancher"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->name, "Hog");
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[1]->HasRush(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_061] Ratchet Privateer - COST:3 [ATK:4/HP:3]
// - Race: Pirate, Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give your weapon +1 Attack.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_061 : Ratchet Privateer")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::ROGUE;
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
        curPlayer, Cards::FindCardByName("Ratchet Privateer"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Ratchet Privateer"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 2);
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_062] Lushwater Murcenary - COST:2 [ATK:3/HP:2]
// - Race: Murloc, Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you control a Murloc, gain +1/+1.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_062 : Lushwater Murcenary")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::ROGUE;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Lushwater Murcenary"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Lushwater Murcenary"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_063] Lushwater Scout - COST:2 [ATK:1/HP:3]
// - Race: Murloc, Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: After you summon a Murloc,
//       give it +1 Attack and <b>Rush</b>.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_063 : Lushwater Scout")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::ROGUE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lushwater Scout"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Tinyfin"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[1]->HasRush(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_064] Talented Arcanist - COST:2 [ATK:1/HP:3]
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Your next spell this turn has
//       <b>Spell Damage +2</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - SPELLPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_064 : Talented Arcanist")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Talented Arcanist"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Talented Arcanist"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetCurrentSpellPower(), 2);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetCurrentSpellPower(), 0);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 22);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetCurrentSpellPower(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetCurrentSpellPower(), 0);
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_065] Venomous Scorpid - COST:3 [ATK:1/HP:3]
// - Race: Beast, Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Poisonous</b>
//       <b>Battlecry:</b> <b>Discover</b> a spell.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - DISCOVER = 1
// - POISONOUS = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_065 : Venomous Scorpid")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Venomous Scorpid"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::SPELL);
        CHECK(card->IsCardClass(CardClass::HUNTER));
    }
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_069] Injured Marauder - COST:4 [ATK:5/HP:10]
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Battlecry:</b> Deal 6 damage to this minion.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_069 : Injured Marauder")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::ROGUE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Injured Marauder"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 4);
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_070] Gruntled Patron - COST:4 [ATK:3/HP:3]
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Frenzy:</b> Summon another Gruntled Patron.
// --------------------------------------------------------
// GameTag:
// - FRENZY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_070 : Gruntled Patron")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::MAGE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Gruntled Patron"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->HasFrenzy(), false);
    CHECK_EQ(curField[1]->HasFrenzy(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(curField[1]));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[1]->HasFrenzy(), false);
    CHECK_EQ(curField[2]->HasFrenzy(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_071] Taurajo Brave - COST:6 [ATK:4/HP:8]
// - Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Frenzy:</b> Destroy a random enemy minion.
// --------------------------------------------------------
// GameTag:
// - FRENZY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_071 : Taurajo Brave")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Taurajo Brave"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(opField.GetCount(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_072] Burning Blade Acolyte - COST:5 [ATK:1/HP:1]
// - Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a 5/8 Demonspawn
//       with <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_072 : Burning Blade Acolyte")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Burning Blade Acolyte"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Demonspawn");
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 8);
    CHECK_EQ(curField[0]->HasTaunt(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_073] Barrens Blacksmith - COST:5 [ATK:3/HP:5]
// - Set: THE_BARRENS, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Frenzy:</b> Give your other minions +2/+2.
// --------------------------------------------------------
// GameTag:
// - FRENZY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_073 : Barrens Blacksmith")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Barrens Blacksmith"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 5);
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[2]->GetAttack(), 1);
    CHECK_EQ(curField[2]->GetHealth(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetAttack(), 5);
    CHECK_EQ(curField[1]->GetHealth(), 3);
    CHECK_EQ(curField[2]->GetAttack(), 3);
    CHECK_EQ(curField[2]->GetHealth(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_074] Far Watch Post - COST:2 [ATK:2/HP:3]
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: Can't attack. After your opponent draws a card,
//       it costs (1) more <i>(up to 10)</i>.
// --------------------------------------------------------
// GameTag:
// - CANT_ATTACK = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_074 : Far Watch Post")
{
    // Normal Case
    {
        GameConfig config;
        config.player1Class = CardClass::MAGE;
        config.player2Class = CardClass::WARRIOR;
        config.startPlayer = PlayerType::PLAYER1;
        config.doFillDecks = false;
        config.autoRun = false;

        for (int i = 0; i < 30; ++i)
        {
            config.player2Deck[i] = Cards::FindCardByName("Ice Barrier");
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

        auto& curField = *(curPlayer->GetFieldZone());
        auto& opHand = *(opPlayer->GetHandZone());

        const auto card1 = Generic::DrawCard(
            curPlayer, Cards::FindCardByName("Far Watch Post"));

        game.Process(curPlayer, PlayCardTask::Minion(card1));

        game.Process(curPlayer, EndTurnTask());
        game.ProcessUntil(Step::MAIN_ACTION);

        CHECK_EQ(opHand[5]->GetCost(), 4);

        game.Process(opPlayer, EndTurnTask());
        game.ProcessUntil(Step::MAIN_ACTION);

        CHECK_EQ(curField[0]->CanAttack(), false);

        game.Process(curPlayer, EndTurnTask());
        game.ProcessUntil(Step::MAIN_ACTION);

        CHECK_EQ(opHand[5]->GetCost(), 4);
        CHECK_EQ(opHand[6]->GetCost(), 4);
    }

    // 10-cost Card Case
    {
        GameConfig config;
        config.player1Class = CardClass::MAGE;
        config.player2Class = CardClass::WARRIOR;
        config.startPlayer = PlayerType::PLAYER1;
        config.doFillDecks = false;
        config.autoRun = false;

        for (int i = 0; i < 30; ++i)
        {
            config.player2Deck[i] = Cards::FindCardByName("Pyroblast");
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

        auto& curField = *(curPlayer->GetFieldZone());
        auto& opHand = *(opPlayer->GetHandZone());

        const auto card1 = Generic::DrawCard(
            curPlayer, Cards::FindCardByName("Far Watch Post"));

        game.Process(curPlayer, PlayCardTask::Minion(card1));

        game.Process(curPlayer, EndTurnTask());
        game.ProcessUntil(Step::MAIN_ACTION);

        CHECK_EQ(opHand[5]->GetCost(), 10);

        game.Process(opPlayer, EndTurnTask());
        game.ProcessUntil(Step::MAIN_ACTION);

        CHECK_EQ(curField[0]->CanAttack(), false);

        game.Process(curPlayer, EndTurnTask());
        game.ProcessUntil(Step::MAIN_ACTION);

        CHECK_EQ(opHand[5]->GetCost(), 10);
        CHECK_EQ(opHand[6]->GetCost(), 10);
    }
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_075] Crossroads Watch Post - COST:4 [ATK:4/HP:6]
// - Set: THE_BARRENS, Rarity: Epic
// --------------------------------------------------------
// Text: Can't attack. Whenever your opponent casts a spell,
//       give your minions +1/+1.
// --------------------------------------------------------
// GameTag:
// - CANT_ATTACK = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_075 : Crossroads Watch Post")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Crossroads Watch Post"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 6);
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[2]->GetAttack(), 1);
    CHECK_EQ(curField[2]->GetHealth(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card4, curPlayer->GetHero()));
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 7);
    CHECK_EQ(curField[1]->GetAttack(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(curField[2]->GetAttack(), 2);
    CHECK_EQ(curField[2]->GetHealth(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->CanAttack(), false);
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_076] Mor'shan Watch Post - COST:3 [ATK:3/HP:4]
// - Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: Can't attack. After your opponent plays a minion,
//       summon a 2/2 Grunt.
// --------------------------------------------------------
// GameTag:
// - CANT_ATTACK = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_076 : Mor'shan Watch Post")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mor'shan Watch Post"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->name, "Watchful Grunt");
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 2);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[2]->card->name, "Watchful Grunt");
    CHECK_EQ(curField[2]->GetAttack(), 2);
    CHECK_EQ(curField[2]->GetHealth(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->CanAttack(), false);
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_077] Kargal Battlescar - COST:7 [ATK:5/HP:5]
// - Set: THE_BARRENS, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a 5/5 Lookout for each
//       Watch Post you've summoned this game.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_077 : Kargal Battlescar")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Kargal Battlescar"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Far Watch Post"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mor'shan Watch Post"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mor'shan Watch Post"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Flamestrike"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(curField.GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card6));
    CHECK_EQ(curField.GetCount(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[1]->card->name, "Lookout");
    CHECK_EQ(curField[1]->GetAttack(), 5);
    CHECK_EQ(curField[1]->GetHealth(), 5);
    CHECK_EQ(curField[2]->card->name, "Lookout");
    CHECK_EQ(curField[2]->GetAttack(), 5);
    CHECK_EQ(curField[2]->GetHealth(), 5);
    CHECK_EQ(curField[3]->card->name, "Lookout");
    CHECK_EQ(curField[3]->GetAttack(), 5);
    CHECK_EQ(curField[3]->GetHealth(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_078] Blademaster Samuro - COST:4 [ATK:1/HP:6]
// - Set: THE_BARRENS, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Rush</b>
//       <b>Frenzy:</b> Deal damage equal to this minion's
//       Attack to all enemy minions.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - FRENZY = 1
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_078 : Blademaster Samuro")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::WARRIOR;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Blademaster Samuro"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, AttackTask(card1, card3));
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 11);
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_082] Barrens Trapper - COST:3 [ATK:2/HP:4]
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: Your <b>Deathrattle</b> cards cost (1) less.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
// RefTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_082 : Barrens Trapper")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Barrens Trapper"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Far Watch Post"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Loot Hoarder"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    CHECK_EQ(card2->GetCost(), 2);
    CHECK_EQ(card3->GetCost(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card2->GetCost(), 2);
    CHECK_EQ(card3->GetCost(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card1));
    CHECK_EQ(card2->GetCost(), 2);
    CHECK_EQ(card3->GetCost(), 2);
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_721] Mankrik - COST:3 [ATK:3/HP:4]
// - Set: THE_BARRENS, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Help Mankrik find his wife!
//       She was last seen somewhere in your deck.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_721 : Mankrik")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::MAGE;
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

    auto& curDeck = *(curPlayer->GetDeckZone());
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mankrik"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curDeck.GetCount(), 1);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 20);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curDeck.GetCount(), 0);
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->name, "Mankrik, Consumed by Hatred");
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 7);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 13);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 17);
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_743] Toad of the Wilds - COST:2 [ATK:2/HP:2]
// - Race: Beast, Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Battlecry:</b> If you're holding a Nature spell,
//       gain +2 Health.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_743 : Toad of the Wilds")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::MAGE;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Toad of the Wilds"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Toad of the Wilds"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Innervate"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 4);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 2);
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_744] Spirit Healer - COST:4 [ATK:3/HP:6]
// - Set: THE_BARRENS, Rarity: Epic
// --------------------------------------------------------
// Text: After you cast a Holy spell,
//       give a random friendly minion +2 Health.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_744 : Spirit Healer")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::MAGE;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Spirit Healer"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Holy Light"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 6);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField[0]->GetHealth(), 8);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curField[0]->GetHealth(), 8);
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_745] Hecklefang Hyena - COST:2 [ATK:2/HP:4]
// - Race: Beast, Set: THE_BARRENS, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 3 damage to your hero.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_745 : Hecklefang Hyena")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hecklefang Hyena"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 27);
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_854] Kindling Elemental - COST:1 [ATK:1/HP:2]
// - Race: Elemental, Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> The next Elemental you play
//       costs (1) less.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_854 : Kindling Elemental")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
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
        curPlayer, Cards::FindCardByName("Kindling Elemental"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Unbound Elemental"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wailing Vapor"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wailing Vapor"));
    const auto card5 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Stranglethorn Tiger"));

    CHECK_EQ(card2->GetCost(), 3);
    CHECK_EQ(card3->GetCost(), 1);
    CHECK_EQ(card4->GetCost(), 1);
    CHECK_EQ(card5->GetCost(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetRemainingMana(), 9);
    CHECK_EQ(card2->GetCost(), 1);
    CHECK_EQ(card3->GetCost(), 0);
    CHECK_EQ(card4->GetCost(), 0);
    CHECK_EQ(card5->GetCost(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curPlayer->GetRemainingMana(), 9);
    CHECK_EQ(card2->GetCost(), 3);
    CHECK_EQ(card4->GetCost(), 1);
    CHECK_EQ(card5->GetCost(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [BAR_890] Crossroads Gossiper - COST:3 [ATK:4/HP:3]
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: After a friendly <b>Secret</b> is revealed, gain +2/+2.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - BAR_890 : Crossroads Gossiper")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::WARRIOR;
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
    auto& curSecret = *(curPlayer->GetSecretZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Crossroads Gossiper"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Snipe"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Chillwind Yeti"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curSecret.GetCount(), 0);
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [WC_027] Devouring Ectoplasm - COST:3 [ATK:3/HP:2]
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a 2/2 Adventurer
//       with a random bonus effect.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
// Entourage: WC_034t,  WC_034t2, WC_034t3, WC_034t4
//            WC_034t5, WC_034t6, WC_034t7, WC_034t8
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - WC_027 : Devouring Ectoplasm")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Devouring Ectoplasm"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->card->IsAdventurer(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->IsAdventurer(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [WC_028] Meeting Stone - COST:1 [ATK:0/HP:2]
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: At the end of your turn, add a 2/2 Adventurer
//       with a random bonus effect to your hand.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - WC_028 : Meeting Stone")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Meeting Stone"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->IsAdventurer(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [WC_029] Selfless Sidekick - COST:7 [ATK:6/HP:6]
// - Set: THE_BARRENS, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Equip a random weapon from your deck.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - WC_029 : Selfless Sidekick")
{
    GameConfig config;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Fiery War Axe");
        config.player1Deck[i + 1] = Cards::FindCardByName("Malygos");
        config.player1Deck[i + 2] = Cards::FindCardByName("Wisp");
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

    auto& curDeck = *(curPlayer->GetDeckZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Selfless Sidekick"));

    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), false);
    CHECK_EQ(curDeck.GetCount(), 26);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), true);
    CHECK_EQ(curDeck.GetCount(), 25);
}