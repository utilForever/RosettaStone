// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetHeaders.hpp>

// ----------------------------------------- HERO - WARLOCK
// [CORE_EX1_323] Lord Jaraxxus - COST:9
// - Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Equip a 3/8 Blood Fury.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Hero] - CORE_EX1_323 : Lord Jaraxxus")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARLOCK;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByID("EX1_323"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 5);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 3);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 8);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 6);
}

// ------------------------------------------ SPELL - DRUID
// [CORE_AT_037] Living Roots - COST:1
// - Set: CORE, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: <b>Choose One -</b> Deal 2 damage;
//       or Summon two 1/1 Saplings.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - CORE_AT_037 : Living Roots")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::DRUID;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Living Roots"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Living Roots"));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero(), 1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);

    game.Process(curPlayer, PlayCardTask::Spell(card2, 2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Sapling");
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->card->name, "Sapling");
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
}

// ------------------------------------------ SPELL - DRUID
// [CORE_CS2_009] Mark of the Wild - COST:2
// - Set: CORE, Rarity: Rare
// - Spell School: Nature
// --------------------------------------------------------
// Text: Give a minion <b>Taunt</b> and +2/+3.<i>
//       (+2 Attack/+3 Health)</i>
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - CORE_CS2_009 : Mark of the Wild")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mark of the Wild"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    auto& curField = *(curPlayer->GetFieldZone());

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAUNT), 0);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAUNT), 1);
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 4);
}

// ------------------------------------------ SPELL - DRUID
// [CORE_CS2_013] Wild Growth - COST:3
// - Faction: Neutral, Set: Basic, Rarity: Free
// - Spell School: Nature
// --------------------------------------------------------
// Text: Gain an empty Mana Crystal.
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - CORE_CS2_013 : Wild Growth")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
    curPlayer->SetTotalMana(9);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wild Growth"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wild Growth"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetRemainingMana(), 6);
    CHECK_EQ(curPlayer->GetTotalMana(), 10);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curPlayer->GetRemainingMana(), 3);
    CHECK_EQ(curPlayer->GetTotalMana(), 10);
}

// ------------------------------------------ SPELL - DRUID
// [CORE_EX1_154] Wrath - COST:2
// - Set: CORE, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: <b>Choose One -</b> Deal 3 damage to a minion;
//       or 1 damage and draw a card.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - CORE_EX1_154 : Wrath")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::DRUID;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wrath"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wrath"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->GetHealth(), 7);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3, 1));
    CHECK_EQ(opField[0]->GetHealth(), 4);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3, 2));
    CHECK_EQ(opField[0]->GetHealth(), 3);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
}

// ------------------------------------------ SPELL - DRUID
// [CORE_EX1_158] Soul of the Forest - COST:4
// - Set: CORE, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: Give your minions
//       "<b>Deathrattle:</b> Summon a 2/2 Treant."
// --------------------------------------------------------
// RefTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - CORE_EX1_158 : Soul of the Forest")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PRIEST;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card7 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Soul of the Forest"));
    const auto card8 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Hellfire"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, PlayCardTask::Minion(card6));

    game.Process(opPlayer, PlayCardTask::Spell(card7));
    CHECK_FALSE(opField[0]->appliedEnchantments.empty());
    CHECK_FALSE(opField[1]->appliedEnchantments.empty());
    CHECK_FALSE(opField[2]->appliedEnchantments.empty());

    game.Process(opPlayer, PlayCardTask::Spell(card8));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opField.GetCount(), 3);
    CHECK_EQ(opField[0]->card->name, "Treant");
    CHECK_EQ(opField[1]->card->name, "Treant");
    CHECK_EQ(opField[2]->card->name, "Treant");
}

// ------------------------------------------ SPELL - DRUID
// [CORE_EX1_160] Power of the Wild - COST:2
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Choose One -</b> Give your minions +1/+1;
//       or Summon a 3/2 Panther.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - CORE_EX1_160 : Power of the Wild")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::DRUID;
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
        curPlayer, Cards::FindCardByName("Power of the Wild"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Power of the Wild"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Power of the Wild"));

    game.Process(curPlayer, PlayCardTask::Spell(card1, 1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK(opField.IsEmpty());

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card2, 1));
    game.Process(opPlayer, PlayCardTask::Spell(card3, 2));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(opField[0]->GetAttack(), 4);
    CHECK_EQ(opField[0]->GetHealth(), 3);
}

// ------------------------------------------ SPELL - DRUID
// [CORE_EX1_164] Nourish - COST:5
// - Set: CORE, Rarity: Rare
// - Spell School: Nature
// --------------------------------------------------------
// Text: <b>Choose One -</b> Gain 2 Mana Crystals;
//       or Draw 3 cards.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - CORE_EX1_164 : Nourish")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::DRUID;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(6);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Nourish"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Nourish"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Nourish"));

    game.Process(curPlayer, PlayCardTask::Spell(card1, 1));
    CHECK_EQ(curPlayer->GetTotalMana(), 8);
    CHECK_EQ(curPlayer->GetRemainingMana(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card3, 1));
    CHECK_EQ(opPlayer->GetTotalMana(), 10);
    CHECK_EQ(opPlayer->GetRemainingMana(), 7);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card2, 2));
    CHECK_EQ(curHand.GetCount(), 8);
}

// ----------------------------------------- MINION - DRUID
// [CORE_EX1_165] Druid of the Claw - COST:5 [ATK:5/HP:4]
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Choose One -</b> Transform into a 5/4
//       with <b>Rush</b>; or a 5/6 with <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - CORE_EX1_165 : Druid of the Claw")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
        curPlayer, Cards::FindCardByName("Druid of the Claw"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Druid of the Claw"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Silence"));

    game.Process(curPlayer, PlayCardTask::Minion(card1, 1));
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK(curField[0]->CanAttack());
    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAUNT), 0);

    game.Process(curPlayer, PlayCardTask::Minion(card2, 2));
    CHECK_EQ(curField[1]->GetAttack(), 5);
    CHECK_EQ(curField[1]->GetHealth(), 6);
    CHECK_FALSE(curField[1]->CanAttack());
    CHECK_EQ(curField[1]->GetGameTag(GameTag::TAUNT), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, curField[1]));
    CHECK_EQ(curField[1]->GetAttack(), 5);
    CHECK_EQ(curField[1]->GetHealth(), 6);
    CHECK_FALSE(curField[1]->CanAttack());
    CHECK_EQ(curField[1]->GetGameTag(GameTag::TAUNT), 0);
}

// ------------------------------------------ SPELL - DRUID
// [CORE_EX1_169] Innervate - COST:0
// - Set: CORE, Rarity: Rare
// - Spell School: Nature
// --------------------------------------------------------
// Text: Gain 1 Mana Crystal this turn only.
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - CORE_EX1_169 : Innervate")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
    curPlayer->SetTotalMana(9);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Innervate"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Innervate"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Dragonling Mechanic"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetRemainingMana(), 10);
    CHECK_EQ(curPlayer->GetTemporaryMana(), 1);
    CHECK_EQ(curPlayer->GetTotalMana(), 9);
    CHECK_EQ(curPlayer->GetUsedMana(), 0);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curPlayer->GetRemainingMana(), 6);
    CHECK_EQ(curPlayer->GetTemporaryMana(), 0);
    CHECK_EQ(curPlayer->GetTotalMana(), 9);
    CHECK_EQ(curPlayer->GetUsedMana(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curPlayer->GetRemainingMana(), 10);
    CHECK_EQ(curPlayer->GetTemporaryMana(), 0);
    CHECK_EQ(curPlayer->GetTotalMana(), 10);
    CHECK_EQ(curPlayer->GetUsedMana(), 0);
}

// ------------------------------------------ SPELL - DRUID
// [CORE_EX1_571] Force of Nature - COST:5
// - Set: CORE, Rarity: Epic
// - Spell School: Nature
// --------------------------------------------------------
// Text: Summon three 2/2 Treants.
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - CORE_EX1_571 : Force of Nature")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Force of Nature"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Force of Nature"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(curField.GetCount(), 3);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 6);
    CHECK_EQ(curField[3]->card->name, "Treant");
    CHECK_EQ(curField[4]->card->name, "Treant");
    CHECK_EQ(curField[5]->card->name, "Treant");

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField.GetCount(), 7);
    CHECK_EQ(curField[6]->card->name, "Treant");
}

// ----------------------------------------- MINION - DRUID
// [CORE_EX1_573] Cenarius - COST:8 [ATK:5/HP:8]
// - Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Choose One -</b> Give your other minions +2/+2;
//       or Summon two 2/2 Treants with <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - CHOOSE_ONE = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - CORE_EX1_573 : Cenarius")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::DRUID;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cenarius"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cenarius"));

    game.Process(curPlayer, PlayCardTask::Minion(card1, 2));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[1]->GetAttack(), 5);
    CHECK_EQ(curField[1]->GetHealth(), 8);
    CHECK_EQ(curField[1]->HasTaunt(), false);
    CHECK_EQ(curField[2]->GetAttack(), 2);
    CHECK_EQ(curField[2]->GetHealth(), 2);
    CHECK_EQ(curField[2]->HasTaunt(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2, 1));
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[1]->GetAttack(), 7);
    CHECK_EQ(curField[1]->GetHealth(), 10);
    CHECK_EQ(curField[1]->HasTaunt(), false);
    CHECK_EQ(curField[2]->GetAttack(), 4);
    CHECK_EQ(curField[2]->GetHealth(), 4);
    CHECK_EQ(curField[2]->HasTaunt(), true);
    CHECK_EQ(curField[3]->GetAttack(), 5);
    CHECK_EQ(curField[3]->GetHealth(), 8);
    CHECK_EQ(curField[3]->HasTaunt(), false);
}

// ----------------------------------------- MINION - DRUID
// [CORE_LOE_050] Mounted Raptor - COST:3 [ATK:3/HP:2]
// - Race: Beast, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a random 1-Cost minion.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - CORE_LOE_050 : Mounted Raptor")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::SHAMAN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mounted Raptor"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->GetCost(), 1);
}

// ----------------------------------------- MINION - DRUID
// [CORE_NEW1_008] Ancient of Lore - COST:7 [ATK:5/HP:5]
// - Set: CORE, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Choose One -</b> Draw 2 cards;
//       or Restore 5 Health.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - CORE_NEW1_008 : Ancient of Lore")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::DRUID;
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
    curPlayer->GetHero()->SetDamage(15);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ancient of Lore"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ancient of Lore"));

    game.Process(curPlayer, PlayCardTask::Minion(card1, 1));
    CHECK_EQ(card1->GetZoneType(), ZoneType::PLAY);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card2, curPlayer->GetHero(), 2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
}

// ----------------------------------------- MINION - DRUID
// [CORE_OG_044] Fandral Staghelm - COST:4 [ATK:3/HP:5]
// - Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: Your <b>Choose One</b> cards and powers
//       have both effects combined.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - CORE_OG_044 : Fandral Staghelmh")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fandral Staghelm"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Living Roots"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Druid of the Claw"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);
    CHECK_EQ(curField.GetCount(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[3]->GetAttack(), 5);
    CHECK_EQ(curField[3]->GetHealth(), 6);
    CHECK_EQ(curField[3]->HasRush(), true);
    CHECK_EQ(curField[3]->HasTaunt(), true);
}

// ------------------------------------------ SPELL - DRUID
// [CORE_OG_047] Feral Rage - COST:3
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Choose One -</b> Give your hero +4 Attack this turn;
//       or Gain 8 Armor.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - CORE_OG_047 : Feral Rage")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::DRUID;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Feral Rage"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Feral Rage"));

    game.Process(curPlayer, PlayCardTask::Spell(card1, 1));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 4);

    game.Process(curPlayer, PlayCardTask::Spell(card2, 2));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 8);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
}

// ------------------------------------------ SPELL - DRUID
// [CORE_TRL_243] Pounce - COST:0
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Give your hero +2 Attack this turn.
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - CORE_TRL_243 : Pounce")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::DRUID;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pounce"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
}

// ------------------------------------------ SPELL - DRUID
// [CORE_UNG_108] Earthen Scales - COST:2
// - Set: CORE, Rarity: Rare
// - Spell School: Nature
// --------------------------------------------------------
// Text: Give a friendly minion +1/+1,
//       then gain Armor equal to its Attack.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_FRIENDLY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - CORE_UNG_108 : Earthen Scales")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::WARLOCK;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Earthen Scales"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 4);
}

// ----------------------------------------- SPELL - HUNTER
// [CORE_BRM_013] Quick Shot - COST:2
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Deal 3 damage. If your hand is empty, draw a card.
// --------------------------------------------------------
// GameTag:
// - AFFECTED_BY_SPELL_POWER = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - CORE_BRM_013 : Quick Shot")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Quick Shot"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Quick Shot"));

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 15);
}

// ----------------------------------------- SPELL - HUNTER
// [CORE_DAL_371] Marked Shot - COST:4
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Deal 4 damage to a minion. <b>Discover</b> a spell.
// --------------------------------------------------------
// GameTag:
// - DISCOVER = 1
// - USE_DISCOVER_VISUALS = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - CORE_DAL_371 : Marked Shot")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Marked Shot"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField[0]->GetHealth(), 8);
    CHECK(opPlayer->choice);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::SPELL);
        CHECK(card->IsCardClass(CardClass::PALADIN));
    }
}

// ----------------------------------------- SPELL - HUNTER
// [CORE_DS1_184] Tracking - COST:1
// - Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Discover</b> a card from your deck.
// --------------------------------------------------------
// GameTag:
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - CORE_DS1_184 : Tracking")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Tracking"));

    CHECK_EQ(curPlayer->GetDeckZone()->GetCount(), 5);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 3u);

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(curPlayer->GetDeckZone()->GetCount(), 4);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
}

// ----------------------------------------- SPELL - HUNTER
// [CORE_DS1_185] Arcane Shot - COST:1
// - Set: CORE, Rarity: Rare
// - Spell School: Arcane
// --------------------------------------------------------
// Text: Deal 2 damage.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - CORE_DS1_185 : Arcane Shot")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Shot"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Shot"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Shot"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Shot"));
    const auto card5 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));

    game.Process(curPlayer, PlayCardTask::Minion(card5));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card6));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card6));
    CHECK_EQ(opPlayer->GetFieldZone()->GetCount(), 0);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card5));
    CHECK_EQ(curPlayer->GetFieldZone()->GetCount(), 0);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 28);
}

// ---------------------------------------- MINION - HUNTER
// [CORE_EX1_534] Savannah Highmane - COST:6 [ATK:6/HP:5]
// - Race: Beast, Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon two 2/2 Hyenas.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - CORE_EX1_534 : Savannah Highmane")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Savannah Highmane"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Loot Hoarder"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 6);
    CHECK_EQ(curField[1]->GetHealth(), 5);

    curField[1]->SetDamage(4);
    CHECK_EQ(curField[1]->GetAttack(), 6);
    CHECK_EQ(curField[1]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[2]->GetAttack(), 2);
    CHECK_EQ(curField[2]->GetHealth(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, AttackTask(card4, card2));
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(curField[2]->GetAttack(), 2);
    CHECK_EQ(curField[2]->GetHealth(), 2);
    CHECK_EQ(curField[3]->GetAttack(), 2);
    CHECK_EQ(curField[3]->GetHealth(), 1);
}

// ---------------------------------------- MINION - HUNTER
// [CORE_EX1_543] King Krush - COST:9 [ATK:8/HP:8]
// - Race: Beast, Faction: Neutral, Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Charge</b>
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - CHARGE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - CORE_EX1_543 : King Krush")
{
    // Do nothing
}

// ----------------------------------------- SPELL - HUNTER
// [CORE_EX1_554] Snake Trap - COST:2
// - Faction: Neutral, Set: CORE, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Secret:</b> When one of your minions is attacked,
//       summon three 1/1 Snakes.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - CORE_EX1_554 : Snake Trap")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::HUNTER;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Snake Trap"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Snake Trap"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chillwind Yeti"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Chillwind Yeti"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, PlayCardTask::Minion(card6));
    game.Process(opPlayer, AttackTask(card6, card3));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[1]->card->GetRace(), Race::BEAST);
    CHECK_EQ(curField[2]->GetAttack(), 1);
    CHECK_EQ(curField[2]->GetHealth(), 1);
    CHECK_EQ(curField[2]->card->GetRace(), Race::BEAST);
    CHECK_EQ(curField[3]->GetAttack(), 1);
    CHECK_EQ(curField[3]->GetHealth(), 1);
    CHECK_EQ(curField[3]->card->GetRace(), Race::BEAST);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField.GetCount(), 5);

    game.Process(curPlayer, AttackTask(card4, card5));
    CHECK_EQ(curSecret->GetCount(), 1);
    CHECK_EQ(opField.GetCount(), 1);
}

// ----------------------------------------- SPELL - HUNTER
// [CORE_EX1_610] Explosive Trap - COST:2
// - Set: CORE, Rarity: Common
// - Spell School: Fire
// --------------------------------------------------------
// Text: <b>Secret:</b> When your hero is attacked,
//       deal 2 damage to all enemies.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - CORE_EX1_610 : Explosive Trap")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::HUNTER;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Explosive Trap"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chillwind Yeti"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Bloodmage Thalnos"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Chillwind Yeti"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField[0]->GetHealth(), 5);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(opField[1]->GetHealth(), 1);

    game.Process(opPlayer, AttackTask(card5, curPlayer->GetHero()));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 5);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 2);
}

// ----------------------------------------- SPELL - HUNTER
// [CORE_EX1_611] Freezing Trap - COST:2
// - Faction: Neutral, Set: CORE, Rarity: Common
// - Spell School: Frost
// --------------------------------------------------------
// Text: <b>Secret:</b> When an enemy minion attacks,
//       return it to its owner's hand. It costs (2) more.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - CORE_EX1_611 : Freezing Trap")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::HUNTER;
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
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Freezing Trap"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opHand.GetCount(), 6);

    game.Process(opPlayer, AttackTask(card2, curPlayer->GetHero()));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(opHand.GetCount(), 7);
    CHECK_EQ(opHand[6]->GetCost(), 5);
}

// ----------------------------------------- SPELL - HUNTER
// [CORE_EX1_617] Deadly Shot - COST:3
// - Faction: Neutral, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Destroy a random enemy minion.
// --------------------------------------------------------
// PlayReq:
// - REQ_MINIMUM_ENEMY_MINIONS = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - CORE_EX1_617 : Deadly Shot")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::HUNTER;
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
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Magma Rager"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Deadly Shot"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Deadly Shot"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Deadly Shot"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Magma Rager"));
    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Magma Rager"));
    const auto card7 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Magma Rager"));

    game.Process(curPlayer, PlayCardTask::Minion(card5));
    game.Process(curPlayer, PlayCardTask::Minion(card6));
    game.Process(curPlayer, PlayCardTask::Minion(card7));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card1));
    game.Process(opPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(opPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(curField.GetCount(), 0);
}

// ---------------------------------------- MINION - HUNTER
// [CORE_GIL_650] Houndmaster Shaw - COST:4 [ATK:3/HP:6]
// - Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: Your other minions have <b>Rush</b>.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - AURA = 1
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - CORE_GIL_650 : Houndmaster Shaw")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Houndmaster Shaw"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodfen Raptor"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bluegill Warrior"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasRush(), false);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->HasRush(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[1]->HasRush(), false);
}

// ----------------------------------------- SPELL - HUNTER
// [CORE_GIL_828] Dire Frenzy - COST:4
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Give a Beast +3/+3.
//       Shuffle 3 copies into your deck with +3/+3.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_WITH_RACE = 20
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - CORE_GIL_828 : Dire Frenzy")
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

    auto& curDeck = *(curPlayer->GetDeckZone());
    auto& curField = *(curPlayer->GetFieldZone());
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dire Frenzy"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodfen Raptor"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bluegill Warrior"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curDeck.GetCount(), 0);
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(curDeck.GetCount(), 0);
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curDeck.GetCount(), 3);
    CHECK_EQ(curHand.GetCount(), 0);
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->name, "Bloodfen Raptor");
    CHECK_EQ(dynamic_cast<Minion*>(curHand[0])->GetAttack(), 6);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[0])->GetHealth(), 5);
}

// ---------------------------------------- MINION - HUNTER
// [CORE_KAR_006] Cloaked Huntress - COST:3 [ATK:3/HP:4]
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Your <b>Secrets</b> cost (0).
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - CORE_KAR_006 : Cloaked Huntress")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cloaked Huntress"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Snake Trap"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Snipe"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    CHECK_EQ(card2->GetCost(), 2);
    CHECK_EQ(card3->GetCost(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card2->GetCost(), 0);
    CHECK_EQ(card3->GetCost(), 0);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curPlayer->GetRemainingMana(), 7);
    CHECK_EQ(card2->GetCost(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card1));
    CHECK_EQ(card2->GetCost(), 2);
}

// ---------------------------------------- WEAPON - HUNTER
// [CORE_LOOT_222] Candleshot - COST:1
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Your hero is <b>Immune</b> while attacking.
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 3
// --------------------------------------------------------
// RefTag:
// - IMMUNE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Weapon] - CORE_LOOT_222 : Candleshot")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::SHAMAN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Candleshot"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetWeapon().GetAttack(), 1);
    CHECK_EQ(curPlayer->GetWeapon().GetDurability(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(curPlayer->GetHero(), card2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(curPlayer->GetHero()->IsImmune(), false);
}

// ----------------------------------------- SPELL - HUNTER
// [CORE_NEW1_031] Animal Companion - COST:3
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Summon a random Beast Companion.
// --------------------------------------------------------
// Entourage: NEW1_032, NEW1_033, NEW1_034
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - CORE_NEW1_031 : Animal Companion")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Animal Companion"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 2);

    const bool isMisha = curField[1]->card->id == "NEW1_032";
    const bool isLeokk = curField[1]->card->id == "NEW1_033";
    const bool isHuffer = curField[1]->card->id == "NEW1_034";
    const bool isAnimal = isMisha || isLeokk || isHuffer;
    CHECK(isAnimal);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, curField[1]));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    SUBCASE("Misha - NEW1_032")
    {
        const auto card =
            Generic::DrawCard(curPlayer, Cards::FindCardByID("NEW1_032"));

        game.Process(curPlayer, PlayCardTask::Minion(card));
        CHECK_EQ(curField.GetCount(), 2);
        CHECK_EQ(curField[1]->GetAttack(), 4);
        CHECK_EQ(curField[1]->GetHealth(), 4);
        CHECK_EQ(curField[1]->HasTaunt(), true);
    }

    SUBCASE("Leokk - NEW1_033")
    {
        const auto card =
            Generic::DrawCard(curPlayer, Cards::FindCardByID("NEW1_033"));

        game.Process(curPlayer, PlayCardTask::Minion(card));
        CHECK_EQ(curField.GetCount(), 2);
        CHECK_EQ(curField[1]->GetAttack(), 2);
        CHECK_EQ(curField[1]->GetHealth(), 4);
        CHECK_EQ(curField[0]->GetAttack(), 4);
    }

    SUBCASE("Huffer - NEW1_034")
    {
        const auto card =
            Generic::DrawCard(curPlayer, Cards::FindCardByID("NEW1_034"));

        game.Process(curPlayer, PlayCardTask::Minion(card));
        CHECK_EQ(curField.GetCount(), 2);
        CHECK_EQ(curField[1]->GetAttack(), 4);
        CHECK_EQ(curField[1]->GetHealth(), 2);
        CHECK_EQ(curField[1]->HasCharge(), true);
    }
}

// ---------------------------------------- MINION - HUNTER
// [CORE_TRL_348] Springpaw - COST:1 [ATK:1/HP:1]
// - Race: Beast, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Rush</b> <b>Battlecry:</b> Add a 1/1 Lynx
//       with <b>Rush</b> to your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - CORE_TRL_348 : Springpaw")
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Springpaw"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasRush(), true);
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->name, "Lynx");

    game.Process(curPlayer, PlayCardTask::Minion(curHand[0]));
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[1]->HasRush(), true);
}

// ---------------------------------------- MINION - HUNTER
// [CS3_015] Selective Breeder - COST:2 [ATK:1/HP:3]
// - Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> <b>Discover</b> a copy of a Beast
//       in your deck.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - CS3_015 : Selective Breeder")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Bloodfen Raptor");
        config.player1Deck[i + 1] = Cards::FindCardByName("Young Dragonhawk");
        config.player1Deck[i + 2] = Cards::FindCardByName("Faerie Dragon");
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Selective Breeder", FormatType::STANDARD));

    CHECK_EQ(curDeck.GetCount(), 26);
    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 2u);

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(curDeck.GetCount(), 26);
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->GetRace(), Race::BEAST);
}

// ------------------------------------------- SPELL - MAGE
// [CORE_BOT_453] Shooting Star - COST:1
// - Set: CORE, Rarity: Common
// - Spell School: Arcane
// --------------------------------------------------------
// Text: Deal 1 damage to a minion and the minions next to it.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - CORE_BOT_453 : Shooting Star")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shooting Star"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField.GetCount(), 3);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 11);
}

// ------------------------------------------- SPELL - MAGE
// [CORE_CS2_023] Arcane Intellect - COST:3
// - Set: CORE, Rarity: Common
// - Spell School: Arcane
// --------------------------------------------------------
// Text: Draw 2 cards.
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - CORE_CS2_023 : Arcane Intellect")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Intellect"));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
}

// ------------------------------------------- SPELL - MAGE
// [CORE_CS2_028] Blizzard - COST:6
// - Set: CORE, Rarity: Rare
// - Spell School: Frost
// --------------------------------------------------------
// Text: Deal 2 damage to all enemy minions
//       and <b>Freeze</b> them.
// --------------------------------------------------------
// GameTag:
// - FREEZE = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - CORE_CS2_028 : Blizzard")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Blizzard"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 5);
    CHECK_EQ(opField[0]->IsFrozen(), true);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(opPlayer->GetHero()->IsFrozen(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, AttackTask(card2, curPlayer->GetHero()));
    CHECK_EQ(opField[0]->IsFrozen(), true);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opField[0]->IsFrozen(), false);
}

// ------------------------------------------- SPELL - MAGE
// [CORE_CS2_029] Fireball - COST:4
// - Set: CORE, Rarity: Common
// - Spell School: Fire
// --------------------------------------------------------
// Text: Deal 6 damage.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - CORE_CS2_029 : Fireball")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card5 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));

    game.Process(curPlayer, PlayCardTask::Minion(card5));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card6));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card6));
    CHECK_EQ(opPlayer->GetFieldZone()->GetCount(), 0);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 24);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card5));
    CHECK_EQ(curPlayer->GetFieldZone()->GetCount(), 0);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 24);
}

// ------------------------------------------- SPELL - MAGE
// [CORE_CS2_032] Flamestrike - COST:7
// - Set: CORE, Rarity: Epic
// - Spell School: Fire
// --------------------------------------------------------
// Text: Deal 5 damage to all enemy minions.
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - CORE_CS2_032 : Flamestrike")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flamestrike"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 2);
}

// ------------------------------------------ MINION - MAGE
// [CORE_DAL_609] Kalecgos - COST:9 [ATK:4/HP:12]
// - Race: Dragon, Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: Your first spell each turn costs (0).
//       <b>Battlecry:</b> <b>Discover</b> a spell.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - AURA = 1
// - BATTLECRY = 1
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - CORE_DAL_609 : Kalecgos")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Kalecgos"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::SPELL);
        CHECK(card->IsCardClass(CardClass::MAGE));
    }

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(curHand.GetCount(), 7);
    CHECK_EQ(card2->GetCost(), 0);
    CHECK_EQ(card3->GetCost(), 0);
    CHECK_EQ(curHand[6]->GetCost(), 0);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(card3->GetCost(), 4);
}

// ------------------------------------------- SPELL - MAGE
// [CORE_EX1_275] Cone of Cold - COST:3
// - Set: CORE, Rarity: Common
// - Spell School: Frost
// --------------------------------------------------------
// Text: <b>Freeze</b> a minion and the minions next to it,
//       and deal 1 damage to them.
// --------------------------------------------------------
// GameTag:
// - FREEZE = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - CORE_EX1_275 : Cone of Cold")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Imp"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Imp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Imp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Imp"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Imp"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Cone of Cold"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[0]->IsFrozen(), false);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(curField[1]->IsFrozen(), false);
    CHECK_EQ(curField[2]->GetHealth(), 2);
    CHECK_EQ(curField[2]->IsFrozen(), false);
    CHECK_EQ(curField[3]->GetHealth(), 2);
    CHECK_EQ(curField[3]->IsFrozen(), false);
    CHECK_EQ(curField[4]->GetHealth(), 2);
    CHECK_EQ(curField[4]->IsFrozen(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card6, card3));
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[0]->IsFrozen(), false);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[1]->IsFrozen(), true);
    CHECK_EQ(curField[2]->GetHealth(), 1);
    CHECK_EQ(curField[2]->IsFrozen(), true);
    CHECK_EQ(curField[3]->GetHealth(), 1);
    CHECK_EQ(curField[3]->IsFrozen(), true);
    CHECK_EQ(curField[4]->GetHealth(), 2);
    CHECK_EQ(curField[4]->IsFrozen(), false);
}

// ------------------------------------------- SPELL - MAGE
// [CORE_EX1_279] Pyroblast - COST:10
// - Set: CORE, Rarity: Epic
// - Spell School: Fire
// --------------------------------------------------------
// Text: Deal 10 damage.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - CORE_EX1_279 : Pyroblast")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pyroblast"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pyroblast"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pyroblast"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pyroblast"));
    const auto card5 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));

    game.Process(curPlayer, PlayCardTask::Minion(card5));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card6));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card6));
    CHECK_EQ(opPlayer->GetFieldZone()->GetCount(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 20);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card5));
    CHECK_EQ(curPlayer->GetFieldZone()->GetCount(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
}

// ------------------------------------------- SPELL - MAGE
// [CORE_EX1_287] Counterspell - COST:3
// - Set: CORE, Rarity: Rare
// - Spell School: Arcane
// --------------------------------------------------------
// Text: <b>Secret:</b> When your opponent casts a spell,
//       <b>Counter</b> it.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
// RefTag:
// - COUNTER = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - CORE_EX1_287 : Counterspell")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::SHAMAN;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Counterspell"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Lightning Bolt"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Lightning Bolt"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(curSecret->GetCount(), 1);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 24);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card3, curPlayer->GetHero()));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(opPlayer->GetRemainingMana(), 9);
    CHECK_EQ(opPlayer->GetOverloadOwed(), 0);

    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card4, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 27);
}

// ------------------------------------------- SPELL - MAGE
// [CORE_EX1_289] Ice Barrier - COST:3
// - Set: CORE, Rarity: Common
// - Spell School: Frost
// --------------------------------------------------------
// Text: <b>Secret:</b> When your hero is attacked,
//       gain 8 Armor.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - CORE_EX1_289 : Ice Barrier")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    auto curSecret = curPlayer->GetSecretZone();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ice Barrier"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fiery War Axe"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Weapon(card2));
    game.Process(opPlayer,
                 AttackTask(opPlayer->GetHero(), curPlayer->GetHero()));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 5);
}

// ------------------------------------------- SPELL - MAGE
// [CORE_GIL_801] Snap Freeze - COST:1
// - Set: CORE, Rarity: Common
// - Spell School: Frost
// --------------------------------------------------------
// Text: <b>Freeze</b> a minion.
//       If it's already <b>Frozen</b>, destroy it.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - FREEZE = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - CORE_GIL_801 : Snap Freeze")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::DRUID;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Snap Freeze"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Snap Freeze"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->IsFrozen(), false);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(opField[0]->IsFrozen(), true);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3));
    CHECK_EQ(opField.GetCount(), 0);
}

// ------------------------------------------ MINION - MAGE
// [CORE_KAR_009] Babbling Book - COST:1 [ATK:1/HP:1]
// - Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Add a random Mage spell to your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - CORE_KAR_009 : Babbling Book")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::MAGE;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Babbling Book"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->GetCardType(), CardType::SPELL);
    CHECK(curHand[0]->card->IsCardClass(CardClass::MAGE));
}

// ------------------------------------------ MINION - MAGE
// [CORE_LOE_003] Ethereal Conjurer - COST:5 [ATK:6/HP:4]
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry: Discover</b> a spell.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - CORE_LOE_003 : Ethereal Conjurer")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::MAGE;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Ethereal Conjurer"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 3);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::SPELL);
        CHECK_EQ(card->IsCardClass(CardClass::MAGE), true);
    }

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(curHand.GetCount(), 1);
}

// ------------------------------------------- SPELL - MAGE
// [CORE_LOOT_101] Explosive Runes - COST:3
// - Set: CORE, Rarity: Rare
// - Spell School: Fire
// --------------------------------------------------------
// Text: <b>Secret:</b> After your opponent plays a minion,
//       deal 6 damage to it and any excess to their hero.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// - ImmuneToSpellpower = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - CORE_LOOT_101 : Explosive Runes")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::HUNTER;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Explosive Runes"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Explosive Runes"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chillwind Yeti"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Bloodmage Thalnos"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Chillwind Yeti"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Chillwind Yeti"));
    const auto card7 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Chillwind Yeti"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curSecret->GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(opField.GetCount(), 0);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 29);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card6));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(opField.GetCount(), 0);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);

    game.Process(opPlayer, PlayCardTask::Minion(card7));
    CHECK_EQ(opField[0]->GetHealth(), 5);
}

// ------------------------------------------ MINION - MAGE
// [CORE_TRL_315] Pyromaniac - COST:3 [ATK:3/HP:4]
// - Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever your Hero Power kills a minion, draw a card.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - CORE_TRL_315 : Pyromaniac")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    auto& curHand = *(curPlayer->GetHandZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pyromaniac"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Goldshire Footman"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField[0]->GetHealth(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask(card2));
    CHECK_EQ(opField[0]->GetHealth(), 1);
    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask(card2));
    CHECK_EQ(opField.GetCount(), 0);
    CHECK_EQ(curHand.GetCount(), 7);
}

// ------------------------------------------ MINION - MAGE
// [CORE_UNG_020] Arcanologist - COST:2 [ATK:2/HP:3]
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Draw a <b>Secret</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - CORE_UNG_020 : Arcanologist")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Bloodfen Raptor");
        config.player1Deck[i + 1] = Cards::FindCardByName("Young Dragonhawk");
        config.player1Deck[i + 2] = Cards::FindCardByName("Ice Barrier");
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcanologist"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->IsSecret(), true);
}

// --------------------------------------- MINION - PALADIN
// [CORE_AT_075] Warhorse Trainer - COST:3 [ATK:3/HP:4]
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Your Silver Hand Recruits have +2 Attack and <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - CORE_AT_075 : Warhorse Trainer")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PALADIN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Warhorse Trainer"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetAttack(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->HasTaunt(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->HasTaunt(), false);
}

// ---------------------------------------- SPELL - PALADIN
// [CORE_CS2_092] Blessing of Kings - COST:4
// - Set: CORE, Rarity: Common
// - Spell School: Holy
// --------------------------------------------------------
// Text: Give a minion +4/+4. <i>(+4 Attack/+4 Health)</i>
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - CORE_CS2_092 : Blessing of Kings")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Blessing of Kings"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField[0]->GetAttack(), 7);
    CHECK_EQ(curField[0]->GetHealth(), 5);
}

// ---------------------------------------- SPELL - PALADIN
// [CORE_CS2_093] Consecration - COST:4
// - Set: CORE, Rarity: Common
// - Spell School: Holy
// --------------------------------------------------------
// Text: Deal 2 damage to all enemies.
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - CORE_CS2_093 : Consecration")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::SHAMAN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Consecration"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 5);
}

// --------------------------------------- WEAPON - PALADIN
// [CORE_CS2_097] Truesilver Champion - COST:4 [ATK:4/HP:0]
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Whenever your hero attacks, restore 2 Health to it.
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 2
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Weapon] - CORE_CS2_097 : Truesilver Champion")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PALADIN;
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
    curPlayer->GetHero()->SetDamage(4);

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Truesilver Champion"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 26);
    CHECK_EQ(curPlayer->GetWeapon().GetAttack(), 4);
    CHECK_EQ(curPlayer->GetWeapon().GetDurability(), 2);

    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 28);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 26);
    CHECK_EQ(curPlayer->GetWeapon().GetDurability(), 1);
}

// --------------------------------------- MINION - PALADIN
// [CORE_DRG_226] Amber Watcher - COST:5 [ATK:4/HP:6]
// - Race: Dragon, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Restore 8 Health.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - CORE_DRG_226 : Amber Watcher")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
    curPlayer->GetHero()->SetDamage(10);

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Amber Watcher"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Amber Watcher"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    opField[0]->SetDamage(6);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card1, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 28);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card3));
    CHECK_EQ(opField[0]->GetHealth(), 12);
}

// --------------------------------------- MINION - PALADIN
// [CORE_DRG_229] Bronze Explorer - COST:3 [ATK:3/HP:3]
// - Race: Dragon, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Lifesteal</b>
//       <b>Battlecry:</b> <b>Discover</b> a Dragon.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - DISCOVER = 1
// - LIFESTEAL = 1
// - USE_DISCOVER_VISUALS = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - CORE_DRG_229 : Bronze Explorer")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bronze Explorer"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 3);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::MINION);
        CHECK_EQ(card->GetRace(), Race::DRAGON);
    }
}

// ---------------------------------------- SPELL - PALADIN
// [CORE_EX1_130] Noble Sacrifice - COST:1
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Secret:</b> When an enemy attacks,
//       summon a 2/1 Defender as the new target.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - CORE_EX1_130 : Noble Sacrifice")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    auto curHero = curPlayer->GetHero();
    auto opHero = opPlayer->GetHero();
    auto curSecret = curPlayer->GetSecretZone();
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Noble Sacrifice"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Noble Sacrifice"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fiery War Axe"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Grommash Hellscream"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Weapon(card3));
    game.Process(opPlayer, AttackTask(opHero, curHero));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(curHero->GetHealth(), 30);
    CHECK_EQ(opHero->GetHealth(), 28);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField[0]->GetAttack(), 4);
    CHECK_EQ(opField[0]->GetHealth(), 9);

    game.Process(opPlayer, AttackTask(card4, curHero));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(curHero->GetHealth(), 30);
    CHECK_EQ(opField[0]->GetAttack(), 10);
    CHECK_EQ(opField[0]->GetHealth(), 7);
}

// --------------------------------------- MINION - PALADIN
// [CORE_EX1_362] Argent Protector - COST:2 [ATK:3/HP:2]
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give a friendly minion
//       <b>Divine Shield</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_MINION_TARGET = 0
// - REQ_FRIENDLY_TARGET = 0
// - REQ_NONSELF_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - CORE_EX1_362 : Argent Protector")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PALADIN;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Magma Rager"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Argent Protector"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card1));
    CHECK_EQ(curField[0]->HasDivineShield(), true);
}

// --------------------------------------- MINION - PALADIN
// [CORE_EX1_382] Aldor Peacekeeper - COST:3 [ATK:3/HP:3]
// - Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Change an enemy minion's Attack to 1.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_ENEMY_TARGET = 0
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - CORE_EX1_382 : Aldor Peacekeeper")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Magma Rager"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Aldor Peacekeeper"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::MinionTarget(card2, card1));
    CHECK_EQ(curField[0]->GetAttack(), 1);
}

// --------------------------------------- MINION - PALADIN
// [CORE_EX1_383] Tirion Fordring - COST:8 [ATK:6/HP:6]
// - Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b><b>Divine Shield</b>,</b> <b>Taunt</b>
//       <b>Deathrattle:</b> Equip a 5/3 Ashbringer.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - DIVINE_SHIELD = 1
// - TAUNT = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - CORE_EX1_383 : Tirion Fordring")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PALADIN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Tirion Fordring"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), false);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 6);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField.GetCount(), 3);

    game.Process(opPlayer, AttackTask(card2, card1));
    CHECK_EQ(curField[0]->GetHealth(), 6);

    game.Process(opPlayer, AttackTask(card3, card1));
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(opPlayer, AttackTask(card4, card1));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), true);
    CHECK_EQ(curPlayer->GetWeapon().GetAttack(), 5);
    CHECK_EQ(curPlayer->GetWeapon().GetDurability(), 3);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 25);
    CHECK_EQ(curPlayer->GetWeapon().GetDurability(), 2);
}

// ---------------------------------------- SPELL - PALADIN
// [CORE_EX1_619] Equality - COST:2
// - Set: CORE, Rarity: Rare
// - Spell School: Holy
// --------------------------------------------------------
// Text: Change the Health of all minions to 1.
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - CORE_EX1_619 : Equality")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PALADIN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Tirion Fordring"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Tirion Fordring"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Equality"));

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 1);
}

// ---------------------------------------- SPELL - PALADIN
// [CORE_FP1_020] Avenge - COST:1
// - Set: CORE, Rarity: Common
// - Spell School: Holy
// --------------------------------------------------------
// Text: <b>Secret:</b> When one of your minions dies,
//       give a random friendly minion +3/+2.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - CORE_FP1_020 : Avenge")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curSecret = *(curPlayer->GetSecretZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Avenge"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curSecret.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card2));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(curSecret.GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card4));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(curSecret.GetCount(), 0);
}

// --------------------------------------- MINION - PALADIN
// [CORE_ICC_038] Righteous Protector - COST:1 [ATK:1/HP:1]
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Divine Shield</b>
// --------------------------------------------------------
// GameTag:
// - DIVINE_SHIELD = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - CORE_ICC_038 : Righteous Protector")
{
    // Do nothing
}

// --------------------------------------- MINION - PALADIN
// [CORE_OG_229] Ragnaros, Lightlord - COST:8 [ATK:8/HP:8]
// - Race: Elemental, Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: At the end of your turn,
//       restore 8 Health to a damaged friendly character.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - CORE_OG_229 : Ragnaros, Lightlord")
{
    GameConfig config;

    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PALADIN;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Ragnaros, Lightlord"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Pyroblast"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Pyroblast"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    int totalHealth =
        curPlayer->GetHero()->GetHealth() + curField[0]->GetHealth();
    CHECK_EQ(totalHealth, 42);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card2));
    totalHealth = curPlayer->GetHero()->GetHealth() + curField[0]->GetHealth();
    CHECK_EQ(totalHealth, 32);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    totalHealth = curPlayer->GetHero()->GetHealth() + curField[0]->GetHealth();
    CHECK_EQ(totalHealth, 40);

    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card4, curPlayer->GetHero()));
    totalHealth = curPlayer->GetHero()->GetHealth() + curField[0]->GetHealth();
    CHECK_EQ(totalHealth, 30);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    totalHealth = curPlayer->GetHero()->GetHealth() + curField[0]->GetHealth();
    const bool checkHealth = totalHealth == 32 || totalHealth == 38;
    CHECK(checkHealth);
}

// ---------------------------------------- SPELL - PALADIN
// [CORE_OG_273] Stand Against Darkness - COST:4
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Summon five 1/1 Silver Hand Recruits.
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - CORE_OG_273 : Stand Against Darkness")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PALADIN;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Stand Against Darkness"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Stand Against Darkness"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 5);
    CHECK_EQ(curField[0]->card->name, "Silver Hand Recruit");
    CHECK_EQ(curField[1]->card->name, "Silver Hand Recruit");
    CHECK_EQ(curField[2]->card->name, "Silver Hand Recruit");
    CHECK_EQ(curField[3]->card->name, "Silver Hand Recruit");
    CHECK_EQ(curField[4]->card->name, "Silver Hand Recruit");

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField.GetCount(), 7);
    CHECK_EQ(curField[5]->card->name, "Silver Hand Recruit");
    CHECK_EQ(curField[6]->card->name, "Silver Hand Recruit");
}

// ---------------------------------------- SPELL - PALADIN
// [CORE_TRL_307] Flash of Light - COST:2
// - Set: CORE, Rarity: Common
// - Spell School: Holy
// --------------------------------------------------------
// Text: Restore 4 Health. Draw a card.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - CORE_TRL_307 : Flash of Light")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flash of Light"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card2, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 24);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 6);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 28);
    CHECK_EQ(curHand.GetCount(), 6);
}

// ---------------------------------------- SPELL - PALADIN
// [CS3_016] Reckoning - COST:1
// - Set: CORE, Rarity: Epic
// - Spell School: Holy
// --------------------------------------------------------
// Text: <b>Secret:</b> After an enemy minion deals 3 or
//       more damage, destroy it.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - CS3_016 : Reckoning")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
        curPlayer, Cards::FindCardByName("Reckoning", FormatType::STANDARD));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, AttackTask(card2, curPlayer->GetHero()));
    CHECK_EQ(curSecret->GetCount(), 1);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 29);
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, AttackTask(card3, curPlayer->GetHero()));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 26);
    CHECK_EQ(opField.GetCount(), 1);
}

// ----------------------------------------- SPELL - PRIEST
// [CORE_AT_055] Flash Heal - COST:1
// - Set: CORE, Rarity: Common
// - Spell School: Holy
// --------------------------------------------------------
// Text: Restore 5 Health.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - CORE_AT_055 : Flash Heal")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    auto curHero = curPlayer->GetHero();
    auto opHero = opPlayer->GetHero();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flash Heal"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flash Heal"));

    CHECK_EQ(curHero->GetHealth(), 20);
    CHECK_EQ(opHero->GetHealth(), 20);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, curHero));
    CHECK_EQ(curHero->GetHealth(), 25);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, opHero));
    CHECK_EQ(opHero->GetHealth(), 25);
}

// ---------------------------------------- MINION - PRIEST
// [CORE_CFM_605] Drakonid Operative - COST:5 [ATK:5/HP:6]
// - Race: Dragon, Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you're holding a Dragon,
//       <b>Discover</b> a copy of a card
//       in your opponent's deck.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - CORE_CFM_605 : Drakonid Operative")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.doShuffle = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player2Deck[i] = Cards::FindCardByName("Wisp");
        config.player2Deck[i + 1] = Cards::FindCardByName("Fireball");
        config.player2Deck[i + 2] = Cards::FindCardByName("Blizzard");
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
    auto& opDeck = *(opPlayer->GetDeckZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Drakonid Operative"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Drakonid Operative"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 3);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        const bool checkName = card->name == "Wisp" ||
                               card->name == "Fireball" ||
                               card->name == "Blizzard";
        CHECK(checkName);
    }

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(curHand.GetCount(), 3);
    CHECK_EQ(opDeck.GetCount(), 26);

    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::Minion(card3));

    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK(!curPlayer->choice);
}

// ----------------------------------------- SPELL - PRIEST
// [CORE_CS1_112] Holy Nova - COST:4
// - Set: CORE, Rarity: Common
// - Spell School: Holy
// --------------------------------------------------------
// Text: Deal 2 damage to all enemy minions.
//       Restore 2 Health to all friendly characters.
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - CORE_CS1_112 : Holy Nova")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
    curPlayer->GetHero()->SetDamage(4);
    opPlayer->GetHero()->SetDamage(4);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Windfury Harpy"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Holy Nova"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Argent Squire"));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Worgen Infiltrator"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(card1, card4));
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(opField[0]->GetGameTag(GameTag::DIVINE_SHIELD), 0);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 28);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 26);
    CHECK_EQ(curField[0]->GetHealth(), 5);
    CHECK_EQ(curField[1]->GetHealth(), 7);
    CHECK_EQ(opField.GetCount(), 0);
}

// ----------------------------------------- SPELL - PRIEST
// [CORE_CS1_130] Holy Smite - COST:1
// - Set: CORE, Rarity: Common
// - Spell School: Holy
// --------------------------------------------------------
// Text: Deal 3 damage to a minion.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - CORE_CS1_130 : Holy Smite")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Holy Smite"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Holy Smite"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Holy Smite"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Holy Smite"));
    const auto card5 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));

    game.Process(curPlayer, PlayCardTask::Minion(card5));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card6));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card6));
    CHECK_EQ(opField[0]->GetHealth(), 4);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card5));
    CHECK_EQ(curField.GetCount(), 0);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
}

// ---------------------------------------- MINION - PRIEST
// [CORE_CS2_235] Northshire Cleric - COST:1 [ATK:1/HP:3]
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Whenever a minion is healed, draw a card.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - CORE_CS2_235 : Northshire Cleric")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
    curPlayer->GetHero()->SetDamage(6);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Northshire Cleric"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Voodoo Doctor"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Voodoo Doctor"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card2, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 26);

    curField[0]->SetDamage(2);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card3, card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 3);
}

// ---------------------------------------- MINION - PRIEST
// [CORE_DRG_090] Murozond the Infinite - COST:8 [ATK:8/HP:8]
// - Race: Dragon, Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Play all cards
//       your opponent played last turn.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - CORE_DRG_090 : Murozond the Infinite")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARRIOR;
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

    auto& opHand = *(opPlayer->GetHandZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fiery War Axe"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shield Block"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Murozond the Infinite"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Spell(card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opPlayer->GetHero()->HasWeapon(), true);
    CHECK_EQ(opPlayer->GetHero()->weapon->card->name, "Fiery War Axe");
    CHECK_EQ(opField.GetCount(), 2);
    CHECK_EQ(opField[1]->card->name, "Wolfrider");
    CHECK_EQ(opHand.GetCount(), 7);
    CHECK_EQ(opPlayer->GetHero()->GetArmor(), 5);
}

// ---------------------------------------- MINION - PRIEST
// [CORE_EX1_193] Psychic Conjurer - COST:1 [ATK:1/HP:1]
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Copy a card in your opponent's deck
//       and add it to your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - CORE_EX1_193 : Psychic Conjurer")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.skipMulligan = true;
    config.doShuffle = false;

    for (int i = 0; i < 5; ++i)
    {
        config.player2Deck[i] = Cards::FindCardByName("Magma Rager");
    }
    config.player2Deck[5] = Cards::FindCardByName("Wolfrider");

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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Psychic Conjurer"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ((curHand[0]->card->name == "Magma Rager" ||
              curHand[0]->card->name == "Wolfrider"),
             true);
}

// ----------------------------------------- SPELL - PRIEST
// [CORE_EX1_194] Power Infusion - COST:4
// - Set: CORE, Rarity: Common
// - Spell School: Holy
// --------------------------------------------------------
// Text: Give a minion +2/+6.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - CORE_EX1_194 : Power Infusion")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Power Infusion"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 7);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField[0]->GetAttack(), 8);
    CHECK_EQ(curField[0]->GetHealth(), 13);
}

// ---------------------------------------- MINION - PRIEST
// [CORE_EX1_195] Kul Tiran Chaplain - COST:2 [ATK:2/HP:3]
// - Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give a friendly minion +2 Health.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_FRIENDLY_TARGET = 0
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - CORE_EX1_195 : Kul Tiran Chaplain")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
        curPlayer, Cards::FindCardByName("Kul Tiran Chaplain"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 3);
}

// ----------------------------------------- SPELL - PRIEST
// [CORE_EX1_197] Shadow Word: Ruin - COST:4
// - Set: CORE, Rarity: Epic
// - Spell School: Shadow
// --------------------------------------------------------
// Text: Destroy all minions with 5 or more Attack.
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - CORE_EX1_197 : Shadow Word: Ruin")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Shadow Word: Ruin"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Leeroy Jenkins"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Leeroy Jenkins"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(opField.GetCount(), 2);
    CHECK_EQ(opField[0]->GetAttack(), 1);
    CHECK_EQ(opField[1]->GetAttack(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[2]->GetAttack(), 1);
    CHECK_EQ(opField.GetCount(), 3);
    CHECK_EQ(opField[0]->GetAttack(), 1);
    CHECK_EQ(opField[1]->GetAttack(), 1);
    CHECK_EQ(opField[2]->GetAttack(), 6);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(opField.GetCount(), 2);
    CHECK_EQ(opField[0]->GetAttack(), 1);
    CHECK_EQ(opField[1]->GetAttack(), 1);
}

// ----------------------------------------- SPELL - PRIEST
// [CORE_EX1_622] Shadow Word: Death - COST:2
// - Set: CORE, Rarity: Common
// - Spell School: Shadow
// --------------------------------------------------------
// Text: Destroy a minion with 5 or more Attack.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_MIN_ATTACK = 5
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - CORE_EX1_622 : Shadow Word: Death")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
        curPlayer, Cards::FindCardByName("Shadow Word: Death"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(curPlayer->GetRemainingMana(), 10);
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
    CHECK_EQ(curPlayer->GetRemainingMana(), 8);
    CHECK_EQ(opField.GetCount(), 1);
}

// ----------------------------------------- SPELL - PRIEST
// [CORE_GVG_008] Lightbomb - COST:6
// - Set: CORE, Rarity: Epic
// - Spell School: Holy
// --------------------------------------------------------
// Text: Deal damage to each minion equal to its Attack.
// --------------------------------------------------------
// GameTag:
// - AFFECTED_BY_SPELL_POWER = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - CORE_GVG_008 : Lightbomb")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lightbomb"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Righteous Protector"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Sen'jin Shieldmasta"));

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
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->HasDivineShield(), false);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 3);
    CHECK_EQ(opField.GetCount(), 0);
}

// ---------------------------------------- MINION - PRIEST
// [CORE_UNG_034] Radiant Elemental - COST:2 [ATK:2/HP:3]
// - Race: Elemental, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Your spells cost (1) less.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - CORE_UNG_034 : Radiant Elemental")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Radiant Elemental"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Radiant Elemental"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Power Infusion"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Silence"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card3->GetCost(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(card3->GetCost(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card1));
    CHECK_EQ(card3->GetCost(), 3);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card2));
    CHECK_EQ(curPlayer->GetRemainingMana(), 7);
}

// ---------------------------------------- MINION - PRIEST
// [CORE_UNG_963] Lyra the Sunshard - COST:5 [ATK:3/HP:5]
// - Race: Elemental, Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: Whenever you cast a spell,
//       add a random Priest spell to your hand.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - CORE_UNG_963 : Lyra the Sunshard")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::WARLOCK;
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
        curPlayer, Cards::FindCardByName("Lyra the Sunshard"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flash Heal"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->GetCardClass(), CardClass::PRIEST);
    CHECK_EQ(curHand[0]->card->GetCardType(), CardType::SPELL);
}

// ---------------------------------------- MINION - PRIEST
// [CS3_013] Shadowed Spirit - COST:3 [ATK:4/HP:3]
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Deal 3 damage to the enemy hero.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - CS3_013 : Shadowed Spirit")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    Hero* opHero = opPlayer->GetHero();
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Shadowed Spirit", FormatType::STANDARD));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(opHero->GetHealth(), 30);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opHero->GetHealth(), 27);
}

// ----------------------------------------- SPELL - PRIEST
// [CS3_027] Focused Will - COST:1
// - Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Silence</b> a minion, then give it +3 Health.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - SILENCE = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - CS3_027 : Focused Will")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
        curPlayer, Cards::FindCardByName("Focused Will", FormatType::STANDARD));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Bloodmage Thalnos"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[0]->GetSpellPower(), 1);
    CHECK_EQ(curField[0]->HasDeathrattle(), true);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[0]->GetSpellPower(), 0);
    CHECK_EQ(curField[0]->HasDeathrattle(), false);
}

// ----------------------------------------- SPELL - PRIEST
// [CS3_028] Thrive in the Shadows - COST:2
// - Set: CORE, Rarity: Rare
// - Spell School: Shadow
// --------------------------------------------------------
// Text: <b>Discover</b> a spell from your deck.
// --------------------------------------------------------
// GameTag:
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - CS3_028 : Thrive in the Shadows")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Bloodfen Raptor");
        config.player1Deck[i + 1] = Cards::FindCardByName("Fireball");
        config.player1Deck[i + 2] = Cards::FindCardByName("Pyroblast");
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
        curPlayer,
        Cards::FindCardByName("Thrive in the Shadows", FormatType::STANDARD));

    CHECK_EQ(curPlayer->GetDeckZone()->GetCount(), 26);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 2u);

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(curPlayer->GetDeckZone()->GetCount(), 25);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
}

// ----------------------------------------- MINION - ROGUE
// [CORE_AT_029] Buccaneer - COST:1 [ATK:2/HP:1]
// - Race: Pirate, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Whenever you equip a weapon, give it +1 Attack.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - CORE_AT_029 : Buccaneer")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::ROGUE;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Buccaneer"));

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 2);
}

// ------------------------------------------ SPELL - ROGUE
// [CORE_CS2_072] Backstab - COST:0
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Deal 2 damage to an undamaged minion.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_UNDAMAGED_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - CORE_CS2_072 : Backstab")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::ROGUE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Backstab"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Backstab"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(opField[0]->GetHealth(), 5);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(opField[0]->GetHealth(), 5);
}

// ------------------------------------------ SPELL - ROGUE
// [CORE_CS2_073] Cold Blood - COST:2
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Give a minion +2 Attack.
//       <b>Combo:</b> +4 Attack instead.
// --------------------------------------------------------
// GameTag:
// - COMBO = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - CORE_CS2_073 : Cold Blood")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::ROGUE;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cold Blood"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cold Blood"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(curField[0]->GetAttack(), 5);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card4));
    CHECK_EQ(curField[1]->GetAttack(), 7);
}

// ------------------------------------------ SPELL - ROGUE
// [CORE_CS2_074] Deadly Poison - COST:1
// - Set: CORE, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: Give your weapon +2 Attack.
// --------------------------------------------------------
// PlayReq:
// - REQ_WEAPON_EQUIPPED = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - CORE_CS2_074 : Deadly Poison")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Deadly Poison"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curPlayer->GetWeapon().GetAttack(), 1);
    CHECK_EQ(curPlayer->GetWeapon().GetDurability(), 2);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetWeapon().GetAttack(), 3);
    CHECK_EQ(curPlayer->GetWeapon().GetDurability(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetWeapon().GetAttack(), 3);
    CHECK_EQ(curPlayer->GetWeapon().GetDurability(), 2);
}

// ------------------------------------------ SPELL - ROGUE
// [CORE_CS2_075] Sinister Strike - COST:1
// - Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: Deal 3 damage to the enemy hero.
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - CORE_CS2_075 : Sinister Strike")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::SHAMAN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sinister Strike"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);
}

// ------------------------------------------ SPELL - ROGUE
// [CORE_CS2_076] Assassinate - COST:4
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Destroy an enemy minion.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_ENEMY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - CORE_CS2_076 : Assassinate")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Assassinate"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
    CHECK_EQ(opField.GetCount(), 0);
}

// ------------------------------------------ SPELL - ROGUE
// [CORE_CS2_077] Sprint - COST:5
// - Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: Draw 4 cards.
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - CORE_CS2_077 : Sprint")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::SHAMAN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sprint"));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 8);
}

// ----------------------------------------- WEAPON - ROGUE
// [CORE_CS2_080] Assassin's Blade - COST:4
// - Set: CORE, Rarity: Rare
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 5
// --------------------------------------------------------
TEST_CASE("[Rogue : Weapon] - CORE_CS2_080 : Assassin's Blade")
{
    // Do nothing
}

// ----------------------------------------- MINION - ROGUE
// [CORE_DAL_416] Hench-Clan Burglar - COST:4 [ATK:4/HP:4]
// - Race: Pirate, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> <b>Discover</b> a spell
//       from another class.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - CORE_DAL_416 : Hench-Clan Burglar")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::ROGUE;
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
        curPlayer, Cards::FindCardByName("Hench-Clan Burglar"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::SPELL);
        CHECK_NE(card->GetCardClass(), CardClass::ROGUE);
    }
}

// ----------------------------------------- MINION - ROGUE
// [CORE_EX1_134] SI:7 Agent - COST:3 [ATK:3/HP:3]
// - Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Combo:</b> Deal 2 damage.
// --------------------------------------------------------
// GameTag:
// - COMBO = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_FOR_COMBO = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - CORE_EX1_134 : SI:7 Agent")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::ROGUE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("SI:7 Agent"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("SI:7 Agent"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);
}

// ------------------------------------------ SPELL - ROGUE
// [CORE_EX1_144] Shadowstep - COST:0
// - Set: CORE, Rarity: Common
// - Spell School: Shadow
// --------------------------------------------------------
// Text: Return a friendly minion to your hand.
//       It costs (2) less.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_FRIENDLY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - CORE_EX1_144 : Shadowstep")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::ROGUE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shadowstep"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shadowstep"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shadowstep"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("SI:7 Agent"));
    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("SI:7 Agent"));

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 9);
    CHECK_EQ(curPlayer->GetFieldZone()->GetCount(), 1);
    CHECK_EQ(card4->GetCost(), 1);

    game.Process(curPlayer, AttackTask(card4, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 29);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card4));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 9);
    CHECK_EQ(curPlayer->GetFieldZone()->GetCount(), 0);
    CHECK_EQ(card4->GetCost(), 0);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(dynamic_cast<Minion*>(card4)->CanAttack(), true);

    game.Process(curPlayer, AttackTask(card4, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);

    CHECK_EQ(curPlayer->IsComboActive(), true);

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card5, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 26);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card5));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 7);
    CHECK_EQ(curPlayer->GetFieldZone()->GetCount(), 1);
    CHECK_EQ(card5->GetCost(), 1);

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card5, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 24);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->IsComboActive(), false);

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card6, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 24);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card6));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(curPlayer->GetFieldZone()->GetCount(), 2);
    CHECK_EQ(card6->GetCost(), 1);

    CHECK_EQ(curPlayer->IsComboActive(), true);

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card6, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 22);
}

// ------------------------------------------ SPELL - ROGUE
// [CORE_EX1_145] Preparation - COST:0
// - Set: CORE, Rarity: Epic
// --------------------------------------------------------
// Text: The next spell you cast this turn costs (2) less.
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - CORE_EX1_145 : Preparation")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::ROGUE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Preparation"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Preparation"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Preparation"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Eviscerate"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Vanish"));

    CHECK_EQ(card1->GetCost(), 0);
    CHECK_EQ(card2->GetCost(), 0);
    CHECK_EQ(card3->GetCost(), 0);
    CHECK_EQ(card4->GetCost(), 2);
    CHECK_EQ(card5->GetCost(), 6);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(card2->GetCost(), 0);
    CHECK_EQ(card3->GetCost(), 0);
    CHECK_EQ(card4->GetCost(), 0);
    CHECK_EQ(card5->GetCost(), 4);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(card3->GetCost(), 0);
    CHECK_EQ(card4->GetCost(), 0);
    CHECK_EQ(card5->GetCost(), 4);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, opPlayer->GetHero()));
    CHECK_EQ(card3->GetCost(), 0);
    CHECK_EQ(card5->GetCost(), 6);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(card5->GetCost(), 4);
}

// ----------------------------------------- MINION - ROGUE
// [CORE_GIL_598] Tess Greymane - COST:7 [ATK:6/HP:6]
// - Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Replay every card from
//       another class you've played this game
//       <i>(targets chosen randomly)</i>.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - CORE_GIL_598 : Tess Greymane")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::WARLOCK;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Tess Greymane"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fiendish Circle"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fiery War Axe"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Righteous Protector"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Twisting Nether"));

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField.GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Weapon(card3));
    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card5));
    CHECK_EQ(curField.GetCount(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), false);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 6);
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), true);
}

// ----------------------------------------- MINION - ROGUE
// [CORE_ICC_809] Plague Scientist - COST:3 [ATK:2/HP:3]
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Combo:</b> Give a friendly minion <b>Poisonous</b>.
// --------------------------------------------------------
// GameTag:
// - COMBO = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_MINION_TARGET = 0
// - REQ_FRIENDLY_TARGET = 0
// - REQ_TARGET_FOR_COMBO = 0
// --------------------------------------------------------
// RefTag:
// - POISONOUS = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - CORE_ICC_809 : Plague Scientist")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::ROGUE;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Plague Scientist"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Plague Scientist"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasPoisonous(), false);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card1));
    CHECK_EQ(curField[0]->HasPoisonous(), true);
    CHECK_EQ(curField[1]->HasPoisonous(), false);
}

// ----------------------------------------- MINION - ROGUE
// [CORE_KAR_069] Swashburglar - COST:1 [ATK:1/HP:1]
// - Race: Pirate, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Add a random card
//       from another class to your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - CORE_KAR_069 : Swashburglar")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::ROGUE;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Swashburglar"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK(curHand[0]->card->IsCardClass(CardClass::HUNTER));
}

// ----------------------------------------- MINION - ROGUE
// [CORE_LOE_012] Tomb Pillager - COST:4 [ATK:5/HP:4]
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Add a Coin to your hand.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - CORE_LOE_012 : Tomb Pillager")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Tomb Pillager"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->name, "The Coin");
}

// ---------------------------------------- MINION - SHAMAN
// [CORE_BOT_533] Menacing Nimbus - COST:2 [ATK:2/HP:2]
// - Race: Elemental, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Add a random Elemental to your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - CORE_BOT_533 : Menacing Nimbus")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::SHAMAN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Menacing Nimbus"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curHand[0]->card->GetRace(), Race::ELEMENTAL);
}

// ---------------------------------------- MINION - SHAMAN
// [CORE_CS2_042] Fire Elemental - COST:6 [ATK:6/HP:5]
// - Race: Elemental, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 4 damage.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - CORE_CS2_042 : Fire Elemental")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::SHAMAN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fire Elemental"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fire Elemental"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 26);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->GetHealth(), 7);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, opField[0]));
    CHECK_EQ(opField[0]->GetHealth(), 3);
}

//----------------------------------------- SPELL - SHAMAN
// [CORE_CS2_045] Rockbiter Weapon - COST:2
// - Set: CORE, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: Give a friendly character +3 Attack this turn.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_FRIENDLY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - CORE_CS2_045 : Rockbiter Weapon")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Rockbiter Weapon"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Rockbiter Weapon"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
    CHECK_EQ(curField[0]->GetAttack(), 3);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 3);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3));
    CHECK_EQ(curField[0]->GetAttack(), 6);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
    CHECK_EQ(curField[0]->GetAttack(), 3);
}

// ----------------------------------------- SPELL - SHAMAN
// [CORE_CS2_046] Bloodlust - COST:5
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Give your minions +3 Attack this turn.
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - CORE_CS2_046 : Bloodlust")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::SHAMAN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodlust"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 6);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[1]->GetAttack(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField[0]->GetAttack(), 9);
    CHECK_EQ(curField[1]->GetAttack(), 6);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[1]->GetAttack(), 3);
}

// ----------------------------------------- SPELL - SHAMAN
// [CORE_CS2_053] Far Sight - COST:3
// - Set: CORE, Rarity: Epic
// --------------------------------------------------------
// Text: Draw a card. That card costs (3) less.
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - CORE_CS2_053 : Far Sight")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::SHAMAN;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Far Sight"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 5);

    const Playable* drawCard = curHand[curHand.GetCount() - 1];
    const int cost = drawCard->card->gameTags[GameTag::COST] - 3;
    CHECK_EQ(cost < 0 ? 0 : cost, drawCard->GetCost());
}

// ----------------------------------------- SPELL - SHAMAN
// [CORE_EX1_238] Lightning Bolt - COST:1
// - Set: CORE, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: Deal 3 damage. <b>Overload:</b> (1)
// --------------------------------------------------------
// GameTag:
// - OVERLOAD = 1
// - OVERLOAD_OWED = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - CORE_EX1_238 : Lightning Bolt")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::SHAMAN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lightning Bolt"));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);
    CHECK_EQ(curPlayer->GetRemainingMana(), 9);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 1);
    CHECK_EQ(curPlayer->GetOverloadLocked(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetRemainingMana(), 9);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 0);
    CHECK_EQ(curPlayer->GetOverloadLocked(), 1);
}

// ----------------------------------------- SPELL - SHAMAN
// [CORE_EX1_246] Hex - COST:4
// - Set: CORE, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: Transform a minion into a 0/1 Frog with <b>Taunt</b>.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - CORE_EX1_246 : Hex")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::SHAMAN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hex"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hex"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 0);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAUNT), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card4));
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetAttack(), 0);
    CHECK_EQ(opField[0]->GetHealth(), 1);
    CHECK_EQ(opField[0]->GetGameTag(GameTag::TAUNT), 1);
}

// ----------------------------------------- SPELL - SHAMAN
// [CORE_EX1_248] Feral Spirit - COST:3
// - Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: Summon two 2/3 Spirit Wolves with <b>Taunt</b>.
//       <b>Overload:</b> (1)
// --------------------------------------------------------
// GameTag:
// - OVERLOAD = 1
// - OVERLOAD_OWED = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - CORE_EX1_248 : Feral Spirit")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::SHAMAN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Feral Spirit"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(curField[1]->HasTaunt(), true);
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 3);

    CHECK_EQ(curPlayer->GetRemainingMana(), 7);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 1);
    CHECK_EQ(curPlayer->GetOverloadLocked(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetRemainingMana(), 9);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 0);
    CHECK_EQ(curPlayer->GetOverloadLocked(), 1);
}

// ----------------------------------------- SPELL - SHAMAN
// [CORE_EX1_259] Lightning Storm - COST:3
// - Set: CORE, Rarity: Rare
// - Spell School: Nature
// --------------------------------------------------------
// Text: Deal 3 damage to all enemy minions.
//       <b>Overload:</b> (2)
// --------------------------------------------------------
// GameTag:
// - OVERLOAD = 2
// - OVERLOAD_OWED = 2
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - CORE_EX1_259 : Lightning Storm")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lightning Storm"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField[0]->GetHealth(), 7);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[1]->GetHealth(), 7);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(opField[0]->GetHealth(), 4);
    CHECK_EQ(opField[1]->GetHealth(), 4);
    CHECK_EQ(curPlayer->GetRemainingMana(), 7);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 2);
    CHECK_EQ(curPlayer->GetOverloadLocked(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetRemainingMana(), 8);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 0);
    CHECK_EQ(curPlayer->GetOverloadLocked(), 2);
}

// ---------------------------------------- MINION - SHAMAN
// [CORE_EX1_565] Flametongue Totem - COST:2 [ATK:0/HP:2]
// - Race: Totem, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Adjacent minions have +2 Attack.
// --------------------------------------------------------
// GameTag:
// - ADJACENT_BUFF = 1
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - CORE_EX1_565 : Flametongue Totem")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARLOCK;
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
        curPlayer, Cards::FindCardByName("Flametongue Totem"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Flametongue Totem"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Flametongue Totem"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Flametongue Totem"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dalaran Mage"));
    const auto card7 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card8 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 0);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(curField[1]->GetAttack(), 8);
    CHECK_EQ(curField[1]->GetHealth(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 10);
    CHECK_EQ(curField[1]->GetHealth(), 7);
    CHECK_EQ(curField[2]->GetAttack(), 0);
    CHECK_EQ(curField[2]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card6));
    CHECK_EQ(curField[3]->GetAttack(), 3);
    CHECK_EQ(curField[3]->GetHealth(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[3]->GetAttack(), 5);
    CHECK_EQ(curField[3]->GetHealth(), 4);
    CHECK_EQ(curField[4]->GetAttack(), 0);
    CHECK_EQ(curField[4]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card7));
    CHECK_EQ(curField[5]->GetAttack(), 5);
    CHECK_EQ(curField[5]->GetHealth(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField[5]->GetAttack(), 7);
    CHECK_EQ(curField[5]->GetHealth(), 1);
    CHECK_EQ(curField[6]->GetAttack(), 0);
    CHECK_EQ(curField[6]->GetHealth(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card8));
    game.Process(opPlayer, AttackTask(card8, card7));

    CHECK_EQ(curField[4]->GetAttack(), 2);
    CHECK_EQ(curField[4]->GetHealth(), 2);
    CHECK_EQ(curField[5]->GetAttack(), 2);
    CHECK_EQ(curField[5]->GetHealth(), 2);
}

// ---------------------------------------- WEAPON - SHAMAN
// [CORE_EX1_567] Doomhammer - COST:5
// - Set: CORE, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Windfury, Overload:</b> (2)
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 8
// - WINDFURY = 1
// - OVERLOAD = 2
// - OVERLOAD_OWED = 2
// --------------------------------------------------------
TEST_CASE("[Shaman : Weapon] - CORE_EX1_567 : Doomhammer")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Doomhammer"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetWeapon().GetAttack(), 2);
    CHECK_EQ(curPlayer->GetWeapon().GetDurability(), 8);
    CHECK_EQ(curPlayer->GetWeapon().GetGameTag(GameTag::WINDFURY), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetRemainingMana(), 8);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 0);
    CHECK_EQ(curPlayer->GetOverloadLocked(), 2);
}

// ---------------------------------------- MINION - SHAMAN
// [CORE_EX1_575] Mana Tide Totem - COST:3 [ATK:0/HP:3]
// - Race: Totem, Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: At the end of your turn, draw a card.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - CORE_EX1_575 : Mana Tide Totem")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mana Tide Totem"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
}

// ----------------------------------------- SPELL - SHAMAN
// [CORE_KAR_073] Maelstrom Portal - COST:2
// - Set: CORE, Rarity: Rare
// - Spell School: Nature
// --------------------------------------------------------
// Text: Deal 1 damage to all enemy minions.
//       Summon a random 1-Cost minion.
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - CORE_KAR_073 : Maelstrom Portal")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::SHAMAN;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Maelstrom Portal"));
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

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->GetCost(), 1);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 11);
}

// ---------------------------------------- MINION - SHAMAN
// [CORE_NEW1_010] Al'Akir the Windlord - COST:8 [ATK:3/HP:6]
// - Race: Elemental, Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Charge, Divine Shield, Taunt, Windfury</b>
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - CHARGE = 1
// - DIVINE_SHIELD = 1
// - TAUNT = 1
// - WINDFURY = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - CORE_NEW1_010 : Al'Akir the Windlord")
{
    // Do nothing
}

// ---------------------------------------- MINION - SHAMAN
// [CORE_TRL_345] Krag'wa, the Frog - COST:6 [ATK:4/HP:6]
// - Race: Beast, Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Return all spells you played
//       last turn to your hand.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - CORE_TRL_345 : Krag'wa, the Frog")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::SHAMAN;
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
        curPlayer, Cards::FindCardByName("Krag'wa, the Frog"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Krag'wa, the Frog"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Doomhammer"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, curPlayer->GetHero()));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 3);
    CHECK_EQ(curHand[2]->card->name, "Fireball");

    curPlayer->SetUsedMana(0);
    game.Process(curPlayer, PlayCardTask::Weapon(card5));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHand.GetCount(), 1);
}

// ----------------------------------------- SPELL - SHAMAN
// [CORE_UNG_817] Tidal Surge - COST:3
// - Set: CORE, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: <b>Lifesteal</b>
//       Deal 4 damage to a minion.
// --------------------------------------------------------
// GameTag:
// - LIFESTEAL = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - CORE_UNG_817 : Tidal Surge")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::WARLOCK;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Tidal Surge"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(curField[0]->GetHealth(), 7);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 24);
    CHECK_EQ(curField[0]->GetHealth(), 3);
}

// ---------------------------------------- MINION - SHAMAN
// [CS3_007] Novice Zapper - COST:1 [ATK:3/HP:2]
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Spell Damage +1</b>
//       <b>Overload:</b> (1)
// --------------------------------------------------------
// GameTag:
// - OVERLOAD = 1
// - OVERLOAD_OWED = 1
// - SPELLPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - CS3_007 : Novice Zapper")
{
    // Do nothing
}

//--------------------------------------- MINION - WARLOCK
// [CORE_AT_021] Tiny Knight of Evil - COST:2 [ATK:3/HP:2]
// - Race: Demon, Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever you discard a card, gain +1/+1.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - CORE_AT_021 : Tiny Knight of Evil")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Tiny Knight of Evil"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Soulfire"));
    [[maybe_unused]] const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Soulfire"));
    [[maybe_unused]] const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Soulfire"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(curHand[0], opPlayer->GetHero()));
    CHECK_EQ(curHand.GetCount(), 0);
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 3);
}

// --------------------------------------- MINION - WARLOCK
// [CORE_BRM_006] Imp Gang Boss - COST:3 [ATK:2/HP:4]
// - Race: Demon, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Whenever this minion takes damage, summon a 1/1 Imp.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - CORE_BRM_006 : Imp Gang Boss")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Imp Gang Boss"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->name, "Imp");
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
}

// --------------------------------------- MINION - WARLOCK
// [CORE_CFM_751] Abyssal Enforcer - COST:7 [ATK:6/HP:6]
// - Race: Demon, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 3 damage to all other characters.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - CORE_CFM_751 : Abyssal Enforcer")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::SHAMAN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Abyssal Enforcer"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));

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

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 27);
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 6);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 4);
}

// ---------------------------------------- SPELL - WARLOCK
// [CORE_CS2_062] Hellfire - COST:4
// - Set: CORE, Rarity: Common
// - Spell School: Fire
// --------------------------------------------------------
// Text: Deal 3 damage to all characters.
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - CORE_CS2_062 : Hellfire")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::SHAMAN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hellfire"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));

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
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 27);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 4);
}

// --------------------------------------- MINION - WARLOCK
// [CORE_CS2_065] Voidwalker - COST:1 [ATK:1/HP:3]
// - Race: Demon, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - CORE_CS2_065 : Voidwalker")
{
    // Do nothing
}

// ---------------------------------------- SPELL - WARLOCK
// [CORE_EX1_302] Mortal Coil - COST:1
// - Set: CORE, Rarity: Common
// - Spell School: Shadow
// --------------------------------------------------------
// Text: Deal 1 damage to a minion.
//       If that kills it, draw a card.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - CORE_EX1_302 : Mortal Coil")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::SHAMAN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mortal Coil"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mortal Coil"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(opField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(opField.GetCount(), 0);
}

// --------------------------------------- MINION - WARLOCK
// [CORE_EX1_304] Void Terror - COST:3 [ATK:3/HP:4]
// - Race: Demon, Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy both adjacent minions
//       and gain their Attack and Health.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - CORE_EX1_304 : Void Terror")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::MAGE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Void Terror"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Void Terror"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Imp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Blood Imp"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[1]->GetAttack(), 0);
    CHECK_EQ(curField[1]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask(card1, nullptr, 1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 7);

    game.Process(curPlayer, PlayCardTask(card2, nullptr, 1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 9);
    CHECK_EQ(curField[0]->GetHealth(), 11);
}

// ---------------------------------------- SPELL - WARLOCK
// [CORE_EX1_309] Siphon Soul - COST:5
// - Set: CORE, Rarity: Rare
// - Spell School: Shadow
// --------------------------------------------------------
// Text: Destroy a minion. Restore 3 Health to your hero.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - CORE_EX1_309 : Siphon Soul")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARLOCK;
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
    curPlayer->GetHero()->SetDamage(8);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Siphon Soul"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Voidwalker"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 22);
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 25);
    CHECK_EQ(curField.GetCount(), 0);
}

// ---------------------------------------- SPELL - WARLOCK
// [CORE_EX1_312] Twisting Nether - COST:8
// - Set: CORE, Rarity: Epic
// - Spell School: Shadow
// --------------------------------------------------------
// Text: Destroy all minions.
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - CORE_EX1_312 : Twisting Nether")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARLOCK;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Twisting Nether"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Voidwalker"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 7);
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(opField.GetCount(), 0);
}

// --------------------------------------- MINION - WARLOCK
// [CORE_EX1_319] Flame Imp - COST:1 [ATK:3/HP:2]
// - Race: Demon, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 3 damage to your hero.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - CORE_EX1_319 : Flame Imp")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARLOCK;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Imp"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 27);
}

// ---------------------------------------- SPELL - WARLOCK
// [CORE_GIL_191] Fiendish Circle - COST:3
// - Set: CORE, Rarity: Common
// - Spell School: Fel
// --------------------------------------------------------
// Text: Summon four 1/1 Imps.
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - CORE_GIL_191 : Fiendish Circle")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::DRUID;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fiendish Circle"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fiendish Circle"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[0]->card->name, "Imp");
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField.GetCount(), 7);
    CHECK_EQ(curField[6]->card->name, "Imp");
    CHECK_EQ(curField[6]->GetAttack(), 1);
    CHECK_EQ(curField[6]->GetHealth(), 1);
}

// ---------------------------------------- SPELL - WARLOCK
// [CORE_ICC_055] Drain Soul - COST:2
// - Set: CORE, Rarity: Common
// - Spell School: Shadow
// --------------------------------------------------------
// Text: <b>Lifesteal</b>
//       Deal 3 damage to a minion.
// --------------------------------------------------------
// GameTag:
// - LIFESTEAL = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - CORE_ICC_055 : Drain Soul")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARLOCK;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Drain Soul"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Sen'jin Shieldmasta"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 23);
    CHECK_EQ(curField[0]->GetHealth(), 2);
}

// --------------------------------------- MINION - WARLOCK
// [CORE_OG_109] Darkshire Librarian - COST:2 [ATK:3/HP:2]
// - Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Discard a random card.
//       <b>Deathrattle:</b> Draw a card.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - CORE_OG_109 : Darkshire Librarian")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Darkshire Librarian"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curHand.GetCount(), 4);
}

// --------------------------------------- MINION - WARLOCK
// [CORE_TRL_252] High Priestess Jeklik - COST:4 [ATK:3/HP:5]
// - Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Taunt</b>, <b>Lifesteal</b>
//       When you discard this,
//       add 2 copies of it to your hand.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - LIFESTEAL = 1
// - TAUNT = 1
// - InvisibleDeathrattle = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - CORE_TRL_252 : High Priestess Jeklik")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    auto& curHand = *(curPlayer->GetHandZone());

    [[maybe_unused]] const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("High Priestess Jeklik"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Darkshire Librarian"));

    CHECK_EQ(curHand.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHand.GetCount(), 2);
    CHECK_EQ(curHand[0]->card->name, "High Priestess Jeklik");
    CHECK_EQ(curHand[1]->card->name, "High Priestess Jeklik");
}

// --------------------------------------- MINION - WARLOCK
// [CORE_UNG_833] Lakkari Felhound - COST:4 [ATK:3/HP:8]
// - Race: Demon, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Battlecry:</b> Discard your two lowest-Cost cards.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - CORE_UNG_833 : Lakkari Felhound")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::DRUID;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lakkari Felhound"));
    [[maybe_unused]] const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    [[maybe_unused]] const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pyroblast"));
    [[maybe_unused]] const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Blizzard"));
    [[maybe_unused]] const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));

    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 2);
    CHECK_EQ(curHand[0]->card->name, "Pyroblast");
    CHECK_EQ(curHand[1]->card->name, "Malygos");
}

// --------------------------------------- MINION - WARLOCK
// [CS3_003] Felsoul Jailer - COST:5 [ATK:4/HP:6]
// - Race: Demon, Set: CORE, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Your opponent discards a minion.
//       <b>Deathrattle:</b> Return it.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - CS3_003 : Felsoul Jailer")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Felsoul Jailer", FormatType::STANDARD));
    [[maybe_unused]] const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    CHECK_EQ(opHand.GetCount(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(opHand.GetCount(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opHand.GetCount(), 2);
    CHECK_EQ(opHand[1]->card->name, "Malygos");
}

// ---------------------------------------- SPELL - WARRIOR
// [CORE_AT_064] Bash - COST:2
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Deal 3 damage.
//       Gain 3 Armor.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - CORE_AT_064 : Bash")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::HUNTER;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bash"));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 3);
}

// --------------------------------------- WEAPON - WARRIOR
// [CORE_CS2_106] Fiery War Axe - COST:3
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 2
// --------------------------------------------------------
TEST_CASE("[Warrior : Weapon] - CORE_CS2_106 : Fiery War Axe")
{
    // Do nothing
}

// ---------------------------------------- SPELL - WARRIOR
// [CORE_CS2_108] Execute - COST:1
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Destroy a damaged enemy minion.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_ENEMY_TARGET = 0
// - REQ_DAMAGED_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - CORE_CS2_108 : Execute")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARRIOR;
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

    const auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Execute"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, AttackTask(card2, card3));

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(opField.GetCount(), 0);
}

// ---------------------------------------- SPELL - WARRIOR
// [CORE_EX1_391] Slam - COST:1
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Deal 2 damage to a minion. If it survives, draw a card.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - CORE_EX1_391 : Slam")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Magma Rager"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chillwind Yeti"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Slam"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Slam"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    int opHandCount = opHand.GetCount();

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(opHandCount, opHand.GetCount());

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(opHandCount - 1, opHand.GetCount());
}

// ---------------------------------------- SPELL - WARRIOR
// [CORE_EX1_400] Whirlwind - COST:1
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Deal 1 damage to all minions.
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - CORE_EX1_400 : Whirlwind")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::HUNTER;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Whirlwind"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetHealth(), 7);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[1]->GetHealth(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField[0]->GetHealth(), 7);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(opField[1]->GetHealth(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 6);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 6);
}

// --------------------------------------- MINION - WARRIOR
// [CORE_EX1_402] Armorsmith - COST:2 [ATK:1/HP:4]
// - Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever a friendly minion takes damage, gain 1 Armor.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - CORE_EX1_402 : Armorsmith")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Armorsmith"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Amani Berserker"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card2));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 1);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 2);
}

// ---------------------------------------- SPELL - WARRIOR
// [CORE_EX1_407] Brawl - COST:5
// - Set: CORE, Rarity: Epic
// --------------------------------------------------------
// Text: Destroy all minions except one.
//       <i>(chosen randomly)</i>
// --------------------------------------------------------
// PlayReq:
// - REQ_MINIMUM_TOTAL_MINIONS = 2
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - CORE_EX1_407 : Brawl")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARRIOR;
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
    auto& curHand = *(curPlayer->GetHandZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Brawl"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(opField.GetCount(), 3);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 0);
    CHECK_EQ(curField.GetCount() + opField.GetCount(), 1);
}

// ---------------------------------------- SPELL - WARRIOR
// [CORE_EX1_410] Shield Slam - COST:1
// - Set: CORE, Rarity: Epic
// --------------------------------------------------------
// Text: Deal 1 damage to a minion for each Armor you have.
// --------------------------------------------------------
// GameTag:
// - AFFECTED_BY_SPELL_POWER = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - CORE_EX1_410 : Shield Slam")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARRIOR;
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
    curPlayer->GetHero()->SetArmor(3);

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shield Slam"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shield Slam"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Bloodmage Thalnos"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Ironbark Protector"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField[0]->GetHealth(), 8);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card4));
    CHECK_EQ(opField[0]->GetHealth(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card4));
    CHECK_EQ(opField[0]->GetHealth(), 1);
}

// --------------------------------------- WEAPON - WARRIOR
// [CORE_EX1_411] Gorehowl - COST:7
// - Set: CORE, Rarity: Epic
// --------------------------------------------------------
// Text: Attacking a minion costs 1 Attack instead of 1 Durability.
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Weapon] - CORE_EX1_411 : Gorehowl")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Gorehowl"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Weapon(card2));
    CHECK_EQ(opPlayer->GetHero()->weapon->GetAttack(), 7);
    CHECK_EQ(opPlayer->GetHero()->weapon->GetDurability(), 1);

    game.Process(opPlayer, AttackTask(opPlayer->GetHero(), card1));
    CHECK_EQ(opPlayer->GetHero()->weapon->GetAttack(), 6);
    CHECK_EQ(opPlayer->GetHero()->weapon->GetDurability(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer,
                 AttackTask(opPlayer->GetHero(), curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 24);
    CHECK_EQ(opPlayer->GetHero()->HasWeapon(), false);
}

// --------------------------------------- MINION - WARRIOR
// [CORE_EX1_414] Grommash Hellscream - COST:8 [ATK:4/HP:9]
// - Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Charge</b>
//       Has +6 Attack while damaged.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - CHARGE = 1
// - ENRAGED = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - CORE_EX1_414 : Grommash Hellscream")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Grommash Hellscream"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Circle of Healing"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 9);

    game.Process(curPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetAttack(), 10);
    CHECK_EQ(curField[0]->GetHealth(), 8);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 9);
}

// --------------------------------------- MINION - WARRIOR
// [CORE_EX1_603] Cruel Taskmaster - COST:2 [ATK:2/HP:3]
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 1 damage to a minion
//       and give it +2 Attack.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_MINION_TARGET = 0
// - REQ_NONSELF_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - CORE_EX1_603 : Cruel Taskmaster")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cruel Taskmaster"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cruel Taskmaster"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card1));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 3);
}

// --------------------------------------- MINION - WARRIOR
// [CORE_EX1_604] Frothing Berserker - COST:3 [ATK:2/HP:4]
// - Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever a minion takes damage, gain +1 Attack.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - CORE_EX1_604 : Frothing Berserker")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Frothing Berserker"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Stonetusk Boar"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));

    game.Process(opPlayer, AttackTask(card4, card2));
    CHECK_EQ(curField[0]->GetAttack(), 5);

    game.Process(opPlayer, AttackTask(card5, card3));
    CHECK_EQ(curField[0]->GetAttack(), 7);
}

// ---------------------------------------- SPELL - WARRIOR
// [CORE_EX1_606] Shield Block - COST:3
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Gain 5 Armor.
//       Draw a card.
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - CORE_EX1_606 : Shield Block")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARRIOR;
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
    curPlayer->GetHero()->SetArmor(3);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shield Block"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 8);
}

// --------------------------------------- MINION - WARRIOR
// [CORE_GIL_547] Darius Crowley - COST:5 [ATK:4/HP:5]
// - Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Rush</b>
//       After this attacks and kills a minion, gain +2/+2.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - RUSH = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - CORE_GIL_547 : Darius Crowley")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::DRUID;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Darius Crowley"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Violet Teacher"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, AttackTask(card1, card3));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(card1, card2));
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 3);
}

// --------------------------------------- MINION - WARRIOR
// [CORE_GVG_053] Shieldmaiden - COST:5 [ATK:5/HP:5]
// - Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Gain 5 Armor.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - CORE_GVG_053 : Shieldmaiden")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shieldmaiden"));

    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 0);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 5);
}

// --------------------------------------- MINION - WARRIOR
// [CORE_OG_218] Bloodhoof Brave - COST:4 [ATK:2/HP:6]
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       Has +3 Attack while damaged.
// --------------------------------------------------------
// GameTag:
// - ENRAGED = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - CORE_OG_218 : Bloodhoof Brave")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodhoof Brave"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 6);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 5);
}

// --------------------------------------- MINION - WARRIOR
// [CS3_008] Bloodsail Deckhand - COST:1 [ATK:2/HP:1]
// - Race: Pirate, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> The next weapon you play costs
//       (1) less.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - CS3_008 : Bloodsail Deckhand")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARRIOR;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Bloodsail Deckhand", FormatType::STANDARD));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fiery War Axe"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fiery War Axe"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Execute"));

    CHECK_EQ(card2->GetCost(), 3);
    CHECK_EQ(card3->GetCost(), 3);
    CHECK_EQ(card4->GetCost(), 9);
    CHECK_EQ(card5->GetCost(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetRemainingMana(), 9);
    CHECK_EQ(card2->GetCost(), 2);
    CHECK_EQ(card3->GetCost(), 2);
    CHECK_EQ(card4->GetCost(), 9);
    CHECK_EQ(card5->GetCost(), 1);

    game.Process(curPlayer, PlayCardTask::Weapon(card2));
    CHECK_EQ(curPlayer->GetRemainingMana(), 7);
    CHECK_EQ(card3->GetCost(), 3);
    CHECK_EQ(card4->GetCost(), 9);
    CHECK_EQ(card5->GetCost(), 1);
}

// ------------------------------------ SPELL - DEMONHUNTER
// [CORE_BT_035] Chaos Strike - COST:2
// - Set: CORE, Rarity: Common
// - Spell School: Fel
// --------------------------------------------------------
// Text: Give your hero +2 Attack this turn. Draw a card.
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - CORE_BT_035 : Chaos Strike")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chaos Strike"));

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 3);
    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
}

// ------------------------------------ SPELL - DEMONHUNTER
// [CORE_BT_036] Coordinated Strike - COST:3
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Summon three 1/1 Illidari with <b>Rush</b>.
// --------------------------------------------------------
// RefTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - CORE_BT_036 : Coordinated Strike")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
        opPlayer, Cards::FindCardByName("Coordinated Strike"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(opField.GetCount(), 3);
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

    game.Process(opPlayer, AttackTask(opField[0], card1));
    game.Process(opPlayer, AttackTask(opField[0], card1));
    game.Process(opPlayer, AttackTask(opField[0], card1));
    CHECK_EQ(curField[0]->GetHealth(), 9);
    CHECK_EQ(opField.GetCount(), 0);
}

// ------------------------------------ SPELL - DEMONHUNTER
// [CORE_BT_235] Chaos Nova - COST:5
// - Set: CORE, Rarity: Common
// - Spell School: Fel
// --------------------------------------------------------
// Text: Deal 4 damage to all minions.
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - CORE_BT_235 : Chaos Nova")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Oasis Snapjaw"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Silverback Patriarch"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Chaos Nova"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Ogre Magi"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(opField.GetCount(), 0);
}

// ----------------------------------- WEAPON - DEMONHUNTER
// [CORE_BT_271] Flamereaper - COST:7
// - Set: CORE, Rarity: Epic
// --------------------------------------------------------
// Text: Also damages the minions next to whomever
//       your hero attacks.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// - DURABILITY = 3
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Weapon] - CORE_BT_271 : Flamereaper")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
// [CORE_BT_323] Sightless Watcher - COST:2 [ATK:3/HP:2]
// - Race: Demon, Faction: Horde, Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Look at 3 cards in your deck.
//       Choose one to put on top.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - CORE_BT_323 : Sightless Watcher")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::DEMONHUNTER;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Magma Rager");
        config.player1Deck[i + 1] = Cards::FindCardByName("Wolfrider");
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
    auto& curDeck = *(curPlayer->GetDeckZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Sightless Watcher"));

    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curDeck.GetCount(), 26);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 3u);

    auto pickedCardID =
        game.entityList[curPlayer->choice->choices[0]]->card->id;
    game.Process(curPlayer,
                 ChooseTask::Pick(curPlayer, curPlayer->choice->choices[0]));

    CHECK_EQ(curHand.GetCount(), 4);
    CHECK_EQ(curDeck.GetCount(), 26);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand[4]->card->id, pickedCardID);
    CHECK_EQ(curDeck.GetCount(), 25);
}

// ----------------------------------- MINION - DEMONHUNTER
// [CORE_BT_351] Battlefiend - COST:1 [ATK:1/HP:2]
// - Race: Demon, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: After your hero attacks, gain +1 Attack.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - CORE_BT_351 : Battlefiend")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

// ----------------------------------- MINION - DEMONHUNTER
// [CORE_BT_355] Wrathscale Naga - COST:3 [ATK:3/HP:2]
// - Race: Naga, Set: CORE, Rarity: Epic
// --------------------------------------------------------
// Text: After a friendly minion dies,
//       deal 3 damage to a random enemy.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - CORE_BT_355 : Wrathscale Naga")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
// [CORE_BT_416] Raging Felscreamer - COST:4 [ATK:4/HP:4]
// - Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> The next Demon you play costs (2) less.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - CORE_BT_416 : Raging Felscreamer")
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
// [CORE_BT_427] Feast of Souls - COST:1
// - Set: CORE, Rarity: Rare
// - Spell School: Shadow
// --------------------------------------------------------
// Text: Draw a card for each friendly minion that died this turn.
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - CORE_BT_427 : Feast of Souls")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
    const auto& opHand = *(opPlayer->GetHandZone());

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

// ------------------------------------ SPELL - DEMONHUNTER
// [CORE_BT_429] Metamorphosis - COST:5
// - Set: CORE, Rarity: Legendary
// - Spell School: Fel
// --------------------------------------------------------
// Text: Swap your Hero Power to "Deal 4 damage."
//       After 2 uses, swap it back.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - CORE_BT_429 : Metamorphosis")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Metamorphosis"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shadowform"));

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curPlayer->GetHero()->heroPower->card->name, "Mind Spike");

    game.Process(curPlayer, HeroPowerTask(opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHero()->heroPower->card->id, "BT_429p");

    game.Process(curPlayer, HeroPowerTask(opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 24);
    CHECK_EQ(curPlayer->GetHero()->heroPower->card->id, "BT_429p2");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask(opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(curPlayer->GetHero()->heroPower->card->name, "Mind Spike");
}

// ----------------------------------- MINION - DEMONHUNTER
// [CORE_BT_480] Crimson Sigil Runner - COST:1 [ATK:1/HP:1]
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Outcast:</b> Draw a card.
// --------------------------------------------------------
// GameTag:
// - OUTCAST = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - CORE_BT_480 : Crimson Sigil Runner")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Crimson Sigil Runner"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Crimson Sigil Runner"));

    CHECK_EQ(curHand.GetCount(), 6);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHand.GetCount(), 6);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
}

// ------------------------------------ SPELL - DEMONHUNTER
// [CORE_BT_491] Spectral Sight - COST:2
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Draw a card.
//       <b>Outcast:</b> Draw another.
// --------------------------------------------------------
// GameTag:
// - OUTCAST = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Spell] - CORE_BT_491 : Spectral Sight")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Spectral Sight"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Spectral Sight"));

    CHECK_EQ(curHand.GetCount(), 6);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curHand.GetCount(), 7);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 7);
}

// ------------------------------------ SPELL - DEMONHUNTER
// [CORE_BT_801] Eye Beam - COST:3
// - Set: CORE, Rarity: Epic
// - Spell School: Fel
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
TEST_CASE("[Demon Hunter : Spell] - CORE_BT_801 : Eye Beam")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

// ----------------------------------- WEAPON - DEMONHUNTER
// [CORE_BT_921] Aldrachi Warblades - COST:3 [ATK:2/HP:0]
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Lifesteal</b>
// --------------------------------------------------------
// GameTag:
// - LIFESTEAL = 1
// - DURABILITY = 2
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Weapon] - CORE_BT_921 : Aldrachi Warblades")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
    curPlayer->GetHero()->SetDamage(15);

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Aldrachi Warblades"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), true);
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 2);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 2);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 3);

    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 18);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 2);
}

// ----------------------------------- MINION - DEMONHUNTER
// [CS3_017] Gan'arg Glaivesmith - COST:3 [ATK:3/HP:2]
// - Race: Demon, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Outcast:</b> Give your hero +3 Attack this turn.
// --------------------------------------------------------
// GameTag:
// - OUTCAST = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - CS3_017 : Gan'arg Glaivesmith")
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Gan'arg Glaivesmith", FormatType::STANDARD));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Gan'arg Glaivesmith", FormatType::STANDARD));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
}

// ----------------------------------- MINION - DEMONHUNTER
// [CS3_019] Kor'vas Bloodthorn - COST:2 [ATK:2/HP:2]
// - Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Charge</b>, <b>Lifesteal</b>
//       After you play a card with <b>Outcast</b>,
//       return this to your hand.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - CHARGE = 1
// - LIFESTEAL = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
// RefTag:
// - OUTCAST = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - CS3_019 : Kor'vas Bloodthorn")
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
    curPlayer->GetHero()->SetDamage(15);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Kor'vas Bloodthorn", FormatType::STANDARD));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Gan'arg Glaivesmith", FormatType::STANDARD));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curHand.GetCount(), 6);

    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 17);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curHand[5]->card->name, "Kor'vas Bloodthorn");

    game.Process(curPlayer, PlayCardTask::Minion(curHand[5]));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 19);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 26);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curHand.GetCount(), 4);
}

// ----------------------------------- MINION - DEMONHUNTER
// [CS3_020] Illidari Inquisitor - COST:8 [ATK:8/HP:8]
// - Race: Demon, Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Rush</b>. After your hero attacks an enemy,
//       this attacks it too.
// --------------------------------------------------------
// GameTag:
// - RUSH = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Minion] - CS3_020 : Illidari Inquisitor")
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
    curPlayer->GetHero()->SetDamage(15);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Illidari Inquisitor", FormatType::STANDARD));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, AttackTask(card1, card2));
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(opField[0]->GetHealth(), 4);

    game.Process(curPlayer, HeroPowerTask());
    game.Process(curPlayer, AttackTask(curPlayer->GetHero(), card2));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opField.GetCount(), 0);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_CFM_120] Mistress of Mixtures - COST:1 [ATK:2/HP:2]
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Restore 4 Health to each hero.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_CFM_120 : Mistress of Mixtures")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mistress of Mixtures"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 15);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 24);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 19);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_CS2_122] Raid Leader - COST:3 [ATK:2/HP:3]
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Your other minions have +1 Attack.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_CS2_122 : Raid Leader")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::SHAMAN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Raid Leader"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 6);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, AttackTask(card3, card1));
    CHECK_EQ(curField[0]->GetAttack(), 6);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_CS2_142] Kobold Geomancer - COST:2 [ATK:2/HP:2]
// - Faction: Horde, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Spell Damage +1</b>
// --------------------------------------------------------
// GameTag:
// - SPELLPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_CS2_142 : Kobold Geomancer")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_CS2_179] Sen'jin Shieldmasta - COST:4 [ATK:3/HP:5]
// - Faction: Horde, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_CS2_179 : Sen'jin Shieldmasta")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_CS2_182] Chillwind Yeti - COST:4 [ATK:4/HP:5]
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_CS2_182 : Chillwind Yeti")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_CS2_188] Abusive Sergeant - COST:1 [ATK:1/HP:1]
// - Faction: Alliance, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give a minion +2 Attack this turn.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_CS2_188 : Abusive Sergeant")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Abusive Sergeant"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Abusive Sergeant"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card3));
    CHECK_EQ(curField[0]->GetAttack(), 5);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card4));
    CHECK_EQ(opField[0]->GetAttack(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(opField[0]->GetAttack(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_CS2_189] Elven Archer - COST:1 [ATK:1/HP:1]
// - Faction: Horde, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 1 damage.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_NONSELF_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_CS2_189 : Elven Archer")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Elven Archer"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField[0]->GetHealth(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(opField[0]->GetHealth(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_CS2_203] Ironbeak Owl - COST:3 [ATK:2/HP:1]
// - Race: Beast, Faction: Horde, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> <b>Silence</b> a minion.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - SILENCE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_CS2_203 : Ironbeak Owl")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ironbeak Owl"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ironbeak Owl"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Leper Gnome"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->HasDeathrattle(), true);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card3));
    CHECK_EQ(curField[0]->HasDeathrattle(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField[0]->GetSpellPower(), 5);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card4));
    CHECK_EQ(opField[0]->GetSpellPower(), 0);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_CS2_222] Stormwind Champion - COST:7 [ATK:7/HP:7]
// - Faction: Alliance, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Your other minions have +1/+1.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_CS2_222 : Stormwind Champion")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::SHAMAN;
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
        curPlayer, Cards::FindCardByName("Stormwind Champion"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 7);
    CHECK_EQ(curField[0]->GetHealth(), 8);
    CHECK_EQ(curField[1]->GetAttack(), 7);
    CHECK_EQ(curField[1]->GetHealth(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, AttackTask(card3, card2));
    CHECK_EQ(curField[0]->GetAttack(), 7);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, AttackTask(card4, card1));
    CHECK_EQ(curField[1]->GetAttack(), 7);
    CHECK_EQ(curField[1]->GetHealth(), 4);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_DAL_086] Sunreaver Spy - COST:2 [ATK:2/HP:3]
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you control a <b>Secret</b>,
//       gain +1/+1.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_DAL_086 : Sunreaver Spy")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PALADIN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sunreaver Spy"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sunreaver Spy"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Noble Sacrifice"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 4);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_EX1_005] Big Game Hunter - COST:4 [ATK:4/HP:2]
// - Set: CORE, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy a minion
//       with 7 or more Attack.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_MIN_ATTACK = 7
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_EX1_005 : Big Game Hunter")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Big Game Hunter"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Core Hound"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card3));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
    CHECK_EQ(opField.GetCount(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_EX1_007] Acolyte of Pain - COST:3 [ATK:1/HP:3]
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Whenever this minion takes damage, draw a card.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_EX1_007 : Acolyte of Pain")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Acolyte of Pain"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Stonetusk Boar"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));

    game.Process(opPlayer, AttackTask(card2, card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_EX1_010] Worgen Infiltrator - COST:1 [ATK:2/HP:1]
// - Faction: Alliance, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Stealth</b>
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_EX1_010 : Worgen Infiltrator")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_EX1_011] Voodoo Doctor - COST:1 [ATK:2/HP:1]
// - Faction: Horde, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Restore 2 Health.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_EX1_011 : Voodoo Doctor")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
    curPlayer->GetHero()->SetDamage(6);

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Voodoo Doctor"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Voodoo Doctor"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    opField[0]->SetDamage(1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card1, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 26);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card3));
    CHECK_EQ(opField[0]->GetHealth(), 2);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_EX1_012] Bloodmage Thalnos - COST:2 [ATK:1/HP:1]
// - Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Spell Damage +1</b>
//       <b>Deathrattle:</b> Draw a card.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - SPELLPOWER = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_EX1_012 : Bloodmage Thalnos")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Bloodmage Thalnos"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Blizzard"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetCurrentSpellPower(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 4);
    CHECK_EQ(opField[0]->IsFrozen(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, AttackTask(card5, card1));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(curPlayer->GetCurrentSpellPower(), 0);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_EX1_017] Jungle Panther - COST:3 [ATK:4/HP:2]
// - Race: Beast, Faction: Horde, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Stealth</b>
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_EX1_017 : Jungle Panther")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_EX1_028] Stranglethorn Tiger - COST:5 [ATK:5/HP:5]
// - Race: Beast, Faction: Alliance, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Stealth</b>
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_EX1_028 : Stranglethorn Tiger")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_EX1_043] Twilight Drake - COST:4 [ATK:4/HP:1]
// - Race: Dragon, Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Gain +1 Health
//       for each card in your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_EX1_043 : Twilight Drake")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Twilight Drake"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 4);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_EX1_046] Dark Iron Dwarf - COST:4 [ATK:4/HP:4]
// - Faction: Alliance, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give a minion +2 Attack this turn.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_EX1_046 : Dark Iron Dwarf")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dark Iron Dwarf"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dark Iron Dwarf"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card3));
    CHECK_EQ(curField[0]->GetAttack(), 5);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card4));
    CHECK_EQ(opField[0]->GetAttack(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(opField[0]->GetAttack(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_EX1_049] Youthful Brewmaster - COST:2 [ATK:3/HP:2]
// - Faction: Alliance, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Return a friendly minion
//       from the battlefield to your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_NONSELF_TARGET = 0
// - REQ_MINION_TARGET = 0
// - REQ_FRIENDLY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_EX1_049 : Youthful Brewmaster")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Youthful Brewmaster"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("SI:7 Agent"));

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(curPlayer->GetFieldZone()->GetCount(), 1);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_EX1_059] Crazed Alchemist - COST:2 [ATK:2/HP:2]
// - Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Swap the Attack and Health of a minion.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_EX1_059 : Crazed Alchemist")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Crazed Alchemist"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_EX1_066] Acidic Swamp Ooze - COST:2 [ATK:3/HP:2]
// - Faction: Alliance, Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy your opponent's weapon.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_EX1_066 : Acidic Swamp Ooze")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::ROGUE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fiery War Axe"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), false);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_EX1_082] Mad Bomber - COST:2 [ATK:3/HP:2]
// - Faction: Alliance, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 3 damage randomly split
//       between all other characters.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_EX1_082 : Mad Bomber")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::MAGE;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mad Bomber"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    int health = curPlayer->GetHero()->GetHealth();
    health += opPlayer->GetHero()->GetHealth();
    health += curField[0]->GetHealth();
    health += opField[0]->GetHealth();
    CHECK_EQ(health, 71);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_EX1_093] Defender of Argus - COST:4 [ATK:3/HP:3]
// - Faction: Alliance, Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give adjacent minions +1/+1
//       and <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_EX1_093 : Defender of Argus")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::SHAMAN;
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
        curPlayer, Cards::FindCardByName("Defender of Argus"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask(card1, nullptr, 1));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAUNT), 1);
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 3);
    CHECK_EQ(curField[1]->GetGameTag(GameTag::TAUNT), 0);
    CHECK_EQ(curField[2]->GetAttack(), 4);
    CHECK_EQ(curField[2]->GetHealth(), 2);
    CHECK_EQ(curField[2]->GetGameTag(GameTag::TAUNT), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_EX1_095] Gadgetzan Auctioneer - COST:6 [ATK:4/HP:4]
// - Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever you cast a spell, draw a card.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_EX1_095 : Gadgetzan Auctioneer")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::SHAMAN;
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
        curPlayer, Cards::FindCardByName("Gadgetzan Auctioneer"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pyroblast"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Lightning Bolt"));

    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 6);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 6);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 7);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);

    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card3, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 6);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_EX1_096] Loot Hoarder - COST:2 [ATK:2/HP:1]
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Draw a card.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_EX1_096 : Loot Hoarder")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::HUNTER;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Loot Hoarder"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 4);
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, AttackTask(card2, card1));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opField.GetCount(), 0);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 6);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_EX1_103] Coldlight Seer - COST:3 [ATK:2/HP:3]
// - Race: Murloc, Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give your other Murlocs +2 Health.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_EX1_103 : Coldlight Seer")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Coldlight Seer"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Raider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Raider"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Murloc Raider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, PlayCardTask::Minion(card3));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 3);
    CHECK_EQ(curField[2]->GetHealth(), 1);
    CHECK_EQ(curField[3]->GetHealth(), 3);
    CHECK_EQ(opField[0]->GetHealth(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_EX1_110] Cairne Bloodhoof - COST:6 [ATK:5/HP:5]
// - Faction: Alliance, Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a 5/5 Baine Bloodhoof.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_EX1_110 : Cairne Bloodhoof")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PALADIN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cairne Bloodhoof"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    curField[0]->SetDamage(4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, AttackTask(card2, card1));
    CHECK(card1->isDestroyed);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_EX1_162] Dire Wolf Alpha - COST:2 [ATK:2/HP:2]
// - Race: Beast, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Adjacent minions have +1 Attack.
// --------------------------------------------------------
// GameTag:
// - ADJACENT_BUFF = 1
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_EX1_162 : Dire Wolf Alpha")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PRIEST;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dire Wolf Alpha"));
    const auto card7 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[2]->GetAttack(), 1);
    CHECK_EQ(curField[3]->GetAttack(), 1);

    game.Process(curPlayer, PlayCardTask(card6, nullptr, 2));
    CHECK_EQ(curField[2]->card->name, "Dire Wolf Alpha");
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[3]->GetAttack(), 2);
    CHECK_EQ(curField[4]->GetAttack(), 1);

    game.Process(curPlayer, PlayCardTask(card5, nullptr, 3));
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[3]->GetAttack(), 2);
    CHECK_EQ(curField[4]->GetAttack(), 1);
    CHECK_EQ(card5, curField[3]);
    CHECK_EQ(card3, curField[4]);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[3]->GetAttack(), 2);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card7, card6));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[2]->GetAttack(), 1);
    CHECK_EQ(curField[3]->GetAttack(), 1);
    CHECK_EQ(curField[4]->GetAttack(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_EX1_186] SI:7 Infiltrator - COST:4 [ATK:5/HP:4]
// - Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy a random enemy <b>Secret</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_EX1_186 : SI:7 Infiltrator")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::ROGUE;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Snipe"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("SI:7 Infiltrator"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(card2->isDestroyed, false);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_EX1_187] Arcane Devourer - COST:8 [ATK:4/HP:8]
// - Race: Elemental, Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever you cast a spell, gain +2/+2.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_EX1_187 : Arcane Devourer")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::ROGUE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Devourer"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 8);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 10);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curField[0]->GetAttack(), 8);
    CHECK_EQ(curField[0]->GetHealth(), 12);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_EX1_249] Baron Geddon - COST:7 [ATK:7/HP:7]
// - Race: Elemental, Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: At the end of your turn,
//       deal 2 damage to all other characters.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_EX1_249 : Baron Geddon")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByID("EX1_249"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 7);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 28);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opField.GetCount(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetHealth(), 7);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 5);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 26);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 26);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_EX1_284] Azure Drake - COST:5 [ATK:4/HP:5]
// - Race: Dragon, Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Spell Damage +1</b>
//       <b>Battlecry:</b> Draw a card.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - SPELLPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_EX1_284 : Azure Drake")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Azure Drake"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Archmage"));

    const auto curHandCount = curPlayer->GetHandZone()->GetCount();

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), curHandCount);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3));

    CHECK_EQ(curPlayer->GetFieldZone()->GetCount(), 1);
    CHECK_EQ(opPlayer->GetFieldZone()->GetCount(), 0);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_EX1_506] Murloc Tidehunter - COST:2 [ATK:2/HP:1]
// - Race: Murloc, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a 1/1 Murloc Scout.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_EX1_506 : Murloc Tidehunter")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARRIOR;
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
        curPlayer, Cards::FindCardByName("Murloc Tidehunter"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_EX1_507] Murloc Warleader - COST:3 [ATK:3/HP:3]
// - Race: Murloc, Set: CORE, Rarity: Epic
// --------------------------------------------------------
// Text: Your other Murlocs have +2 Attack.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_EX1_507 : Murloc Warleader")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PRIEST;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Raider"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Murloc Raider"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Murloc Warleader"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, PlayCardTask::Minion(card6));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(opField[0]->GetAttack(), 4);
    CHECK_EQ(opField[1]->GetAttack(), 1);
    CHECK_EQ(opField[2]->GetAttack(), 3);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card6));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(opField[0]->GetAttack(), 2);
    CHECK_EQ(opField[1]->GetAttack(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_EX1_509] Murloc Tidecaller - COST:1 [ATK:1/HP:2]
// - Race: Murloc, Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever you summon a Murloc, gain +1 Attack.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_EX1_509 : Murloc Tidecaller")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Murloc Tidecaller"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Murloc Tidehunter"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Magma Rager"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Magma Rager"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Murloc Tidehunter"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetAttack(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField[0]->GetAttack(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(curField[0]->GetAttack(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_EX1_564] Faceless Manipulator - COST:5 [ATK:3/HP:3]
// - Set: CORE, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Choose a minion and become a copy of it.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_MINION_TARGET = 0
// - REQ_NONSELF_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_EX1_564 : Faceless Manipulator")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PRIEST;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Faceless Manipulator"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Faceless Manipulator"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Northshire Cleric"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Shattered Sun Cleric"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->GetAttack(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 3);

    game.Process(opPlayer, PlayCardTask::MinionTarget(card4, card3));
    CHECK_EQ(opField[0]->GetAttack(), 2);
    CHECK_EQ(opField[0]->GetHealth(), 4);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card3));
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 4);

    curField[1]->SetDamage(1);

    game.Process(curPlayer, HeroPowerTask(curField[1]));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_EX1_586] Sea Giant - COST:10 [ATK:8/HP:8]
// - Set: CORE, Rarity: Epic
// --------------------------------------------------------
// Text: Costs (1) less for each other minion
//       on the battlefield.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_EX1_586 : Sea Giant")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PRIEST;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sea Giant"));
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

    CHECK_EQ(card1->GetCost(), 10);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(card1->GetCost(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, PlayCardTask::Minion(card6));
    CHECK_EQ(card1->GetCost(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_FP1_007] Nerubian Egg - COST:2 [ATK:0/HP:2]
// - Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a 4/4 Nerubian.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_FP1_007 : Nerubian Egg")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Nerubian Egg"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Nerubian");
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 4);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_GIL_124] Mossy Horror - COST:6 [ATK:2/HP:7]
// - Set: CORE, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy all other minions
//       with 2 or less Attack.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_GIL_124 : Mossy Horror")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::HUNTER;
    config.player2Class = CardClass::DRUID;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mossy Horror"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
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

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Wolfrider");
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->card->name, "Wolfrider");
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_GIL_622] Lifedrinker - COST:4 [ATK:3/HP:3]
// - Race: Beast, Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 3 damage to the enemy hero.
//       Restore 3 Health to your hero.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_GIL_622 : Lifedrinker")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARLOCK;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lifedrinker"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 23);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 17);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_GVG_076] Explosive Sheep - COST:2 [ATK:1/HP:1]
// - Race: Mechanical, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Deal 2 damage to all minions.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_GVG_076 : Explosive Sheep")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PALADIN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Explosive Sheep"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Spider Tank"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Violet Teacher"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_GVG_085] Annoy-o-Tron - COST:2 [ATK:1/HP:2]
// - Race: Mechanical, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Divine Shield</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_GVG_085 : Annoy-o-Tron")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_ICC_026] Grim Necromancer - COST:4 [ATK:2/HP:4]
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon two 1/1 Skeletons.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_ICC_026 : Grim Necromancer")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARLOCK;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Grim Necromancer"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->card->name, "Skeleton");
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->card->name, "Grim Necromancer");
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 4);
    CHECK_EQ(curField[2]->card->name, "Skeleton");
    CHECK_EQ(curField[2]->GetAttack(), 1);
    CHECK_EQ(curField[2]->GetHealth(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_ICC_029] Cobalt Scalebane - COST:5 [ATK:5/HP:5]
// - Race: Dragon, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: At the end of your turn,
//       give another random friendly minion +3 Attack.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_ICC_029 : Cobalt Scalebane")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cobalt Scalebane"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[1]->GetAttack(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_LOE_011] Reno Jackson - COST:6 [ATK:4/HP:6]
// - Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If your deck has no duplicates,
//       fully heal your hero.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// - AFFECTED_BY_HEALING_DOES_DAMAGE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_LOE_011 : Reno Jackson")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::HUNTER;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 6; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Wisp");
        config.player2Deck[i] = Cards::FindCardByName("Wisp");
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
    curPlayer->GetHero()->SetDamage(20);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Reno Jackson"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Reno Jackson"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 10);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_LOE_039] Gorillabot A-3 - COST:3 [ATK:3/HP:4]
// - Race: Mechanical, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you control another Mech,
//       <b>Discover</b> a Mech.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - DISCOVER = 1
// - USE_DISCOVER_VISUALS = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_LOE_039 : Gorillabot A-3")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Gorillabot A-3"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Gorillabot A-3"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(!curPlayer->choice);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 3);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::MINION);
        CHECK_EQ(card->GetRace(), Race::MECHANICAL);
    }
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_LOE_076] Sir Finley Mrrgglton - COST:1 [ATK:1/HP:3]
// - Race: Murloc, Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b><b>Battlecry:</b> Discover</b> a new basic Hero Power.
// --------------------------------------------------------
// Entourage: HERO_01bp, HERO_02bp, HERO_03bp, HERO_04bp,
//            HERO_05bp, HERO_06bp, HERO_07bp, HERO_08bp,
//            HERO_09bp, HERO_10bp
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// - DISCOVER = 1
// - USE_DISCOVER_VISUALS = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_LOE_076 : Sir Finley Mrrgglton")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::HUNTER;
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
        curPlayer, Cards::FindCardByName("Sir Finley Mrrgglton"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK(curPlayer->choice);
    CHECK_EQ(curPlayer->choice->choices.size(), 3);

    auto cards = TestUtils::GetChoiceCards(game);
    for (auto& card : cards)
    {
        CHECK_EQ(card->GetCardType(), CardType::HERO_POWER);
    }
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_LOE_077] Brann Bronzebeard - COST:3 [ATK:2/HP:4]
// - Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: Your <b>Battlecries</b> trigger twice.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - AURA = 1
// --------------------------------------------------------
// RefTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_LOE_077 : Brann Bronzebeard")
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
    opPlayer->GetHero()->SetDamage(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Brann Bronzebeard"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Elven Archer"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Razorfen Hunter"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Abusive Sergeant"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->ExtraBattlecry(), true);

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 5);
    CHECK_EQ(curField[2]->card->name, "Razorfen Hunter");
    CHECK_EQ(curField[3]->card->name, "Boar");
    CHECK_EQ(curField[4]->card->name, "Boar");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card5, card1));
    CHECK_EQ(curPlayer->ExtraBattlecry(), false);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card4, card2));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_LOE_079] Elise Starseeker - COST:4 [ATK:3/HP:5]
// - Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Shuffle the
//       'Map to the Golden Monkey' into your deck.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_LOE_079 : Elise Starseeker")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    config.player1Deck[0] = Cards::FindCardByName("Bloodfen Raptor");
    config.player1Deck[1] = Cards::FindCardByName("Young Dragonhawk");
    config.player1Deck[2] = Cards::FindCardByName("Faerie Dragon");

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);
    opPlayer->GetHero()->SetDamage(0);

    auto& curDeck = *(curPlayer->GetDeckZone());
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Elise Starseeker"));

    CHECK_EQ(curHand.GetCount(), 4);
    CHECK_EQ(curDeck.GetCount(), 0);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 3);
    CHECK_EQ(curDeck.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 4);
    CHECK_EQ(curHand[3]->card->name, "Map to the Golden Monkey");

    game.Process(curPlayer, PlayCardTask::Spell(curHand[3]));
    CHECK_EQ(curHand.GetCount(), 4);
    CHECK_EQ(curHand[3]->card->name, "Golden Monkey");
    CHECK_EQ(curDeck.GetCount(), 0);

    Card* wispCard = Cards::FindCardByName("Wisp");
    Generic::ShuffleIntoDeck(curPlayer, curPlayer,
                             Entity::GetFromCard(curPlayer, wispCard));
    Generic::ShuffleIntoDeck(curPlayer, curPlayer,
                             Entity::GetFromCard(curPlayer, wispCard));
    Generic::ShuffleIntoDeck(curPlayer, curPlayer,
                             Entity::GetFromCard(curPlayer, wispCard));
    CHECK_EQ(curDeck.GetCount(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(curHand[3]));
    CHECK_EQ(curHand[0]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curHand[0]->card->GetRarity(), Rarity::LEGENDARY);
    CHECK_EQ(curHand[1]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curHand[1]->card->GetRarity(), Rarity::LEGENDARY);
    CHECK_EQ(curHand[2]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curHand[2]->card->GetRarity(), Rarity::LEGENDARY);
    CHECK_EQ(curDeck[0]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curDeck[0]->card->GetRarity(), Rarity::LEGENDARY);
    CHECK_EQ(curDeck[1]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curDeck[1]->card->GetRarity(), Rarity::LEGENDARY);
    CHECK_EQ(curDeck[2]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curDeck[2]->card->GetRarity(), Rarity::LEGENDARY);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_LOEA10_3] Murloc Tinyfin - COST:0 [ATK:1/HP:1]
// - Race: Murloc, Set: CORE, Rarity: Common
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_LOEA10_3 : Murloc Tinyfin")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_LOOT_124] Lone Champion - COST:3 [ATK:2/HP:4]
// - Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you control no other minions,
//       gain <b>Taunt</b> and <b>Divine Shield</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_LOOT_124 : Lone Champion")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lone Champion"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lone Champion"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[0]->HasDivineShield(), true);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->HasTaunt(), false);
    CHECK_EQ(curField[1]->HasDivineShield(), false);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_LOOT_137] Sleepy Dragon - COST:9 [ATK:4/HP:12]
// - Race: Dragon, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_LOOT_137 : Sleepy Dragon")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_LOOT_413] Plated Beetle - COST:2 [ATK:2/HP:3]
// - Race: Beast, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Gain 3 Armor.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_LOOT_413 : Plated Beetle")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Plated Beetle"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_LOOT_516] Zola the Gorgon - COST:3 [ATK:2/HP:2]
// - Race: Naga, Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Choose a friendly minion.
//       Add a Golden copy of it to your hand.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_FRIENDLY_TARGET = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_LOOT_516 : Zola the Gorgon")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::DRUID;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Zola the Gorgon"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->name, "Wisp");
    CHECK_EQ(curHand[0]->IsGoldenCard(), true);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_NEW1_018] Bloodsail Raider - COST:2 [ATK:2/HP:3]
// - Race: Pirate, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Gain Attack equal to the Attack
//       of your weapon.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_NEW1_018 : Bloodsail Raider")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PRIEST;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fiery War Axe"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodsail Raider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodsail Raider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[1]->GetAttack(), 5);
    CHECK_EQ(curField[1]->GetHealth(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_NEW1_020] Wild Pyromancer - COST:2 [ATK:3/HP:2]
// - Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: After you cast a spell, deal 1 damage to all minions.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_NEW1_020 : Wild Pyromancer")
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wild Pyromancer"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Shot"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Shot"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Arcane Shot"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card7 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card6));
    game.Process(opPlayer, PlayCardTask::Minion(card7));
    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card5, curPlayer->GetHero()));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, opPlayer->GetHero()));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opField.GetCount(), 0);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_NEW1_021] Doomsayer - COST:2 [ATK:0/HP:7]
// - Set: CORE, Rarity: Epic
// --------------------------------------------------------
// Text: At the start of your turn, destroy all minions.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_NEW1_021 : Doomsayer")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Doomsayer"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Kor'kron Elite"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Water Elemental"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 4);
    CHECK_EQ(curField.GetCount(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(opField.GetCount(), 0);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_NEW1_023] Faerie Dragon - COST:2 [ATK:3/HP:2]
// - Race: Dragon, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: Can't be targeted by spells or Hero Powers.
// --------------------------------------------------------
// GameTag:
// - CANT_BE_TARGETED_BY_SPELLS = 1
// - CANT_BE_TARGETED_BY_HERO_POWERS = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_NEW1_023 : Faerie Dragon")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Faerie Dragon"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField[0]->GetHealth(), 2);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_NEW1_026] Violet Teacher - COST:4 [ATK:3/HP:5]
// - Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever you cast a spell,
//       summon a 1/1 Violet Apprentice.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_NEW1_026 : Violet Teacher")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::ROGUE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Violet Teacher"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Preparation"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[1]->card->name, "Violet Apprentice");
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_NEW1_027] Southsea Captain - COST:3 [ATK:3/HP:3]
// - Race: Pirate, Set: CORE, Rarity: Epic
// --------------------------------------------------------
// Text: Your other Pirates have +1/+1.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_NEW1_027 : Southsea Captain")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Southsea Captain"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Southsea Captain"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shieldbearer"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Southsea Captain"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Southsea Captain"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[1]->GetAttack(), 0);
    CHECK_EQ(curField[1]->GetHealth(), 4);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[2]->GetAttack(), 4);
    CHECK_EQ(curField[2]->GetHealth(), 4);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 5);
    CHECK_EQ(curField[1]->GetAttack(), 0);
    CHECK_EQ(curField[1]->GetHealth(), 4);
    CHECK_EQ(curField[2]->GetAttack(), 5);
    CHECK_EQ(curField[2]->GetHealth(), 5);
    CHECK_EQ(curField[3]->GetAttack(), 5);
    CHECK_EQ(curField[3]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 5);
    CHECK_EQ(curField[1]->GetAttack(), 0);
    CHECK_EQ(curField[1]->GetHealth(), 4);
    CHECK_EQ(curField[2]->GetAttack(), 5);
    CHECK_EQ(curField[2]->GetHealth(), 5);
    CHECK_EQ(curField[3]->GetAttack(), 5);
    CHECK_EQ(curField[3]->GetHealth(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_ULD_191] Beaming Sidekick - COST:1 [ATK:1/HP:2]
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give a friendly minion +2 Health.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_FRIENDLY_TARGET = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_ULD_191 : Beaming Sidekick")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Beaming Sidekick"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Beaming Sidekick"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Beaming Sidekick"));

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, nullptr));
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card1));
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card3, card2));
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 4);
    CHECK_EQ(curField[2]->GetHealth(), 2);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_ULD_209] Vulpera Scoundrel - COST:3 [ATK:2/HP:3]
// - Set: CORE, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry</b>: <b>Discover</b> a spell
//       or pick a mystery choice.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - DISCOVER = 1
// - USE_DISCOVER_VISUALS = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_ULD_209 : Vulpera Scoundrel")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::SHAMAN;
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
    curPlayer->GetHero()->SetDamage(6);

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Vulpera Scoundrel"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Vulpera Scoundrel"));

    SUBCASE("A spell card - Except ULD_209t")
    {
        game.Process(curPlayer, PlayCardTask::Spell(card1));
        CHECK(curPlayer->choice);

        auto cards = TestUtils::GetChoiceCards(game);
        for (std::size_t i = 0; i < 3; ++i)
        {
            CHECK_EQ(cards[i]->IsCardClass(CardClass::DRUID), true);
            CHECK_EQ(cards[i]->GetCardType(), CardType::SPELL);
        }
        CHECK_EQ(cards[3]->id, "ULD_209t");

        TestUtils::ChooseNthChoice(game, 1);
        CHECK_EQ(curHand.GetCount(), 2);
        CHECK_EQ(curHand[1]->card->IsCardClass(CardClass::DRUID), true);
        CHECK_EQ(curHand[1]->card->GetCardType(), CardType::SPELL);
    }

    SUBCASE("Mystery Choice! - ULD_209t")
    {
        game.Process(curPlayer, PlayCardTask::Spell(card2));
        CHECK(curPlayer->choice);

        auto cards = TestUtils::GetChoiceCards(game);
        for (std::size_t i = 0; i < 3; ++i)
        {
            CHECK_EQ(cards[i]->IsCardClass(CardClass::DRUID), true);
            CHECK_EQ(cards[i]->GetCardType(), CardType::SPELL);
        }
        CHECK_EQ(cards[3]->id, "ULD_209t");

        TestUtils::ChooseNthChoice(game, 4);
        CHECK_EQ(curHand.GetCount(), 2);
        CHECK_EQ(curHand[1]->card->IsCardClass(CardClass::DRUID), true);
        CHECK_EQ(curHand[1]->card->GetCardType(), CardType::SPELL);
    }
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_ULD_271] Injured Tol'vir - COST:2 [ATK:2/HP:6]
// - Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Battlecry:</b> Deal 3 damage to this minion.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_ULD_271 : Injured Tol'vir")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Injured Tol'vir"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetDamage(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_UNG_813] Stormwatcher - COST:7 [ATK:4/HP:8]
// - Race: Elemental, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Windfury</b>
// --------------------------------------------------------
// GameTag:
// - WINDFURY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_UNG_813 : Stormwatcher")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_UNG_844] Humongous Razorleaf - COST:3 [ATK:4/HP:8]
// - Faction: Alliance, Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: Can't attack.
// --------------------------------------------------------
// GameTag:
// - CANT_ATTACK = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_UNG_844 : Humongous Razorleaf")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_UNG_848] Primordial Drake - COST:8 [ATK:4/HP:8]
// - Race: Dragon, Set: CORE, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Battlecry:</b> Deal 2 damage to all other minions.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_UNG_848 : Primordial Drake")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Primordial Drake"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetHealth(), 12);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 10);
    CHECK_EQ(opField[0]->GetHealth(), 10);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_UNG_928] Tar Creeper - COST:3 [ATK:1/HP:5]
// - Race: Elemental, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       Has +2 Attack during your opponent's turn.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_UNG_928 : Tar Creeper")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Tar Creeper"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [CORE_YOD_006] Escaped Manasaber - COST:4 [ATK:3/HP:5]
// - Race: Beast, Set: CORE, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Stealth</b>
//       Whenever this attacks,
//       gain 1 Mana Crystal this turn only.
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CORE_YOD_006 : Escaped Manasaber")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::DRUID;
    config.player2Class = CardClass::HUNTER;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(5);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Escaped Manasaber"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetTotalMana(), 6);
    CHECK_EQ(curPlayer->GetRemainingMana(), 6);
    CHECK_EQ(curPlayer->GetTemporaryMana(), 0);

    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetTotalMana(), 6);
    CHECK_EQ(curPlayer->GetRemainingMana(), 7);
    CHECK_EQ(curPlayer->GetTemporaryMana(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetTotalMana(), 7);
    CHECK_EQ(curPlayer->GetRemainingMana(), 7);
    CHECK_EQ(curPlayer->GetTemporaryMana(), 0);
}

// --------------------------------------- MINION - NEUTRAL
// [CS3_022] Fogsail Freebooter - COST:2 [ATK:2/HP:2]
// - Race: Pirate, Set: CORE, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you have a weapon equipped,
//       deal 2 damage.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CS3_022 : Fogsail Freebooter")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
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
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    const auto opHero = opPlayer->GetHero();

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Fogsail Freebooter", FormatType::STANDARD));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Fogsail Freebooter", FormatType::STANDARD));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opHero->GetHealth(), 30);

    game.Process(curPlayer, HeroPowerTask());
    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, opHero));
    CHECK_EQ(opHero->GetHealth(), 28);
}

// --------------------------------------- MINION - NEUTRAL
// [CS3_024] Taelan Fordring - COST:5 [ATK:3/HP:3]
// - Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b><b>Taunt</b>, Divine Shield</b>
//       <b>Deathrattle:</b> Draw your highest Cost minion.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - DEATHRATTLE = 1
// - DIVINE_SHIELD = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CS3_024 : Taelan Fordring")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Stormwatcher");
        config.player1Deck[i + 1] = Cards::FindCardByName("Sleepy Dragon");
        config.player1Deck[i + 2] = Cards::FindCardByName("Faerie Dragon");
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
        curPlayer,
        Cards::FindCardByName("Taelan Fordring", FormatType::STANDARD));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Sleepy Dragon");
}

// --------------------------------------- MINION - NEUTRAL
// [CS3_025] Overlord Runthak - COST:5 [ATK:3/HP:6]
// - Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Rush</b>. Whenever this attacks,
//       give +1/+1 to all minions in your hand.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - RUSH = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CS3_025 : Overlord Runthak")
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
        curPlayer,
        Cards::FindCardByName("Overlord Runthak", FormatType::STANDARD));
    [[maybe_unused]] const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    [[maybe_unused]] const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, AttackTask(card1, card4));
    CHECK_EQ(dynamic_cast<Minion*>(curHand[0])->GetAttack(), 2);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[0])->GetHealth(), 2);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[1])->GetAttack(), 5);
    CHECK_EQ(dynamic_cast<Minion*>(curHand[1])->GetHealth(), 13);
}

// --------------------------------------- MINION - NEUTRAL
// [CS3_031] Alexstrasza the Life-Binder - COST:9 [ATK:8/HP:8]
// - Race: Dragon, Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry</b>: Choose a character.
//       If it's friendly, restore 8 Health.
//       If it's an enemy, deal 8 damage.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CS3_031 : Alexstrasza the Life-Binder")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Alexstrasza the Life-Binder",
                                         FormatType::STANDARD));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Alexstrasza the Life-Binder",
                                        FormatType::STANDARD));

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card1, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 28);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer,
                 PlayCardTask::MinionTarget(card2, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 20);
}

// --------------------------------------- MINION - NEUTRAL
// [CS3_032] Onyxia the Broodmother - COST:9 [ATK:8/HP:8]
// - Race: Dragon, Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: At the end of each turn,
//       fill your board with 1/1 Whelps.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CS3_032 : Onyxia the Broodmother")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Onyxia the Broodmother", FormatType::STANDARD));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Flamestrike"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 7);
    CHECK_EQ(curField[0]->card->name, "Whelp");
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[0]->card->name, "Whelp");
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[2]->card->name, "Whelp");
    CHECK_EQ(curField[2]->GetAttack(), 1);
    CHECK_EQ(curField[2]->GetHealth(), 1);
    CHECK_EQ(curField[3]->card->name, "Onyxia the Broodmother");
    CHECK_EQ(curField[3]->GetAttack(), 8);
    CHECK_EQ(curField[3]->GetHealth(), 8);
    CHECK_EQ(curField[4]->card->name, "Whelp");
    CHECK_EQ(curField[4]->GetAttack(), 1);
    CHECK_EQ(curField[4]->GetHealth(), 1);
    CHECK_EQ(curField[5]->card->name, "Whelp");
    CHECK_EQ(curField[5]->GetAttack(), 1);
    CHECK_EQ(curField[5]->GetHealth(), 1);
    CHECK_EQ(curField[6]->card->name, "Whelp");
    CHECK_EQ(curField[6]->GetAttack(), 1);
    CHECK_EQ(curField[6]->GetHealth(), 1);

    game.Process(opPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 7);
    CHECK_EQ(curField[0]->card->name, "Whelp");
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[0]->card->name, "Whelp");
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[2]->card->name, "Whelp");
    CHECK_EQ(curField[2]->GetAttack(), 1);
    CHECK_EQ(curField[2]->GetHealth(), 1);
    CHECK_EQ(curField[3]->card->name, "Onyxia the Broodmother");
    CHECK_EQ(curField[3]->GetAttack(), 8);
    CHECK_EQ(curField[3]->GetHealth(), 3);
    CHECK_EQ(curField[4]->card->name, "Whelp");
    CHECK_EQ(curField[4]->GetAttack(), 1);
    CHECK_EQ(curField[4]->GetHealth(), 1);
    CHECK_EQ(curField[5]->card->name, "Whelp");
    CHECK_EQ(curField[5]->GetAttack(), 1);
    CHECK_EQ(curField[5]->GetHealth(), 1);
    CHECK_EQ(curField[6]->card->name, "Whelp");
    CHECK_EQ(curField[6]->GetAttack(), 1);
    CHECK_EQ(curField[6]->GetHealth(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [CS3_033] Ysera the Dreamer - COST:9 [ATK:4/HP:12]
// - Race: Dragon, Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Add one of each Dream card
//       to your hand.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CS3_033 : Ysera the Dreamer")
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
        curPlayer,
        Cards::FindCardByName("Ysera the Dreamer", FormatType::STANDARD));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[0]->card->name, "Nightmare");
    CHECK_EQ(curHand[1]->card->name, "Dream");
    CHECK_EQ(curHand[2]->card->name, "Laughing Sister");
    CHECK_EQ(curHand[3]->card->name, "Ysera Awakens");
    CHECK_EQ(curHand[4]->card->name, "Emerald Drake");
}

// --------------------------------------- MINION - NEUTRAL
// [CS3_034] Malygos the Spellweaver - COST:9 [ATK:4/HP:12]
// - Race: Dragon, Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Draw spells until your hand is full.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CS3_034 : Malygos the Spellweaver")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::SHAMAN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Bloodfen Raptor");
        config.player1Deck[i + 1] = Cards::FindCardByName("Fireball");
        config.player1Deck[i + 2] = Cards::FindCardByName("Frostbolt");
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
        curPlayer,
        Cards::FindCardByName("Malygos the Spellweaver", FormatType::STANDARD));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 10);
    CHECK_EQ(curHand[4]->card->GetCardType(), CardType::SPELL);
    CHECK_EQ(curHand[5]->card->GetCardType(), CardType::SPELL);
    CHECK_EQ(curHand[6]->card->GetCardType(), CardType::SPELL);
    CHECK_EQ(curHand[7]->card->GetCardType(), CardType::SPELL);
    CHECK_EQ(curHand[8]->card->GetCardType(), CardType::SPELL);
    CHECK_EQ(curHand[9]->card->GetCardType(), CardType::SPELL);
}

// --------------------------------------- MINION - NEUTRAL
// [CS3_036] Deathwing the Destroyer - COST:10 [ATK:12/HP:12]
// - Race: Dragon, Set: CORE, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy all other minions.
//       Discard a card for each destroyed.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CS3_036 : Deathwing the Destroyer")
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
    auto& curHand = *(curPlayer->GetHandZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Deathwing the Destroyer", FormatType::STANDARD));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 6);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curHand.GetCount(), 3);
    CHECK_EQ(opField.GetCount(), 0);
}

// --------------------------------------- MINION - NEUTRAL
// [CS3_037] Emerald Skytalon - COST:1 [ATK:2/HP:1]
// - Race: Beast, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Rush</b>
// --------------------------------------------------------
// GameTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CS3_037 : Emerald Skytalon")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [CS3_038] Redgill Razorjaw - COST:2 [ATK:3/HP:1]
// - Race: Murloc, Set: CORE, Rarity: Common
// --------------------------------------------------------
// Text: <b>Rush</b>
// --------------------------------------------------------
// GameTag:
// - RUSH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CS3_038 : Redgill Razorjaw")
{
    // Do nothing
}