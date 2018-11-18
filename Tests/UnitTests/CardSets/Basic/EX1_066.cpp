// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.h>

#include <hspp/Cards/Cards.h>

TEST(BasicCardSet, EX1_066)
{
    GameAgent agent(CardClass::DRUID, CardClass::ROGUE, PLAYER1);

    TaskAgent& taskAgent = agent.GetTaskAgent();
    TestUtils::AutoResponder response(agent);

    Player& currentPlayer = agent.GetCurrentPlayer();
    Player& opponentPlayer = agent.GetCurrentPlayer().GetOpponent();

    currentPlayer.totalMana = currentPlayer.existMana = 10;
    opponentPlayer.totalMana = opponentPlayer.existMana = 10;

    agent.RunTask(currentPlayer,
                  BasicTasks::DrawCardTask(
                      Cards::GetInstance().FindCardByName("Fiery War Axe")));
    EXPECT_EQ(currentPlayer.hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(currentPlayer.hand[0]->card->name, "Fiery War Axe");

    agent.RunTask(opponentPlayer,
                  BasicTasks::DrawCardTask(Cards::GetInstance().FindCardByName(
                      "Acidic Swamp Ooze")));
    EXPECT_EQ(opponentPlayer.hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(opponentPlayer.hand[0]->card->name, "Acidic Swamp Ooze");

    // Create response for GameAgent to run PlayCardTask
    auto respPlayCard1 = response.PlayCard(0);
    MetaData result =
        agent.RunTask(currentPlayer, BasicTasks::PlayCardTask(taskAgent));
    EXPECT_EQ(result, MetaData::PLAY_WEAPON_SUCCESS);
    EXPECT_NE(currentPlayer.hero->weapon, static_cast<Weapon*>(nullptr));

    TaskMeta reqPlayCard1 = respPlayCard1.get();
    EXPECT_EQ(reqPlayCard1.id, +TaskID::REQUIRE);
    auto require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(reqPlayCard1);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_CARD);

    // Create multiple response for PlayCardTask And PlayMinionTask
    auto respAutoMinion = response.AutoMinion(0, 0);
    result = agent.RunTask(opponentPlayer, BasicTasks::PlayCardTask(taskAgent));
    EXPECT_EQ(result, MetaData::PLAY_MINION_SUCCESS);
    EXPECT_EQ(currentPlayer.hero->weapon, static_cast<Weapon*>(nullptr));

    auto [respPlayCard2, respPlayMinion] = respAutoMinion.get();
    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayCard2);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_CARD);

    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayMinion);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_POSITION);
}