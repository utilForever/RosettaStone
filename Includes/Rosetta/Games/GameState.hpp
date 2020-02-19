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
    struct GameStateInfo
    {
        std::string cardID;
        std::map<GameTag, int> gameTags;
    };

    //! Gets the turn of the game.
    //! \return The turn of the game.
    int GetTurn() const;

    //! Sets the turn of the game.
    //! \param turn The turn of the game.
    void SetTurn(int turn);

    //! Increases the turn of the game.
    void IncreaseTurn();

 private:
    std::size_t m_turn = 0;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_GAME_STATE_HPP
