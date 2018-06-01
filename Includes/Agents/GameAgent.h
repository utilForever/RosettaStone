/*************************************************************************
> File Name: GameAgent.h
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Hearthstone Game Agent
> Created Time: 2017/09/26
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_GAME_AGENT_H
#define HEARTHSTONEPP_GAME_AGENT_H

#include <Agents/AgentStructures.h>
#include <Commons/Constants.h>
#include <Tasks/TaskAgent.h>
#include <Tasks/Tasks.h>

#include <array>
#include <functional>
#include <thread>

namespace Hearthstonepp
{
class GameAgent
{
 public:
    // Constant expression of User type checking
    template <typename T>
    static constexpr inline bool isUser = std::is_same_v<std::decay_t<T>, User>;

    template <typename UserT, typename = std::enable_if_t<isUser<UserT>>>
    GameAgent(UserT&& user1, UserT&& user2)
        : m_current(std::forward<UserT>(user1)),
          m_opponent(std::forward<UserT>(user2))
    {
        // Do Nothing
    }

    std::thread StartAgent();

    // Get TaskMeta From TaskAgent
    void GetTaskMeta(TaskMeta& meta);
    // Write TaskMeta to TaskAgent, using side channel as default
    void WriteSyncBuffer(TaskMeta&& data, bool sideChannel = true);

 private:
    User m_current;
    User m_opponent;

    TaskAgent m_taskAgent;

    bool IsGameEnd();

    void BeginPhase();
    // Return true if game end
    bool MainPhase();
    void FinalPhase();

    // Ready for main phase, draw, modify mana, clear attacked vector
    void MainReady();
    // Select main menu and call action method, return true if game end
    bool MainMenu();
    // Use card such as summon minion, use spell etc.
    void MainUseCard();
    // Combat with other minion or hero.
    void MainCombat();

    std::array<std::function<void(GameAgent&)>, GAME_MAIN_MENU_SIZE - 1>
        m_mainMenuFuncs = {
            &GameAgent::MainUseCard,
            &GameAgent::MainCombat,
    };
};
}  // namespace Hearthstonepp

#endif