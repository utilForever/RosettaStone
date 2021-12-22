// Copyright (c) 2017-2021 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Utils/CardSetUtils.hpp>
#include <Utils/TestUtils.hpp>

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

// ----------------------------------- HERO_POWER - WARRIOR
// [VAN_CS2_102_H3] Armor Up! - COST:2
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Hero Power</b> Gain 2 Armor.
// --------------------------------------------------------
TEST_CASE("[Warrior : Hero Power] - VAN_CS2_102_H3 : Armor Up!")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 0);

    game.Process(curPlayer, HeroPowerTask());

    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 2);
}

// ----------------------------------- HERO_POWER - WARRIOR
// [VAN_HERO_01bp] Armor Up! - COST:2
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Hero Power</b> Gain 2 Armor.
// --------------------------------------------------------
TEST_CASE("[Warrior : Hero Power] - VAN_HERO_01bp : Armor Up!")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 0);

    game.Process(curPlayer, HeroPowerTask());

    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 2);
}

// ------------------------------------ HERO_POWER - SHAMAN
// [VAN_HERO_02bp] Totemic Call - COST:2
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Hero Power</b> Summon a random Totem.
// --------------------------------------------------------
// Entourage: VAN_CS2_050, VAN_CS2_051, VAN_CS2_052, VAN_NEW1_009
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// - REQ_ENTIRE_ENTOURAGE_NOT_IN_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Shaman : Hero Power] - VAN_HERO_02bp : Totemic Call")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    game.Process(curPlayer, HeroPowerTask());
    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask());
    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask());
    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask());
    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask());
    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask());
    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask());
    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask());
    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(opField.GetCount(), 4);
}

// ------------------------------------- HERO_POWER - ROGUE
// [VAN_HERO_03bp] Dagger Mastery - COST:2
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Hero Power</b> Equip a 1/2 Dagger.
// --------------------------------------------------------
TEST_CASE("[Rogue : Hero Power] - VAN_HERO_03bp : Dagger Mastery")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), false);

    game.Process(curPlayer, HeroPowerTask());

    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), true);
    CHECK_EQ(curPlayer->GetWeapon().GetAttack(), 1);
    CHECK_EQ(curPlayer->GetWeapon().GetDurability(), 2);

    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetWeapon().GetDurability(), 1);
}

// ----------------------------------- HERO_POWER - PALADIN
// [VAN_HERO_04bp] Reinforce - COST:2
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Hero Power</b> Summon a 1/1 Silver Hand Recruit.
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Hero Power] - VAN_HERO_04bp : Reinforce")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    game.Process(curPlayer, HeroPowerTask());

    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
}

// ------------------------------------ HERO_POWER - HUNTER
// [VAN_HERO_05bp] Steady Shot - COST:2
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Hero Power</b> Deal 2 damage to the enemy hero.
// --------------------------------------------------------
// PlayReq:
// - REQ_STEADY_SHOT = 0
// - REQ_MINION_OR_ENEMY_HERO = 0
// --------------------------------------------------------
TEST_CASE("[Hunter : Hero Power] - VAN_HERO_05bp : Steady Shot")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    game.Process(curPlayer, HeroPowerTask());

    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);
}

// ------------------------------------- HERO_POWER - DRUID
// [VAN_HERO_06bp] Shapeshift - COST:2
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Hero Power</b> +1 Attack this turn. +1 Armor.
// --------------------------------------------------------
TEST_CASE("[Druid : Hero Power] - VAN_HERO_06bp : Shapeshift")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Northshire Cleric"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card1));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 0);
    CHECK_EQ(opField[0]->GetHealth(), 3);

    game.Process(curPlayer, HeroPowerTask());

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 1);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 1);

    game.Process(curPlayer, AttackTask(curPlayer->GetHero(), card1));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 1);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 0);
    CHECK_EQ(opField[0]->GetHealth(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 0);
}

// ----------------------------------- HERO_POWER - WARLOCK
// [VAN_HERO_07bp] Life Tap - COST:2
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Hero Power</b> Draw a card and take 2 damage.
// --------------------------------------------------------
TEST_CASE("[Warlock : Hero Power] - VAN_HERO_07bp : Life Tap")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 4);

    game.Process(curPlayer, HeroPowerTask());

    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 28);
}

// -------------------------------------- HERO_POWER - MAGE
// [VAN_HERO_08bp] Fireblast - COST:2
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Hero Power</b> Deal 1 damage.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Mage : Hero Power] - VAN_HERO_08bp : Fireblast")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Northshire Cleric"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opField[0]->GetHealth(), 3);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask(card1));

    CHECK_EQ(opField[0]->GetHealth(), 2);
}

// ------------------------------------ HERO_POWER - PRIEST
// [VAN_HERO_09bp] Lesser Heal - COST:2
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Hero Power</b> Restore 2 Health.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Hero Power] - VAN_HERO_09bp : Lesser Heal")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 29);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask(curPlayer->GetHero()));

    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 30);
}

// ------------------------------- HERO_POWER - DEMONHUNTER
// [VAN_HERO_10bp] Demon Claws - COST:1
// - Set: VANILLA
// --------------------------------------------------------
// Text: <b>Hero Power</b> +1 Attack this turn.
// --------------------------------------------------------
TEST_CASE("[Demon Hunter : Hero Power] - VAN_HERO_10bp : Demon Claws")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
    config.player1Class = CardClass::DRUID;
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

    const auto card1 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Northshire Cleric"));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card1));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
    CHECK_EQ(opField[0]->GetHealth(), 3);

    game.Process(curPlayer, HeroPowerTask());

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 1);

    game.Process(curPlayer, AttackTask(curPlayer->GetHero(), card1));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
}

// ------------------------------------------ SPELL - DRUID
// [VAN_CS2_005] Claw - COST:1
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Give your hero +2 Attack this turn. Gain 2 Armor.
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - VAN_CS2_005 : Claw")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Claw", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 2);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 2);

    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 2);
}

// ------------------------------------------ SPELL - DRUID
// [VAN_CS2_007] Healing Touch - COST:3
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Restore 8 Health.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - VAN_CS2_007 : Healing Touch")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
    config.player1Class = CardClass::DRUID;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Healing Touch", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Healing Touch", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));

    curPlayer->GetHero()->SetDamage(15);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    opField[0]->SetDamage(6);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 23);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3));
    CHECK_EQ(opField[0]->GetHealth(), 7);
}

// ------------------------------------------ SPELL - DRUID
// [VAN_CS2_008] Moonfire - COST:0
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Deal 1 damage.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - VAN_CS2_008 : Moonfire")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Moonfire", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Moonfire", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Moonfire", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Moonfire", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));
    const auto card6 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card5));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card6));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card6));
    CHECK_EQ(opField[0]->GetHealth(), 1);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 29);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card5));
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 29);
}

// ------------------------------------------ SPELL - DRUID
// [VAN_CS2_009] Mark of the Wild - COST:2
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Give a minion <b>Taunt</b> and +2/+2.<i>
//       (+2 Attack/+2 Health)</i>
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - VAN_CS2_009 : Mark of the Wild")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Mark of the Wild", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

    auto& curField = *(curPlayer->GetFieldZone());

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAUNT), 0);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAUNT), 1);
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 3);
}

// ------------------------------------------ SPELL - DRUID
// [VAN_CS2_011] Savage Roar - COST:3
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Give your characters +2 Attack this turn.
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - VAN_CS2_011 : Savage Roar")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer, Cards::FindCardByName("Savage Roar", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Dalaran Mage", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetAttack(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[1]->GetAttack(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetAttack(), 1);
}

// ------------------------------------------ SPELL - DRUID
// [VAN_CS2_012] Swipe - COST:4
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Deal 4 damage to an enemy and 1 damage
//       to all other enemies.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_ENEMY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - VAN_CS2_012 : Swipe")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Swipe", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Swipe", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->GetHealth(), 7);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField[1]->GetHealth(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 29);
    CHECK_EQ(opField[0]->GetHealth(), 3);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 25);
    CHECK_EQ(opField[0]->GetHealth(), 2);
}

// ------------------------------------------ SPELL - DRUID
// [VAN_CS2_013] Wild Growth - COST:2
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Gain an empty Mana Crystal.
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - VAN_CS2_013 : Wild Growth")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wild Growth", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wild Growth", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curPlayer->GetRemainingMana(), 7);
    CHECK_EQ(curPlayer->GetTotalMana(), 10);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->name, "Excess Mana");
    CHECK_EQ(curPlayer->GetRemainingMana(), 5);
    CHECK_EQ(curPlayer->GetTotalMana(), 10);

    game.Process(curPlayer, PlayCardTask::Spell(curHand[4]));
    CHECK_EQ(curHand.GetCount(), 5);
}

// ----------------------------------------- MINION - DRUID
// [VAN_CS2_232] Ironbark Protector - COST:8 [ATK:8/HP:8]
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - VAN_CS2_232 : Ironbark Protector")
{
    // Do nothing
}

// ------------------------------------------ SPELL - DRUID
// [VAN_EX1_154] Wrath - COST:2
// - Set: VANILLA, Rarity: Common
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
TEST_CASE("[Druid : Spell] - VAN_EX1_154 : Wrath")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wrath", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wrath", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));

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
// [VAN_EX1_155] Mark of Nature - COST:3
// - Set: VANILLA, Rarity: Common
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
TEST_CASE("[Druid : Spell] - VAN_EX1_155 : Mark of Nature")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Mark of Nature", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Mark of Nature", FormatType::CLASSIC));

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
// [VAN_EX1_158] Soul of the Forest - COST:4
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Give your minions
//       "<b>Deathrattle:</b> Summon a 2/2 Treant."
// --------------------------------------------------------
// RefTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - VAN_EX1_158 : Soul of the Forest")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card6 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card7 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Soul of the Forest", FormatType::CLASSIC));
    const auto card8 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Hellfire", FormatType::CLASSIC));

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
// [VAN_EX1_160] Power of the Wild - COST:2
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Choose One -</b> Give your minions +1/+1;
//       or Summon a 3/2 Panther.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - VAN_EX1_160 : Power of the Wild")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Power of the Wild", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Power of the Wild", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Power of the Wild", FormatType::CLASSIC));

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
// [VAN_EX1_161] Naturalize - COST:1
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Destroy a minion. Your opponent draws 2 cards.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - VAN_EX1_161 : Naturalize")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Naturalize", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Magma Rager", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    const auto curHandCount = curPlayer->GetHandZone()->GetCount();
    game.Process(opPlayer, PlayCardTask::SpellTarget(card1, card2));

    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), curHandCount + 2);
    CHECK_EQ(curPlayer->GetFieldZone()->GetCount(), 0);
}

// ------------------------------------------ SPELL - DRUID
// [VAN_EX1_164] Nourish - COST:5
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Choose One -</b> Gain 2 Mana Crystals;
//       or Draw 3 cards.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - VAN_EX1_164 : Nourish")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Nourish", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Nourish", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Nourish", FormatType::CLASSIC));

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
// [VAN_EX1_165] Druid of the Claw - COST:5 [ATK:4/HP:4]
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Choose One -</b> <b>Charge</b>;
//       or +2 Health and <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// --------------------------------------------------------
// RefTag:
// - CHARGE = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - VAN_EX1_165 : Druid of the Claw")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Druid of the Claw", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Druid of the Claw", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Silence", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1, 1));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[0]->CanAttack(), true);
    CHECK_EQ(curField[0]->HasTaunt(), false);

    game.Process(curPlayer, PlayCardTask::Minion(card2, 2));
    CHECK_EQ(curField[1]->GetAttack(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 6);
    CHECK_EQ(curField[1]->CanAttack(), false);
    CHECK_EQ(curField[1]->HasTaunt(), true);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, curField[1]));
    CHECK_EQ(curField[1]->GetAttack(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 6);
    CHECK_EQ(curField[1]->CanAttack(), false);
    CHECK_EQ(curField[1]->HasTaunt(), false);
}

// ----------------------------------------- MINION - DRUID
// [VAN_EX1_166] Keeper of the Grove - COST:4 [ATK:2/HP:4]
// - Set: VANILLA, Rarity: Rare
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
TEST_CASE("[Druid : Minion] - VAN_EX1_166 : Keeper of the Grove")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Keeper of the Grove", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Keeper of the Grove", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Archmage", FormatType::CLASSIC));

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

// ------------------------------------------ SPELL - DRUID
// [VAN_EX1_169] Innervate - COST:0
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Gain 2 Mana Crystals this turn only.
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - VAN_EX1_169 : Innervate")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Innervate", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Innervate", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Dragonling Mechanic", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetRemainingMana(), 10);
    CHECK_EQ(curPlayer->GetTemporaryMana(), 2);
    CHECK_EQ(curPlayer->GetTotalMana(), 8);
    CHECK_EQ(curPlayer->GetUsedMana(), 0);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curPlayer->GetRemainingMana(), 6);
    CHECK_EQ(curPlayer->GetTemporaryMana(), 0);
    CHECK_EQ(curPlayer->GetTotalMana(), 8);
    CHECK_EQ(curPlayer->GetUsedMana(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curPlayer->GetRemainingMana(), 10);
    CHECK_EQ(curPlayer->GetTemporaryMana(), 1);
    CHECK_EQ(curPlayer->GetTotalMana(), 9);
    CHECK_EQ(curPlayer->GetUsedMana(), 0);
}

// ------------------------------------------ SPELL - DRUID
// [VAN_EX1_173] Starfire - COST:6
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Deal 5 damage. Draw a card.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - VAN_EX1_173 : Starfire")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Starfire", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField[0]->GetHealth(), 7);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(opField[0]->GetHealth(), 2);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
}

// ----------------------------------------- MINION - DRUID
// [VAN_EX1_178] Ancient of War - COST:7 [ATK:5/HP:5]
// - Set: VANILLA, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Choose One -</b> +5 Attack;
//       or +5 Health and <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - CHOOSE_ONE = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Minion] - VAN_EX1_178 : Ancient of War")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Ancient of War", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Ancient of War", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1, 1));
    CHECK_EQ(curField[0]->GetHealth(), 10);
    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAUNT), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2, 2));
    CHECK_EQ(opField[0]->GetAttack(), 10);
}

// ------------------------------------------ SPELL - DRUID
// [VAN_EX1_570] Bite - COST:4
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: Give your hero +4 Attack this turn. Gain 4 Armor.
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - VAN_EX1_570 : Bite")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Bite", FormatType::CLASSIC));

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
// [VAN_EX1_571] Force of Nature - COST:6
// - Set: VANILLA, Rarity: Epic
// --------------------------------------------------------
// Text: Summon three 2/2 Treants with <b>Charge</b>
//       that die at the end of the turn.
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
// RefTag:
// - CHARGE = 1
// --------------------------------------------------------
TEST_CASE("[Druid : Spell] - VAN_EX1_571 : Force of Nature")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Force of Nature", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Force of Nature", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    game.Process(curPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(curField.GetCount(), 3);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 6);
    CHECK_EQ(curField[3]->card->name, "Treant");
    CHECK_EQ(curField[3]->HasCharge(), true);
    CHECK_EQ(curField[4]->card->name, "Treant");
    CHECK_EQ(curField[4]->HasCharge(), true);
    CHECK_EQ(curField[5]->card->name, "Treant");
    CHECK_EQ(curField[5]->HasCharge(), true);

    curPlayer->SetUsedMana(0);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField.GetCount(), 7);
    CHECK_EQ(curField[6]->card->name, "Treant");
    CHECK_EQ(curField[6]->HasCharge(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 3);
}

// ----------------------------------------- MINION - DRUID
// [VAN_EX1_573] Cenarius - COST:9 [ATK:5/HP:8]
// - Set: VANILLA, Rarity: Legendary
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
TEST_CASE("[Druid : Minion] - VAN_EX1_573 : Cenarius")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Cenarius", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Cenarius", FormatType::CLASSIC));

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
// [VAN_EX1_578] Savagery - COST:1
// - Set: VANILLA, Rarity: Rare
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
TEST_CASE("[Druid : Spell] - VAN_EX1_578 : Savagery")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Malygos", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Savagery", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Savagery", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Bloodmage Thalnos", FormatType::CLASSIC));

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
// [VAN_NEW1_007] Starfall - COST:5
// - Set: VANILLA, Rarity: Rare
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
TEST_CASE("[Druid : Spell] - VAN_NEW1_007 : Starfall")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Starfall", FormatType::CLASSIC));
    const auto card6 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Starfall", FormatType::CLASSIC));
    const auto card7 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Starfall", FormatType::CLASSIC));

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
// [VAN_NEW1_008] Ancient of Lore - COST:7 [ATK:5/HP:5]
// - Set: VANILLA, Rarity: Epic
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
TEST_CASE("[Druid : Minion] - VAN_NEW1_008 : Ancient of Lore")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Ancient of Lore", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Ancient of Lore", FormatType::CLASSIC));

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

// ----------------------------------------- SPELL - HUNTER
// [VAN_CS2_084] Hunter's Mark - COST:0
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Change a minion's Health to 1.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - VAN_CS2_084 : Hunter's Mark")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
    config.player1Class = CardClass::SHAMAN;
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
        curPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Hunter's Mark", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField[0]->GetHealth(), 1);
}

// ---------------------------------------- MINION - HUNTER
// [VAN_CS2_237] Starving Buzzard - COST:2 [ATK:2/HP:1]
// - Race: Beast, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Whenever you summon a Beast, draw a card.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - VAN_CS2_237 : Starving Buzzard")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Starving Buzzard", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Ironfur Grizzly", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
}

// ---------------------------------------- MINION - HUNTER
// [VAN_DS1_070] Houndmaster - COST:4 [ATK:4/HP:3]
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give a friendly Beast +2/+2
//       and <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_FRIENDLY_TARGET = 0
// - REQ_TARGET_WITH_RACE = 20
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - VAN_DS1_070 : Houndmaster")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer, Cards::FindCardByName("Houndmaster", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Starving Buzzard", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAUNT), 0);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card3));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
    CHECK_EQ(curField[1]->GetAttack(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 3);
    CHECK_EQ(curField[1]->GetGameTag(GameTag::TAUNT), 1);
}

// ---------------------------------------- MINION - HUNTER
// [VAN_DS1_175] Timber Wolf - COST:1 [ATK:1/HP:1]
// - Race: Beast, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Your other Beasts have +1 Attack.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - VAN_DS1_175 : Timber Wolf")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer, Cards::FindCardByName("Timber Wolf", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Timber Wolf", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Starving Buzzard", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(curField[2]->GetAttack(), 3);
    CHECK_EQ(curField[2]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[2]->GetAttack(), 4);
    CHECK_EQ(curField[2]->GetHealth(), 1);
    CHECK_EQ(curField[3]->GetAttack(), 2);
    CHECK_EQ(curField[3]->GetHealth(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));
    game.Process(opPlayer, AttackTask(card5, card2));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->GetAttack(), 3);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[2]->GetAttack(), 3);
    CHECK_EQ(curField[2]->GetHealth(), 1);
}

// ---------------------------------------- MINION - HUNTER
// [VAN_DS1_178] Tundra Rhino - COST:5 [ATK:2/HP:5]
// - Race: Beast, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Your Beasts have <b>Charge</b>.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
// RefTag:
// - CHARGE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - VAN_DS1_178 : Tundra Rhino")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer, Cards::FindCardByName("Tundra Rhino", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Timber Wolf", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Starving Buzzard", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetGameTag(GameTag::CHARGE), 0);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetGameTag(GameTag::CHARGE), 1);
    CHECK_EQ(curField[1]->GetGameTag(GameTag::CHARGE), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetGameTag(GameTag::CHARGE), 1);
    CHECK_EQ(curField[1]->GetGameTag(GameTag::CHARGE), 1);
    CHECK_EQ(curField[2]->GetGameTag(GameTag::CHARGE), 1);
}

// ----------------------------------------- SPELL - HUNTER
// [VAN_DS1_183] Multi-Shot - COST:4
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Deal 3 damage to two random enemy minions.
// --------------------------------------------------------
// PlayReq:
// - REQ_MINIMUM_ENEMY_MINIONS = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - VAN_DS1_183 : Multi-Shot")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Multi-Shot", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Dalaran Mage", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Dalaran Mage", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Dalaran Mage", FormatType::CLASSIC));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    int totalHealth = opField[0]->GetHealth();
    CHECK_EQ(totalHealth, 4);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    totalHealth += opField[1]->GetHealth();
    CHECK_EQ(totalHealth, 8);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    totalHealth += opField[2]->GetHealth();
    CHECK_EQ(totalHealth, 12);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(opField.GetCount(), 3);
    totalHealth = opField[0]->GetHealth();
    totalHealth += opField[1]->GetHealth();
    totalHealth += opField[2]->GetHealth();
    CHECK_EQ(totalHealth, 6);
}

// ----------------------------------------- SPELL - HUNTER
// [VAN_DS1_184] Tracking - COST:1
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Look at the top 3 cards of your deck.
//       Draw one and discard the others.
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - VAN_DS1_184 : Tracking")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer, Cards::FindCardByName("Tracking", FormatType::CLASSIC));

    CHECK_EQ(curPlayer->GetDeckZone()->GetCount(), 5);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK(curPlayer->choice != nullptr);
    CHECK_EQ(curPlayer->choice->choices.size(), 3u);

    TestUtils::ChooseNthChoice(game, 1);
    CHECK_EQ(curPlayer->GetDeckZone()->GetCount(), 2);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
}

// ----------------------------------------- SPELL - HUNTER
// [VAN_DS1_185] Arcane Shot - COST:1
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Deal 2 damage.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - VAN_DS1_185 : Arcane Shot")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Arcane Shot", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Arcane Shot", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Arcane Shot", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Arcane Shot", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));
    const auto card6 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));

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

// ---------------------------------------- WEAPON - HUNTER
// [VAN_DS1_188] Gladiator's Longbow - COST:7
// - Set: VANILLA, Rarity: Epic
// --------------------------------------------------------
// Text: Your hero is <b>Immune</b> while attacking.
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 2
// --------------------------------------------------------
// RefTag:
// - IMMUNE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Weapon] - VAN_DS1_188 : Gladiator's Longbow")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Gladiator's Longbow", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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
    CHECK_EQ(curPlayer->GetHero()->IsImmune(), false);
}

// ---------------------------------------- MINION - HUNTER
// [VAN_EX1_531] Scavenging Hyena - COST:2 [ATK:2/HP:2]
// - Race: Beast, Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Whenever a friendly Beast dies, gain +2/+1.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - VAN_EX1_531 : Scavenging Hyena")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Scavenging Hyena", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Stonetusk Boar", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Bloodfen Raptor", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Arcane Explosion", FormatType::CLASSIC));

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
// [VAN_EX1_533] Misdirection - COST:2
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Secret:</b> When an enemy attacks your hero,
//       instead it attacks another random character.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - VAN_EX1_533 : Misdirection")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Misdirection", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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
// [VAN_EX1_534] Savannah Highmane - COST:6 [ATK:6/HP:5]
// - Race: Beast, Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon two 2/2 Hyenas.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - VAN_EX1_534 : Savannah Highmane")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Stonetusk Boar", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Savannah Highmane", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Loot Hoarder", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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
// [VAN_EX1_536] Eaglehorn Bow - COST:3 [ATK:3/HP:0]
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever a <b>Secret</b> is revealed,
//       gain +1 Durability.
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 2
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Weapon] - VAN_EX1_536 : Eaglehorn Bow")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Eaglehorn Bow", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Snipe", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Chillwind Yeti", FormatType::CLASSIC));

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
// [VAN_EX1_537] Explosive Shot - COST:5
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: Deal 5 damage to a minion and 2 damage
//       to adjacent ones.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - VAN_EX1_537 : Explosive Shot")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Chillwind Yeti", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Malygos", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Chillwind Yeti", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Explosive Shot", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Explosive Shot", FormatType::CLASSIC));

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
// [VAN_EX1_538] Unleash the Hounds - COST:3
// - Set: VANILLA, Rarity: Common
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
TEST_CASE("[Hunter : Spell] - VAN_EX1_538 : Unleash the Hounds")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Unleash the Hounds", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card6 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card7 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card8 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card9 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Unleash the Hounds", FormatType::CLASSIC));

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

// ----------------------------------------- SPELL - HUNTER
// [VAN_EX1_539] Kill Command - COST:3
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Deal 3 damage. If you control a Beast,
//       deal 5 damage instead.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - VAN_EX1_539 : Kill Command")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Kill Command", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Kill Command", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Ironfur Grizzly", FormatType::CLASSIC));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 22);
}

// ---------------------------------------- MINION - HUNTER
// [VAN_EX1_543] King Krush - COST:9 [ATK:8/HP:8]
// - Race: Beast, Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Charge</b>
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - CHARGE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Minion] - VAN_EX1_543 : King Krush")
{
    // Do nothing
}

// ----------------------------------------- SPELL - HUNTER
// [VAN_EX1_544] Flare - COST:1
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: All minions lose <b>Stealth</b>.
//       Destroy all enemy <b>Secrets</b>. Draw a card.
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - VAN_EX1_544 : Flare")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Worgen Infiltrator", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Misdirection", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Noble Sacrifice", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Worgen Infiltrator", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Flare", FormatType::CLASSIC));

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
// [VAN_EX1_549] Bestial Wrath - COST:1
// - Set: VANILLA, Rarity: Epic
// --------------------------------------------------------
// Text: Give a Beast +2 Attack and <b>Immune</b> this turn.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_TARGET_WITH_RACE = 20
// - REQ_FRIENDLY_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - IMMUNE = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - VAN_EX1_549 : Bestial Wrath")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Stonetusk Boar", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Bestial Wrath", FormatType::CLASSIC));

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
// [VAN_EX1_554] Snake Trap - COST:2
// - Set: VANILLA, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Secret:</b> When one of your minions is attacked,
//       summon three 1/1 Snakes.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - VAN_EX1_554 : Snake Trap")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Snake Trap", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Snake Trap", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Chillwind Yeti", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Chillwind Yeti", FormatType::CLASSIC));
    const auto card6 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card7 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card8 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card9 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));

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
// [VAN_EX1_609] Snipe - COST:2
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Secret:</b> After your opponent plays a minion,
//       deal 4 damage to it.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - VAN_EX1_609 : Snipe")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer, Cards::FindCardByName("Snipe", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Snipe", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Chillwind Yeti", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Bloodmage Thalnos", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Chillwind Yeti", FormatType::CLASSIC));
    const auto card6 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Chillwind Yeti", FormatType::CLASSIC));
    const auto card7 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Chillwind Yeti", FormatType::CLASSIC));

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
// [VAN_EX1_610] Explosive Trap - COST:2
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Secret:</b> When your hero is attacked,
//       deal 2 damage to all enemies.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - VAN_EX1_610 : Explosive Trap")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Explosive Trap", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Chillwind Yeti", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Bloodmage Thalnos", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Chillwind Yeti", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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
// [VAN_EX1_611] Freezing Trap - COST:2
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Secret:</b> When an enemy minion attacks,
//       return it to its owner's hand. It costs (2) more.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - VAN_EX1_611 : Freezing Trap")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Freezing Trap", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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
// [VAN_EX1_617] Deadly Shot - COST:3
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Destroy a random enemy minion.
// --------------------------------------------------------
// PlayReq:
// - REQ_MINIMUM_ENEMY_MINIONS = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - VAN_EX1_617 : Deadly Shot")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Magma Rager", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Deadly Shot", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Deadly Shot", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Deadly Shot", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Magma Rager", FormatType::CLASSIC));
    const auto card6 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Magma Rager", FormatType::CLASSIC));
    const auto card7 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Magma Rager", FormatType::CLASSIC));

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

// ----------------------------------------- SPELL - HUNTER
// [VAN_NEW1_031] Animal Companion - COST:3
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Summon a random Beast Companion.
// --------------------------------------------------------
// Entourage: NEW1_032, NEW1_033, NEW1_034
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
TEST_CASE("[Hunter : Spell] - VAN_NEW1_031 : Animal Companion")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Animal Companion", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fireball", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 2);

    const bool isMisha = curField[1]->card->id == "VAN_NEW1_032";
    const bool isLeokk = curField[1]->card->id == "VAN_NEW1_033";
    const bool isHuffer = curField[1]->card->id == "VAN_NEW1_034";
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

    SUBCASE("Misha - VAN_NEW1_032")
    {
        const auto card =
            Generic::DrawCard(curPlayer, Cards::FindCardByID("VAN_NEW1_032"));

        game.Process(curPlayer, PlayCardTask::Minion(card));
        CHECK_EQ(curField.GetCount(), 2);
        CHECK_EQ(curField[1]->GetAttack(), 4);
        CHECK_EQ(curField[1]->GetHealth(), 4);
        CHECK_EQ(curField[1]->HasTaunt(), true);
    }

    SUBCASE("Leokk - VAN_NEW1_033")
    {
        const auto card =
            Generic::DrawCard(curPlayer, Cards::FindCardByID("VAN_NEW1_033"));

        game.Process(curPlayer, PlayCardTask::Minion(card));
        CHECK_EQ(curField.GetCount(), 2);
        CHECK_EQ(curField[1]->GetAttack(), 2);
        CHECK_EQ(curField[1]->GetHealth(), 4);
        CHECK_EQ(curField[0]->GetAttack(), 4);
    }

    SUBCASE("Huffer - VAN_NEW1_034")
    {
        const auto card =
            Generic::DrawCard(curPlayer, Cards::FindCardByID("VAN_NEW1_034"));

        game.Process(curPlayer, PlayCardTask::Minion(card));
        CHECK_EQ(curField.GetCount(), 2);
        CHECK_EQ(curField[1]->GetAttack(), 4);
        CHECK_EQ(curField[1]->GetHealth(), 2);
        CHECK_EQ(curField[1]->HasCharge(), true);
    }
}

// ------------------------------------------- SPELL - MAGE
// [VAN_CS2_025] Arcane Explosion - COST:2
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Deal 1 damage to all enemy minions.
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - VAN_CS2_025 : Arcane Explosion")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Arcane Explosion", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Arcane Explosion", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));
    CHECK_EQ(opField.GetCount(), 3);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(opField.GetCount(), 0);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);
}

// ------------------------------------------- SPELL - MAGE
// [VAN_CS2_029] Fireball - COST:4
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Deal 6 damage.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - VAN_CS2_029 : Fireball")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer, Cards::FindCardByName("Fireball", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fireball", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fireball", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fireball", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));
    const auto card6 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));

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

// ----------------------------------------- SPELL - PRIEST
// [VAN_EX1_332] Silence - COST:0
// - Set: VANILLA, Rarity: Common
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
TEST_CASE("[Priest : Spell] - VAN_EX1_332 : Silence")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Silence", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Silence", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Leper Gnome", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Malygos", FormatType::CLASSIC));

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

// ---------------------------------------- SPELL - WARLOCK
// [VAN_CS2_062] Hellfire - COST:4
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Deal 3 damage to all characters.
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - VAN_CS2_062 : Hellfire")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Hellfire", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));

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
// [VAN_EX1_323] Lord Jaraxxus - COST:9 [ATK:3/HP:15]
// - Race: Demon, Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy your hero and
//       replace it with Lord Jaraxxus.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - VAN_EX1_323 : Lord Jaraxxus")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer, Cards::FindCardByName("Lord Jaraxxus", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 15);
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