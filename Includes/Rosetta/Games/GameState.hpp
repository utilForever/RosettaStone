// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_GAME_STATE_HPP
#define ROSETTASTONE_GAME_STATE_HPP

#include <Rosetta/Models/Player.hpp>

namespace RosettaStone
{
//!
//! \brief GameState class.
//!
//! This class stores data related the game.
//!
class GameState
{
 public:
    //! Returns the player controlling the current turn.
    //! \return The player controlling the current turn.
    Player& GetCurrentPlayer();

    //! Gets the player controlling the current turn.
    //! \return The player controlling the current turn.
    const Player& GetCurrentPlayer() const;

    //! Returns the opponent player.
    //! \return The opponent player.
    Player& GetOpponentPlayer();

    //! Returns the opponent player.
    //! \return The opponent player.
    const Player& GetOpponentPlayer() const;

    //! Swaps the player for the next turn.
    void SwapPlayer();

    //! Gets the turn of the game.
    //! \return The turn of the game.
    int GetTurn() const;

    //! Sets the turn of the game.
    //! \param turn The turn of the game.
    void SetTurn(int turn);

    //! Increases the turn of the game.
    void IncreaseTurn();

 private:
    std::array<Player, 2> m_players;
    PlayerType m_curPlayer = PlayerType::INVALID;

    std::size_t m_turn = 0;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_GAME_STATE_HPP
