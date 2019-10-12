// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/CountTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>

namespace RosettaStone::SimpleTasks
{

CountTask::CountTask(EntityType entityType, int numIndex, std::vector<SelfCondition> conditions)
    : ITask(entityType), m_numIndex(numIndex), m_conditions(std::move(conditions))
{
    // Do nothing
}

TaskStatus CountTask::Impl(Player& player)
{
    const auto entities =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);
    
    int count;
    if (m_conditions.empty())
    {
        count = static_cast<int>(entities.size());
    }
    else
    {
        std::vector<Entity*> filtered;
        filtered.reserve(entities.size());

        for (auto& entity : entities)
        {
            bool flag = true;
            for (auto& condition : m_conditions)
            {
                if (!condition.Evaluate(entity))
                {
                    flag = false;
                }
            }
            if (flag)
            {
                filtered.push_back(entity);
            }
        }
        count = static_cast<int>(filtered.size());
    }

    switch (m_numIndex)
    {
        case 0:
            player.GetGame()->taskStack.num = count;
            break;
        case 1:
            player.GetGame()->taskStack.num1 = count;
            break;
        default:
            throw std::invalid_argument(
                "CountTask::Impl() - Invalid number index");
    }
    return TaskStatus::COMPLETE;
}

ITask* CountTask::CloneImpl()
{
    return new CountTask(m_entityType, m_numIndex, m_conditions);
}
}  // namespace RosettaStone::SimpleTasks
