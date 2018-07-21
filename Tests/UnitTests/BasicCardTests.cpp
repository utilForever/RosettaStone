#include "gtest/gtest.h"

#include <Managers/GameAgent.h>
#include <Managers/GameInterface.h>
#include <Tasks/BasicTasks/Draw.h>
#include <Tasks/BasicTasks/PlayCard.h>

#include <future>

using namespace Hearthstonepp;

TEST(BasicCard, EX1_066)
{
    GameAgent agent(
        Player(new Account("Player 1", ""), new Deck("", CardClass::WARRIOR)),
        Player(new Account("Player 2", ""), new Deck("", CardClass::MAGE)));
    agent.GetPlayer1().totalMana = agent.GetPlayer1().existMana = 10;
    agent.GetPlayer2().totalMana = agent.GetPlayer2().existMana = 10;

    agent.Process(agent.GetPlayer1(),
                  BasicTasks::DrawCardTask(
                      Cards::GetInstance()->FindCardByName("Fiery War Axe")));
    EXPECT_EQ(agent.GetPlayer1().hand.size(), static_cast<size_t>(1));

    agent.Process(agent.GetPlayer2(),
                  BasicTasks::DrawCardTask(Cards::GetInstance()->FindCardByName(
                      "Acidic Swamp Ooze")));
    EXPECT_EQ(agent.GetPlayer2().hand.size(), static_cast<size_t>(1));

    TaskAgent& taskAgent = agent.GetTaskAgent();

    agent.Process(agent.GetPlayer1(), BasicTasks::PlayCardTask(taskAgent));
    std::future<void>

    EXPECT_NE(agent.GetPlayer1().hero->weapon, nullptr);

    agent.Process(agent.GetPlayer2(), BasicTasks::PlayCardTask(taskAgent));
    EXPECT_EQ(agent.GetPlayer1().hero->weapon, nullptr);
}

TEST(BasicCard, CS2_041)
{
    GameAgent agent(
        Player(new Account("Player 1", ""), new Deck("", CardClass::SHAMAN)),
        Player(new Account("Player 2", ""), new Deck("", CardClass::MAGE)));
    agent.GetPlayer1().totalMana = agent.GetPlayer1().existMana = 10;
    agent.GetPlayer2().totalMana = agent.GetPlayer2().existMana = 10;

    agent.Process(agent.GetPlayer1(),
                  BasicTasks::DrawCardTask(Cards::GetInstance()->FindCardByName(
                      "Acidic Swamp Ooze")));
    agent.Process(agent.GetPlayer1(),
                  BasicTasks::DrawCardTask(Cards::GetInstance()->FindCardByName(
                      "Ancestral Healing")));
    EXPECT_EQ(agent.GetPlayer1().hand.size(), static_cast<size_t>(2));
//
//    agent.Process(agent.GetPlayer1(), BasicTask::PlayCardTask(0, 0));
//    auto minion = dynamic_cast<Character*>(agent.GetPlayer1().field.at(0));
//    minion->health -= 1;
//    EXPECT_EQ(minion->health, 1u);
//
//    agent.Process(agent.GetPlayer1(),
//                  BasicTask::PlayCardTask(0, -1, TargetType::MY_FIELD, 1));
    // EXPECT_EQ(static_cast<bool>(minion->gameTags[GameTag::TAUNT]), true);
    // EXPECT_EQ(minion->health, 2);
}