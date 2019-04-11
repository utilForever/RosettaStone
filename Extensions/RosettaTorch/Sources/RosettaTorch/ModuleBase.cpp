// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <RosettaTorch/ModuleBase.hpp>

namespace RosettaTorch
{
torch::Tensor forward(torch::Tensor available, torch::Tensor context)
{
    (void)available;
    (void)context;
    return torch::Tensor();
}
}  // namespace RosettaTorch