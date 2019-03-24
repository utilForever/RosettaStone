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

    Game game(config);
    game.StartGame();

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetCurrentPlayer().GetOpponent();
    curPlayer.maximumMana = 10;
    curPlayer.currentMana = 10;

    std::size_t initHandNum = curPlayer.GetHand().GetNumOfCards();
    std::size_t initOpHandNum = opPlayer.GetHand().GetNumOfCards();

    const auto card = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Coldlight Oracle"));

    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), initHandNum + 1u);

    Task::Run(curPlayer, PlayCardTask::Minion(curPlayer, card));

    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), initHandNum + 2u);
    EXPECT_EQ(opPlayer.GetHand().GetNumOfCards(), initOpHandNum + 2u);
}
