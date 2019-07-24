// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_TYPES_HPP
#define ROSETTASTONE_TORCH_MCTS_TYPES_HPP

#include <Rosetta/Commons/Constants.hpp>
#include <Rosetta/Enums/CardEnums.hpp>

#include <stdexcept>

using namespace RosettaStone;

namespace RosettaTorch::MCTS
{
class StateValue
{
 public:
    float GetValue(PlayerType type) const
    {
        if (type == PlayerType::PLAYER1)
        {
            return m_value;
        }

        return -m_value;
    }

    void SetValue(PlayerType type, PlayState state)
    {
        if (state == PlayState::WON)
        {
            m_value = (type == PlayerType::PLAYER1 ? 1.0f : -1.0f);
        }
        else if (state == PlayState::LOST)
        {
            m_value = (type == PlayerType::PLAYER1 ? -1.0f : 1.0f);
        }
        else if (state == PlayState::TIED)
        {
            m_value = 0.0f;
        }
        else
        {
            throw std::invalid_argument("Invalid play state!");
        }
    }

 private:
    float m_value = 0.0f;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_TYPES_HPP