// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetHeaders.hpp>

// ----------------------------------------- SPELL - PRIEST
// [GVG_008] Lightbomb - COST:6
// - Set: Gvg, Rarity: Epic
// --------------------------------------------------------
// Text: Deal damage to each minion equal to its Attack.
// --------------------------------------------------------
// GameTag:
// - AFFECTED_BY_SPELL_POWER = 1
// --------------------------------------------------------
TEST_CASE("[Priest : Spell] - GVG_008 : Lightbomb")
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

// --------------------------------------- MINION - WARRIOR
// [GVG_053] Shieldmaiden - COST:6 [ATK:5/HP:5]
// - Set: Gvg, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Gain 5 Armor.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Warrior : Minion] - GVG_053 : Shieldmaiden")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Shieldmaiden"));

    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 0);

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curPlayer->GetHero()->GetArmor(), 5);
}

// --------------------------------------- MINION - NEUTRAL
// [GVG_013] Cogmaster - COST:1 [ATK:1/HP:2]
// - Set: Gvg, Rarity: Common
// --------------------------------------------------------
// Text: Has +2 Attack while you have a Mech.
// --------------------------------------------------------
// GameTag:
// - AURA = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - GVG_013 : Cogmaster")
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
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Cogmaster"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Spider Tank"));
    const auto card3 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Wolfrider"));
    const auto card4 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Fireball"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    CHECK_EQ(curField[0]->GetAttack(), 1);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(curField[0]->GetAttack(), 3);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(opPlayer, PlayCardTask::SpellTarget(card4, card2));
    CHECK_EQ(curField[0]->GetAttack(), 1);

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    game.Process(curPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(curField[0]->GetAttack(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [GVG_044] Spider Tank - COST:3 [ATK:3/HP:4]
// - Race: Mechanical, Set: Gvg, Rarity: Common
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - GVG_044 : Spider Tank")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [GVG_076] Explosive Sheep - COST:2 [ATK:1/HP:1]
// - Race: Mechanical, Set: Gvg, Rarity: Common
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Deal 2 damage to all minions.
// --------------------------------------------------------
// GameTag:
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - GVG_076 : Explosive Sheep")
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
// [GVG_085] Annoy-o-Tron - COST:2 [ATK:1/HP:2]
// - Race: Mechanical, Set: Gvg, Rarity: Common
// --------------------------------------------------------
// Text: <b>Taunt</b>
//       <b>Divine Shield</b>
// --------------------------------------------------------
// GameTag:
// - TAUNT = 1
// - DIVINE_SHIELD = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - GVG_085 : Annoy-o-Tron")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [GVG_109] Mini-Mage - COST:3 [ATK:3/HP:1]
// - Set: Gvg, Rarity: Epic
// --------------------------------------------------------
// Text: <b>Stealth</b>
//       <b>Spell Damage +1</b>
// --------------------------------------------------------
// GameTag:
// - STEALTH = 1
// - SPELLPOWER = 1
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - GVG_109 : Mini-Mage")
{
    // Do nothing
}

// --------------------------------------- MINION - NEUTRAL
// [GVG_121] Clockwork Giant - COST:12 [ATK:8/HP:8]
// - Race: Mechanical, Set: Gvg, Rarity: Epic
// --------------------------------------------------------
// Text: Costs (1) less for each card in your opponent's hand.
// --------------------------------------------------------
TEST_CASE("[Neutral : Minion] - GVG_121 : Clockwork Giant")
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

    const auto card1 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Clockwork Giant"));
    const auto card2 =
        Generic::DrawCard(curPlayer, Cards::FindCardByName("Spider Tank"));
    const auto card3 =
        Generic::DrawCard(opPlayer, Cards::FindCardByName("Violet Teacher"));

    CHECK_EQ(card1->GetCost(), 6);

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    CHECK_EQ(card1->GetCost(), 6);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_ACTION);

    CHECK_EQ(card1->GetCost(), 5);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    CHECK_EQ(card1->GetCost(), 6);
}