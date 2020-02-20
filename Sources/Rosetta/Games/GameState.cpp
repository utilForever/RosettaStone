// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Rosetta/Games/GameState.hpp>

namespace RosettaStone
{
Player& GameState::GetCurrentPlayer()
{
    return (m_curPlayer == PlayerType::PLAYER1) ? m_players[0] : m_players[1];
}

const Player& GameState::GetCurrentPlayer() const
{
    return (m_curPlayer == PlayerType::PLAYER1) ? m_players[0] : m_players[1];
}

Player& GameState::GetOpponentPlayer()
{
    return (m_curPlayer == PlayerType::PLAYER1) ? m_players[1] : m_players[0];
}

const Player& GameState::GetOpponentPlayer() const
{
    return (m_curPlayer == PlayerType::PLAYER1) ? m_players[1] : m_players[0];
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
