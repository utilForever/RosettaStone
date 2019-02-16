// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"

#include <hspp/Cards/Cards.hpp>
#include <hspp/Models/Game.hpp>
#include <hspp/Policies/BasicPolicy.hpp>
#include <hspp/Tasks/SimpleTasks/DrawCardTask.hpp>

using namespace Hearthstonepp;
using namespace SimpleTasks;

TEST(DrawCardTask, GetTaskID)
{
    const Card card{};
    const DrawCardTask draw(card);

    EXPECT_EQ(draw.GetTaskID(), +TaskID::DRAW);
}

TEST(DrawCardTask, Run)
{
    Cards& instance = Cards::GetInstance();
    Game game(CardClass::ROGUE, CardClass::DRUID, PlayerType::PLAYER1);

    Card nerubian = instance.FindCardByID("AT_036t");
    EXPECT_NE(nerubian.id, "");
    EXPECT_EQ(nerubian.name, "Nerubian");

    Card poisonedBlade = instance.FindCardByID("AT_034");
    EXPECT_NE(poisonedBlade.id, "");
    EXPECT_EQ(poisonedBlade.name, "Poisoned Blade");

    auto minionNerubian = new Minion(game.GetPlayer1(), nerubian);
    auto weaponPoisonedBlade = new Weapon(game.GetPlayer1(), poisonedBlade);
    // game.GetPlayer1().GetDeck().emplace_back(weaponPoisonedBlade);
    // game.GetPlayer1().GetDeck().emplace_back(minionNerubian);

    DrawCardTask drawNerubian(nerubian);
    TaskStatus result = drawNerubian.Run(game.GetPlayer1());

    EXPECT_EQ(result, TaskStatus::DRAW_SUCCESS);
    EXPECT_EQ(game.GetPlayer1().GetHand().GetNumOfCards(), 1u);
    EXPECT_EQ(game.GetPlayer1().GetHand().GetCard(0)->card.id, nerubian.id);
    EXPECT_EQ(game.GetPlayer1().GetDeck().GetNumOfCards(), 1u);
    // EXPECT_EQ(game.GetPlayer1().GetDeck()[0]->card->id, poisonedBlade.id);

    DrawCardTask drawPoisonedBlade(poisonedBlade);
    result = drawPoisonedBlade.Run(game.GetPlayer1());

    EXPECT_EQ(result, TaskStatus::DRAW_SUCCESS);
    EXPECT_EQ(game.GetPlayer1().GetHand().GetNumOfCards(), 2u);
    EXPECT_EQ(game.GetPlayer1().GetHand().GetCard(1)->card.id,
              poisonedBlade.id);
    EXPECT_EQ(game.GetPlayer1().GetDeck().GetNumOfCards(), 0u);

    delete minionNerubian;
    delete weaponPoisonedBlade;
}