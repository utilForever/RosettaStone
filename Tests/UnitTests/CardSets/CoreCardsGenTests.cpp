// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.hpp>

#include <hspp/Actions/Generic.hpp>
#include <hspp/Cards/Cards.hpp>

using namespace Hearthstonepp;
using namespace PlayerTasks;
using namespace SimpleTasks;

TEST(CoreCardsGen, EX1_066)
{
    GameAgent agent(CardClass::WARRIOR, CardClass::ROGUE, PlayerType::PLAYER1);
    TaskAgent& taskAgent = agent.GetTaskAgent();

    Player& currentPlayer = agent.GetCurrentPlayer();
    Player& opponentPlayer = agent.GetCurrentPlayer().GetOpponent();
    currentPlayer.SetMaximumMana(10);
    currentPlayer.SetAvailableMana(10);
    opponentPlayer.SetMaximumMana(10);
    opponentPlayer.SetAvailableMana(10);

    const auto card1 = Generic::DrawCard(
        currentPlayer, Cards::GetInstance().FindCardByName("Fiery War Axe"));
    const auto card2 = Generic::DrawCard(
        opponentPlayer,
        Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));

    GameAgent::RunTask(currentPlayer, PlayCardTask(taskAgent, card1));
    EXPECT_EQ(currentPlayer.GetHero()->HasWeapon(), true);

    GameAgent::RunTask(opponentPlayer, PlayCardTask(taskAgent, card2));
    EXPECT_EQ(currentPlayer.GetHero()->HasWeapon(), false);
}

TEST(CoreCardsGen, EX1_306)
{
    GameAgent agent(CardClass::WARLOCK, CardClass::WARRIOR,
                    PlayerType::PLAYER1);
    TaskAgent& taskAgent = agent.GetTaskAgent();

    Player& currentPlayer = agent.GetCurrentPlayer();
    Player& opponentPlayer = agent.GetCurrentPlayer().GetOpponent();
    currentPlayer.SetMaximumMana(10);
    currentPlayer.SetAvailableMana(10);
    opponentPlayer.SetMaximumMana(10);
    opponentPlayer.SetAvailableMana(10);

    const auto card1 = Generic::DrawCard(
        currentPlayer, Cards::GetInstance().FindCardByName("Succubus"));
    Generic::DrawCard(currentPlayer,
                      Cards::GetInstance().FindCardByName("Stonetusk Boar"));
    const auto card2 = Generic::DrawCard(
        opponentPlayer,
        Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));
    Generic::DrawCard(opponentPlayer,
                      Cards::GetInstance().FindCardByName("Fiery War Axe"));

    GameAgent::RunTask(currentPlayer, PlayCardTask(taskAgent, card1));
    EXPECT_EQ(currentPlayer.GetHand().size(), 0u);

    GameAgent::RunTask(opponentPlayer, PlayCardTask(taskAgent, card2));
    EXPECT_EQ(opponentPlayer.GetHand().size(), 1u);
}

TEST(CoreCardsGen, CS2_041)
{
    GameAgent agent(CardClass::SHAMAN, CardClass::ROGUE, PlayerType::PLAYER1);
    TaskAgent& taskAgent = agent.GetTaskAgent();

    Player& currentPlayer = agent.GetCurrentPlayer();
    Player& opponentPlayer = agent.GetCurrentPlayer().GetOpponent();
    currentPlayer.SetMaximumMana(10);
    currentPlayer.SetAvailableMana(10);
    opponentPlayer.SetMaximumMana(10);
    opponentPlayer.SetAvailableMana(10);

    const auto card1 = Generic::DrawCard(
        currentPlayer,
        Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));
    const auto card2 = Generic::DrawCard(
        currentPlayer,
        Cards::GetInstance().FindCardByName("Ancestral Healing"));
    const auto card3 = Generic::DrawCard(
        opponentPlayer, Cards::GetInstance().FindCardByName("Stonetusk Boar"));

    GameAgent::RunTask(currentPlayer, PlayCardTask(taskAgent, card1));
    GameAgent::RunTask(opponentPlayer, PlayCardTask(taskAgent, card3));

    GameAgent::RunTask(opponentPlayer, CombatTask(taskAgent, card3, card1));
    EXPECT_EQ(currentPlayer.GetField()[0]->health, 1);
    EXPECT_EQ(opponentPlayer.GetField().size(), 0u);

    GameAgent::RunTask(currentPlayer,
                       PlayCardTask(taskAgent, card2, -1, card1));
    EXPECT_EQ(currentPlayer.GetField()[0]->health, 2);
    EXPECT_EQ(currentPlayer.GetField()[0]->GetGameTag(GameTag::TAUNT), 1);
}

TEST(CoreCardsGen, CS2_088)
{
    GameAgent agent(CardClass::DRUID, CardClass::PALADIN, PlayerType::PLAYER1);
    TaskAgent& taskAgent = agent.GetTaskAgent();

    Player& currentPlayer = agent.GetCurrentPlayer();
    Player& opponentPlayer = agent.GetCurrentPlayer().GetOpponent();
    currentPlayer.SetMaximumMana(10);
    currentPlayer.SetAvailableMana(10);
    opponentPlayer.SetMaximumMana(10);
    opponentPlayer.SetAvailableMana(10);
    opponentPlayer.GetHero()->health = 24;

    const auto card1 = Generic::DrawCard(
        opponentPlayer,
        Cards::GetInstance().FindCardByName("Guardian of Kings"));

    GameAgent::RunTask(opponentPlayer, PlayCardTask(taskAgent, card1));
    EXPECT_EQ(opponentPlayer.GetHero()->maxHealth,
              opponentPlayer.GetHero()->health);
}

TEST(CoreCardsGen, CS1_112)
{
    GameAgent agent(CardClass::PRIEST, CardClass::PALADIN, PlayerType::PLAYER1);
    TaskAgent& taskAgent = agent.GetTaskAgent();

    Player& currentPlayer = agent.GetCurrentPlayer();
    Player& opponentPlayer = agent.GetCurrentPlayer().GetOpponent();
    currentPlayer.SetMaximumMana(10);
    currentPlayer.SetAvailableMana(10);
    opponentPlayer.SetMaximumMana(10);
    opponentPlayer.SetAvailableMana(10);
    currentPlayer.GetHero()->health = 26;

    const auto card1 = Generic::DrawCard(
        currentPlayer, Cards::GetInstance().FindCardByName("Windfury Harpy"));
    const auto card2 = Generic::DrawCard(
        currentPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card3 = Generic::DrawCard(
        currentPlayer, Cards::GetInstance().FindCardByName("Holy Nova"));
    const auto card4 = Generic::DrawCard(
        opponentPlayer, Cards::GetInstance().FindCardByName("Argent Squire"));
    const auto card5 = Generic::DrawCard(
        opponentPlayer,
        Cards::GetInstance().FindCardByName("Worgen Infiltrator"));

    GameAgent::RunTask(currentPlayer, PlayCardTask(taskAgent, card1));
    currentPlayer.SetAvailableMana(10);
    GameAgent::RunTask(currentPlayer, PlayCardTask(taskAgent, card2));
    currentPlayer.SetAvailableMana(10);
    GameAgent::RunTask(opponentPlayer, PlayCardTask(taskAgent, card4));
    GameAgent::RunTask(opponentPlayer, PlayCardTask(taskAgent, card5));

    GameAgent::RunTask(currentPlayer, InitAttackCountTask());

    GameAgent::RunTask(currentPlayer, CombatTask(taskAgent, card1, card4));
    EXPECT_EQ(currentPlayer.GetField()[0]->health, 4);
    EXPECT_EQ(opponentPlayer.GetField()[0]->GetGameTag(GameTag::DIVINE_SHIELD),
              0);

    GameAgent::RunTask(currentPlayer, PlayCardTask(taskAgent, card3));
    EXPECT_EQ(currentPlayer.GetHero()->health, 28);
    EXPECT_EQ(opponentPlayer.GetHero()->health, 28);
    EXPECT_EQ(currentPlayer.GetField()[0]->health, 5);
    EXPECT_EQ(currentPlayer.GetField()[1]->health, 7);
    EXPECT_EQ(opponentPlayer.GetField().size(), 0u);
}

TEST(CoreCardsGen, CS1_113)
{
    GameAgent agent(CardClass::PRIEST, CardClass::PALADIN, PlayerType::PLAYER1);
    TaskAgent& taskAgent = agent.GetTaskAgent();

    Player& currentPlayer = agent.GetCurrentPlayer();
    Player& opponentPlayer = agent.GetCurrentPlayer().GetOpponent();
    currentPlayer.SetMaximumMana(10);
    currentPlayer.SetAvailableMana(10);
    opponentPlayer.SetMaximumMana(10);
    opponentPlayer.SetAvailableMana(10);

    const auto card1 = Generic::DrawCard(
        currentPlayer, Cards::GetInstance().FindCardByName("Windfury Harpy"));
    const auto card2 = Generic::DrawCard(
        opponentPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card3 = Generic::DrawCard(
        currentPlayer, Cards::GetInstance().FindCardByName("Mind Control"));

    GameAgent::RunTask(currentPlayer, PlayCardTask(taskAgent, card1));
    currentPlayer.SetAvailableMana(10);
    GameAgent::RunTask(opponentPlayer, PlayCardTask(taskAgent, card2));
    EXPECT_EQ(currentPlayer.GetField().size(), 1u);
    EXPECT_EQ(opponentPlayer.GetField().size(), 1u);

    GameAgent::RunTask(currentPlayer, PlayCardTask(taskAgent, card3, -1, card2));
    EXPECT_EQ(currentPlayer.GetField().size(), 2u);
    EXPECT_EQ(opponentPlayer.GetField().size(), 0u);
}