// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone
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

void ITask::SetPlayer(Player* player)
{
    m_player = player;
}

void ITask::SetSource(Entity* source)
{
    m_source = source;
}

void ITask::SetTarget(Entity* target)
{
    m_target = target;
}

TaskStatus ITask::Run()
{
    return Impl(*m_player);
}

ITask* ITask::Clone()
{
    ITask* clonedTask = CloneImpl();
    clonedTask->SetFreeable();

    clonedTask->m_entityType = m_entityType;
    clonedTask->m_player = m_player;
    clonedTask->m_source = m_source;
    clonedTask->m_target = m_target;

    return clonedTask;
}

bool ITask::IsFreeable() const
{
    return m_isFreeable;
}

void ITask::SetFreeable()
{
    m_isFreeable = true;
}

}  // namespace RosettaStone
