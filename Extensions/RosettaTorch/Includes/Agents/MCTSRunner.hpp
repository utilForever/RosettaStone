// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_AGENTS_MCTS_RUNNER_HPP
#define ROSETTASTONE_TORCH_AGENTS_MCTS_RUNNER_HPP

#include <Agents/MCTSConfig.hpp>
#include <MCTS/MOMCTS.hpp>
#include <MCTS/Selection/TreeNode.hpp>
#include <MCTS/Statistics/Statistics.hpp>

#include <Rosetta/Cards/Cards.hpp>

#include <thread>

namespace RosettaTorch::Agents
{
class MCTSRunner
{
 public:
    MCTSRunner(const MCTSConfig& config) : m_config(config)
    {
        // Do nothing
    }

    ~MCTSRunner()
    {
        WaitUntilStopped();
    }

    void Run(const GameConfig& gameConfig)
    {
        assert(m_threads.empty());
        m_stopFlag = false;

        for (int i = 0; i < m_config.threads; ++i)
        {
            m_threads.emplace_back([this, gameConfig]() {
                MCTS::MOMCTS mcts(m_p1Tree, m_p2Tree, m_statistics);

                while (!m_stopFlag.load())
                {
                    Game game(gameConfig);
                    mcts.Iterate(game);

                    m_statistics.IterateSucceeded();
                }
            });
        }
    }

    const MCTS::Statistics<>& GetStatistics() const
    {
        return m_statistics;
    }

    auto GetRootNode(PlayerType playerType) const
    {
        if (playerType == PlayerType::PLAYER1)
        {
            return &m_p1Tree;
        }
        else
        {
            return &m_p2Tree;
        }
    }

    int NotifyStop()
    {
        m_stopFlag = true;
        return 0;
    }

    void WaitUntilStopped()
    {
        NotifyStop();

        for (auto& thread : m_threads)
        {
            thread.join();
        }

        m_threads.clear();
    }

 private:
    MCTSConfig m_config;
    std::vector<std::thread> m_threads;

    MCTS::TreeNode m_p1Tree;
    MCTS::TreeNode m_p2Tree;
    MCTS::Statistics<> m_statistics;

    std::atomic_bool m_stopFlag = false;
};
}  // namespace RosettaTorch::Agents

#endif  // ROSETTASTONE_TORCH_AGENTS_MCTS_RUNNER_HPP