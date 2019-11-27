// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <AlphaZero/Utils/ThreadRunner.hpp>

#include <utility>

namespace RosettaTorch::AlphaZero
{
void ThreadRunner::Initialize()
{
    m_thread.reset(new std::thread(ThreadMain, this));
}

void ThreadRunner::Release() const
{
    if (m_thread)
    {
        m_thread->join();
    }
}

void ThreadRunner::Wait()
{
    std::unique_lock<std::mutex> lock(m_taskMutex);
    while (m_task)
    {
        m_taskCondVar.wait(lock);
    }
}

void ThreadRunner::RunAsync(std::function<void()> task)
{
    std::lock_guard<std::mutex> guard(m_taskMutex);

    if (m_task != nullptr)
    {
        throw std::runtime_error("You should wait for the previous work done.");
    }

    m_task = std::move(task);
    m_taskCondVar.notify_one();
}

void ThreadRunner::RunAsyncUnderCondition(
    ConditionCallback condition, std::function<void(ConditionCallback)> task)
{
    RunAsync(std::bind(task, condition));
}

void ThreadRunner::RunAsyncUntil(
    std::chrono::steady_clock::time_point timePoint,
    std::function<void(ConditionCallback)> task)
{
    RunAsyncUnderCondition(
        [timePoint]() -> bool {
            return std::chrono::steady_clock::now() < timePoint;
        },
        std::move(task));
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