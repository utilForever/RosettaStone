// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_ALPHA_ZERO_OPTIMIZER_RUN_OPTIONS_HPP
#define ROSETTASTONE_TORCH_ALPHA_ZERO_OPTIMIZER_RUN_OPTIONS_HPP

#include <cstdlib>

namespace RosettaTorch::AlphaZero::Optimizer
{
//!
//! \brief RunOptions struct.
//!
//! This struct holds the options of the optimizer.
//!
struct RunOptions
{
    std::size_t batchSize = 32;
    std::size_t batches = 100;
    std::size_t epoches = 10000;
    std::size_t epochesForRun = 100;
    double maximumFetchFailureRate = 0.1;
};
}  // namespace RosettaTorch::AlphaZero::Optimizer

#endif  // ROSETTASTONE_TORCH_ALPHA_ZERO_OPTIMIZER_RUN_OPTIONS_HPP