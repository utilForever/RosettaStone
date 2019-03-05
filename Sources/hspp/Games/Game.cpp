// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Cards/Cards.hpp>
#include <hspp/Games/Game.hpp>

#include <random>

namespace Hearthstonepp
{
Game::Game(CardClass p1Class, CardClass p2Class, PlayerType startPlayer)
    : m_startPlayer(startPlayer)
{
    m_player1.AddHeroAndPower(
        Cards::GetInstance().GetHeroCard(p1Class),
        Cards::GetInstance().GetDefaultHeroPower(p1Class));
    m_player2.AddHeroAndPower(
        Cards::GetInstance().GetHeroCard(p2Class),
        Cards::GetInstance().GetDefaultHeroPower(p2Class));

    m_player1.SetOpponent(&m_player2);
    m_player2.SetOpponent(&m_player1);
}

Player& Game::GetPlayer1()
{
    return m_player1;
}

Player& Game::GetPlayer2()
{
    return m_player2;
}

Player& Game::GetCurrentPlayer()
{
    return *m_currentPlayer;
}

Player& Game::GetOpponentPlayer()
{
    return m_currentPlayer->GetOpponent();
}

void Game::BeginFirst()
{
    // Do nothing
}

void Game::BeginShuffle()
{
    // Do nothing
}

void Game::BeginDraw()
{
    // Do nothing
}

void Game::BeginMulligan()
{
    // Do nothing
}

void Game::MainBegin()
{
    // Do nothing
}

void Game::MainReady()
{
    // Do nothing
}

void Game::MainStartTriggers()
{
    // Do nothing
}

void Game::MainResource()
{
    // Do nothing
}

void Game::MainDraw()
{
    // Do nothing
}

void Game::MainStart()
{
    // Do nothing
}

void Game::MainAction()
{
    // Do nothing
}

void Game::MainCombat()
{
    // Do nothing
}

void Game::MainEnd()
{
    // Do nothing
}

void Game::MainCleanUp()
{
    // Do nothing
}

void Game::MainNext()
{
    // Do nothing
}

void Game::FinalWrapUp()
{
    // Do nothing
}

void Game::FinalGameOver()
{
    // Do nothing
}

void Game::StartGame()
{
    // Determine first player
    switch (m_startPlayer)
    {
        case PlayerType::RANDOM:
        {
            std::random_device rd;
            std::uniform_int_distribution<int> dist(0, 1);

            const std::size_t idx = dist(rd);
            if (idx == 0)
            {
                m_firstPlayer = &m_player1;
            }
            else
            {
                m_firstPlayer = &m_player2;
            }
            break;
        }
        case PlayerType::PLAYER1:
            m_firstPlayer = &m_player1;
            break;
        case PlayerType::PLAYER2:
            m_firstPlayer = &m_player2;
            break;
    }
    m_currentPlayer = m_firstPlayer;
}
}  // namespace Hearthstonepp