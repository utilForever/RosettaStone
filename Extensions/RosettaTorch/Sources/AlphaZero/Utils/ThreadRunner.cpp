// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <AlphaZero/Utils/ThreadRunner.hpp>

namespace RosettaTorch::AlphaZero
{
void ThreadRunner::Initialize()
{
    if (m_thread == nullptr)
    {
        m_thread.reset(new std::thread(ThreadMain, this));
    }
}

void ThreadRunner::Release() const
{
    if (m_thread)
    {
        m_thread->join();
    }
}

void ThreadRunner::ThreadMain(ThreadRunner* runner)
{
    runner->MainLoop();
}

void ThreadRunner::MainLoop()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(m_taskMutex);
        while (!m_task)
        {
            m_taskCondVar.wait(lock);
        }

        m_task();

        m_task = std::function<void()>();
        m_taskCondVar.notify_one();
    }
}
}  // namespace RosettaTorch::AlphaZero