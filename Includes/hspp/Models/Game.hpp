// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_GAME_HPP
#define HEARTHSTONEPP_GAME_HPP

#include <hspp/Commons/Constants.hpp>
#include <hspp/Enums/CardEnums.hpp>
#include <hspp/Models/Player.hpp>

namespace Hearthstonepp
{
//!
//! \brief Game class.
//!
//! This class stores Hearthstone game states which consists of informations of
//! both players.
//!
class Game
{
 public:
    //! Constructs account with given \p p1Class, \p p2Class and \p firstPlayer.
    //! \param p1Class The class of player 1.
    //! \param p2Class The class of player 2.
    //! \param startPlayer The starting player.
    Game(CardClass p1Class, CardClass p2Class,
         PlayerType startPlayer = PlayerType::RANDOM);

    //! Copy Constructor
    Game(const Game&) = delete;

    //! Move Constructor
    Game(Game&&) = delete;

    //! Copy assignment
    Game& operator=(const Game&) = delete;

    //! Move assignment
    Game& operator=(Game&&) = delete;

    //! Returns the first player.
    //! \return The first player.
    Player& GetPlayer1();

    //! Returns the second player.
    //! \return The second player.
    Player& GetPlayer2();

    //! Returns the player controlling the current turn.
    //! \return The player controlling the current turn.
    Player& GetCurrentPlayer();

    //! Returns the opponent player.
    //! \return The opponent player.
    Player& GetOpponentPlayer();

 private:
    Player m_player1;
    Player m_player2;

    PlayerType m_startPlayer = PlayerType::RANDOM;
    Player* m_firstPlayer = nullptr;
    Player* m_currentPlayer = nullptr;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_GAME_HPP