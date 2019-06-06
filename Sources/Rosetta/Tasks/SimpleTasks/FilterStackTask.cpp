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
FilterStackTask::FilterStackTask(EntityType entityType,
                                 SelfCondition selfCondition)
    : ITask(entityType),
      m_selfCondition(new SelfCondition(std::move(selfCondition)))
{
    // Do nothing
}

TaskID FilterStackTask::GetTaskID() const
{
    return TaskID::FILTER_STACK;
}

TaskStatus FilterStackTask::Impl(Player& player)
{
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
