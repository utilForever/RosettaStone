// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Tasks/SimpleTasks/ShuffleTask.hpp>

#include <random>

namespace Hearthstonepp::SimpleTasks
{
TaskID ShuffleTask::GetTaskID() const
{
    return TaskID::SHUFFLE;
}

TaskStatus ShuffleTask::Impl(Player& player)
{
    std::random_device rd;
    std::default_random_engine gen(rd());

    std::shuffle(player.GetDeck().begin(), player.GetDeck().end(), gen);

    return TaskStatus::SHUFFLE_SUCCESS;
}
}  // namespace Hearthstonepp::SimpleTasks