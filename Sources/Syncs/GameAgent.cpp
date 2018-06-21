/*************************************************************************
> File Name: GameAgent.cpp
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Hearthstone Game Agent
> Created Time: 2017/09/26
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#include <Syncs/GameAgent.h>
#include <Tasks/BasicTask.h>
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

void GameAgent::Process(Player& player, Task t)
{
    TaskMeta meta;

    if (player == m_current)
    {
        m_taskAgent.Run(t, meta, m_current, m_opponent, false);
    }
    else
    {
        m_taskAgent.Run(t, meta, m_opponent, m_current, false);
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
        m_taskAgent.Add(BasicTask::SwapPlayerTask());
    }

    auto untilMulliganSuccess = [](const TaskMeta& serialized) {
        return serialized.status == MetaData::MULLIGAN_SUCCESS;
    };

    // BeginPhase Task List
    m_taskAgent.Add(BasicTask::PlayerSettingTask());
    m_taskAgent.Add(BasicTask::DoBothPlayer(BasicTask::ShuffleTask()));
    m_taskAgent.Add(
        BasicTask::DoBothPlayer(BasicTask::DrawTask(NUM_BEGIN_DRAW)));
    m_taskAgent.Add(BasicTask::BriefTask());
    m_taskAgent.Add(BasicTask::DoUntil(BasicTask::MulliganTask(m_taskAgent),
                                       untilMulliganSuccess));
    m_taskAgent.Add(BasicTask::SwapPlayerTask());
    m_taskAgent.Add(BasicTask::BriefTask());
    m_taskAgent.Add(BasicTask::DoUntil(BasicTask::MulliganTask(m_taskAgent),
                                       untilMulliganSuccess));
    m_taskAgent.Add(BasicTask::SwapPlayerTask());

    TaskMeta meta;
    m_taskAgent.Run(meta, m_current, m_opponent);
    m_taskAgent.Clear();

    // TODO: Coin for later user
    m_opponent.hand.push_back(new Card());
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
    m_taskAgent.Run(BasicTask::GameEndTask(), meta, m_current, m_opponent);
}

void GameAgent::MainReady()
{
    // MainReady : Draw, ModifyMana, Clear vector `attacked`
    m_taskAgent.Add(BasicTask::DrawTask(1));
    m_taskAgent.Add(BasicTask::ModifyManaTask(BasicTask::NUM_ADD,
                                              BasicTask::MANA_TOTAL, 1));
    m_taskAgent.Add(BasicTask::ModifyManaByRef(
        BasicTask::NUM_SYNC, BasicTask::MANA_EXIST, m_current.totalMana));

    TaskMeta meta;
    m_taskAgent.Run(meta, m_current, m_opponent);
    m_taskAgent.Clear();

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
    m_taskAgent.Run(BasicTask::BriefTask(), meta, m_current, m_opponent);
    m_taskAgent.Run(BasicTask::SelectMenuTask(m_taskAgent), meta, m_current,
                    m_opponent);

    // Interface pass menu by status of TaskMeta
    TaskMeta::status_t menu = meta.status;

    if (menu == GAME_MAIN_MENU_SIZE - 1)
    {
        // Main End phase
        m_taskAgent.Run(BasicTask::SwapPlayerTask(), meta, m_current,
                        m_opponent);
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

void GameAgent::MainUseCard()
{
    // Read what kinds of card user wants to use
    TaskMeta meta;
    m_taskAgent.Run(BasicTask::SelectCardTask(m_taskAgent), meta, m_current,
                    m_opponent);

    if (meta.status == MetaData::SELECT_CARD_MINION)
    {
        using Require = FlatData::RequireSummonMinionTaskMeta;
        const auto& buffer = meta.GetConstBuffer();
        if (buffer != nullptr)
        {
            auto minion = flatbuffers::GetRoot<Require>(buffer.get());
            if (minion != nullptr)
            {
                m_taskAgent.Run(BasicTask::PlayCardTask(m_current, minion->position()),
                                meta, m_current, m_opponent);
            }
        }
    }
    else
    {
        // TODO : If else selected card is not minion
    }
}

void GameAgent::MainCombat()
{
    TaskMeta meta;
    m_taskAgent.Run(BasicTask::SelectTargetTask(m_taskAgent), meta, m_current,
                    m_opponent);

    using Require = FlatData::RequireTargetingTaskMeta;
    const auto& buffer = meta.GetConstBuffer();
    if (buffer != nullptr)
    {
        auto targeting = flatbuffers::GetRoot<Require>(buffer.get());
        if (targeting != nullptr)
        {
            m_taskAgent.Run(
                BasicTask::CombatTask(targeting->src(), targeting->dst()), meta,
                m_current, m_opponent);
        }
    }
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