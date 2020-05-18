// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Rosetta/PlayMode/Views/BoardRefView.hpp>
#include <Rosetta/PlayMode/Views/BoardView.hpp>

namespace RosettaStone::PlayMode
{
void BoardView::Parse(BoardRefView gameState,
                      Views::Types::UnknownCardsInfo& p1Unknown,
                      Views::Types::UnknownCardsInfo& p2Unknown)
{
    m_turn = gameState.GetTurn();
    m_curPlayer = gameState.GetCurrentPlayer();
    m_player1.Parse(gameState, PlayerType::PLAYER1, p1Unknown);
    m_player2.Parse(gameState, PlayerType::PLAYER2, p2Unknown);
}

int BoardView::GetTurn() const
{
    return m_turn;
}

PlayerType BoardView::GetCurrentPlayer() const
{
    return m_curPlayer;
}

const Views::Types::Player& BoardView::GetPlayer1() const
{
    return m_player1;
}

const Views::Types::Player& BoardView::GetPlayer2() const
{
    return m_player2;
}
}  // namespace RosettaStone::PlayMode