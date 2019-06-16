// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BOARD_REF_VIEW_HPP
#define ROSETTASTONE_BOARD_REF_VIEW_HPP

#include <Rosetta/Games/Game.hpp>

namespace RosettaStone
{
//!
//! \brief BoardRefView class.
//!
//! This class is an simple implementation of board reference view.
//! It is based on peter1591's hearthstone-ai repository.
//! References: https://github.com/peter1591/hearthstone-ai
//!
class BoardRefView
{
 public:
    BoardRefView(Game& game, PlayerType type);

    PlayerType GetType() const;
    int GetTurn() const;
    Player& GetCurrentPlayer() const;

 private:
    Game& m_game;
    PlayerType m_type;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_BOARD_REF_VIEW_HPP
