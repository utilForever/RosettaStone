// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Actions/Draw.hpp>
#include <hspp/Tasks/SimpleTasks/DrawTask.hpp>

namespace Hearthstonepp::SimpleTasks
{
DrawTask::DrawTask(std::size_t num) : m_num(num)
{
    // Do nothing
}

TaskID DrawTask::GetTaskID() const
{
    return TaskID::DRAW;
}

TaskStatus DrawTask::Impl(Player& player)
{
    for (std::size_t i = 0; i < m_num; ++i)
    {
        Generic::Draw(player, std::nullopt);
    }

    return TaskStatus::DRAW_SUCCESS;
}
}  // namespace Hearthstonepp::SimpleTasks