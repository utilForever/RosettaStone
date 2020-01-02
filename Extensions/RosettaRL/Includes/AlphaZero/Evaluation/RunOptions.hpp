// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_ALPHA_ZERO_EVALUATION_RUN_OPTIONS_HPP
#define ROSETTASTONE_TORCH_ALPHA_ZERO_EVALUATION_RUN_OPTIONS_HPP

#include <Agents/MCTSConfig.hpp>

namespace RosettaTorch::AlphaZero::Evaluation
{
//!
//! \brief RunOptions struct.
//!
//! This struct holds the options of the evaluation runner.
//! Note that the unit of variable 'showInterval' is 'ms'.
//!
struct RunOptions
{
    std::size_t runs = 1000;
    std::size_t showInterval = 1000;
    Agents::MCTSConfig agentConfig;
};
}  // namespace RosettaTorch::AlphaZero::Evaluation

#endif  // ROSETTASTONE_TORCH_ALPHA_ZERO_EVALUATION_RUN_OPTIONS_HPP