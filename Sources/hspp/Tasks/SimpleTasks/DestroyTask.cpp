// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Tasks/SimpleTasks/DestroyTask.hpp>
#include <hspp/Tasks/SimpleTasks/IncludeTask.hpp>

namespace Hearthstonepp::SimpleTasks
{
DestroyTask::DestroyTask(EntityType entityType) : ITask(entityType)
{
    // Do nothing
}

TaskID DestroyTask::GetTaskID() const
{
    return TaskID::DESTROY;
}

MetaData DestroyTask::Impl(Player& player)
{
    auto entities =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& entity : entities)
    {
        entity->Destroy();
    }

    return MetaData::DESTROY_SUCCESS;
}
}  // namespace Hearthstonepp::SimpleTasks