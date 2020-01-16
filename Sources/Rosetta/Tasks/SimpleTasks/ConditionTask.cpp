// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/ConditionTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>

#include <utility>

namespace RosettaStone::SimpleTasks
{
ConditionTask::ConditionTask(EntityType entityType,
                             std::vector<SelfCondition*> selfConditions)
    : ITask(entityType), m_selfConditions(std::move(selfConditions))
{
    // Do nothing
}

ConditionTask::ConditionTask(EntityType entityType,
                             std::vector<RelaCondition*> relaConditions)
    : ITask(entityType), m_relaConditions(std::move(relaConditions))
{
    // Do nothing
}

ConditionTask::ConditionTask(EntityType entityType,
                             std::vector<SelfCondition*> selfConditions,
                             std::vector<RelaCondition*> relaConditions)
    : ITask(entityType),
      m_selfConditions(std::move(selfConditions)),
      m_relaConditions(std::move(relaConditions))
{
    // Do nothing
}

TaskStatus ConditionTask::Impl(Player* player)
{
    auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);
    if (playables.empty())
    {
        return TaskStatus::STOP;
    }

    bool flag = true;

    for (auto& playable : playables)
    {
        for (auto& condition : m_selfConditions)
        {
            flag = flag && condition->Evaluate(playable);
        }

        for (auto& condition : m_relaConditions)
        {
            flag = flag && condition->Evaluate(
                               dynamic_cast<Playable*>(m_source), playable);
        }
    }

    player->game->taskStack.source = m_source;
    player->game->taskStack.target = m_target;
    player->game->taskStack.flag = flag;

    return TaskStatus::COMPLETE;
}

ITask* ConditionTask::CloneImpl()
{
    return new ConditionTask(m_entityType, m_selfConditions, m_relaConditions);
}
}  // namespace RosettaStone::SimpleTasks
