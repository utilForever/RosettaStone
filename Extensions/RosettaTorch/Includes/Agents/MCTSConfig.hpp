// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_AGENTS_MCTS_CONFIG_HPP
#define ROSETTASTONE_TORCH_AGENTS_MCTS_CONFIG_HPP

#include <MCTS/Commons/Config.hpp>

namespace RosettaTorch::Agents
{
//!
//! \brief MCTSConfig struct.
//!
//! This struct holds configuration values to create a new MCTS agent/runner.
//!
struct MCTSConfig
{
    MCTSConfig()
        : threads(1),
          iterationsPerAction(10000),
          callbackInterval(1000),
          mcts(),
          actionFollowTemperature(0.0)
    {
        // Do nothing
    }

    int threads;

    int iterationsPerAction;
    int callbackInterval;

    MCTS::Config mcts;

    double actionFollowTemperature;
};
}  // namespace RosettaTorch::Agents

#endif  // ROSETTASTONE_TORCH_AGENTS_MCTS_CONFIG_HPP