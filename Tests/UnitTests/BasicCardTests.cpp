#include "gtest/gtest.h"

#include <Syncs/GameAgent.h>
#include <Syncs/Interface.h>
#include <Tasks/BasicTask.h>

using namespace Hearthstonepp;

TEST(BasicCard, EX1_066)
{
    GameAgent agent(
        Player(new Account("Player 1", ""), new Deck("", CardClass::WARRIOR)),
        Player(new Account("Player 2", ""), new Deck("", CardClass::MAGE)));
    agent.GetPlayer1().totalMana = agent.GetPlayer1().existMana = 10;
    agent.GetPlayer2().totalMana = agent.GetPlayer2().existMana = 10;

    agent.Process(agent.GetPlayer1(),
                  BasicTask::DrawTask(
                      Cards::GetInstance()->FindCardByName("Fiery War Axe")));
    EXPECT_EQ(agent.GetPlayer1().hand.size(), static_cast<size_t>(1));

    agent.Process(agent.GetPlayer2(),
                  BasicTask::DrawTask(Cards::GetInstance()->FindCardByName(
                      "Acidic Swamp Ooze")));
    EXPECT_EQ(agent.GetPlayer2().hand.size(), static_cast<size_t>(1));

    agent.Process(
        agent.GetPlayer1(),
        BasicTask::PlayCardTask(0));
    EXPECT_EQ(agent.GetPlayer1().hero->weapon != nullptr, true);

    agent.Process(
        agent.GetPlayer2(),
        BasicTask::PlayCardTask(0, 0));
    EXPECT_EQ(agent.GetPlayer1().hero->weapon != nullptr, false);
}