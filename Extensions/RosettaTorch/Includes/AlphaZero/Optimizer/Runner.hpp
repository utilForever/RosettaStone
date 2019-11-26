// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_ALPHA_ZERO_OPTIMIZER_RUNNER_HPP
#define ROSETTASTONE_TORCH_ALPHA_ZERO_OPTIMIZER_RUNNER_HPP

#include <AlphaZero/Logger/ILogger.hpp>
#include <AlphaZero/Optimizer/Optimizer.hpp>
#include <AlphaZero/Training/TrainingData.hpp>
#include <AlphaZero/Utils/ThreadRunner.hpp>

namespace RosettaTorch::AlphaZero::Optimizer
{
//!
//! \brief Runner class.
//!
//! This class is a simple runner for optimizer.
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

    //! Initializes the optimizer runner.
    void Initialize();

    //! The method that runs before method Run().
    //! \param runOptions The options of the optimizer runner.
    //! \param thread The thread runner.
    //! \param neuralNet The neural network.
    //! \param trainingData The training data.
    void BeforeRun(const RunOptions& runOptions, ThreadRunner* thread,
                   NeuralNet::NeuralNetwork& neuralNet,
                   TrainingData& trainingData);

    //! The method that runs after method Run().
    void AfterRun();

 private:
    ILogger& m_logger;
    Optimizer m_optimizer;

    NeuralNet::NeuralNetworkInput m_input;
    NeuralNet::NeuralNetworkOutput m_output;
};
}  // namespace RosettaTorch::AlphaZero::Optimizer

#endif  // ROSETTASTONE_TORCH_ALPHA_ZERO_OPTIMIZER_RUNNER_HPP