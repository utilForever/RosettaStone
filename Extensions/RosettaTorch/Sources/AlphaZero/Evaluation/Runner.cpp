// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <AlphaZero/Evaluation/Runner.hpp>

namespace RosettaTorch::AlphaZero::Evaluation
{
Runner::Runner(ILogger& logger) : m_logger(logger)
{
    // Do nothing
}

void Runner::Initialize(std::size_t threads)
{
    for (std::size_t i = 0; i < threads; ++i)
    {
        m_evaluators.emplace_back(Evaluator());
    }
}

void Runner::BeforeRun(const RunOptions& runOptions,
                       const std::vector<ThreadRunner*>& threads,
                       const std::string& bestNetPath,
                       const std::string& competitorNetPath)
{
    assert(threads.size() <= m_evaluators.size());

    m_result.Clear();
    m_nextShow = std::chrono::steady_clock::now();
    const auto cond = [&runOptions, this]() {
        std::lock_guard<std::mutex> lock(m_nextShowMutex);
        const auto now = std::chrono::steady_clock::now();

        if (now > m_nextShow)
        {
            m_nextShow =
                now + std::chrono::milliseconds(runOptions.showInterval);
            m_logger.Info([&](auto& s) {
                s << "Run " << m_result.GetTotal()
                  << " trials. Competitor wins " << m_result.GetWin()
                  << " times.";
            });
        }

        return m_result.GetTotal() < runOptions.runs;
    };

    for (std::size_t i = 0; i < threads.size(); ++i)
    {
        m_evaluators[i].BeforeRun(bestNetPath, competitorNetPath, m_result);
    }

    for (std::size_t i = 0; i < threads.size(); ++i)
    {
        auto& evaluator = m_evaluators[i];
        threads[i]->RunAsyncUnderCondition(
            cond, [&evaluator, &runOptions](auto&& callback) {
                evaluator.Run(runOptions, callback);
            });
    }

    m_runningEvaluators = threads.size();
}

const CompetitionResult& Runner::AfterRun() const
{
    return m_result;
}
}  // namespace RosettaTorch::AlphaZero::Evaluation