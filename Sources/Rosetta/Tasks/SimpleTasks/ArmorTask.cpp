// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Tasks/SimpleTasks/ArmorTask.hpp>

namespace RosettaStone::SimpleTasks
{
ArmorTask::ArmorTask(int amount) : m_amount(amount)
{
    // Do nothing
}

TaskStatus ArmorTask::Impl(Player* player)
{
    player->GetHero()->GainArmor(m_amount);

    return TaskStatus::COMPLETE;
}

ITask* ArmorTask::CloneImpl()
{
    return new ArmorTask(m_amount);
}
}  // namespace RosettaStone::SimpleTasks
