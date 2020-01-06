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
//!
//! \brief MCTSRunner class.
//!
//! This class runs multi-thread MCTS with simple statistics.
//!
class MCTSRunner
{
 public:
    //! Constructs MCTS runner with given \p config.
    //! \param config The MCTS config.
    explicit MCTSRunner(const MCTSConfig& config);

    //! Destructs MCTS runner.
    ~MCTSRunner();

    //! Runs MCTS as many threads as you set in config.
    //! \param view The board ref view to set game state.
    void Run(const BoardRefView& view);

    //! Returns the statistics of MCTS runner.
    //! \return The statistics of MCTS runner.
    const MCTS::Statistics<>& GetStatistics() const;

    //! Returns the root node of the tree.
    //! \param playerType The type of player.
    //! \return The root node of the tree.
    const MCTS::TreeNode* GetRootNode(PlayerType playerType) const;

    //! Notifies threads to stop.
    void NotifyStop();

    //! Waits until all threads stop.
    void WaitUntilStopped();

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