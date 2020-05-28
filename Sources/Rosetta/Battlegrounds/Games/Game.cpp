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
    // Assign minion pool in Tavern
    std::size_t idx = 0;

    // Tier 1
    for (const auto& card : Cards::GetTier1Minions())
    {
        for (std::size_t i = 0; i < NUM_COPIES_OF_EACH_TIER1_MINIONS; ++i)
        {
            m_gameState.minionPool.at(idx) = { Minion(card), true };
            ++idx;
        }
    }
    // Tier 2
    for (const auto& card : Cards::GetTier2Minions())
    {
        for (std::size_t i = 0; i < NUM_COPIES_OF_EACH_TIER2_MINIONS; ++i)
        {
            m_gameState.minionPool.at(idx) = { Minion(card), true };
            ++idx;
        }
    }
    // Tier 3
    for (const auto& card : Cards::GetTier3Minions())
    {
        for (std::size_t i = 0; i < NUM_COPIES_OF_EACH_TIER3_MINIONS; ++i)
        {
            m_gameState.minionPool.at(idx) = { Minion(card), true };
            ++idx;
        }
    }
    // Tier 4
    for (const auto& card : Cards::GetTier4Minions())
    {
        for (std::size_t i = 0; i < NUM_COPIES_OF_EACH_TIER4_MINIONS; ++i)
        {
            m_gameState.minionPool.at(idx) = { Minion(card), true };
            ++idx;
        }
    }
    // Tier 5
    for (const auto& card : Cards::GetTier5Minions())
    {
        for (std::size_t i = 0; i < NUM_COPIES_OF_EACH_TIER5_MINIONS; ++i)
        {
            m_gameState.minionPool.at(idx) = { Minion(card), true };
            ++idx;
        }
    }
    // Tier 6
    for (const auto& card : Cards::GetTier6Minions())
    {
        for (std::size_t i = 0; i < NUM_COPIES_OF_EACH_TIER6_MINIONS; ++i)
        {
            m_gameState.minionPool.at(idx) = { Minion(card), true };
            ++idx;
        }
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

    // Assign 4 heroes to each player
    std::size_t heroIdx = 0;
    for (auto& player : m_gameState.players)
    {
        for (std::size_t i = 0; i < 4; ++i)
        {
            player.heroChoices.at(i) = currentHeroes.at(heroIdx + i).dbfID;
            player.selectHeroCallback = selectHeroCallback;
        }

        heroIdx += 4;
    }
}

void Game::Recruit()
{
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
