// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Tasks/PlayerTasks/ChooseTask.hpp>

namespace Hearthstonepp::PlayerTasks
{
TaskID ChooseTask::GetTaskID() const
{
    return TaskID::CHOOSE;
}

ChooseTask::ChooseTask(std::vector<std::size_t> choices) : m_choices(choices)
{
    // Do nothing
}

TaskStatus ChooseTask::Impl(Player& player)
{
    (void)player;

    return TaskStatus::COMPLETE;
}
}  // namespace Hearthstonepp::PlayerTasks