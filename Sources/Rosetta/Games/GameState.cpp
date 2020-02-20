// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Rosetta/Games/GameState.hpp>

namespace RosettaStone
{
const Player& GameState::GetCurrentPlayer() const
{
    if (m_curPlayer == PlayerType::PLAYER1)
    {
        return m_players[0];
    }
    else if (m_curPlayer == PlayerType::PLAYER2)
    {
        return m_players[1];
    }
    else
    {
        throw std::invalid_argument(
            "GameState::GetCurrentPlayer() - Invalid player type!");
    }
}

void GameState::SwapPlayer()
{
    m_curPlayer = (m_curPlayer == PlayerType::PLAYER1) ? PlayerType::PLAYER2
                                                       : PlayerType::PLAYER1;
}

int GameState::GetTurn() const
{
    return m_turn;
}

void GameState::SetTurn(int turn)
{
    m_turn = turn;
}

void GameState::IncreaseTurn()
{
    ++m_turn;
}
}  // namespace RosettaStone
