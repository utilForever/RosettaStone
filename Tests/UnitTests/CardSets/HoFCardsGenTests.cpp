// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.hpp>

#include <Rosetta/Actions/Draw.hpp>
#include <Rosetta/Cards/Cards.hpp>

using namespace RosettaStone;
using namespace PlayerTasks;
using namespace SimpleTasks;

// ------------------------------------------ SPELL - DRUID
// [EX1_161] Naturalize - COST:1
// - Set: HoF, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> <b>Silence</b> a minion.
// --------------------------------------------------------
// PlayReq:
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST(DruidHoFTest, EX1_161_Naturalize)
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::DRUID;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();
    curPlayer.SetTotalMana(10);
    curPlayer.SetUsedMana(0);
    opPlayer.SetTotalMana(10);
    opPlayer.SetUsedMana(0);

    const auto card1 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Naturalize"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Magma Rager"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    const auto curHandCount = curPlayer.GetHandZone().GetCount();
    game.Process(opPlayer, PlayCardTask::SpellTarget(card1, card2));

    EXPECT_EQ(curPlayer.GetHandZone().GetCount(), curHandCount + 2);
    EXPECT_EQ(curPlayer.GetFieldZone().GetCount(), 0);
}

// --------------------------------------- MINION - WARLOCK
// [EX1_310] Doomguard - COST:5 [ATK:5/HP:7]
// - Race: Demon, Set: HoF, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Charge</b>. <b>Battlecry:</b> Discard two random cards.
// --------------------------------------------------------
// GameTag:
// - CHARGE = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST(WarlockHoFTest, EX1_310_Doomguard)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();
    curPlayer.SetTotalMana(10);
    curPlayer.SetUsedMana(0);
    opPlayer.SetTotalMana(10);
    opPlayer.SetUsedMana(0);

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Doomguard"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    EXPECT_EQ(curPlayer.GetHandZone().GetCount(), 2);

    game.Process(curPlayer, AttackTask(card1, opPlayer.GetHero()));
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 25);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    EXPECT_EQ(opPlayer.GetHandZone().GetCount(), 6);
}

// ---------------------------------------- SPELL - WARLOCK
// [EX1_316] Power Overwhelming - COST:1
// - Set: HoF, Rarity: Common
// --------------------------------------------------------
// Text: Give a friendly minion +4/+4 until end of turn. Then, it dies. Horribly.
// --------------------------------------------------------
// PlayReq:
// - REQ_FRIENDLY_TARGET = 0
// - REQ_MINION_TARGET = 0
// - REQ_TARGET_TO_PLAY = 0
// --------------------------------------------------------
TEST(WarlockHoFTest, EX1_316_PowerOverwhelming)
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::WARRIOR;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();
    curPlayer.SetTotalMana(10);
    curPlayer.SetUsedMana(0);
    opPlayer.SetTotalMana(10);
    opPlayer.SetUsedMana(0);

    auto& curField = curPlayer.GetFieldZone();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Power Overwhelming"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Goldshire Footman"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("King Mukla"));

    game.Process(curPlayer, PlayCardTask::Minion(card2));
    
    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, PlayCardTask::Minion(card3));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card1, card2));
    game.Process(curPlayer, AttackTask(card2, card3));

    EXPECT_EQ(curField[0]->GetHealth(), 1);
    EXPECT_EQ(opPlayer.GetFieldZone().GetCount(), 0);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    EXPECT_EQ(curPlayer.GetFieldZone().GetCount(), 0);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_016] Sylvanas Windrunner - COST:6 [ATK:5/HP:5]
// - Set: HoF, Rarity: Legendary
// --------------------------------------------------------
// Text: <b>Deathrattle:</b> Take
//       control of a random
//       enemy minion.
// --------------------------------------------------------
// GameTag:
// - ELITE = 1
// - DEATHRATTLE = 1
// --------------------------------------------------------
TEST(NeutralHoFTest, EX1_016_SylvanasWindrunner)
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();
    curPlayer.SetTotalMana(10);
    curPlayer.SetUsedMana(0);
    opPlayer.SetTotalMana(10);
    opPlayer.SetUsedMana(0);

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Sylvanas Windrunner"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Magma Rager"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Oasis Snapjaw"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Wolfrider"));

    game.Process(curPlayer, PlayCardTask::Minion(card1));

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    game.Process(opPlayer, PlayCardTask::Minion(card3));
    game.Process(opPlayer, PlayCardTask::Minion(card4));

    game.Process(opPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer, AttackTask(card1, card2));
    EXPECT_EQ(curPlayer.GetFieldZone().GetCount(), 1);
    EXPECT_EQ(opPlayer.GetFieldZone().GetCount(), 1);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_050] Coldlight Oracle - COST:3 [ATK:2/HP:2]
// - Faction: Neutral, Set: Core, Rarity: Free
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Each player draws 2 cards.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST(NeutralHoFTest, EX1_050_ColdlightOracle)
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();
    curPlayer.SetTotalMana(10);
    curPlayer.SetUsedMana(0);
    opPlayer.SetTotalMana(10);
    opPlayer.SetUsedMana(0);

    const auto card = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Coldlight Oracle"));
    EXPECT_EQ(curPlayer.GetHandZone().GetCount(), 5);

    game.Process(curPlayer, PlayCardTask::Minion(card));
    EXPECT_EQ(curPlayer.GetHandZone().GetCount(), 6);
    EXPECT_EQ(opPlayer.GetHandZone().GetCount(), 7);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_284] Azure Drake - COST:5 [ATK:4/HP:4]
// - Set: HoF, Rarity: Rare
// --------------------------------------------------------
// Text: <b>Spell Damage +1</b>
//       <b>Battlecry:</b> Draw a card.
// --------------------------------------------------------
// GameTag:
// - SPELLPOWER = 1
// - BATTLECRY = 1
// --------------------------------------------------------
TEST(NeutralHoFTest, EX1_284_AzureDrake)
{
    GameConfig config;
    config.player1Class = CardClass::MAGE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.StartGame();
    game.ProcessUntil(Step::MAIN_START);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetOpponentPlayer();
    curPlayer.SetTotalMana(10);
    curPlayer.SetUsedMana(0);
    opPlayer.SetTotalMana(10);
    opPlayer.SetUsedMana(0);

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Azure Drake"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Fireball"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Archmage"));

    auto curHandCount = curPlayer.GetHandZone().GetCount();

    game.Process(curPlayer, PlayCardTask::Minion(card1));
    EXPECT_EQ(curPlayer.GetHandZone().GetCount(), curHandCount);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, PlayCardTask::Minion(card3));
    
    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(curPlayer, PlayCardTask::SpellTarget(card2, card3));

    EXPECT_EQ(curPlayer.GetFieldZone().GetCount(), 1);
    EXPECT_EQ(opPlayer.GetFieldZone().GetCount(), 0);
}