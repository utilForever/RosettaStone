// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_ALPHA_ZERO_THREAD_RUNNER_HPP
#define ROSETTASTONE_TORCH_ALPHA_ZERO_THREAD_RUNNER_HPP

#include <chrono>
#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <thread>

namespace RosettaTorch::AlphaZero
{
//!
//! \brief ThreadRunner class.
//!
//! This class is helper for running a thread asynchronously.
//!
class ThreadRunner
{
 public:
    using ConditionCallback = std::function<bool()>;

    //! Default constructor.
    ThreadRunner() = default;

    //! Default destructor.
    ~ThreadRunner() = default;

    //! Deleted copy constructor.
    ThreadRunner(const ThreadRunner&) = delete;

    //! Deleted move constructor.
    ThreadRunner(ThreadRunner&&) noexcept = delete;

    //! Deleted copy assignment operator.
    ThreadRunner& operator=(const ThreadRunner&) = delete;

    //! Deleted move assignment operator.
    ThreadRunner& operator=(ThreadRunner&&) noexcept = delete;

    //! Initializes the thread runner.
    void Initialize();

    //! Releases the thread runner.
    void Release() const;

    //! Waits the thread runner until the task is finished.
    void Wait();

    //! Runs a thread asynchronously.
    //! \param task The task to run.
    void RunAsync(std::function<void()> task);

    //! Runs a thread asynchronously under \p condition.
    //! \param condition The condition to run a thread.
    //! \param task The task to run.
    void RunAsyncUnderCondition(ConditionCallback condition,
                                std::function<void(ConditionCallback)> task);

    //! Runs a thread asynchronously until \p timePoint.
    //! \param timePoint The time point to finish running.
    //! \param task The task to run.
    void RunAsyncUntil(std::chrono::steady_clock::time_point timePoint,
                       std::function<void(ConditionCallback)> task);

 private:
    //! The main entry of the thread.
    //! \param runner The thread runner.
    static void ThreadMain(ThreadRunner* runner);

    //! The main loop of the thread.
    void MainLoop();

    std::unique_ptr<std::thread> m_thread;
    std::function<void()> m_task;
    std::mutex m_taskMutex;
    std::condition_variable m_taskCondVar;
};
}  // namespace RosettaTorch::AlphaZero

#endif  // ROSETTASTONE_TORCH_ALPHA_ZERO_THREAD_RUNNER_HPP