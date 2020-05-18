// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_PLAYMODE_BOARD_VIEW_HPP
#define ROSETTASTONE_PLAYMODE_BOARD_VIEW_HPP

#include <Rosetta/PlayMode/Views/Types/Player.hpp>
#include <Rosetta/PlayMode/Views/Types/UnknownCards.hpp>

namespace RosettaStone::PlayMode
{
//!
//! \brief BoardView class.
//!
//! This class parses game information from board ref view to restore the game.
//!
class BoardView
{
 public:
    //! Parses game information from \p gameState.
    //! \param gameState The board ref view to restore the game.
    //! \param p1Unknown The unknown card information of player 1.
    //! \param p2Unknown The unknown card information of player 2.
    void Parse(BoardRefView gameState,
               Views::Types::UnknownCardsInfo& p1Unknown,
               Views::Types::UnknownCardsInfo& p2Unknown);

    //! Returns the turn of the game.
    //! \return The turn of the game.
    int GetTurn() const;

    //! Returns The current player of the game.
    //! \return The current player of the game.
    PlayerType GetCurrentPlayer() const;

    //! Returns the player 1 of the game.
    //! \return The player 1 of the game.
    const Views::Types::Player& GetPlayer1() const;

    //! Returns the player 2 of the game.
    //! \return The player 2 of the game.
    const Views::Types::Player& GetPlayer2() const;

 private:
    int m_turn = 0;
    PlayerType m_curPlayer = PlayerType::INVALID;
    Views::Types::Player m_player1{};
    Views::Types::Player m_player2{};
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_BOARD_VIEW_HPP
