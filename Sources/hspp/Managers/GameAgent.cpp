// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Managers/GameAgent.h>
#include <hspp/Tasks/BasicTasks/BriefTask.h>
#include <hspp/Tasks/BasicTasks/CombatTask.h>
#include <hspp/Tasks/BasicTasks/DrawTask.h>
#include <hspp/Tasks/BasicTasks/GameEndTask.h>
#include <hspp/Tasks/BasicTasks/InitAttackCountTask.h>
#include <hspp/Tasks/BasicTasks/ModifyManaTask.h>
#include <hspp/Tasks/BasicTasks/MulliganTask.h>
#include <hspp/Tasks/BasicTasks/PlayCardTask.h>
#include <hspp/Tasks/BasicTasks/PlayerSettingTask.h>
#include <hspp/Tasks/BasicTasks/ShuffleTask.h>
#include <hspp/Tasks/BasicTasks/SwapPlayerTask.h>
#include <hspp/Tasks/MetaData.h>
#include <hspp/Tasks/Requirement.h>
#include <hspp/Tasks/TaskWrapper.h>

#include <random>

namespace Hearthstonepp
{
std::thread GameAgent::Start()
{
    auto flow = [this]() {
        BeginPhase();

        while (true)
        {
            const bool isGameEnd = MainPhase();
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

void GameAgent::WriteSyncBuffer(TaskMeta&& data, bool isUseSideChannel)
{
    m_taskAgent.Notify(std::move(data), isUseSideChannel);
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

    const auto success = [](const TaskMeta& meta) {
        return meta.status == MetaData::MULLIGAN_SUCCESS;
    };

    TaskMeta meta;
    // BeginPhase Task List
    m_taskAgent.RunMulti(
        meta, m_player1, m_player2, BasicTasks::PlayerSettingTask(m_taskAgent),
        BasicTasks::DoBothPlayer(BasicTasks::ShuffleTask()),
        BasicTasks::DoBothPlayer(
            BasicTasks::DrawTask(m_taskAgent, NUM_DRAW_CARDS_AT_START)),
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
    PrepareMainPhase();
    // ProcessMainMenu return isGameEnd flag
    return ProcessMainMenu();
}

void GameAgent::FinalPhase()
{
    TaskMeta meta;
    m_taskAgent.Run(meta, m_player1, m_player2, BasicTasks::GameEndTask());
}

void GameAgent::PrepareMainPhase()
{
    // PrepareMainPhase: Draw card, reset used mana,
    // increase total mana, initialize attack count
    TaskMeta meta;
    m_taskAgent.RunMulti(
        meta, m_player1, m_player2, BasicTasks::DrawTask(m_taskAgent, 1),
        BasicTasks::ModifyManaTask(NumMode::ADD, ManaMode::TOTAL, 1),
        BasicTasks::ModifyManaTask(NumMode::SET, ManaMode::EXIST,
                                   m_player1.totalMana + 1),
        BasicTasks::InitAttackCountTask());
}

bool GameAgent::ProcessMainMenu()
{
    // Check before starting main phase
    if (IsGameOver())
    {
        return true;
    }

    TaskMeta meta;
    m_taskAgent.Run(meta, m_player1, m_player2, BasicTasks::BriefTask());
    // Get Menu Response from GameInterface
    BasicTasks::Requirement(TaskID::SELECT_MENU, m_taskAgent)
        .Interact(m_player1.id, meta);

    // Interface pass menu by status of TaskMeta
    const status_t menu = static_cast<status_t>(meta.status);

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
        return ProcessMainMenu();
    }

    return false;
}

void GameAgent::PlayCard()
{
    TaskMeta meta;
    m_taskAgent.Run(meta, m_player1, m_player2,
                    BasicTasks::PlayCardTask(m_taskAgent));
}

void GameAgent::Combat()
{
    TaskMeta meta;
    m_taskAgent.Run(meta, m_player1, m_player2,
                    BasicTasks::CombatTask(m_taskAgent));
}

bool GameAgent::IsGameOver() const
{
    const size_t healthCurrent = m_player1.hero->health;
    const size_t healthOpponent = m_player2.hero->health;

    return healthCurrent <= 0 || healthOpponent <= 0;
}
}  // namespace Hearthstonepp