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

    Player& curPlayer = agent.GetCurrentPlayer();
    Player& opPlayer = agent.GetCurrentPlayer().GetOpponent();
    curPlayer.SetMaximumMana(10);
    curPlayer.SetAvailableMana(10);
    opPlayer.SetMaximumMana(10);
    opPlayer.SetAvailableMana(10);

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Fiery War Axe"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));

    GameAgent::RunTask(curPlayer, PlayCardTask(taskAgent, card1));
    EXPECT_EQ(curPlayer.GetHero()->HasWeapon(), true);

    GameAgent::RunTask(opPlayer, PlayCardTask(taskAgent, card2));
    EXPECT_EQ(curPlayer.GetHero()->HasWeapon(), false);
}

TEST(CoreCardsGen, EX1_306)
{
    GameAgent agent(CardClass::WARLOCK, CardClass::WARRIOR,
                    PlayerType::PLAYER1);
    TaskAgent& taskAgent = agent.GetTaskAgent();

    Player& curPlayer = agent.GetCurrentPlayer();
    Player& opPlayer = agent.GetCurrentPlayer().GetOpponent();
    curPlayer.SetMaximumMana(10);
    curPlayer.SetAvailableMana(10);
    opPlayer.SetMaximumMana(10);
    opPlayer.SetAvailableMana(10);

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Succubus"));
    Generic::DrawCard(curPlayer,
                      Cards::GetInstance().FindCardByName("Stonetusk Boar"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));
    Generic::DrawCard(opPlayer,
                      Cards::GetInstance().FindCardByName("Fiery War Axe"));

    GameAgent::RunTask(curPlayer, PlayCardTask(taskAgent, card1));
    EXPECT_EQ(curPlayer.GetHand().size(), 0u);

    GameAgent::RunTask(opPlayer, PlayCardTask(taskAgent, card2));
    EXPECT_EQ(opPlayer.GetHand().size(), 1u);
}

TEST(CoreCardsGen, CS2_041)
{
    GameAgent agent(CardClass::SHAMAN, CardClass::ROGUE, PlayerType::PLAYER1);
    TaskAgent& taskAgent = agent.GetTaskAgent();

    Player& curPlayer = agent.GetCurrentPlayer();
    Player& opPlayer = agent.GetCurrentPlayer().GetOpponent();
    curPlayer.SetMaximumMana(10);
    curPlayer.SetAvailableMana(10);
    opPlayer.SetMaximumMana(10);
    opPlayer.SetAvailableMana(10);

    auto& curField = curPlayer.GetField();
    const auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Ancestral Healing"));
    const auto card3 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Stonetusk Boar"));

    GameAgent::RunTask(curPlayer, PlayCardTask(taskAgent, card1));
    GameAgent::RunTask(opPlayer, PlayCardTask(taskAgent, card3));

    GameAgent::RunTask(opPlayer, CombatTask(taskAgent, card3, card1));
    EXPECT_EQ(curField.GetMinion(0)->health, 1);
    EXPECT_EQ(opField.GetNumOfMinions(), 0u);

    GameAgent::RunTask(curPlayer, PlayCardTask(taskAgent, card2, -1, card1));
    EXPECT_EQ(curField.GetMinion(0)->health, 2);
    EXPECT_EQ(curField.GetMinion(0)->GetGameTag(GameTag::TAUNT), 1);
}

TEST(CoreCardsGen, CS2_088)
{
    GameAgent agent(CardClass::DRUID, CardClass::PALADIN, PlayerType::PLAYER1);
    TaskAgent& taskAgent = agent.GetTaskAgent();

    Player& curPlayer = agent.GetCurrentPlayer();
    Player& opPlayer = agent.GetCurrentPlayer().GetOpponent();
    curPlayer.SetMaximumMana(10);
    curPlayer.SetAvailableMana(10);
    opPlayer.SetMaximumMana(10);
    opPlayer.SetAvailableMana(10);
    opPlayer.GetHero()->health = 24;

    const auto card1 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Guardian of Kings"));

    GameAgent::RunTask(opPlayer, PlayCardTask(taskAgent, card1));
    EXPECT_EQ(opPlayer.GetHero()->maxHealth, opPlayer.GetHero()->health);
}

TEST(CoreCardsGen, CS1_112)
{
    GameAgent agent(CardClass::PRIEST, CardClass::PALADIN, PlayerType::PLAYER1);
    TaskAgent& taskAgent = agent.GetTaskAgent();

    Player& curPlayer = agent.GetCurrentPlayer();
    Player& opPlayer = agent.GetCurrentPlayer().GetOpponent();
    curPlayer.SetMaximumMana(10);
    curPlayer.SetAvailableMana(10);
    opPlayer.SetMaximumMana(10);
    opPlayer.SetAvailableMana(10);
    curPlayer.GetHero()->health = 26;

    auto& curField = curPlayer.GetField();
    auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Windfury Harpy"));
    const auto card2 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Holy Nova"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Argent Squire"));
    const auto card5 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Worgen Infiltrator"));

    GameAgent::RunTask(curPlayer, PlayCardTask(taskAgent, card1));
    curPlayer.SetAvailableMana(10);
    GameAgent::RunTask(curPlayer, PlayCardTask(taskAgent, card2));
    curPlayer.SetAvailableMana(10);
    GameAgent::RunTask(opPlayer, PlayCardTask(taskAgent, card4));
    GameAgent::RunTask(opPlayer, PlayCardTask(taskAgent, card5));

    GameAgent::RunTask(curPlayer, InitAttackCountTask());

    GameAgent::RunTask(curPlayer, CombatTask(taskAgent, card1, card4));
    EXPECT_EQ(curField.GetMinion(0)->health, 4);
    EXPECT_EQ(opField.GetMinion(0)->GetGameTag(GameTag::DIVINE_SHIELD), 0);

    GameAgent::RunTask(curPlayer, PlayCardTask(taskAgent, card3));
    EXPECT_EQ(curPlayer.GetHero()->health, 28);
    EXPECT_EQ(opPlayer.GetHero()->health, 28);
    EXPECT_EQ(curField.GetMinion(0)->health, 5);
    EXPECT_EQ(curField.GetMinion(1)->health, 7);
    EXPECT_EQ(opField.GetNumOfMinions(), 0u);
}

TEST(CoreCardsGen, CS1_113)
{
    GameAgent agent(CardClass::PRIEST, CardClass::PALADIN, PlayerType::PLAYER1);
    TaskAgent& taskAgent = agent.GetTaskAgent();

    Player& curPlayer = agent.GetCurrentPlayer();
    Player& opPlayer = agent.GetCurrentPlayer().GetOpponent();
    curPlayer.SetMaximumMana(10);
    curPlayer.SetAvailableMana(10);
    opPlayer.SetMaximumMana(10);
    opPlayer.SetAvailableMana(10);

    const auto& curField = curPlayer.GetField();
    const auto& opField = opPlayer.GetField();

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Windfury Harpy"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Boulderfist Ogre"));
    const auto card3 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Mind Control"));
    const auto card4 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Mind Control"));

    GameAgent::RunTask(curPlayer, PlayCardTask(taskAgent, card1));
    curPlayer.SetAvailableMana(10);
    GameAgent::RunTask(opPlayer, PlayCardTask(taskAgent, card2));
    EXPECT_EQ(curField.GetNumOfMinions(), 1u);
    EXPECT_EQ(opField.GetNumOfMinions(), 1u);

    GameAgent::RunTask(curPlayer, PlayCardTask(taskAgent, card3, -1, card2));
    EXPECT_EQ(curField.GetNumOfMinions(), 2u);
    EXPECT_EQ(opField.GetNumOfMinions(), 0u);

    opPlayer.SetAvailableMana(10);
    auto result = GameAgent::RunTask(
        opPlayer, PlayCardTask(taskAgent, card4, -1, curPlayer.GetHero()));
    EXPECT_EQ(result, MetaData::PLAY_CARD_INVALID_TARGET);
}