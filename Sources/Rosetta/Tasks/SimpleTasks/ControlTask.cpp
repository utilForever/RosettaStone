// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Models/Minion.hpp>
#include <Rosetta/Tasks/SimpleTasks/ControlTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Zones/FieldZone.hpp>

namespace RosettaStone::SimpleTasks
{
ControlTask::ControlTask(EntityType entityType) : ITask(entityType)
{
    // Do nothing
}

TaskStatus ControlTask::Impl(Player* player)
{
    auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);
    auto myField = player->GetFieldZone();
    auto opField = player->opponent->GetFieldZone();

    for (auto& playable : playables)
    {
        const auto& minion = dynamic_cast<Minion*>(playable);
        if (minion == nullptr)
        {
            continue;
        }

        if (myField->IsFull())
        {
            playable->Destroy();
            continue;
        }

        const auto removedMinion = opField->Remove(minion);
        removedMinion->player = player;
        myField->Add(removedMinion);
    }

    return TaskStatus::COMPLETE;
}

ITask* ControlTask::CloneImpl()
{
    return new ControlTask(m_entityType);
}
}  // namespace RosettaStone::SimpleTasks
