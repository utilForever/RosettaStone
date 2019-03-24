// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Draw.hpp>
#include <Rosetta/Tasks/SimpleTasks/DrawOpTask.hpp>

namespace RosettaStone::SimpleTasks
{
DrawOpTask::DrawOpTask(std::size_t num) : m_num(num)
{
    // Do nothing
}

TaskID DrawOpTask::GetTaskID() const
{
    return TaskID::DRAWOP;
}

TaskStatus DrawOpTask::Impl(Player& player)
{
    for (std::size_t i = 0; i < m_num; ++i)
    {
        Generic::Draw(player.GetOpponent(), std::nullopt);
    }

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::SimpleTasks
