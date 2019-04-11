// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_TORCH_ACTION_ENCODER_HPP
#define ROSETTASTONE_TORCH_ACTION_ENCODER_HPP

#include <Rosetta/Actions/AvailableActions.hpp>

#include <torch/torch.h>

namespace RosettaTorch
{
using namespace RosettaStone;

//!
//! \brief ActionEncoder struct.
//!
//! This struct generates torch tensor from ActionEncode.
//!
struct ActionEncoder
{
    static constexpr size_t TaskIDSize = 4;

    static constexpr TaskID TaskIDs[TaskIDSize] = {
        TaskID::MULLIGAN, TaskID::END_TURN, TaskID::ATTACK, TaskID::PLAY_CARD
    };

    /////////////////////////////////////////////
    // My hand, my field, your field
    static constexpr size_t TargetPlaceSize = 3;

    static constexpr size_t CurrentHandOffset = 0;

    static constexpr size_t CurrentFieldOffset = 1;

    static constexpr size_t OpponentFieldOffset = 2;

    /////////////////////////////////////////////
    static constexpr size_t MaximumFieldSize = 10;

    static constexpr size_t EntityEncodeSize =
        TargetPlaceSize + MaximumFieldSize;

    /////////////////////////////////////////////
    static constexpr size_t NumSource = 1;

    static constexpr size_t NumTarget = Generic::ActionEncode::NumTarget;

    /////////////////////////////////////////////
    static constexpr size_t ActionTensorSize =
        TaskIDSize + EntityEncodeSize * (NumSource + NumTarget);

    //! Convert ActionEncode to torch::Tensor.
    static torch::Tensor ActionToTensor(const Game& game,
                                        const Generic::ActionEncode& action);
};
}  // namespace RosettaTorch

#endif