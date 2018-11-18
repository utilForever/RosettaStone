// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.h>

#include <hspp/Cards/Cards.h>

TEST(ClassicCardSet, CS2_041)
{
    GameAgent agent(CardClass::DRUID, CardClass::ROGUE, PLAYER1);

    TaskAgent& taskAgent = agent.GetTaskAgent();
    TestUtils::AutoResponder response(agent);

    Player& player1 = agent.GetPlayer1();
    Player& player2 = agent.GetPlayer2();

    player1.totalMana = agent.GetPlayer1().existMana = 10;
    player2.totalMana = agent.GetPlayer2().existMana = 10;

    agent.RunTask(agent.GetCurrentPlayer(),
                  BasicTasks::DrawCardTask(Cards::GetInstance().FindCardByName(
                      "Acidic Swamp Ooze")));
    EXPECT_EQ(agent.GetPlayer1().hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(agent.GetPlayer1().hand[0]->card->name, "Acidic Swamp Ooze");

    agent.RunTask(agent.GetCurrentPlayer(),
                  BasicTasks::DrawCardTask(Cards::GetInstance().FindCardByName(
                      "Ancestral Healing")));
    EXPECT_EQ(agent.GetPlayer1().hand.size(), static_cast<size_t>(2));
    EXPECT_EQ(agent.GetPlayer1().hand[1]->card->name, "Ancestral Healing");

    agent.RunTask(agent.GetOpponentPlayer(),
                  BasicTasks::DrawCardTask(
                      Cards::GetInstance().FindCardByName("Stonetusk Boar")));
    EXPECT_EQ(agent.GetPlayer2().hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(agent.GetPlayer2().hand[0]->card->name, "Stonetusk Boar");

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
    EXPECT_EQ(agent.GetPlayer2().field[0]->card->name, "Stonetusk Boar");

    auto [respPlayCard2, respPlayMinion2] = respAutoMinion.get();
    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayCard2);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_CARD);

    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayMinion2);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_POSITION);

    auto respAutoTarget = response.Target(1, 1);
    result = agent.RunTask(agent.GetOpponentPlayer(),
                           BasicTasks::CombatTask(taskAgent));
    EXPECT_EQ(result, MetaData::COMBAT_SUCCESS);
    EXPECT_EQ(agent.GetPlayer1().field[0]->health, static_cast<size_t>(1));
    EXPECT_EQ(agent.GetPlayer2().field.size(), static_cast<size_t>(0));

    // Create multiple response for PlayCardTask And PlaySpellTask
    auto respAutoSpell = response.AutoSpell(0, EntityType::FIELD, 0);
    result = agent.RunTask(agent.GetCurrentPlayer(),
                           BasicTasks::PlayCardTask(taskAgent));
    EXPECT_EQ(result, MetaData::PLAY_SPELL_SUCCESS);

    auto [respPlayCard3, respPlaySpell] = respAutoSpell.get();
    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayCard3);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_CARD);

    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlaySpell);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_TARGET);

    EXPECT_EQ(agent.GetPlayer1().field[0]->health, static_cast<size_t>(2));
    EXPECT_EQ(agent.GetPlayer1().field[0]->GetGameTag(GameTag::TAUNT), 1);
}