// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.h>

#include <hspp/Cards/Cards.h>

using namespace BasicTasks;

TEST(ClassicCardSet, CS2_088)
{
    GameAgent agent(CardClass::DRUID, CardClass::ROGUE, PLAYER1);
    TaskAgent& taskAgent = agent.GetTaskAgent();

    Player& currentPlayer = agent.GetCurrentPlayer();
    Player& opponentPlayer = agent.GetCurrentPlayer().GetOpponent();
    currentPlayer.totalMana = currentPlayer.existMana = 10;
    opponentPlayer.totalMana = opponentPlayer.existMana = 10;
    opponentPlayer.hero->health = 24;

    GameAgent::RunTask(
        currentPlayer,
        DrawCardTask(Cards::GetInstance().FindCardByName("Acidic Swamp Ooze")));
    EXPECT_EQ(currentPlayer.hand.size(), 1u);
    EXPECT_EQ(currentPlayer.hand[0]->card->name, "Acidic Swamp Ooze");

    GameAgent::RunTask(
        opponentPlayer,
        DrawCardTask(Cards::GetInstance().FindCardByName("Guardian of Kings")));
    EXPECT_EQ(opponentPlayer.hand.size(), 1u);
    EXPECT_EQ(opponentPlayer.hand[0]->card->name, "Guardian of Kings");

    GameAgent::RunTask(currentPlayer, PlayCardTask(taskAgent));
    EXPECT_EQ(currentPlayer.field[0]->card->name, "Acidic Swamp Ooze");

    GameAgent::RunTask(opponentPlayer, PlayCardTask(taskAgent));
    EXPECT_EQ(opponentPlayer.field[0]->card->name, "Guardian of Kings");
    EXPECT_EQ(opponentPlayer.hero->maxHealth, opponentPlayer.hero->health);
}