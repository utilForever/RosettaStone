// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Cards/Cards.hpp>
#include <Rosetta/Battlegrounds/Games/Game.hpp>
#include <Rosetta/Battlegrounds/Managers/GameManager.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::Battlegrounds
{
GameState& Game::GetGameState()
{
    return m_gameState;
}

void Game::Start()
{
    // Initialize the minion pool
    m_gameState.minionPool.Initialize();

    // Create callback to increase player count and process next phase
    auto selectHeroCallback = [this]() {
        ++m_playerCount;

        if (m_playerCount >= 8)
        {
            // Set next phase
            m_gameState.nextPhase = Phase::RECRUIT;
            GameManager::ProcessNextPhase(*this, m_gameState.nextPhase);
        }
    };

    // Create callback to prepare a list of minions for purchase
    auto prepareMinionCallback = [this](Player& player) {
        // Shuffle the minion pool
        m_gameState.minionPool.Shuffle();

        // Add minions to player's Tavern
        m_gameState.minionPool.AddMinionsToTavern(player);
    };

    // Initialize variables and callbacks
    for (auto& player : m_gameState.players)
    {
        player.remainCoin = 0;
        player.totalCoin = 2;
        player.currentTier = 1;

        player.selectHeroCallback = selectHeroCallback;
        player.fillTavernMinionCallback = prepareMinionCallback;
    }

    // Set next phase
    m_gameState.nextPhase = Phase::SELECT_HERO;
    GameManager::ProcessNextPhase(*this, m_gameState.nextPhase);
}

void Game::SelectHero()
{
    // Shuffle current heroes
    auto currentHeroes = Cards::GetInstance().GetCurrentHeroes();
    Random::shuffle(currentHeroes.begin(), currentHeroes.end());

    // Assign 4 heroes to each player
    std::size_t heroIdx = 0;
    for (auto& player : m_gameState.players)
    {
        for (std::size_t i = 0; i < 4; ++i)
        {
            player.heroChoices.at(i) = currentHeroes.at(heroIdx + i).dbfID;
        }

        heroIdx += 4;
    }
}

void Game::Recruit()
{
    for (auto& player : m_gameState.players)
    {
        // Set the value of coin (remain/total)
        if (player.totalCoin < COIN_UPPER_LIMIT)
        {
            ++player.totalCoin;
        }
        player.remainCoin = player.totalCoin;

        // Assign a list of minions to each player for purchase
        player.FillTavernMinions();
    }
}

void Game::Combat()
{
    // Set next phase
    m_gameState.nextPhase = Phase::RECRUIT;
    GameManager::ProcessNextPhase(*this, m_gameState.nextPhase);
}

void Game::GameOver()
{
}
}  // namespace RosettaStone::Battlegrounds
