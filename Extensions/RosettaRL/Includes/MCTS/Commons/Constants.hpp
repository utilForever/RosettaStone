// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_CONSTANTS_HPP
#define ROSETTASTONE_TORCH_MCTS_CONSTANTS_HPP

#include <type_traits>

namespace RosettaTorch::MCTS
{
//! Dummy structure for updater policy: TreeUpdate.
struct TreeUpdate
{
    // Do nothing
};

//! Dummy structure for updater policy: LinearUpdate.
struct LinearUpdate
{
    // Do nothing
};

using UpdaterPolicy = TreeUpdate;

//! The flag indicates whether to enable statistics.
constexpr static bool ENABLE_STATISTICS = true;

//! The value of credit that effectively increase 'm_total' field
//! by 100 for each simulation.
constexpr static int CREDIT_GRANULARITY = 100;

//! When we visit a node, add this amount of virtual losses to it to encourage
//! other CPUs to explore other parts of the search tree.
constexpr static int VIRTUAL_LOSS = 3;

//! The flag indicates whether to record leading nodes.
constexpr static bool RECORD_LEADING_NODES =
    std::is_same_v<UpdaterPolicy, TreeUpdate>;

}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_CONSTANTS_HPP