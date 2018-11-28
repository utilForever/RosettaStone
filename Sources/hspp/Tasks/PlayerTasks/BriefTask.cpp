// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

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