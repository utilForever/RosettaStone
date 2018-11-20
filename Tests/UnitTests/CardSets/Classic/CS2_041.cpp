// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.h>

#include <hspp/Cards/Cards.h>

using namespace BasicTasks;

TEST(ClassicCardSet, CS2_041)
{
    GameAgent agent(CardClass::DRUID, CardClass::ROGUE, PLAYER1);
    TaskAgent& taskAgent = agent.GetTaskAgent();

    Player& currentPlayer = agent.GetCurrentPlayer();
    Player& opponentPlayer = agent.GetCurrentPlayer().GetOpponent();
    currentPlayer.totalMana = currentPlayer.existMana = 10;
    opponentPlayer.totalMana = opponentPlayer.existMana = 10;

    GameAgent::RunTask(
        currentPlayer,
        DrawCardTask(Cards::GetInstance().FindCardByName("Acidic Swamp Ooze")));
    EXPECT_EQ(currentPlayer.hand.size(), 1u);
    EXPECT_EQ(currentPlayer.hand[0]->card->name, "Acidic Swamp Ooze");

    GameAgent::RunTask(
        currentPlayer,
        DrawCardTask(Cards::GetInstance().FindCardByName("Ancestral Healing")));
    EXPECT_EQ(currentPlayer.hand.size(), 2u);
    EXPECT_EQ(currentPlayer.hand[1]->card->name, "Ancestral Healing");

    GameAgent::RunTask(
        opponentPlayer,
        DrawCardTask(Cards::GetInstance().FindCardByName("Stonetusk Boar")));
    EXPECT_EQ(opponentPlayer.hand.size(), 1u);
    EXPECT_EQ(opponentPlayer.hand[0]->card->name, "Stonetusk Boar");

    GameAgent::RunTask(currentPlayer, PlayCardTask(taskAgent));
    EXPECT_EQ(currentPlayer.field[0]->card->name, "Acidic Swamp Ooze");

    GameAgent::RunTask(agent.GetOpponentPlayer(), PlayCardTask(taskAgent));
    EXPECT_EQ(opponentPlayer.field[0]->card->name, "Stonetusk Boar");

    GameAgent::RunTask(agent.GetOpponentPlayer(), CombatTask(taskAgent));
    EXPECT_EQ(currentPlayer.field[0]->health, 1u);
    EXPECT_EQ(opponentPlayer.field.size(), 0u);

    GameAgent::RunTask(currentPlayer, PlayCardTask(taskAgent));
    EXPECT_EQ(currentPlayer.field[0]->health, 2u);
    EXPECT_EQ(currentPlayer.field[0]->GetGameTag(GameTag::TAUNT), 1);
}