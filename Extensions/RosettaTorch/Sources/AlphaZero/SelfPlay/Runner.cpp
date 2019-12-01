// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <AlphaZero/SelfPlay/Runner.hpp>

namespace RosettaTorch::AlphaZero::SelfPlay
{
Runner::Runner(ILogger& logger) : m_logger(logger)
{
    // Do nothing
}

void Runner::Initialize(std::size_t threads, TrainingData& trainingData,
                        const RunOptions& options)
{
    for (std::size_t i = 0; i < threads; ++i)
    {
        m_players.emplace_back(m_logger);
    }

    m_trainingData = &trainingData;
    m_runOptions = options;
}

void Runner::BeforeRun(int milliseconds,
                       const std::vector<ThreadRunner*>& threads,
                       const NeuralNet::NeuralNetwork& neuralNet)
{
    const auto start = std::chrono::steady_clock::now();
    auto until = start + std::chrono::milliseconds(milliseconds);

    return BeforeRun(
        [until]() { return std::chrono::steady_clock::now() < until; }, threads,
        neuralNet);
}

void Runner::BeforeRun(ThreadRunner::ConditionCallback condition,
                       const std::vector<ThreadRunner*>& threads,
                       const NeuralNet::NeuralNetwork& neuralNet)
{
    assert(threads.size() <= m_players.size());

    for (std::size_t i = 0; i < threads.size(); ++i)
    {
        m_players[i].BeforeRun(*m_trainingData, neuralNet, m_runOptions);
    }

    for (std::size_t i = 0; i < threads.size(); ++i)
    {
        auto& player = m_players[i];
        threads[i]->RunAsyncUnderCondition(
            condition, [&](auto&& callback) { player.Run(callback); });
    }

    m_runningPlayers = threads.size();
}

RunResult Runner::AfterRun()
{
    RunResult result;

    for (std::size_t i = 0; i < m_runningPlayers; ++i)
    {
        result += m_players[i].AfterRun();
    }

    return result;
}
}  // namespace RosettaTorch::AlphaZero::SelfPlay