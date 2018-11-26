// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.h>

#include <hspp/Actions/Generic.h>
#include <hspp/Cards/Cards.h>

using namespace Hearthstonepp;
using namespace BasicTasks;

TEST(ClassicCardSet, CS2_041)
{
    GameAgent agent(CardClass::DRUID, CardClass::ROGUE, PlayerType::PLAYER1);
    TaskAgent& taskAgent = agent.GetTaskAgent();

    Player& currentPlayer = agent.GetCurrentPlayer();
    Player& opponentPlayer = agent.GetCurrentPlayer().GetOpponent();
    currentPlayer.SetMaximumMana(10);
    currentPlayer.SetAvailableMana(10);
    opponentPlayer.SetMaximumMana(10);
    opponentPlayer.SetAvailableMana(10);

    const auto card1 = Generic::DrawCard(
        currentPlayer,
        Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));
    EXPECT_EQ(currentPlayer.GetHand().size(), 1u);
    EXPECT_EQ(currentPlayer.GetHand()[0]->card->name, "Acidic Swamp Ooze");

    const auto card2 = Generic::DrawCard(
        currentPlayer,
        Cards::GetInstance().FindCardByName("Ancestral Healing"));
    EXPECT_EQ(currentPlayer.GetHand().size(), 2u);
    EXPECT_EQ(currentPlayer.GetHand()[1]->card->name, "Ancestral Healing");

    const auto card3 = Generic::DrawCard(
        opponentPlayer, Cards::GetInstance().FindCardByName("Stonetusk Boar"));
    EXPECT_EQ(opponentPlayer.GetHand().size(), 1u);
    EXPECT_EQ(opponentPlayer.GetHand()[0]->card->name, "Stonetusk Boar");

    GameAgent::RunTask(currentPlayer, PlayCardTask(taskAgent, card1));
    EXPECT_EQ(currentPlayer.GetField()[0]->card->name, "Acidic Swamp Ooze");

    GameAgent::RunTask(opponentPlayer, PlayCardTask(taskAgent, card3));
    EXPECT_EQ(opponentPlayer.GetField()[0]->card->name, "Stonetusk Boar");

    GameAgent::RunTask(opponentPlayer, CombatTask(taskAgent, card3, card1));
    EXPECT_EQ(currentPlayer.GetField()[0]->health, 1);
    EXPECT_EQ(opponentPlayer.GetField().size(), 0u);

    GameAgent::RunTask(currentPlayer, PlayCardTask(taskAgent, card2, -1, card1));
    EXPECT_EQ(currentPlayer.GetField()[0]->health, 2);
    EXPECT_EQ(currentPlayer.GetField()[0]->GetGameTag(GameTag::TAUNT), 1);
}