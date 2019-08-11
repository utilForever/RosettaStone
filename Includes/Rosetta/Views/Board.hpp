// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_BOARD_HPP
#define ROSETTASTONE_BOARD_HPP

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Views/BoardRefView.hpp>

namespace RosettaStone
{
//!
//! \brief Board class.
//!
class Board
{
 public:
    Board(Game& game, PlayerType playerType);

    //! Copies the contents from reference \p rhs.
    //! \param rhs The source to copy the content.
    void RefCopyFrom(const Board& rhs);

    //! Returns the current player of the game.
    //! \return The current player of the game.
    Player& GetCurrentPlayer() const;

    //! Returns the view type of the board.
    //! \return the view type of the board.
    PlayerType GetViewType() const;

    ReducedBoardView CreateView() const;

    CurrentPlayerBoardRefView GetCurPlayerStateRefView() const;

    PlayState ApplyAction(ActionParams& params) const;

    const Game& RevealHiddenInfoForSimulation() const;

 private:
    Game& m_game;
    PlayerType m_playerType;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_BOARD_HPP
