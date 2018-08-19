#include <Utils/CardSetUtils.h>

TEST(ClassicCardSet, CS2_187)
{
    GameAgent agent(
        Player(new Account("Player 1", ""), new Deck("", CardClass::ROGUE)),
        Player(new Account("Player 2", ""), new Deck("", CardClass::WARRIOR)));

    TaskAgent& taskAgent = agent.GetTaskAgent();
    TestUtils::AutoResponder response(agent);

    Player& player1 = agent.GetPlayer1();
    Player& player2 = agent.GetPlayer2();

    player1.totalMana = agent.GetPlayer1().existMana = 10;
    player2.totalMana = agent.GetPlayer2().existMana = 10;

    agent.RunTask(BasicTasks::DrawCardTask(Cards::GetInstance()->FindCardByName(
                      "Booty Bay Bodyguard")),
                  player1, player2);
    EXPECT_EQ(agent.GetPlayer1().hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(agent.GetPlayer1().hand[0]->card->name, "Booty Bay Bodyguard");

    agent.RunTask(BasicTasks::DrawCardTask(
                      Cards::GetInstance()->FindCardByName("Bloodfen Raptor")),
                  player1, player2);
    EXPECT_EQ(agent.GetPlayer1().hand.size(), static_cast<size_t>(2));
    EXPECT_EQ(agent.GetPlayer1().hand[1]->card->name, "Bloodfen Raptor");

    agent.RunTask(BasicTasks::DrawCardTask(
                      Cards::GetInstance()->FindCardByName("Chillwind Yeti")),
                  player2, player1);
    EXPECT_EQ(agent.GetPlayer2().hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(agent.GetPlayer2().hand[0]->card->name, "Chillwind Yeti");

    // Create multiple response for PlayCardTask And PlayMinionTask
    auto respAutoMinion = response.AutoMinion(0, 0);
    MetaData result =
        agent.RunTask(BasicTasks::PlayCardTask(taskAgent), player1, player2);
    EXPECT_EQ(result, MetaData::PLAY_MINION_SUCCESS);
    EXPECT_EQ(agent.GetPlayer1().field[0]->card->name, "Booty Bay Bodyguard");

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
        agent.RunTask(BasicTasks::PlayCardTask(taskAgent), player1, player2);
    EXPECT_EQ(result, MetaData::PLAY_MINION_SUCCESS);
    EXPECT_EQ(agent.GetPlayer1().field[0]->card->name, "Bloodfen Raptor");
    EXPECT_EQ(agent.GetPlayer1().field.size(), static_cast<size_t>(2));

    auto [respPlayCard1_1, respPlayMinion1_1] = respAutoMinion.get();
    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayCard1_1);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_CARD);

    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayMinion1_1);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_POSITION);

    // Create multiple response for PlayCardTask And PlayMinionTask
    respAutoMinion = response.AutoMinion(0, 0);
    result =
        agent.RunTask(BasicTasks::PlayCardTask(taskAgent), player2, player1);
    EXPECT_EQ(result, MetaData::PLAY_MINION_SUCCESS);
    EXPECT_EQ(agent.GetPlayer2().field[0]->card->name, "Chillwind Yeti");

    auto [respPlayCard2, respPlayMinion2] = respAutoMinion.get();
    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayCard2);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_CARD);

    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayMinion2);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_POSITION);

    TaskMeta tempTaskMeta;
    taskAgent.RunMulti(tempTaskMeta, player1, player2,
                       BasicTasks::SwapPlayerTask(),
                       BasicTasks::SwapPlayerTask());

    // TODO: Add new test scenario for Taunt minion to interrupt opponent
    // minions from attacking the hero. CombatTask result must return FAILURE if
    // it's targeted by opponent minion, but it's not implemented yet.

    // Chillwind Yeti try to attack Bloodfen but Booty Bay Bodyguard with Taunt
    auto resAutoTarget = response.Target(1, 1);
    result = agent.RunTask(BasicTasks::CombatTask(taskAgent), player2, player1);
    EXPECT_EQ(result, MetaData::COMBAT_FIELD_HAVE_TAUNT);

    // Chillwind Yeti attack to Booty Bay Bodyguard with Taunt
    resAutoTarget = response.Target(1, 2);
    result = agent.RunTask(BasicTasks::CombatTask(taskAgent), player2, player1);
    EXPECT_EQ(result, MetaData::COMBAT_SUCCESS);
    EXPECT_EQ(agent.GetPlayer1().field.size(), static_cast<size_t>(1));
    EXPECT_EQ(agent.GetPlayer1().field[0]->health, static_cast<size_t>(2));
    EXPECT_EQ(agent.GetPlayer2().field.size(), static_cast<size_t>(0));
}