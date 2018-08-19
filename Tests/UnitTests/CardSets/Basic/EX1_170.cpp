#include <Utils/CardSetUtils.h>

TEST(BasicCardSet, EX1_170)
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
                      Cards::GetInstance()->FindCardByName("Emperor Cobra")),
                  player1, player2);

    agent.RunTask(BasicTasks::DrawCardTask(
                      Cards::GetInstance()->FindCardByName("Stormwind Knight")),
                  player2, player1);

    // Create multiple response for PlayCardTask And PlayMinionTask
    auto respAutoMinion = response.AutoMinion(0, 0);
    agent.RunTask(BasicTasks::PlayCardTask(taskAgent), player1, player2);

    auto [respPlayCard1, respPlayMinion1] = respAutoMinion.get();
    TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayCard1);
    TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayMinion1);

    // Create multiple response for PlayCardTask And PlayMinionTask
    respAutoMinion = response.AutoMinion(0, 0);
    agent.RunTask(BasicTasks::PlayCardTask(taskAgent), player2, player1);

    auto [respPlayCard2, respPlayMinion2] = respAutoMinion.get();
    TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayCard2);
    TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayMinion2);

    auto respAutoTarget = response.Target(1, 1);
    auto result =
        agent.RunTask(BasicTasks::CombatTask(taskAgent), player2, player1);
    EXPECT_EQ(result, MetaData::COMBAT_SUCCESS);

    EXPECT_EQ(agent.GetPlayer1().field[0]->health, static_cast<size_t>(1));
    EXPECT_EQ(agent.GetPlayer2().field.size(), static_cast<size_t>(0));
}