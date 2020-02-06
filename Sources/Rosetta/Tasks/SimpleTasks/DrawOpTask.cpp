// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Draw.hpp>
#include <Rosetta/Tasks/SimpleTasks/DrawOpTask.hpp>

namespace RosettaStone::SimpleTasks
{
DrawOpTask::DrawOpTask(int amount) : m_amount(amount)
{
    // Do nothing
}

TaskStatus DrawOpTask::Impl(Player* player)
{
    for (int i = 0; i < m_amount; ++i)
    {
        Generic::Draw(player->opponent, nullptr);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> DrawOpTask::CloneImpl()
{
    return std::make_unique<DrawOpTask>(m_amount);
}
}  // namespace RosettaStone::SimpleTasks