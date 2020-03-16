// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/NumberConditionTask.hpp>

namespace RosettaStone::SimpleTasks
{
NumberConditionTask::NumberConditionTask(int referenceValue, RelaSign relaSign)
    : m_referenceValue(referenceValue), m_relaSign(relaSign)
{
    // Do nothing
}

TaskStatus NumberConditionTask::Impl(Player* player)
{
    auto& taskStack = player->game->taskStack;

    if (m_relaSign == RelaSign::GEQ)
    {
        taskStack.flag = taskStack.num[0] >= m_referenceValue;
    }
    else if (m_relaSign == RelaSign::LEQ)
    {
        taskStack.flag = taskStack.num[0] <= m_referenceValue;
    }
    else
    {
        taskStack.flag = taskStack.num[0] == m_referenceValue;
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> NumberConditionTask::CloneImpl()
{
    return std::make_unique<NumberConditionTask>(m_referenceValue, m_relaSign);
}
}  // namespace RosettaStone::SimpleTasks
