// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ManaCrystalTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
ManaCrystalTask::ManaCrystalTask(int amount, bool fill, bool isOpponent)
    : m_amount(amount), m_fill(fill), m_isOpponent(isOpponent)
{
    // Do nothing
}

TaskStatus ManaCrystalTask::Impl(Player* player)
{
    if (m_isOpponent)
    {
        Generic::ChangeManaCrystal(player->opponent, m_amount, m_fill);
    }
    else
    {
        Generic::ChangeManaCrystal(player, m_amount, m_fill);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> ManaCrystalTask::CloneImpl()
{
    return std::make_unique<ManaCrystalTask>(m_amount, m_fill, m_isOpponent);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
