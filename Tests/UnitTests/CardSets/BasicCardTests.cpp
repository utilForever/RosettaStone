#include "gtest/gtest.h"

#include <Utils/ResponseUtils.h>

#include <Managers/GameAgent.h>
#include <Managers/GameInterface.h>
#include <Tasks/BasicTasks/CombatTask.h>
#include <Tasks/BasicTasks/DrawTask.h>
#include <Tasks/BasicTasks/PlayCardTask.h>
#include <Tasks/BasicTasks/InitAttackCountTask.h>

#include <future>
#include <Tasks/BasicTasks/SwapPlayerTask.h>

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

    agent.RunTask(BasicTasks::DrawCardTask(
                      Cards::GetInstance()->FindCardByName("Fiery War Axe")),
                  player1, player2);
    EXPECT_EQ(agent.GetPlayer1().hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(agent.GetPlayer1().hand[0]->card->name, "Fiery War Axe");

    agent.RunTask(BasicTasks::DrawCardTask(Cards::GetInstance()->FindCardByName(
                      "Acidic Swamp Ooze")),
                  player2, player1);
    EXPECT_EQ(agent.GetPlayer2().hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(agent.GetPlayer2().hand[0]->card->name, "Acidic Swamp Ooze");

    // Create response for GameAgent to run PlayCardTask
    auto respPlayCard1 = response.PlayCard(0);
    MetaData result =
        agent.RunTask(BasicTasks::PlayCardTask(taskAgent), player1, player2);
    EXPECT_EQ(result, MetaData::PLAY_WEAPON_SUCCESS);
    EXPECT_NE(agent.GetPlayer1().hero->weapon, nullptr);

    TaskMeta reqPlayCard1 = respPlayCard1.get();
    EXPECT_EQ(reqPlayCard1.id, +TaskID::REQUIRE);
    auto require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(reqPlayCard1);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_CARD);

    // Create multiple response for PlayCardTask And PlayMinionTask
    auto respAutoMinion = response.AutoMinion(0, 0);
    result =
        agent.RunTask(BasicTasks::PlayCardTask(taskAgent), player2, player1);
    EXPECT_EQ(result, MetaData::PLAY_MINION_SUCCESS);
    EXPECT_EQ(agent.GetPlayer1().hero->weapon, nullptr);

    auto[respPlayCard2, respPlayMinion] = respAutoMinion.get();
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

    TaskAgent& taskAgent = agent.GetTaskAgent();
    TestUtils::AutoResponder response(agent);

    Player& player1 = agent.GetPlayer1();
    Player& player2 = agent.GetPlayer2();

    player1.totalMana = agent.GetPlayer1().existMana = 10;
    player2.totalMana = agent.GetPlayer2().existMana = 10;

    agent.RunTask(BasicTasks::DrawCardTask(Cards::GetInstance()->FindCardByName(
                      "Acidic Swamp Ooze")),
                  player1, player2);
    EXPECT_EQ(agent.GetPlayer1().hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(agent.GetPlayer1().hand[0]->card->name, "Acidic Swamp Ooze");

    agent.RunTask(BasicTasks::DrawCardTask(Cards::GetInstance()->FindCardByName(
                      "Ancestral Healing")),
                  player1, player2);
    EXPECT_EQ(agent.GetPlayer1().hand.size(), static_cast<size_t>(2));
    EXPECT_EQ(agent.GetPlayer1().hand[1]->card->name, "Ancestral Healing");

    agent.RunTask(BasicTasks::DrawCardTask(
                      Cards::GetInstance()->FindCardByName("Stonetusk Boar")),
                  player2, player1);
    EXPECT_EQ(agent.GetPlayer2().hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(agent.GetPlayer2().hand[0]->card->name, "Stonetusk Boar");

    // Create multiple response for PlayCardTask And PlayMinionTask
    auto respAutoMinion = response.AutoMinion(0, 0);
    MetaData result =
        agent.RunTask(BasicTasks::PlayCardTask(taskAgent), player1, player2);
    EXPECT_EQ(result, MetaData::PLAY_MINION_SUCCESS);
    EXPECT_EQ(agent.GetPlayer1().field[0]->card->name, "Acidic Swamp Ooze");

    auto[respPlayCard1, respPlayMinion1] = respAutoMinion.get();
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
    EXPECT_EQ(agent.GetPlayer2().field[0]->card->name, "Stonetusk Boar");

    auto[respPlayCard2, respPlayMinion2] = respAutoMinion.get();
    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayCard2);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_CARD);

    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayMinion2);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_POSITION);

    auto respAutoTarget = response.Target(1, 1);
    result = agent.RunTask(BasicTasks::CombatTask(taskAgent), player2, player1);
    EXPECT_EQ(result, MetaData::COMBAT_SUCCESS);
    EXPECT_EQ(agent.GetPlayer1().field[0]->health, static_cast<size_t>(1));
    EXPECT_EQ(agent.GetPlayer2().field.size(), static_cast<size_t>(0));

    // Create multiple response for PlayCardTask And PlaySpellTask
    auto respAutoSpell = response.AutoSpell(0, TargetType::MY_FIELD, 0);
    result =
        agent.RunTask(BasicTasks::PlayCardTask(taskAgent), player1, player2);
    EXPECT_EQ(result, MetaData::PLAY_SPELL_SUCCESS);

    auto[respPlayCard3, respPlaySpell] = respAutoSpell.get();
    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayCard3);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_CARD);

    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlaySpell);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_TARGET);

    EXPECT_EQ(agent.GetPlayer1().field[0]->health, static_cast<size_t>(2));
    EXPECT_EQ(agent.GetPlayer1().field[0]->gameTags[GameTag::TAUNT], 1);
}

TEST(BasicCard, CS2_171)
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

    agent.RunTask(BasicTasks::DrawCardTask(Cards::GetInstance()->FindCardByName(
                      "Acidic Swamp Ooze")),
                  player1, player2);
    EXPECT_EQ(agent.GetPlayer1().hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(agent.GetPlayer1().hand[0]->card->name, "Acidic Swamp Ooze");

    agent.RunTask(BasicTasks::DrawCardTask(
                      Cards::GetInstance()->FindCardByName("Stonetusk Boar")),
                  player2, player1);
    EXPECT_EQ(agent.GetPlayer2().hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(agent.GetPlayer2().hand[0]->card->name, "Stonetusk Boar");

    // Create multiple response for PlayCardTask And PlayMinionTask
    auto respAutoMinion = response.AutoMinion(0, 0);
    MetaData result =
        agent.RunTask(BasicTasks::PlayCardTask(taskAgent), player1, player2);
    EXPECT_EQ(result, MetaData::PLAY_MINION_SUCCESS);
    EXPECT_EQ(agent.GetPlayer1().field[0]->card->name, "Acidic Swamp Ooze");

    auto[respPlayCard1, respPlayMinion1] = respAutoMinion.get();
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
    EXPECT_EQ(agent.GetPlayer2().field[0]->card->name, "Stonetusk Boar");

    auto[respPlayCard2, respPlayMinion2] = respAutoMinion.get();
    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayCard2);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_CARD);

    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayMinion2);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_POSITION);

    auto respAutoTarget = response.Target(1, 1);
    result = agent.RunTask(BasicTasks::CombatTask(taskAgent), player2, player1);
    EXPECT_EQ(result, MetaData::COMBAT_SUCCESS);
    EXPECT_EQ(agent.GetPlayer1().field[0]->health, static_cast<size_t>(1));
    EXPECT_EQ(agent.GetPlayer2().field.size(), static_cast<size_t>(0));
}

TEST(BasicCard, EX1_170)
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

    agent.RunTask(BasicTasks::DrawCardTask(Cards::GetInstance()->FindCardByName(
                      "Emperor Cobra")),
                  player1, player2);

    agent.RunTask(BasicTasks::DrawCardTask(
                      Cards::GetInstance()->FindCardByName("Stormwind Knight")),
                  player2, player1);

    // Create multiple response for PlayCardTask And PlayMinionTask
    auto respAutoMinion = response.AutoMinion(0, 0);
    agent.RunTask(BasicTasks::PlayCardTask(taskAgent), player1, player2);

    auto[respPlayCard1, respPlayMinion1] = respAutoMinion.get();
    TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayCard1);
    TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayMinion1);

    // Create multiple response for PlayCardTask And PlayMinionTask
    respAutoMinion = response.AutoMinion(0, 0);
    agent.RunTask(BasicTasks::PlayCardTask(taskAgent), player2, player1);

    auto[respPlayCard2, respPlayMinion2] = respAutoMinion.get();
    TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayCard2);
    TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayMinion2);

    auto respAutoTarget = response.Target(1, 1);
    auto result = agent.RunTask(BasicTasks::CombatTask(taskAgent), player2, player1);
    EXPECT_EQ(result, MetaData::COMBAT_SUCCESS);
    
    EXPECT_EQ(agent.GetPlayer1().field[0]->health, static_cast<size_t>(1));
    EXPECT_EQ(agent.GetPlayer2().field.size(), static_cast<size_t>(0));
}

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

    auto[respPlayCard1, respPlayMinion1] = respAutoMinion.get();
    TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayCard1);
    TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayMinion1);

    // Create multiple response for PlayCardTask And PlayMinionTask
    respAutoMinion = response.AutoMinion(0, 0);
    agent.RunTask(BasicTasks::PlayCardTask(taskAgent), player2, player1);

    auto[respPlayCard2, respPlayMinion2] = respAutoMinion.get();
    TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayCard2);
    TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayMinion2);

    agent.RunTask(BasicTasks::InitAttackCountTask(player2), player1, player2);

    auto respAutoTarget = response.Target(1, 1);
    EXPECT_EQ(agent.GetPlayer1().field[0]->gameTags[+GameTag::DIVINE_SHIELD], 1);
    auto result = agent.RunTask(BasicTasks::CombatTask(taskAgent), player2, player1);
    EXPECT_EQ(result, MetaData::COMBAT_SUCCESS);
    EXPECT_EQ(agent.GetPlayer1().field[0]->health, agent.GetPlayer1().field[0]->maxHealth);
    EXPECT_EQ(agent.GetPlayer1().field[0]->gameTags[+GameTag::DIVINE_SHIELD], 0);
}

TEST(BasicCard, EX1_017)
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

    std::string player1Card = "Ironfur Grizzly";
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

    auto[respPlayCard1, respPlayMinion1] = respAutoMinion.get();
    TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayCard1);
    TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayMinion1);

    // Create multiple response for PlayCardTask And PlayMinionTask
    respAutoMinion = response.AutoMinion(0, 0);
    agent.RunTask(BasicTasks::PlayCardTask(taskAgent), player2, player1);

    auto[respPlayCard2, respPlayMinion2] = respAutoMinion.get();
    TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayCard2);
    TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayMinion2);

    agent.RunTask(BasicTasks::InitAttackCountTask(player2), player1, player2);

    auto respAutoTarget = response.Target(1, 0);
    auto result = agent.RunTask(BasicTasks::CombatTask(taskAgent), player2, player1);
    EXPECT_EQ(result, MetaData::COMBAT_FIELD_HAVE_TAUNT);
}

TEST(BasicCard, CS2_125)
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

    std::string player1Card = "Jungle Panther";
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

    auto[respPlayCard1, respPlayMinion1] = respAutoMinion.get();
    TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayCard1);
    TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayMinion1);

    // Create multiple response for PlayCardTask And PlayMinionTask
    respAutoMinion = response.AutoMinion(0, 0);
    agent.RunTask(BasicTasks::PlayCardTask(taskAgent), player2, player1);

    auto[respPlayCard2, respPlayMinion2] = respAutoMinion.get();
    TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayCard2);
    TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayMinion2);

    agent.RunTask(BasicTasks::InitAttackCountTask(player2), player1, player2);

    auto respAutoTarget = response.Target(1, 1);
    auto result = agent.RunTask(BasicTasks::CombatTask(taskAgent), player2, player1);
    EXPECT_EQ(result, MetaData::COMBAT_TARGET_STEALTH);
}


TEST(BasicCard, CS2_169)
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

    std::string player1Card = "Young Dragonhawk";
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

    auto[respPlayCard1, respPlayMinion1] = respAutoMinion.get();
    TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayCard1);
    TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayMinion1);

    // Create multiple response for PlayCardTask And PlayMinionTask
    respAutoMinion = response.AutoMinion(0, 0);
    agent.RunTask(BasicTasks::PlayCardTask(taskAgent), player2, player1);

    auto[respPlayCard2, respPlayMinion2] = respAutoMinion.get();
    TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayCard2);
    TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayMinion2);

    agent.RunTask(BasicTasks::InitAttackCountTask(player1), player1, player2);

    auto respAutoTarget = response.Target(1, 0);
    auto result = agent.RunTask(BasicTasks::CombatTask(taskAgent), player1, player2);
    EXPECT_EQ(result, MetaData::COMBAT_SUCCESS);

    respAutoTarget = response.Target(1, 0);
    result = agent.RunTask(BasicTasks::CombatTask(taskAgent), player1, player2);
    EXPECT_EQ(result, MetaData::COMBAT_SUCCESS);
}

TEST(BasicCard, CS2_179)
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
                      "Sen'jin Shieldmasta")),
                  player1, player2);
    EXPECT_EQ(agent.GetPlayer1().hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(agent.GetPlayer1().hand[0]->card->name, "Sen'jin Shieldmasta");

    agent.RunTask(BasicTasks::DrawCardTask(
                      Cards::GetInstance()->FindCardByName("Stonetusk Boar")),
                  player2, player1);
    EXPECT_EQ(agent.GetPlayer2().hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(agent.GetPlayer2().hand[0]->card->name, "Stonetusk Boar");

    // Create multiple response for PlayCardTask And PlayMinionTask
    auto respAutoMinion = response.AutoMinion(0, 0);
    MetaData result =
        agent.RunTask(BasicTasks::PlayCardTask(taskAgent), player1, player2);
    EXPECT_EQ(result, MetaData::PLAY_MINION_SUCCESS);
    EXPECT_EQ(agent.GetPlayer1().field[0]->card->name, "Sen'jin Shieldmasta");

    auto[respPlayCard1, respPlayMinion1] = respAutoMinion.get();
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
    EXPECT_EQ(agent.GetPlayer2().field[0]->card->name, "Stonetusk Boar");

    auto[respPlayCard2, respPlayMinion2] = respAutoMinion.get();
    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayCard2);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_CARD);

    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayMinion2);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_POSITION);
	
	// TODO: Add new test scenario for Taunt minion to interrupt opponent minions from attacking the hero.
	// CombatTask result must return FAILURE if it's targeted by opponent minion, but it's not implemented yet.

    auto respAutoTarget = response.Target(1, 1);
    result = agent.RunTask(BasicTasks::CombatTask(taskAgent), player2, player1);
    EXPECT_EQ(result, MetaData::COMBAT_SUCCESS);
    EXPECT_EQ(agent.GetPlayer1().field[0]->health, static_cast<size_t>(4));
    EXPECT_EQ(agent.GetPlayer2().field.size(), static_cast<size_t>(0));
}

TEST(BasicCard, CS2_118)
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
                      Cards::GetInstance()->FindCardByName("Magma Rager")),
                  player1, player2);
    EXPECT_EQ(agent.GetPlayer1().hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(agent.GetPlayer1().hand[0]->card->name, "Magma Rager");

    agent.RunTask(BasicTasks::DrawCardTask(
                      Cards::GetInstance()->FindCardByName("Stonetusk Boar")),
                  player2, player1);
    EXPECT_EQ(agent.GetPlayer2().hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(agent.GetPlayer2().hand[0]->card->name, "Stonetusk Boar");

    // Create multiple response for PlayCardTask And PlayMinionTask
    auto respAutoMinion = response.AutoMinion(0, 0);
    MetaData result =
        agent.RunTask(BasicTasks::PlayCardTask(taskAgent), player1, player2);
    EXPECT_EQ(result, MetaData::PLAY_MINION_SUCCESS);
    EXPECT_EQ(agent.GetPlayer1().field[0]->card->name, "Magma Rager");

    auto[respPlayCard1, respPlayMinion1] = respAutoMinion.get();
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
    EXPECT_EQ(agent.GetPlayer2().field[0]->card->name, "Stonetusk Boar");

    auto[respPlayCard2, respPlayMinion2] = respAutoMinion.get();
    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayCard2);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_CARD);

    require = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(respPlayMinion2);
    EXPECT_EQ(TaskID::_from_integral(require->required()),
              +TaskID::SELECT_POSITION);

    auto respAutoTarget = response.Target(1, 1);
    result = agent.RunTask(BasicTasks::CombatTask(taskAgent), player2, player1);
    EXPECT_EQ(result, MetaData::COMBAT_SUCCESS);
    EXPECT_EQ(agent.GetPlayer1().field.size(), static_cast<size_t>(0));
    EXPECT_EQ(agent.GetPlayer2().field.size(), static_cast<size_t>(0));
}