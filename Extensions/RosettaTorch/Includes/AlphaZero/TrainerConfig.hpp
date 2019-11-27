// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_ALPHA_ZERO_TRAINER_CONFIG_HPP
#define ROSETTASTONE_TORCH_ALPHA_ZERO_TRAINER_CONFIG_HPP

#include <AlphaZero/Evaluation/RunOptions.hpp>
#include <AlphaZero/Optimizer/RunOptions.hpp>
#include <AlphaZero/SelfPlay/RunOptions.hpp>

#include <string>

namespace RosettaTorch::AlphaZero
{
//!
//! \brief TrainerConfig struct.
//!
//! This struct holds configuration values for trainer.
//!
struct TrainerConfig
{
    std::size_t threads = 2;

    std::string bestNetPath;
    std::string competitorNetPath;
    bool isBestNetRandom = false;

    std::size_t TRAINING_DATA_CAPACITY = 10;
    // Need at least this number of training data to start training
    std::size_t MINIMUM_TRAINING_DATA = 0;
    // If new competitor's win rate larger than this one,
    // use it to replace the best neural net so far
    float EVALUATION_WIN_RATE = 0.55f;

    SelfPlay::RunOptions selfPlay;
    Optimizer::RunOptions optimizer;
    Evaluation::RunOptions evaluation;
};
}  // namespace RosettaTorch::AlphaZero

#endif  // ROSETTASTONE_TORCH_ALPHA_ZERO_TRAINER_CONFIG_HPP