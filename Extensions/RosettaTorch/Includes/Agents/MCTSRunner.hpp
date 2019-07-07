// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_AGENTS_MCTS_RUNNER_HPP
#define ROSETTASTONE_TORCH_AGENTS_MCTS_RUNNER_HPP

#include <MCTS/Statistics.h>
#include <Agents/MCTSConfig.hpp>
#include <MCTS/MOMCTS.hpp>
#include <MCTS/Selection/TreeNode.hpp>

#include <Rosetta/Cards/Cards.hpp>

#include <thread>

namespace RosettaTorch::Agents
{
class MCTSRunner
{
 public:
    MCTSRunner(const MCTSConfig& config) : m_config(config), m_stopFlag(false)
    {
        // Do nothing
    }

    ~MCTSRunner()
    {
        WaitUntilStopped();
    }

    void Run()
    {
        assert(m_threads.empty());
        m_stopFlag = false;

        for (int i = 0; i < m_config.threads; ++i)
        {
            m_threads.emplace_back([this]() {
                MCTS::MOMCTS mcts(m_p1Tree, m_p2Tree, m_statistics);

                while (!m_stopFlag.load())
                {
                    GameConfig config;
                    config.player1Class = CardClass::PRIEST;
                    config.player2Class = CardClass::MAGE;
                    config.startPlayer = PlayerType::PLAYER1;
                    config.doShuffle = false;
                    config.doFillDecks = false;
                    config.skipMulligan = true;
                    config.autoRun = true;

                    std::array<std::string, START_DECK_SIZE> deck = {
                        "CS2_106", "CS2_105", "CS1_112", "CS1_112",  // 1
                        "CS1_113", "CS1_113", "CS1_130", "CS1_130",  // 2
                        "CS2_007", "CS2_007", "CS2_022", "CS2_022",  // 3
                        "CS2_023", "CS2_023", "CS2_024", "CS2_024",  // 4
                        "CS2_025", "CS2_025", "CS2_026", "CS2_026",  // 5
                        "CS2_027", "CS2_027", "CS2_029", "CS2_029",  // 6
                        "CS2_032", "CS2_032", "CS2_033", "CS2_033",  // 7
                        "CS2_037", "CS2_037"
                    };

                    for (size_t j = 0; j < START_DECK_SIZE; ++j)
                    {
                        config.player1Deck[j] = Cards::FindCardByID(deck[j]);
                        config.player2Deck[j] = Cards::FindCardByID(deck[j]);
                    }

                    while (!m_stopFlag.load())
                    {
                        Game game(config);
                        mcts.Iterate(game);

                        m_statistics.IterateSucceeded();
                    }
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

    std::atomic_bool m_stopFlag;
};
}  // namespace RosettaTorch::Agents

#endif  // ROSETTASTONE_TORCH_AGENTS_MCTS_RUNNER_HPP