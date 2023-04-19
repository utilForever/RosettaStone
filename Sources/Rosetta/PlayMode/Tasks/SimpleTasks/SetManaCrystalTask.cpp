// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Tasks/SimpleTasks/SetManaCrystalTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
SetManaCrystalTask::SetManaCrystalTask(int amount, bool both)
    : m_amount(amount), m_both(both)
{
    // Do nothing
}

TaskStatus SetManaCrystalTask::Impl(Player* player)
{
    int remainingMana = player->GetRemainingMana();

    if (m_amount > remainingMana)
    {
        player->SetUsedMana(m_amount - remainingMana);
    }
    else
    {
        player->SetUsedMana(0);
    }

    player->SetTotalMana(m_amount);

    if (m_both)
    {
        remainingMana = player->opponent->GetRemainingMana();

        if (m_amount > remainingMana)
        {
            player->opponent->SetUsedMana(m_amount - remainingMana);
        }
        else
        {
            player->opponent->SetUsedMana(0);
        }

        player->opponent->SetTotalMana(m_amount);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> SetManaCrystalTask::CloneImpl()
{
    return std::make_unique<SetManaCrystalTask>(m_amount, m_both);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
