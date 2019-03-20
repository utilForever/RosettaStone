// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Tasks/PlayerTasks/EndTurnTask.hpp>

namespace Hearthstonepp::PlayerTasks
{
TaskID EndTurnTask::GetTaskID() const
{
    return TaskID::END_TURN;
}

TaskStatus EndTurnTask::Impl(Player& player)
{
    player.GetGame()->step = Step::MAIN_END;
    player.GetGame()->MainEnd();

    return TaskStatus::COMPLETE;
}
}  // namespace Hearthstonepp::PlayerTasks