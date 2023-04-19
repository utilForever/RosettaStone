// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Tasks/TaskQueue.hpp>

namespace RosettaStone::PlayMode
{
std::queue<std::unique_ptr<ITask>>& TaskQueue::GetCurrentQueue()
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

void TaskQueue::Enqueue(std::unique_ptr<ITask> task)
{
    if (m_eventFlag)
    {
        if (!GetCurrentQueue().empty())
        {
            m_eventStack.push(std::queue<std::unique_ptr<ITask>>{});
        }

        m_eventFlag = false;
    }

    GetCurrentQueue().push(std::move(task));
}

TaskStatus TaskQueue::Process()
{
    std::unique_ptr<ITask> currentTask = std::move(GetCurrentQueue().front());
    GetCurrentQueue().pop();

    const TaskStatus status = currentTask->Run();
    return status;
}
}  // namespace RosettaStone::PlayMode
