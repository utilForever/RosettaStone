/*************************************************************************
> File Name: GameAgent.cpp
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Hearthstone Game Agent
> Created Time: 2017/09/26
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#include <InGame/GameAgent.h>
#include <Tasks/BasicTasks/Brief.h>
#include <Tasks/BasicTasks/Combat.h>
#include <Tasks/BasicTasks/Draw.h>
#include <Tasks/BasicTasks/GameEnd.h>
#include <Tasks/BasicTasks/ModifyMana.h>
#include <Tasks/BasicTasks/Mulligan.h>
#include <Tasks/BasicTasks/PlayCard.h>
#include <Tasks/BasicTasks/PlayerSetting.h>
#include <Tasks/BasicTasks/Requirement.h>
#include <Tasks/BasicTasks/Shuffle.h>
#include <Tasks/BasicTasks/SwapPlayer.h>
#include <Tasks/BasicTasks/Wrapper.h>
#include <Tasks/MetaData.h>

#include <random>

namespace Hearthstonepp
{
std::thread GameAgent::StartAgent()
{
    auto flow = [this]() {
        BeginPhase();
        while (true)
        {
            bool isGameEnd = MainPhase();
            if (isGameEnd)
            {
                break;
            }
        }

        FinalPhase();
    };

    return std::thread(std::move(flow));
}

void GameAgent::GetTaskMeta(TaskMeta& meta)
{
    m_taskAgent.Read(meta);
}

void GameAgent::WriteSyncBuffer(TaskMeta&& data, bool sideChannel)
{
    m_taskAgent.Notify(std::move(data), sideChannel);
}

Player& GameAgent::GetPlayer1()
{
    return m_current;
}

Player& GameAgent::GetPlayer2()
{
    return m_opponent;
}

void GameAgent::Process(Player& player, const ITask& t)
{
    if (player == m_current)
    {
        t.Run(m_current, m_opponent);
    }
    else
    {
        t.Run(m_opponent, m_current);
    }
}

void GameAgent::BeginPhase()
{
    std::random_device rd;
    std::default_random_engine gen(rd());

    // get random number, zero or one.
    std::uniform_int_distribution<int> bin(0, 1);
    // swap user with 50% probability
    if (bin(gen) == 1)
    {
        SwapPlayerTask().Run(m_current, m_opponent);
    }

    auto success = [](const TaskMeta& meta) {
        return meta.status == MetaData::MULLIGAN_SUCCESS;
    };

    TaskMeta meta;
    // BeginPhase Task List
    m_taskAgent.Run(
        meta, m_current, m_opponent, PlayerSettingTask(),
        DoBothPlayer(ShuffleTask()), DoBothPlayer(DrawTask(NUM_BEGIN_DRAW)),
        BriefTask(), DoUntil(MulliganTask(m_taskAgent), success),
        SwapPlayerTask(), BriefTask(),
        DoUntil(MulliganTask(m_taskAgent), success), SwapPlayerTask());

    // TODO: Coin for later user
    // m_opponent.hand.push_back(new Card());
}

bool GameAgent::MainPhase()
{
    // Ready for main phase
    MainReady();
    // MainMenu return isGameEnd flag
    return MainMenu();
}

void GameAgent::FinalPhase()
{
    TaskMeta meta;
    m_taskAgent.Run(meta, m_current, m_opponent, GameEndTask());
}

void GameAgent::MainReady()
{
    // MainReady : Draw, ModifyMana, Clear vector `attacked`
    TaskMeta meta;
    m_taskAgent.Run(
        meta, m_current, m_opponent, DrawTask(1),
        ModifyManaTask(NumMode::ADD, ManaMode::TOTAL, 1),
        ModifyManaByRef(NumMode::SYNC, ManaMode::EXIST, m_current.totalMana));

    m_current.attacked.clear();
}

bool GameAgent::MainMenu()
{
    // Check before starting main phase
    if (IsGameEnd())
    {
        return true;
    }

    TaskMeta meta;
    m_taskAgent.Run(meta, m_current, m_opponent, BriefTask());
    Requirement(TaskID::SELECT_MENU, m_taskAgent).Interact(m_current.id, meta);

    // Interface pass menu by status of TaskMeta
    status_t menu = static_cast<status_t>(meta.status);

    if (menu == GAME_MAIN_MENU_SIZE - 1)
    {
        // Main End phase
        m_taskAgent.Run(meta, m_current, m_opponent, SwapPlayerTask());
    }
    else
    {
        if (menu < GAME_MAIN_MENU_SIZE - 1)
        {
            // call action method
            m_mainMenuFuncs[menu](*this);
        }
        // Recursion
        return MainMenu();
    }

    return false;
}

void GameAgent::MainPlayCard()
{
    // Read what kinds of card user wants to use
    TaskMeta meta;
    m_taskAgent.Run(meta, m_current, m_opponent, PlayCardTask(m_taskAgent));
}

void GameAgent::MainCombat()
{
    TaskMeta meta;
    m_taskAgent.Run(meta, m_current, m_opponent, CombatTask(m_taskAgent));
}

bool GameAgent::IsGameEnd()
{
    size_t healthCurrent = m_current.hero->health;
    size_t healthOpponent = m_opponent.hero->health;

    if (healthCurrent < 1 || healthOpponent < 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
}  // namespace Hearthstonepp