// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Cards/Cards.hpp>
#include <Rosetta/Battlegrounds/Models/MinionPool.hpp>
#include <Rosetta/Battlegrounds/Utils/GameUtils.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::Battlegrounds
{
void MinionPool::Initialize()
{
    std::size_t idx = 0;

    // Tier 1
    for (const auto& card : Cards::GetTier1Minions())
    {
        for (std::size_t i = 0; i < NUM_COPIES_OF_EACH_TIER1_MINIONS; ++i)
        {
            m_minions.at(idx) = { Minion(card), idx, true };
            ++idx;
        }
    }

    // Tier 2
    for (const auto& card : Cards::GetTier2Minions())
    {
        for (std::size_t i = 0; i < NUM_COPIES_OF_EACH_TIER2_MINIONS; ++i)
        {
            m_minions.at(idx) = { Minion(card), idx, true };
            ++idx;
        }
    }

    // Tier 3
    for (const auto& card : Cards::GetTier3Minions())
    {
        for (std::size_t i = 0; i < NUM_COPIES_OF_EACH_TIER3_MINIONS; ++i)
        {
            m_minions.at(idx) = { Minion(card), idx, true };
            ++idx;
        }
    }

    // Tier 4
    for (const auto& card : Cards::GetTier4Minions())
    {
        for (std::size_t i = 0; i < NUM_COPIES_OF_EACH_TIER4_MINIONS; ++i)
        {
            m_minions.at(idx) = { Minion(card), idx, true };
            ++idx;
        }
    }

    // Tier 5
    for (const auto& card : Cards::GetTier5Minions())
    {
        for (std::size_t i = 0; i < NUM_COPIES_OF_EACH_TIER5_MINIONS; ++i)
        {
            m_minions.at(idx) = { Minion(card), idx, true };
            ++idx;
        }
    }

    // Tier 6
    for (const auto& card : Cards::GetTier6Minions())
    {
        for (std::size_t i = 0; i < NUM_COPIES_OF_EACH_TIER6_MINIONS; ++i)
        {
            m_minions.at(idx) = { Minion(card), idx, true };
            ++idx;
        }
    }
}

void MinionPool::Shuffle()
{
    Random::shuffle(m_minions.begin(), m_minions.end());
}

void MinionPool::AddMinionsToTavern(Player& player)
{
    const std::size_t numMinions = GetNumMinionsCanPurchase(player.currentTier);
    auto minions = GetMinions(1, player.currentTier, true);

    Random::shuffle(minions.begin(), minions.end());

    std::size_t idx = 0;
    for (auto& minion : minions)
    {
        player.tavernMinions.Add(std::get<0>(minion));
        std::get<2>(minion) = false;
        ++idx;

        if (idx == numMinions)
        {
            break;
        }
    }
}

std::vector<MinionPoolData> MinionPool::GetMinions(int minTier, int maxTier,
                                                   bool isInPoolOnly)
{
    std::vector<MinionPoolData> result;

    for (auto& minion : m_minions)
    {
        const int tier = std::get<0>(minion).GetTier();

        if (tier >= minTier && tier <= maxTier)
        {
            if (isInPoolOnly && std::get<2>(minion) == false)
            {
                continue;
            }

            result.emplace_back(minion);
        }
    }

    return result;
}
}  // namespace RosettaStone::Battlegrounds
