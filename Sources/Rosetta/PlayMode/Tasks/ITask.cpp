// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode
{
ITask::ITask(EntityType entityType) : m_entityType(entityType)
{
    // Do nothing
}

ITask::ITask(Entity* source, Playable* target)
    : m_source(source), m_target(target)
{
    // Do nothing
}

ITask::ITask(EntityType entityType, Entity* source, Playable* target)
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

void ITask::SetTarget(Playable* target)
{
    m_target = target;
}

TaskStatus ITask::Run()
{
    return Impl(m_player);
}

std::unique_ptr<ITask> ITask::Clone()
{
    std::unique_ptr<ITask> clonedTask = CloneImpl();

    clonedTask->m_entityType = m_entityType;
    clonedTask->m_player = m_player;
    clonedTask->m_source = m_source;
    clonedTask->m_target = m_target;

    return clonedTask;
}
}  // namespace RosettaStone::PlayMode
