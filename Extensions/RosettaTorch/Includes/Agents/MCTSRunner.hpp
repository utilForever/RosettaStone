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
                        config.player1Deck[j] =
                            Cards::GetInstance().FindCardByID(deck[j]);
                        config.player2Deck[j] =
                            Cards::GetInstance().FindCardByID(deck[j]);
                    }

                    Game game(config);
                //    int sample_seed = get_next_selection_seed();
                //    selection_rand.seed(sample_seed);
                    mcts.Iterate(game);
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