// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <AlphaZero/Utils/ThreadPool.hpp>

namespace RosettaTorch::AlphaZero
{
void ThreadPool::Initialize(std::size_t threads)
{
    for (std::size_t i = 0; i < threads; ++i)
    {
        m_threads.emplace_back(new ThreadRunner());
        m_threads.back()->Initialize();
    }
}

void ThreadPool::Release()
{
    for (auto& thread : m_threads)
    {
        thread->Wait();
    }

    m_threads.clear();
}

ThreadRunner& ThreadPool::Get(std::size_t idx)
{
    return *m_threads[idx];
}

std::size_t ThreadPool::Size() const
{
    return m_threads.size();
}
}  // namespace RosettaTorch::AlphaZero