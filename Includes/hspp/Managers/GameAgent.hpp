// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_GAME_AGENT_HPP
#define HEARTHSTONEPP_GAME_AGENT_HPP

#include <hspp/Cards/Minion.hpp>
#include <hspp/Accounts/Player.hpp>
#include <hspp/Commons/Constants.hpp>
#include <hspp/Tasks/TaskAgent.hpp>
#include <hspp/Tasks/Tasks.hpp>

#include <array>
#include <functional>
#include <thread>

namespace Hearthstonepp
{
//!
//! \brief GameAgent class.
//!
//! This class manages Hearthstone game and saves information of both players
//! playing the game. Also, it stores task agent manages the task.
//!
class GameAgent
{
 public:
    //! Constructs account with given \p p1Class, \p p2Class and \p firstPlayer.
    //! \param p1Class The class of player 1.
    //! \param p2Class The class of player 2.
    //! \param firstPlayer The first player who starts turn first.
    GameAgent(CardClass p1Class, CardClass p2Class,
              PlayerType firstPlayer = PlayerType::PLAYER1);

    //! Starts the game agent.
    //! \return The thread that plays the game.
    std::thread Start();

    //! Returns task meta from task agent.
    //! \param meta A task meta that defines return status of task.
    void GetTaskMeta(TaskMeta& meta);

    //! Writes task meta to task agent using side channel as default.
    //! \param data A task meta to write to task agent.
    //! \param isUseSideChannel A variable that tells you whether to use side
    //! channel.
    void WriteSyncBuffer(TaskMeta&& data, bool isUseSideChannel = true);

    //! Returns the task agent.
    //! \return the task agent.
    TaskAgent& GetTaskAgent();

    //! Returns the first player.
    //! \return The first player.
    Player& GetPlayer1();

    //! Returns the second player.
    //! \return The second player.
    Player& GetPlayer2();

    //! Returns the first player.
    //! \return The first player.
    Player& GetFirstPlayer();

    //! Sets the first player.
    //! \param playerType The first player who starts turn first.
    void SetFirstPlayer(PlayerType playerType);

    //! Returns the player controlling the current turn.
    //! \return The player controlling the current turn.
    Player& GetCurrentPlayer();

    //! Sets the player controlling the current turn.
    //! \param playerType The player controlling the current turn.
    void SetCurrentPlayer(PlayerType playerType);

    //! Returns the opponent player.
    //! \return The opponent player.
    Player& GetOpponentPlayer();

    //! Runs the task with given \p player and \p task.
    //! \param player The player to run task.
    //! \param task The task to run (lvalue ref).
    //! \return The result of running the task.
    static MetaData RunTask(Player& player, ITask& task);

    //! Runs the task with given \p player and \p task.
    //! \param player The player to run task.
    //! \param task The task to run (rvalue ref).
    //! \return The result of running the task.
    static MetaData RunTask(Player& player, ITask&& task);

    //! Notifies a task meta to the task agent.
    //! \param meta A task meta to write to task agent (lvalue ref).
    //! \param sideChannel A variable that tells you whether to use side.
    void NotifyToTaskAgent(TaskMeta& meta, bool sideChannel = false);

    //! Notifies a task meta to the task agent.
    //! \param meta A task meta to write to task agent (lvalue ref).
    //! \param sideChannel A variable that tells you whether to use side.
    void NotifyToTaskAgent(TaskMeta&& meta, bool sideChannel = false);

    //! Kills a minion from field.
    //! \param minion A character to kill.
    void KillMinion(Minion& minion) const;

 private:
    //! Returns whether the game is over.
    //! \return true if the game is over, and false otherwise.
    bool IsGameOver() const;

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

    Player m_player1;
    Player m_player2;

    PlayerType m_firstPlayer;
    PlayerType m_currentPlayer;

    TaskAgent m_taskAgent;

    std::array<std::function<void(GameAgent&)>, GAME_MAIN_MENU_SIZE - 1>
        m_mainMenuFuncs = {
            &GameAgent::PlayCard,
            &GameAgent::Combat,
        };
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_GAME_AGENT_HPP