// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Games/Game.hpp>
#include <hspp/Models/Player.hpp>
#include <hspp/Tasks/PlayerTasks/EndTurnTask.hpp>

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