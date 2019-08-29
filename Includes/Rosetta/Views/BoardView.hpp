// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_BOARD_VIEW_HPP
#define ROSETTASTONE_BOARD_VIEW_HPP

#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Views/Types/Player.hpp>

namespace RosettaStone
{
//!
//! \brief BoardView class.
//!
//!
class BoardView
{
 private:
    int m_turn;
    PlayerType m_curPlayer;
    ViewTypes::Player m_player1;
    ViewTypes::Player m_player2;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_BOARD_VIEW_HPP
