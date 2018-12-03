// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/SimpleTasks/ControlTask.hpp>
#include <hspp/Tasks/SimpleTasks/IncludeTask.hpp>

namespace Hearthstonepp::SimpleTasks
{
ControlTask::ControlTask(EntityType entityType)
    : ITask(entityType)
{
    // Do nothing
}

TaskID ControlTask::GetTaskID() const
{
    return TaskID::CONTROL;
}

MetaData ControlTask::Impl(Player& player)
{
    auto entities = IncludeTask::GetEntities(m_entityType, player);

    for (auto& entity : entities)
    {
        (void)entity;
    }

    return MetaData::CONTROL_SUCCESS;
}
}  // namespace Hearthstonepp::SimpleTasks
