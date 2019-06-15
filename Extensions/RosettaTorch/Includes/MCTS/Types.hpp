// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_TORCH_MCTS_TYPES_HPP
#define ROSETTASTONE_TORCH_MCTS_TYPES_HPP

#include <Rosetta/Commons/Constants.hpp>
#include <Rosetta/Enums/CardEnums.hpp>

using namespace RosettaStone;

namespace RosettaTorch::MCTS
{
class StateValue
{
 public:
    float GetValue(PlayerType type) const;
    void SetValue(PlayerType type, PlayState state);

 private:
    float m_value = 0.0f;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_TYPES_HPP