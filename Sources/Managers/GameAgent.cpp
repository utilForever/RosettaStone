/*************************************************************************
> File Name: GameAgent.cpp
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Hearthstone Game Agent
> Created Time: 2017/09/26
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#include <Managers/GameAgent.h>
#include <Tasks/BasicTasks/BriefTask.h>
#include <Tasks/BasicTasks/CombatTask.h>
#include <Tasks/BasicTasks/DrawTask.h>
#include <Tasks/BasicTasks/GameEndTask.h>
#include <Tasks/BasicTasks/ModifyManaTask.h>
#include <Tasks/BasicTasks/MulliganTask.h>
#include <Tasks/BasicTasks/PlayCardTask.h>
#include <Tasks/BasicTasks/PlayerSettingTask.h>
#include <Tasks/BasicTasks/Requirement.h>
#include <Tasks/BasicTasks/ShuffleTask.h>
#include <Tasks/BasicTasks/SwapPlayerTask.h>
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
    return m_player1;
}

Player& GameAgent::GetPlayer2()
{
    return m_player2;
}

MetaData GameAgent::RunTask(ITask& task, Player& player1, Player& player2)
{
    return task.Run(player1, player2);
}

MetaData GameAgent::RunTask(ITask&& task, Player& player1, Player& player2)
{
    return task.Run(player1, player2);
}

TaskAgent& GameAgent::GetTaskAgent()
{
    return m_taskAgent;
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
        BasicTasks::SwapPlayerTask().Run(m_player1, m_player2);
    }

    auto success = [](const TaskMeta& meta) {
        return meta.status == MetaData::MULLIGAN_SUCCESS;
    };

    TaskMeta meta;
    // BeginPhase Task List
    m_taskAgent.RunMulti(
        meta, m_player1, m_player2, BasicTasks::PlayerSettingTask(m_taskAgent),
        BasicTasks::DoBothPlayer(BasicTasks::ShuffleTask()),
        BasicTasks::DoBothPlayer(BasicTasks::DrawTask(NUM_BEGIN_DRAW, m_taskAgent)),
        BasicTasks::BriefTask(),
        BasicTasks::DoUntil(BasicTasks::MulliganTask(m_taskAgent), success),
        BasicTasks::SwapPlayerTask(), BasicTasks::BriefTask(),
        BasicTasks::DoUntil(BasicTasks::MulliganTask(m_taskAgent), success),
        BasicTasks::SwapPlayerTask());

    // TODO: Coin for later user
    // m_player2.hand.push_back(new Card());
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
    m_taskAgent.Run(meta, m_player1, m_player2, BasicTasks::GameEndTask());
}

void GameAgent::MainReady()
{
    // MainReady : Draw, ModifyMana, Clear field character attackableCount
    TaskMeta meta;
    m_taskAgent.RunMulti(
        meta, m_player1, m_player2, BasicTasks::DrawTask(1, m_taskAgent),
        BasicTasks::ModifyManaTask(NumMode::ADD, ManaMode::TOTAL, 1),
        BasicTasks::ModifyManaByRef(NumMode::SET, ManaMode::EXIST,
                                    m_player1.totalMana));

    for (auto &character : m_player1.field)
    {
        if (character->gameTags[+GameTag::FROZEN] == 1)
        {
            character->gameTags[+GameTag::FROZEN] = 0;
        }
        else if (character->gameTags[+GameTag::FROZEN] == 2)
        {
            character->gameTags[+GameTag::FROZEN] = 1;
            character->attackableCount = 0;
            continue;
        }

        character->attackableCount = character->gameTags[+GameTag::WINDFURY] ? 2 : 1;
    }
}

bool GameAgent::MainMenu()
{
    // Check before starting main phase
    if (IsGameEnd())
    {
        return true;
    }

    TaskMeta meta;
    m_taskAgent.Run(meta, m_player1, m_player2, BasicTasks::BriefTask());
    // Get Menu Response from GameInterface
    BasicTasks::Requirement(TaskID::SELECT_MENU, m_taskAgent)
        .Interact(m_player1.id, meta);

    // Interface pass menu by status of TaskMeta
    status_t menu = static_cast<status_t>(meta.status);

    if (menu == GAME_MAIN_MENU_SIZE - 1)
    {
        // Main End phase
        m_taskAgent.Run(meta, m_player1, m_player2,
                        BasicTasks::SwapPlayerTask());
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
    TaskMeta meta;
    m_taskAgent.Run(meta, m_player1, m_player2,
                    BasicTasks::PlayCardTask(m_taskAgent));
}

void GameAgent::MainCombat()
{
    TaskMeta meta;
    m_taskAgent.Run(meta, m_player1, m_player2,
                    BasicTasks::CombatTask(m_taskAgent));
}

bool GameAgent::IsGameEnd()
{
    size_t healthCurrent = m_player1.hero->health;
    size_t healthOpponent = m_player2.hero->health;

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