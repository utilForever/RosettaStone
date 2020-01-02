// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_ALPHA_ZERO_SELF_PLAY_RUN_OPTIONS_HPP
#define ROSETTASTONE_TORCH_ALPHA_ZERO_SELF_PLAY_RUN_OPTIONS_HPP

#include <Agents/MCTSConfig.hpp>

namespace RosettaTorch::AlphaZero::SelfPlay
{
//!
//! \brief RunOptions struct.
//!
//! This struct holds the options of the self-play runner.
//!
struct RunOptions
{
    std::string saveDir;
    Agents::MCTSConfig agentConfig;
};
}  // namespace RosettaTorch::AlphaZero::SelfPlay

#endif  // ROSETTASTONE_TORCH_ALPHA_ZERO_SELF_PLAY_RUN_OPTIONS_HPP