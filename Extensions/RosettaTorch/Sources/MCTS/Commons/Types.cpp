// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <MCTS/Commons/Types.hpp>

#include <stdexcept>
#include <tuple>

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

void StateValue::SetValue(float valueForCurPlayer, PlayerType type)
{
    m_value = valueForCurPlayer;

    if (type == PlayerType::PLAYER2)
    {
        m_value = -m_value;
    }
}

void StateValue::SetValue(PlayerType type,
                          std::tuple<PlayState, PlayState> state)
{
    auto& [p1Result, p2Result] = state;

    if (p1Result == PlayState::WON && p2Result == PlayState::LOST)
    {
        m_value = 1.0f;
    }
    else if (p1Result == PlayState::LOST && p2Result == PlayState::WON)
    {
        m_value = -1.0f;
    }
    else if (p1Result == PlayState::TIED && p2Result == PlayState::TIED)
    {
        m_value = 0.0f;
    }
    else
    {
        throw std::invalid_argument("Invalid play state!");
    }
}
}  // namespace RosettaTorch::MCTS