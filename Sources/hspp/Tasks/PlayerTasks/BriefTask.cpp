// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Tasks/PlayerTasks/BriefTask.hpp>

namespace Hearthstonepp::PlayerTasks
{
TaskID BriefTask::GetTaskID() const
{
    return TaskID::BRIEF;
}

MetaData BriefTask::Impl(Player&)
{
    return MetaData::BRIEF;
}
}  // namespace Hearthstonepp::PlayerTasks