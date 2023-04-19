// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ConditionTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>

#include <utility>

namespace RosettaStone::PlayMode::SimpleTasks
{
ConditionTask::ConditionTask(
    EntityType entityType,
    std::vector<std::shared_ptr<SelfCondition>> selfConditions)
    : ITask(entityType), m_selfConditions(std::move(selfConditions))
{
    // Do nothing
}

ConditionTask::ConditionTask(
    EntityType entityType,
    std::vector<std::shared_ptr<RelaCondition>> relaConditions)
    : ITask(entityType), m_relaConditions(std::move(relaConditions))
{
    // Do nothing
}

ConditionTask::ConditionTask(
    EntityType entityType,
    std::vector<std::shared_ptr<SelfCondition>> selfConditions,
    std::vector<std::shared_ptr<RelaCondition>> relaConditions)
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
        player->game->taskStack.flag = false;
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

    player->game->taskStack.flag = flag;

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> ConditionTask::CloneImpl()
{
    return std::make_unique<ConditionTask>(m_entityType, m_selfConditions,
                                           m_relaConditions);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
