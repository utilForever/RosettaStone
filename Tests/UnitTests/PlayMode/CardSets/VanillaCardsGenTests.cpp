// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetHeaders.hpp>

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

    const auto& curField = *(curPlayer->GetFieldZone());
    const auto& opField = *(opPlayer->GetFieldZone());

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
    CHECK(curPlayer->choice);
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
// [VAN_CS2_022] Polymorph - COST:4
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Transform a minion into a 1/1 Sheep.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - VAN_CS2_022 : Polymorph")
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Polymorph", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Polymorph", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card3));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card4));
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetAttack(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 1);
}

// ------------------------------------------- SPELL - MAGE
// [VAN_CS2_023] Arcane Intellect - COST:3
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Draw 2 cards.
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - VAN_CS2_023 : Arcane Intellect")
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

    const auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Arcane Intellect", FormatType::CLASSIC));

    CHECK_EQ(curHand.GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 6);
}

// ------------------------------------------- SPELL - MAGE
// [VAN_CS2_024] Frostbolt - COST:2
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Deal 3 damage to a character and <b>Freeze</b> it.
// --------------------------------------------------------
// GameTag:
// - FREEZE = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - VAN_CS2_024 : Frostbolt")
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
        curPlayer, Cards::FindCardByName("Frostbolt", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Frostbolt", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Frostbolt", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Frostbolt", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card6 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));

    auto& curField = *(curPlayer->GetFieldZone());

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
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);
    CHECK_EQ(opPlayer->GetHero()->IsFrozen(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card5));
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[0]->IsFrozen(), true);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 27);
    CHECK_EQ(curPlayer->GetHero()->IsFrozen(), true);
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
// [VAN_CS2_026] Frost Nova - COST:3
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Freeze</b> all enemy minions.
// --------------------------------------------------------
// GameTag:
// - FREEZE = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - VAN_CS2_026 : Frost Nova")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Frost Nova", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(opField[0]->GetHealth(), 2);
    CHECK_EQ(opField[0]->IsFrozen(), true);
    CHECK_EQ(opField[1]->GetHealth(), 1);
    CHECK_EQ(opField[1]->IsFrozen(), true);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);
    CHECK_EQ(opPlayer->GetHero()->IsFrozen(), false);
}

// ------------------------------------------- SPELL - MAGE
// [VAN_CS2_027] Mirror Image - COST:1
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Summon two 0/2 minions with <b>Taunt</b>.
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - VAN_CS2_027 : Mirror Image")
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
        curPlayer, Cards::FindCardByName("Mirror Image", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mirror Image", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mirror Image", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mirror Image", FormatType::CLASSIC));

    auto& curField = *(curPlayer->GetFieldZone());
    CHECK_EQ(curField.GetCount(), 0);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->GetAttack(), 0);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAUNT), 1);
    CHECK_EQ(curField[1]->GetAttack(), 0);
    CHECK_EQ(curField[1]->GetHealth(), 2);
    CHECK_EQ(curField[1]->GetGameTag(GameTag::TAUNT), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField.GetCount(), 4);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curField.GetCount(), 6);

    game.Process(curPlayer, PlayCardTask::Spell(card4));
    CHECK_EQ(curField.GetCount(), 7);
}

// ------------------------------------------- SPELL - MAGE
// [VAN_CS2_028] Blizzard - COST:6
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: Deal 2 damage to all enemy minions and <b>Freeze</b> them.
// --------------------------------------------------------
// GameTag:
// - FREEZE = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - VAN_CS2_028 : Blizzard")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Blizzard", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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

// ------------------------------------------- SPELL - MAGE
// [VAN_CS2_031] Ice Lance - COST:1
// - Set: VANILLA, Rarity: Common
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
TEST_CASE("[Mage : Spell] - VAN_CS2_031 : Ice Lance")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Ice Lance", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Ice Lance", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Ice Lance", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Ice Lance", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Bloodmage Thalnos", FormatType::CLASSIC));
    const auto card6 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Ancient Watcher", FormatType::CLASSIC));
    const auto card7 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Ancient Watcher", FormatType::CLASSIC));

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
// [VAN_CS2_032] Flamestrike - COST:7
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Deal 4 damage to all enemy minions.
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - VAN_CS2_032 : Flamestrike")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Flamestrike", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 3);
}

// ------------------------------------------ MINION - MAGE
// [VAN_CS2_033] Water Elemental - COST:4 [ATK:3/HP:6]
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Freeze</b> any character damaged by this minion.
// --------------------------------------------------------
// GameTag:
// - FREEZE = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - VAN_CS2_033 : Water Elemental")
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Water Elemental", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Chillwind Yeti", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(card1, card2));

    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(opField[0]->GetHealth(), 2);
    CHECK_EQ(curField[0]->IsFrozen(), false);
    CHECK_EQ(opField[0]->IsFrozen(), true);
}

// ------------------------------------------ MINION - MAGE
// [VAN_EX1_274] Ethereal Arcanist - COST:4 [ATK:3/HP:3]
// - Set: VANILLA, Rarity: Rare
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
TEST_CASE("[Mage : Minion] - VAN_EX1_274 : Ethereal Arcanist")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Ethereal Arcanist", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Counterspell", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Counterspell", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Counterspell", FormatType::CLASSIC));

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
// [VAN_EX1_275] Cone of Cold - COST:4
// - Set: VANILLA, Rarity: Common
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
TEST_CASE("[Mage : Spell] - VAN_EX1_275 : Cone of Cold")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Flame Imp", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Flame Imp", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Flame Imp", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Flame Imp", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Flame Imp", FormatType::CLASSIC));
    const auto card6 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Cone of Cold", FormatType::CLASSIC));

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
// [VAN_EX1_277] Arcane Missiles - COST:1
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Deal 3 damage randomly split among all enemy characters.
// --------------------------------------------------------
// GameTag:
// - ImmuneToSpellpower = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - VAN_EX1_277 : Arcane Missiles")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Arcane Missiles", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Arcane Missiles", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    int totalHealth = opPlayer->GetHero()->GetHealth();
    totalHealth += opField[0]->GetHealth();
    CHECK_EQ(totalHealth, 37);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    totalHealth = opPlayer->GetHero()->GetHealth();
    totalHealth += opField[0]->GetHealth();
    CHECK_EQ(totalHealth, 34);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    totalHealth = opPlayer->GetHero()->GetHealth();
    totalHealth += opField[0]->GetHealth();
    CHECK_EQ(totalHealth, 31);
}

// ------------------------------------------- SPELL - MAGE
// [VAN_EX1_279] Pyroblast - COST:10
// - Set: VANILLA, Rarity: Epic
// --------------------------------------------------------
// Text: Deal 10 damage.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - VAN_EX1_279 : Pyroblast")
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
        curPlayer, Cards::FindCardByName("Pyroblast", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Pyroblast", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Pyroblast", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Pyroblast", FormatType::CLASSIC));
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
// [VAN_EX1_287] Counterspell - COST:3
// - Set: VANILLA, Rarity: Rare
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
TEST_CASE("[Mage : Spell] - VAN_EX1_287 : Counterspell")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Counterspell", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fireball", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Lightning Bolt", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Lightning Bolt", FormatType::CLASSIC));

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
// [VAN_EX1_289] Ice Barrier - COST:3
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Secret:</b> As soon as your hero is attacked,
//       gain 8 Armor.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - VAN_EX1_289 : Ice Barrier")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Ice Barrier", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Fiery War Axe", FormatType::CLASSIC));

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
// [VAN_EX1_294] Mirror Entity - COST:3
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Secret:</b> When your opponent plays a minion,
//       summon a copy of it.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - VAN_EX1_294 : Mirror Entity")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mirror Entity", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mirror Entity", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card6 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card7 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card8 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card9 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Injured Blademaster", FormatType::CLASSIC));
    const auto card10 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Injured Blademaster", FormatType::CLASSIC));

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
// [VAN_EX1_295] Ice Block - COST:3
// - Set: VANILLA, Rarity: Epic
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
TEST_CASE("[Mage : Spell] - VAN_EX1_295 : Ice Block")
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

    auto curSecret = curPlayer->GetSecretZone();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Ice Block", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Fireball", FormatType::CLASSIC));

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
// [VAN_EX1_559] Archmage Antonidas - COST:7 [ATK:5/HP:7]
// - Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: Whenever you cast a spell,
//       add a 'Fireball' spell to your hand.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - VAN_EX1_559 : Archmage Antonidas")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Archmage Antonidas", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Frostbolt", FormatType::CLASSIC));

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
// [VAN_EX1_594] Vaporize - COST:3
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Secret:</b> When a minion attacks your hero,
//       destroy it.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - VAN_EX1_594 : Vaporize")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Vaporize", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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
// [VAN_EX1_608] Sorcerer's Apprentice - COST:2 [ATK:3/HP:2]
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Your spells cost (1) less.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - VAN_EX1_608 : Sorcerer's Appretice")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Sorcerer's Apprentice", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Sorcerer's Apprentice", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fireball", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Silence", FormatType::CLASSIC));

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
// [VAN_EX1_612] Kirin Tor Mage - COST:3 [ATK:4/HP:3]
// - Set: VANILLA, Rarity: Rare
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
TEST_CASE("[Mage : Minion] - VAN_EX1_612 : Kirin Tor Mage")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Kirin Tor Mage", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Kirin Tor Mage", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Ice Barrier", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Ice Barrier", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fireball", FormatType::CLASSIC));

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
// [VAN_NEW1_012] Mana Wyrm - COST:1 [ATK:1/HP:3]
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Whenever you cast a spell, gain +1 Attack.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Minion] - VAN_NEW1_012 : Mana Wyrm")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        Generic::DrawCard(curPlayer, Cards::FindCardByID("VAN_NEW1_012"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fireball", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fireball", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Lightning Bolt", FormatType::CLASSIC));

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
// [VAN_tt_010] Spellbender - COST:3
// - Set: VANILLA, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Secret:</b> When an enemy casts a spell on a minion,
//       summon a 1/3 as the new target.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Mage : Spell] - VAN_tt_010 : Spellbender")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Spellbender", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Fireball", FormatType::CLASSIC));

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
// [VAN_CS2_087] Blessing of Might - COST:1
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Give a minion +3 Attack.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Paladin : SPell] - VAN_CS2_087 : Blessing of Might")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Blessing of Might", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 3);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField[0]->GetAttack(), 6);
}

// --------------------------------------- MINION - PALADIN
// [VAN_CS2_088] Guardian of Kings - COST:7 [ATK:5/HP:6]
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Restore 6 Health to your hero.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - VAN_CS2_088 : Guardian of Kings")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
    config.player1Class = CardClass::PALADIN;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Guardian of Kings", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 26);
}

// ---------------------------------------- SPELL - PALADIN
// [VAN_CS2_089] Holy Light - COST:2
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Restore 6 Health.
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - VAN_CS2_089 : Holy Light")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Holy Light", FormatType::CLASSIC));

    curPlayer->GetHero()->SetDamage(15);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 21);
}

// --------------------------------------- WEAPON - PALADIN
// [VAN_CS2_091] Light's Justice - COST:1 [ATK:1/HP:0]
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 4
// --------------------------------------------------------
TEST_CASE("[Paladin : Weapon] - VAN_CS2_091 : Light's Justice")
{
    // Do nothing
}

// ---------------------------------------- SPELL - PALADIN
// [VAN_CS2_092] Blessing of Kings - COST:4
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Give a minion +4/+4. <i>(+4 Attack/+4 Health)</i>
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - VAN_CS2_092 : Blessing of Kings")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Blessing of Kings", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField[0]->GetAttack(), 7);
    CHECK_EQ(curField[0]->GetHealth(), 5);
}

// ---------------------------------------- SPELL - PALADIN
// [VAN_CS2_093] Consecration - COST:4
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Deal 2 damage to all enemies.
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - VAN_CS2_093 : Consecration")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Consecration", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));

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

// ---------------------------------------- SPELL - PALADIN
// [VAN_CS2_094] Hammer of Wrath - COST:4
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Deal 3 damage. Draw a card.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - VAN_CS2_094 : Hammer of Wrath")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Hammer of Wrath", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(opField[0]->GetHealth(), 4);
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
}

// --------------------------------------- WEAPON - PALADIN
// [VAN_CS2_097] Truesilver Champion - COST:4 [ATK:4/HP:0]
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Whenever your hero attacks, restore 2 Health to it.
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 2
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Weapon] - VAN_CS2_097 : Truesilver Champion")
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
    curPlayer->GetHero()->SetDamage(4);

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Truesilver Champion", FormatType::CLASSIC));

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

// ---------------------------------------- SPELL - PALADIN
// [VAN_EX1_130] Noble Sacrifice - COST:1
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Secret:</b> When an enemy attacks,
//       summon a 2/1 Defender as the new target.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - VAN_EX1_130 : Noble Sacrifice")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Noble Sacrifice", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Noble Sacrifice", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Fiery War Axe", FormatType::CLASSIC));
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
// [VAN_EX1_132] Eye for an Eye - COST:1
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Secret:</b> When your hero takes damage,
//       deal that much damage to the enemy hero.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - VAN_EX1_132 : Eye for an Eye")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Eye for an Eye", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Eye for an Eye", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Fiery War Axe", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Mortal Strike", FormatType::CLASSIC));

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
// [VAN_EX1_136] Redemption - COST:1
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Secret:</b> When a friendly minion dies,
//       return it to life with 1 Health.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - VAN_EX1_136 : Redemption")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Redemption", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Argent Protector", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Fiery War Axe", FormatType::CLASSIC));

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
// [VAN_EX1_349] Divine Favor - COST:3
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: Draw cards until you have as many in hand
//       as your opponent.
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - VAN_EX1_349 : Divine Favor")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Divine Favor", FormatType::CLASSIC));

    Generic::DrawCard(opPlayer, Cards::FindCardByName("Sense Demons"));
    Generic::DrawCard(opPlayer, Cards::FindCardByName("Sense Demons"));
    Generic::DrawCard(opPlayer, Cards::FindCardByName("Sense Demons"));
    Generic::DrawCard(opPlayer, Cards::FindCardByName("Sense Demons"));

    game.Process(curPlayer, PlayCardTask::Spell(card1));

    CHECK_EQ(curPlayer->GetHandZone()->GetCount(),
             opPlayer->GetHandZone()->GetCount());
}

// ---------------------------------------- SPELL - PALADIN
// [VAN_EX1_354] Lay on Hands - COST:8
// - Set: VANILLA, Rarity: Epic
// --------------------------------------------------------
// Text: Restore 8 Health. Draw 3 cards.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - VAN_EX1_354 : Lay on Hands")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Lay on Hands", FormatType::CLASSIC));

    const auto curHandCount = curPlayer->GetHandZone()->GetCount();

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, curPlayer->GetHero()));

    CHECK_EQ(curHandCount + 2, curPlayer->GetHandZone()->GetCount());
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 29);
}

// ---------------------------------------- SPELL - PALADIN
// [VAN_EX1_355] Blessed Champion - COST:5
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: Double a minion's Attack.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - VAN_EX1_355 : Blessed Champion")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Blessed Champion", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Tirion Fordring", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField[0]->GetAttack(), 12);
}

// ---------------------------------------- SPELL - PALADIN
// [VAN_EX1_360] Humility - COST:1
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Change a minion's Attack to 1.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - VAN_EX1_360 : Humility")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Humility", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField[0]->GetAttack(), 6);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(opField[0]->GetAttack(), 1);
}

// --------------------------------------- MINION - PALADIN
// [VAN_EX1_362] Argent Protector - COST:2 [ATK:2/HP:2]
// - Set: VANILLA, Rarity: Common
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
TEST_CASE("[Paladin : Minion] - VAN_EX1_362 : Argent Protector")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Magma Rager", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Argent Protector", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card1));
    CHECK_EQ(curField[0]->HasDivineShield(), true);
}

// ---------------------------------------- SPELL - PALADIN
// [VAN_EX1_363] Blessing of Wisdom - COST:1
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Choose a minion. Whenever it attacks, draw a card.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - VAN_EX1_363 : Blessing of Wisdom")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Blessing of Wisdom", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 4);

    game.Process(curPlayer, AttackTask(card2, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
}

// ---------------------------------------- SPELL - PALADIN
// [VAN_EX1_365] Holy Wrath - COST:5
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: Draw a card and deal damage equal to its Cost.
// --------------------------------------------------------
// GameTag:
// - AFFECTED_BY_SPELL_POWER = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - VAN_EX1_365 : Holy Wrath")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Holy Wrath", FormatType::CLASSIC));

    CHECK_EQ(curHand.GetCount(), 5);
    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(curHand.GetCount(), 5);

    Entity* drawnCard = curHand[curHand.GetCount() - 1];
    const int cardCost = drawnCard->card->gameTags[GameTag::COST];
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30 - cardCost);
}

// --------------------------------------- WEAPON - PALADIN
// [VAN_EX1_366] Sword of Justice - COST:3 [ATK:1/HP:0]
// - Set: VANILLA, Rarity: Epic
// --------------------------------------------------------
// Text: After you summon a minion,
//       give it +1/+1 and this loses 1 Durability.
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 5
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Weapon] - VAN_EX1_366 : Sword of Justice")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Sword of Justice", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));

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
// [VAN_EX1_371] Hand of Protection - COST:1
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Give a minion <b>Divine Shield</b>.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - VAN_EX1_371 : Hand of Protection")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Hand of Protection", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Hammer of Wrath", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->GetHealth(), 7);
    CHECK_EQ(opField[0]->GetGameTag(GameTag::DIVINE_SHIELD), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(opField[0]->GetHealth(), 7);
    CHECK_EQ(opField[0]->GetGameTag(GameTag::DIVINE_SHIELD), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3));
    CHECK_EQ(opField[0]->GetHealth(), 7);
    CHECK_EQ(opField[0]->GetGameTag(GameTag::DIVINE_SHIELD), 0);
}

// ---------------------------------------- SPELL - PALADIN
// [VAN_EX1_379] Repentance - COST:1
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Secret:</b> After your opponent plays a minion,
//       reduce its Health to 1.
// --------------------------------------------------------
// GameTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - VAN_EX1_379 : Repentance")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Repentance", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Grommash Hellscream", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curSecret->GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curSecret->GetCount(), 0);
    CHECK_EQ(opField[0]->GetHealth(), 1);
}

// --------------------------------------- MINION - PALADIN
// [VAN_EX1_382] Aldor Peacekeeper - COST:3 [ATK:3/HP:3]
// - Set: VANILLA, Rarity: Rare
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
TEST_CASE("[Paladin : Minion] - VAN_EX1_382 : Aldor Peacekeeper")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer, Cards::FindCardByName("Magma Rager", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Aldor Peacekeeper", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::MinionTarget(card2, card1));
    CHECK_EQ(curField[0]->GetAttack(), 1);
}

// --------------------------------------- MINION - PALADIN
// [VAN_EX1_383] Tirion Fordring - COST:8 [ATK:6/HP:6]
// - Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: <b><b>Divine Shield</b>,</b> <b>Taunt</b>
//       <b>Deathrattle:</b> Equip a 5/3 Ashbringer.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - DEATHRATTLE = 1
// - DIVINE_SHIELD = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Minion] - VAN_EX1_383 : Tirion Fordring")
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Tirion Fordring", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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
// [VAN_EX1_384] Avenging Wrath - COST:6
// - Set: VANILLA, Rarity: Epic
// --------------------------------------------------------
// Text: Deal 8 damage randomly split
//       among all enemy characters.
// --------------------------------------------------------
// GameTag:
// - ImmuneToSpellpower = 1
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - VAN_EX1_384 : Avenging Wrath")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Avenging Wrath", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Avenging Wrath", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Malygos", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Bloodmage Thalnos", FormatType::CLASSIC));

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
// [VAN_EX1_619] Equality - COST:2
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: Change the Health of all minions to 1.
// --------------------------------------------------------
TEST_CASE("[Paladin : Spell] - VAN_EX1_619 : Equality")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Tirion Fordring", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Tirion Fordring", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Equality", FormatType::CLASSIC));

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
// [VAN_CS1_112] Holy Nova - COST:5
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Deal 2 damage to all enemies.
//       Restore 2 Health to all friendly characters.
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - VAN_CS1_112 : Holy Nova")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Windfury Harpy", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Holy Nova", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Argent Squire", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Worgen Infiltrator", FormatType::CLASSIC));

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
// [VAN_CS1_113] Mind Control - COST:10
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Take control of an enemy minion.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_ENEMY_TARGET = 0
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - VAN_CS1_113 : Mind Control")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto& curField = *(curPlayer->GetFieldZone());
    const auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Windfury Harpy", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mind Control", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Mind Control", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card2));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(opField.GetCount(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer,
                 PlayCardTask::SpellTarget(card4, curPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 8);
}

// ----------------------------------------- SPELL - PRIEST
// [VAN_CS1_129] Inner Fire - COST:1
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Change a minion's Attack to be equal to its Health.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - VAN_CS1_129 : Inner Fire")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer, Cards::FindCardByName("Inner Fire", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Divine Spirit", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Inner Fire", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Inner Fire", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Northshire Cleric", FormatType::CLASSIC));

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

// ----------------------------------------- SPELL - PRIEST
// [VAN_CS1_130] Holy Smite - COST:1
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Deal 2 damage.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - VAN_CS1_130 : Holy Smite")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer, Cards::FindCardByName("Holy Smite", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Holy Smite", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Holy Smite", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Holy Smite", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));
    const auto card6 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card5));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card6));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card6));
    CHECK_EQ(opField[0]->GetHealth(), 5);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card5));
    CHECK_EQ(curField.GetCount(), 0);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, curPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 28);
}

// ----------------------------------------- SPELL - PRIEST
// [VAN_CS2_003] Mind Vision - COST:1
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Put a copy of a random card in your opponent's
//       hand into your hand.
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - VAN_CS2_003 : Mind Vision")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mind Vision", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    const auto gainedCard = curHand[4];

    bool flag = false;
    for (const auto& handCard : opPlayer->GetHandZone()->GetAll())
    {
        if (handCard->card->id == gainedCard->card->id)
        {
            flag = true;
            break;
        }
    }

    CHECK(flag);
}

// ----------------------------------------- SPELL - PRIEST
// [VAN_CS2_004] Power Word: Shield - COST:1
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Give a minion +2 Health. Draw a card.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - VAN_CS2_004 : Power Word: Shield")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    auto& curHand = *(curPlayer->GetHandZone());
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Power Word: Shield", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetRemainingMana(), 4);
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 7);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curPlayer->GetRemainingMana(), 3);
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 9);
}

// ----------------------------------------- SPELL - PRIEST
// [VAN_CS2_234] Shadow Word: Pain - COST:2
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Destroy a minion with 3 or less Attack.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_TARGET_MAX_ATTACK = 3
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - VAN_CS2_234 : Shadow Word: Pain")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Shadow Word: Pain", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));

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

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
    CHECK_EQ(opField.GetCount(), 1);
}

// ---------------------------------------- MINION - PRIEST
// [VAN_CS2_235] Northshire Cleric - COST:1 [ATK:1/HP:3]
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Whenever a minion is healed, draw a card.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - VAN_CS2_235 : Northshire Cleric")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Northshire Cleric", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Voodoo Doctor", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Voodoo Doctor", FormatType::CLASSIC));

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

// ----------------------------------------- SPELL - PRIEST
// [VAN_CS2_236] Divine Spirit - COST:2
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Double a minion's Health.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - VAN_CS2_236 : Divine Spirit")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Divine Spirit", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetHealth(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, AttackTask(card3, card2));
    CHECK_EQ(curField[0]->GetHealth(), 4);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField[0]->GetHealth(), 8);
}

// ----------------------------------------- SPELL - PRIEST
// [VAN_DS1_233] Mind Blast - COST:2
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Deal 5 damage to the enemy hero.
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - VAN_DS1_233 : Mind Blast")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mind Blast", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 25);
}

// ---------------------------------------- MINION - PRIEST
// [VAN_EX1_091] Cabal Shadow Priest - COST:6 [ATK:4/HP:5]
// - Set: VANILLA, Rarity: Epic
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
TEST_CASE("[Priest : Minion] - VAN_EX1_091 : Cabal Shadow Priest")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Cabal Shadow Priest", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Cabal Shadow Priest", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Stonetusk Boar", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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

// ----------------------------------------- SPELL - PRIEST
// [VAN_EX1_334] Shadow Madness - COST:4
// - Set: VANILLA, Rarity: Rare
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
TEST_CASE("[Priest : Spell] - VAN_EX1_334 : Shadow Madness")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Pit Lord", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Felguard", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Shadow Madness", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Shadow Madness", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card1));
    CHECK_EQ(opPlayer->GetRemainingMana(), 6);
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
    CHECK_EQ(opPlayer->GetRemainingMana(), 6);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(opField.GetCount(), 0);
}

// ---------------------------------------- MINION - PRIEST
// [VAN_EX1_335] Lightspawn - COST:4 [ATK:0/HP:5]
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: This minion's Attack is always equal to its Health.
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - VAN_EX1_335 : Lightspawn")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Lightspawn", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, AttackTask(card2, card1));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);
}

// ----------------------------------------- SPELL - PRIEST
// [VAN_EX1_339] Thoughtsteal - COST:3
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Copy 2 cards in your opponent's deck and
//       add them to your hand.
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - VAN_EX1_339 : Thoughtsteal")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.skipMulligan = true;
    config.doShuffle = false;

    for (int i = 0; i < 5; ++i)
    {
        config.player2Deck[i] =
            Cards::FindCardByName("Magma Rager", FormatType::CLASSIC);
    }
    config.player2Deck[5] =
        Cards::FindCardByName("Wolfrider", FormatType::CLASSIC);

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
        curPlayer, Cards::FindCardByName("Thoughtsteal", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetRemainingMana(), 7);
    CHECK_EQ((curHand[0]->card->name == "Magma Rager" ||
              curHand[0]->card->name == "Wolfrider"),
             true);
    CHECK_EQ((curHand[1]->card->name == "Magma Rager" ||
              curHand[1]->card->name == "Wolfrider"),
             true);
}

// ---------------------------------------- MINION - PRIEST
// [VAN_EX1_341] Lightwell - COST:2 [ATK:0/HP:5]
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: At the start of your turn, restore 3 Health
//       to a damaged friendly character.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - VAN_EX1_341 : Lightwell")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Lightwell", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Northshire Cleric", FormatType::CLASSIC));

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
// [VAN_EX1_345] Mindgames - COST:4
// - Set: VANILLA, Rarity: Epic
// --------------------------------------------------------
// Text: Put a copy of a random minion from
//       your opponent's deck into the battlefield.
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - VAN_EX1_345 : Mindgames")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.skipMulligan = true;
    config.doShuffle = false;

    for (int i = 0; i < 5; ++i)
    {
        config.player2Deck[i] =
            Cards::FindCardByName("Magma Rager", FormatType::CLASSIC);
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mindgames", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mindgames", FormatType::CLASSIC));

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
// [VAN_EX1_350] Prophet Velen - COST:7 [ATK:7/HP:7]
// - Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: Double the damage and healing of
//       your spells and Hero Power.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - VAN_EX1_350 : Prophet Velen")
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
    curPlayer->GetHero()->SetDamage(10);

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Prophet Velen", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mind Blast", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mind Blast", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Pyroblast", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Fireball", FormatType::CLASSIC));
    const auto card6 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Prophet Velen", FormatType::CLASSIC));
    const auto card7 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Prophet Velen", FormatType::CLASSIC));

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
// [VAN_EX1_591] Auchenai Soulpriest - COST:4 [ATK:3/HP:5]
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: Your cards and powers that restore Health
//       now deal damage instead.
// --------------------------------------------------------
TEST_CASE("[Priest : Minion] - VAN_EX1_591 : Auchenai Soulpriest")
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Auchenai Soulpriest", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Circle of Healing", FormatType::CLASSIC));

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
// [VAN_EX1_621] Circle of Healing - COST:0
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Restore 4 Health to all minions.
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - VAN_EX1_621 : Circle of Healing")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Bloodmage Thalnos", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Circle of Healing", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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

// ----------------------------------------- SPELL - PRIEST
// [VAN_EX1_622] Shadow Word: Death - COST:3
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Destroy a minion with 5 or more Attack.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_MIN_ATTACK = 5
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - VAN_EX1_622 : Shadow Word: Death")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Shadow Word: Death", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));

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
    CHECK_EQ(curPlayer->GetRemainingMana(), 7);
    CHECK_EQ(opField.GetCount(), 1);
}

// ---------------------------------------- MINION - PRIEST
// [VAN_EX1_623] Temple Enforcer - COST:6 [ATK:6/HP:6]
// - Set: VANILLA, Rarity: Common
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
TEST_CASE("[Priest : Minion] - VAN_EX1_623 : Temple Enforcer")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Temple Enforcer", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetRemainingMana(), 7);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(curPlayer->GetRemainingMana(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetAttack(), 6);
    CHECK_EQ(curField[1]->GetHealth(), 6);
}

// ----------------------------------------- SPELL - PRIEST
// [VAN_EX1_624] Holy Fire - COST:6
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: Deal 5 damage. Restore 5 Health to your hero.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - VAN_EX1_624 : Holy Fire")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Holy Fire", FormatType::CLASSIC));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 27);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 25);
}

// ----------------------------------------- SPELL - PRIEST
// [VAN_EX1_625] Shadowform - COST:3
// - Set: VANILLA, Rarity: Epic
// --------------------------------------------------------
// Text: Your Hero Power becomes 'Deal 2 damage.'
//       If already in Shadowform: 3 damage.
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - VAN_EX1_625 : Shadowform")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Shadowform", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Shadowform", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Shadowform", FormatType::CLASSIC));

    game.Process(curPlayer, HeroPowerTask(opHero));
    CHECK_EQ(opHero->GetHealth(), 29);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHero()->heroPower->card->name, "Mind Spike");

    game.Process(curPlayer, HeroPowerTask(opHero));
    CHECK_EQ(opHero->GetHealth(), 27);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask(opHero));
    CHECK_EQ(opHero->GetHealth(), 25);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curPlayer->GetHero()->heroPower->card->name, "Mind Shatter");

    game.Process(curPlayer, HeroPowerTask(opHero));
    CHECK_EQ(opHero->GetHealth(), 22);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask(opHero));
    CHECK_EQ(opHero->GetHealth(), 19);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curPlayer->GetHero()->heroPower->card->name, "Mind Shatter");

    game.Process(curPlayer, HeroPowerTask(opHero));
    CHECK_EQ(opHero->GetHealth(), 19);
}

// ----------------------------------------- SPELL - PRIEST
// [VAN_EX1_626] Mass Dispel - COST:4
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Silence</b> all enemy minions. Draw a card.
// --------------------------------------------------------
// GameTag:
// - SILENCE = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - VAN_EX1_626 : Mass Dispel")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mass Dispel", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Bloodmage Thalnos", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Bloodmage Thalnos", FormatType::CLASSIC));

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
// [VAN_CS2_072] Backstab - COST:0
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Deal 2 damage to an undamaged minion.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_UNDAMAGED_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - VAN_CS2_072 : Backstab")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Backstab", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Backstab", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));

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
// [VAN_CS2_073] Cold Blood - COST:1
// - Set: VANILLA, Rarity: Common
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
TEST_CASE("[Rogue : Spell] - VAN_CS2_073 : Cold Blood")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Cold Blood", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Cold Blood", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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
// [VAN_CS2_074] Deadly Poison - COST:1
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Give your weapon +2 Attack.
// --------------------------------------------------------
// PlayReq:
// - REQ_WEAPON_EQUIPPED = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - VAN_CS2_074 : Deadly Poison")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Deadly Poison", FormatType::CLASSIC));

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
// [VAN_CS2_075] Sinister Strike - COST:1
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Deal 3 damage to the enemy hero.
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - VAN_CS2_075 : Sinister Strike")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Sinister Strike", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);
}

// ------------------------------------------ SPELL - ROGUE
// [VAN_CS2_076] Assassinate - COST:5
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Destroy an enemy minion.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_ENEMY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - VAN_CS2_076 : Assassinate")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Assassinate", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));

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
// [VAN_CS2_077] Sprint - COST:7
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Draw 4 cards.
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - VAN_CS2_077 : Sprint")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Sprint", FormatType::CLASSIC));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 8);
}

// ----------------------------------------- WEAPON - ROGUE
// [VAN_CS2_080] Assassin's Blade - COST:5 [ATK:2/HP:0]
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 5
// --------------------------------------------------------
TEST_CASE("[Rogue : Weapon] - VAN_CS2_080 : Assassin's Blade")
{
    // Do nothing
}

// ------------------------------------------ SPELL - ROGUE
// [VAN_CS2_233] Blade Flurry - COST:2
// - Set: VANILLA, Rarity: Rare
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
TEST_CASE("[Rogue : Spell] - VAN_CS2_233 : Blade Flurry")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer, Cards::FindCardByName("Leper Gnome", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Malygos", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Blade Flurry", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Blade Flurry", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Dalaran Mage", FormatType::CLASSIC));

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
// [VAN_EX1_124] Eviscerate - COST:2
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Deal 2 damage. <b>Combo:</b> Deal 4 damage instead.
// --------------------------------------------------------
// GameTag:
// - COMBO = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - VAN_EX1_124 : Eviscerate")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer, Cards::FindCardByName("Eviscerate", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Eviscerate", FormatType::CLASSIC));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 24);
}

// ------------------------------------------ SPELL - ROGUE
// [VAN_EX1_126] Betrayal - COST:2
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Force an enemy minion to deal its damage
//       to the minions next to it.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_ENEMY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - VAN_EX1_126 : Betrayal")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Betrayal", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Betrayal", FormatType::CLASSIC));
    const auto card6 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Betrayal", FormatType::CLASSIC));

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
// [VAN_EX1_128] Conceal - COST:1
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Give your minions <b>Stealth</b> until your next turn.
// --------------------------------------------------------
// RefTag:
// - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - VAN_EX1_128 : Conceal")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Conceal", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Patient Assassin", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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

// ------------------------------------------ SPELL - ROGUE
// [VAN_EX1_129] Fan of Knives - COST:3
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Deal 1 damage to all enemy minions. Draw a card.
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - VAN_EX1_129 : Fan of Knives")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fan of Knives", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fan of Knives", FormatType::CLASSIC));
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
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 7);
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 7);
    CHECK_EQ(opField.GetCount(), 0);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);
}

// ----------------------------------------- MINION - ROGUE
// [VAN_EX1_131] Defias Ringleader - COST:2 [ATK:2/HP:2]
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Combo:</b> Summon a 2/1 Defias Bandit.
// --------------------------------------------------------
// GameTag:
// - COMBO = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - VAN_EX1_131 : Defias Ringleader")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Defias Ringleader", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Defias Ringleader", FormatType::CLASSIC));

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
// [VAN_EX1_133] Perdition's Blade - COST:3 [ATK:2/HP:0]
// - Set: VANILLA, Rarity: Rare
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
TEST_CASE("[Rogue : Weapon] - VAN_EX1_133 : Perdition's Blade")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Perdition's Blade", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Perdition's Blade", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("SI:7 Agent", FormatType::CLASSIC));

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
// [VAN_EX1_134] SI:7 Agent - COST:3 [ATK:3/HP:3]
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Combo:</b> Deal 2 damage.
// --------------------------------------------------------
// GameTag:
// - COMBO = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_FOR_COMBO = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - VAN_EX1_134 : SI:7 Agent")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer, Cards::FindCardByName("SI:7 Agent", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("SI:7 Agent", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);
}

// ------------------------------------------ SPELL - ROGUE
// [VAN_EX1_137] Headcrack - COST:3
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: Deal 2 damage to the enemy hero.
//       <b>Combo:</b> Return this to your hand next turn.
// --------------------------------------------------------
// GameTag:
// - COMBO = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - VAN_EX1_137 : Headcrack")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Headcrack", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Headcrack", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Bloodmage Thalnos", FormatType::CLASSIC));

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
// [VAN_EX1_144] Shadowstep - COST:0
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Return a friendly minion to your hand.
//       It costs (2) less.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_FRIENDLY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - VAN_EX1_144 : Shadowstep")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer, Cards::FindCardByName("Shadowstep", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Shadowstep", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Shadowstep", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Stonetusk Boar", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("SI:7 Agent", FormatType::CLASSIC));
    const auto card6 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("SI:7 Agent", FormatType::CLASSIC));

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
// [VAN_EX1_145] Preparation - COST:0
// - Set: VANILLA, Rarity: Epic
// --------------------------------------------------------
// Text: The next spell you cast this turn costs (3) less.
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - VAN_EX1_145 : Preparation")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer, Cards::FindCardByName("Preparation", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Preparation", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Preparation", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Eviscerate", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Vanish", FormatType::CLASSIC));

    CHECK_EQ(card1->GetCost(), 0);
    CHECK_EQ(card2->GetCost(), 0);
    CHECK_EQ(card3->GetCost(), 0);
    CHECK_EQ(card4->GetCost(), 2);
    CHECK_EQ(card5->GetCost(), 6);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(card2->GetCost(), 0);
    CHECK_EQ(card3->GetCost(), 0);
    CHECK_EQ(card4->GetCost(), 0);
    CHECK_EQ(card5->GetCost(), 3);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(card3->GetCost(), 0);
    CHECK_EQ(card4->GetCost(), 0);
    CHECK_EQ(card5->GetCost(), 3);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card4, opPlayer->GetHero()));
    CHECK_EQ(card3->GetCost(), 0);
    CHECK_EQ(card5->GetCost(), 6);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(card5->GetCost(), 3);
}

// ------------------------------------------ SPELL - ROGUE
// [VAN_EX1_278] Shiv - COST:2
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Deal 1 damage. Draw a card.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - VAN_EX1_278 : Shiv")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Shiv", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Shiv", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Kobold Geomancer", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField[0]->GetHealth(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card4));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 8);
    CHECK_EQ(opField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curPlayer->GetCurrentSpellPower(), 1);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 7);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);
}

// ----------------------------------------- MINION - ROGUE
// [VAN_EX1_522] Patient Assassin - COST:2 [ATK:1/HP:1]
// - Set: VANILLA, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Stealth</b>.
//       Destroy any minion damaged by this minion.
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// - POISONOUS = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - VAN_EX1_522 : Patient Assassin")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Patient Assassin", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Chillwind Yeti", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(card1, card2));

    CHECK(card2->isDestroyed);
}

// ------------------------------------------ SPELL - ROGUE
// [VAN_EX1_581] Sap - COST:2
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Return an enemy minion to your opponent's hand.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_ENEMY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - VAN_EX1_581 : Sap")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Sap", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Blessing of Kings", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::SpellTarget(card3, card4));
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(opField[0]->GetAttack(), 7);
    CHECK_EQ(opField[0]->GetHealth(), 5);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card4));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 7);
    CHECK_EQ(opField[0]->GetAttack(), 3);
    CHECK_EQ(opField[0]->GetHealth(), 1);
}

// ----------------------------------------- MINION - ROGUE
// [VAN_EX1_613] Edwin VanCleef - COST:3 [ATK:2/HP:2]
// - Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Combo:</b> Gain +2/+2 for each card
//       played earlier this turn.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - COMBO = 1
// --------------------------------------------------------
TEST_CASE("[Rogue : Minion] - VAN_EX1_613 : Edwin VanCleef")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Edwin VanCleef", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Edwin VanCleef", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Edwin VanCleef", FormatType::CLASSIC));

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

// ------------------------------------------ SPELL - ROGUE
// [VAN_NEW1_004] Vanish - COST:6
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Return all minions to their owner's hand.
// --------------------------------------------------------
TEST_CASE("[Rogue : Spell] - VAN_NEW1_004 : Vanish")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Vanish", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Voidwalker", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 7);
    CHECK_EQ(opField.GetCount(), 0);
}

// ----------------------------------------- MINION - ROGUE
// [VAN_NEW1_005] Kidnapper - COST:6 [ATK:5/HP:3]
// - Set: VANILLA, Rarity: Epic
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
TEST_CASE("[Rogue : Minion] - VAN_NEW1_005 : Kidnapper")
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

    auto& opField = *(opPlayer->GetFieldZone());
    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Kidnapper", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Kidnapper", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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
// [VAN_NEW1_014] Master of Disguise - COST:4 [ATK:4/HP:4]
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give a friendly minion <b>Stealth</b>.
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
TEST_CASE("[Rogue : Minion] - VAN_NEW1_014 : Master of Disguise")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Master of Disguise", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->HasStealth(), false);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(curField[0]->HasStealth(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->HasStealth(), true);
}

// ----------------------------------------- SPELL - SHAMAN
// [VAN_CS2_037] Frost Shock - COST:1
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Deal 1 damage to an enemy character and
//       <b>Freeze</b> it.
// --------------------------------------------------------
// GameTag:
// - FREEZE = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_ENEMY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - VAN_CS2_037 : Frost Shock")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Frost Shock", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Frost Shock", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField.GetCount(), 2);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(opField[0]->GetHealth(), 1);
    CHECK_EQ(opField[0]->IsFrozen(), true);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card4));
    CHECK_EQ(opField.GetCount(), 1);
}

// ----------------------------------------- SPELL - SHAMAN
// [VAN_CS2_038] Ancestral Spirit - COST:2
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: Choose a minion. When that minion is destroyed,
//       return it to the battlefield.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - VAN_CS2_038 : Ancestral Spirit")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Magma Rager", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Ancestral Spirit", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Murloc Raider", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("River Crocolisk", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Murloc Raider", FormatType::CLASSIC));

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
// [VAN_CS2_039] Windfury - COST:2
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Give a minion <b>Windfury</b>.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - WINDFURY = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - VAN_CS2_039 : Windfury")
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
        curPlayer, Cards::FindCardByName("Windfury", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasWindfury(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 24);
    CHECK_EQ(curField[0]->IsExhausted(), true);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField[0]->HasWindfury(), true);
    CHECK_EQ(curField[0]->IsExhausted(), false);

    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 18);
    CHECK_EQ(curField[0]->IsExhausted(), true);
}

// ----------------------------------------- SPELL - SHAMAN
// [VAN_CS2_041] Ancestral Healing - COST:0
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Restore a minion to full Health and
//       give it <b>Taunt</b>.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - VAN_CS2_041 : Ancestral Healing")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
    config.player1Class = CardClass::SHAMAN;
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
    const auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Ancestral Healing", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Stonetusk Boar", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, AttackTask(card3, card1));
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(opField.GetCount(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField[0]->GetHealth(), 2);
    CHECK_EQ(curField[0]->GetGameTag(GameTag::TAUNT), 1);
}

// ---------------------------------------- MINION - SHAMAN
// [VAN_CS2_042] Fire Elemental - COST:6 [ATK:6/HP:5]
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 3 damage.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - VAN_CS2_042 : Fire Elemental")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Fire Elemental", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Fire Elemental", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->GetHealth(), 7);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, opField[0]));
    CHECK_EQ(opField[0]->GetHealth(), 4);
}

// ----------------------------------------- SPELL - SHAMAN
// [VAN_CS2_045] Rockbiter Weapon - COST:1
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Give a friendly character +3 Attack this turn.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_FRIENDLY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - VAN_CS2_045 : Rockbiter Weapon")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Rockbiter Weapon", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Rockbiter Weapon", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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
// [VAN_CS2_046] Bloodlust - COST:5
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Give your minions +3 Attack this turn.
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - VAN_CS2_046 : Bloodlust")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer, Cards::FindCardByName("Bloodlust", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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
// [VAN_CS2_053] Far Sight - COST:3
// - Set: VANILLA, Rarity: Epic
// --------------------------------------------------------
// Text: Draw a card. That card costs (3) less.
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - VAN_CS2_053 : Far Sight")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Far Sight", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curHand.GetCount(), 5);

    const Playable* drawCard = curHand[curHand.GetCount() - 1];
    const int cost = drawCard->card->gameTags[GameTag::COST] - 3;
    CHECK_EQ(cost < 0 ? 0 : cost, drawCard->GetCost());
}

// ----------------------------------------- SPELL - SHAMAN
// [VAN_EX1_238] Lightning Bolt - COST:1
// - Set: VANILLA, Rarity: Common
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
TEST_CASE("[Shaman : Spell] - VAN_EX1_238 : Lightning Bolt")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Lightning Bolt", FormatType::CLASSIC));

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
// [VAN_EX1_241] Lava Burst - COST:3
// - Set: VANILLA, Rarity: Rare
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
TEST_CASE("[Shaman : Spell] - VAN_EX1_241 : Lava Burst")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Lava Burst", FormatType::CLASSIC));

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
// [VAN_EX1_243] Dust Devil - COST:1 [ATK:3/HP:1]
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Windfury</b>. <b>Overload:</b> (2)
// --------------------------------------------------------
// GameTag:
// - OVERLOAD = 2
// - OVERLOAD_OWED = 2
// - WINDFURY = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - VAN_EX1_243 : Dust Devil")
{
    // Do nothing
}

// ----------------------------------------- SPELL - SHAMAN
// [VAN_EX1_244] Totemic Might - COST:0
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Give your Totems +2 Health.
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - VAN_EX1_244 : Totemic Might")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Totemic Might", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

    game.Process(curPlayer, HeroPowerTask());

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask());
    int totem1Health = curField[0]->GetHealth();
    int totem2Health = curField[1]->GetHealth();

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[2]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField[0]->GetHealth(), totem1Health + 2);
    CHECK_EQ(curField[1]->GetHealth(), totem2Health + 2);
    CHECK_EQ(curField[2]->GetHealth(), 1);
}

// ----------------------------------------- SPELL - SHAMAN
// [VAN_EX1_245] Earth Shock - COST:1
// - Set: VANILLA, Rarity: Common
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
TEST_CASE("[Shaman : Spell] - VAN_EX1_245 : Earth Shock")
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

    const auto& curField = *(curPlayer->GetFieldZone());
    const auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Bloodmage Thalnos", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Earth Shock", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    const int curHandCount = curHand.GetCount();

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));

    CHECK_EQ(curField.GetCount(), 0);
    CHECK_EQ(curHand.GetCount(), curHandCount);
}

// ----------------------------------------- SPELL - SHAMAN
// [VAN_EX1_246] Hex - COST:3
// - Set: VANILLA, Rarity: Free
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
TEST_CASE("[Shaman : Spell] - VAN_EX1_246 : Hex")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Hex", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Hex", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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

// ---------------------------------------- WEAPON - SHAMAN
// [VAN_EX1_247] Stormforged Axe - COST:2 [ATK:2/HP:0]
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Overload:</b> (1)
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 3
// - OVERLOAD = 1
// - OVERLOAD_OWED = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Weapon] - VAN_EX1_247 : Stormforged Axe")
{
    // Do nothing
}

// ----------------------------------------- SPELL - SHAMAN
// [VAN_EX1_248] Feral Spirit - COST:3
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: Summon two 2/3 Spirit Wolves with <b>Taunt</b>.
//       <b>Overload:</b> (2)
// --------------------------------------------------------
// GameTag:
// - OVERLOAD = 2
// - OVERLOAD_OWED = 2
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - VAN_EX1_248 : Feral Spirit")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer, Cards::FindCardByName("Feral Spirit", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(curField[1]->HasTaunt(), true);
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 3);

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
// [VAN_EX1_250] Earth Elemental - COST:5 [ATK:7/HP:8]
// - Set: VANILLA, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Taunt</b>.
//       <b><b>Overload</b>:</b> (3)
// --------------------------------------------------------
// GameTag:
// - OVERLOAD = 3
// - OVERLOAD_OWED = 3
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - VAN_EX1_250 : Earth Elemental")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Earth Elemental", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->HasTaunt(), true);
    CHECK_EQ(curField[0]->GetAttack(), 7);
    CHECK_EQ(curField[0]->GetHealth(), 8);

    CHECK_EQ(curPlayer->GetRemainingMana(), 5);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 3);
    CHECK_EQ(curPlayer->GetOverloadLocked(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetRemainingMana(), 7);
    CHECK_EQ(curPlayer->GetOverloadOwed(), 0);
    CHECK_EQ(curPlayer->GetOverloadLocked(), 3);
}

// ----------------------------------------- SPELL - SHAMAN
// [VAN_EX1_251] Forked Lightning - COST:1
// - Set: VANILLA, Rarity: Common
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
TEST_CASE("[Shaman : Spell] - VAN_EX1_251 : Forked Lightning")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Forked Lightning", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));

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
// [VAN_EX1_258] Unbound Elemental - COST:3 [ATK:2/HP:4]
// - Set: VANILLA, Rarity: Common
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
TEST_CASE("[Shaman : Minion] - VAN_EX1_258 : Unbound Elemental")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Unbound Elemental", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Earth Elemental", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Feral Spirit", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 4);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card3));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 6);
}

// ----------------------------------------- SPELL - SHAMAN
// [VAN_EX1_259] Lightning Storm - COST:3
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: Deal 2-3 damage to all enemy minions.
//       <b>Overload:</b> (2)
// --------------------------------------------------------
// GameTag:
// - OVERLOAD = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Spell] - VAN_EX1_259 : Lightning Storm")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Lightning Storm", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));

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
    CHECK((opField[0]->GetHealth() == 4 || opField[0]->GetHealth() == 5));
    CHECK((opField[1]->GetHealth() == 4 || opField[1]->GetHealth() == 5));
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
// [VAN_EX1_565] Flametongue Totem - COST:2 [ATK:0/HP:3]
// - Race: Totem, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Adjacent minions have +2 Attack.
// --------------------------------------------------------
// GameTag:
// - ADJACENT_BUFF = 1
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - VAN_EX1_565 : Flametongue Totem")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Flametongue Totem", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Flametongue Totem", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Flametongue Totem", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Flametongue Totem", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card6 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Dalaran Mage", FormatType::CLASSIC));
    const auto card7 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card8 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 0);
    CHECK_EQ(curField[0]->GetHealth(), 3);

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
    CHECK_EQ(curField[2]->GetHealth(), 3);

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
    CHECK_EQ(curField[4]->GetHealth(), 3);

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
    CHECK_EQ(curField[6]->GetHealth(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card8));
    game.Process(opPlayer, AttackTask(card8, card7));

    CHECK_EQ(curField[4]->GetAttack(), 2);
    CHECK_EQ(curField[4]->GetHealth(), 3);
    CHECK_EQ(curField[5]->GetAttack(), 2);
    CHECK_EQ(curField[5]->GetHealth(), 3);
}

// ---------------------------------------- WEAPON - SHAMAN
// [VAN_EX1_567] Doomhammer - COST:5 [ATK:2/HP:0]
// - Set: VANILLA, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Windfury, Overload:</b> (2)
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 8
// - WINDFURY = 1
// - OVERLOAD = 2
// - OVERLOAD_OWED = 2
// --------------------------------------------------------
TEST_CASE("[Shaman : Weapon] - VAN_EX1_567 : Doomhammer")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer, Cards::FindCardByName("Doomhammer", FormatType::CLASSIC));

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
// [VAN_EX1_575] Mana Tide Totem - COST:3 [ATK:0/HP:3]
// - Race: Totem, Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: At the end of your turn, draw a card.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - VAN_EX1_575 : Mana Tide Totem")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Mana Tide Totem", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
}

// ---------------------------------------- MINION - SHAMAN
// [VAN_EX1_587] Windspeaker - COST:4 [ATK:3/HP:3]
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give a friendly minion <b>Windfury</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_MINION_TARGET = 0
// - REQ_FRIENDLY_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - WINDFURY = 1
// --------------------------------------------------------
TEST_CASE("[Shaman : Minion] - VAN_EX1_587 : Windspeaker")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Windspeaker", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->HasWindfury(), false);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->HasWindfury(), false);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card3));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(opField[0]->HasWindfury(), false);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
    CHECK_EQ(curField[0]->HasWindfury(), true);
}

// ---------------------------------------- MINION - SHAMAN
// [VAN_NEW1_010] Al'Akir the Windlord - COST:8 [ATK:3/HP:5]
// - Set: VANILLA, Rarity: Legendary
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
TEST_CASE("[Shaman : Minion] - VAN_NEW1_010 : Al'Akir the Windlord")
{
    // Do nothing
}

// ---------------------------------------- SPELL - WARLOCK
// [VAN_CS2_057] Shadow Bolt - COST:3
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Deal 4 damage to a minion.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - VAN_CS2_057 : Shadow Bolt")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Shadow Bolt", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Shadow Bolt", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(opField[0]->GetHealth(), 3);

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);
}

// --------------------------------------- MINION - WARLOCK
// [VAN_CS2_059] Blood Imp - COST:1 [ATK:0/HP:1]
// - Race: Demon, Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Stealth</b>. At the end of your turn,
//       give another random friendly minion +1 Health.
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - VAN_CS2_059 : Blood Imp")
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
        curPlayer, Cards::FindCardByName("Blood Imp", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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
// [VAN_CS2_061] Drain Life - COST:3
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Deal 2 damage. Restore 2 Health to your hero.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - VAN_CS2_061 : Drain Life")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();

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
        opPlayer, Cards::FindCardByName("Drain Life", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    opPlayer->GetHero()->SetDamage(10);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField[0]->GetHealth(), 5);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 22);
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

// ---------------------------------------- SPELL - WARLOCK
// [VAN_CS2_063] Corruption - COST:1
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Choose an enemy minion.
//       At the start of your turn, destroy it.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_ENEMY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - VAN_CS2_063 : Corruption")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Corruption", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opField.GetCount(), 0);
}

// --------------------------------------- MINION - WARLOCK
// [VAN_CS2_064] Dread Infernal - COST:6 [ATK:6/HP:6]
// - Race: Demon, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 1 damage to all other characters.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - VAN_CS2_064 : Dread Infernal")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Dread Infernal", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 7);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 29);
    CHECK_EQ(curField[0]->GetHealth(), 6);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 29);
}

// --------------------------------------- MINION - WARLOCK
// [VAN_CS2_065] Voidwalker - COST:1 [ATK:1/HP:3]
// - Race: Demon, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - VAN_CS2_065 : Voidwalker")
{
    // Do nothing
}

// --------------------------------------- MINION - WARLOCK
// [VAN_EX1_301] Felguard - COST:3 [ATK:3/HP:5]
// - Race: Demon, Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Battlecry:</b> Destroy one of your Mana Crystals.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - VAN_EX1_301 : Felguard")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Felguard", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Felguard", FormatType::CLASSIC));

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
// [VAN_EX1_302] Mortal Coil - COST:1
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Deal 1 damage to a minion.
//       If that kills it, draw a card.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - VAN_EX1_302 : Mortal Coil")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mortal Coil", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mortal Coil", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));

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

// ---------------------------------------- SPELL - WARLOCK
// [VAN_EX1_303] Shadowflame - COST:4
// - Set: VANILLA, Rarity: Rare
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
TEST_CASE("[Warlock : Spell] - VAN_EX1_303 : Shadowflame")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Chillwind Yeti", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Chillwind Yeti", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Bloodmage Thalnos", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Chillwind Yeti", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Shadowflame", FormatType::CLASSIC));

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
// [VAN_EX1_304] Void Terror - COST:3 [ATK:3/HP:3]
// - Race: Demon, Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy both adjacent minions
//       and gain their Attack and Health.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - VAN_EX1_304 : Void Terror")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Void Terror", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Void Terror", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Flame Imp", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Blood Imp", FormatType::CLASSIC));

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
    CHECK_EQ(curField[0]->GetHealth(), 6);

    game.Process(curPlayer, PlayCardTask(card2, nullptr, 1));
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 9);
    CHECK_EQ(curField[0]->GetHealth(), 9);
}

// --------------------------------------- MINION - WARLOCK
// [VAN_EX1_306] Felstalker - COST:2 [ATK:4/HP:3]
// - Race: Demon, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Discard a random card.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - VAN_EX1_306 : Felstalker")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Felstalker", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 6);
}

// ---------------------------------------- SPELL - WARLOCK
// [VAN_EX1_308] Soulfire - COST:0
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Deal 4 damage. Discard a random card.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - VAN_EX1_308 : Soulfire")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Soulfire", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
    CHECK_EQ(opField.GetCount(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 4);
    CHECK_EQ(opField.GetCount(), 0);

    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Soulfire"));

    game.Process(curPlayer,
                 PlayCardTask::SpellTarget(card3, opPlayer->GetHero()));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 3);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 26);
}

// ---------------------------------------- SPELL - WARLOCK
// [VAN_EX1_309] Siphon Soul - COST:6
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: Destroy a minion. Restore 3 Health to your hero.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - VAN_EX1_309 : Siphon Soul")
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
    curPlayer->GetHero()->SetDamage(8);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Siphon Soul", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Voidwalker", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 22);
    CHECK_EQ(curField.GetCount(), 1);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 25);
    CHECK_EQ(curField.GetCount(), 0);
}

// --------------------------------------- MINION - WARLOCK
// [VAN_EX1_310] Doomguard - COST:5 [ATK:5/HP:7]
// - Race: Demon, Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Charge</b>.
//       <b>Battlecry:</b> Discard two random cards.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - CHARGE = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - VAN_EX1_310 : Doomguard")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Doomguard", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));

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
// [VAN_EX1_312] Twisting Nether - COST:8
// - Set: VANILLA, Rarity: Epic
// --------------------------------------------------------
// Text: Destroy all minions.
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - VAN_EX1_312 : Twisting Nether")
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Twisting Nether", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Voidwalker", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));

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
// [VAN_EX1_313] Pit Lord - COST:4 [ATK:5/HP:6]
// - Race: Demon, Set: VANILLA, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 5 damage to your hero.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - VAN_EX1_313 : Pit Lord")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Pit Lord", FormatType::CLASSIC));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 25);
}

// --------------------------------------- MINION - WARLOCK
// [VAN_EX1_315] Summoning Portal - COST:4 [ATK:0/HP:4]
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Your minions cost (2) less, but not less than (1).
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - VAN_EX1_315 : Summoning Portal")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; ++i)
    {
        config.player1Deck[i] =
            Cards::FindCardByName("Pit Lord", FormatType::CLASSIC);
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
        Cards::FindCardByName("Summoning Portal", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Summoning Portal", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Flame Imp", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Pit Lord", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Fireball", FormatType::CLASSIC));

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

    const auto card6 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Shadowstep", FormatType::CLASSIC));
    game.Process(curPlayer, PlayCardTask::SpellTarget(card6, card4));
    CHECK_EQ(card4->GetCost(), 0);
}

// ---------------------------------------- SPELL - WARLOCK
// [VAN_EX1_316] Power Overwhelming - COST:1
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Give a friendly minion +4/+4 until end of turn.
//       Then, it dies. Horribly.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_FRIENDLY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - VAN_EX1_316 : Power Overwhelming")
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
        curPlayer,
        Cards::FindCardByName("Power Overwhelming", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Goldshire Footman", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("King Mukla", FormatType::CLASSIC));

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
// [VAN_EX1_317] Sense Demons - COST:3
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Draw 2 Demons from your deck.
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - VAN_EX1_317 : Sense Demons")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;
    config.skipMulligan = true;
    config.doShuffle = false;

    for (int i = 0; i < 7; ++i)
    {
        config.player1Deck[i] =
            Cards::FindCardByName("Blood Imp", FormatType::CLASSIC);
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
        curPlayer, Cards::FindCardByName("Sense Demons", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Sense Demons", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curDeck.GetCount(), 1);
    CHECK_EQ(curHand[5]->card->name, "Blood Imp");
    CHECK_EQ(curHand[6]->card->name, "Blood Imp");

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curDeck.GetCount(), 0);
    CHECK_EQ(curHand[6]->card->name, "Blood Imp");
    CHECK_EQ(curHand[7]->card->name, "Worthless Imp");
}

// --------------------------------------- MINION - WARLOCK
// [VAN_EX1_319] Flame Imp - COST:1 [ATK:3/HP:2]
// - Race: Demon, Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 3 damage to your hero.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warlock : Minion] - VAN_EX1_319 : Flame Imp")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Flame Imp", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 27);
}

// ---------------------------------------- SPELL - WARLOCK
// [VAN_EX1_320] Bane of Doom - COST:5
// - Set: VANILLA, Rarity: Epic
// --------------------------------------------------------
// Text: Deal 2 damage to a character.
//       If that kills it, summon a random Demon.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - VAN_EX1_320 : Bane of Doom")
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
        curPlayer, Cards::FindCardByName("Magma Rager", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Chillwind Yeti", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Bane of Doom", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Bane of Doom", FormatType::CLASSIC));

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

// ---------------------------------------- SPELL - WARLOCK
// [VAN_EX1_596] Demonfire - COST:2
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Deal 2 damage to a minion.
//       If it's a friendly Demon, give it +2/+2 instead.
// --------------------------------------------------------
// PlayReq:
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - VAN_EX1_596 : Demonfire")
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Demonfire", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Demonfire", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Demonfire", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Bloodmage Thalnos", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Felguard", FormatType::CLASSIC));
    const auto card6 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Felguard", FormatType::CLASSIC));

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

// ---------------------------------------- SPELL - WARLOCK
// [VAN_NEW1_003] Sacrificial Pact - COST:0
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Destroy a Demon.
//       Restore 5 Health to your hero.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_TARGET_WITH_RACE = 15
// --------------------------------------------------------
TEST_CASE("[Warlock : Spell] - VAN_NEW1_003 : Sacrificial Pact")
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
    curPlayer->GetHero()->SetDamage(8);

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Sacrificial Pact", FormatType::CLASSIC));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Voidwalker"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card3));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 22);
    CHECK_EQ(curField.GetCount(), 2);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 27);
    CHECK_EQ(curField.GetCount(), 1);
}

// ---------------------------------------- SPELL - WARRIOR
// [VAN_CS2_103] Charge - COST:3
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Give a friendly minion +2 Attack and <b>Charge</b>.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_FRIENDLY_TARGET = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
// RefTag:
// - CHARGE = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - VAN_CS2_103 : Charge")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Charge", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->HasCharge(), false);

    game.Process(curPlayer, AttackTask(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    CHECK_EQ(curField[0]->GetAttack(), 8);
    CHECK_EQ(curField[0]->HasCharge(), true);

    game.Process(curPlayer, AttackTask(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 22);
}

// ---------------------------------------- SPELL - WARRIOR
// [VAN_CS2_104] Rampage - COST:2
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Give a damaged minion +3/+3.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_DAMAGED_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - VAN_CS2_104 : Rampage")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Rampage", FormatType::CLASSIC));

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
// [VAN_CS2_105] Heroic Strike - COST:2
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Give your hero +4 Attack this turn.
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - VAN_CS2_105 : Heroic Strike")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Heroic Strike", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Heroic Strike", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fiery War Axe", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 4);

    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 26);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 0);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Weapon(card3));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 3);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 7);

    game.Process(curPlayer,
                 AttackTask(curPlayer->GetHero(), opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 19);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curPlayer->GetHero()->GetAttack(), 3);
}

// --------------------------------------- WEAPON - WARRIOR
// [VAN_CS2_106] Fiery War Axe - COST:2 [ATK:3/HP:0]
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 2
// --------------------------------------------------------
TEST_CASE("[Warrior : Weapon] - VAN_CS2_106 : Fiery War Axe")
{
    // Do nothing
}

// ---------------------------------------- SPELL - WARRIOR
// [VAN_CS2_108] Execute - COST:1
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Destroy a damaged enemy minion.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// - REQ_ENEMY_TARGET = 0
// - REQ_DAMAGED_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - VAN_CS2_108 : Execute")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Execute", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));

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

// --------------------------------------- WEAPON - WARRIOR
// [VAN_CS2_112] Arcanite Reaper - COST:5 [ATK:5/HP:0]
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 2
// --------------------------------------------------------
TEST_CASE("[Warrior : Weapon] - VAN_CS2_112 : Arcanite Reaper")
{
    // Do nothing
}

// ---------------------------------------- SPELL - WARRIOR
// [VAN_CS2_114] Cleave - COST:2
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Deal 2 damage to two random enemy minions.
// --------------------------------------------------------
// PlayReq:
// - REQ_MINIMUM_ENEMY_MINIONS = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - VAN_CS2_114 : Cleave")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Cleave", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Cleave", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->GetHealth(), 7);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(opField[0]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    CHECK_EQ(opField[1]->GetHealth(), 7);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(opField[0]->GetHealth(), 3);
    CHECK_EQ(opField[1]->GetHealth(), 5);
}

// --------------------------------------- MINION - WARRIOR
// [VAN_EX1_084] Warsong Commander - COST:3 [ATK:2/HP:3]
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Whenever you summon a minion with 3 or less Attack,
//       give it <b>Charge</b>.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
// RefTag:
// - CHARGE = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - VAN_EX1_084 : Warsong Commander")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Warsong Commander", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Bloodfen Raptor", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Magma Rager", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->HasCharge(), false);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->HasCharge(), true);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[2]->HasCharge(), false);
}

// ---------------------------------------- SPELL - WARRIOR
// [VAN_EX1_391] Slam - COST:2
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Deal 2 damage to a minion.
//       If it survives, draw a card.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - VAN_EX1_391 : Slam")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Magma Rager", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Chillwind Yeti", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Slam", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Slam", FormatType::CLASSIC));

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
// [VAN_EX1_392] Battle Rage - COST:2
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Draw a card for each damaged friendly character.
// --------------------------------------------------------
// PlayReq:
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - VAN_EX1_392 : Battle Rage")
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
    curPlayer->GetHero()->SetDamage(1);
    opPlayer->GetHero()->SetDamage(1);

    auto& opField = *(opPlayer->GetFieldZone());
    auto& curHand = *(curPlayer->GetHandZone());
    auto& opHand = *(opPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Battle Rage", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Battle Rage", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Chillwind Yeti", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));

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
// [VAN_EX1_398] Arathi Weaponsmith - COST:4 [ATK:3/HP:3]
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Equip a 2/2 weapon.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - VAN_EX1_398 : Arathi Weaponsmith")
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Arathi Weaponsmith", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 2);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 2);
}

// ---------------------------------------- SPELL - WARRIOR
// [VAN_EX1_400] Whirlwind - COST:1
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Deal 1 damage to all minions.
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - VAN_EX1_400 : Whirlwind")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Whirlwind", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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
// [VAN_EX1_402] Armorsmith - COST:2 [ATK:1/HP:4]
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever a friendly minion takes damage,
//       gain 1 Armor.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - VAN_EX1_402 : Armorsmith")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Armorsmith", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Amani Berserker", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Frostbolt", FormatType::CLASSIC));

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
// [VAN_EX1_407] Brawl - COST:5
// - Set: VANILLA, Rarity: Epic
// --------------------------------------------------------
// Text: Destroy all minions except one.
//       <i>(chosen randomly)</i>
// --------------------------------------------------------
// PlayReq:
// - REQ_MINIMUM_TOTAL_MINIONS = 2
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - VAN_EX1_407 : Brawl")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Brawl", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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
// [VAN_EX1_408] Mortal Strike - COST:4
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: Deal 4 damage.
//       If you have 12 or less Health, deal 6 instead.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - VAN_EX1_408 : Mortal Strike")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mortal Strike", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mortal Strike", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fireball", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Fireball", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Fireball", FormatType::CLASSIC));

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
// [VAN_EX1_409] Upgrade! - COST:1
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: If you have a weapon, give it +1/+1.
//       Otherwise equip a 1/3 weapon.
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - VAN_EX1_409 : Upgrade!")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Upgrade!", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Upgrade!", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), true);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 1);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 3);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curPlayer->GetHero()->weapon->GetAttack(), 2);
    CHECK_EQ(curPlayer->GetHero()->weapon->GetDurability(), 4);
}

// ---------------------------------------- SPELL - WARRIOR
// [VAN_EX1_410] Shield Slam - COST:1
// - Set: VANILLA, Rarity: Epic
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
TEST_CASE("[Warrior : Spell] - VAN_EX1_410 : Shield Slam")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Shield Slam", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Shield Slam", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Bloodmage Thalnos", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Ironbark Protector", FormatType::CLASSIC));

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
// [VAN_EX1_411] Gorehowl - COST:7 [ATK:7/HP:0]
// - Set: VANILLA, Rarity: Epic
// --------------------------------------------------------
// Text: Attacking a minion costs 1 Attack instead of 1 Durability.
// --------------------------------------------------------
// GameTag:
// - DURABILITY = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Weapon] - VAN_EX1_411 : Gorehowl")
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
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Gorehowl", FormatType::CLASSIC));

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
// [VAN_EX1_414] Grommash Hellscream - COST:8 [ATK:4/HP:9]
// - Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Charge</b> <b>Enrage:</b> +6 Attack
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - CHARGE = 1
// --------------------------------------------------------
// RefTag:
// - ENRAGED = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - VAN_EX1_414 : Grommash Hellscream")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Grommash Hellscream", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Circle of Healing", FormatType::CLASSIC));

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
// [VAN_EX1_603] Cruel Taskmaster - COST:2 [ATK:2/HP:2]
// - Set: VANILLA, Rarity: Common
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
TEST_CASE("[Warrior : Minion] - VAN_EX1_603 : Cruel Taskmaster")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Cruel Taskmaster", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Cruel Taskmaster", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card1));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 1);
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 2);
}

// --------------------------------------- MINION - WARRIOR
// [VAN_EX1_604] Frothing Berserker - COST:3 [ATK:2/HP:4]
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever a minion takes damage, gain +1 Attack.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - VAN_EX1_604 : Frothing Berserker")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Frothing Berserker", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Stonetusk Boar", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Stonetusk Boar", FormatType::CLASSIC));

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
// [VAN_EX1_606] Shield Block - COST:3
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Gain 5 Armor.
//       Draw a card.
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - VAN_EX1_606 : Shield Block")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Shield Block", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Spell(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 8);
}

// ---------------------------------------- SPELL - WARRIOR
// [VAN_EX1_607] Inner Rage - COST:0
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Deal 1 damage to a minion and give it +2 Attack.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_TO_PLAY = 0
// - REQ_MINION_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - VAN_EX1_607 : Inner Rage")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Inner Rage", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 6);
    CHECK_EQ(curField[0]->GetHealth(), 7);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card1));
    CHECK_EQ(curField[0]->GetAttack(), 8);
    CHECK_EQ(curField[0]->GetHealth(), 6);
}

// --------------------------------------- MINION - WARRIOR
// [VAN_NEW1_011] Kor'kron Elite - COST:4 [ATK:4/HP:3]
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Charge</b>
// --------------------------------------------------------
// GameTag:
// - CHARGE = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - VAN_NEW1_011 : Kor'kron Elite")
{
    // Do nothing
}

// ---------------------------------------- SPELL - WARRIOR
// [VAN_NEW1_036] Commanding Shout - COST:2
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: Your minions can't be reduced below 1 Health this turn.
//       Draw a card.
// --------------------------------------------------------
TEST_CASE("[Warrior : Spell] - VAN_NEW1_036 : Commanding Shout")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Commanding Shout", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Commanding Shout", FormatType::CLASSIC));
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
// [VAN_CS1_042] Goldshire Footman - COST:1 [ATK:1/HP:2]
// - Faction: Alliance, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS1_042 : Goldshire Footman")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS1_069] Fen Creeper - COST:5 [ATK:3/HP:6]
// - Faction: Alliance, Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS1_069 : Fen Creeper")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_117] Earthen Ring Farseer - COST:3 [ATK:3/HP:3]
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Restore 3 Health.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_117 : Earthen Ring Farseer")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Earthen Ring Farseer", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Earthen Ring Farseer", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));

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
// [VAN_CS2_118] Magma Rager - COST:3 [ATK:5/HP:1]
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_118 : Magma Rager")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_119] Oasis Snapjaw - COST:4 [ATK:2/HP:7]
// - Race: Beast, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_119 : Oasis Snapjaw")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_120] River Crocolisk - COST:2 [ATK:2/HP:3]
// - Race: Beast, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_120 : River Crocolisk")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_121] Frostwolf Grunt - COST:2 [ATK:2/HP:2]
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_121 : Frostwolf Grunt")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_122] Raid Leader - COST:3 [ATK:2/HP:2]
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Your other minions have +1 Attack.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_122 : Raid Leader")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Raid Leader", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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
// [VAN_CS2_124] Wolfrider - COST:3 [ATK:3/HP:1]
// - Faction: Horde, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Charge</b>
// --------------------------------------------------------
// GameTag:
// - CHARGE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_124 : Wolfrider")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_125] Ironfur Grizzly - COST:3 [ATK:3/HP:3]
// - Race: Beast, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_125 : Ironfur Grizzly")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_127] Silverback Patriarch - COST:3 [ATK:1/HP:4]
// - Race: Beast, Faction: Horde, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_127 : Silverback Patriarch")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_131] Stormwind Knight - COST:4 [ATK:2/HP:5]
// - Faction: Alliance, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Charge</b>
// --------------------------------------------------------
// GameTag:
// - CHARGE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_131 : Stormwind Knight")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_141] Ironforge Rifleman - COST:3 [ATK:2/HP:2]
// - Faction: Alliance, Set: VANILLA, Rarity: Free
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
TEST_CASE("[Neutral : Minion] - VAN_CS2_141 : Ironforge Rifleman")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Ironforge Rifleman", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));

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
// [VAN_CS2_142] Kobold Geomancer - COST:2 [ATK:2/HP:2]
// - Faction: Horde, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Spell Damage +1</b>
// --------------------------------------------------------
// GameTag:
// - SPELLPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_142 : Kobold Geomancer")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_146] Southsea Deckhand - COST:1 [ATK:2/HP:1]
// - Race: Pirate, Faction: Alliance, Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Has <b>Charge</b> while you have a weapon equipped.
// --------------------------------------------------------
// RefTag:
// - CHARGE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_146 : Southsea Deckhand")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Southsea Deckhand", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Shadowstep", FormatType::CLASSIC));

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
// [VAN_CS2_147] Gnomish Inventor - COST:4 [ATK:2/HP:4]
// - Faction: Alliance, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Draw a card.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_147 : Gnomish Inventor")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Gnomish Inventor", FormatType::CLASSIC));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_150] Stormpike Commando - COST:5 [ATK:4/HP:2]
// - Faction: Alliance, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 2 damage.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_NONSELF_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_150 : Stormpike Commando")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Stormpike Commando", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Stormpike Commando", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opField[0]->GetHealth(), 7);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card2, card3));
    CHECK_EQ(opField[0]->GetHealth(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_151] Silver Hand Knight - COST:5 [ATK:4/HP:4]
// - Faction: Alliance, Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a 2/2 Squire.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_151 : Silver Hand Knight")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Silver Hand Knight", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 2);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_155] Archmage - COST:6 [ATK:4/HP:7]
// - Faction: Alliance, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Spell Damage +1</b>
// --------------------------------------------------------
// GameTag:
// - SPELLPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_155 : Archmage")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_161] Ravenholdt Assassin - COST:7 [ATK:7/HP:5]
// - Faction: Alliance, Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Stealth</b>
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_161 : Ravenholdt Assassin")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_162] Lord of the Arena - COST:6 [ATK:6/HP:5]
// - Faction: Alliance, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_162 : Lord of the Arena")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_168] Murloc Raider - COST:1 [ATK:2/HP:1]
// - Race: Murloc, Faction: Alliance, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_168 : Murloc Raider")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_169] Young Dragonhawk - COST:1 [ATK:1/HP:1]
// - Race: Beast, Faction: Horde, Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Windfury</b>
// --------------------------------------------------------
// GameTag:
// - WINDFURY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_169 : Young Dragonhawk")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_171] Stonetusk Boar - COST:1 [ATK:1/HP:1]
// - Race: Beast, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Charge</b>
// --------------------------------------------------------
// GameTag:
// - CHARGE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_171 : Stonetusk Boar")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_172] Bloodfen Raptor - COST:2 [ATK:3/HP:2]
// - Race: Beast, Faction: Horde, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_172 : Bloodfen Raptor")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_173] Bluegill Warrior - COST:2 [ATK:2/HP:1]
// - Race: Murloc, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Charge</b>
// --------------------------------------------------------
// GameTag:
// - CHARGE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_173 : Bluegill Warrior")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_179] Sen'jin Shieldmasta - COST:4 [ATK:3/HP:5]
// - Faction: Horde, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_179 : Sen'jin Shieldmasta")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_181] Injured Blademaster - COST:3 [ATK:4/HP:7]
// - Faction: Horde, Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 4 damage to HIMSELF.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_181 : Injured Blademaster")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Injured Blademaster", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_182] Chillwind Yeti - COST:4 [ATK:4/HP:5]
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_182 : Chillwind Yeti")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_186] War Golem - COST:7 [ATK:7/HP:7]
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_186 : War Golem")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_187] Booty Bay Bodyguard - COST:5 [ATK:5/HP:4]
// - Faction: Horde, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_187 : Booty Bay Bodyguard")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_188] Abusive Sergeant - COST:1 [ATK:2/HP:1]
// - Faction: Alliance, Set: VANILLA, Rarity: Common
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
TEST_CASE("[Neutral : Minion] - VAN_CS2_188 : Abusive Sergeant")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Abusive Sergeant", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Abusive Sergeant", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));

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
// [VAN_CS2_189] Elven Archer - COST:1 [ATK:1/HP:1]
// - Faction: Horde, Set: VANILLA, Rarity: Free
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
TEST_CASE("[Neutral : Minion] - VAN_CS2_189 : Elven Archer")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Elven Archer", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));

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
// [VAN_CS2_196] Razorfen Hunter - COST:3 [ATK:2/HP:3]
// - Faction: Horde, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a 1/1 Boar.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_196 : Razorfen Hunter")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Razorfen Hunter", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 3);
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_197] Ogre Magi - COST:4 [ATK:4/HP:4]
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Spell Damage +1</b>
// --------------------------------------------------------
// GameTag:
// - SPELLPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_197 : Ogre Magi")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_200] Boulderfist Ogre - COST:6 [ATK:6/HP:7]
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_200 : Boulderfist Ogre")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_201] Core Hound - COST:7 [ATK:9/HP:5]
// - Race: Beast, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_201 : Core Hound")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_203] Ironbeak Owl - COST:2 [ATK:2/HP:1]
// - Race: Beast, Faction: Horde, Set: VANILLA, Rarity: Common
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
TEST_CASE("[Neutral : Minion] - VAN_CS2_203 : Ironbeak Owl")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Ironbeak Owl", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Ironbeak Owl", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Leper Gnome", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Malygos", FormatType::CLASSIC));

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
// [VAN_CS2_213] Reckless Rocketeer - COST:6 [ATK:5/HP:2]
// - Faction: Horde, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Charge</b>
// --------------------------------------------------------
// GameTag:
// - CHARGE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_213 : Reckless Rocketeer")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_221] Spiteful Smith - COST:5 [ATK:4/HP:6]
// - Faction: Horde, Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Enrage:</b> Your weapon has +2 Attack.
// --------------------------------------------------------
// RefTag:
// - ENRAGED = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_221 : Spiteful Smith")
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Spiteful Smith", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Ironbeak Owl", FormatType::CLASSIC));

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
// [VAN_CS2_222] Stormwind Champion - COST:7 [ATK:6/HP:6]
// - Faction: Alliance, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Your other minions have +1/+1.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_222 : Stormwind Champion")
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Stormwind Champion", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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
    CHECK_EQ(curField[1]->GetAttack(), 6);
    CHECK_EQ(curField[1]->GetHealth(), 6);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, AttackTask(card3, card2));
    CHECK_EQ(curField[0]->GetAttack(), 7);
    CHECK_EQ(curField[0]->GetHealth(), 5);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, AttackTask(card4, card1));
    CHECK_EQ(curField[1]->GetAttack(), 6);
    CHECK_EQ(curField[1]->GetHealth(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_226] Frostwolf Warlord - COST:5 [ATK:4/HP:4]
// - Faction: Horde, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Gain +1/+1 for each
//       other friendly minion on the battlefield.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_226 : Frostwolf Warlord")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Frostwolf Warlord", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Frostwolf Warlord", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Frostwolf Warlord", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 4);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[1]->GetAttack(), 5);
    CHECK_EQ(curField[1]->GetHealth(), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[2]->GetAttack(), 6);
    CHECK_EQ(curField[2]->GetHealth(), 6);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_227] Venture Co. Mercenary - COST:5 [ATK:7/HP:6]
// - Faction: Horde, Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Your minions cost (3) more.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_227 : Venture Co. Mercenary")
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Venture Co. Mercenary", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Ironbeak Owl", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Malygos", FormatType::CLASSIC));

    CHECK_EQ(card2->GetCost(), 2);
    CHECK_EQ(card3->GetCost(), 9);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card2->GetCost(), 5);
    CHECK_EQ(card3->GetCost(), 12);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_CS2_231] Wisp - COST:0 [ATK:1/HP:1]
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_CS2_231 : Wisp")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_DS1_055] Darkscale Healer - COST:5 [ATK:4/HP:5]
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Restore 2 Health to
//       all friendly characters.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_DS1_055 : Darkscale Healer")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Darkscale Healer", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Argent Squire", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));
    curField[0]->SetDamage(5);
    curField[2]->SetDamage(1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetHealth(), 4);
    CHECK_EQ(curField[1]->GetHealth(), 1);
    CHECK_EQ(curField[2]->GetHealth(), 2);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_001] Lightwarden - COST:1 [ATK:1/HP:2]
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever a character is healed, gain +2 Attack.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_001 : Lightwarden")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Lightwarden", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetAttack(), 1);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetAttack(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_002] The Black Knight - COST:6 [ATK:4/HP:5]
// - Set: VANILLA, Rarity: Legendary
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
TEST_CASE("[Neutral : Minion] - VAN_EX1_002 : The Black Knight")
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Ironbark Protector", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Murloc Raider", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("The Black Knight", FormatType::CLASSIC));

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
// [VAN_EX1_004] Young Priestess - COST:1 [ATK:2/HP:1]
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: At the end of your turn,
//       give another random friendly minion +1 Health.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_004 : Young Priestess")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Young Priestess", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Young Priestess", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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
// [VAN_EX1_005] Big Game Hunter - COST:3 [ATK:4/HP:2]
// - Set: VANILLA, Rarity: Epic
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
TEST_CASE("[Neutral : Minion] - VAN_EX1_005 : Big Game Hunter")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Big Game Hunter", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Core Hound", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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
// [VAN_EX1_006] Alarm-o-Bot - COST:3 [ATK:0/HP:3]
// - Race: Mechanical, Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: At the start of your turn,
//       swap this minion with a random one in your hand.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_006 : Alarm-o-Bot")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Alarm-o-Bot", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Loot Hoarder", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Acolyte of Pain", FormatType::CLASSIC));

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
// [VAN_EX1_007] Acolyte of Pain - COST:3 [ATK:1/HP:3]
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Whenever this minion takes damage, draw a card.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_007 : Acolyte of Pain")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Acolyte of Pain", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Stonetusk Boar", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));

    game.Process(opPlayer, AttackTask(card2, card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_008] Argent Squire - COST:1 [ATK:1/HP:1]
// - Faction: Alliance, Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Divine Shield</b>
// --------------------------------------------------------
// GameTag:
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_008 : Argent Squire")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_009] Angry Chicken - COST:1 [ATK:1/HP:1]
// - Race: Beast, Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Enrage:</b> +5 Attack.
// --------------------------------------------------------
// RefTag:
// - ENRAGED = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_009 : Angry Chicken")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Angry Chicken", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Shattered Sun Cleric", FormatType::CLASSIC));

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
// [VAN_EX1_010] Worgen Infiltrator - COST:1 [ATK:2/HP:1]
// - Faction: Alliance, Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Stealth</b>
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_010 : Worgen Infiltrator")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_011] Voodoo Doctor - COST:1 [ATK:2/HP:1]
// - Faction: Horde, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Restore 2 Health.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_011 : Voodoo Doctor")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Voodoo Doctor", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Voodoo Doctor", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));

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
// [VAN_EX1_012] Bloodmage Thalnos - COST:2 [ATK:1/HP:1]
// - Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Spell Damage +1</b>
//       <b>Deathrattle:</b> Draw a card.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - SPELLPOWER = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_012 : Bloodmage Thalnos")
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Bloodmage Thalnos", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Blizzard", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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
// [VAN_EX1_014] King Mukla - COST:3 [ATK:5/HP:5]
// - Race: Beast, Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give your opponent 2 Bananas.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_014 : King Mukla")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("King Mukla", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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
// [VAN_EX1_015] Novice Engineer - COST:2 [ATK:1/HP:1]
// - Faction: Alliance, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Draw a card.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_015 : Novice Engineer")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Novice Engineer", FormatType::CLASSIC));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_016] Sylvanas Windrunner - COST:6 [ATK:5/HP:5]
// - Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Deathrattle:</b>
//       Take control of a random enemy minion.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_016 : Sylvanas Windrunner")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Sylvanas Windrunner", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Magma Rager", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Oasis Snapjaw", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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
// [VAN_EX1_017] Jungle Panther - COST:3 [ATK:4/HP:2]
// - Race: Beast, Faction: Horde, Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Stealth</b>
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_017 : Jungle Panther")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_019] Shattered Sun Cleric - COST:3 [ATK:3/HP:2]
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give a friendly minion +1/+1.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// - REQ_MINION_TARGET = 0
// - REQ_FRIENDLY_TARGET = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_019 : Shattered Sun Cleric")
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
        Cards::FindCardByName("Shattered Sun Cleric", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Ironfur Grizzly", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 4);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_020] Scarlet Crusader - COST:3 [ATK:3/HP:1]
// - Faction: Alliance, Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Divine Shield</b>
// --------------------------------------------------------
// GameTag:
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_020 : Scarlet Crusader")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_021] Thrallmar Farseer - COST:3 [ATK:2/HP:3]
// - Faction: Horde, Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Windfury</b>
// --------------------------------------------------------
// GameTag:
// - WINDFURY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_021 : Thrallmar Farseer")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_023] Silvermoon Guardian - COST:4 [ATK:3/HP:3]
// - Faction: Horde, Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Divine Shield</b>
// --------------------------------------------------------
// GameTag:
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_023 : Silvermoon Guardian")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_025] Dragonling Mechanic - COST:4 [ATK:2/HP:4]
// - Faction: Alliance, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a 2/1 Mechanical Dragonling.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_025 : Dragonling Mechanic")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Dragonling Mechanic", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_028] Stranglethorn Tiger - COST:5 [ATK:5/HP:5]
// - Race: Beast, Faction: Alliance, Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Stealth</b>
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_028 : Stranglethorn Tiger")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_029] Leper Gnome - COST:1 [ATK:2/HP:1]
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Deal 2 damage to the enemy hero.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_029 : Leper Gnome")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Leper Gnome", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, AttackTask(card2, card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 28);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_032] Sunwalker - COST:6 [ATK:4/HP:5]
// - Faction: Alliance, Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Divine Shield</b>
// --------------------------------------------------------
// GameTag:
// - DIVINE_SHIELD = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_032 : Sunwalker")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_033] Windfury Harpy - COST:6 [ATK:4/HP:5]
// - Faction: Alliance, Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Windfury</b>
// --------------------------------------------------------
// GameTag:
// - WINDFURY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_033 : Windfury Harpy")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_043] Twilight Drake - COST:4 [ATK:4/HP:1]
// - Race: Dragon, Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Gain +1 Health
//       for each card in your hand.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_043 : Twilight Drake")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Twilight Drake", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 4);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_044] Questing Adventurer - COST:3 [ATK:2/HP:2]
// - Faction: Alliance, Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever you play a card, gain +1/+1.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_044 : Questing Adventurer")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Questing Adventurer", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Stonetusk Boar", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Stonetusk Boar", FormatType::CLASSIC));

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
// [VAN_EX1_045] Ancient Watcher - COST:2 [ATK:4/HP:5]
// - Faction: Alliance, Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: Can't attack.
// --------------------------------------------------------
// GameTag:
// - CANT_ATTACK = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_045 : Ancient Watcher")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_046] Dark Iron Dwarf - COST:4 [ATK:4/HP:4]
// - Faction: Alliance, Set: VANILLA, Rarity: Common
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
TEST_CASE("[Neutral : Minion] - VAN_EX1_046 : Dark Iron Dwarf")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Dark Iron Dwarf", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Dark Iron Dwarf", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));

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
// [VAN_EX1_048] Spellbreaker - COST:4 [ATK:4/HP:3]
// - Faction: Horde, Set: VANILLA, Rarity: Common
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
TEST_CASE("[Neutral : Minion] - VAN_EX1_048 : Spellbreaker")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Spellbreaker", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Spellbreaker", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Leper Gnome", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Malygos", FormatType::CLASSIC));

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
// [VAN_EX1_049] Youthful Brewmaster - COST:2 [ATK:3/HP:2]
// - Faction: Alliance, Set: VANILLA, Rarity: Common
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
TEST_CASE("[Neutral : Minion] - VAN_EX1_049 : Youthful Brewmaster")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Youthful Brewmaster", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("SI:7 Agent", FormatType::CLASSIC));

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
// [VAN_EX1_050] Coldlight Oracle - COST:3 [ATK:2/HP:2]
// - Race: Murloc, Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Each player draws 2 cards.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_050 : Coldlight Oracle")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Coldlight Oracle", FormatType::CLASSIC));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card));
    CHECK_EQ(curPlayer->GetHandZone()->GetCount(), 6);
    CHECK_EQ(opPlayer->GetHandZone()->GetCount(), 7);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_055] Mana Addict - COST:2 [ATK:1/HP:3]
// - Faction: Alliance, Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever you cast a spell, gain +2 Attack this turn.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_055 : Mana Addict")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer, Cards::FindCardByName("Mana Addict", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fireball", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fireball", FormatType::CLASSIC));

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
// [VAN_EX1_057] Ancient Brewmaster - COST:4 [ATK:5/HP:4]
// - Faction: Alliance, Set: VANILLA, Rarity: Common
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
TEST_CASE("[Neutral : Minion] - VAN_EX1_057 : Ancient Brewmaster")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Ancient Brewmaster", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("SI:7 Agent", FormatType::CLASSIC));

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
// [VAN_EX1_058] Sunfury Protector - COST:2 [ATK:2/HP:3]
// - Faction: Alliance, Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give adjacent minions <b>Taunt</b>.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
// RefTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_058 : Sunfury Protector")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Sunfury Protector", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Sunfury Protector", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Stonetusk Boar", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Stonetusk Boar", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Stonetusk Boar", FormatType::CLASSIC));

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
// [VAN_EX1_059] Crazed Alchemist - COST:2 [ATK:2/HP:2]
// - Set: VANILLA, Rarity: Rare
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
TEST_CASE("[Neutral : Minion] - VAN_EX1_059 : Crazed Alchemist")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Crazed Alchemist", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 3);
    CHECK_EQ(curField[0]->GetHealth(), 1);

    game.Process(curPlayer, PlayCardTask::MinionTarget(card1, card2));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_062] Old Murk-Eye - COST:4 [ATK:2/HP:4]
// - Race: Murloc, Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Charge</b>. Has +1 Attack for each other Murloc
//       on the battlefield.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - CHARGE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_062 : Old Murk-Eye")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer, Cards::FindCardByName("Old Murk-Eye", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Murloc Raider", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Murloc Raider", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Murloc Raider", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Murloc Raider", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(card1->GetGameTag(GameTag::ATK), 2);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    game.Process(curPlayer, PlayCardTask::Minion(card4));

    CHECK_EQ(card1->GetGameTag(GameTag::ATK), 5);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card5));

    CHECK_EQ(card1->GetGameTag(GameTag::ATK), 6);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_066] Acidic Swamp Ooze - COST:2 [ATK:3/HP:2]
// - Faction: Alliance, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy your opponent's weapon.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_066 : Acidic Swamp Ooze")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fiery War Axe", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), true);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curPlayer->GetHero()->HasWeapon(), false);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_067] Argent Commander - COST:6 [ATK:4/HP:2]
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Charge</b>
//       <b>Divine Shield</b>
// --------------------------------------------------------
// GameTag:
// - CHARGE = 1
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_067 : Argent Commander")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_076] Pint-Sized Summoner - COST:2 [ATK:2/HP:2]
// - Faction: Alliance, Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: The first minion you play each turn costs (1) less.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_076 : Pint-Sized Summoner")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Pint-Sized Summoner", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Bloodfen Raptor", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Bloodfen Raptor", FormatType::CLASSIC));

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
// [VAN_EX1_080] Secretkeeper - COST:1 [ATK:1/HP:2]
// - Faction: Alliance, Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever a <b>Secret</b> is played, gain +1/+1.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
// RefTag:
// - SECRET = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_080 : Secretkeeper")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Secretkeeper", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Counterspell", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 2);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_082] Mad Bomber - COST:2 [ATK:3/HP:2]
// - Faction: Alliance, Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Deal 3 damage randomly split
//       between all other characters.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_082 : Mad Bomber")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mad Bomber", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));

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
// [VAN_EX1_083] Tinkmaster Overspark - COST:3 [ATK:3/HP:3]
// - Faction: Alliance, Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Transform another random minion
//       into a 5/5 Devilsaur or a 1/1 Squirrel.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_083 : Tinkmaster Overspark")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Tinkmaster Overspark", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ((curField[0]->card->id == "VAN_EX1_tk28" ||
              curField[0]->card->id == "VAN_EX1_tk29"),
             true);
    CHECK_EQ((curField[0]->GetAttack() == 1 || curField[0]->GetAttack() == 5),
             true);
    CHECK_EQ((curField[0]->GetHealth() == 1 || curField[0]->GetHealth() == 5),
             true);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_085] Mind Control Tech - COST:3 [ATK:3/HP:3]
// - Faction: Alliance, Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> If your opponent has 4 or
//       more minions, take control of one at random.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_085 : Mind Control Tech")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Mind Control Tech", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Stonetusk Boar", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Stonetusk Boar", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Stonetusk Boar", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Stonetusk Boar", FormatType::CLASSIC));
    const auto card6 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Stonetusk Boar", FormatType::CLASSIC));
    const auto card7 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Stonetusk Boar", FormatType::CLASSIC));
    const auto card8 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Stonetusk Boar", FormatType::CLASSIC));
    const auto card9 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Mind Control Tech", FormatType::CLASSIC));
    const auto card10 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Stonetusk Boar", FormatType::CLASSIC));
    const auto card11 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Stonetusk Boar", FormatType::CLASSIC));

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
// [VAN_EX1_089] Arcane Golem - COST:3 [ATK:4/HP:2]
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Charge</b>.
//       <b>Battlecry:</b> Give your opponent a Mana Crystal.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - CHARGE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_089 : Arcane Golem")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Arcane Golem", FormatType::CLASSIC));

    CHECK_EQ(opPlayer->GetTotalMana(), 3);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opPlayer->GetTotalMana(), 4);

    game.Process(curPlayer, AttackTask(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 26);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_093] Defender of Argus - COST:4 [ATK:2/HP:3]
// - Faction: Alliance, Set: VANILLA, Rarity: Rare
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
TEST_CASE("[Neutral : Minion] - VAN_EX1_093 : Defender of Argus")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Defender of Argus", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Stonetusk Boar", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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
    CHECK_EQ(curField[1]->GetAttack(), 2);
    CHECK_EQ(curField[1]->GetHealth(), 3);
    CHECK_EQ(curField[1]->GetGameTag(GameTag::TAUNT), 0);
    CHECK_EQ(curField[2]->GetAttack(), 4);
    CHECK_EQ(curField[2]->GetHealth(), 2);
    CHECK_EQ(curField[2]->GetGameTag(GameTag::TAUNT), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_095] Gadgetzan Auctioneer - COST:5 [ATK:4/HP:4]
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever you cast a spell, draw a card.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_095 : Gadgetzan Auctioneer")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Gadgetzan Auctioneer", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Pyroblast", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Lightning Bolt", FormatType::CLASSIC));

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
// [VAN_EX1_096] Loot Hoarder - COST:2 [ATK:2/HP:1]
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Draw a card.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_096 : Loot Hoarder")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Loot Hoarder", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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
// [VAN_EX1_097] Abomination - COST:5 [ATK:4/HP:4]
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Taunt</b>.
//       <b>Deathrattle:</b> Deal 2 damage to all characters.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_097 : Abomination")
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Abomination", FormatType::CLASSIC));
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
    const auto card6 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card7 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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
// [VAN_EX1_100] Lorewalker Cho - COST:2 [ATK:0/HP:4]
// - Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: Whenever a player casts a spell,
//       put a copy into the other player's hand.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_100 : Lorewalker Cho")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Lorewalker Cho", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fireball", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Blizzard", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Inner Rage", FormatType::CLASSIC));

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
// [VAN_EX1_102] Demolisher - COST:3 [ATK:1/HP:4]
// - Race: Mechanical, Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: At the start of your turn,
//       deal 2 damage to a random enemy.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_102 : Demolisher")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Demolisher", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Dalaran Mage", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Dalaran Mage", FormatType::CLASSIC));

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
// [VAN_EX1_103] Coldlight Seer - COST:3 [ATK:2/HP:3]
// - Race: Murloc, Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give all other Murlocs +2 Health.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_103 : Coldlight Seer")
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Coldlight Seer", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Murloc Raider", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Murloc Raider", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Murloc Raider", FormatType::CLASSIC));

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
// [VAN_EX1_105] Mountain Giant - COST:12 [ATK:8/HP:8]
// - Set: VANILLA, Rarity: Epic
// --------------------------------------------------------
// Text: Costs (1) less for each other card in your hand.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_105 : Mountain Giant")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Mountain Giant", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Mountain Giant", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Mountain Giant", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Mountain Giant", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Sap", FormatType::CLASSIC));
    const auto card6 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Assassinate", FormatType::CLASSIC));

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
// [VAN_EX1_110] Cairne Bloodhoof - COST:6 [ATK:4/HP:5]
// - Faction: Alliance, Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a 4/5 Baine Bloodhoof.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_110 : Cairne Bloodhoof")
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Cairne Bloodhoof", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    curField[0]->SetDamage(4);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, AttackTask(card2, card1));
    CHECK(card1->isDestroyed);
    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetAttack(), 4);
    CHECK_EQ(curField[0]->GetHealth(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_112] Gelbin Mekkatorque - COST:6 [ATK:6/HP:6]
// - Faction: Alliance, Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon an AWESOME invention.
// --------------------------------------------------------
// Entourage: Mekka1, Mekka2, Mekka3, Mekka4
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
// PlayReq:
// - REQ_NUM_MINION_SLOTS = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_112 : Gelbin Mekkatorque")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Gelbin Mekkatorque", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 2);

    const bool isMekka = curField[1]->card->name == "Homing Chicken" ||
                         curField[1]->card->name == "Repair Bot" ||
                         curField[1]->card->name == "Emboldener 3000" ||
                         curField[1]->card->name == "Poultryizer";
    CHECK(isMekka);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_116] Leeroy Jenkins - COST:4 [ATK:6/HP:2]
// - Faction: Alliance, Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Charge</b>.
//       <b>Battlecry:</b> Summon two 1/1 Whelps for your opponent.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// - CHARGE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_116 : Leeroy Jenkins")
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

    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Leeroy Jenkins", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opField.GetCount(), 2);
    CHECK_EQ(opField[0]->GetHealth(), 1);
    CHECK_EQ(opField[0]->GetAttack(), 1);
    CHECK_EQ(opField[1]->GetHealth(), 1);
    CHECK_EQ(opField[1]->GetAttack(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_162] Dire Wolf Alpha - COST:2 [ATK:2/HP:2]
// - Race: Beast, Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Adjacent minions have +1 Attack.
// --------------------------------------------------------
// GameTag:
// - ADJACENT_BUFF = 1
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_162 : Dire Wolf Alpha")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card6 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Dire Wolf Alpha", FormatType::CLASSIC));
    const auto card7 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Fireball", FormatType::CLASSIC));

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
// [VAN_EX1_170] Emperor Cobra - COST:3 [ATK:2/HP:3]
// - Race: Beast, Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: Destroy any minion damaged by this minion.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_170 : Emperor Cobra")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer, Cards::FindCardByName("Emperor Cobra", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Chillwind Yeti", FormatType::CLASSIC));

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
// [VAN_EX1_249] Baron Geddon - COST:7 [ATK:7/HP:5]
// - Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: At the end of your turn,
//       deal 2 damage to all other characters.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_249 : Baron Geddon")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Baron Geddon", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Boulderfist Ogre", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField.GetCount(), 1);
    CHECK_EQ(curField[0]->GetHealth(), 5);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 28);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(opField.GetCount(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(curField[0]->GetHealth(), 5);
    CHECK_EQ(opField.GetCount(), 1);
    CHECK_EQ(opField[0]->GetHealth(), 5);
    CHECK_EQ(curPlayer->GetHero()->GetHealth(), 26);
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 26);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_283] Frost Elemental - COST:6 [ATK:5/HP:5]
// - Race: Elemental, Set: Expert1, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> <b>Freeze</b> a character.
// --------------------------------------------------------
// PlayReq:
// - REQ_TARGET_IF_AVAILABLE = 0
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_283 : Frost Elemental")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        opPlayer,
        Cards::FindCardByName("Frost Elemental", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fen Creeper", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fen Creeper", FormatType::CLASSIC));

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
// [VAN_EX1_284] Azure Drake - COST:5 [ATK:4/HP:4]
// - Race: Dragon, Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Spell Damage +1</b>
//       <b>Battlecry:</b> Draw a card.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// - SPELLPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_284 : Azure Drake")
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
        curPlayer, Cards::FindCardByName("Azure Drake", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fireball", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Archmage", FormatType::CLASSIC));

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
// [VAN_EX1_298] Ragnaros the Firelord - COST:8 [ATK:8/HP:8]
// - Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: Can't attack. At the end of your turn,
//       deal 8 damage to a random enemy.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - CANT_ATTACK = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_298 : Ragnaros the Firelord")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Ragnaros the Firelord", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Grommash Hellscream", FormatType::CLASSIC));

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
// [VAN_EX1_390] Tauren Warrior - COST:3 [ATK:2/HP:3]
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>.
//       <b>Enrage:</b> +3 Attack
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
// RefTag:
// - ENRAGED = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_390 : Tauren Warrior")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Tauren Warrior", FormatType::CLASSIC));

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
// [VAN_EX1_393] Amani Berserker - COST:2 [ATK:2/HP:3]
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Enrage:</b> +3 Attack
// --------------------------------------------------------
// RefTag:
// - ENRAGED = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - VAN_EX1_393 : Amani Berserker")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Amani Berserker", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetAttack(), 5);
    CHECK_EQ(curField[0]->GetHealth(), 2);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_396] Mogu'shan Warden - COST:4 [ATK:1/HP:7]
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_396 : Mogu'shan Warden")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_399] Gurubashi Berserker - COST:5 [ATK:2/HP:7]
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: Whenever this minion takes damage, gain +3 Attack.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_399 : Gurubashi Berserker")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Gurubashi Berserker", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetAttack(), 5);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, HeroPowerTask(card1));
    CHECK_EQ(curField[0]->GetAttack(), 8);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_405] Shieldbearer - COST:1 [ATK:0/HP:4]
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_405 : Shieldbearer")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_412] Raging Worgen - COST:3 [ATK:3/HP:3]
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Enrage:</b> <b>Windfury</b> and +1 Attack
// --------------------------------------------------------
// RefTag:
// - ENRAGED = 1
// - WINDFURY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_412 : Raging Worgen")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer, Cards::FindCardByName("Raging Worgen", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Circle of Healing", FormatType::CLASSIC));

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
// [VAN_EX1_506] Murloc Tidehunter - COST:2 [ATK:2/HP:1]
// - Race: Murloc, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a 1/1 Murloc Scout.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_506 : Murloc Tidehunter")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Murloc Tidehunter", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField.GetCount(), 2);
    CHECK_EQ(curField[1]->GetAttack(), 1);
    CHECK_EQ(curField[1]->GetHealth(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_507] Murloc Warleader - COST:3 [ATK:3/HP:3]
// - Race: Murloc, Set: VANILLA, Rarity: Epic
// --------------------------------------------------------
// Text: ALL other murlocs have +2/+1.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_507 : Murloc Warleader")
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
        curPlayer, Cards::FindCardByName("Murloc Raider", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fireball", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Murloc Raider", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card6 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Murloc Warleader", FormatType::CLASSIC));

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
// [VAN_EX1_508] Grimscale Oracle - COST:1 [ATK:1/HP:1]
// - Race: Murloc, Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: ALL other Murlocs have +1 Attack.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_508 : Grimscale Oracle")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Grimscale Oracle", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Grimscale Oracle", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Murloc Raider", FormatType::CLASSIC));
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

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_509] Murloc Tidecaller - COST:1 [ATK:1/HP:2]
// - Race: Murloc, Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever a Murloc is summoned, gain +1 Attack.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_509 : Murloc Tidecaller")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Murloc Tidecaller", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Murloc Tidehunter", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Magma Rager", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Magma Rager", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Murloc Tidehunter", FormatType::CLASSIC));

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
// [VAN_EX1_556] Harvest Golem - COST:3 [ATK:2/HP:3]
// - Race: Mechanical, Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a 2/1 Damaged Golem.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_556 : Harvest Golem")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Magma Rager", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Harvest Golem", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Magma Rager", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fireball", FormatType::CLASSIC));

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
// [VAN_EX1_557] Nat Pagle - COST:2 [ATK:0/HP:4]
// - Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: At the start of your turn,
//       you have a 50% chance to draw an extra card.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_557 : Nat Pagle")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Nat Pagle", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ((curHand.GetCount() == 5 || curHand.GetCount() == 6), true);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_558] Harrison Jones - COST:5 [ATK:5/HP:4]
// - Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy your opponent's weapon
//       and draw cards equal to its Durability.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_558 : Harrison Jones")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fiery War Axe", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Harrison Jones", FormatType::CLASSIC));

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
// [VAN_EX1_560] Nozdormu - COST:9 [ATK:8/HP:8]
// - Race: Dragon, Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: Players only have 15 seconds to take their turns.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_560 : Nozdormu")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Nozdormu", FormatType::CLASSIC));

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
// [VAN_EX1_561] Alexstrasza - COST:9 [ATK:8/HP:8]
// - Race: Dragon, Set: VANILLA, Rarity: Legendary
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
TEST_CASE("[Neutral : Minion] - VAN_EX1_561 : Alexstrasza")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Alexstrasza", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Alexstrasza", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Lord Jaraxxus", FormatType::CLASSIC));

    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 30);

    game.Process(curPlayer,
                 PlayCardTask::MinionTarget(card1, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 15);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 15);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, HeroPowerTask(opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 14);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer,
                 PlayCardTask::MinionTarget(card2, opPlayer->GetHero()));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 15);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_562] Onyxia - COST:9 [ATK:8/HP:8]
// - Race: Dragon, Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon 1/1 Whelps until your side
//       of the battlefield is full.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_562 : Onyxia")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Onyxia", FormatType::CLASSIC));

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
// [VAN_EX1_563] Malygos - COST:9 [ATK:4/HP:12]
// - Race: Dragon, Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Spell Damage +5</b>
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - SPELLPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_563 : Malygos")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_564] Faceless Manipulator - COST:5 [ATK:3/HP:3]
// - Set: VANILLA, Rarity: Epic
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
TEST_CASE("[Neutral : Minion] - VAN_EX1_564 : Faceless Manipulator")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Faceless Manipulator", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Faceless Manipulator", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Northshire Cleric", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Shattered Sun Cleric", FormatType::CLASSIC));

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
// [VAN_EX1_572] Ysera - COST:9 [ATK:4/HP:12]
// - Race: Dragon, Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: At the end of your turn, add a Dream Card to your hand.
// --------------------------------------------------------
// Entourage: DREAM_01, DREAM_02, DREAM_03, DREAM_04, DREAM_05
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_572 : Ysera")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Ysera", FormatType::CLASSIC));

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
// [VAN_EX1_577] The Beast - COST:6 [ATK:9/HP:7]
// - Race: Beast, Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Summon a 3/3 Finkle Einhorn
//       for your opponent.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_577 : The Beast")
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("The Beast", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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
// [VAN_EX1_582] Dalaran Mage - COST:3 [ATK:1/HP:4]
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Spell Damage +1</b>
// --------------------------------------------------------
// GameTag:
// - SPELLPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_582 : Dalaran Mage")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_583] Priestess of Elune - COST:6 [ATK:5/HP:4]
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Restore 4 Health to your hero.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_583 : Priestess of Elune")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        curPlayer,
        Cards::FindCardByName("Priestess of Elune", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Chillwind Yeti", FormatType::CLASSIC));

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
// [VAN_EX1_584] Ancient Mage - COST:4 [ATK:2/HP:5]
// - Set: VANILLA, Rarity: Rare
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
TEST_CASE("[Neutral : Minion] - VAN_EX1_584 : Ancient Mage")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Ancient Mage", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));

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
// [VAN_EX1_586] Sea Giant - COST:10 [ATK:8/HP:8]
// - Set: VANILLA, Rarity: Epic
// --------------------------------------------------------
// Text: Costs (1) less for each other minion on the battlefield.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_586 : Sea Giant")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Sea Giant", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card6 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));

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
// [VAN_EX1_590] Blood Knight - COST:3 [ATK:3/HP:3]
// - Set: VANILLA, Rarity: Epic
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
TEST_CASE("[Neutral : Minion] - VAN_EX1_590 : Blood Knight")
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
        curPlayer, Cards::FindCardByName("Argent Squire", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Argent Squire", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Blood Knight", FormatType::CLASSIC));
    const auto card6 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Argent Squire", FormatType::CLASSIC));
    const auto card7 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));

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
// [VAN_EX1_593] Nightblade - COST:5 [ATK:4/HP:4]
// - Set: VANILLA, Rarity: Free
// --------------------------------------------------------
// Text: <b>Battlecry: </b>Deal 3 damage to the enemy hero.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_593 : Nightblade")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Nightblade", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(opPlayer->GetHero()->GetHealth(), 27);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_595] Cult Master - COST:4 [ATK:4/HP:2]
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: After a friendly minion dies, draw a card.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_595 : Cult Master")
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Cult Master", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Argent Squire", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card6 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card7 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Stonetusk Boar", FormatType::CLASSIC));

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
// [VAN_EX1_597] Imp Master - COST:3 [ATK:1/HP:5]
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: At the end of your turn,
//       deal 1 damage to this minion and summon a 1/1 Imp.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_597 : Imp Master")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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
        const auto card = Generic::DrawCard(
            curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
        game.Process(curPlayer, PlayCardTask::Minion(card));
    }

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Imp Master", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Frostbolt", FormatType::CLASSIC));

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
// [VAN_EX1_614] Illidan Stormrage - COST:6 [ATK:7/HP:5]
// - Race: Demon, Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: Whenever you play a card,
//       summon a 2/1 Flame of Azzinoth.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_614 : Illidan Stormrage")
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Illidan Stormrage", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Moonfire", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField.GetCount(), 3);
    CHECK_EQ(curField[1]->card->name, "Flame of Azzinoth");
    CHECK_EQ(curField[2]->card->name, "Wisp");

    game.Process(curPlayer, PlayCardTask::SpellTarget(card3, card1));
    CHECK_EQ(curField.GetCount(), 4);
    CHECK_EQ(curField[1]->card->name, "Flame of Azzinoth");
    CHECK_EQ(curField[2]->card->name, "Flame of Azzinoth");
    CHECK_EQ(curField[3]->card->name, "Wisp");
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_EX1_616] Mana Wraith - COST:2 [ATK:2/HP:2]
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: All minions cost (1) more.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_616 : Mana Wraith")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Mana Wraith", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fireball", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Starfall", FormatType::CLASSIC));

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
// [VAN_EX1_620] Molten Giant - COST:20 [ATK:8/HP:8]
// - Set: VANILLA, Rarity: Epic
// --------------------------------------------------------
// Text: Costs (1) less for each damage your hero has taken.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_EX1_620 : Molten Giant")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Molten Giant", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Flame Imp", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Flame Imp", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Flame Imp", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Flame Imp", FormatType::CLASSIC));

    CHECK_EQ(card1->GetCost(), 20);

    game.Process(curPlayer, PlayCardTask(card2));
    game.Process(curPlayer, PlayCardTask(card3));
    game.Process(curPlayer, PlayCardTask(card4));
    game.Process(curPlayer, PlayCardTask(card5));

    CHECK_EQ(card1->GetCost(), 8);

    const auto card6 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Flame Imp", FormatType::CLASSIC));
    const auto card7 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Flame Imp", FormatType::CLASSIC));
    const auto card8 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Flame Imp", FormatType::CLASSIC));
    const auto card9 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Flame Imp", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask(card6));
    game.Process(curPlayer, PlayCardTask(card7));
    game.Process(curPlayer, PlayCardTask(card8));
    game.Process(curPlayer, PlayCardTask(card9));

    CHECK_EQ(card1->GetCost(), 0);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_NEW1_016] Captain's Parrot - COST:2 [ATK:1/HP:1]
// - Race: Beast, Set: VANILLA, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Draw a Pirate from your deck.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_NEW1_016 : Captain's Parrot")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
    config.player1Class = CardClass::WARRIOR;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    for (int i = 0; i < 30; i += 3)
    {
        config.player1Deck[i] = Cards::FindCardByName("Magma Rager");
        config.player1Deck[i + 1] = Cards::FindCardByName("Southsea Captain");
        config.player1Deck[i + 2] = Cards::FindCardByName("Murloc Tidehunter");
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
        Cards::FindCardByName("Captain's Parrot", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 5);
    CHECK_EQ(curHand[4]->card->GetRace(), Race::PIRATE);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_NEW1_017] Hungry Crab - COST:1 [ATK:1/HP:2]
// - Race: Beast, Set: VANILLA, Rarity: Epic
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
TEST_CASE("[Neutral : Minion] - VAN_NEW1_017 : Hungry Crab")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Murloc Raider", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Hungry Crab", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Hungry Crab", FormatType::CLASSIC));

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
// [VAN_NEW1_018] Bloodsail Raider - COST:2 [ATK:2/HP:3]
// - Race: Pirate, Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Gain Attack equal to the Attack
//       of your weapon.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_NEW1_018 : Bloodsail Raider")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Fiery War Axe", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Bloodsail Raider", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Bloodsail Raider", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 2);
    CHECK_EQ(curField[0]->GetHealth(), 3);

    game.Process(curPlayer, PlayCardTask::Weapon(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[1]->GetAttack(), 5);
    CHECK_EQ(curField[1]->GetHealth(), 3);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_NEW1_019] Knife Juggler - COST:2 [ATK:3/HP:2]
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: After you summon a minion,
//       deal 1 damage to a random enemy.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_NEW1_019 : Knife Juggler")
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Knife Juggler", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Magma Rager", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Magma Rager", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Chillwind Yeti", FormatType::CLASSIC));

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
// [VAN_NEW1_020] Wild Pyromancer - COST:2 [ATK:3/HP:2]
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: After you cast a spell, deal 1 damage to all minions.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_NEW1_020 : Wild Pyromancer")
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
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Wild Pyromancer", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Arcane Shot", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Arcane Shot", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Arcane Shot", FormatType::CLASSIC));
    const auto card6 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card7 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));

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
// [VAN_NEW1_021] Doomsayer - COST:2 [ATK:0/HP:7]
// - Set: VANILLA, Rarity: Epic
// --------------------------------------------------------
// Text: At the start of your turn, destroy all minions.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_NEW1_021 : Doomsayer")
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

    auto& curField = *(curPlayer->GetFieldZone());
    auto& opField = *(opPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Doomsayer", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Kor'kron Elite", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Water Elemental", FormatType::CLASSIC));
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
// [VAN_NEW1_022] Dread Corsair - COST:4 [ATK:3/HP:3]
// - Race: Pirate, Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       Costs (1) less per Attack of your weapon.
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_NEW1_022 : Dread Corsair")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Dread Corsair", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Deadly Poison", FormatType::CLASSIC));

    CHECK_EQ(card1->GetCost(), 4);

    game.Process(curPlayer, HeroPowerTask());
    CHECK_EQ(card1->GetCost(), 3);

    game.Process(curPlayer, PlayCardTask::Spell(card2));
    CHECK_EQ(card1->GetCost(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_NEW1_023] Faerie Dragon - COST:2 [ATK:3/HP:2]
// - Race: Dragon, Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Can't be targeted by spells or Hero Powers.
// --------------------------------------------------------
// GameTag:
// - CANT_BE_TARGETED_BY_SPELLS = 1
// - CANT_BE_TARGETED_BY_HERO_POWERS = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_NEW1_023 : Faerie Dragon")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Faerie Dragon", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Fireball", FormatType::CLASSIC));

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
// [VAN_NEW1_024] Captain Greenskin - COST:5 [ATK:5/HP:4]
// - Race: Pirate, Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give your weapon +1/+1.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_NEW1_024 : Captain Greenskin")
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Captain Greenskin", FormatType::CLASSIC));

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
// [VAN_NEW1_025] Bloodsail Corsair - COST:1 [ATK:1/HP:2]
// - Race: Pirate, Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Remove 1 Durability from
//       your opponent's weapon.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_NEW1_025 : Bloodsail Corsair")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Bloodsail Corsair", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Bloodsail Corsair", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Bloodsail Corsair", FormatType::CLASSIC));

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
// [VAN_NEW1_026] Violet Teacher - COST:4 [ATK:3/HP:5]
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: Whenever you cast a spell,
//       summon a 1/1 Violet Apprentice.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_NEW1_026 : Violet Teacher")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Violet Teacher", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Preparation", FormatType::CLASSIC));

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
// [VAN_NEW1_027] Southsea Captain - COST:3 [ATK:3/HP:3]
// - Race: Pirate, Set: VANILLA, Rarity: Epic
// --------------------------------------------------------
// Text: Your other Pirates have +1/+1.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_NEW1_027 : Southsea Captain")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Southsea Captain", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Southsea Captain", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Shieldbearer", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Southsea Captain", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Southsea Captain", FormatType::CLASSIC));

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
// [VAN_NEW1_029] Millhouse Manastorm - COST:2 [ATK:4/HP:4]
// - Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Enemy spells cost (0) next turn.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_NEW1_029 : Millhouse Manastorm")
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

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Millhouse Manastorm", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Fireball", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Frostbolt", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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
// [VAN_NEW1_030] Deathwing - COST:10 [ATK:12/HP:12]
// - Race: Dragon, Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy all other minions
//       and discard your hand.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_NEW1_030 : Deathwing")
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

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Deathwing", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Magma Rager", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Magma Rager", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Magma Rager", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Magma Rager", FormatType::CLASSIC));

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
// [VAN_NEW1_037] Master Swordsmith - COST:2 [ATK:1/HP:3]
// - Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: At the end of your turn,
//       give another random friendly minion +1 Attack.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_NEW1_037 : Master Swordsmith")
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
        curPlayer,
        Cards::FindCardByName("Master Swordsmith", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Acidic Swamp Ooze", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wolfrider", FormatType::CLASSIC));

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
// [VAN_NEW1_038] Gruul - COST:8 [ATK:7/HP:7]
// - Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: At the end of each turn, gain +1/+1.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_NEW1_038 : Gruul")
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
        curPlayer, Cards::FindCardByName("Gruul", FormatType::CLASSIC));

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
// [VAN_NEW1_040] Hogger - COST:6 [ATK:4/HP:4]
// - Set: VANILLA, Rarity: Legendary
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
TEST_CASE("[Neutral : Minion] - VAN_NEW1_040 : Hogger")
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
        curPlayer, Cards::FindCardByName("Hogger", FormatType::CLASSIC));

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
// [VAN_NEW1_041] Stampeding Kodo - COST:5 [ATK:3/HP:5]
// - Race: Beast, Set: VANILLA, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Destroy a random enemy minion
//       with 2 or less Attack.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_NEW1_041 : Stampeding Kodo")
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
        opPlayer,
        Cards::FindCardByName("Stampeding Kodo", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Stampeding Kodo", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        opPlayer,
        Cards::FindCardByName("Stampeding Kodo", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Voidwalker", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("River Crocolisk", FormatType::CLASSIC));
    const auto card6 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Bloodfen Raptor", FormatType::CLASSIC));

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
// [VAN_PRO_001] Elite Tauren Chieftain - COST:5 [ATK:5/HP:5]
// - Set: VANILLA, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Give both players the power to ROCK!
//       (with a Power Chord card)
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_PRO_001 : Elite Tauren Chieftain")
{
    GameConfig config;
    config.formatType = FormatType::CLASSIC;
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

    auto& curHand = *(curPlayer->GetHandZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Elite Tauren Chieftain", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curHand.GetCount(), 1);

    const bool isChieftainCard = curHand[0]->card->name == "I Am Murloc" ||
                                 curHand[0]->card->name == "Rogues Do It..." ||
                                 curHand[0]->card->name == "Power of the Horde";
    CHECK(isChieftainCard);
}

// --------------------------------------- MINION - NEUTRAL
// [VAN_tt_004] Flesheating Ghoul - COST:3 [ATK:2/HP:3]
// - Set: VANILLA, Rarity: Common
// --------------------------------------------------------
// Text: Whenever a minion dies, gain +1 Attack.
// --------------------------------------------------------
// GameTag:
// - TRIGGER_VISUAL = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - VAN_tt_004 : Flesheating Ghoul")
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

    auto& curField = *(curPlayer->GetFieldZone());

    const auto card1 = Generic::DrawCard(
        curPlayer,
        Cards::FindCardByName("Flesheating Ghoul", FormatType::CLASSIC));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::FindCardByName("Wisp", FormatType::CLASSIC));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Stonetusk Boar", FormatType::CLASSIC));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::FindCardByName("Stonetusk Boar", FormatType::CLASSIC));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    game.Process(curPlayer, PlayCardTask::Minion(card2));
    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetAttack(), 2);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::Minion(card4));
    game.Process(opPlayer, PlayCardTask::Minion(card5));

    game.Process(opPlayer, AttackTask(card4, card2));
    CHECK_EQ(curField[0]->GetAttack(), 4);

    game.Process(opPlayer, AttackTask(card5, card3));
    CHECK_EQ(curField[0]->GetAttack(), 6);
}