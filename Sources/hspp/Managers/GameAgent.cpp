// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Cards/Cards.h>
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
#include <hspp/Tasks/MetaData.h>
#include <hspp/Tasks/Requirement.h>
#include <hspp/Tasks/TaskWrapper.h>

#include <random>

namespace Hearthstonepp
{
GameAgent::GameAgent(CardClass player1Class, CardClass player2Class,
                     size_t firstPlayer)
    : m_firstPlayer(firstPlayer), m_currentPlayer(firstPlayer)
{
    m_player1.AddHeroAndPower(
        Cards::GetInstance().GetHeroCard(player1Class),
        Cards::GetInstance().GetDefaultHeroPower(player1Class));
    m_player2.AddHeroAndPower(
        Cards::GetInstance().GetHeroCard(player2Class),
        Cards::GetInstance().GetDefaultHeroPower(player2Class));

    m_player1.SetGameAgent(this);
    m_player2.SetGameAgent(this);

    m_player1.SetOpponent(&m_player2);
    m_player2.SetOpponent(&m_player1);
}

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

Player& GameAgent::GetFirstPlayer()
{
    return m_firstPlayer == PLAYER1 ? m_player1 : m_player2;
}

void GameAgent::SetFirstPlayer(size_t playerNum)
{
    m_firstPlayer = playerNum;
}

Player& GameAgent::GetCurrentPlayer()
{
    return m_currentPlayer == PLAYER1 ? m_player1 : m_player2;
}

void GameAgent::SetCurrentPlayer(size_t playerNum)
{
    m_currentPlayer = playerNum;
}

Player& GameAgent::GetOpponentPlayer()
{
    return m_currentPlayer == PLAYER1 ? m_player2 : m_player1;
}

MetaData GameAgent::RunTask(Player& player, ITask& task)
{
    return task.Run(player);
}

MetaData GameAgent::RunTask(Player& player, ITask&& task)
{
    return task.Run(player);
}

void GameAgent::NotifyToTaskAgent(TaskMeta& meta, bool sideChannel)
{
    m_taskAgent.Notify(meta, sideChannel);
}

void GameAgent::NotifyToTaskAgent(TaskMeta&& meta, bool sideChannel)
{
    m_taskAgent.Notify(std::move(meta), sideChannel);
}

TaskAgent& GameAgent::GetTaskAgent()
{
    return m_taskAgent;
}

void GameAgent::BeginPhase()
{
    std::random_device rd;
    std::default_random_engine gen(rd());

    // Get random number: zero or one.
    std::uniform_int_distribution<int> bin(0, 1);

    SetFirstPlayer(PLAYER1);
    SetCurrentPlayer(PLAYER1);

    // Swap user with 50% probability
    if (bin(gen) == 1)
    {
        SetFirstPlayer(PLAYER2);
        SetCurrentPlayer(PLAYER2);
    }

    const auto success = [](const TaskMeta& meta) {
        return meta.status == MetaData::MULLIGAN_SUCCESS;
    };

    TaskMeta meta;

    // Task list of begin phase
    // 1. Both players shuffle the deck.
    // 2. Both players draw cards from the deck.
    // NOTE: The player going first will be given 3 cards
    // while the player going second will be given 4 cards.
    // 3. Both players enter the mulligan stage.
    // NOTE: Each player is shown their randomly selected starting hand and is
    // given the option to redraw as many of those cards as they like. Only one
    // redraw of the selected cards is allowed; there is no chance to redraw
    // again after seeing the results.
    // 4. The player going second receives "The Coin" card.
    // NOTE: The Coin is a special uncollectible spell card granted at the start
    // of each game to whichever player is selected to go second.
    m_taskAgent.Run(meta, GetFirstPlayer(),
                    BasicTasks::PlayerSettingTask(m_taskAgent));

    m_taskAgent.RunMulti(
        meta, GetFirstPlayer(), BasicTasks::ShuffleTask(),
        BasicTasks::DrawTask(NUM_DRAW_CARDS_AT_START_FIRST),
        BasicTasks::DoUntil(BasicTasks::MulliganTask(m_taskAgent), success),
        BasicTasks::BriefTask());

    m_taskAgent.RunMulti(
        meta, GetFirstPlayer().GetOpponent(), BasicTasks::ShuffleTask(),
        BasicTasks::DrawTask(NUM_DRAW_CARDS_AT_START_SECOND),
        BasicTasks::DoUntil(BasicTasks::MulliganTask(m_taskAgent), success),
        BasicTasks::BriefTask(),
        BasicTasks::DrawCardTask(
            Cards::GetInstance().FindCardByName("The Coin")));
}

bool GameAgent::MainPhase()
{
    // Ready for main phase
    PrepareMainPhase();

    // NOTE: It returns isGameEnd flag
    return ProcessMainMenu();
}

void GameAgent::FinalPhase()
{
    TaskMeta meta;
    m_taskAgent.Run(meta, GetCurrentPlayer(), BasicTasks::GameEndTask());
}

void GameAgent::PrepareMainPhase()
{
    // increase total mana, initialize attack count
    TaskMeta meta;

    // Task list of prepare main phase
    // 1. Draw a card from deck.
    // 2. Gain a new mana crystal. (increase maximum mana by 1)
    // NOTE: A player can never have more than 10 maximum mana.
    // 3. Refill all of their non-overloaded mana crystals.
    // 4. Initialize attack count of minions and hero.
    m_taskAgent.RunMulti(
        meta, GetCurrentPlayer(), BasicTasks::DrawTask(1),
        BasicTasks::ModifyManaTask(ManaOperator::ADD, ManaType::TOTAL, 1),
        BasicTasks::ModifyManaTask(ManaOperator::SET, ManaType::EXIST,
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
    m_taskAgent.Run(meta, GetCurrentPlayer(), BasicTasks::BriefTask());

    // Get menu response from game interface
    BasicTasks::Requirement(TaskID::SELECT_MENU, m_taskAgent)
        .Interact(m_player1.id, meta);

    // Interface pass menu by the status of TaskMeta
    const auto menu = static_cast<status_t>(meta.status);

    if (menu == GAME_MAIN_MENU_SIZE - 1)
    {
        // End main end phase
        SetCurrentPlayer(m_currentPlayer == PLAYER1 ? PLAYER2 : PLAYER1);
    }
    else
    {
        if (menu < GAME_MAIN_MENU_SIZE - 1)
        {
            // Call action method
            m_mainMenuFuncs[menu](*this);
        }

        // NOTE: It returns isGameEnd flag
        return ProcessMainMenu();
    }

    return false;
}

void GameAgent::PlayCard()
{
    TaskMeta meta;
    m_taskAgent.Run(meta, GetCurrentPlayer(),
                    BasicTasks::PlayCardTask(m_taskAgent));
}

void GameAgent::Combat()
{
    TaskMeta meta;
    m_taskAgent.Run(meta, GetCurrentPlayer(),
                    BasicTasks::CombatTask(m_taskAgent, nullptr, nullptr));
}

bool GameAgent::IsGameOver() const
{
    const size_t healthCurrent = m_player1.hero->health;
    const size_t healthOpponent = m_player2.hero->health;

    return healthCurrent <= 0 || healthOpponent <= 0;
}
}  // namespace Hearthstonepp