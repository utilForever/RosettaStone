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

    TaskAgent& taskAgent = agent.GetTaskAgent();

    Player& player1 = agent.GetPlayer1();
    Player& player2 = agent.GetPlayer2();

    player1.totalMana = player1.existMana = 10;
    player2.totalMana = player2.existMana = 10;

    Card* FieryWarAxe = Cards::GetInstance()->FindCardByName("Fiery War Axe");
    Card* AcidicSwampOoze =
        Cards::GetInstance()->FindCardByName("Acidic Swamp Ooze");

    BasicTasks::DrawCardTask(FieryWarAxe).Run(player1, player2);
    EXPECT_EQ(agent.GetPlayer1().hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(agent.GetPlayer1().hand[0]->card->name, "Fiery War Axe");

    BasicTasks::DrawCardTask(AcidicSwampOoze).Run(player2, player1);
    EXPECT_EQ(agent.GetPlayer2().hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(agent.GetPlayer2().hand[0]->card->name, "Acidic Swamp Ooze");

    std::future<void> response1 = std::async(std::launch::async, [&agent]() {
        TaskMeta meta;
        agent.GetTaskMeta(meta);

        auto required = flatbuffers::GetRoot<FlatData::RequireTaskMeta>(
            meta.GetConstBuffer().get());
        EXPECT_EQ(TaskID::_from_integral(required->required()),
                  +TaskID::SELECT_CARD);

        meta = Serializer::CreateResponsePlayCard(0);
        agent.WriteSyncBuffer(std::move(meta));
    });

    MetaData result = BasicTasks::PlayCardTask(taskAgent).Run(player1, player2);
    EXPECT_EQ(result, MetaData::PLAY_WEAPON_SUCCESS);
    EXPECT_NE(agent.GetPlayer1().hero->weapon, nullptr);

    std::future<void> response2 = std::async(std::launch::async, [&agent]() {
        TaskMeta meta;
        agent.GetTaskMeta(meta);

        auto selectCard = flatbuffers::GetRoot<FlatData::RequireTaskMeta>(
            meta.GetConstBuffer().get());
        EXPECT_EQ(TaskID::_from_integral(selectCard->required()),
                  +TaskID::SELECT_CARD);

        TaskMeta card = Serializer::CreateResponsePlayCard(0);
        agent.WriteSyncBuffer(std::move(card));

        agent.GetTaskMeta(meta);
        auto selectPosition = flatbuffers::GetRoot<FlatData::RequireTaskMeta>(
            meta.GetConstBuffer().get());
        EXPECT_EQ(TaskID::_from_integral(selectPosition->required()),
                  +TaskID::SELECT_POSITION);

        TaskMeta position = Serializer::CreateResponsePlayMinion(0);
        agent.WriteSyncBuffer(std::move(position));
    });

    result = BasicTasks::PlayCardTask(taskAgent).Run(player2, player1);
    EXPECT_EQ(result, MetaData::PLAY_MINION_SUCCESS);
    EXPECT_EQ(agent.GetPlayer1().hero->weapon, nullptr);
}

TEST(BasicCard, CS2_041)
{
    GameAgent agent(
        Player(new Account("Player 1", ""), new Deck("", CardClass::SHAMAN)),
        Player(new Account("Player 2", ""), new Deck("", CardClass::MAGE)));

    Player& player1 = agent.GetPlayer1();
    Player& player2 = agent.GetPlayer2();

    player1.totalMana = agent.GetPlayer1().existMana = 10;
    player2.totalMana = agent.GetPlayer2().existMana = 10;

    Card* AcidicSwampOoze =
        Cards::GetInstance()->FindCardByName("Acidic Swamp Ooze");
    Card* AncestralHealing =
        Cards::GetInstance()->FindCardByName("Ancestral Healing");

    BasicTasks::DrawCardTask(AcidicSwampOoze).Run(player1, player2);
    BasicTasks::DrawCardTask(AncestralHealing).Run(player1, player2);
    EXPECT_EQ(agent.GetPlayer1().hand.size(), static_cast<size_t>(2));

//    agent.Process(agent.GetPlayer1(), BasicTask::PlayCardTask(0, 0));
//    auto minion = dynamic_cast<Character*>(agent.GetPlayer1().field.at(0));
//    minion->health -= 1;
//    EXPECT_EQ(minion->health, 1u);
//
//    agent.Process(agent.GetPlayer1(),
//                  BasicTask::PlayCardTask(0, -1, TargetType::MY_FIELD, 1));
//    EXPECT_EQ(static_cast<bool>(minion->gameTags[GameTag::TAUNT]), true);
//    EXPECT_EQ(minion->health, 2);
}