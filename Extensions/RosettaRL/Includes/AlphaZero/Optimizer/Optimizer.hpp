// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_ALPHA_ZERO_OPTIMIZER_OPTIMIZER_HPP
#define ROSETTASTONE_TORCH_ALPHA_ZERO_OPTIMIZER_OPTIMIZER_HPP

#include <AlphaZero/Optimizer/RunOptions.hpp>
#include <NeuralNet/NeuralNetwork.hpp>
#include <NeuralNet/NeuralNetworkInput.hpp>
#include <NeuralNet/NeuralNetworkOutput.hpp>

namespace RosettaTorch::AlphaZero::Optimizer
{
//!
//! \brief Optimizer class.
//!
//! This class is a helper for optimizing the neural network that provides
//! BeforeRun(), Run() and AfterRun().
//!
class Optimizer
{
 public:
    //! Initializes the optimizer.
    void Initialize();

    //! The method that runs before method Run().
    void BeforeRun();

    //! The main method of the optimizer.
    //! \param input The input of the neural network.
    //! \param output The output of the neural network.
    //! \param options The options of the runner.
    //! \param neuralNet The neural network.
    //! \param callback The callback to run.
    template <typename Callback>
    void Run(const NeuralNet::NeuralNetworkInput& input,
             const NeuralNet::NeuralNetworkOutput& output,
             const RunOptions& options, NeuralNet::NeuralNetwork& neuralNet,
             Callback&& callback)
    {
        while (callback())
        {
            neuralNet.Train(input, output, options.batchSize,
                            options.epochesForRun);
        }
    }

    //! The method that runs after method Run().
    void AfterRun();
};
}  // namespace RosettaTorch::AlphaZero::Optimizer

#endif  // ROSETTASTONE_TORCH_ALPHA_ZERO_OPTIMIZER_OPTIMIZER_HPP