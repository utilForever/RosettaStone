// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_ALPHA_ZERO_SELF_PLAY_RUNNER_HPP
#define ROSETTASTONE_TORCH_ALPHA_ZERO_SELF_PLAY_RUNNER_HPP

#include <AlphaZero/Logger/ILogger.hpp>
#include <AlphaZero/SelfPlay/RunOptions.hpp>
#include <AlphaZero/SelfPlay/SelfPlayer.hpp>
#include <AlphaZero/Utils/ThreadRunner.hpp>

namespace RosettaTorch::AlphaZero::SelfPlay
{
//!
//! \brief Runner class.
//!
//! This class is a simple runner for self player.
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

    //! Initializes the self player runner.
    //! \param threads The number of threads.
    //! \param trainingData The training data.
    //! \param options The options of the self player runner.
    void Initialize(std::size_t threads, TrainingData& trainingData,
                    const RunOptions& options);

    //! The method that runs before method Run().
    //! \param milliseconds The time(ms) to finish running.
    //! \param threads A list of thread runners.
    //! \param neuralNet The neural network.
    void BeforeRun(int milliseconds, const std::vector<ThreadRunner*>& threads,
                   const NeuralNet::NeuralNetwork& neuralNet);

    //! The method that runs before method Run().
    //! \param condition The condition callback for thread runner.
    //! \param threads A list of thread runners.
    //! \param neuralNet The neural network.
    void BeforeRun(ThreadRunner::ConditionCallback condition,
                   const std::vector<ThreadRunner*>& threads,
                   const NeuralNet::NeuralNetwork& neuralNet);

    //! The method that runs after method Run().
    //! \return The result of self player.
    RunResult AfterRun();

 private:
    ILogger& m_logger;
    TrainingData* m_trainingData = nullptr;
    RunOptions m_runOptions;

    std::vector<SelfPlayer> m_players;
    std::size_t m_runningPlayers = 0;
};
}  // namespace RosettaTorch::AlphaZero::SelfPlay

#endif  // ROSETTASTONE_TORCH_ALPHA_ZERO_SELF_PLAY_RUNNER_HPP