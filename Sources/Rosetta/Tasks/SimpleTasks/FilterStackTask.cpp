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
FilterStackTask::FilterStackTask(std::vector<SelfCondition*> selfConditions)
    : m_selfConditions(std::move(selfConditions))
{
    // Do nothing
}

FilterStackTask::FilterStackTask(EntityType type,
                                 std::vector<RelaCondition*> relaConditions)
    : ITask(type), m_relaConditions(std::move(relaConditions))
{
    // Do nothing
}

TaskStatus FilterStackTask::Impl(Player* player)
{
    if (!m_relaConditions.empty())
    {
        auto entities =
            IncludeTask::GetEntities(m_entityType, player, m_source, m_target);
        if (entities.size() != 1)
        {
            return TaskStatus::STOP;
        }

        std::vector<Playable*> filtered;
        filtered.reserve(entities.size());

        for (auto& playable : player->game->taskStack.playables)
        {
            bool flag = true;

            for (auto& condition : m_relaConditions)
            {
                flag = flag && condition->Evaluate(entities[0], playable);
            }

            if (flag)
            {
                filtered.emplace_back(playable);
            }
        }

        player->game->taskStack.playables = filtered;
    }

    if (!m_selfConditions.empty())
    {
        std::vector<Playable*> filtered;
        filtered.reserve(player->game->taskStack.playables.size());

        for (auto& playable : player->game->taskStack.playables)
        {
            bool flag = true;

            for (auto& condition : m_selfConditions)
            {
                flag = flag && condition->Evaluate(playable);
            }

            if (flag)
            {
                filtered.emplace_back(playable);
            }
        }

        player->game->taskStack.playables = filtered;
    }

    return TaskStatus::COMPLETE;
}

ITask* FilterStackTask::CloneImpl()
{
    if (!m_selfConditions.empty())
    {
        return new FilterStackTask(m_selfConditions);
    }

    if (!m_relaConditions.empty())
    {
        return new FilterStackTask(m_entityType, m_relaConditions);
    }

    return nullptr;
}
}  // namespace RosettaStone::SimpleTasks
