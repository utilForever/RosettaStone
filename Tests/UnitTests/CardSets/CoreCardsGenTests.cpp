// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/CardSetUtils.hpp>

#include <hspp/Actions/Draw.hpp>
#include <hspp/Cards/Cards.hpp>

using namespace Hearthstonepp;
using namespace PlayerTasks;
using namespace SimpleTasks;

TEST(CoreCardsGen, EX1_066)
{
    Game game(CardClass::WARRIOR, CardClass::ROGUE, PlayerType::PLAYER1);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetCurrentPlayer().GetOpponent();
    curPlayer.SetMaximumMana(10);
    curPlayer.SetAvailableMana(10);
    opPlayer.SetMaximumMana(10);
    opPlayer.SetAvailableMana(10);

    const auto card1 = Generic::DrawCard(
        curPlayer, Cards::GetInstance().FindCardByName("Fiery War Axe"));
    const auto card2 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Acidic Swamp Ooze"));

    Task::Run(curPlayer, PlayCardTask(card1));
    EXPECT_EQ(curPlayer.GetHero()->HasWeapon(), true);

    Task::Run(opPlayer, PlayCardTask(card2));
    EXPECT_EQ(curPlayer.GetHero()->HasWeapon(), false);
}

TEST(CoreCardsGen, EX1_306)
{
    Game game(CardClass::WARLOCK, CardClass::WARRIOR, PlayerType::PLAYER1);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetCurrentPlayer().GetOpponent();
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

    Task::Run(curPlayer, PlayCardTask(card1));
    EXPECT_EQ(curPlayer.GetHand().GetNumOfCards(), 0u);

    Task::Run(opPlayer, PlayCardTask(card2));
    EXPECT_EQ(opPlayer.GetHand().GetNumOfCards(), 1u);
}

TEST(CoreCardsGen, CS2_041)
{
    Game game(CardClass::SHAMAN, CardClass::ROGUE, PlayerType::PLAYER1);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetCurrentPlayer().GetOpponent();
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

    Task::Run(curPlayer, PlayCardTask(card1));
    Task::Run(opPlayer, PlayCardTask(card3));

    Task::Run(opPlayer, CombatTask(card3, card1));
    EXPECT_EQ(curField.GetMinion(0)->health, 1);
    EXPECT_EQ(opField.GetNumOfMinions(), 0u);

    Task::Run(curPlayer, PlayCardTask(card2, -1, card1));
    EXPECT_EQ(curField.GetMinion(0)->health, 2);
    EXPECT_EQ(curField.GetMinion(0)->GetGameTag(GameTag::TAUNT), 1);
}

TEST(CoreCardsGen, CS2_088)
{
    Game game(CardClass::DRUID, CardClass::PALADIN, PlayerType::PLAYER1);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetCurrentPlayer().GetOpponent();
    curPlayer.SetMaximumMana(10);
    curPlayer.SetAvailableMana(10);
    opPlayer.SetMaximumMana(10);
    opPlayer.SetAvailableMana(10);
    opPlayer.GetHero()->health = 24;

    const auto card1 = Generic::DrawCard(
        opPlayer, Cards::GetInstance().FindCardByName("Guardian of Kings"));

    Task::Run(opPlayer, PlayCardTask(card1));
    EXPECT_EQ(opPlayer.GetHero()->maxHealth, opPlayer.GetHero()->health);
}

TEST(CoreCardsGen, CS1_112)
{
    Game game(CardClass::PRIEST, CardClass::PALADIN, PlayerType::PLAYER1);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetCurrentPlayer().GetOpponent();
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

    Task::Run(curPlayer, PlayCardTask(card1));
    curPlayer.SetAvailableMana(10);
    Task::Run(curPlayer, PlayCardTask(card2));
    curPlayer.SetAvailableMana(10);
    Task::Run(opPlayer, PlayCardTask(card4));
    Task::Run(opPlayer, PlayCardTask(card5));

    Task::Run(curPlayer, InitAttackCountTask());

    Task::Run(curPlayer, CombatTask(card1, card4));
    EXPECT_EQ(curField.GetMinion(0)->health, 4);
    EXPECT_EQ(opField.GetMinion(0)->GetGameTag(GameTag::DIVINE_SHIELD), 0);

    Task::Run(curPlayer, PlayCardTask(card3));
    EXPECT_EQ(curPlayer.GetHero()->health, 28);
    EXPECT_EQ(opPlayer.GetHero()->health, 28);
    EXPECT_EQ(curField.GetMinion(0)->health, 5);
    EXPECT_EQ(curField.GetMinion(1)->health, 7);
    EXPECT_EQ(opField.GetNumOfMinions(), 0u);
}

TEST(CoreCardsGen, CS1_113)
{
    Game game(CardClass::PRIEST, CardClass::PALADIN, PlayerType::PLAYER1);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& opPlayer = game.GetCurrentPlayer().GetOpponent();
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

    Task::Run(curPlayer, PlayCardTask(card1));
    curPlayer.SetAvailableMana(10);
    Task::Run(opPlayer, PlayCardTask(card2));
    EXPECT_EQ(curField.GetNumOfMinions(), 1u);
    EXPECT_EQ(opField.GetNumOfMinions(), 1u);

    Task::Run(curPlayer, PlayCardTask(card3, -1, card2));
    EXPECT_EQ(curField.GetNumOfMinions(), 2u);
    EXPECT_EQ(opField.GetNumOfMinions(), 0u);

    opPlayer.SetAvailableMana(10);
    auto result =
        Task::Run(opPlayer, PlayCardTask(card4, -1, curPlayer.GetHero()));
    EXPECT_EQ(result, TaskStatus::PLAY_CARD_INVALID_TARGET);
}