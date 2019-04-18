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

TEST(HoFCardsGen, EX1_050)
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

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 6u);
    EXPECT_EQ(opPlayer.GetHand().GetNumOfCards(), 7u);
}

TEST(HoFCardsGen, EX1_310)
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
    
    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card1));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 2u);
    
    Task::Run(curPlayer, AttackTask(card1, opPlayer.GetHero()));
    EXPECT_EQ(opPlayer.GetHero()->GetHealth(), 25);
    
    Task::Run(opPlayer, PlayCardTask::Minion(opPlayer, card2));
    EXPECT_EQ(opPlayer.GetHand().GetNumOfCards(), 5u);
}

