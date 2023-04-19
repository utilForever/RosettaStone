// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Cards/Cards.hpp>
#include <Rosetta/Battlegrounds/Games/Game.hpp>
#include <Rosetta/Battlegrounds/Managers/GameManager.hpp>
#include <Rosetta/Battlegrounds/Models/Battle.hpp>

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
    m_playerFightPair.reserve(NUM_BATTLEGROUNDS_PLAYERS / 2);

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
        m_gameState.minionPool.AddMinionsToTavern(player, player.tavern);
    };

    // Create callback to purchase a minion in Tavern
    auto purchaseMinionCallback = [](Player& player, std::size_t tavernIdx) {
        Minion minion =
            player.tavern.fieldZone.Remove(player.tavern.fieldZone[tavernIdx]);
        player.hand.Add(minion, -1);
    };

    // Create callback to get next card index
    auto getNextCardIndexCallback = [this]() -> int { return m_cardIndex++; };

    // Create callback to return a minion to the minion pool
    auto returnMinionCallback = [this](int poolIdx) {
        m_gameState.minionPool.ReturnMinion(poolIdx);
    };

    // Create callback to clear a list of minions in Tavern's field
    auto clearTavernMinionsCallback = [this](Player& player) {
        while (!player.tavern.fieldZone.IsEmpty())
        {
            Minion minion =
                player.tavern.fieldZone.Remove(player.tavern.fieldZone[0]);
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

    // Create callback to get opponent player
    auto getOpponentPlayerCallback = [this](Player& player) -> Player& {
        const std::size_t idx = FindPlayerNextFight(player.idx);
        return m_gameState.players[idx];
    };

    // Create callback to process the tasks related to defeat
    auto processDefeatCallback = [this](Player& player) {
        player.playState = PlayState::LOST;

        // Determine player's rank
        player.rank = m_gameState.numRemainPlayer;
        --m_gameState.numRemainPlayer;

        player.tavern.fieldZone.ForEach([&](MinionData& minion) {
            m_gameState.minionPool.ReturnMinion(minion.value().GetPoolIndex());
        });

        player.hand.ForEach([&](std::optional<CardData>& card) {
            if (std::holds_alternative<Minion>(card.value()))
            {
                const auto minion = std::get<Minion>(card.value());
                m_gameState.minionPool.ReturnMinion(minion.GetPoolIndex());
            }
        });

        player.recruitField.ForEach([&](MinionData& minion) {
            m_gameState.minionPool.ReturnMinion(minion.value().GetPoolIndex());
        });

        m_gameState.ghostPlayerIdx = player.idx;
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
        player.purchaseMinionCallback = purchaseMinionCallback;
        player.getNextCardIndexCallback = getNextCardIndexCallback;
        player.returnMinionCallback = returnMinionCallback;
        player.clearTavernMinionsCallback = clearTavernMinionsCallback;
        player.upgradeTavernCallback = upgradeTavernCallback;
        player.completeRecruitCallback = completeRecruitCallback;
        player.getOpponentPlayerCallback = getOpponentPlayerCallback;
        player.processDefeatCallback = processDefeatCallback;

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
    // Check this game is over
    if (m_gameState.numRemainPlayer == 1)
    {
        // Set next phase
        m_gameState.nextPhase = Phase::GAMEOVER;
        GameManager::ProcessNextPhase(*this, m_gameState.nextPhase);
        return;
    }

    // Initialize player count for callback
    m_playerCount = 0;

    // Determine each player's opponent
    DetermineOpponent();

    for (auto& player : m_gameState.players)
    {
        if (player.playState != PlayState::PLAYING)
        {
            continue;
        }

        // Set the flag
        player.isInCombat = true;

        // Assign the index of the player to fight next.
        player.playerIdxNextFight = FindPlayerNextFight(player.idx);

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

        if (!player.freezeTavern)
        {
            // Clear a list of minions in Tavern
            while (!player.tavern.fieldZone.IsEmpty())
            {
                Minion minion =
                    player.tavern.fieldZone.Remove(player.tavern.fieldZone[0]);
                m_gameState.minionPool.ReturnMinion(minion.GetPoolIndex());
            }

            // Prepare a list of minions to each player for purchase
            player.PrepareTavern();
        }

        player.freezeTavern = false;
    }
}

void Game::Combat()
{
    for (auto& player : m_gameState.players)
    {
        // Set the flag
        player.isInCombat = true;
    }

    // Simulates a battle for each pair
    for (const auto& pair : m_playerFightPair)
    {
        Player& player1 = m_gameState.players.at(std::get<0>(pair));
        Player& player2 = m_gameState.players.at(std::get<1>(pair));

        Battle battle(player1, player2);

        // Create callback to get battle
        player1.getBattleCallback = [&]() -> Battle& { return battle; };
        player2.getBattleCallback = [&]() -> Battle& { return battle; };

        battle.Run();
    }

    // Set next phase
    m_gameState.nextPhase = Phase::RECRUIT;
    GameManager::ProcessNextPhase(*this, m_gameState.nextPhase);
}

void Game::GameOver()
{
    m_gameState.phase = Phase::COMPLETE;
}

void Game::DetermineOpponent()
{
    // NOTE: Random player that you didn't fight. If there is an odd number of
    // players alive, bottom 3 have a chance to play the ghost. Can't fight a
    // ghost 2 turns in a row. Ghost is the 1 of the most recent players to die.
    m_playerFightPair.clear();

    auto playerData = CalculateRank();

    // Check there is an odd number of players alive
    if (playerData.size() % 2 == 1)
    {
        // Determine player to fight the ghost
        const std::size_t playerIdx = DeterminePlayerToFightGhost(playerData);
        m_playerFightPair.emplace_back(
            std::make_tuple(playerIdx, m_gameState.ghostPlayerIdx));

        // Pair a list of players
        PairPlayers(playerData);
    }
    else
    {
        // Pair a list of players
        PairPlayers(playerData);
    }
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

std::size_t Game::DeterminePlayerToFightGhost(
    std::vector<std::tuple<int, int>>& playerData)
{
    // Bottom 3 have a chance to play the ghost
    std::vector<int> ghostCandidates;

    for (std::size_t i = playerData.size() - 3; i < playerData.size(); ++i)
    {
        // Can't fight a ghost 2 turns in a row
        if (m_gameState.players.at(i).isFoughtGhostLastTurn)
        {
            continue;
        }

        ghostCandidates.emplace_back(i);
    }

    // Fight randomly selected player and the ghost
    const std::size_t idx =
        Random::get<std::size_t>(0, ghostCandidates.size() - 1);

    // Remove the index of randomly selected player from player data
    playerData.erase(std::remove_if(playerData.begin(), playerData.end(),
                                    [&](std::tuple<int, int> data) {
                                        return std::get<0>(data) ==
                                               static_cast<int>(idx);
                                    }),
                     playerData.end());

    return idx;
}

void Game::SetPlayerPair(int player1Idx, int player2Idx)
{
    m_playerFightPair.emplace_back(std::make_tuple(player1Idx, player2Idx));
}

void Game::PairPlayers(std::vector<std::tuple<int, int>>& playerData)
{
    // Shuffle indefinitely until the conditions are met
    while (true)
    {
        bool isSucceed = true;
        Random::shuffle(playerData.begin(), playerData.end());

        for (std::size_t i = 0; i < playerData.size(); i += 2)
        {
            const int player1Idx = std::get<0>(playerData.at(i));
            const int player2Idx = std::get<0>(playerData.at(i + 1));

            // Check this player is the player you've been playing
            // against before
            if (m_gameState.players.at(player1Idx).playerIdxFoughtLastTurn ==
                static_cast<std::size_t>(player2Idx))
            {
                isSucceed = false;
                break;
            }
        }

        // If the conditions are not met, repeat while statement again
        if (!isSucceed)
        {
            continue;
        }

        // If the conditions are met, save the player's index pair
        for (std::size_t i = 0; i < playerData.size(); i += 2)
        {
            const int player1Idx = std::get<0>(playerData.at(i));
            const int player2Idx = std::get<0>(playerData.at(i + 1));

            m_playerFightPair.emplace_back(
                std::make_tuple(player1Idx, player2Idx));
        }

        break;
    }
}

std::size_t Game::FindPlayerNextFight(std::size_t playerIdx)
{
    for (const auto& fightPair : m_playerFightPair)
    {
        if (std::get<0>(fightPair) == playerIdx)
        {
            return std::get<1>(fightPair);
        }

        if (std::get<1>(fightPair) == playerIdx)
        {
            return std::get<0>(fightPair);
        }
    }

    return std::numeric_limits<std::size_t>::max();
}
}  // namespace RosettaStone::Battlegrounds
