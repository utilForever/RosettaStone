#include <Utils/CardSetUtils.h>

TEST(BasicCard, EX1_008)
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

    std::string player1Card = "Argent Squire";
    std::string player2Card = "Grimscale Oracle";

    agent.RunTask(BasicTasks::DrawCardTask(
                      Cards::GetInstance()->FindCardByName(player1Card)),
                  player1, player2);

    agent.RunTask(BasicTasks::DrawCardTask(
                      Cards::GetInstance()->FindCardByName(player2Card)),
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

    agent.RunTask(BasicTasks::InitAttackCountTask(player2), player1, player2);

    auto respAutoTarget = response.Target(1, 1);
    EXPECT_EQ(agent.GetPlayer1().field[0]->gameTags[+GameTag::DIVINE_SHIELD],
              1);
    auto result =
        agent.RunTask(BasicTasks::CombatTask(taskAgent), player2, player1);
    EXPECT_EQ(result, MetaData::COMBAT_SUCCESS);
    EXPECT_EQ(agent.GetPlayer1().field[0]->health,
              agent.GetPlayer1().field[0]->maxHealth);
    EXPECT_EQ(agent.GetPlayer1().field[0]->gameTags[+GameTag::DIVINE_SHIELD],
              0);
}