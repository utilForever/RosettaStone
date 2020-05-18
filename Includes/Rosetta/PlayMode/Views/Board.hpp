// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_PLAYMODE_BOARD_HPP
#define ROSETTASTONE_PLAYMODE_BOARD_HPP

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Views/BoardRefView.hpp>

namespace RosettaStone::PlayMode
{
//!
//! \brief Board class.
//!
//! This class is a base class for creating the reduced board view or returning
//! the board ref view with method that applies the action.
//!
class Board
{
 public:
    //! Constructs board with given \p game and \p playerType.
    //! \param game The game context.
    //! \param playerType The view type of the board.
    Board(Game& game, PlayerType playerType);

    //! Copies the contents from reference \p rhs.
    //! \param rhs The source to copy the content.
    void RefCopyFrom(const Board& rhs);

    //! Returns the current player of the game.
    //! \return The current player of the game.
    Player* GetCurrentPlayer() const;

    //! Returns the view type of the board.
    //! \return the view type of the board.
    PlayerType GetViewType() const;

    //! Creates the reduced board view for the player type.
    //! \return The reduced board view that is created for the player type.
    ReducedBoardView CreateView() const;

    //! Returns the board ref view for the current player.
    //! \return The board ref view for the current player.
    CurrentPlayerBoardRefView GetCurPlayerStateRefView() const;

    //! Applies action with given \p params.
    //! \param params The parameter for action.
    //! \return The result of the game (player1 and player2).
    std::tuple<PlayState, PlayState> ApplyAction(ActionParams& params) const;

    //! Returns the game that is revealed hidden info for simulation.
    //! \return The game that is revealed hidden info for simulation.
    Game& RevealHiddenInfoForSimulation() const;

 private:
    Game& m_game;
    PlayerType m_playerType;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_BOARD_HPP
