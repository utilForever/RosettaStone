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

TaskStatus CountTask::Impl(Player* player)
{
    const auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);
    
    int count;
    if (m_conditions.empty())
    {
        count = static_cast<int>(playables.size());
    }
    else
    {
        std::vector<Playable*> filtered;
        filtered.reserve(playables.size());

        for (auto& playable : playables)
        {
            bool flag = true;
            for (auto& condition : m_conditions)
            {
                if (!condition.Evaluate(playable))
                {
                    flag = false;
                }
            }
            if (flag)
            {
                filtered.push_back(playable);
            }
        }
        count = static_cast<int>(filtered.size());
    }

    switch (m_numIndex)
    {
        case 0:
            player->game->taskStack.num[0] = count;
            break;
        case 1:
            player->game->taskStack.num[1] = count;
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
