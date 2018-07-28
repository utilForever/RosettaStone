#include "TestUtils/ResponseUtils.h"
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
    TestUtils::AutoResponder response(agent);

    Player& player1 = agent.GetPlayer1();
    Player& player2 = agent.GetPlayer2();

    player1.totalMana = player1.existMana = 10;
    player2.totalMana = player2.existMana = 10;

    Card* FieryWarAxe = Cards::GetInstance()->FindCardByName("Fiery War Axe");
    Card* AcidicSwampOoze =
        Cards::GetInstance()->FindCardByName("Acidic Swamp Ooze");

    agent.RunTask(BasicTasks::DrawCardTask(FieryWarAxe), player1, player2);
    EXPECT_EQ(agent.GetPlayer1().hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(agent.GetPlayer1().hand[0]->card->name, "Fiery War Axe");

    agent.RunTask(BasicTasks::DrawCardTask(AcidicSwampOoze), player2, player1);
    EXPECT_EQ(agent.GetPlayer2().hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(agent.GetPlayer2().hand[0]->card->name, "Acidic Swamp Ooze");

    // Create Response for GameAgent to Run PlayCardTask
    std::future<TaskMeta> respPlayCard = response.PlayCard(0);
    MetaData result =
        agent.RunTask(BasicTasks::PlayCardTask(taskAgent), player1, player2);
    EXPECT_EQ(result, MetaData::PLAY_WEAPON_SUCCESS);
    EXPECT_NE(agent.GetPlayer1().hero->weapon, nullptr);

    TaskMeta reqPlayCard = respPlayCard.get();
    EXPECT_EQ(reqPlayCard.id, +TaskID::REQUIRE);
    auto require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(reqPlayCard);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_CARD);

    // Create Multiple Response for PlayCardTask And PlayMinionTask
    auto resp = response.AutoMinion(0, 0);
    result =
        agent.RunTask(BasicTasks::PlayCardTask(taskAgent), player2, player1);
    EXPECT_EQ(result, MetaData::PLAY_MINION_SUCCESS);
    EXPECT_EQ(agent.GetPlayer1().hero->weapon, nullptr);

    auto [respPlayCard2, respPlayMinion] = resp.get();
    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayCard2);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_CARD);

    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayMinion);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_POSITION);
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

    agent.RunTask(BasicTasks::DrawCardTask(AcidicSwampOoze), player1, player2);
    agent.RunTask(BasicTasks::DrawCardTask(AncestralHealing), player1, player2);
    EXPECT_EQ(agent.GetPlayer1().hand.size(), static_cast<size_t>(2));

    //
    //    agent.Process(agent.GetPlayer1(), BasicTask::PlayCardTask(0, 0));
    //    auto minion =
    //    dynamic_cast<Character*>(agent.GetPlayer1().field.at(0));
    //    minion->health -= 1;
    //    EXPECT_EQ(minion->health, 1u);
    //
    //    agent.Process(agent.GetPlayer1(),
    //                  BasicTask::PlayCardTask(0, -1, TargetType::MY_FIELD,
    //                  1));
    //    EXPECT_EQ(static_cast<bool>(minion->gameTags[GameTag::TAUNT]), true);
    //    EXPECT_EQ(minion->health, 2);
}
