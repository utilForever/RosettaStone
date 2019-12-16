// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Models/Minion.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/RevealStealthTask.hpp>

namespace RosettaStone::SimpleTasks
{
RevealStealthTask::RevealStealthTask(EntityType entityType) : ITask(entityType)
{
    // Do nothing
}

TaskStatus RevealStealthTask::Impl(Player* player)
{
    auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        if (auto minion = dynamic_cast<Minion*>(playable); minion)
        {
            minion->SetGameTag(GameTag::STEALTH, 0);
        }
    }

    return TaskStatus::COMPLETE;
}

ITask* RevealStealthTask::CloneImpl()
{
    return new RevealStealthTask(m_entityType);
}
}  // namespace RosettaStone::SimpleTasks
