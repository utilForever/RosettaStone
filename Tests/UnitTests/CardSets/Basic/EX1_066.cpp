// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.h>

#include <hspp/Cards/Cards.h>

using namespace BasicTasks;

TEST(BasicCardSet, EX1_066)
{
    GameAgent agent(CardClass::DRUID, CardClass::ROGUE, PLAYER1);
    TaskAgent& taskAgent = agent.GetTaskAgent();

    Player& currentPlayer = agent.GetCurrentPlayer();
    Player& opponentPlayer = agent.GetCurrentPlayer().GetOpponent();
    currentPlayer.totalMana = currentPlayer.existMana = 10;
    opponentPlayer.totalMana = opponentPlayer.existMana = 10;

    GameAgent::RunTask(
        currentPlayer,
        DrawCardTask(Cards::GetInstance().FindCardByName("Fiery War Axe")));
    EXPECT_EQ(currentPlayer.hand.size(), 1u);
    EXPECT_EQ(currentPlayer.hand[0]->card->name, "Fiery War Axe");

    GameAgent::RunTask(
        opponentPlayer,
        DrawCardTask(Cards::GetInstance().FindCardByName("Acidic Swamp Ooze")));
    EXPECT_EQ(opponentPlayer.hand.size(), 1u);
    EXPECT_EQ(opponentPlayer.hand[0]->card->name, "Acidic Swamp Ooze");

    GameAgent::RunTask(currentPlayer, PlayCardTask(taskAgent));
    EXPECT_NE(currentPlayer.hero->weapon, static_cast<Weapon*>(nullptr));

    GameAgent::RunTask(opponentPlayer, PlayCardTask(taskAgent));
    EXPECT_EQ(currentPlayer.hero->weapon, static_cast<Weapon*>(nullptr));
}