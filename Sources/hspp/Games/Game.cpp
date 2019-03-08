// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Cards/Cards.hpp>
#include <hspp/Games/Game.hpp>

#include <effolkronium/random.hpp>

#include <algorithm>

using Random = effolkronium::random_static;

namespace Hearthstonepp
{
Game::Game(GameConfig& gameConfig) : m_gameConfig(gameConfig)
{
    // Add hero and hero power
    GetPlayer1().AddHeroAndPower(
        Cards::GetInstance().GetHeroCard(gameConfig.player1Class),
        Cards::GetInstance().GetDefaultHeroPower(gameConfig.player1Class));
    GetPlayer2().AddHeroAndPower(
        Cards::GetInstance().GetHeroCard(gameConfig.player2Class),
        Cards::GetInstance().GetDefaultHeroPower(gameConfig.player2Class));

    // Set opponent player
    GetPlayer1().SetOpponent(&GetPlayer2());
    GetPlayer2().SetOpponent(&GetPlayer1());
}

Player& Game::GetPlayer1()
{
    return m_players[0];
}

Player& Game::GetPlayer2()
{
    return m_players[1];
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
    // Reverse card order in deck
    if (!m_gameConfig.doShuffle)
    {
        std::reverse(m_gameConfig.player1Deck.begin(),
                     m_gameConfig.player1Deck.end());
        std::reverse(m_gameConfig.player2Deck.begin(),
                     m_gameConfig.player2Deck.end());
    }

    // Set up decks
    for (auto& card : m_gameConfig.player1Deck)
    {
        Entity* entity = Entity::GetFromCard(GetPlayer1(), std::move(card));
        GetPlayer1().GetDeck().AddCard(*entity);
    }
    for (auto& card : m_gameConfig.player2Deck)
    {
        Entity* entity = Entity::GetFromCard(GetPlayer2(), std::move(card));
        GetPlayer2().GetDeck().AddCard(*entity);
    }

    // Determine first player
    switch (m_gameConfig.startPlayer)
    {
        case PlayerType::RANDOM:
        {
            auto val = Random::get(0, 1);
            m_firstPlayer = &m_players[val];
            break;
        }
        case PlayerType::PLAYER1:
            m_firstPlayer = &m_players[0];
            break;
        case PlayerType::PLAYER2:
            m_firstPlayer = &m_players[1];
            break;
    }
    m_currentPlayer = m_firstPlayer;

    // Set first turn
    m_turn = 1;
}
}  // namespace Hearthstonepp