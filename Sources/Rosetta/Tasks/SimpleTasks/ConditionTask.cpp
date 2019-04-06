// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/ConditionTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>

namespace RosettaStone::SimpleTasks
{
ConditionTask::ConditionTask(EntityType entityType,
                             std::vector<SelfCondition> selfConditions)
    : ITask(entityType), m_selfConditions(selfConditions)
{
    // Do nothing
}

TaskID ConditionTask::GetTaskID() const
{
    return TaskID::CONDITION;
}

TaskStatus ConditionTask::Impl(Player& player)
{
    auto entities =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);
    if (entities.empty())
    {
        return TaskStatus::STOP;
    }

    bool flag = true;
    for (auto& condition : m_selfConditions)
    {
        flag = flag && condition.Evaluate(m_source);
    }

    player.GetGame()->taskStack.source = m_source;
    player.GetGame()->taskStack.target = m_target;
    player.GetGame()->taskStack.flag = flag;

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::SimpleTasks
