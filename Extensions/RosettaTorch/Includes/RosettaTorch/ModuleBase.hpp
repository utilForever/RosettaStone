// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_TORCH_MODULE_BASE_HPP
#define ROSETTASTONE_TORCH_MODULE_BASE_HPP

#include <torch/torch.h>

namespace RosettaTorch
{
//!
//! \brief ModuleBase struct.
//!
//! This struct provides interface of torch module.
//!
class ModuleBase : public torch::nn::Module
{
 public:
    //! Default virtual destructor.
    virtual ~ModuleBase() = default;

    //! Forwarding tensors to generate decision.
    //! \param available The availbale actions.
    //! \param context The game context encoded by GameToVec.
    //! \return The probability to make decision based on available actions.
    virtual torch::Tensor forward(torch::Tensor available, torch::Tensor context);
};
}  // namespace RosettaTorch

#endif