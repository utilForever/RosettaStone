// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <MCTS/Policies/PlayerController.hpp>

namespace RosettaTorch::MCTS
{
PlayerController::Player::Player(RosettaStone::PlayerType playerType)
    : m_playerType(playerType)
{
    // Do nothing
}

PlayerController::Player PlayerController::Player::Player1()
{
    return Player(RosettaStone::PlayerType::PLAYER1);
}

PlayerController::Player PlayerController::Player::Player2()
{
    return Player(RosettaStone::PlayerType::PLAYER2);
}

bool PlayerController::Player::operator==(const Player& rhs) const
{
    return m_playerType == rhs.m_playerType;
}

bool PlayerController::Player::operator!=(const Player& rhs) const
{
    return m_playerType != rhs.m_playerType;
}

PlayerController::Player PlayerController::Player::Opponent() const
{
    return Player(m_playerType == RosettaStone::PlayerType::PLAYER1
                      ? RosettaStone::PlayerType::PLAYER2
                      : RosettaStone::PlayerType::PLAYER1);
}

bool PlayerController::Player::IsPlayer1() const
{
    return m_playerType == RosettaStone::PlayerType::PLAYER1;
}

bool PlayerController::Player::IsPlayer2() const
{
    return m_playerType == RosettaStone::PlayerType::PLAYER2;
}

RosettaStone::PlayerType PlayerController::Player::GetPlayerType() const
{
    return m_playerType;
}

PlayerController::Player PlayerController::GetPlayer() const
{
    return Player(m_game.GetGameState().GetCurrentPlayer());
}

RosettaStone::Board PlayerController::GetPlayerBoard(Player player)
{
    return RosettaStone::Board(m_game, player.GetPlayerType());
}
}  // namespace RosettaTorch::MCTS