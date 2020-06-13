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
    // Choose a race to exclude from the minion pool at random
    const auto raceIdx =
        Random::get<std::size_t>(0, RACES_IN_BATTLEGROUNDS.size() - 1);
    m_excludeRace = RACES_IN_BATTLEGROUNDS.at(raceIdx);

    // Initialize the minion pool
    m_gameState.minionPool.Initialize(m_excludeRace);

    // Create callback to increase player count and process next phase
    auto selectHeroCallback = [this](Player& player) {
        ++m_playerCount;

        player.hero.health = player.hero.card.GetHealth();

        if (m_playerCount >= NUM_BATTLEGROUNDS_PLAYERS)
        {
            // Set next phase
            m_gameState.nextPhase = Phase::RECRUIT;
            GameManager::ProcessNextPhase(*this, m_gameState.nextPhase);
        }
    };

    // Create callback to prepare a list of minions for purchase
    auto prepareTavernMinionsCallback = [this](Player& player) {
        m_gameState.minionPool.AddMinionsToTavern(player);
    };

    // Create callback to return a minion to the minion pool
    auto returnMinionCallback = [this](int poolIdx) {
        m_gameState.minionPool.ReturnMinion(poolIdx);
    };

    // Create callback to clear a list of minions in Tavern's field
    auto clearTavernMinionsCallback = [this](FieldZone& minions) {
        while (!minions.IsEmpty())
        {
            Minion minion = minions.Remove(minions[0]);
            m_gameState.minionPool.ReturnMinion(minion.GetPoolIndex());
        }
    };

    // Create callback to upgrade player's Tavern to the next tier
    auto upgradeTavernCallback = [](Player& player) {
        ++player.currentTier;

        // Set the value of coin to upgrade player's Tavern to the next tier
        switch (player.currentTier)
        {
            case 2:
                player.coinToUpgradeTavern = NUM_COIN_UPGRADE_TAVERN_TIER_3;
                break;
            case 3:
                player.coinToUpgradeTavern = NUM_COIN_UPGRADE_TAVERN_TIER_4;
                break;
            case 4:
                player.coinToUpgradeTavern = NUM_COIN_UPGRADE_TAVERN_TIER_5;
                break;
            case 5:
                player.coinToUpgradeTavern = NUM_COIN_UPGRADE_TAVERN_TIER_6;
                break;
            default:
                throw std::logic_error("Invalid player's current tier");
        }
    };

    // Create callback to complete recruit and process next phase
    auto completeRecruitCallback = [this]() {
        ++m_playerCount;

        if (m_playerCount >= NUM_BATTLEGROUNDS_PLAYERS)
        {
            // Set next phase
            m_gameState.nextPhase = Phase::COMBAT;
            GameManager::ProcessNextPhase(*this, m_gameState.nextPhase);
        }
    };

    std::size_t playerIdx = 0;

    // Initialize variables and callbacks
    for (auto& player : m_gameState.players)
    {
        player.playState = PlayState::PLAYING;
        player.idx = playerIdx;

        player.remainCoin = 0;
        player.totalCoin = 2;
        player.currentTier = 1;
        player.coinToUpgradeTavern = NUM_COIN_UPGRADE_TAVERN_TIER_2 + 1;

        player.selectHeroCallback = selectHeroCallback;
        player.prepareTavernMinionsCallback = prepareTavernMinionsCallback;
        player.returnMinionCallback = returnMinionCallback;
        player.clearTavernMinionsCallback = clearTavernMinionsCallback;
        player.upgradeTavernCallback = upgradeTavernCallback;
        player.completeRecruitCallback = completeRecruitCallback;

        ++playerIdx;
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
        for (std::size_t i = 0; i < NUM_HEROES_ON_SELECTION_LIST; ++i)
        {
            player.heroChoices.at(i) = currentHeroes.at(heroIdx + i).dbfID;
        }

        heroIdx += NUM_HEROES_ON_SELECTION_LIST;
    }
}

void Game::Recruit()
{
    for (auto& player : m_gameState.players)
    {
        if (player.playState != PlayState::PLAYING)
        {
            continue;
        }

        // Set the value of coin (remain/total)
        if (player.totalCoin < COIN_UPPER_LIMIT)
        {
            ++player.totalCoin;
        }
        player.remainCoin = player.totalCoin;

        // Decrease the value of coin to upgrade player's Tavern to next tier
        if (player.currentTier < TIER_UPPER_LIMIT)
        {
            --player.coinToUpgradeTavern;
        }

        // Prepare a list of minions to each player for purchase
        player.PrepareTavern();
    }
}

void Game::Combat()
{
    // Determine each player's opponent
    DetermineOpponent();
}

void Game::GameOver()
{
}

void Game::DetermineOpponent()
{
    // NOTE: Random player that you didn't fight. If there is an odd number of
    // players alive, bottom 3 have a chance to play the ghost. Can't fight a
    // ghost 2 turns in a row. Ghost is the 1 of the most recent players to die.
    auto playerData = CalculateRank();
    (void)playerData;
}

std::vector<std::tuple<int, int>> Game::CalculateRank()
{
    std::vector<std::tuple<int, int>> playerData;
    playerData.reserve(NUM_BATTLEGROUNDS_PLAYERS);

    for (const auto& player : m_gameState.players)
    {
        if (player.playState != PlayState::PLAYING)
        {
            continue;
        }

        playerData.emplace_back(
            std::make_tuple(player.idx, player.hero.health));
    }

    std::sort(playerData.begin(), playerData.end(),
              [](std::tuple<int, int> a, std::tuple<int, int> b) {
                  return std::get<1>(a) > std::get<1>(b);
              });

    return playerData;
}
}  // namespace RosettaStone::Battlegrounds
