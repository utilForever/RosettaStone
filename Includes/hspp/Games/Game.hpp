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
//! This class stores Hearthstone game states which consists of information of
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

    //! Part of the game state.
    void BeginFirst();

    //! Part of the game state.
    void BeginShuffle();

    //! Part of the game state.
    void BeginDraw();

    //! Part of the game state.
    void BeginMulligan();

    //! Part of the game state.
    void MainBegin();

    //! Part of the game state.
    void MainReady();

    //! Part of the game state.
    void MainStartTriggers();

    //! Part of the game state.
    void MainResource();

    //! Part of the game state.
    void MainDraw();

    //! Part of the game state.
    void MainStart();

    //! Part of the game state.
    void MainAction();

    //! Part of the game state.
    void MainCombat();

    //! Part of the game state.
    void MainEnd();

    //! Part of the game state.
    void MainCleanUp();

    //! Part of the game state.
    void MainNext();

    //! Part of the game state.
    void FinalWrapUp();

    //! Part of the game state.
    void FinalGameOver();

    //! Starts the game.
    void StartGame();

    Step step = Step::INVALID;
    Step nextStep = Step::INVALID;

 private:
    std::array<Player, 2> m_players;

    PlayerType m_startPlayer = PlayerType::RANDOM;
    Player* m_firstPlayer = nullptr;
    Player* m_currentPlayer = nullptr;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_GAME_HPP