// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Tasks/SimpleTasks/RefreshManaTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
RefreshManaTask::RefreshManaTask(int amount) : m_amount(amount)
{
    // Do nothing
}

TaskStatus RefreshManaTask::Impl(Player* player)
{
    if (player->GetRemainingMana() + m_amount > player->GetTotalMana())
    {
        player->SetUsedMana(0);
    }
    else
    {
        player->SetUsedMana(player->GetUsedMana() - m_amount);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> RefreshManaTask::CloneImpl()
{
    return std::make_unique<RefreshManaTask>(m_amount);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
