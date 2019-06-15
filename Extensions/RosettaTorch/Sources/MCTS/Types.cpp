// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <MCTS/Types.hpp>

#include <stdexcept>

namespace RosettaTorch::MCTS
{
float StateValue::GetValue(PlayerType type) const
{
    if (type == PlayerType::PLAYER1)
    {
        return m_value;
    }

    return -m_value;
}

void StateValue::SetValue(PlayerType type, PlayState state)
{
    if (type == PlayerType::PLAYER1)
    {
        if (state == PlayState::WON)
        {
            m_value = 1.0f;
        }
        else if (state == PlayState::LOST)
        {
            m_value = -1.0f;
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
    else if (type == PlayerType::PLAYER2)
    {
        if (state == PlayState::WON)
        {
            m_value = -1.0f;
        }
        else if (state == PlayState::LOST)
        {
            m_value = 1.0f;
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
}
}  // namespace RosettaTorch::MCTS