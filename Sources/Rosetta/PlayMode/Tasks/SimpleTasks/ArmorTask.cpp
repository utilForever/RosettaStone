// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ArmorTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
ArmorTask::ArmorTask(int amount, bool useNumber)
    : m_amount(amount), m_useNumber(useNumber)
{
    // Do nothing
}

TaskStatus ArmorTask::Impl(Player* player)
{
    const int amount = m_useNumber ? player->game->taskStack.num[0] : m_amount;
    player->GetHero()->GainArmor(amount);

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> ArmorTask::CloneImpl()
{
    return std::make_unique<ArmorTask>(m_amount, m_useNumber);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
