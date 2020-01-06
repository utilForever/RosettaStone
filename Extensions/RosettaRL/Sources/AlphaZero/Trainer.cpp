// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <AlphaZero/Trainer.hpp>

namespace RosettaTorch::AlphaZero
{
Trainer::Trainer(ILogger& logger)
    : m_logger(logger),
      m_optimizer(logger),
      m_evaluator(logger),
      m_selfPlayer(logger)
{
    // Do nothing
}

void Trainer::Initialize(const TrainerConfig& config)
{
    m_config = config;

    m_schedule.selfPlayTime = 3000;
    m_schedule.trainEpochs = 1000;

    m_threads.Initialize(m_config.threads);
    m_trainingData.Initialize(m_config.TRAINING_DATA_CAPACITY);

    m_bestNeuralNet.Load(m_config.bestNetPath, m_config.isBestNetRandom);
    m_neuralNet.Load(m_config.bestNetPath);

    m_optimizer.Initialize();
    m_evaluator.Initialize(m_config.threads);
    m_selfPlayer.Initialize(m_config.threads, m_trainingData,
                            m_config.selfPlay);
}

void Trainer::Release()
{
    m_threads.Release();
}

void Trainer::Train()
{
    PrepareData();

    while (true)
    {
        AdjustSchedule();

        TrainNeuralNetwork();

        EvaluateNeuralNetwork();

        SelfPlay();
    }
}

void Trainer::PrepareData()
{
    m_logger.Info() << "Start to prepare training data.";

    std::mutex nextShowMutex;
    auto nextShow = std::chrono::steady_clock::now();
    const auto condition = [&nextShowMutex, &nextShow, this]() mutable -> bool {
        auto records = m_trainingData.Size();
        bool show = false;

        {
            std::lock_guard<std::mutex> lock(nextShowMutex);
            const auto now = std::chrono::steady_clock::now();

            if (now > nextShow)
            {
                nextShow = now + std::chrono::seconds(5);
                show = true;  // No need to logger lock here,
                              // so use a flag to release lock
            }
        }

        if (show)
        {
            m_logger.Info([&](auto& s) {
                s << "Generated " << records << " / "
                  << m_config.MINIMUM_TRAINING_DATA << " records.";
            });
        }

        return records < m_config.MINIMUM_TRAINING_DATA;
    };

    InternalSelfPlay(condition);
}

void Trainer::AdjustSchedule()
{
    // Do nothing
}

void Trainer::TrainNeuralNetwork()
{
    m_logger.Info() << "Start training neural network.";

    m_optimizer.BeforeRun(m_config.optimizer, &m_threads.Get(0),
                          m_bestNeuralNet, m_trainingData);

    m_threads.Get(0).Wait();

    m_optimizer.AfterRun();

    m_neuralNet.Save(m_config.competitorNetPath);

    m_logger.Info() << "Saved trained neural net as competitor. "
                    << "(path = " << m_config.competitorNetPath << ")";
}

void Trainer::EvaluateNeuralNetwork()
{
    m_logger.Info() << "Start evaluation neural network.";

    m_bestNeuralNet.Save(m_config.bestNetPath);
    m_neuralNet.Save(m_config.competitorNetPath);

    const Evaluation::RunOptions options = m_config.evaluation;

    std::vector<ThreadRunner*> threads;
    for (std::size_t i = 0; i < m_threads.Size(); ++i)
    {
        threads.push_back(&m_threads.Get(i));
    }

    m_evaluator.BeforeRun(options, threads, m_config.bestNetPath,
                          m_config.competitorNetPath);

    for (auto thread : threads)
    {
        thread->Wait();
    }

    const auto& result = m_evaluator.AfterRun();

    const std::size_t winThreshold = static_cast<std::size_t>(
        m_config.EVALUATION_WIN_RATE * result.GetTotal());
    if (result.GetWin() > winThreshold)
    {
        m_logger.Info()
            << "Replace the best neural network with the new competitor!";
        m_bestNeuralNet.CopyFrom(m_neuralNet);
    }
    else
    {
        m_logger.Info() << "Competitor not strong enough. Continue to use the "
                           "best neural network so far.";
    }
}

void Trainer::SelfPlay()
{
    m_logger.Info() << "Start self play.";

    const auto start = std::chrono::steady_clock::now();
    auto until = start + std::chrono::milliseconds(m_schedule.selfPlayTime);
    const auto result = InternalSelfPlay(
        [until]() { return std::chrono::steady_clock::now() < until; });

    m_logger.Info() << "Generated " << result.generatedCount << " records.";
}

SelfPlay::RunResult Trainer::InternalSelfPlay(
    ThreadRunner::ConditionCallback condition)
{
    std::vector<ThreadRunner*> threads;
    const std::size_t useThreadsNum = m_threads.Size();

    for (std::size_t i = 0; i < useThreadsNum; ++i)
    {
        threads.push_back(&m_threads.Get(i));
    }

    m_selfPlayer.BeforeRun(std::move(condition), threads, m_bestNeuralNet);

    for (auto thread : threads)
    {
        thread->Wait();
    }

    return m_selfPlayer.AfterRun();
}
}  // namespace RosettaTorch::AlphaZero