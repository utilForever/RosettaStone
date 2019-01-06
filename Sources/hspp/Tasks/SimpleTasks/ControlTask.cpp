// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/SimpleTasks/ControlTask.hpp>
#include <hspp/Tasks/SimpleTasks/IncludeTask.hpp>

namespace Hearthstonepp::SimpleTasks
{
ControlTask::ControlTask(EntityType entityType) : ITask(entityType)
{
    // Do nothing
}

TaskID ControlTask::GetTaskID() const
{
    return TaskID::CONTROL;
}

MetaData ControlTask::Impl(Player& player)
{
    auto entities = IncludeTask::GetEntities(m_entityType, player, m_target);
    auto& myField = player.GetField();
    auto& opField = player.GetOpponent().GetField();

    if (myField.GetNumOfMinions() == FIELD_SIZE)
    {
        return MetaData::CONTROL_FIELD_IS_FULL;
    }

    for (auto& entity : entities)
    {
        auto fieldIter = std::find(opField.begin(), opField.end(), entity);
        if (fieldIter == opField.end())
        {
            return MetaData::CONTROL_INVALID_TARGET;
        }

        myField.emplace_back(*fieldIter);
        opField.erase(fieldIter);
    }

    return MetaData::CONTROL_SUCCESS;
}
}  // namespace Hearthstonepp::SimpleTasks
