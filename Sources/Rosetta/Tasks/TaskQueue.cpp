// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/TaskQueue.hpp>

namespace RosettaStone
{
TaskQueue::TaskQueue(Game* game) : m_game(game)
{
    // Do nothing
}

std::queue<ITask*>& TaskQueue::GetCurrentQueue()
{
    return m_eventStack.empty() ? m_baseQueue : m_eventStack.top();
}

bool TaskQueue::IsEmpty()
{
    return m_eventFlag || GetCurrentQueue().empty();
}

void TaskQueue::StartEvent()
{
    m_eventFlag = true;
}

void TaskQueue::EndEvent()
{
    if (m_eventFlag)
    {
        m_eventFlag = false;
        return;
    }

    if (!m_eventStack.empty())
    {
        m_eventStack.pop();
    }
}

void TaskQueue::Enqueue(ITask* task)
{
    if (m_eventFlag)
    {
        if (!GetCurrentQueue().empty())
        {
            m_eventStack.push(std::queue<ITask*>{});
        }

        m_eventFlag = false;
    }

    GetCurrentQueue().push(task);
}

TaskStatus TaskQueue::Process()
{
    ITask* currentTask = GetCurrentQueue().front();
    GetCurrentQueue().pop();
    m_currentTask = currentTask;

    const TaskStatus status = currentTask->Run();

    m_currentTask = nullptr;

    return status;
}
}  // namespace RosettaStone
