// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Views/BoardRefView.hpp>

namespace RosettaStone
{
BoardRefView::BoardRefView(Game& game, PlayerType type)
    : m_game(game), m_type(type)
{
    // Do nothing
}

PlayerType BoardRefView::GetType() const
{
    return m_type;
}

int BoardRefView::GetTurn() const
{
    return m_game.GetTurn();
}

Player& BoardRefView::GetCurrentPlayer() const
{
    return m_game.GetCurrentPlayer();
}
}  // namespace RosettaStone