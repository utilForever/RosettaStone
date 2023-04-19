// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Models/Minion.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/RevealStealthTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
RevealStealthTask::RevealStealthTask(EntityType entityType) : ITask(entityType)
{
    // Do nothing
}

TaskStatus RevealStealthTask::Impl(Player* player)
{
    const auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        if (const auto minion = dynamic_cast<Minion*>(playable); minion)
        {
            minion->SetGameTag(GameTag::STEALTH, 0);
        }
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> RevealStealthTask::CloneImpl()
{
    return std::make_unique<RevealStealthTask>(m_entityType);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
