// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_ALPHA_ZERO_THREAD_POOL_HPP
#define ROSETTASTONE_TORCH_ALPHA_ZERO_THREAD_POOL_HPP

#include <AlphaZero/Utils/ThreadRunner.hpp>

#include <vector>

namespace RosettaTorch::AlphaZero
{
//!
//! \brief ThreadPool class.
//!
//! This class is a software design pattern for achieving concurrency of
//! execution in a computer program.
//!
class ThreadPool
{
 public:
    //! Default constructor.
    ThreadPool() = default;

    //! Default destructor.
    ~ThreadPool() = default;

    //! Deleted copy constructor.
    ThreadPool(const ThreadPool&) = delete;

    //! Deleted move constructor.
    ThreadPool(ThreadPool&&) noexcept = delete;

    //! Deleted copy assignment operator.
    ThreadPool& operator=(const ThreadPool&) = delete;

    //! Deleted move assignment operator.
    ThreadPool& operator=(ThreadPool&&) noexcept = delete;

    //! Initializes the thread pool.
    //! \param threads The number of threads.
    void Initialize(std::size_t threads);

    //! Releases the thread pool.
    void Release();

    //! Gets a thread in the thread pool.
    //! \param idx The index of the thread pool.
    //! \return A thread in the thread pool.
    ThreadRunner& Get(std::size_t idx);

    //! Returns the size of the thread pool.
    //! \return The size of the thread pool.
    std::size_t Size() const;

 private:
    std::vector<std::unique_ptr<ThreadRunner>> m_threads;
};
}  // namespace RosettaTorch::AlphaZero

#endif  // ROSETTASTONE_TORCH_ALPHA_ZERO_THREAD_POOL_HPP