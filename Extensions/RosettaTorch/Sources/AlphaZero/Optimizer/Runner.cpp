// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <AlphaZero/Optimizer/Runner.hpp>

namespace RosettaTorch::AlphaZero::Optimizer
{
Runner::Runner(ILogger& logger) : m_logger(logger)
{
    // Do nothing
}

void Runner::Initialize()
{
    m_optimizer.Initialize();
}

void Runner::BeforeRun(const RunOptions& runOptions, ThreadRunner* thread,
                       NeuralNet::NeuralNetwork& neuralNet,
                       TrainingData& trainingData)
{
    m_logger.Info() << "Preparing training data...";

    m_input.Clear();
    m_output.Clear();

    std::size_t fetched = 0;
    int restTries = static_cast<int>(runOptions.batches * runOptions.batchSize);
    int allowedFetchFailures =
        static_cast<int>(runOptions.maximumFetchFailureRate * restTries);

    while (--restTries >= 0)
    {
        const bool success =
            trainingData.GetRandom([&](const TrainingDataItem& item) {
                m_input.AddData(&item.GetInput());
                m_output.AddData(item.GetLabel());
                ++fetched;
            });

        if (!success)
        {
            if (--allowedFetchFailures < 0)
            {
                m_logger.Info() << "Failed to fetch training data. (Too high "
                                   "failure rate).";
                return;
            }
        }
    }

    if (fetched < runOptions.batchSize)
    {
        m_logger.Info() << "Not enough training data for batch.";
        return;
    }

    m_logger.Info() << "Training neural network... (fetched " << fetched
                    << " data)";
    m_optimizer.BeforeRun();

    thread->RunAsync([&]() {
        std::size_t epoch = 0;
        const auto callback = [&]() {
            epoch += runOptions.epochesForRun;
            m_logger.Info() << "Trained " << epoch << " epoches.";

            return epoch < runOptions.epoches;
        };

        m_optimizer.Run(m_input, m_output, runOptions, neuralNet, callback);
    });
}

void Runner::AfterRun()
{
    return m_optimizer.AfterRun();
}
}  // namespace RosettaTorch::AlphaZero::Optimizer