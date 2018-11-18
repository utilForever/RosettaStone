// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.h>

#include <hspp/Cards/Cards.h>

TEST(ClassicCardSet, CS2_088)
{
    // init agent state
    GameAgent agent(CardClass::DRUID, CardClass::ROGUE, PLAYER1);

    TaskAgent& taskAgent = agent.GetTaskAgent();
    TestUtils::AutoResponder response(agent);

    Player& player1 = agent.GetPlayer1();
    Player& player2 = agent.GetPlayer2();

    player1.totalMana = player1.existMana = 10;
    player2.totalMana = player2.existMana = 10;
    player2.hero->health = 24;

    // drawing procedure of player 1
    agent.RunTask(agent.GetCurrentPlayer(),
                  BasicTasks::DrawCardTask(Cards::GetInstance().FindCardByName(
                      "Acidic Swamp Ooze")));
    EXPECT_EQ(agent.GetPlayer1().hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(agent.GetPlayer1().hand[0]->card->name, "Acidic Swamp Ooze");

    // drawing procedure of player 2
    agent.RunTask(agent.GetOpponentPlayer(),
                  BasicTasks::DrawCardTask(Cards::GetInstance().FindCardByName(
                      "Guardian of Kings")));
    EXPECT_EQ(agent.GetPlayer2().hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(agent.GetPlayer2().hand[0]->card->name, "Guardian of Kings");

    // Create multiple response for PlayCardTask And PlayMinionTask
    auto respAutoMinion = response.AutoMinion(0, 0);
    MetaData result = agent.RunTask(agent.GetCurrentPlayer(),
                                    BasicTasks::PlayCardTask(taskAgent));
    EXPECT_EQ(result, MetaData::PLAY_MINION_SUCCESS);
    EXPECT_EQ(agent.GetPlayer1().field[0]->card->name, "Acidic Swamp Ooze");

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
    result = agent.RunTask(agent.GetOpponentPlayer(),
                           BasicTasks::PlayCardTask(taskAgent));
    EXPECT_EQ(result, MetaData::PLAY_MINION_SUCCESS);
    EXPECT_EQ(agent.GetPlayer2().field[0]->card->name, "Guardian of Kings");

    auto [respPlayCard2, respPlayMinion2] = respAutoMinion.get();
    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayCard2);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_CARD);

    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayMinion2);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_POSITION);

    EXPECT_EQ(player2.hero->maxHealth, player2.hero->health);
}