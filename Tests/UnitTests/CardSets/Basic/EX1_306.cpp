// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.h>

#include <hspp/Cards/Cards.h>

TEST(BasicCardSet, EX1_306)
{
    GameAgent agent(CardClass::DRUID, CardClass::ROGUE, PLAYER1);

    TaskAgent& taskAgent = agent.GetTaskAgent();
    TestUtils::AutoResponder response(agent);

    Player& player1 = agent.GetCurrentPlayer();
    Player& player2 = agent.GetCurrentPlayer().GetOpponent();

    player1.totalMana = player1.existMana = 10;
    player2.totalMana = player2.existMana = 10;

    // Each players draw 2 cards.
    agent.RunTask(player1,
                  BasicTasks::DrawCardTask(
                      Cards::GetInstance().FindCardByName("Succubus")));
    EXPECT_EQ(player1.hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(player1.hand[0]->card->name, "Succubus");

    agent.RunTask(player1,
                  BasicTasks::DrawCardTask(
                      Cards::GetInstance().FindCardByName("Fiery War Axe")));
    EXPECT_EQ(player1.hand.size(), static_cast<size_t>(2));
    EXPECT_EQ(player1.hand[1]->card->name, "Fiery War Axe");

    agent.RunTask(
        player2, BasicTasks::DrawCardTask(
                     Cards::GetInstance().FindCardByName("Acidic Swamp Ooze")));
    EXPECT_EQ(player2.hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(player2.hand[0]->card->name, "Acidic Swamp Ooze");

    agent.RunTask(player2,
                  BasicTasks::DrawCardTask(
                      Cards::GetInstance().FindCardByName("Stonetusk Boar")));
    EXPECT_EQ(player2.hand.size(), static_cast<size_t>(2));
    EXPECT_EQ(player2.hand[1]->card->name, "Stonetusk Boar");

    // Player 1 plays Succubus, and now the player 1's hand is empty
    auto respAutoMinion = response.AutoMinion(0, 0);
    MetaData result =
        agent.RunTask(player1, BasicTasks::PlayCardTask(taskAgent));
    EXPECT_EQ(result, MetaData::PLAY_MINION_SUCCESS);
    EXPECT_EQ(player1.hand.size(), static_cast<size_t>(0));

    auto [respPlayCard1, respPlayMinion1] = respAutoMinion.get();
    auto require =
        TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayCard1);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_CARD);

    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayMinion1);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_POSITION);

    // This task doesn't affect player 2's hand
    respAutoMinion = response.AutoMinion(0, 0);
    result = agent.RunTask(player2, BasicTasks::PlayCardTask(taskAgent));
    EXPECT_EQ(result, MetaData::PLAY_MINION_SUCCESS);
    EXPECT_EQ(player2.hand.size(), static_cast<size_t>(1));

    auto [respPlayCard2, respPlayMinion2] = respAutoMinion.get();
    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayCard2);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_CARD);

    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayMinion2);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_POSITION);
}