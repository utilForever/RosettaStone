// This code is based on Sabberstone project.
// Copyright (c) 2017-2021 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2021 Chris Ohk

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Minion.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeAdjacentTask.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
IncludeAdjacentTask::IncludeAdjacentTask(EntityType entityType,
                                         bool includeCenter)
    : ITask(entityType), m_includeCenter(includeCenter)
{
    // Do nothing
}

TaskStatus IncludeAdjacentTask::Impl(Player* player)
{
    Minion* center = nullptr;

    std::vector<Playable*> minions;

    switch (m_entityType)
    {
        case EntityType::SOURCE:
            center = dynamic_cast<Minion*>(m_source);
            break;
        case EntityType::TARGET:
            center = dynamic_cast<Minion*>(m_target);
            break;
        case EntityType::EVENT_TARGET:
            if (const auto eventData = player->game->currentEventData.get();
                eventData)
            {
                center = dynamic_cast<Minion*>(eventData->eventTarget);
            }
            break;
        default:
            throw std::invalid_argument(
                "IncludeAdjacentTask::Impl() - Invalid entity type");
    }

    if (!center)
    {
        return TaskStatus::STOP;
    }

    if (center->GetZoneType() == ZoneType::PLAY)
    {
        FieldZone* fieldZone = center->player->GetFieldZone();
        const int pos = center->GetZonePosition();
        int count = m_includeCenter ? 1 : 0;

        Minion* left = nullptr;
        Minion* right = nullptr;

        if (pos > 0)
        {
            Placeable* leftPlaceable = (*fieldZone)[pos - 1];

            if (const auto leftMinion = dynamic_cast<Minion*>(leftPlaceable);
                leftMinion && !leftMinion->IsUntouchable())
            {
                left = leftMinion;
                ++count;
            }

            if (pos < fieldZone->GetCount() - 1)
            {
                Placeable* rightPlaceable = (*fieldZone)[pos + 1];

                if (const auto rightMinion =
                        dynamic_cast<Minion*>(rightPlaceable);
                    rightMinion && !rightMinion->IsUntouchable())
                {
                    right = rightMinion;
                    ++count;
                }
            }
        }
        else if (fieldZone->GetCount() > 1)
        {
            Placeable* rightPlaceable = (*fieldZone)[pos + 1];

            if (const auto rightMinion = dynamic_cast<Minion*>(rightPlaceable);
                rightMinion && !rightMinion->IsUntouchable())
            {
                right = rightMinion;
                ++count;
            }
        }

        minions.reserve(count);

        if (left)
        {
            minions.emplace_back(left);
        }
        if (m_includeCenter)
        {
            minions.emplace_back(center);
        }
        if (right)
        {
            minions.emplace_back(right);
        }
    }

    player->game->taskStack.playables = minions;

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> IncludeAdjacentTask::CloneImpl()
{
    return std::make_unique<IncludeAdjacentTask>(m_entityType, m_includeCenter);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
