// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_GAME_AGENT_HPP
#define HEARTHSTONEPP_GAME_AGENT_HPP

#include <hspp/Accounts/Player.hpp>
#include <hspp/Commons/Constants.hpp>
#include <hspp/Game/Game.hpp>
#include <hspp/Tasks/Tasks.hpp>

#include <array>
#include <functional>
#include <thread>

namespace Hearthstonepp
{
struct GameResult
{
};

//!
//! \brief GameAgent class.
//!
//! This class manages Hearthstone game and saves information of both players
//! playing the game. Also, it stores task agent manages the task.
//!
class GameAgent
{
 public:
    //! Constructs game with given \p p1Class, \p p2Class and \p firstPlayer.
    //! \param p1Class The class of player 1.
    //! \param p2Class The class of player 2.
    //! \param p1Policy The game playing policy for player1.
    //! \param p2Policy The game playing policy for player2.
    //! \param firstPlayer The first player who starts turn first.
    GameAgent(CardClass p1Class, CardClass p2Class, IPolicy* p1Policy,
              IPolicy* p2Policy, PlayerType firstPlayer = PlayerType::PLAYER1);

    //! Starts the game agent.
    //! \return The thread that plays the game.
    GameResult Start();

    //! Get game structure.
    //! \return The game structure.
    Game& GetGame();

    //! Get game structure.
    //! \return The game structure.
    const Game& GetGame() const;

 private:
    //! Returns whether the game is over.
    //! \return true if the game is over, and false otherwise.
    bool IsGameOver();

    //! Processes the begin phase of the game.
    void BeginPhase();

    //! Processes the main phase of the game.
    //! \return true if the game is over, and false otherwise.
    bool MainPhase();

    //! Processes the final phase of the game.
    void FinalPhase();

    //! Prepares to handle the main phase: draw card, modify mana and clear
    //! attacked characters.
    void PrepareMainPhase();

    //! Processes command in main menu and calls action.
    //! \return return true if the game is over, and false otherwise.
    bool ProcessMainMenu();

    //! Plays card such as minion, weapon and spell.
    void PlayCard();

    //! Combats with other minion or hero.
    void Combat();

    Game m_game;

    std::array<std::function<void(GameAgent&)>, GAME_MAIN_MENU_SIZE - 1>
        m_mainMenuFuncs = {
            &GameAgent::PlayCard,
            &GameAgent::Combat,
        };
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_GAME_AGENT_HPP