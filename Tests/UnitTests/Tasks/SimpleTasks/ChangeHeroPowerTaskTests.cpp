// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/ChangeHeroPowerTask.hpp>

using namespace RosettaStone;
using namespace SimpleTasks;

TEST(ChangeHeroPowerTask, Run)
{
    GameConfig config;
    config.startPlayer = PlayerType::PLAYER1;
    config.player1Class = CardClass::PRIEST;
    Game game(config);

    Hero& hero = *game.GetPlayer1()->GetHero();

    hero.heroPower->SetExhausted(true);
    EXPECT_EQ(hero.heroPower->card->id,
              Cards::GetDefaultHeroPower(CardClass::PRIEST)->id);
    EXPECT_TRUE(hero.heroPower->IsExhausted());

    ChangeHeroPowerTask change(Cards::GetDefaultHeroPower(CardClass::MAGE)->id);
    change.SetPlayer(game.GetPlayer1());

    TaskStatus result = change.Run();
    EXPECT_EQ(result, TaskStatus::COMPLETE);
    EXPECT_EQ(hero.heroPower->card->id,
              Cards::GetDefaultHeroPower(CardClass::MAGE)->id);
    EXPECT_FALSE(hero.heroPower->IsExhausted());
}