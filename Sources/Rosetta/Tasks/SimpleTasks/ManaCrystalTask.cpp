// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Tasks/SimpleTasks/ManaCrystalTask.hpp>

namespace RosettaStone::SimpleTasks
{
ManaCrystalTask::ManaCrystalTask(int amount, bool fill)
    : m_amount(amount), m_fill(fill)
{
    // Do nothing
}

TaskID ManaCrystalTask::GetTaskID() const
{
    return TaskID::MANA_CRYSTAL;
}

TaskStatus ManaCrystalTask::Impl(Player& player)
{
    Generic::ChangeManaCrystal(player, m_amount, m_fill);

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::SimpleTasks
