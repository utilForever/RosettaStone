// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/Models/Player.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/TradeCardTask.hpp>

namespace RosettaStone::PlayMode::PlayerTasks
{
TaskStatus TradeCardTask::Impl(Player* player)
{
    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> TradeCardTask::CloneImpl()
{
    return std::make_unique<TradeCardTask>();
}
}  // namespace RosettaStone::PlayMode::PlayerTasks
