// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.h>

TEST(ClassicCardSet, CS2_201)
{
    GameAgent agent(
        Player(new Account("Player 1", ""), new Deck("", CardClass::SHAMAN)),
        Player(new Account("Player 2", ""), new Deck("", CardClass::MAGE)));
    TaskAgent& taskAgent = agent.GetTaskAgent();
    TestUtils::AutoResponder response(agent);
    Player& player1 = agent.GetPlayer1();
    Player& player2 = agent.GetPlayer2();
    player1.totalMana = agent.GetPlayer1().existMana = 10;
    player2.totalMana = agent.GetPlayer2().existMana = 10;
    agent.RunTask(BasicTasks::DrawCardTask(
                      Cards::GetInstance()->FindCardByName("Stonetusk Boar")),
                  player1, player2);
    EXPECT_EQ(agent.GetPlayer1().hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(agent.GetPlayer1().hand[0]->card->name, "Stonetusk Boar");
    agent.RunTask(BasicTasks::DrawCardTask(
                      Cards::GetInstance()->FindCardByName("Core Hound")),
                  player2, player1);
    EXPECT_EQ(agent.GetPlayer2().hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(agent.GetPlayer2().hand[0]->card->name, "Core Hound");
    // Create multiple response for PlayCardTask And PlayMinionTask
    auto respAutoMinion = response.AutoMinion(0, 0);
    MetaData result =
        agent.RunTask(BasicTasks::PlayCardTask(taskAgent), player1, player2);
    EXPECT_EQ(result, MetaData::PLAY_MINION_SUCCESS);
    EXPECT_EQ(agent.GetPlayer1().field[0]->card->name, "Stonetusk Boar");
    auto [respPlayCard1, respPlayMinion1] = respAutoMinion.get();
    auto require =
        TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayCard1);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_CARD);
    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayMinion1);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_POSITION);
    // Create multiple response for PlayCardTask And PlayMinionTask
    respAutoMinion = response.AutoMinion(0, 0);
    result =
        agent.RunTask(BasicTasks::PlayCardTask(taskAgent), player2, player1);
    EXPECT_EQ(result, MetaData::PLAY_MINION_SUCCESS);
    EXPECT_EQ(agent.GetPlayer2().field[0]->card->name, "Core Hound");
    auto [respPlayCard2, respPlayMinion2] = respAutoMinion.get();
    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayCard2);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_CARD);
    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayMinion2);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_POSITION);
    auto respAutoTarget = response.Target(1, 1);
    result = agent.RunTask(BasicTasks::CombatTask(taskAgent), player1, player2);
    EXPECT_EQ(result, MetaData::COMBAT_SUCCESS);
    EXPECT_EQ(agent.GetPlayer1().field.size(), static_cast<size_t>(0));
    EXPECT_EQ(agent.GetPlayer2().field[0]->health, static_cast<size_t>(4));
}