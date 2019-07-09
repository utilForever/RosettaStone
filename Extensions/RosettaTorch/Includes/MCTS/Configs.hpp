// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_CONFIGS_HPP
#define ROSETTASTONE_TORCH_MCTS_CONFIGS_HPP

#include <type_traits>

namespace RosettaTorch::MCTS
{
struct TreeUpdate
{
    // Do nothing
};
struct LinearUpdate
{
    // Do nothing
};

using UpdaterPolicy = TreeUpdate;

constexpr static bool ENABLE_STATISTICS = true;
constexpr static int CREDIT_GRANULARITY = 100;
constexpr static int VIRTUAL_LOSS = 3;
constexpr static bool RECORD_LEADING_NODES =
    std::is_same_v<UpdaterPolicy, TreeUpdate>;

}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_CONFIGS_HPP