// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/FreezeTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
FreezeTask::FreezeTask(EntityType entityType) : ITask(entityType)
{
    // Do nothing
}

TaskStatus FreezeTask::Impl(Player* player)
{
    const auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        if (const auto character = dynamic_cast<Character*>(playable))
        {
            character->Freeze();
        }
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> FreezeTask::CloneImpl()
{
    return std::make_unique<FreezeTask>(m_entityType);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
