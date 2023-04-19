// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/CountTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
CountTask::CountTask(EntityType entityType, int numIndex,
                     std::vector<SelfCondition> conditions)
    : ITask(entityType),
      m_conditions(std::move(conditions)),
      m_numIndex(numIndex)
{
    // Do nothing
}

CountTask::CountTask(ZoneType zoneType, bool getFreeSpace, bool opponent)
    : m_zoneType(zoneType), m_getFreeSpace(getFreeSpace), m_opponent(opponent)
{
    // Do nothing
}

CountTask::CountTask(EntityType entityType, int numIndex,
                     std::vector<SelfCondition> conditions, ZoneType zoneType,
                     bool getFreeSpace, bool opponent)
    : ITask(entityType),
      m_zoneType(zoneType),
      m_conditions(std::move(conditions)),
      m_numIndex(numIndex),
      m_getFreeSpace(getFreeSpace),
      m_opponent(opponent)
{
    // Do nothing
}

TaskStatus CountTask::Impl(Player* player)
{
    if (m_zoneType != ZoneType::INVALID)
    {
        if (m_zoneType == ZoneType::PLAY)
        {
            const FieldZone* zone = m_opponent
                                        ? player->opponent->GetFieldZone()
                                        : player->GetFieldZone();
            player->game->taskStack.num[0] =
                m_getFreeSpace ? zone->GetFreeSpace() : zone->GetCount();
        }

        return TaskStatus::COMPLETE;
    }

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

std::unique_ptr<ITask> CountTask::CloneImpl()
{
    return std::make_unique<CountTask>(m_entityType, m_numIndex, m_conditions,
                                       m_zoneType, m_getFreeSpace, m_opponent);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
