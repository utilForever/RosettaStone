// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/FilterStackTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>

#include <utility>

namespace RosettaStone::SimpleTasks
{
FilterStackTask::FilterStackTask(SelfCondition selfCondition)
    : m_selfCondition(new SelfCondition(std::move(selfCondition)))
{
    // Do nothing
}

FilterStackTask::FilterStackTask(EntityType type, RelaCondition relaCondition)
    : ITask(type), m_relaCondition(new RelaCondition(std::move(relaCondition)))
{
    // Do nothing
}

TaskID FilterStackTask::GetTaskID() const
{
    return TaskID::FILTER_STACK;
}

ITask* FilterStackTask::CloneImpl()
{
    if (m_selfCondition != nullptr)
    {
        return new FilterStackTask(*m_selfCondition);
    }

    if (m_relaCondition != nullptr)
    {
        return new FilterStackTask(m_entityType, *m_relaCondition);
    }

    return nullptr;
}

TaskStatus FilterStackTask::Impl(Player& player)
{
    if (m_relaCondition != nullptr)
    {
        auto entities =
            IncludeTask::GetEntities(m_entityType, player, m_source, m_target);
        if (entities.size() != 1)
        {
            return TaskStatus::STOP;
        }

        std::vector<Entity*> filtered;
        filtered.reserve(entities.size());

        for (auto& entity : player.GetGame()->taskStack.entities)
        {
            if (m_relaCondition->Evaluate(entities[0], entity))
            {
                filtered.emplace_back(entity);
            }
        }

        player.GetGame()->taskStack.entities = filtered;
    }

    if (m_selfCondition != nullptr)
    {
        std::vector<Entity*> filtered;
        filtered.reserve(player.GetGame()->taskStack.entities.size());

        for (auto& entity : player.GetGame()->taskStack.entities)
        {
            if (m_selfCondition->Evaluate(entity))
            {
                filtered.emplace_back(entity);
            }
        }

        player.GetGame()->taskStack.entities = filtered;
    }

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::SimpleTasks
