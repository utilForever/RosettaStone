// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_ALPHA_ZERO_EVALUATION_RUNNER_HPP
#define ROSETTASTONE_TORCH_ALPHA_ZERO_EVALUATION_RUNNER_HPP

#include <AlphaZero/Evaluation/Evaluator.hpp>
#include <AlphaZero/Logger/ILogger.hpp>
#include <AlphaZero/Utils/ThreadRunner.hpp>

namespace RosettaTorch::AlphaZero::Evaluation
{
//!
//! \brief Runner class.
//!
//! This class is a simple runner for evaluation.
//!
class Runner
{
 public:
    //! Constructs runner with given \p logger.
    //! \param logger The logger to write the log.
    explicit Runner(ILogger& logger);

    //! Deleted copy constructor.
    Runner(const Runner&) = delete;

    //! Deleted move constructor.
    Runner(Runner&&) noexcept = delete;

    //! Deleted copy assignment operator.
    Runner& operator=(const Runner&) = delete;

    //! Deleted move assignment operator.
    Runner& operator=(Runner&&) noexcept = delete;

    //! Initializes the evaluation runner.
    //! \param threads The number of threads.
    void Initialize(std::size_t threads);

    //! The method that runs before method Run().
    //! \param runOptions The options of the evaluation runner.
    //! \param threads A list of thread runners.
    //! \param bestNetPath The path of the best neural network.
    //! \param competitorNetPath The path of the competitor neural network.
    void BeforeRun(const RunOptions& runOptions,
                   const std::vector<ThreadRunner*>& threads,
                   const std::string& bestNetPath,
                   const std::string& competitorNetPath);

    //! The method that runs after method Run().
    //! \return The result of the competition.
    const CompetitionResult& AfterRun() const;

 private:
    ILogger& m_logger;
    std::vector<Evaluator> m_evaluators;
    CompetitionResult m_result;

    std::mutex m_nextShowMutex;
    std::chrono::steady_clock::time_point m_nextShow;

    std::size_t m_runningEvaluators = 0;
};
}  // namespace RosettaTorch::AlphaZero::Evaluation

#endif  // ROSETTASTONE_TORCH_ALPHA_ZERO_EVALUATION_RUNNER_HPP