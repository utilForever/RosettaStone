// Copyright (c) 2017-2024 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Cards/Cards.hpp>
#include <Rosetta/Battlegrounds/Loaders/CardLoader.hpp>
#include <Rosetta/Battlegrounds/Loaders/InternalCardLoader.hpp>

namespace RosettaStone::Battlegrounds
{
std::array<Card, NUM_BATTLEGROUNDS_CARDS> Cards::m_cards;
std::array<Card, NUM_BATTLEGROUNDS_HEROES> Cards::m_curHeroes;
std::array<Card, NUM_TIER1_MINIONS> Cards::m_tier1Minions;
std::array<Card, NUM_TIER2_MINIONS> Cards::m_tier2Minions;
std::array<Card, NUM_TIER3_MINIONS> Cards::m_tier3Minions;
std::array<Card, NUM_TIER4_MINIONS> Cards::m_tier4Minions;
std::array<Card, NUM_TIER5_MINIONS> Cards::m_tier5Minions;
std::array<Card, NUM_TIER6_MINIONS> Cards::m_tier6Minions;

Cards::Cards()
{
    CardLoader::Load(m_cards);
    InternalCardLoader::Load(m_cards);

    std::size_t heroIdx = 0;
    std::size_t tier1Idx = 0, tier2Idx = 0, tier3Idx = 0, tier4Idx = 0,
                tier5Idx = 0, tier6Idx = 0;

    for (auto& card : m_cards)
    {
        card.Initialize();

        if (card.GetCardType() == CardType::HERO && card.isCurHero)
        {
            m_curHeroes.at(heroIdx) = card;
            ++heroIdx;
        }

        if (card.isBattlegroundsPoolMinion)
        {
            if (card.GetTier() == 1)
            {
                m_tier1Minions.at(tier1Idx) = card;
                ++tier1Idx;
            }
            else if (card.GetTier() == 2)
            {
                m_tier2Minions.at(tier2Idx) = card;
                ++tier2Idx;
            }
            else if (card.GetTier() == 3)
            {
                m_tier3Minions.at(tier3Idx) = card;
                ++tier3Idx;
            }
            else if (card.GetTier() == 4)
            {
                m_tier4Minions.at(tier4Idx) = card;
                ++tier4Idx;
            }
            else if (card.GetTier() == 5)
            {
                m_tier5Minions.at(tier5Idx) = card;
                ++tier5Idx;
            }
            else if (card.GetTier() == 6)
            {
                m_tier6Minions.at(tier6Idx) = card;
                ++tier6Idx;
            }
        }
    }
}

Cards& Cards::GetInstance()
{
    static Cards instance;
    return instance;
}

const std::array<Card, NUM_BATTLEGROUNDS_CARDS>& Cards::GetAllCards()
{
    return m_cards;
}

Card Cards::FindCardByID(const std::string_view& id)
{
    for (auto& card : m_cards)
    {
        if (card.id == id)
        {
            return card;
        }
    }

    return Card{};
}

Card Cards::FindCardByDbfID(int dbfID)
{
    for (auto& card : m_cards)
    {
        if (card.dbfID == dbfID)
        {
            return card;
        }
    }

    return Card{};
}

Card Cards::FindCardByName(const std::string_view& name)
{
    for (auto& card : m_cards)
    {
        if (card.name == name &&
            (card.GetCardSet() == CardSet::BATTLEGROUNDS ||
             card.normalDbfID != 0 || card.premiumDbfID != 0))
        {
            return card;
        }
    }

    return Card{};
}

const std::array<Card, NUM_BATTLEGROUNDS_HEROES>& Cards::GetCurrentHeroes()
{
    return m_curHeroes;
}

const std::array<Card, NUM_TIER1_MINIONS>& Cards::GetTier1Minions()
{
    return m_tier1Minions;
}

const std::array<Card, NUM_TIER2_MINIONS>& Cards::GetTier2Minions()
{
    return m_tier2Minions;
}

const std::array<Card, NUM_TIER3_MINIONS>& Cards::GetTier3Minions()
{
    return m_tier3Minions;
}

const std::array<Card, NUM_TIER4_MINIONS>& Cards::GetTier4Minions()
{
    return m_tier4Minions;
}

const std::array<Card, NUM_TIER5_MINIONS>& Cards::GetTier5Minions()
{
    return m_tier5Minions;
}

const std::array<Card, NUM_TIER6_MINIONS>& Cards::GetTier6Minions()
{
    return m_tier6Minions;
}
}  // namespace RosettaStone::Battlegrounds
