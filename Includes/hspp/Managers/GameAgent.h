// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_GAME_AGENT_H
#define HEARTHSTONEPP_GAME_AGENT_H

#include <hspp/Accounts/Player.h>
#include <hspp/Commons/Constants.h>
#include <hspp/Tasks/TaskAgent.h>
#include <hspp/Tasks/Tasks.h>

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
    //! Constant expression to check if \tparam T is a Player type.
    template <typename T>
    static constexpr inline bool isPlayer =
        std::is_same_v<std::decay_t<T>, Player>;

    //! Constructs game agent with given \p player1 and \p player2.
    //! \tparam PlayerT Player type.
    //! \param player1 The first player.
    //! \param player2 The second player.
    template <typename PlayerT, typename = std::enable_if_t<isPlayer<PlayerT>>>
    GameAgent(PlayerT&& player1, PlayerT&& player2)
        : m_player1(std::forward<PlayerT>(player1)),
          m_player2(std::forward<PlayerT>(player2)),
          m_firstPlayer(m_player1),
          m_currentPlayer(m_player1)
    {
        // Do nothing
    }

    //! Starts the game agent.
    //! \return The thread that plays the game.
    std::thread Start();

    //! Returns task meta from task agent.
    //! \param meta A task meta that defines return status of task.
    void GetTaskMeta(TaskMeta& meta);

    //! Writes task meta to task agent using side channel as default.
    //! \param data A task meta data to write to task agent.
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
    Player& GetFirstPlayer() const;

    //! Returns the player controlling the current turn.
    //! \return The player controlling the current turn.
    Player& GetCurrentPlayer() const;

    //! Returns the opponent player.
    //! \return The opponent player.
    Player& GetOpponentPlayer();

    //! Runs the task with given \p task, \p player1 and \p player2.
    //! \param task The task to run (lvalue ref).
    //! \param player1 The first player.
    //! \param player2 The second player.
    //! \return The result of running the task.
    static MetaData RunTask(ITask& task, Player& player1, Player& player2);

    //! Runs the task with given \p task, \p player1 and \p player2.
    //! \param task The task to run (rvalue ref).
    //! \param player1 The first player.
    //! \param player2 The second player.
    //! \return The result of running the task.
    static MetaData RunTask(ITask&& task, Player& player1, Player& player2);

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

    Player& m_firstPlayer;
    Player& m_currentPlayer;

    TaskAgent m_taskAgent;

    std::array<std::function<void(GameAgent&)>, GAME_MAIN_MENU_SIZE - 1>
        m_mainMenuFuncs = {
            &GameAgent::PlayCard,
            &GameAgent::Combat,
        };
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_GAME_AGENT_H