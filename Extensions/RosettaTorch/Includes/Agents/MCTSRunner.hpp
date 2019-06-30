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

    void Run(const BoardRefView& game)
    {
        assert(m_threads.empty());
        m_stopFlag = false;

        for (int i = 0; i < m_config.threads; ++i)
        {
            m_threads.emplace_back([this, game]() {
                // engine::view::BoardView board_view;
                // engine::view::board_view::UnknownCardsInfo first_unknown;
                // engine::view::board_view::UnknownCardsInfo second_unknown;

                //// TODO: guess/feed deck type
                //// TODO: remove revealed/played/removed cards
                // first_unknown.deck_cards_ =
                //    decks::Decks::GetDeckCards("InnKeeperExpertWarlock");
                // second_unknown.deck_cards_ =
                //    decks::Decks::GetDeckCards("InnKeeperExpertWarlock");

                // board_view.Parse(game, first_unknown, second_unknown);
                // auto state_restorer =
                //    engine::view::board_view::StateRestorer::Prepare(
                //        board_view, first_unknown, second_unknown);
                // auto state_getter = [&](std::mt19937& rnd) -> state::State {
                //    return state_restorer.RestoreState(rnd);
                //};

                // std::mt19937 selection_rand;
                // std::mt19937 simulation_rand(thread_seed);
                MCTS::MOMCTS mcts(m_p1Tree, m_p2Tree);

                // size_t tree_sample_random_idx = 0;
                // auto get_next_selection_seed = [tree_sample_random_idx,
                //                                this]() mutable {
                //    int v = tree_sample_randoms_[tree_sample_random_idx];
                //    ++tree_sample_random_idx;
                //    if (tree_sample_random_idx >= tree_sample_randoms_.size())
                //    {
                //        tree_sample_random_idx = 0;
                //    }
                //    return v;
                //};

                while (!m_stopFlag.load())
                {
                //    int sample_seed = get_next_selection_seed();
                //    selection_rand.seed(sample_seed);
                    mcts.Iterate();
                //        [&]() { return state_getter(selection_rand); });

                //    statistic_.IterateSucceeded();
                }
            });
        }
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

    std::atomic_bool m_stopFlag;
};
}  // namespace RosettaTorch::Agents

#endif  // ROSETTASTONE_TORCH_AGENTS_MCTS_RUNNER_HPP