// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Rosetta/PlayMode/Views/Board.hpp>

namespace RosettaStone::PlayMode
{
Board::Board(Game& game, PlayerType playerType)
    : m_game(game), m_playerType(playerType)
{
    // Do nothing
}

void Board::RefCopyFrom(const Board& rhs)
{
    m_game.RefCopyFrom(rhs.m_game);

    m_playerType = rhs.m_playerType;
}

Player* Board::GetCurrentPlayer() const
{
    return m_game.GetCurrentPlayer();
}

PlayerType Board::GetViewType() const
{
    return m_playerType;
}

ReducedBoardView Board::CreateView() const
{
    if (m_playerType == PlayerType::PLAYER1)
    {
        return ReducedBoardView(BoardRefView(m_game, PlayerType::PLAYER1));
    }
    else
    {
        return ReducedBoardView(BoardRefView(m_game, PlayerType::PLAYER2));
    }
}

CurrentPlayerBoardRefView Board::GetCurPlayerStateRefView() const
{
    if (m_game.GetCurrentPlayer()->playerType != m_playerType)
    {
        throw std::runtime_error("current player does not match.");
    }

    return CurrentPlayerBoardRefView(m_game);
}

std::tuple<PlayState, PlayState> Board::ApplyAction(ActionParams& params) const
{
    return m_game.PerformAction(params);
}

Game& Board::RevealHiddenInfoForSimulation() const
{
    return m_game;
}
}  // namespace RosettaStone::PlayMode