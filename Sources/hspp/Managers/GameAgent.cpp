// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Cards/Cards.hpp>
#include <hspp/Managers/GameAgent.hpp>
#include <hspp/Tasks/MetaData.hpp>
#include <hspp/Tasks/PlayerTasks/BriefTask.hpp>
#include <hspp/Tasks/PlayerTasks/CombatTask.hpp>
#include <hspp/Tasks/PlayerTasks/GameEndTask.hpp>
#include <hspp/Tasks/PlayerTasks/MulliganTask.hpp>
#include <hspp/Tasks/PlayerTasks/PlayCardTask.hpp>
#include <hspp/Tasks/PlayerTasks/PlayerSettingTask.hpp>
#include <hspp/Tasks/Requirement.hpp>
#include <hspp/Tasks/SimpleTasks/DrawTask.hpp>
#include <hspp/Tasks/SimpleTasks/InitAttackCountTask.hpp>
#include <hspp/Tasks/SimpleTasks/ModifyManaTask.hpp>
#include <hspp/Tasks/SimpleTasks/ShuffleTask.hpp>
#include <hspp/Tasks/TaskWrapper.hpp>

#include <random>

using namespace Hearthstonepp::PlayerTasks;
using namespace Hearthstonepp::SimpleTasks;

namespace Hearthstonepp
{
GameAgent::GameAgent(CardClass p1Class, CardClass p2Class, Policy* p1Policy,
                     Policy* p2Policy, PlayerType firstPlayer)
    : m_game(p1Class, p2Class, firstPlayer)
{
    m_game.GetPlayer1().SetPolicy(p1Policy);
    m_game.GetPlayer2().SetPolicy(p2Policy);
}

GameAgent::GameAgent(const Game& game, Policy* p1Policy, Policy* p2Policy)
    : m_game(game)
{
    m_game.GetPlayer1().SetPolicy(p1Policy);
    m_game.GetPlayer2().SetPolicy(p2Policy);
}

GameAgent::GameAgent(Game&& game, Policy* p1Policy, Policy* p2Policy)
    : m_game(std::move(game))
{
    m_game.GetPlayer1().SetPolicy(p1Policy);
    m_game.GetPlayer2().SetPolicy(p2Policy);
}

GameResult GameAgent::Start()
{
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

    return GameResult();
}

Game& GameAgent::GetGame()
{
    return m_game;
}

const Game& GameAgent::GetGame() const
{
    return m_game;
}

void GameAgent::BeginPhase()
{
    std::random_device rd;
    std::default_random_engine gen(rd());

    // Get random number: zero or one.
    std::uniform_int_distribution<int> bin(0, 1);

    m_game.SetFirstPlayer(PlayerType::PLAYER1);
    m_game.SetCurrentPlayer(PlayerType::PLAYER1);

    // Swap user with 50% probability
    if (bin(gen) == 1)
    {
        m_game.SetFirstPlayer(PlayerType::PLAYER2);
        m_game.SetCurrentPlayer(PlayerType::PLAYER2);
    }

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
    Task::Run(m_game.GetFirstPlayer(), PlayerSettingTask());

    Task::RunMulti(m_game.GetFirstPlayer(), ShuffleTask(),
                   DrawTask(NUM_DRAW_CARDS_AT_START_FIRST),
                   DoUntil(MulliganTask(), MetaData::MULLIGAN_SUCCESS));

    Task::RunMulti(
        m_game.GetFirstPlayer().GetOpponent(), ShuffleTask(),
        DrawTask(NUM_DRAW_CARDS_AT_START_SECOND),
        DoUntil(MulliganTask(), MetaData::MULLIGAN_SUCCESS),
        DrawCardTask(Cards::GetInstance().FindCardByName("The Coin")));
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
    Task::Run(m_game.GetCurrentPlayer(), GameEndTask());
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
    Task::RunMulti(m_game.GetCurrentPlayer(), DrawTask(1),
                   ModifyManaTask(ManaOperator::ADD, ManaType::MAXIMUM, 1),
                   ModifyManaTask(ManaOperator::SET, ManaType::AVAILABLE,
                                  m_player1.GetMaximumMana() + 1),
                   InitAttackCountTask());
}

bool GameAgent::ProcessMainMenu()
{
    // Check before starting main phase
    if (IsGameOver())
    {
        return true;
    }

    TaskMeta meta;
    m_taskAgent.Run(meta, GetCurrentPlayer(), BriefTask());

    // Get menu response from game interface
    Requirement(TaskID::SELECT_MENU, m_taskAgent)
        .Interact(m_player1.GetID(), meta);

    // Interface pass menu by the status of TaskMeta
    const auto menu = static_cast<status_t>(meta.GetStatus());

    if (menu == GAME_MAIN_MENU_SIZE - 1)
    {
        // End main end phase
        SetCurrentPlayer(m_currentPlayer == PlayerType::PLAYER2
                             ? PlayerType::PLAYER1
                             : PlayerType::PLAYER2);
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
    m_taskAgent.Run(meta, GetCurrentPlayer(), PlayCardTask(m_taskAgent));
}

void GameAgent::Combat()
{
    TaskMeta meta;
    m_taskAgent.Run(meta, GetCurrentPlayer(),
                    CombatTask(m_taskAgent, nullptr, nullptr));
}

bool GameAgent::IsGameOver() const
{
    const int healthCurrent = m_player1.GetHero()->health;
    const int healthOpponent = m_player2.GetHero()->health;

    return healthCurrent <= 0 || healthOpponent <= 0;
}
}  // namespace Hearthstonepp