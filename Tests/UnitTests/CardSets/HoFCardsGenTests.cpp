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
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 2u);

    game.Process(curPlayer, AttackTask(card1, opPlayer.GetHero()));
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 25);

    game.Process(curPlayer, EndTurnTask());
    game.ProcessUntil(Step::MAIN_START);

    game.Process(opPlayer, PlayCardTask::Minion(card2));
    EXPECT_EQ(opPlayer.GetHand().GetNumOfCards(), 6u);
}

// --------------------------------------- MINION - NEUTRAL
// [EX1_050] Coldlight Oracle - COST:3
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
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 5u);

    game.Process(curPlayer, PlayCardTask::Minion(card));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 6u);
    EXPECT_EQ(opPlayer.GetHand().GetNumOfCards(), 7u);
}