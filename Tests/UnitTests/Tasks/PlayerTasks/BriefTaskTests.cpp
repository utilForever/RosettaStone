// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"

#include <hspp/Models/Game.hpp>
#include <hspp/Tasks/PlayerTasks/BriefTask.hpp>

using namespace Hearthstonepp;
using namespace PlayerTasks;

TEST(BriefTask, GetTaskID)
{
    const BriefTask brief;
    EXPECT_EQ(brief.GetTaskID(), +TaskID::BRIEF);
}

TEST(BriefTask, Run)
{
    BriefTask brief;
    Game game(CardClass::ROGUE, CardClass::DRUID, PlayerType::PLAYER1);

    game.GetPlayer1().SetID(100);

    TaskStatus result = brief.Run(game.GetPlayer1());
    EXPECT_EQ(result, TaskStatus::BRIEF);
}
