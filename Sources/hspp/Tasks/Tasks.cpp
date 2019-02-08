// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/Tasks.hpp>

namespace Hearthstonepp
{
ITask::ITask(EntityType entityType) : m_entityType(entityType)
{
    // Do nothing
}

ITask::ITask(Entity* source, Entity* target)
    : m_source(source), m_target(target)
{
    // Do nothing
}

ITask::ITask(EntityType entityType, Entity* source, Entity* target)
    : m_entityType(entityType), m_source(source), m_target(target)
{
    // Do nothing
}

EntityType ITask::GetEntityType() const
{
    return m_entityType;
}

void ITask::SetSource(Entity* source)
{
    m_source = source;
}

void ITask::SetTarget(Entity* target)
{
    m_target = target;
}

TaskStatus ITask::Run(Player& player)
{
    return Impl(player);
}
}  // namespace Hearthstonepp