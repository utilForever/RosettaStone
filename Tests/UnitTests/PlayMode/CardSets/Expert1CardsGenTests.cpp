// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetHeaders.hpp>

// ----------------------------------------- HERO - WARLOCK
// [EX1_323] Lord Jaraxxus - COST:9 [ATK:0/HP:30]
// - Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Equip a 3/8 Blood Fury.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Hero] - EX1_323 : Lord Jaraxxus")
{
    GameConfig config;
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
// [EX1_154] Wrath - COST:2
// - Faction: Neutral, Set: Expert1, Rarity: Common
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
TEST_CASE("[Druid : Spell] - EX1_154 : Wrath")
{
    GameConfig config;
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
// [EX1_155] Mark of Nature - COST:3
// - Faction: Neutral, Set: Expert1, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: <b>Choose One -</b> Give a minion +4 Attack;
//       or +4 Health and <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - EX1_155 : Mark of Nature")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mark of Nature"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mark of Nature"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card1, 1));
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[0]->HasTaunt(), false);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card4, card2, 2));
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 5);
    CHECK_EQ(curField[1]->HasTaunt(), true);
}

// ------------------------------------------ SPELL - DRUID
// [EX1_158] Soul of the Forest - COST:4
// - Faction: Neutral, Set: Expert1, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: Give your minions "<b>Deathrattle:</b> Summon a 2/2 Treant."
// --------------------------------------------------------
// RefTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - EX1_158 : Soul of the Forest")
{
    GameConfig config;
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
// [EX1_160] Power of the Wild - COST:2
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Choose One -</b> Give your minions +1/+1;
//       or Summon a 3/2 Panther.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - EX1_160 : Power of the Wild")
{
    GameConfig config;
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
// [EX1_161] Naturalize - COST:1
// - Faction: Neutral, Set: Expert1, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: Destroy a minion. Your opponent draws 2 cards.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - EX1_161 : Naturalize")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Naturalize"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Magma Rager"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    const auto curHandCount = curPlayer->GetHandZone()->GetCount();
    game.Process(opPlayer, PlayCardTask::SpellTarget(card1, card2));

    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), curHandCount + 2);
    CHECK_EQ(curPlayer->GetFieldZone()->GetCount(), 0);
}

// ------------------------------------------ SPELL - DRUID
// [EX1_164] Nourish - COST:5
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// - Spell School: Nature
// --------------------------------------------------------
// Text: <b>Choose One -</b> Gain 2 Mana Crystals;
//       or Draw 3 cards.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - EX1_164 : Nourish")
{
    GameConfig config;
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
// [EX1_165] Druid of the Claw - COST:5 [ATK:5/HP:4]
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Choose One -</b> Transform into a 5/4 with <b>Charge</b>;
//       or a 5/6 with <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// --------------------------------------------------------
// RefTag:
// - CHARGE = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - EX1_165 : Druid of the Claw")
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
        curPlayer, Cards::FindCardByName("Druid of the Claw"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Druid of the Claw"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Silence"));

    game.Process(curPlayer, PlayCardTask::Minion(card1, 1));
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[0]->CanAttack(), true);
    CHECK_EQ(curField[0]->HasTaunt(), false);

    game.Process(curPlayer, PlayCardTask::Minion(card2, 2));
    CHECK_EQ(curField[1]->GetAttack(), 5);
    CHECK_EQ(curField[1]->GetHealth(), 6);
    CHECK_EQ(curField[1]->CanAttack(), false);
    CHECK_EQ(curField[1]->HasTaunt(), true);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, curField[1]));
    CHECK_EQ(curField[1]->GetAttack(), 5);
    CHECK_EQ(curField[1]->GetHealth(), 6);
    CHECK_EQ(curField[1]->CanAttack(), false);
    CHECK_EQ(curField[1]->HasTaunt(), false);
}

// ----------------------------------------- MINION - DRUID
// [EX1_166] Keeper of the Grove - COST:4 [ATK:2/HP:4]
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Choose One -</b> Deal 2 damage;
//       or <b>Silence</b> a minion.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
// RefTag:
// - SILENCE = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - EX1_166 : Keeper of the Grove")
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
        curPlayer, Cards::FindCardByName("Keeper of the Grove"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Keeper of the Grove"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Archmage"));

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card1, opPlayer->GetHero(), 1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opPlayer->GetCurrentSpellPower(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card3, 2));
    CHECK_EQ(opPlayer->GetCurrentSpellPower(), 0);
}

// ----------------------------------------- MINION - DRUID
// [EX1_178] Ancient of War - COST:7 [ATK:5/HP:5]
// - Faction: Neutral, Set: Expert1, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Choose One -</b>+5 Attack;
//       or +5 Health and <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - EX1_178 : Ancient of War")
{
    GameConfig config;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ancient of War"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Ancient of War"));

    game.Process(curPlayer, PlayCardTask::Minion(card1, 1));
    CHECK_EQ(curField[0]->GetHealth(), 10);
    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAUNT), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2, 2));
    CHECK_EQ(opField[0]->GetAttack(), 10);
}

// ------------------------------------------ SPELL - DRUID
// [EX1_183] Gift of the Wild - COST:8
// - Set: Expert1, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: Give your minions +2/+2 and <b>Taunt</b>.
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - EX1_183 : Gift of the Wild")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Gift of the Wild"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[0]->HasTaunt(), false);
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[1]->HasTaunt(), false);
    CHECK_EQ(curField[2]->GetAttack(), 3);
    CHECK_EQ(curField[2]->GetHealth(), 2);
    CHECK_EQ(curField[2]->HasTaunt(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[1]->GetAttack(), 5);
    CHECK_EQ(curField[1]->GetHealth(), 3);
    CHECK_EQ(curField[1]->HasTaunt(), true);
    CHECK_EQ(curField[2]->GetAttack(), 5);
    CHECK_EQ(curField[2]->GetHealth(), 4);
    CHECK_EQ(curField[2]->HasTaunt(), true);
}

// ------------------------------------------- SPELL - DRUID
// [EX1_570] Bite - COST:4
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: Give your hero +4 Attack this turn. Gain 4 Armor.
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - EX1_570 : Bite")
{
    GameConfig config;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bite"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 4);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 4);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 5);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 5);
}

// ------------------------------------------ SPELL - DRUID
// [EX1_571] Force of Nature - COST:5
// - Faction: Neutral, Set: Expert1, Rarity: Epic
// - Spell School: Nature
// --------------------------------------------------------
// Text: Summon three 2/2 Treants.
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - EX1_571 : Force of Nature")
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
// [EX1_573] Cenarius - COST:8 [ATK:5/HP:8]
// - Faction: Neutral, Set: Expert1, Rarity: Legendary
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
TEST_CASE("[Druid : Minion] - EX1_573 : Cenarius")
{
    GameConfig config;
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

// ------------------------------------------ SPELL - DRUID
// [EX1_578] Savagery - COST:1
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: Deal damage equal to your hero's Attack to a minion.
// --------------------------------------------------------
// GameTag:
// - AFFECTED_BY_SPELL_POWER = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - EX1_578 : Savagery")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Savagery"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Savagery"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Bloodmage Thalnos"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 12);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask());
    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField[0]->GetHealth(), 11);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask());
    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(curField[0]->GetHealth(), 9);
}

// ------------------------------------------ SPELL - DRUID
// [NEW1_007] Starfall - COST:5
// - Set: Expert1, Rarity: Rare
// - Spell School: Arcane
// --------------------------------------------------------
// Text: <b>Choose One -</b> Deal 5 damage to a minion;
//       or 2 damage to all enemy minions.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - NEW1_007 : Starfall")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Starfall"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Starfall"));
    const auto card7 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Starfall"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField.GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card6, card1, 2));
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(opPlayer, PlayCardTask::Spell(card7, 1));
    CHECK_EQ(curField.GetCount(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card5, 1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 0);
}

// ----------------------------------------- MINION - DRUID
// [NEW1_008] Ancient of Lore - COST:7 [ATK:5/HP:5]
// - Set: Expert1, Rarity: Epic
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
TEST_CASE("[Druid : Minion] - NEW1_008 : Ancient of Lore")
{
    GameConfig config;
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

// ---------------------------------------- WEAPON - HUNTER
// [DS1_188] Gladiator's Longbow - COST:7 [ATK:5/HP:0]
// - Faction: Neutral, Set: Expert1, Rarity: Epic
// --------------------------------------------------------
// Text: Your hero is <b>Immune</b> while attacking.
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 2
// --------------------------------------------------------
// RefTag:
// - IMMUNE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Weapon] - DS1_188 : Gladiator's Longbow")
{
    GameConfig config;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Gladiator's Longbow"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetWeapon().GetAttack(), 5);
    CHECK_EQ(curPlayer->GetWeapon().GetDurability(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(curPlayer->GetHero(), card2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(curPlayer->GetHero()->GetGameTag(GameTag::IMMUNE), 0);
}

// ---------------------------------------- MINION - HUNTER
// [EX1_531] Scavenging Hyena - COST:2 [ATK:2/HP:2]
// - Race: Beast, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: Whenever a friendly Beast dies, gain +2/+1.
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - EX1_531 : Scavenging Hyena")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Scavenging Hyena"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodfen Raptor"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Arcane Explosion"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card5));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(opPlayer, HeroPowerTask(card4));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 3);
}

// ----------------------------------------- SPELL - HUNTER
// [EX1_533] Misdirection - COST:2
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Secret:</b> When an enemy attacks your hero,
//       instead it attacks another random character.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - EX1_533 : Misdirection")
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

    auto curSecret = curPlayer->GetSecretZone();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Misdirection"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));

    game.Process(opPlayer, AttackTask(card2, curPlayer->GetHero()));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ((card3->isDestroyed || opPlayer->GetHero()->GetHealth() == 27),
             true);
}

// ---------------------------------------- MINION - HUNTER
// [EX1_534] Savannah Highmane - COST:6 [ATK:6/HP:5]
// - Race: Beast, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon two 2/2 Hyenas.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - EX1_534 : Savannah Highmane")
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

// ---------------------------------------- WEAPON - HUNTER
// [EX1_536] Eaglehorn Bow - COST:3 [ATK:3/HP:0]
// - Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever a friendly <b>Secret</b> is revealed,
//       gain +1 Durability.
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 2
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Weapon] - EX1_536 : Eaglehorn Bow")
{
    GameConfig config;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Eaglehorn Bow"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Snipe"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Chillwind Yeti"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 3);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 2);

    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 2);
}

// ----------------------------------------- SPELL - HUNTER
// [EX1_537] Explosive Shot - COST:5
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// - Spell School: Fire
// --------------------------------------------------------
// Text: Deal 5 damage to a minion and 2 damage
//       to adjacent ones.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - EX1_537 : Explosive Shot")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chillwind Yeti"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chillwind Yeti"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Explosive Shot"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Explosive Shot"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask(card2, nullptr, 1));
    CHECK_EQ(curField[0]->GetHealth(), 5);
    CHECK_EQ(curField[1]->GetHealth(), 12);
    CHECK_EQ(curField[2]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card2));
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 7);
    CHECK_EQ(curField[2]->GetHealth(), 3);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card5, card1));
    CHECK_EQ(curField[0]->GetHealth(), 5);
    CHECK_EQ(curField[1]->GetHealth(), 3);
}

// ----------------------------------------- SPELL - HUNTER
// [EX1_538] Unleash the Hounds - COST:3
// - Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: For each enemy minion,
//       summon a 1/1 Hound with <b>Charge</b>.
// --------------------------------------------------------
// PlayReq:
// - REQ_MINIMUM_ENEMY_MINIONS = 1
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
// RefTag:
// - CHARGE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - EX1_538 : Unleash the Hounds")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Unleash the Hounds"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card7 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card8 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card9 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Unleash the Hounds"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[0]->HasCharge(), true);
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[1]->HasCharge(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, PlayCardTask::Minion(card6));
    game.Process(opPlayer, PlayCardTask::Minion(card7));
    game.Process(opPlayer, PlayCardTask::Minion(card8));
    CHECK_EQ(opField.GetCount(), 7);

    game.Process(opPlayer, PlayCardTask::Spell(card9));
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 2);
}

// ---------------------------------------- MINION - HUNTER
// [EX1_543] King Krush - COST:9 [ATK:8/HP:8]
// - Race: Beast, Faction: Neutral, Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Charge</b>
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - CHARGE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - EX1_543 : King Krush")
{
    // Do nothing
}

// ----------------------------------------- SPELL - HUNTER
// [EX1_544] Flare - COST:1
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: All minions lose <b>Stealth</b>.
//       Destroy all enemy <b>Secrets</b>. Draw a card.
// --------------------------------------------------------
// RefTag:
// - STEALTH = 1
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - EX1_544 : Flare")
{
    GameConfig config;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Worgen Infiltrator"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Misdirection"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Noble Sacrifice"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Worgen Infiltrator"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Flare"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasStealth(), true);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curSecret->GetCount(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField[0]->HasStealth(), true);

    game.Process(opPlayer, PlayCardTask::Spell(card5));
    CHECK_EQ(curField[0]->HasStealth(), false);
    CHECK_EQ(opField[0]->HasStealth(), false);
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 7);
}

// ----------------------------------------- SPELL - HUNTER
// [EX1_549] Bestial Wrath - COST:1
// - Faction: Neutral, Set: Expert1, Rarity: Epic
// --------------------------------------------------------
// Text: Give a friendly Beast +2 Attack and <b>Immune</b> this turn.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_TARGET_WITH_RACE = 20
// - REQ_FRIENDLY_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - IMMUNE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - EX1_549 : Bestial Wrath")
{
    GameConfig config;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Bestial Wrath"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card2));
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 7);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card3));
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(opField[1]->GetAttack(), 3);
    CHECK_EQ(opField[1]->GetHealth(), 1);
    CHECK_EQ(opField[1]->IsImmune(), true);

    game.Process(opPlayer, AttackTask(card3, card1));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opField[1]->GetAttack(), 1);
    CHECK_EQ(opField[1]->GetHealth(), 1);
    CHECK_EQ(opField[1]->IsImmune(), false);
}

// ----------------------------------------- SPELL - HUNTER
// [EX1_554] Snake Trap - COST:2
// - Faction: Neutral, Set: Expert1, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Secret:</b> When one of your minions is attacked,
//       summon three 1/1 Snakes.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - EX1_554 : Snake Trap")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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
    const auto card7 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card8 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card9 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

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
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card7));
    game.Process(curPlayer, PlayCardTask::Minion(card8));
    game.Process(curPlayer, PlayCardTask::Minion(card9));
    CHECK_EQ(curField.GetCount(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, AttackTask(card5, curField[6]));
    CHECK_EQ(curSecret->GetCount(), 1);
    CHECK_EQ(curField.GetCount(), 6);
}

// ----------------------------------------- SPELL - HUNTER
// [EX1_609] Snipe - COST:2
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Secret:</b> After your opponent plays a minion,
//       deal 4 damage to it.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - EX1_609 : Snipe")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Snipe"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Snipe"));
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
    CHECK_EQ(opField[0]->GetHealth(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card4));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card6));
    CHECK(card6->isDestroyed);

    game.Process(opPlayer, PlayCardTask::Minion(card7));
    CHECK_EQ(opField[1]->GetHealth(), 5);
}

// ----------------------------------------- SPELL - HUNTER
// [EX1_610] Explosive Trap - COST:2
// - Faction: Neutral, Set: Expert1, Rarity: Common
// - Spell School: Fire
// --------------------------------------------------------
// Text: <b>Secret:</b> When your hero is attacked,
//       deal 2 damage to all enemies.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - EX1_610 : Explosive Trap")
{
    GameConfig config;
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
// [EX1_611] Freezing Trap - COST:2
// - Faction: Neutral, Set: Expert1, Rarity: Common
// - Spell School: Frost
// --------------------------------------------------------
// Text: <b>Secret:</b> When an enemy minion attacks,
//       return it to its owner's hand. It costs (2) more.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - EX1_611 : Freezing Trap")
{
    GameConfig config;
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
// [EX1_617] Deadly Shot - COST:3
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: Destroy a random enemy minion.
// --------------------------------------------------------
// PlayReq:
// - REQ_MINIMUM_ENEMY_MINIONS = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - EX1_617 : Deadly Shot")
{
    GameConfig config;
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

// ------------------------------------------- SPELL - MAGE
// [CS2_028] Blizzard - COST:6
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// - Spell School: Frost
// --------------------------------------------------------
// Text: Deal 2 damage to all enemy minions
//       and <b>Freeze</b> them.
// --------------------------------------------------------
// GameTag:
// - FREEZE = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - CS2_028 : Blizzard")
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
// [CS2_031] Ice Lance - COST:1
// - Faction: Neutral, Set: Expert1, Rarity: Common
// - Spell School: Frost
// --------------------------------------------------------
// Text: <b>Freeze</b> a character.
//       If it was already <b>Frozen</b>, deal 4 damage instead.
// --------------------------------------------------------
// GameTag:
// - FREEZE = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - CS2_031 : Ice Lance")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Ice Lance"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Ice Lance"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Ice Lance"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Ice Lance"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Bloodmage Thalnos"));
    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ancient Watcher"));
    const auto card7 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ancient Watcher"));

    game.Process(curPlayer, PlayCardTask::Minion(card6));
    game.Process(curPlayer, PlayCardTask::Minion(card7));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card1, card6));
    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card7));
    CHECK_EQ(curField[0]->IsFrozen(), true);
    CHECK_EQ(curField[1]->IsFrozen(), true);
    CHECK_EQ(curField[0]->GetDamage(), 0);
    CHECK_EQ(curField[1]->GetDamage(), 0);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card6));
    CHECK_EQ(curField[0]->GetDamage(), 4);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card7));
    CHECK_EQ(card7->isDestroyed, true);
}

// ------------------------------------------- SPELL - MAGE
// [EX1_179] Icicle - COST:2
// - Set: Expert1, Rarity: Epic
// - Spell School: Frost
// --------------------------------------------------------
// Text: Deal 2 damage to a minion.
//       If it's <b>Frozen</b>, draw a card.
// --------------------------------------------------------
// PlayReq:
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
// RefTag:
// - FREEZE = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - EX1_179 : Icicle")
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
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Icicle"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Icicle"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Ice Lance"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chillwind Yeti"));

    game.Process(curPlayer, PlayCardTask::Minion(card4));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card1, card4));
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(opHand.GetCount(), 8);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card4));
    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card4));
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[0]->IsFrozen(), true);
    CHECK_EQ(opHand.GetCount(), 7);
}

// ------------------------------------------- SPELL - MAGE
// [EX1_180] Tome of Intellect - COST:1
// - Set: Expert1, Rarity: Common
// - Spell School: Arcane
// --------------------------------------------------------
// Text: Add a random Mage spell to your hand.
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - EX1_180 : Tome of Intellect")
{
    GameConfig config;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Tome of Intellect"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand[4]->card->GetCardClass(), CardClass::MAGE);
}

// ------------------------------------------ MINION - MAGE
// [EX1_274] Ethereal Arcanist - COST:4 [ATK:3/HP:3]
// - Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: If you control a <b>Secret</b> at the end of your turn,
//       gain +2/+2.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - EX1_274 : Ethereal Arcanist")
{
    GameConfig config;
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
    auto& curSecret = *(curPlayer->GetSecretZone());
    auto& opSecret = *(opPlayer->GetSecretZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Ethereal Arcanist"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Counterspell"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Counterspell"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Counterspell"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_FALSE(curSecret.IsEmpty());

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(opPlayer, PlayCardTask::Spell(card3));
    CHECK(curSecret.IsEmpty());
    CHECK(opSecret.IsEmpty());

    game.Process(opPlayer, PlayCardTask::Spell(card4));
    CHECK_FALSE(opSecret.IsEmpty());

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 5);
}

// ------------------------------------------- SPELL - MAGE
// [EX1_275] Cone of Cold - COST:3
// - Faction: Neutral, Set: Expert1, Rarity: Common
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
TEST_CASE("[Mage : Spell] - EX1_275 : Cone of Cold")
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
// [EX1_279] Pyroblast - COST:10
// - Faction: Neutral, Set: Expert1, Rarity: Epic
// - Spell School: Fire
// --------------------------------------------------------
// Text: Deal 10 damage.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - EX1_279 : Pyroblast")
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
// [EX1_287] Counterspell - COST:3
// - Faction: Neutral, Set: Expert1, Rarity: Rare
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
TEST_CASE("[Mage : Spell] - EX1_287 : Counterspell")
{
    GameConfig config;
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
// [EX1_289] Ice Barrier - COST:3
// - Faction: Neutral, Set: Expert1, Rarity: Common
// - Spell School: Frost
// --------------------------------------------------------
// Text: <b>Secret:</b> When your hero is attacked,
//       gain 8 Armor.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - EX1_289 : Ice Barrier")
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
// [EX1_294] Mirror Entity - COST:3
// - Faction: Neutral, Set: Expert1, Rarity: Common
// - Spell School: Arcane
// --------------------------------------------------------
// Text: <b>Secret:</b> After your opponent plays a minion,
//       summon a copy of it.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - EX1_294 : Mirror Entity")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::PRIEST;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mirror Entity"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mirror Entity"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card7 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card8 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card9 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Injured Blademaster"));
    const auto card10 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Injured Blademaster"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card9));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(curField[1]->GetHealth(), 3);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::Minion(card5));
    game.Process(curPlayer, PlayCardTask::Minion(card6));
    CHECK_EQ(curField.GetCount(), 5);
    game.Process(curPlayer, PlayCardTask::Minion(card7));
    CHECK_EQ(curField.GetCount(), 6);
    game.Process(curPlayer, PlayCardTask::Minion(card8));
    CHECK_EQ(curField.GetCount(), 7);
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card10));
    CHECK_EQ(curField.GetCount(), 7);
    CHECK_EQ(curSecret->GetCount(), 1);
}

// ------------------------------------------- SPELL - MAGE
// [EX1_295] Ice Block - COST:3
// - Faction: Neutral, Set: Expert1, Rarity: Epic
// - Spell School: Frost
// --------------------------------------------------------
// Text: <b>Secret:</b> When your hero takes fatal damage,
//       prevent it and become <b>Immune</b> this turn.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
// RefTag:
// - IMMUNE = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - EX1_295 : Ice Block")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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

    auto curSecret = curPlayer->GetSecretZone();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ice Block"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curSecret->GetCount(), 1);

    curPlayer->GetHero()->SetDamage(25);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card2, curPlayer->GetHero()));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(curPlayer->GetHero()->IsImmune(), true);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->IsImmune(), false);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 5);
}

// ------------------------------------------ MINION - MAGE
// [EX1_559] Archmage Antonidas - COST:7 [ATK:5/HP:7]
// - Faction: Neutral, Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: Whenever you cast a spell,
//       add a 'Fireball' spell to your hand.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - EX1_559 : Archmage Antonidas")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Archmage Antonidas"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curHand[5]->card->name, "Fireball");

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(curHand[5], opPlayer->GetHero()));
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curHand[5]->card->name, "Fireball");
}

// ------------------------------------------- SPELL - MAGE
// [EX1_594] Vaporize - COST:3
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// - Spell School: Fire
// --------------------------------------------------------
// Text: <b>Secret:</b> When a minion attacks your hero,
//       destroy it.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - EX1_594 : Vaporize")
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

    auto curSecret = curPlayer->GetSecretZone();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Vaporize"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, AttackTask(card2, curPlayer->GetHero()));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(opPlayer->GetFieldZone()->GetCount(), 0);
}

// ------------------------------------------ MINION - MAGE
// [EX1_608] Sorcerer's Apprentice - COST:4 [ATK:3/HP:2]
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: Your spells cost (1) less.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - EX1_608 : Sorcerer's Appretice")
{
    GameConfig config;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Sorcerer's Apprentice"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Sorcerer's Apprentice"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
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

// ------------------------------------------ MINION - MAGE
// [EX1_612] Kirin Tor Mage - COST:3 [ATK:4/HP:3]
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> The next <b>Secret</b>
//       you play this turn costs (0).
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - EX1_612 : Kirin Tor Mage")
{
    GameConfig config;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Kirin Tor Mage"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Kirin Tor Mage"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ice Barrier"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ice Barrier"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    CHECK_EQ(card3->GetCost(), 3);
    CHECK_EQ(card4->GetCost(), 3);
    CHECK_EQ(card5->GetCost(), 4);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card3->GetCost(), 0);
    CHECK_EQ(card4->GetCost(), 0);
    CHECK_EQ(card5->GetCost(), 4);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card5, opPlayer->GetHero()));
    CHECK_EQ(card3->GetCost(), 0);
    CHECK_EQ(card4->GetCost(), 0);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(card4->GetCost(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card4->GetCost(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(card4->GetCost(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card4->GetCost(), 3);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card4->GetCost(), 3);
}

// ------------------------------------------ MINION - MAGE
// [NEW1_012] Mana Wyrm - COST:1 [ATK:1/HP:2]
// - Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: Whenever you cast a spell, gain +1 Attack.
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - NEW1_012 : Mana Wyrm")
{
    GameConfig config;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByID("NEW1_012"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Lightning Bolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 1);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 24);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card4, curPlayer->GetHero()));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 27);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 18);
}

// ------------------------------------------- SPELL - MAGE
// [tt_010] Spellbender - COST:3
// - Faction: Neutral, Set: Expert1, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Secret:</b> When an enemy casts a spell on a minion,
//       summon a 1/3 as the new target.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - tt_010 : Spellbender")
{
    GameConfig config;
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

    auto curSecret = curPlayer->GetSecretZone();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Spellbender"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetFieldZone()->GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card2));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(curPlayer->GetFieldZone()->GetCount(), 1);
}

// ---------------------------------------- SPELL - PALADIN
// [EX1_130] Noble Sacrifice - COST:1
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Secret:</b> When an enemy attacks,
//       summon a 2/1 Defender as the new target.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - EX1_130 : Noble Sacrifice")
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

// ---------------------------------------- SPELL - PALADIN
// [EX1_132] Eye for an Eye - COST:1
// - Faction: Neutral, Set: Expert1, Rarity: Common
// - Spell School: Holy
// --------------------------------------------------------
// Text: <b>Secret:</b> When your hero takes damage,
//       deal that much damage to the enemy hero.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - EX1_132 : Eye for an Eye")
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

    auto curHero = curPlayer->GetHero();
    auto opHero = opPlayer->GetHero();
    auto curSecret = curPlayer->GetSecretZone();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Eye for an Eye"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Eye for an Eye"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fiery War Axe"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Mortal Strike"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Weapon(card3));
    game.Process(opPlayer, AttackTask(opHero, curHero));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(curHero->GetHealth(), 27);
    CHECK_EQ(opHero->GetHealth(), 27);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, curHero));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(curHero->GetHealth(), 23);
    CHECK_EQ(opHero->GetHealth(), 23);
}

// ---------------------------------------- SPELL - PALADIN
// [EX1_136] Redemption - COST:1
// - Faction: Neutral, Set: Expert1, Rarity: Common
// - Spell School: Holy
// --------------------------------------------------------
// Text: <b>Secret:</b> When a friendly minion dies,
//       return it to life with 1 Health.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - EX1_136 : Redemption")
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
    auto curSecret = curPlayer->GetSecretZone();
    auto opHero = opPlayer->GetHero();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Redemption"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Argent Protector"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fiery War Axe"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Weapon(card3));
    game.Process(opPlayer, AttackTask(opHero, curField[0]));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(curField[0]->GetHealth(), 1);
}

// ---------------------------------------- SPELL - PALADIN
// [EX1_184] Righteousness - COST:5
// - Set: Expert1, Rarity: Rare
// - Spell School: Holy
// --------------------------------------------------------
// Text: Give your minions <b>Divine Shield</b>.
// --------------------------------------------------------
// RefTag:
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - EX1_184 : Righteousness")
{
    GameConfig config;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Righteousness"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField[0]->HasDivineShield(), false);
    CHECK_EQ(curField[1]->HasDivineShield(), false);
    CHECK_EQ(curField[2]->HasDivineShield(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField[0]->HasDivineShield(), true);
    CHECK_EQ(curField[1]->HasDivineShield(), true);
    CHECK_EQ(curField[2]->HasDivineShield(), true);
}

// ----------------------------------------- SPELL - PALADIN
// [EX1_349] Divine Favor - COST:3
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// - Spell School: Holy
// --------------------------------------------------------
// Text: Draw cards until you have as many in hand
//       as your opponent.
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - EX1_349 : Divine Favor")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Divine Favor"));

    Generic::DrawCard(opPlayer, Cards::FindCardByName("Sense Demons"));
    Generic::DrawCard(opPlayer, Cards::FindCardByName("Sense Demons"));
    Generic::DrawCard(opPlayer, Cards::FindCardByName("Sense Demons"));
    Generic::DrawCard(opPlayer, Cards::FindCardByName("Sense Demons"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));

    CHECK_EQ(curPlayer->GetHandZone()->GetCount(),
             opPlayer->GetHandZone()->GetCount());
}

// ---------------------------------------- SPELL - PALADIN
// [EX1_354] Lay on Hands - COST:8
// - Faction: Neutral, Set: Expert1, Rarity: Epic
// - Spell School: Holy
// --------------------------------------------------------
// Text: Restore 8 Health. Draw 3 cards.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - EX1_354 : Lay on Hands")
{
    GameConfig config;
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

    curPlayer->GetHero()->SetDamage(9);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lay on Hands"));

    const auto curHandCount = curPlayer->GetHandZone()->GetCount();

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, curPlayer->GetHero()));

    CHECK_EQ(curHandCount + 2, curPlayer->GetHandZone()->GetCount());
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 29);
}

// ---------------------------------------- SPELL - PALADIN
// [EX1_355] Blessed Champion - COST:5
// - Set: Expert1, Rarity: Rare
// - Spell School: Holy
// --------------------------------------------------------
// Text: Double a minion's Attack.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - EX1_355 : Blessed Champion")
{
    GameConfig config;
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Blessed Champion"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Tirion Fordring"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField[0]->GetAttack(), 12);
}

// --------------------------------------- MINION - PALADIN
// [EX1_362] Argent Protector - COST:2 [ATK:3/HP:2]
// - Faction: Neutral, Set: Expert1, Rarity: Common
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
TEST_CASE("[Paladin : Minion] - EX1_362 : Argent Protector")
{
    GameConfig config;
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

// ---------------------------------------- SPELL - PALADIN
// [EX1_363] Blessing of Wisdom - COST:1
// - Set: Expert1, Rarity: Common
// - Spell School: Holy
// --------------------------------------------------------
// Text: Choose a minion. Whenever it attacks, draw a card.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - EX1_363 : Blessing of Wisdom")
{
    GameConfig config;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Blessing of Wisdom"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 4);

    game.Process(curPlayer, AttackTask(card2, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
}

// ------------------------------------------ SPELL - PALADIN
// [EX1_365] Holy Wrath - COST:5
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// - Spell School: Holy
// --------------------------------------------------------
// Text: Draw a card and deal damage equal to its Cost.
// --------------------------------------------------------
// GameTag:
// - AFFECTED_BY_SPELL_POWER = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - EX1_365 : Holy Wrath")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Holy Wrath"));

    CHECK_EQ(curHand.GetCount(), 5);
    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(curHand.GetCount(), 5);

    Entity* drawnCard = curHand[curHand.GetCount() - 1];
    const int cardCost = drawnCard->card->gameTags[GameTag::COST];
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30 - cardCost);
}

// --------------------------------------- WEAPON - PALADIN
// [EX1_366] Sword of Justice - COST:3 [ATK:1/HP:0]
// - Faction: Neutral, Set: Expert1, Rarity: Epic
// --------------------------------------------------------
// Text: After you summon a minion,
//       give it +1/+1 and this loses 1 Durability.
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 5
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Weapon] - EX1_366 : Sword of Justice")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sword of Justice"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 5);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 4);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[2]->GetAttack(), 2);
    CHECK_EQ(curField[2]->GetHealth(), 2);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField[3]->GetAttack(), 2);
    CHECK_EQ(curField[3]->GetHealth(), 2);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(curField[4]->GetAttack(), 2);
    CHECK_EQ(curField[4]->GetHealth(), 2);
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), false);
}

// ---------------------------------------- SPELL - PALADIN
// [EX1_379] Repentance - COST:1
// - Faction: Neutral, Set: Expert1, Rarity: Common
// - Spell School: Holy
// --------------------------------------------------------
// Text: <b>Secret:</b> After your opponent plays a minion,
//       reduce its Health to 1.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - EX1_379 : Repentance")
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

    auto curSecret = curPlayer->GetSecretZone();
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Repentance"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Grommash Hellscream"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(opField[0]->GetHealth(), 1);
}

// --------------------------------------- MINION - PALADIN
// [EX1_382] Aldor Peacekeeper - COST:3 [ATK:3/HP:3]
// - Faction: Neutral, Set: Expert1, Rarity: Rare
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
TEST_CASE("[Paladin : Minion] - EX1_382 : Aldor Peacekeeper")
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
// [EX1_383] Tirion Fordring - COST:8 [ATK:6/HP:6]
// - Faction: Neutral, Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Divine Shield</b>, <b>Taunt</b>
//       <b>Deathrattle:</b> Equip a 5/3 Ashbringer.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - DIVINE_SHIELD = 1
// - TAUNT = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - EX1_383 : Tirion Fordring")
{
    GameConfig config;
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
// [EX1_384] Avenging Wrath - COST:6
// - Faction: Neutral, Set: Expert1, Rarity: Epic
// - Spell School: Holy
// --------------------------------------------------------
// Text: Deal 8 damage randomly split among all enemies.
// --------------------------------------------------------
// GameTag:
// - ImmuneToSpellpower = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - EX1_384 : Avenging Wrath")
{
    GameConfig config;
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Avenging Wrath"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Avenging Wrath"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Bloodmage Thalnos"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    int totalHealth = opPlayer->GetHero()->GetHealth();
    totalHealth += opField[0]->GetHealth();
    CHECK_EQ(totalHealth, 42);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    totalHealth = opPlayer->GetHero()->GetHealth();
    totalHealth += opField[0]->GetHealth();
    CHECK_EQ(totalHealth, 34);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::Spell(card2));
    totalHealth = opPlayer->GetHero()->GetHealth();
    totalHealth += opField[0]->GetHealth();
    CHECK_EQ(totalHealth, 25);
}

// ---------------------------------------- SPELL - PALADIN
// [EX1_619] Equality - COST:2
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// - Spell School: Holy
// --------------------------------------------------------
// Text: Change the Health of all minions to 1.
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - EX1_619 : Equality")
{
    GameConfig config;
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

// ----------------------------------------- SPELL - PRIEST
// [CS1_129] Inner Fire - COST:1
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: Change a minion's Attack to be equal to its Health.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - CS1_129 : Inner Fire")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Inner Fire"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Divine Spirit"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Inner Fire"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Inner Fire"));
    const auto card5 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Northshire Cleric"));

    game.Process(curPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, curField[0]));
    CHECK_EQ(curField[0]->GetHealth(), curField[0]->GetAttack());

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, curField[0]));
    CHECK_EQ(curField[0]->GetHealth(), 6);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, curField[0]));
    CHECK_EQ(curField[0]->GetHealth(), curField[0]->GetAttack());

    curField[0]->SetDamage(1);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card4, curField[0]));
    CHECK_EQ(curField[0]->GetHealth(), curField[0]->GetAttack());
}

// ---------------------------------------- MINION - PRIEST
// [EX1_091] Cabal Shadow Priest - COST:6 [ATK:4/HP:5]
// - Faction: Neutral, Set: Expert1, Rarity: Epic
// - Spell School: Shadow
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Take control of an enemy minion
//       that has 2 or less Attack.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_TARGET_MAX_ATTACK = 2
// - REQ_MINION_TARGET = 0
// - REQ_ENEMY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - EX1_091 : Cabal Shadow Priest")
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Cabal Shadow Priest"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Cabal Shadow Priest"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card4));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card3));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(opField.GetCount(), 1);
}

// ---------------------------------------- MINION - PRIEST
// [EX1_195] Kul Tiran Chaplain - COST:2 [ATK:2/HP:3]
// - Set: Expert1, Rarity: Rare
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
TEST_CASE("[Priest : Minion] - EX1_195 : Kul Tiran Chaplain")
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

// ---------------------------------------- MINION - PRIEST
// [EX1_196] Scarlet Subjugator - COST:1 [ATK:2/HP:1]
// - Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give an enemy minion -2 Attack
//       until your next turn.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_ENEMY_TARGET = 0
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - EX1_196 : Scarlet Subjugator")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Scarlet Subjugator"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::MinionTarget(card2, card1));
    CHECK_EQ(curField[0]->GetAttack(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetAttack(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetAttack(), 3);
}

// ----------------------------------------- SPELL - PRIEST
// [EX1_197] Shadow Word: Ruin - COST:4
// - Set: Expert1, Rarity: Epic
// - Spell School: Shadow
// --------------------------------------------------------
// Text: Destroy all minions with 5 or more Attack.
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - EX1_197 : Shadow Word: Ruin")
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

// ---------------------------------------- MINION - PRIEST
// [EX1_198] Natalie Seline - COST:8 [ATK:8/HP:1]
// - Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy a minion and gain its Health.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - EX1_198 : Natalie Seline")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Natalie Seline"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 12);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetHealth(), 11);

    game.Process(opPlayer, PlayCardTask::MinionTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opField[0]->GetAttack(), 8);
    CHECK_EQ(opField[0]->GetHealth(), 11);
}

// ----------------------------------------- SPELL - PRIEST
// [EX1_332] Silence - COST:0
// - Faction: Neutral, Set: Expert1, Rarity: Common
// - Spell School: Shadow
// --------------------------------------------------------
// Text: <b>Silence</b> a minion.
// --------------------------------------------------------
// GameTag:
// - SILENCE = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - EX1_332 : Silence")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Silence"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Silence"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Leper Gnome"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->HasDeathrattle(), true);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(curField[0]->HasDeathrattle(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField[0]->GetSpellPower(), 5);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card4));
    CHECK_EQ(opField[0]->GetSpellPower(), 0);
}

// ----------------------------------------- SPELL - PRIEST
// [EX1_334] Shadow Madness - COST:3
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// - Spell School: Shadow
// --------------------------------------------------------
// Text: Gain control of an enemy minion with 3 or
//       less Attack until end of turn.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_ENEMY_TARGET = 0
// - REQ_NUM_MINION_SLOTS = 1
// - REQ_TARGET_MAX_ATTACK = 3
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - EX1_334 : Shadow Madness")
{
    GameConfig config;
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pit Lord"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Felguard"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Shadow Madness"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Shadow Madness"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card1));
    CHECK_EQ(opPlayer->GetRemainingMana(), 7);
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetAttack(), 3);
    CHECK_EQ(opField[0]->GetHealth(), 1);

    game.Process(opPlayer, AttackTask(card1, card3));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(opField.GetCount(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card5, card2));
    CHECK_EQ(opPlayer->GetRemainingMana(), 10);
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(opField.GetCount(), 0);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card5, card3));
    CHECK_EQ(opPlayer->GetRemainingMana(), 7);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(opField.GetCount(), 0);
}

// ---------------------------------------- MINION - PRIEST
// [EX1_335] Lightspawn - COST:3 [ATK:0/HP:4]
// - Race: Elemental, Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: This minion's Attack is always equal to its Health.
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - EX1_335 : Lightspawn")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lightspawn"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, AttackTask(card2, card1));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
}

// ----------------------------------------- SPELL - PRIEST
// [EX1_339] Thoughtsteal - COST:2
// - Faction: Neutral, Set: Expert1, Rarity: Common
// - Spell School: Shadow
// --------------------------------------------------------
// Text: Copy 2 cards in your opponent's deck and
//       add them to your hand.
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - EX1_339 : Thoughtsteal")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Thoughtsteal"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetRemainingMana(), 8);
    CHECK_EQ((curHand[0]->card->name == "Magma Rager" ||
              curHand[0]->card->name == "Wolfrider"),
             true);
    CHECK_EQ((curHand[1]->card->name == "Magma Rager" ||
              curHand[1]->card->name == "Wolfrider"),
             true);
}

// ---------------------------------------- MINION - PRIEST
// [EX1_341] Lightwell - COST:2 [ATK:0/HP:5]
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: At the start of your turn, restore 3 Health
//       to a damaged friendly character.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - EX1_341 : Lightwell")
{
    GameConfig config;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lightwell"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Northshire Cleric"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));

    curField[0]->SetDamage(4);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    const auto p1HandCount = curPlayer->GetHandZone()->GetCount();

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), p1HandCount + 2);
    CHECK_EQ(curField[0]->GetHealth(), 4);
}

// ----------------------------------------- SPELL - PRIEST
// [EX1_345] Mindgames - COST:4
// - Faction: Neutral, Set: Expert1, Rarity: Epic
// - Spell School: Shadow
// --------------------------------------------------------
// Text: Put a copy of a random minion from
//       your opponent's deck into the battlefield.
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - EX1_345 : Mindgames")
{
    GameConfig config;
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
    auto& opDeck = *(opPlayer->GetDeckZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mindgames"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mindgames"));

    CHECK_EQ(opDeck.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField[0]->card->name, "Magma Rager");
    CHECK_EQ(opDeck.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opDeck.GetCount(), 0);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->name, "Shadow of Nothing");
}

// ---------------------------------------- MINION - PRIEST
// [EX1_350] Prophet Velen - COST:7 [ATK:7/HP:7]
// - Faction: Neutral, Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: Double the damage and healing of
//       your spells and Hero Power.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - EX1_350 : Prophet Velen")
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
    curPlayer->GetHero()->SetDamage(10);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Prophet Velen"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mind Blast"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mind Blast"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Pyroblast"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Prophet Velen"));
    const auto card7 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Prophet Velen"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card6));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 20);

    game.Process(curPlayer, HeroPowerTask(curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 24);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card1));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 15);

    game.Process(curPlayer, HeroPowerTask(curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 26);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card7));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card5, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 2);
}

// ---------------------------------------- MINION - PRIEST
// [EX1_591] Auchenai Soulpriest - COST:4 [ATK:3/HP:5]
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: Your cards and powers that restore Health
//       now deal damage instead.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - EX1_591 : Auchenai Soulpriest")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Auchenai Soulpriest"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Circle of Healing"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField[0]->GetHealth(), 5);

    game.Process(opPlayer, HeroPowerTask(curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 28);

    game.Process(opPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(opField[0]->GetHealth(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask(card2));
    CHECK_EQ(opField.GetCount(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
}

// ----------------------------------------- SPELL - PRIEST
// [EX1_621] Circle of Healing - COST:0
// - Set: Expert1, Rarity: Common
// - Spell School: Holy
// --------------------------------------------------------
// Text: Restore 4 Health to all minions.
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - EX1_621 : Circle of Healing")
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Bloodmage Thalnos"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Circle of Healing"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, AttackTask(card5, card3));
    game.Process(opPlayer, AttackTask(card4, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(opField[0]->GetHealth(), 6);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField[0]->GetHealth(), 7);
    CHECK_EQ(opField[0]->GetHealth(), 7);
}

// ---------------------------------------- MINION - PRIEST
// [EX1_623] Temple Enforcer - COST:5 [ATK:5/HP:6]
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give a friendly minion +3 Health.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_FRIENDLY_TARGET = 0
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - EX1_623 : Temple Enforcer")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Temple Enforcer"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetRemainingMana(), 7);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(curPlayer->GetRemainingMana(), 2);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetAttack(), 5);
    CHECK_EQ(curField[1]->GetHealth(), 6);
}

// ----------------------------------------- SPELL - PRIEST
// [EX1_624] Holy Fire - COST:6
// - Faction: Priest, Set: Expert1, Rarity: Rare
// - Spell School: Holy
// --------------------------------------------------------
// Text: Deal 5 damage. Restore 5 Health to your hero.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - EX1_624 : Holy Fire")
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
    curPlayer->GetHero()->SetDamage(8);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Holy Fire"));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 27);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 25);
}

// ----------------------------------------- SPELL - PRIEST
// [EX1_625] Shadowform - COST:2
// - Faction: Priest, Set: Expert1, Rarity: Epic
// - Spell School: Shadow
// --------------------------------------------------------
// Text: Your Hero Power becomes 'Deal 2 damage'.
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - EX1_625 : Shadowform")
{
    GameConfig config;
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

    Hero* opHero = opPlayer->GetHero();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shadowform"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shadowform"));

    game.Process(curPlayer, HeroPowerTask(opHero));
    CHECK_EQ(opHero->GetHealth(), 29);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHero()->heroPower->card->name, "Mind Spike");

    game.Process(curPlayer, HeroPowerTask(opHero));
    CHECK_EQ(opHero->GetHealth(), 27);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curPlayer->GetHero()->heroPower->card->name, "Mind Spike");

    game.Process(curPlayer, HeroPowerTask(opHero));
    CHECK_EQ(opHero->GetHealth(), 25);
}

// ----------------------------------------- SPELL - PRIEST
// [EX1_626] Mass Dispel - COST:4
// - Set: Expert1, Rarity: Rare
// - Spell School: Holy
// --------------------------------------------------------
// Text: <b>Silence</b> all enemy minions. Draw a card.
// --------------------------------------------------------
// GameTag:
// - SILENCE = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - EX1_626 : Mass Dispel")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mass Dispel"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Bloodmage Thalnos"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Bloodmage Thalnos"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    auto p1HandCount = curPlayer->GetHandZone()->GetCount();

    game.Process(curPlayer, PlayCardTask::Spell(card1));

    CHECK_EQ(p1HandCount, curPlayer->GetHandZone()->GetCount());

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    const auto p2HandCount = opPlayer->GetHandZone()->GetCount();

    game.Process(opPlayer, PlayerTasks::AttackTask(card3, card2));

    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), p1HandCount + 1);
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), p2HandCount);
}

// ------------------------------------------ SPELL - ROGUE
// [CS2_073] Cold Blood - COST:1
// - Faction: Neutral, Set: Expert1, Rarity: Common
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
TEST_CASE("[Rogue : Spell] - CS2_073 : Cold Blood")
{
    GameConfig config;
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
// [CS2_233] Blade Flurry - COST:2
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: Destroy your weapon and deal its damage
//       to all enemies.
// --------------------------------------------------------
// GameTag:
// - AFFECTED_BY_SPELL_POWER = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_WEAPON_EQUIPPED = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - CS2_233 : Blade Flurry")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Leper Gnome"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Blade Flurry"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Blade Flurry"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Dalaran Mage"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(opPlayer, HeroPowerTask());
    CHECK_EQ(opPlayer->GetHero()->HasWeapon(), true);

    game.Process(opPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(opPlayer->GetHero()->HasWeapon(), false);
    CHECK_EQ(curField.GetCount(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(curField[0]->GetHealth(), 12);

    game.Process(opPlayer, HeroPowerTask());
    CHECK_EQ(opPlayer->GetHero()->HasWeapon(), true);

    game.Process(opPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(opPlayer->GetHero()->HasWeapon(), false);
    CHECK_EQ(curField[0]->GetHealth(), 10);
}

// ------------------------------------------ SPELL - ROGUE
// [EX1_124] Eviscerate - COST:2
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: Deal 2 damage. <b>Combo:</b> Deal 4 damage instead.
// --------------------------------------------------------
// GameTag:
// - COMBO = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - EX1_124 : Eviscerate")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Eviscerate"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Eviscerate"));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 24);
}

// ------------------------------------------ SPELL - ROGUE
// [EX1_126] Betrayal - COST:2
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: Force an enemy minion to deal its damage
//       to the minions next to it.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_ENEMY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - EX1_126 : Betrayal")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Betrayal"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Betrayal"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Betrayal"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetHealth(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[2]->GetHealth(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card2));
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 7);
    CHECK_EQ(curField[2]->GetHealth(), 1);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card5, card1));
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[2]->GetHealth(), 1);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card6, card3));
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(card2->isDestroyed, true);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);
}

// ------------------------------------------ SPELL - ROGUE
// [EX1_128] Conceal - COST:1
// - Faction: Neutral, Set: Expert1, Rarity: Common
// - Spell School: Shadow
// --------------------------------------------------------
// Text: Give your minions <b>Stealth</b> until your next turn.
// --------------------------------------------------------
// RefTag:
// - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - EX1_128 : Conceal")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Conceal"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Patient Assassin"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));

    game.Process(curPlayer, PlayCardTask::Spell(card1));

    CHECK_EQ(card2->GetGameTag(GameTag::STEALTH), 1);
    CHECK_EQ(card3->GetGameTag(GameTag::STEALTH), 1);
    CHECK_EQ(card4->GetGameTag(GameTag::STEALTH), 1);

    game.Process(curPlayer, AttackTask(card3, opPlayer->GetHero()));

    CHECK_EQ(card2->GetGameTag(GameTag::STEALTH), 1);
    CHECK_EQ(card3->GetGameTag(GameTag::STEALTH), 0);
    CHECK_EQ(card4->GetGameTag(GameTag::STEALTH), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->GetGameTag(GameTag::STEALTH), 1);
    CHECK_EQ(card3->GetGameTag(GameTag::STEALTH), 0);
    CHECK_EQ(card4->GetGameTag(GameTag::STEALTH), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->GetGameTag(GameTag::STEALTH), 1);
    CHECK_EQ(card3->GetGameTag(GameTag::STEALTH), 0);
    CHECK_EQ(card4->GetGameTag(GameTag::STEALTH), 0);
}

// ----------------------------------------- MINION - ROGUE
// [EX1_131] Defias Ringleader - COST:2 [ATK:2/HP:2]
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Combo:</b> Summon a 2/1 Defias Bandit.
// --------------------------------------------------------
// GameTag:
// - COMBO = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - EX1_131 : Defias Ringleader")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Defias Ringleader"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Defias Ringleader"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(curField[2]->GetAttack(), 2);
    CHECK_EQ(curField[2]->GetHealth(), 1);
}

// ----------------------------------------- WEAPON - ROGUE
// [EX1_133] Perdition's Blade - COST:3 [ATK:2/HP:0]
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 1 damage.
//       <b>Combo:</b> Deal 2 instead.
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 2
// - BATTLECRY = 1
// - COMBO = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Weapon] - EX1_133 : Perdition's Blade")
{
    GameConfig config;
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Perdition's Blade"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Perdition's Blade"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("SI:7 Agent"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::WeaponTarget(card1, card3));
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::WeaponTarget(card2, card3));
    CHECK_EQ(opField.GetCount(), 0);
}

// ----------------------------------------- MINION - ROGUE
// [EX1_134] SI:7 Agent - COST:3 [ATK:3/HP:3]
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Combo:</b> Deal 2 damage.
// --------------------------------------------------------
// GameTag:
// - COMBO = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_FOR_COMBO = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - EX1_134 : SI:7 Agent")
{
    GameConfig config;
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
// [EX1_137] Headcrack - COST:3
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: Deal 2 damage to the enemy hero.
//       <b>Combo:</b> Return this to your hand next turn.
// --------------------------------------------------------
// GameTag:
// - COMBO = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - EX1_137 : Headcrack")
{
    GameConfig config;
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

    auto& curHand = *(curPlayer->GetHandZone());
    auto opHero = opPlayer->GetHero();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Headcrack"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Headcrack"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Bloodmage Thalnos"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(opHero->GetHealth(), 28);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 25);
    CHECK_EQ(curHand.GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Headcrack");
}

// ------------------------------------------ SPELL - ROGUE
// [EX1_144] Shadowstep - COST:0
// - Faction: Neutral, Set: Expert1, Rarity: Common
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
TEST_CASE("[Rogue : Spell] - EX1_144 : Shadowstep")
{
    GameConfig config;
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
// [EX1_145] Preparation - COST:0
// - Faction: Neutral, Set: Expert1, Rarity: Epic
// --------------------------------------------------------
// Text: The next spell you cast this turn costs (2) less.
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - EX1_145 : Preparation")
{
    GameConfig config;
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

// ------------------------------------------ SPELL - ROGUE
// [EX1_182] Pilfer - COST:1
// - Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: Add a random card from another class to your hand
//       <i>(from your opponent's class)</i>.
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - EX1_182 : Pilfer")
{
    GameConfig config;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pilfer"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pilfer"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand[5]->card->GetCardClass(), CardClass::PALADIN);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curHand[5]->card->GetCardClass(), CardClass::PALADIN);
}

// ----------------------------------------- MINION - ROGUE
// [EX1_522] Patient Assassin - COST:2 [ATK:1/HP:2]
// - Faction: Neutral, Set: Expert1, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Stealth</b>
//       <b>Poisonous</b>
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// - POISONOUS = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - EX1_522 : Patient Assassin")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Patient Assassin"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Chillwind Yeti"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(card1, card2));

    CHECK(card2->isDestroyed);
}

// ----------------------------------------- MINION - ROGUE
// [EX1_613] Edwin VanCleef - COST:3 [ATK:2/HP:2]
// - Faction: Neutral, Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Combo:</b> Gain +2/+2 for each other card
//       you've played this turn.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - COMBO = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - EX1_613 : Edwin VanCleef")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Edwin VanCleef"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Edwin VanCleef"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Edwin VanCleef"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 4);

    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[2]->GetAttack(), 6);
    CHECK_EQ(curField[2]->GetHealth(), 6);
}

// ----------------------------------------- MINION - ROGUE
// [NEW1_005] Kidnapper - COST:6 [ATK:5/HP:3]
// - Faction: Neutral, Set: Expert1, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Combo:</b> Return a minion to its owner's hand.
// --------------------------------------------------------
// GameTag:
// - COMBO = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_FOR_COMBO = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - NEW1_005 : Kidnapper")
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

    auto& opField = *(opPlayer->GetFieldZone());
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Kidnapper"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Kidnapper"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 7);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card3, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 7);
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 6);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card4, card5));
    CHECK_EQ(opField.GetCount(), 0);
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 7);
}

// ----------------------------------------- MINION - ROGUE
// [NEW1_014] Master of Disguise - COST:4 [ATK:4/HP:4]
// - Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give a friendly minion <b>Stealth</b>
//       until your next turn.
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
// RefTag:
// - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - NEW1_014 : Master of Disguise")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Master of Disguise"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->HasStealth(), false);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(curField[0]->HasStealth(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->HasStealth(), false);
}

// ----------------------------------------- SPELL - SHAMAN
// [CS2_038] Ancestral Spirit - COST:2
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: Give a minion "<b>Deathrattle:</b> Resummon this minion."
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - CS2_038 : Ancestral Spirit")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Magma Rager"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Ancestral Spirit"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Murloc Raider"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("River Crocolisk"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Murloc Raider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));

    CHECK_EQ(opField[0]->card->name, "Murloc Raider");
    CHECK_EQ(opField[1]->card->name, "River Crocolisk");
    CHECK_EQ(opField[2]->card->name, "Murloc Raider");

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card4));
    CHECK_EQ(opField[1]->appliedEnchantments.size(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(card1, card4));
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opField.GetCount(), 3);
    CHECK_EQ(opField[1]->card->name, "River Crocolisk");
    CHECK_FALSE(opField[1]->HasDeathrattle());
}

// ----------------------------------------- SPELL - SHAMAN
// [CS2_053] Far Sight - COST:3
// - Faction: Neutral, Set: Expert1, Rarity: Epic
// --------------------------------------------------------
// Text: Draw a card. That card costs (3) less.
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - CS2_053 : Far Sight")
{
    GameConfig config;
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
// [EX1_238] Lightning Bolt - COST:1
// - Faction: Neutral, Set: Expert1, Rarity: Common
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
TEST_CASE("[Shaman : Spell] - EX1_238 : Lightning Bolt")
{
    GameConfig config;
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
// [EX1_241] Lava Burst - COST:3
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// - Spell School: Fire
// --------------------------------------------------------
// Text: Deal 5 damage. <b>Overload:</b> (2)
// --------------------------------------------------------
// GameTag:
// - OVERLOAD = 2
// - OVERLOAD_OWED = 2
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - EX1_241 : Lava Burst")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lava Burst"));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 25);
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
// [EX1_243] Dust Devil - COST:1 [ATK:3/HP:1]
// - Race: Elemental, Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Windfury</b>. <b>Overload:</b> (2)
// --------------------------------------------------------
// GameTag:
// - OVERLOAD = 2
// - OVERLOAD_OWED = 2
// - WINDFURY = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - EX1_243 : Dust Devil")
{
    // Do nothing
}

// ----------------------------------------- SPELL - SHAMAN
// [EX1_245] Earth Shock - COST:1
// - Faction: Neutral, Set: Expert1, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: <b>Silence</b> a minion, then deal 1 damage to it.
// --------------------------------------------------------
// GameTag:
// - SILENCE = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - EX1_245 : Earth Shock")
{
    GameConfig config;
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

    const auto& curField = *(curPlayer->GetFieldZone());
    const auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Bloodmage Thalnos"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Earth Shock"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    const int curHandCount = curHand.GetCount();

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));

    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(curHand.GetCount(), curHandCount);
}

// ---------------------------------------- WEAPON - SHAMAN
// [EX1_247] Stormforged Axe - COST:2 [ATK:2/HP:0]
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Overload:</b> (1)
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 3
// - OVERLOAD = 1
// - OVERLOAD_OWED = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Weapon] - EX1_247 : Stormforged Axe")
{
    // Do nothing
}

// ----------------------------------------- SPELL - SHAMAN
// [EX1_248] Feral Spirit - COST:3
// - Faction: Neutral, Set: Expert1, Rarity: Rare
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
TEST_CASE("[Shaman : Spell] - EX1_248 : Feral Spirit")
{
    GameConfig config;
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

// ---------------------------------------- MINION - SHAMAN
// [EX1_250] Earth Elemental - COST:5 [ATK:7/HP:8]
// - Race: Elemental, Faction: Neutral, Set: Expert1, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b><b>Overload</b>:</b> (2)
// --------------------------------------------------------
// GameTag:
// - OVERLOAD = 2
// - OVERLOAD_OWED = 2
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - EX1_250 : Earth Elemental")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Earth Elemental"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[0]->GetAttack(), 7);
    CHECK_EQ(curField[0]->GetHealth(), 8);

    CHECK_EQ(curPlayer->GetRemainingMana(), 5);
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

// ----------------------------------------- SPELL - SHAMAN
// [EX1_251] Forked Lightning - COST:1
// - Faction: Neutral, Set: Expert1, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: Deal 2 damage to 2 random enemy minions.
//       <b>Overload:</b> (2)
// --------------------------------------------------------
// GameTag:
// - OVERLOAD = 2
// - OVERLOAD_OWED = 2
// --------------------------------------------------------
// PlayReq:
// - REQ_MINIMUM_ENEMY_MINIONS = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - EX1_251 : Forked Lightning")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Forked Lightning"));
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
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(opField[0]->GetHealth(), 5);
    CHECK_EQ(opField[1]->GetHealth(), 5);
    CHECK_EQ(curPlayer->GetRemainingMana(), 9);
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
// [EX1_258] Unbound Elemental - COST:3 [ATK:3/HP:4]
// - Race: Elemental, Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: After you play a card with <b>Overload</b>,
//       gain +1/+1.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
// RefTag:
// - OVERLOAD = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - EX1_258 : Unbound Elemental")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Unbound Elemental"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Earth Elemental"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Feral Spirit"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 4);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 6);
}

// ----------------------------------------- SPELL - SHAMAN
// [EX1_259] Lightning Storm - COST:3
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// - Spell School: Nature
// --------------------------------------------------------
// Text: Deal 3 damage to all enemy minions.
//       <b>Overload:</b> (2)
// --------------------------------------------------------
// GameTag:
// - OVERLOAD = 2
// - OVERLOAD_OWED = 2
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - EX1_259 : Lightning Storm")
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

// ---------------------------------------- WEAPON - SHAMAN
// [EX1_567] Doomhammer - COST:5 [ATK:2/HP:0]
// - Faction: Neutral, Set: Expert1, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Windfury, Overload:</b> (2)
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 8
// - WINDFURY = 1
// - OVERLOAD = 2
// - OVERLOAD_OWED = 2
// --------------------------------------------------------
TEST_CASE("[Shaman : Weapon] - EX1_567 : Doomhammer")
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
// [EX1_575] Mana Tide Totem - COST:3 [ATK:0/HP:3]
// - Race: Totem, Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: At the end of your turn, draw a card.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - EX1_575 : Mana Tide Totem")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mana Tide Totem"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
}

// ---------------------------------------- MINION - SHAMAN
// [NEW1_010] Al'Akir the Windlord - COST:8 [ATK:3/HP:6]
// - Race: Elemental, Set: Expert1, Rarity: Legendary
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
TEST_CASE("[Shaman : Minion] - NEW1_010 : Al'Akir the Windlord")
{
    // Do nothing
}

// --------------------------------------- MINION - WARLOCK
// [CS2_059] Blood Imp - COST:1 [ATK:0/HP:1]
// - Race: Demon, Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Stealth</b>. At the end of your turn,
//       give another random friendly minion +1 Health.
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - CS2_059 : Blood Imp")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Blood Imp"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));

    int totalHealth = curField[1]->GetHealth();
    totalHealth += curField[2]->GetHealth();
    CHECK_EQ(totalHealth, 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    totalHealth = curField[1]->GetHealth();
    totalHealth += curField[2]->GetHealth();
    CHECK_EQ(totalHealth, 4);
}

// ---------------------------------------- SPELL - WARLOCK
// [EX1_181] Call of the Void - COST:1
// - Set: Expert1, Rarity: Common
// - Spell School: Shadow
// --------------------------------------------------------
// Text: Add a random Demon to your hand.
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - EX1_181 : Call of the Void")
{
    GameConfig config;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Call of the Void"));

    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Spell(card1));

    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->GetRace(), Race::DEMON);
}

// --------------------------------------- MINION - WARLOCK
// [EX1_185] Siegebreaker - COST:7 [ATK:5/HP:8]
// - Race: Demon, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       Your other Demons have +1 Attack.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - EX1_185 : Siegebreaker")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Siegebreaker"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Felguard"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Pyroblast"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 8);
    CHECK_EQ(curField[0]->HasTaunt(), true);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 8);
    CHECK_EQ(curField[1]->GetAttack(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 5);
}

// --------------------------------------- MINION - WARLOCK
// [EX1_301] Felguard - COST:3 [ATK:3/HP:5]
// - Race: Demon, Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Battlecry:</b> Destroy one of your Mana Crystals.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - EX1_301 : Felguard")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Felguard"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Felguard"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetTotalMana(), 9);
    CHECK_EQ(curPlayer->GetRemainingMana(), 7);
    CHECK_EQ(opPlayer->GetTotalMana(), 10);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetTotalMana(), 8);
    CHECK_EQ(curPlayer->GetRemainingMana(), 4);
    CHECK_EQ(opPlayer->GetTotalMana(), 10);
}

// ---------------------------------------- SPELL - WARLOCK
// [EX1_303] Shadowflame - COST:4
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// - Spell School: Shadow
// --------------------------------------------------------
// Text: Destroy a friendly minion and deal its Attack damage
//       to all enemy minions.
// --------------------------------------------------------
// GameTag:
// - AFFECTED_BY_SPELL_POWER = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_FRIENDLY_TARGET = 0
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - EX1_303 : Shadowflame")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chillwind Yeti"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chillwind Yeti"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Bloodmage Thalnos"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Chillwind Yeti"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Shadowflame"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::SpellTarget(card5, card3));
    CHECK_EQ(curField[0]->GetDamage(), 2);
    CHECK_EQ(curField[1]->GetDamage(), 2);
    CHECK_EQ(opField[0]->GetDamage(), 0);
}

// --------------------------------------- MINION - WARLOCK
// [EX1_304] Void Terror - COST:3 [ATK:3/HP:4]
// - Race: Demon, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy both adjacent minions
//       and gain their Attack and Health.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - EX1_304 : Void Terror")
{
    GameConfig config;
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
// [EX1_309] Siphon Soul - COST:5
// - Set: Expert1, Rarity: Rare
// - Spell School: Shadow
// --------------------------------------------------------
// Text: Destroy a minion. Restore 3 Health to your hero.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - EX1_309 : Siphon Soul")
{
    GameConfig config;
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

// --------------------------------------- MINION - WARLOCK
// [EX1_310] Doomguard - COST:5 [ATK:5/HP:7]
// - Race: Demon, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Charge</b>.
//       <b>Battlecry:</b> Discard two random cards.
// --------------------------------------------------------
// GameTag:
// - CHARGE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - EX1_310 : Doomguard")
{
    GameConfig config;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Doomguard"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 2);

    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 25);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 6);
}

// ---------------------------------------- SPELL - WARLOCK
// [EX1_312] Twisting Nether - COST:8
// - Set: Expert1, Rarity: Epic
// - Spell School: Shadow
// --------------------------------------------------------
// Text: Destroy all minions.
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - EX1_312 : Twisting Nether")
{
    GameConfig config;
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
// [EX1_313] Pit Lord - COST:4 [ATK:5/HP:6]
// - Race: Demon, Set: Expert1, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 5 damage to your hero.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - EX1_313 : Pit Lord")
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

    const auto card1 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Pit Lord"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 25);
}

// --------------------------------------- MINION - WARLOCK
// [EX1_315] Summoning Portal - COST:4 [ATK:0/HP:4]
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: Your minions cost (2) less, but not less than (1).
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - EX1_315 : Summoning Portal")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Pit Lord");
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Summoning Portal"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Summoning Portal"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Imp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Pit Lord"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    CHECK_EQ(card1->GetCost(), 4);
    CHECK_EQ(card2->GetCost(), 4);
    CHECK_EQ(card3->GetCost(), 1);
    CHECK_EQ(card4->GetCost(), 4);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card2->GetCost(), 2);
    CHECK_EQ(card3->GetCost(), 1);
    CHECK_EQ(card4->GetCost(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(card3->GetCost(), 1);
    CHECK_EQ(card4->GetCost(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card5, card1));
    CHECK_EQ(card3->GetCost(), 1);
    CHECK_EQ(card4->GetCost(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 7);
    CHECK_EQ(curHand[6]->GetCost(), 2);

    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shadowstep"));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card6, card4));
    CHECK_EQ(card4->GetCost(), 0);
}

// ---------------------------------------- SPELL - WARLOCK
// [EX1_316] Power Overwhelming - COST:1
// - Faction: Neutral, Set: Expert1, Rarity: Common
// - Spell School: Shadow
// --------------------------------------------------------
// Text: Give a friendly minion +4/+4 until end of turn.
//       Then, it dies. Horribly.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_FRIENDLY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - EX1_316 : Power Overwhelming")
{
    GameConfig config;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Power Overwhelming"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Goldshire Footman"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("King Mukla"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    game.Process(curPlayer, AttackTask(card2, card3));

    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(opPlayer->GetFieldZone()->GetCount(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetFieldZone()->GetCount(), 0);
}

// ---------------------------------------- SPELL - WARLOCK
// [EX1_317] Sense Demons - COST:3
// - Faction: Neutral, Set: Expert1, Rarity: Common
// - Spell School: Shadow
// --------------------------------------------------------
// Text: Draw 2 Demons from your deck.
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - EX1_317 : Sense Demons")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.skipMulligan = true;
    config.doShuffle = false;

    for (int i = 0; i < 7; ++i)
    {
        config.player1Deck[i] = Cards::FindCardByName("Blood Imp");
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sense Demons"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Sense Demons"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curDeck.GetCount(), 1);
    CHECK_EQ(curHand[5]->card->name, "Blood Imp");
    CHECK_EQ(curHand[6]->card->name, "Blood Imp");

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curDeck.GetCount(), 0);
    CHECK_EQ(curHand[6]->card->name, "Blood Imp");
    CHECK_EQ(curHand[7]->card->name, "Worthless Imp");
}

// ---------------------------------------- SPELL - WARLOCK
// [EX1_319] Flame Imp - COST:1
// - Race: Demon, Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 3 damage to your hero.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - EX1_319 : Flame Imp")
{
    GameConfig config;
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
// [EX1_320] Bane of Doom - COST:5
// - Faction: Neutral, Set: Expert1, Rarity: Epic
// - Spell School: Shadow
// --------------------------------------------------------
// Text: Deal 2 damage to a character.
//       If that kills it, summon a random Demon.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - EX1_320 : Bane of Doom")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Magma Rager"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chillwind Yeti"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Bane of Doom"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Bane of Doom"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card2));

    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(opField.GetCount(), 0);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card1));

    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->card->GetRace(), Race::DEMON);
}

// ---------------------------------------- SPELL - WARLOCK
// [EX1_596] Demonfire - COST:2
// - Faction: Neutral, Set: Expert1, Rarity: Common
// - Spell School: Fel
// --------------------------------------------------------
// Text: Deal 2 damage to a minion.
//       If it's a friendly Demon, give it +2/+2 instead.
// --------------------------------------------------------
// PlayReq:
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - EX1_596 : Demonfire")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Demonfire"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Demonfire"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Demonfire"));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Bloodmage Thalnos"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Felguard"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Felguard"));

    game.Process(curPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card6));
    CHECK_EQ(opField[0]->GetAttack(), 3);
    CHECK_EQ(opField[0]->GetHealth(), 5);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card5));
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 7);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card6));
    CHECK_EQ(opField[0]->GetAttack(), 3);
    CHECK_EQ(opField[0]->GetHealth(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card6));
    CHECK(opField.IsEmpty());
}

// ---------------------------------------- SPELL - WARRIOR
// [CS2_104] Rampage - COST:2
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: Give a damaged minion +3/+3.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_DAMAGED_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - CS2_104 : Rampage")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Rampage"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 7);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 6);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField[0]->GetAttack(), 9);
    CHECK_EQ(curField[0]->GetHealth(), 9);
}

// ---------------------------------------- SPELL - WARRIOR
// [EX1_391] Slam - COST:1
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: Deal 2 damage to a minion.
//       If it survives, draw a card.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - EX1_391 : Slam")
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
// [EX1_392] Battle Rage - COST:2
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: Draw a card for each damaged friendly character.
// --------------------------------------------------------
// PlayReq:
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - EX1_392 : Battle Rage")
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
    curPlayer->GetHero()->SetDamage(1);
    opPlayer->GetHero()->SetDamage(1);

    auto& opField = *(opPlayer->GetFieldZone());
    auto& curHand = *(curPlayer->GetHandZone());
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Battle Rage"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Battle Rage"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Chillwind Yeti"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, HeroPowerTask(card3));
    game.Process(opPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(opField[0]->GetDamage(), 1);
    CHECK_EQ(opHand.GetCount(), 8);
}

// --------------------------------------- MINION - WARRIOR
// [EX1_393] Amani Berserker - COST:2 [ATK:2/HP:3]
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: Has +3 Attack while damaged.
// --------------------------------------------------------
// GameTag:
// - ENRAGED = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - EX1_393 : Amani Berserker")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Amani Berserker"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 2);
}

// --------------------------------------- MINION - WARRIOR
// [EX1_398] Arathi Weaponsmith - COST:4 [ATK:3/HP:3]
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Equip a 2/2 weapon.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - EX1_398 : Arathi Weaponsmith")
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
        curPlayer, Cards::FindCardByName("Arathi Weaponsmith"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 2);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 2);
}

// --------------------------------------- MINION - WARRIOR
// [EX1_402] Armorsmith - COST:2 [ATK:1/HP:4]
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever a friendly minion takes damage,
//       gain 1 Armor.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - EX1_402 : Armorsmith")
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
// [EX1_407] Brawl - COST:5
// - Faction: Neutral, Set: Expert1, Rarity: Epic
// --------------------------------------------------------
// Text: Destroy all minions except one.
//       <i>(chosen randomly)</i>
// --------------------------------------------------------
// PlayReq:
// - REQ_MINIMUM_TOTAL_MINIONS = 2
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - EX1_407 : Brawl")
{
    GameConfig config;
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
// [EX1_408] Mortal Strike - COST:4
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: Deal 4 damage.
//       If you have 12 or less Health, deal 6 instead.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - EX1_408 : Mortal Strike")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mortal Strike"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mortal Strike"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, curPlayer->GetHero()));
    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 24);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 26);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card4, curPlayer->GetHero()));
    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card5, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 20);
}

// ---------------------------------------- SPELL - WARRIOR
// [EX1_409] Upgrade! - COST:1
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: If you have a weapon, give it +1/+1.
//       Otherwise equip a 1/3 weapon.
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - EX1_409 : Upgrade!")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Upgrade!"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Upgrade!"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), true);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 1);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 3);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 2);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 4);
}

// ---------------------------------------- SPELL - WARRIOR
// [EX1_410] Shield Slam - COST:1
// - Faction: Neutral, Set: Expert1, Rarity: Epic
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
TEST_CASE("[Warrior : Spell] - EX1_410 : Shield Slam")
{
    GameConfig config;
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
// [EX1_411] Gorehowl - COST:7 [ATK:7/HP:0]
// - Faction: Neutral, Set: Expert1, Rarity: Epic
// --------------------------------------------------------
// Text: Attacking a minion costs 1 Attack instead of 1 Durability.
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Weapon] - EX1_411 : Gorehowl")
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
// [EX1_414] Grommash Hellscream - COST:8 [ATK:4/HP:9]
// - Faction: Neutral, Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Charge</b>
//       Has +6 Attack while damaged.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - CHARGE = 1
// - ENRAGED = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - EX1_414 : Grommash Hellscream")
{
    GameConfig config;
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
// [EX1_603] Cruel Taskmaster - COST:2 [ATK:2/HP:3]
// - Faction: Neutral, Set: Expert1, Rarity: Common
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
TEST_CASE("[Warrior : Minion] - EX1_603 : Cruel Taskmaster")
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
// [EX1_604] Frothing Berserker - COST:3 [ATK:2/HP:4]
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever a minion takes damage, gain +1 Attack.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - EX1_604 : Frothing Berserker")
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

// ----------------------------------------- SPELL - WARRIOR
// [EX1_607] Inner Rage - COST:0
// - Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: Deal 1 damage to a minion and give it +2 Attack.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - EX1_607 : Inner Rage")
{
    GameConfig config;
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Inner Rage"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 7);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField[0]->GetAttack(), 8);
    CHECK_EQ(curField[0]->GetHealth(), 6);
}

// ----------------------------------------- SPELL - WARRIOR
// [NEW1_036] Commanding Shout - COST:2
// - Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: Your minions can't be reduced below 1 Health this turn.
//       Draw a card.
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - NEW1_036 : Commanding Shout")
{
    GameConfig config;
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
    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Gurubashi Berserker"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Commanding Shout"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Commanding Shout"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetAttack(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curHand.GetCount(), 8);

    game.Process(curPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetHealth(), 6);
    CHECK_EQ(curField[0]->GetAttack(), 8);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card4, card1));
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 11);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    game.Process(curPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 11);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK(curField.IsEmpty());
}

// --------------------------------------- MINION - NEUTRAL
// [CS1_069] Fen Creeper - COST:5 [ATK:3/HP:6]
// - Faction: Alliance, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CS1_069 : Fen Creeper")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [CS2_117] Earthen Ring Farseer - COST:3 [ATK:3/HP:3]
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Restore 3 Health.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CS2_117 : Earthen Ring Farseer")
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
    curPlayer->GetHero()->SetDamage(10);

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Earthen Ring Farseer"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Earthen Ring Farseer"));
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
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 23);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card3));
    CHECK_EQ(opField[0]->GetHealth(), 2);
}

// --------------------------------------- MINION - NEUTRAL
// [CS2_146] Southsea Deckhand - COST:1 [ATK:2/HP:1]
// - Race: Pirate, Faction: Alliance, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: Has <b>Charge</b> while you have a weapon equipped.
// --------------------------------------------------------
// RefTag:
// - CHARGE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CS2_146 : Southsea Deckhand")
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
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
        curPlayer, Cards::FindCardByName("Southsea Deckhand"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shadowstep"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetGameTag(GameTag::CHARGE), 0);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curField[0]->GetGameTag(GameTag::CHARGE), 1);

    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));
    CHECK_EQ(curField[0]->GetNumAttacksThisTurn(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(card1->GetZoneType(), ZoneType::HAND);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetGameTag(GameTag::CHARGE), 1);
    CHECK_EQ(curField[0]->IsExhausted(), false);
    CHECK_EQ(curField[0]->GetNumAttacksThisTurn(), 0);
}

// --------------------------------------- MINION - NEUTRAL
// [CS2_151] Silver Hand Knight - COST:5 [ATK:4/HP:4]
// - Faction: Alliance, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a 2/2 Squire.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CS2_151 : Silver Hand Knight")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Silver Hand Knight"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 2);
}

// --------------------------------------- MINION - NEUTRAL
// [CS2_161] Ravenholdt Assassin - COST:7 [ATK:7/HP:5]
// - Faction: Alliance, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Stealth</b>
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CS2_161 : Ravenholdt Assassin")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [CS2_169] Young Dragonhawk - COST:1 [ATK:1/HP:1]
// - Race: Beast, Faction: Horde, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Windfury</b>
// --------------------------------------------------------
// GameTag:
// - WINDFURY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CS2_169 : Young Dragonhawk")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [CS2_181] Injured Blademaster - COST:3 [ATK:4/HP:7]
// - Faction: Horde, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 4 damage to himself.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CS2_181 : Injured Blademaster")
{
    GameConfig config;
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
        curPlayer, Cards::FindCardByName("Injured Blademaster"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [CS2_188] Abusive Sergeant - COST:1 [ATK:1/HP:1]
// - Faction: Alliance, Set: Expert1, Rarity: Common
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
TEST_CASE("[Neutral : Minion] - CS2_188 : Abusive Sergeant")
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
// [CS2_203] Ironbeak Owl - COST:3 [ATK:2/HP:1]
// - Race: Beast, Faction: Horde, Set: Expert1, Rarity: Common
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
TEST_CASE("[Neutral : Minion] - CS2_203 : Ironbeak Owl")
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
// [CS2_221] Spiteful Smith - COST:5 [ATK:4/HP:6]
// - Faction: Horde, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Enrage:</b> Your weapon has +2 Attack.
// --------------------------------------------------------
// GameTag:
// - ENRAGED = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CS2_221 : Spiteful Smith")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Spiteful Smith"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Ironbeak Owl"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 3);

    game.Process(opPlayer, PlayCardTask::MinionTarget(card2, card1));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [CS2_227] Venture Co. Mercenary - COST:5 [ATK:7/HP:6]
// - Faction: Horde, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: Your minions cost (3) more.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CS2_227 : Venture Co. Mercenary")
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
        curPlayer, Cards::FindCardByName("Venture Co. Mercenary"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ironbeak Owl"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Malygos"));

    CHECK_EQ(card2->GetCost(), 3);
    CHECK_EQ(card3->GetCost(), 9);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card2->GetCost(), 6);
    CHECK_EQ(card3->GetCost(), 12);
}

// --------------------------------------- MINION - NEUTRAL
// [CS2_231] Wisp - COST:0 [ATK:1/HP:1]
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - CS2_231 : Wisp")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_001] Lightwarden - COST:1 [ATK:1/HP:2]
// - Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever a character is healed, gain +2 Attack.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_001 : Lightwarden")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lightwarden"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetAttack(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_002] The Black Knight - COST:6 [ATK:4/HP:5]
// - Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy an enemy minion
//       with <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_MINION_TARGET = 0
// - REQ_MUST_TARGET_TAUNTER = 0
// - REQ_ENEMY_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_002 : The Black Knight")
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Ironbark Protector"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Raider"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("The Black Knight"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::MinionTarget(card3, card2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(opField.GetCount(), 0);

    game.Process(opPlayer, PlayCardTask::MinionTarget(card3, card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(opField.GetCount(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_004] Young Priestess - COST:1 [ATK:2/HP:1]
// - Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: At the end of your turn,
//       give another random friendly minion +1 Health.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_004 : Young Priestess")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Young Priestess"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Young Priestess"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));

    int totalHealth = curField[0]->GetHealth();
    totalHealth += curField[1]->GetHealth();
    totalHealth += curField[2]->GetHealth();
    CHECK_EQ(totalHealth, 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    totalHealth = curField[0]->GetHealth();
    totalHealth += curField[1]->GetHealth();
    totalHealth += curField[2]->GetHealth();
    CHECK_EQ(totalHealth, 5);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_005] Big Game Hunter - COST:4 [ATK:4/HP:2]
// - Set: Expert1, Rarity: Epic
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
TEST_CASE("[Neutral : Minion] - EX1_005 : Big Game Hunter")
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
// [EX1_006] Alarm-o-Bot - COST:3 [ATK:0/HP:3]
// - Race: Mechanical, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: At the start of your turn,
//       swap this minion with a random one in your hand.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_006 : Alarm-o-Bot")
{
    GameConfig config;
    config.player1Class = CardClass::HUNTER;
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
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Alarm-o-Bot"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Loot Hoarder"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Acolyte of Pain"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->card->name, "Alarm-o-Bot");
    CHECK_EQ(curField[1]->card->name, "Loot Hoarder");
    CHECK_EQ(card3->zone->GetType(), ZoneType::HAND);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curHand[0]->card->name, "Alarm-o-Bot");
    CHECK_EQ(curField[0]->card->name, "Acolyte of Pain");
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_007] Acolyte of Pain - COST:3 [ATK:1/HP:3]
// - Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: Whenever this minion takes damage, draw a card.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_007 : Acolyte of Pain")
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
// [EX1_008] Argent Squire - COST:1 [ATK:1/HP:1]
// - Faction: Alliance, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Divine Shield</b>
// --------------------------------------------------------
// GameTag:
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_008 : Argent Squire")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_009] Angry Chicken - COST:1 [ATK:1/HP:1]
// - Race: Beast, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Enrage:</b> +5 Attack.
// --------------------------------------------------------
// GameTag:
// - ENRAGED = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_009 : Angry Chicken")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Angry Chicken"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Shattered Sun Cleric"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card1));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetAttack(), 7);
    CHECK_EQ(curField[0]->GetHealth(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_010] Worgen Infiltrator - COST:1 [ATK:2/HP:1]
// - Faction: Alliance, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Stealth</b>
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_010 : Worgen Infiltrator")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_012] Bloodmage Thalnos - COST:2 [ATK:1/HP:1]
// - Faction: Neutral, Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Spell Damage +1</b>
//       <b>Deathrattle:</b> Draw a card.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - SPELLPOWER = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_012 : Bloodmage Thalnos")
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
// [EX1_014] King Mukla - COST:3 [ATK:5/HP:5]
// - Race: Beast, Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give your opponent 2 Bananas.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_014 : King Mukla")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("King Mukla"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    auto& opHand = *(opPlayer->GetHandZone());
    auto& opField = *(opPlayer->GetFieldZone());

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opHand.GetCount(), 4);
    CHECK_EQ(opHand[2]->card->name, "Bananas");
    CHECK_EQ(opHand[3]->card->name, "Bananas");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField[0]->GetAttack(), 3);
    CHECK_EQ(opField[0]->GetHealth(), 1);

    game.Process(opPlayer, PlayCardTask::SpellTarget(opHand[1], card2));
    game.Process(opPlayer, PlayCardTask::SpellTarget(opHand[1], card2));
    CHECK_EQ(opField[0]->GetAttack(), 5);
    CHECK_EQ(opField[0]->GetHealth(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_016] Sylvanas Windrunner - COST:6 [ATK:5/HP:5]
// - Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Deathrattle:</b>
//       Take control of a random enemy minion.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_016 : Sylvanas Windrunner")
{
    GameConfig config;
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
        curPlayer, Cards::FindCardByName("Sylvanas Windrunner"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Magma Rager"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Oasis Snapjaw"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(card1, card2));
    CHECK_EQ(curPlayer->GetFieldZone()->GetCount(), 1);
    CHECK_EQ(opPlayer->GetFieldZone()->GetCount(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_017] Jungle Panther - COST:3 [ATK:4/HP:2]
// - Race: Beast, Faction: Horde, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Stealth</b>
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_017 : Jungle Panther")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_020] Scarlet Crusader - COST:3 [ATK:3/HP:1]
// - Faction: Alliance, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Divine Shield</b>
// --------------------------------------------------------
// GameTag:
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_020 : Scarlet Crusader")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_021] Thrallmar Farseer - COST:3 [ATK:2/HP:3]
// - Faction: Horde, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Windfury</b>
// --------------------------------------------------------
// GameTag:
// - WINDFURY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_021 : Thrallmar Farseer")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_023] Silvermoon Guardian - COST:4 [ATK:3/HP:3]
// - Faction: Horde, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Divine Shield</b>
// --------------------------------------------------------
// GameTag:
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_023 : Silvermoon Guardian")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_028] Stranglethorn Tiger - COST:5 [ATK:5/HP:5]
// - Race: Beast, Faction: Alliance, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Stealth</b>
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_028 : Stranglethorn Tiger")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_029] Leper Gnome - COST:1 [ATK:2/HP:1]
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Deal 2 damage to the enemy hero.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_029 : Leper Gnome")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Leper Gnome"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, AttackTask(card2, card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_032] Sunwalker - COST:6 [ATK:4/HP:5]
// - Faction: Alliance, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Divine Shield</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_032 : Sunwalker")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_033] Windfury Harpy - COST:6 [ATK:4/HP:5]
// - Faction: Alliance, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Windfury</b>
// --------------------------------------------------------
// GameTag:
// - WINDFURY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_033 : Windfury Harpy")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_043] Twilight Drake - COST:4 [ATK:4/HP:1]
// - Faction: Alliance, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Gain +1 Health
//       for each card in your hand.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_043 : Twilight Drake")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Twilight Drake"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 4);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_044] Questing Adventurer - COST:3 [ATK:2/HP:2]
// - Faction: Alliance, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever you play a card, gain +1/+1.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_044 : Questing Adventurer")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Questing Adventurer"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 4);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_045] Ancient Watcher - COST:2 [ATK:4/HP:5]
// - Faction: Alliance, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: Can't attack.
// --------------------------------------------------------
// GameTag:
// - CANT_ATTACK = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_045 : Ancient Watcher")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_046] Dark Iron Dwarf - COST:4 [ATK:4/HP:4]
// - Faction: Alliance, Set: Expert1, Rarity: Common
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
TEST_CASE("[Neutral : Minion] - EX1_046 : Dark Iron Dwarf")
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
// [EX1_048] Spellbreaker - COST:4 [ATK:4/HP:3]
// - Faction: Horde, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> <b>Silence</b> a minion.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_MINION_TARGET = 0
// - REQ_NONSELF_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - SILENCE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_048 : Spellbreaker")
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Spellbreaker"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Spellbreaker"));
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
// [EX1_049] Youthful Brewmaster - COST:2 [ATK:3/HP:2]
// - Faction: Alliance, Set: Expert1, Rarity: Common
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
TEST_CASE("[Neutral : Minion] - EX1_049 : Youthful Brewmaster")
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
// [EX1_050] Coldlight Oracle - COST:3 [ATK:2/HP:2]
// - Faction: Neutral, Set: Expert1, Rarity: Free
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Each player draws 2 cards.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_050 : Coldlight Oracle")
{
    GameConfig config;
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

    const auto card =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Coldlight Oracle"));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 7);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_055] Mana Addict - COST:2 [ATK:1/HP:3]
// - Faction: Alliance, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever you cast a spell, gain +2 Attack this turn.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_055 : Mana Addict")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mana Addict"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 1);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 24);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 18);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetAttack(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_057] Ancient Brewmaster - COST:4 [ATK:5/HP:4]
// - Faction: Alliance, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Return a friendly minion
//       from the battlefield to your hand.
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
TEST_CASE("[Neutral : Minion] - EX1_057 : Ancient Brewmaster")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Ancient Brewmaster"));
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
// [EX1_058] Sunfury Protector - COST:2 [ATK:2/HP:3]
// - Faction: Alliance, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give adjacent minions <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_058 : Sunfury Protector")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Sunfury Protector"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Sunfury Protector"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAUNT), 0);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAUNT), 1);
    CHECK_EQ(curField[1]->GetGameTag(GameTag::TAUNT), 0);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField[2]->GetGameTag(GameTag::TAUNT), 0);

    game.Process(curPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(curField[3]->GetGameTag(GameTag::TAUNT), 0);

    game.Process(curPlayer, PlayCardTask(card2, nullptr, 3));
    CHECK_EQ(curField[2]->GetGameTag(GameTag::TAUNT), 1);
    CHECK_EQ(curField[3]->GetGameTag(GameTag::TAUNT), 0);
    CHECK_EQ(curField[4]->GetGameTag(GameTag::TAUNT), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_059] Crazed Alchemist - COST:2 [ATK:2/HP:2]
// - Faction: Neutral, Set: Expert1, Rarity: Rare
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
TEST_CASE("[Neutral : Minion] - EX1_059 : Crazed Alchemist")
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
// [EX1_067] Argent Commander - COST:6 [ATK:4/HP:2]
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Charge</b>
//       <b>Divine Shield</b>
// --------------------------------------------------------
// GameTag:
// - DIVINE_SHIELD = 1
// - CHARGE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_067 : Argent Commander")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_076] Pint-Sized Summoner - COST:2 [ATK:2/HP:2]
// - Faction: Alliance, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: The first minion you play each turn costs (1) less.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_076 : Pint-Sized Summoner")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Pint-Sized Summoner"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodfen Raptor"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodfen Raptor"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card2->GetCost(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->GetCost(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(card3->GetCost(), 2);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_080] Secretkeeper - COST:1 [ATK:1/HP:2]
// - Faction: Alliance, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever a <b>Secret</b> is played, gain +1/+1.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_080 : Secretkeeper")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Secretkeeper"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Counterspell"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_082] Mad Bomber - COST:2 [ATK:3/HP:2]
// - Faction: Alliance, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 3 damage randomly split
//       between all other characters.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_082 : Mad Bomber")
{
    GameConfig config;
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
// [EX1_083] Tinkmaster Overspark - COST:3 [ATK:3/HP:3]
// - Faction: Alliance, Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Transform another random minion
//       into a 5/5 Devilsaur or a 1/1 Squirrel.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_083 : Tinkmaster Overspark")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Tinkmaster Overspark"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ((curField[0]->card->id == "EX1_tk28" ||
              curField[0]->card->id == "EX1_tk29"),
             true);
    CHECK_EQ((curField[0]->GetAttack() == 1 || curField[0]->GetAttack() == 5),
             true);
    CHECK_EQ((curField[0]->GetHealth() == 1 || curField[0]->GetHealth() == 5),
             true);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_085] Mind Control Tech - COST:3 [ATK:3/HP:3]
// - Faction: Alliance, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If your opponent has 4 or
//       more minions, take control of one at random.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_085 : Mind Control Tech")
{
    GameConfig config;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mind Control Tech"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card7 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card8 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card9 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Mind Control Tech"));
    const auto card10 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card11 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Stonetusk Boar"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(curField.GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card9));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, PlayCardTask::Minion(card10));
    game.Process(opPlayer, PlayCardTask::Minion(card11));
    CHECK_EQ(opField.GetCount(), 4);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card6));
    game.Process(curPlayer, PlayCardTask::Minion(card7));
    game.Process(curPlayer, PlayCardTask::Minion(card8));
    CHECK_EQ(curField.GetCount(), 6);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 7);
    CHECK_EQ(opField.GetCount(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_089] Arcane Golem - COST:3 [ATK:4/HP:2]
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Charge</b>.
//       <b>Battlecry:</b> Give your opponent a Mana Crystal.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - CHARGE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_089 : Arcane Golem")
{
    GameConfig config;
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
    curPlayer->SetTotalMana(3);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(3);
    opPlayer->SetUsedMana(0);

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Golem"));

    CHECK_EQ(opPlayer->GetTotalMana(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opPlayer->GetTotalMana(), 4);

    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 26);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_093] Defender of Argus - COST:4 [ATK:3/HP:3]
// - Faction: Alliance, Set: Expert1, Rarity: Rare
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
TEST_CASE("[Neutral : Minion] - EX1_093 : Defender of Argus")
{
    GameConfig config;
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

// ---------------------------------------- MINION - NEUTRAL
// [EX1_095] Gadgetzan Auctioneer - COST:5 [ATK:4/HP:4]
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever you cast a spell, draw a card.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_095 : Gadgetzan Auctioneer")
{
    GameConfig config;
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
// [EX1_096] Loot Hoarder - COST:2 [ATK:2/HP:1]
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Draw a card.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_096 : Loot Hoarder")
{
    GameConfig config;
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
// [EX1_097] Abomination - COST:5 [ATK:4/HP:4]
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Taunt</b>.
//       <b>Deathrattle:</b> Deal 2 damage to all characters.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_097 : Abomination")
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Abomination"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Boulderfist Ogre"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Boulderfist Ogre"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card7 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card6));
    game.Process(opPlayer, PlayCardTask::Minion(card7));
    CHECK_EQ(opField.GetCount(), 4);

    game.Process(opPlayer, AttackTask(card6, card1));
    game.Process(opPlayer, AttackTask(card7, card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 28);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 5);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_100] Lorewalker Cho - COST:2 [ATK:0/HP:4]
// - Faction: Neutral, Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: Whenever a player casts a spell,
//       put a copy into the other player's hand.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_100 : Lorewalker Cho")
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
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Lorewalker Cho"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Blizzard"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Inner Rage"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opHand[3]->card->name, "Fireball");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curHand[0]->card->name, "Blizzard");

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card1));
    CHECK_EQ(curHand[1]->card->name, "Inner Rage");
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_102] Demolisher - COST:3 [ATK:1/HP:4]
// - Race: Mechanical, Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: At the start of your turn,
//       deal 2 damage to a random enemy.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_102 : Demolisher")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Demolisher"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Dalaran Mage"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Dalaran Mage"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));

    int totalHealth = opField[0]->GetHealth();
    totalHealth += opField[1]->GetHealth();
    totalHealth += opPlayer->GetHero()->GetHealth();
    CHECK_EQ(totalHealth, 38);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    totalHealth = opField[0]->GetHealth();
    totalHealth += opField[1]->GetHealth();
    totalHealth += opPlayer->GetHero()->GetHealth();
    CHECK_EQ(totalHealth, 36);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_103] Coldlight Seer - COST:3 [ATK:2/HP:3]
// - Race: Murloc, Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give your other Murlocs +2 Health.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_103 : Coldlight Seer")
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
// [EX1_105] Mountain Giant - COST:12 [ATK:8/HP:8]
// - Race: Elemental, Faction: Neutral, Set: Expert1, Rarity: Epic
// --------------------------------------------------------
// Text: Costs (1) less for each other card in your hand.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_105 : Mountain Giant")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mountain Giant"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mountain Giant"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mountain Giant"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mountain Giant"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Sap"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Assassinate"));

    CHECK_EQ(card1->GetCost(), 9);
    CHECK_EQ(card2->GetCost(), 9);
    CHECK_EQ(card3->GetCost(), 9);
    CHECK_EQ(card4->GetCost(), 9);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card2->GetCost(), 10);
    CHECK_EQ(card3->GetCost(), 10);
    CHECK_EQ(card4->GetCost(), 10);

    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(card3->GetCost(), 11);
    CHECK_EQ(card4->GetCost(), 11);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card5, card1));
    CHECK_EQ(card1->GetCost(), 10);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card6, card2));
    CHECK_EQ(card2->GetCost(), 12);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_110] Cairne Bloodhoof - COST:6 [ATK:5/HP:5]
// - Faction: Alliance, Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a 5/5 Baine Bloodhoof.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_110 : Cairne Bloodhoof")
{
    GameConfig config;
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
// [EX1_116] Leeroy Jenkins - COST:5 [ATK:6/HP:2]
// - Faction: Alliance, Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Charge</b>.
//       <b>Battlecry:</b> Summon two 1/1 Whelps for your opponent.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - CHARGE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_116 : Leeroy Jenkins")
{
    GameConfig config;
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Leeroy Jenkins"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opField.GetCount(), 2);
    CHECK_EQ(opField[0]->GetHealth(), 1);
    CHECK_EQ(opField[0]->GetAttack(), 1);
    CHECK_EQ(opField[1]->GetHealth(), 1);
    CHECK_EQ(opField[1]->GetAttack(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_162] Dire Wolf Alpha - COST:2 [ATK:2/HP:2]
// - Race: Beast, Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: Adjacent minions have +1 Attack.
// --------------------------------------------------------
// GameTag:
// - ADJACENT_BUFF = 1
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_162 : Dire Wolf Alpha")
{
    GameConfig config;
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
// [EX1_170] Emperor Cobra - COST:3 [ATK:2/HP:3]
// - Race: Beast, Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Poisonous</b>
// --------------------------------------------------------
// GameTag:
// - POISONOUS = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_170 : Emperor Cobra")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Emperor Cobra"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Chillwind Yeti"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(card1, card2));

    CHECK(card2->isDestroyed);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_186] SI:7 Infiltrator - COST:4 [ATK:5/HP:4]
// - Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy a random enemy <b>Secret</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_186 : SI:7 Infiltrator")
{
    GameConfig config;
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
// [EX1_187] Arcane Devourer - COST:8 [ATK:4/HP:8]
// - Race: Elemental, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever you cast a spell, gain +2/+2.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_187 : Arcane Devourer")
{
    GameConfig config;
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
// [EX1_188] Barrens Stablehand - COST:7 [ATK:5/HP:5]
// - Set: Expert1, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a random Beast.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_188 : Barrens Stablehand")
{
    GameConfig config;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Barrens Stablehand"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->card->GetRace(), Race::BEAST);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_189] Brightwing - COST:3 [ATK:3/HP:2]
// - Race: Dragon, Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Add a random <b>Legendary</b>
//       minion to your hand.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_189 : Brightwing")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Brightwing"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->GetCardType(), CardType::MINION);
    CHECK_EQ(curHand[0]->card->GetRarity(), Rarity::LEGENDARY);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_190] High Inquisitor Whitemane - COST:6 [ATK:5/HP:7]
// - Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon all friendly minions
//       that died this turn.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_190 : High Inquisitor Whitemane")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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
    curPlayer->GetHero()->SetBaseHealth(100);
    opPlayer->GetHero()->SetBaseHealth(100);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("High Inquisitor Whitemane"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("High Inquisitor Whitemane"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("High Inquisitor Whitemane"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card7 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card8 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card9 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));
    const auto card10 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Malygos"));

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::Minion(card5));
    game.Process(curPlayer, PlayCardTask::Minion(card6));
    CHECK_EQ(curField.GetCount(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card9));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(card4, card9));
    game.Process(curPlayer, AttackTask(card5, card9));
    game.Process(curPlayer, AttackTask(card6, card9));
    CHECK_EQ(curField.GetCount(), 0);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card10));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card7));
    game.Process(curPlayer, PlayCardTask::Minion(card8));
    CHECK_EQ(curField.GetCount(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(curField[1], card10));
    game.Process(curPlayer, AttackTask(curField[1], card10));
    game.Process(curPlayer, AttackTask(curField[1], card10));
    game.Process(curPlayer, AttackTask(card7, card9));
    game.Process(curPlayer, AttackTask(card8, card10));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 7);

    std::size_t numWolfRider = 0, numWhitemane = 0;
    for (auto& minion : curField.GetAll())
    {
        if (minion->card->name == "Wolfrider")
        {
            ++numWolfRider;
        }
        else if (minion->card->name == "High Inquisitor Whitemane")
        {
            ++numWhitemane;
        }
    }

    CHECK_EQ(numWolfRider, 4);
    CHECK_EQ(numWhitemane, 3);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_249] Baron Geddon - COST:7 [ATK:7/HP:7]
// - Race: Elemental, Faction: Neutral, Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: At the end of your turn,
//       deal 2 damage to all other characters.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_249 : Baron Geddon")
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
// [EX1_283] Frost Elemental - COST:6 [ATK:5/HP:5]
// - Race: Elemental, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> <b>Freeze</b> a character.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_283 : Frost Elemental")
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

    const auto card1 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Frost Elemental"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fen Creeper"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fen Creeper"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::MinionTarget(card1, card2));

    CHECK_EQ(curField[0]->IsFrozen(), true);
    CHECK_EQ(curField[1]->IsFrozen(), false);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, AttackTask(card1, card3));

    CHECK_EQ(curField[1]->GetGameTag(GameTag::DAMAGE), 5);
    CHECK_EQ(curField[1]->IsFrozen(), false);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_284] Azure Drake - COST:5 [ATK:4/HP:5]
// - Race: Dragon, Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Spell Damage +1</b>
//       <b>Battlecry:</b> Draw a card.
// --------------------------------------------------------
// GameTag:
// - SPELLPOWER = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_284 : Azure Drake")
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
// [EX1_298] Ragnaros the Firelord - COST:8 [ATK:8/HP:8]
// - Race: Elemental, Faction: Neutral, Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: Can't attack. At the end of your turn,
//       deal 8 damage to a random enemy.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_298 : Ragnaros the Firelord")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Ragnaros the Firelord"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Grommash Hellscream"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 22);

    game.Process(opPlayer, PlayCardTask::Minion(card2));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opField.GetCount(), 1);
    const bool check =
        opPlayer->GetHero()->GetHealth() == 14 || opField[0]->GetHealth() == 1;
    CHECK_EQ(check, true);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_390] Tauren Warrior - COST:3 [ATK:2/HP:3]
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b> Has +3 Attack while damaged.
// --------------------------------------------------------
// GameTag:
// - ENRAGED = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_390 : Tauren Warrior")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Tauren Warrior"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAUNT), 1);
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAUNT), 1);
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 2);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_396] Mogu'shan Warden - COST:4 [ATK:1/HP:7]
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_396 : Mogu'shan Warden")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_405] Shieldbearer - COST:1 [ATK:0/HP:4]
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_405 : Shieldbearer")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_412] Raging Worgen - COST:3 [ATK:3/HP:3]
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: Has +1 Attack and <b>Windfury</b> while damaged.
// --------------------------------------------------------
// GameTag:
// - ENRAGED = 1
// --------------------------------------------------------
// RefTag:
// - WINDFURY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_412 : Raging Worgen")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Raging Worgen"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Circle of Healing"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasWindfury(), false);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));
    CHECK_FALSE(curField[0]->CanAttack());
    CHECK_EQ(curField[0]->HasWindfury(), false);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, HeroPowerTask(card1));
    CHECK(curField[0]->CanAttack());
    CHECK_EQ(curField[0]->HasWindfury(), true);
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_FALSE(curField[0]->CanAttack());
    CHECK_EQ(curField[0]->HasWindfury(), false);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_507] Murloc Warleader - COST:3 [ATK:3/HP:3]
// - Race: Murloc, Faction: Neutral, Set: Expert1, Rarity: Epic
// --------------------------------------------------------
// Text: Your other Murlocs have +2 Attack.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_507 : Murloc Warleader")
{
    GameConfig config;
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
// [EX1_509] Murloc Tidecaller - COST:1 [ATK:1/HP:2]
// - Race: Murloc, Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever you summon a Murloc, gain +1 Attack.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_509 : Murloc Tidecaller")
{
    GameConfig config;
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
// [EX1_556] Harvest Golem - COST:3 [ATK:2/HP:3]
// - Race: Mechanical, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a 2/1 Damaged Golem.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_556 : Harvest Golem")
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Magma Rager"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Harvest Golem"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Magma Rager"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->card->name, "Magma Rager");
    CHECK_EQ(curField[1]->card->name, "Harvest Golem");
    CHECK_EQ(curField[2]->card->name, "Magma Rager");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card4, card2));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[1]->card->name, "Damaged Golem");
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_557] Nat Pagle - COST:2 [ATK:0/HP:4]
// - Faction: Neutral, Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: At the start of your turn,
//       you have a 50% chance to draw an extra card.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_557 : Nat Pagle")
{
    GameConfig config;
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

    const auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Nat Pagle"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ((curHand.GetCount() == 5 || curHand.GetCount() == 6), true);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_558] Harrison Jones - COST:5 [ATK:5/HP:4]
// - Faction: Neutral, Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy your opponent's weapon
//       and draw cards equal to its Durability.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_558 : Harrison Jones")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fiery War Axe"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Harrison Jones"));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 2);

    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), false);
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 7);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_560] Nozdormu - COST:9 [ATK:8/HP:8]
// - Race: Dragon, Faction: Neutral, Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: Players only have 15 seconds to take their turns.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_560 : Nozdormu")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Nozdormu"));

    CHECK_EQ(curPlayer->GetTimeOut(), 75);
    CHECK_EQ(opPlayer->GetTimeOut(), 75);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetTimeOut(), 15);
    CHECK_EQ(opPlayer->GetTimeOut(), 15);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetTimeOut(), 15);
    CHECK_EQ(opPlayer->GetTimeOut(), 15);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_561] Alexstrasza - COST:9 [ATK:8/HP:8]
// - Race: Dragon, Faction: Neutral, Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Set a hero's remaining Health to 15.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_HERO_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_561 : Alexstrasza")
{
    GameConfig config;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Alexstrasza"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Alexstrasza"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Lord Jaraxxus"));

    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 15);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 15);
    CHECK_EQ(opPlayer->GetHero()->GetArmor(), 5);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask(opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 15);
    CHECK_EQ(opPlayer->GetHero()->GetArmor(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer,
                 PlayCardTask::MinionTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 15);
    CHECK_EQ(opPlayer->GetHero()->GetArmor(), 4);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_562] Onyxia - COST:9 [ATK:8/HP:8]
// - Race: Dragon, Faction: Neutral, Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon 1/1 Whelps until your side
//       of the battlefield is full.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_562 : Onyxia")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Onyxia"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 7);
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[2]->GetAttack(), 1);
    CHECK_EQ(curField[2]->GetHealth(), 1);
    CHECK_EQ(curField[3]->GetAttack(), 8);
    CHECK_EQ(curField[3]->GetHealth(), 8);
    CHECK_EQ(curField[4]->GetAttack(), 1);
    CHECK_EQ(curField[4]->GetHealth(), 1);
    CHECK_EQ(curField[5]->GetAttack(), 1);
    CHECK_EQ(curField[5]->GetHealth(), 1);
    CHECK_EQ(curField[6]->GetAttack(), 1);
    CHECK_EQ(curField[6]->GetHealth(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_563] Malygos - COST:9 [ATK:4/HP:12]
// - Race: Dragon, Faction: Neutral, Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Spell Damage +5</b>
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - SPELLPOWER = 5
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_563 : Malygos")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_564] Faceless Manipulator - COST:5 [ATK:3/HP:3]
// - Faction: Neutral, Set: Expert1, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Choose a minion and become a copy of it.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_MINION_TARGET = 0
// - REQ_NONSELF_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_564 : Faceless Manipulator")
{
    GameConfig config;
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
// [EX1_572] Ysera - COST:9 [ATK:4/HP:12]
// - Race: Dragon, Faction: Neutral, Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: At the end of your turn, add a Dream Card to your hand.
// --------------------------------------------------------
// Entourage: DREAM_01, DREAM_02, DREAM_03, DREAM_04, DREAM_05
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_572 : Ysera")
{
    GameConfig config;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ysera"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curHand.GetCount(), 5);

    const Card* dreamCard = curHand[4]->card;
    const Card* yseraCard = Cards::FindCardByName("Ysera");
    auto& entourages = yseraCard->entourages;
    CHECK(std::find(entourages.begin(), entourages.end(), dreamCard->id) !=
          entourages.end());
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_577] The Beast - COST:6 [ATK:9/HP:7]
// - Race: Beast, Faction: Neutral, Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a 3/3 Finkle Einhorn
//       for your opponent.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_577 : The Beast")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("The Beast"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    curField[0]->SetBaseHealth(1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    opField[0]->SetBaseHealth(99);

    game.Process(opPlayer, AttackTask(card2, card1));
    CHECK(card1->isDestroyed);
    CHECK_EQ(opField.GetCount(), 2);
    CHECK_EQ(opField[1]->GetHealth(), 3);
    CHECK_EQ(opField[1]->GetAttack(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_583] Priestess of Elune - COST:6 [ATK:5/HP:4]
// - Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Restore 4 Health to your hero.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_583 : Priestess of Elune")
{
    GameConfig config;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Priestess of Elune"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chillwind Yeti"));

    curPlayer->GetHero()->SetDamage(5);
    opPlayer->GetHero()->SetDamage(5);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 25);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 25);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 29);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 25);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_584] Ancient Mage - COST:4 [ATK:2/HP:5]
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give adjacent minions
//       <b>Spell Damage +1</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - SPELLPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_584 : Ancient Mage")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ancient Mage"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask(card1, nullptr, 1, 0));

    CHECK_EQ(curField[1]->card->name, "Ancient Mage");
    CHECK_EQ(curField[0]->GetSpellPower(), 1);
    CHECK_EQ(curField[2]->GetSpellPower(), 1);
    CHECK_EQ(curField[3]->GetSpellPower(), 0);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_586] Sea Giant - COST:10 [ATK:8/HP:8]
// - Faction: Neutral, Set: Expert1, Rarity: Epic
// --------------------------------------------------------
// Text: Costs (1) less for each other minion
//       on the battlefield.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_586 : Sea Giant")
{
    GameConfig config;
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
// [EX1_590] Blood Knight - COST:3 [ATK:3/HP:3]
// - Faction: Neutral, Set: Expert1, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> All minions lose <b>Divine Shield</b>.
//       Gain +3/+3 for each Shield lost.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_590 : Blood Knight")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Argent Squire"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Argent Squire"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Blood Knight"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Argent Squire"));
    const auto card7 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wisp"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField[0]->HasDivineShield(), true);
    CHECK_EQ(curField[1]->HasDivineShield(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card6));
    game.Process(opPlayer, PlayCardTask::Minion(card7));
    CHECK_EQ(opField[0]->HasDivineShield(), true);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(opField[2]->GetAttack(), 12);
    CHECK_EQ(opField[2]->GetHealth(), 12);
    CHECK_EQ(curField[0]->HasDivineShield(), false);
    CHECK_EQ(curField[1]->HasDivineShield(), false);
    CHECK_EQ(opField[0]->HasDivineShield(), false);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_595] Cult Master - COST:4 [ATK:4/HP:2]
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: Whenever one of your other minions dies, draw a card.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_595 : Cult Master")
{
    GameConfig config;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cult Master"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Argent Squire"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card6 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card7 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Stonetusk Boar"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curHand.GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, PlayCardTask::Minion(card6));
    game.Process(opPlayer, PlayCardTask::Minion(card7));

    game.Process(opPlayer, AttackTask(card4, card2));
    CHECK_EQ(curHand.GetCount(), 4);

    game.Process(opPlayer, AttackTask(card5, card2));
    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(opPlayer, AttackTask(card7, card3));
    CHECK_EQ(curHand.GetCount(), 6);

    game.Process(opPlayer, AttackTask(card6, card1));
    CHECK_EQ(curHand.GetCount(), 6);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    const auto card8 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cult Master"));
    const auto card9 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card10 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card11 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Hellfire"));

    game.Process(curPlayer, PlayCardTask::Minion(card8));
    game.Process(curPlayer, PlayCardTask::Minion(card9));
    game.Process(curPlayer, PlayCardTask::Minion(card10));
    CHECK_EQ(curHand.GetCount(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card11));
    CHECK_EQ(curHand.GetCount(), 7);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_597] Imp Master - COST:3 [ATK:1/HP:5]
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: At the end of your turn,
//       deal 1 damage to this minion and summon a 1/1 Imp.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_597 : Imp Master")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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

    // Summon 5 Wisps
    for (int i = 0; i < 5; i++)
    {
        const auto card =
            Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
        game.Process(curPlayer, PlayCardTask::Minion(card));
    }

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Imp Master"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Frostbolt"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 6);
    CHECK_EQ(curField[5]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);
    CHECK_EQ(curField.GetCount(), 7);
    CHECK_EQ(curField[5]->GetHealth(), 4);

    // Deal 3 damage to "Imp Master"
    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, curField[5]));
    CHECK_EQ(curField[5]->GetHealth(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    // "Imp Master kills" self, and full field make it cannot summon "Imp".
    CHECK_EQ(curField.GetCount(), 6);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_614] Xavius - COST:6 [ATK:7/HP:5]
// - Race: Demon, Faction: Neutral, Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: After you play a card, summon a 2/1 Satyr.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_614 : Xavius")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Xavius"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Moonfire"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[1]->card->name, "Xavian Satyr");
    CHECK_EQ(curField[2]->card->name, "Wisp");

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[1]->card->name, "Xavian Satyr");
    CHECK_EQ(curField[2]->card->name, "Xavian Satyr");
    CHECK_EQ(curField[3]->card->name, "Wisp");
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_616] Mana Wraith - COST:2 [ATK:2/HP:2]
// - Faction: Neutral, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: ALL minions cost (1) more.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_616 : Mana Wraith")
{
    GameConfig config;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Mana Wraith"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fireball"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Starfall"));

    CHECK_EQ(card1->GetCost(), 2);
    CHECK_EQ(card2->GetCost(), 0);
    CHECK_EQ(card3->GetCost(), 4);
    CHECK_EQ(card4->GetCost(), 3);
    CHECK_EQ(card5->GetCost(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card2->GetCost(), 1);
    CHECK_EQ(card3->GetCost(), 4);
    CHECK_EQ(card4->GetCost(), 4);
    CHECK_EQ(card5->GetCost(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card5, card1, 2));
    CHECK_EQ(card2->GetCost(), 0);
    CHECK_EQ(card3->GetCost(), 4);
    CHECK_EQ(card4->GetCost(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_620] Molten Giant - COST:20 [ATK:8/HP:8]
// - Race: Elemental, Faction: Neutral, Set: Expert1, Rarity: Epic
// --------------------------------------------------------
// Text: Costs (1) less for each damage your hero has taken.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - EX1_620 : Molten Giant")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Molten Giant"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Imp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Imp"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Imp"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Imp"));

    CHECK_EQ(card1->GetCost(), 20);

    game.Process(curPlayer, PlayCardTask(card2));
    game.Process(curPlayer, PlayCardTask(card3));
    game.Process(curPlayer, PlayCardTask(card4));
    game.Process(curPlayer, PlayCardTask(card5));

    CHECK_EQ(card1->GetCost(), 8);

    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Imp"));
    const auto card7 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Imp"));
    const auto card8 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Imp"));
    const auto card9 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Flame Imp"));

    game.Process(curPlayer, PlayCardTask(card6));
    game.Process(curPlayer, PlayCardTask(card7));
    game.Process(curPlayer, PlayCardTask(card8));
    game.Process(curPlayer, PlayCardTask(card9));

    CHECK_EQ(card1->GetCost(), 0);
}

// --------------------------------------- MINION - NEUTRAL
// [NEW1_017] Hungry Crab - COST:1 [ATK:1/HP:2]
// - Race: Beast, Set: Expert1, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy a Murloc and gain +2/+2.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_TARGET_WITH_RACE = 14
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - NEW1_017 : Hungry Crab")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Raider"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wisp"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hungry Crab"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hungry Crab"));

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, PlayCardTask::MinionTarget(card3, card2));
    CHECK_EQ(curField.GetCount(), 3);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card3, card1));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[2]->GetAttack(), 3);
    CHECK_EQ(curField[2]->GetHealth(), 4);
}

// --------------------------------------- MINION - NEUTRAL
// [NEW1_018] Bloodsail Raider - COST:2 [ATK:2/HP:3]
// - Race: Pirate, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Gain Attack equal to the Attack
//       of your weapon.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - NEW1_018 : Bloodsail Raider")
{
    GameConfig config;
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
// [NEW1_019] Knife Juggler - COST:2 [ATK:3/HP:2]
// - Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: After you summon a minion,
//       deal 1 damage to a random enemy.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - NEW1_019 : Knife Juggler")
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByID("NEW1_019"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Magma Rager"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Magma Rager"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Chillwind Yeti"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 29);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 29);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(opField[0]->GetHealth(), 5);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ((opPlayer->GetHero()->GetHealth() == 28 ||
              opField[0]->GetHealth() == 4),
             true);
}

// --------------------------------------- MINION - NEUTRAL
// [NEW1_020] Wild Pyromancer - COST:2 [ATK:3/HP:2]
// - Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: After you cast a spell, deal 1 damage to all minions.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - NEW1_020 : Wild Pyromancer")
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
// [NEW1_021] Doomsayer - COST:2 [ATK:0/HP:7]
// - Faction: Neutral, Set: Expert1, Rarity: Epic
// --------------------------------------------------------
// Text: At the start of your turn, destroy all minions.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - NEW1_021 : Doomsayer")
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
// [NEW1_022] Dread Corsair - COST:4 [ATK:3/HP:3]
// - Race: Pirate, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       Costs (1) less per Attack of your weapon.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - NEW1_022 : Dread Corsair")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Dread Corsair"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Deadly Poison"));

    CHECK_EQ(card1->GetCost(), 4);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(card1->GetCost(), 3);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(card1->GetCost(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [NEW1_023] Faerie Dragon - COST:2 [ATK:3/HP:2]
// - Race: Dragon, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: Can't be targeted by spells or Hero Powers.
// --------------------------------------------------------
// GameTag:
// - CANT_BE_TARGETED_BY_SPELLS = 1
// - CANT_BE_TARGETED_BY_HERO_POWERS = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - NEW1_023 : Faerie Dragon")
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
// [NEW1_024] Captain Greenskin - COST:5 [ATK:5/HP:4]
// - Race: Pirate, Set: Expert1, Rarity: legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give your weapon +1/+1.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - NEW1_024 : Captain Greenskin")
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
        curPlayer, Cards::FindCardByName("Captain Greenskin"));

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 1);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 2);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 2);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [NEW1_025] Bloodsail Corsair - COST:2 [ATK:1/HP:2]
// - Race: Pirate, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Remove 1 Durability from
//       your opponent's weapon.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - NEW1_025 : Bloodsail Corsair")
{
    GameConfig config;
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

    const auto card1 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Bloodsail Corsair"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Bloodsail Corsair"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Bloodsail Corsair"));

    game.Process(curPlayer, HeroPowerTask(nullptr));
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(nullptr));
    CHECK_EQ(opPlayer->GetHero()->weapon->GetDurability(), 2);

    game.Process(opPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 1);
    CHECK_EQ(opPlayer->GetHero()->weapon->GetDurability(), 2);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHero()->weapon, nullptr);
    CHECK_EQ(opPlayer->GetHero()->weapon->GetDurability(), 2);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curPlayer->GetHero()->weapon, nullptr);
    CHECK_EQ(opPlayer->GetHero()->weapon->GetDurability(), 2);
}

// --------------------------------------- MINION - NEUTRAL
// [NEW1_026] Violet Teacher - COST:4 [ATK:3/HP:5]
// - Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever you cast a spell,
//       summon a 1/1 Violet Apprentice.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - NEW1_026 : Violet Teacher")
{
    GameConfig config;
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
// [NEW1_027] Southsea Captain - COST:3 [ATK:3/HP:3]
// - Race: Pirate, Faction: Neutral, Set: Expert1, Rarity: Epic
// --------------------------------------------------------
// Text: Your other Pirates have +1/+1.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - NEW1_027 : Southsea Captain")
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
// [NEW1_029] Millhouse Manastorm - COST:2 [ATK:4/HP:4]
// - Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Enemy spells cost (0) next turn.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - NEW1_029 : Millhouse Manastorm")
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
        curPlayer, Cards::FindCardByName("Millhouse Manastorm"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Frostbolt"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    CHECK_EQ(card2->GetCost(), 4);
    CHECK_EQ(card3->GetCost(), 2);
    CHECK_EQ(card4->GetCost(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card2->GetCost(), 0);
    CHECK_EQ(card3->GetCost(), 0);
    CHECK_EQ(card4->GetCost(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card3, curPlayer->GetHero()));
    CHECK_EQ(card2->GetCost(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card2->GetCost(), 4);
    CHECK_EQ(card4->GetCost(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [NEW1_030] Deathwing - COST:10 [ATK:12/HP:12]
// - Race: Dragon, Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy all other minions
//       and discard your hand.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - NEW1_030 : Deathwing")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByID("NEW1_030"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Magma Rager"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Magma Rager"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Magma Rager"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Magma Rager"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card4));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card5));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    CHECK_EQ(curPlayer->GetFieldZone()->GetCount(), 1);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 0);

    CHECK_EQ(opPlayer->GetFieldZone()->GetCount(), 0);
    CHECK_NE(opPlayer->GetHandZone()->GetCount(), 0);
}

// --------------------------------------- MINION - NEUTRAL
// [NEW1_037] Master Swordsmith - COST:2 [ATK:1/HP:3]
// - Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: At the end of your turn,
//       give another random friendly minion +1 Attack.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - NEW1_037 : Master Swordsmith")
{
    GameConfig config;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Master Swordsmith"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Acidic Swamp Ooze"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));

    int totalAttack = curField[1]->GetAttack();
    totalAttack += curField[2]->GetAttack();
    CHECK_EQ(totalAttack, 6);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    totalAttack = curField[1]->GetAttack();
    totalAttack += curField[2]->GetAttack();
    CHECK_EQ(totalAttack, 7);
}

// --------------------------------------- MINION - NEUTRAL
// [NEW1_038] Gruul - COST:8 [ATK:7/HP:7]
// - Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: At the end of each turn, gain +1/+1.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - NEW1_038 : Gruul")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Gruul"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 7);
    CHECK_EQ(curField[0]->GetHealth(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetAttack(), 8);
    CHECK_EQ(curField[0]->GetHealth(), 8);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetAttack(), 9);
    CHECK_EQ(curField[0]->GetHealth(), 9);
}

// --------------------------------------- MINION - NEUTRAL
// [NEW1_040] Hogger - COST:6 [ATK:4/HP:4]
// - Set: Expert1, Rarity: Legendary
// --------------------------------------------------------
// Text: At the end of your turn,
//       summon a 2/2 Gnoll with <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - NEW1_040 : Hogger")
{
    GameConfig config;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Hogger"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField.GetAll()[1]->card->id, "NEW1_040t");

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 2);
}

// --------------------------------------- MINION - NEUTRAL
// [NEW1_041] Stampeding Kodo - COST:5 [ATK:3/HP:5]
// - Race: Beast, Set: Expert1, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy a random enemy minion
//       with 2 or less Attack.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - NEW1_041 : Stampeding Kodo")
{
    GameConfig config;
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
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Stampeding Kodo"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Stampeding Kodo"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Stampeding Kodo"));
    const auto card4 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Voidwalker"));
    const auto card5 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("River Crocolisk"));
    const auto card6 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bloodfen Raptor"));

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::Minion(card5));
    game.Process(curPlayer, PlayCardTask::Minion(card6));
    CHECK_EQ(curField.GetCount(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField.GetAll()[0]->card->name, "Bloodfen Raptor");

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [tt_004] Flesheating Ghoul - COST:3 [ATK:3/HP:3]
// - Faction: Neutral, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: Whenever a minion dies, gain +1 Attack.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - tt_004 : Flesheating Ghoul")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Flesheating Ghoul"));
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
    CHECK_EQ(curField[0]->GetAttack(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));

    game.Process(opPlayer, AttackTask(card4, card2));
    CHECK_EQ(curField[0]->GetAttack(), 5);

    game.Process(opPlayer, AttackTask(card5, card3));
    CHECK_EQ(curField[0]->GetAttack(), 7);
}

// ----------------------------------------- MINION - DREAM
// [DREAM_01] Laughing Sister (*) - COST:2 [ATK:3/HP:5]
// - Set: Expert1
// --------------------------------------------------------
// Text: Can't be targeted by spells or Hero Powers.
// --------------------------------------------------------
// GameTag:
// - CANT_BE_TARGETED_BY_SPELLS = 1
// - CANT_BE_TARGETED_BY_HERO_POWERS = 1
// --------------------------------------------------------
TEST_CASE("[Dream : Minion] - DREAM_01 : Laughing Sister")
{
    // Do nothing
}

// ------------------------------------------ SPELL - DREAM
// [DREAM_02] Ysera Awakens (*) - COST:3
// - Set: Expert1
// --------------------------------------------------------
// Text: Deal 5 damage to all minions except Ysera.
// --------------------------------------------------------
TEST_CASE("[Dream : Spell] - DREAM_02 : Ysera Awakens")
{
    GameConfig config;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByID("DREAM_02"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Ysera"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Fen Creeper"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Ysera"));
    const auto card5 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fen Creeper"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(card2->GetGameTag(GameTag::DAMAGE), 0);
    CHECK_EQ(card4->GetGameTag(GameTag::DAMAGE), 0);
    CHECK_EQ(card3->GetGameTag(GameTag::DAMAGE), 5);
    CHECK_EQ(card5->GetGameTag(GameTag::DAMAGE), 5);
}

// ----------------------------------------- MINION - DREAM
// [DREAM_03] Emerald Drake (*) - COST:4 [ATK:7/HP:6]
// - Race: Dragon, Set: Expert1
// --------------------------------------------------------
TEST_CASE("[Dream : Minion] - DREAM_03 : Emerald Drake")
{
    // Do nothing
}

// ------------------------------------------ SPELL - DREAM
// [DREAM_04] Dream (*) - COST:1
// - Set: Expert1
// --------------------------------------------------------
// Text: Return an enemy minion to your opponent's hand.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_ENEMY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Dream : Spell] - DREAM_04 : Dream")
{
    GameConfig config;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::PRIEST;
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
    auto& curHand = *(curPlayer->GetHandZone());
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 =
        Generic::DrawCard(opPlayer, Cards::FindCardByID("DREAM_04"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Magma Rager"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Magma Rager"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(opHand.GetCount(), 2);
    CHECK_EQ(opHand[1]->card->name, "Dream");

    game.Process(opPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(opHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->name, "Magma Rager");
}

// ------------------------------------------ SPELL - DREAM
// [DREAM_05] Nightmare (*) - COST:0
// - Set: Expert1
// --------------------------------------------------------
// Text: Give a minion +4/+4. At the start of your next turn, destroy it.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Dream : Spell] - DREAM_05 : Nightmare")
{
    GameConfig config;
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
        Generic::DrawCard(opPlayer, Cards::FindCardByID("DREAM_05"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Magma Rager"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField[0]->appliedEnchantments.size(), 1);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 9);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 0);
}