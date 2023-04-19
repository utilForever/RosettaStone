// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetHeaders.hpp>

// ------------------------------------------ SPELL - DRUID
// [YOD_001] Rising Winds - COST:2
// - Set: YoD, Rarity: Common
// --------------------------------------------------------
// Text: <b>Twinspell</b> <b>Choose One -</b>
//       Draw a card; or Summon a 3/2 Eagle.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// - TWINSPELL_COPY = 56141
// - TWINSPELL = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - YOD_001 : Rising Winds")
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

    auto& curHand = *(curPlayer->GetHandZone());
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByID("YOD_001"));

    game.Process(curPlayer, PlayCardTask::Spell(card1, 1));
    CHECK_EQ(curHand.GetCount(), 6);
    CHECK_EQ(curHand[4]->card->id, "YOD_001ts");

    game.Process(curPlayer, PlayCardTask::Spell(curHand[4], 2));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Eagle");
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 2);
}

// ----------------------------------------- MINION - DRUID
// [YOD_003] Winged Guardian - COST:7 [ATK:6/HP:8]
// - Race: Beast, Set: YoD, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Taunt</b>, <b>Reborn</b>
//       Can't be targeted by spells or Hero Powers.
// --------------------------------------------------------
// GameTag:
// - CANT_BE_TARGETED_BY_SPELLS = 1
// - CANT_BE_TARGETED_BY_HERO_POWERS = 1
// - REBORN = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - YOD_003 : Winged Guardian")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Winged Guardian"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("King Krush"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 8);
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[0]->HasReborn(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetHealth(), 8);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField[0]->GetHealth(), 8);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, AttackTask(card3, curField[0]));
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[0]->HasReborn(), false);
}

// ----------------------------------------- MINION - DRUID
// [YOD_040] Steel Beetle - COST:2 [ATK:2/HP:3]
// - Race: Beast, Set: YoD, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you're holding a spell that
//       costs (5) or more, gain 5 Armor.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - YOD_040 : Steel Beetle")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Steel Beetle"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Steel Beetle"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Gift of the Wild"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 5);
}

// ---------------------------------------- MINION - HUNTER
// [YOD_004] Chopshop Copter - COST:3 [ATK:2/HP:4]
// - Race: Mechanical, Set: YoD, Rarity: Rare
// --------------------------------------------------------
// Text: After a friendly Mech dies,
//       add a random Mech to your hand.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - YOD_004 : Chopshop Copter")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Chopshop Copter"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Harvest Golem"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curHand.GetCount(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card2));
    CHECK_EQ(curHand.GetCount(), 0);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card3));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->GetRace(), Race::MECHANICAL);
}

// ----------------------------------------- SPELL - HUNTER
// [YOD_005] Fresh Scent - COST:2
// - Set: YoD, Rarity: Common
// --------------------------------------------------------
// Text: <b>Twinspell</b> Give a Beast +2/+2.
// --------------------------------------------------------
// GameTag:
// - TWINSPELL_COPY = 56142
// - TWINSPELL = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_TO_PLAY = 0
// - REQ_TARGET_WITH_RACE = 20
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - YOD_005 : Fresh Scent")
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
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByID("YOD_005"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Raider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->id, "YOD_005");
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->id, "YOD_005ts");
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, PlayCardTask::SpellTarget(curHand[0], card3));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->id, "YOD_005ts");
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(curHand[0], card2));
    CHECK_EQ(curHand.GetCount(), 0);
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 5);
}

// ---------------------------------------- MINION - HUNTER
// [YOD_036] Rotnest Drake - COST:5 [ATK:6/HP:5]
// - Race: Dragon, Set: YoD, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you're holding a Dragon,
//       destroy a random enemy minion.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - YOD_036 : Rotnest Drake")
{
    GameConfig config;
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Amplifier"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Amplifier"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Rotnest Drake"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Rotnest Drake"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField.GetCount(), 1);
}

// ------------------------------------------ MINION - MAGE
// [YOD_007] Animated Avalanche - COST:7 [ATK:7/HP:6]
// - Race: Elemental, Set: YoD, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you played an Elemental
//       last turn, summon a copy of this.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - YOD_007 : Animated Avalanche")
{
    GameConfig config;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Animated Avalanche"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Animated Avalanche"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->card->name, "Animated Avalanche");

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[1]->card->name, "Animated Avalanche");
    CHECK_EQ(curField[2]->card->name, "Animated Avalanche");
}

// ------------------------------------------ MINION - MAGE
// [YOD_008] Arcane Amplifier - COST:3 [ATK:2/HP:5]
// - Race: Elemental, Set: YoD, Rarity: Common
// --------------------------------------------------------
// Text: Your Hero Power deals 2 extra damage.
// --------------------------------------------------------
// GameTag:
// - HEROPOWER_DAMAGE = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - YOD_008 : Arcane Amplifier")
{
    GameConfig config;
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

    const auto opHero = opPlayer->GetHero();

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Arcane Amplifier"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("King Krush"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, HeroPowerTask(opHero));
    CHECK_EQ(opHero->GetHealth(), 27);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, AttackTask(card2, card1));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask(opHero));
    CHECK_EQ(opHero->GetHealth(), 26);
}

// --------------------------------------- MINION - PALADIN
// [YOD_010] Shotbot - COST:2 [ATK:2/HP:2]
// - Race: Mechanical, Set: YoD, Rarity: Common
// --------------------------------------------------------
// Text: <b>Reborn</b>
// --------------------------------------------------------
// GameTag:
// - REBORN = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - YOD_010 : Shotbot")
{
    // Do nothing
}

// ---------------------------------------- SPELL - PALADIN
// [YOD_012] Air Raid - COST:2
// - Set: YoD, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Twinspell</b>
//       Summon two 1/1 Silver Hand Recruits with <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - TWINSPELL_COPY = 56144
// - TWINSPELL = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - YOD_012 : Air Raid")
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
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curHand = *(curPlayer->GetHandZone());
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByID("YOD_012"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->id, "YOD_012ts");
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Silver Hand Recruit");
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[1]->card->name, "Silver Hand Recruit");
    CHECK_EQ(curField[1]->HasTaunt(), true);

    game.Process(curPlayer, PlayCardTask::Spell(curHand[0]));
    CHECK_EQ(curHand.GetCount(), 0);
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[0]->card->name, "Silver Hand Recruit");
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[1]->card->name, "Silver Hand Recruit");
    CHECK_EQ(curField[1]->HasTaunt(), true);
    CHECK_EQ(curField[2]->card->name, "Silver Hand Recruit");
    CHECK_EQ(curField[2]->HasTaunt(), true);
    CHECK_EQ(curField[3]->card->name, "Silver Hand Recruit");
    CHECK_EQ(curField[3]->HasTaunt(), true);
}

// --------------------------------------- MINION - PALADIN
// [YOD_043] Scalelord - COST:5 [ATK:5/HP:6]
// - Race: Dragon, Set: YoD, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give your Murlocs <b>Divine Shield</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - YOD_043 : Scalelord")
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
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Scalelord"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Stonetusk Boar"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Murloc Raider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->HasDivineShield(), false);
    CHECK_EQ(curField[1]->HasDivineShield(), true);
    CHECK_EQ(curField[2]->HasDivineShield(), false);
}

// ---------------------------------------- MINION - PRIEST
// [YOD_014] Aeon Reaver - COST:6 [ATK:4/HP:4]
// - Race: Dragon, Set: YoD, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal damage to a minion equal
//       to its Attack.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - YOD_014 : Aeon Reaver")
{
    GameConfig config;
    config.player1Class = CardClass::DRUID;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Ironbark Protector"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Aeon Reaver"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 8);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::MinionTarget(card2, card1));
    CHECK_EQ(curField[0]->GetHealth(), 4);
}

// ----------------------------------------- MINION - ROGUE
// [YOD_016] Skyvateer - COST:2 [ATK:1/HP:3]
// - Set: YoD, Rarity: Common
// --------------------------------------------------------
// Text: <b>Stealth</b> <b>Deathrattle:</b> Draw a card.
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// --------------------------------------------------------
// RefTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - YOD_016 : Skyvateer")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Skyvateer"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Flamestrike"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 4);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->HasStealth(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
    CHECK_EQ(curField.GetCount(), 0);
}

// ----------------------------------------- SPELL - SHAMAN
// [YOD_020] Explosive Evolution - COST:2
// - Set: YoD, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: Transform a minion into a random one that costs (3) more.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - YOD_020 : Explosive Evolution")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Explosive Evolution"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Explosive Evolution"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Shattered Rumbler"));

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->card->GetCost(), 5);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, curField[0]));
    CHECK_EQ(curField[0]->card->GetCost(), 8);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, curField[0]));
    CHECK_EQ(curField[0]->card->GetCost(), 11);
}

// ----------------------------------------- SPELL - SHAMAN
// [YOD_041] Eye of the Storm - COST:10
// - Set: YoD, Rarity: Common
// - Spell School: Nature
// --------------------------------------------------------
// Text: Summon three 5/6 Elementals with <b>Taunt</b>.
//       <b>Overload:</b> (3)
// --------------------------------------------------------
// GameTag:
// - OVERLOAD = 3
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - YOD_041 : Eye of the Storm")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Eye of the Storm"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[0]->card->name, "Stormblocker");
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 6);
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[1]->card->name, "Stormblocker");
    CHECK_EQ(curField[2]->card->name, "Stormblocker");
    CHECK_EQ(curPlayer->GetOverloadLocked(), 0);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetRemainingMana(), 7);
    CHECK_EQ(curPlayer->GetOverloadLocked(), 3);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 0);
}

// ---------------------------------------- SPELL - WARLOCK
// [YOD_025] Twisted Knowledge - COST:2
// - Set: YoD, Rarity: Common
// --------------------------------------------------------
// Text: <b>Discover</b> 2 Warlock cards.
// --------------------------------------------------------
// GameTag:
// - DISCOVER = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - YOD_025 : Twisted Knowledge")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Twisted Knowledge"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK(curPlayer->choice);

    TestUtils::ChooseNthChoice(game, 1);
    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(curHand.GetCount(), 2);
    CHECK_EQ(curHand[0]->card->GetCardClass(), CardClass::WARLOCK);
    CHECK_EQ(curHand[1]->card->GetCardClass(), CardClass::WARLOCK);
}

// --------------------------------------- MINION - WARRIOR
// [YOD_022] Risky Skipper - COST:1 [ATK:1/HP:3]
// - Set: YoD, Rarity: Rare
// --------------------------------------------------------
// Text: After you play a minion, deal 1 damage to all minions.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - YOD_022 : Risky Skipper")
{
    GameConfig config;
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Risky Skipper"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("River Crocolisk"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(opField.GetCount(), 0);
}

// --------------------------------------- MINION - WARRIOR
// [YOD_024] Bomb Wrangler - COST:3 [ATK:2/HP:3]
// - Set: YoD, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever this minion takes damage, summon a 1/1 Boom Bot.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - YOD_024 : Bomb Wrangler")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Bomb Wrangler"));
    const auto card2 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[1]->card->name, "Boom Bot");

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->card->name, "Boom Bot");
    CHECK_EQ(curField[1]->card->name, "Boom Bot");
}

// --------------------------------------- MINION - NEUTRAL
// [YOD_006] Escaped Manasaber - COST:4 [ATK:3/HP:5]
// - Race: Beast, Faction: Neutral, Set: YoD, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Stealth</b>
//       Whenever this attacks,
//       gain 1 Mana Crystal this turn only.
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - YOD_006 : Escaped Manasaber")
{
    GameConfig config;
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
// [YOD_030] Licensed Adventurer - COST:2 [ATK:2/HP:2]
// - Faction: Neutral, Set: YoD, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If you control a <b>Quest</b>,
//       add a Coin to your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - QUEST = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - YOD_030 : Licensed Adventurer")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Licensed Adventurer"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Licensed Adventurer"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Untapped Potential"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 6);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "The Coin");
}

// --------------------------------------- MINION - NEUTRAL
// [YOD_035] Grand Lackey Erkh - COST:4 [ATK:2/HP:3]
// - Faction: Neutral, Set: YoD, Rarity: Legendary
// --------------------------------------------------------
// Text: After you play a <b>Lackey</b>,
//       add a <b>Lackey</b> to your hand.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - YOD_035 : Grand Lackey Erkh")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Grand Lackey Erkh"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByID("DAL_614"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curHand.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curHand.GetCount(), 1);
    CHECK_EQ(curHand[0]->card->IsLackey(), true);
}