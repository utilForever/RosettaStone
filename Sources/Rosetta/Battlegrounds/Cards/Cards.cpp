// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Cards/Cards.hpp>
#include <Rosetta/Battlegrounds/Loaders/CardLoader.hpp>

namespace RosettaStone::Battlegrounds
{
std::array<Card, NUM_BATTLEGROUNDS_CARDS> Cards::m_cards;
std::array<Card, NUM_HEROES_IN_BATTLEGROUNDS> Cards::m_curHeroes;
std::array<Card, NUM_TIER1_MINIONS_IN_BATTLEGROUNDS> Cards::m_tier1Minions;
std::array<Card, NUM_TIER2_MINIONS_IN_BATTLEGROUNDS> Cards::m_tier2Minions;
std::array<Card, NUM_TIER3_MINIONS_IN_BATTLEGROUNDS> Cards::m_tier3Minions;
std::array<Card, NUM_TIER4_MINIONS_IN_BATTLEGROUNDS> Cards::m_tier4Minions;
std::array<Card, NUM_TIER5_MINIONS_IN_BATTLEGROUNDS> Cards::m_tier5Minions;
std::array<Card, NUM_TIER6_MINIONS_IN_BATTLEGROUNDS> Cards::m_tier6Minions;

Cards::Cards()
{
    CardLoader::Load(m_cards);

    std::size_t heroIdx = 0;
    std::size_t tier1Idx = 0, tier2Idx = 0, tier3Idx = 0, tier4Idx = 0,
                tier5Idx = 0, tier6Idx = 0;

    for (auto& card : m_cards)
    {
        if (card.GetCardType() == CardType::HERO && card.isCurHero)
        {
            m_curHeroes.at(heroIdx) = card;
            ++heroIdx;
        }

        if (card.GetCardType() == CardType::MINION)
        {
            switch (card.GetTier())
            {
                case 1:
                    m_tier1Minions.at(tier1Idx) = card;
                    ++tier1Idx;
                    break;
                case 2:
                    m_tier2Minions.at(tier2Idx) = card;
                    ++tier2Idx;
                    break;
                case 3:
                    m_tier3Minions.at(tier3Idx) = card;
                    ++tier3Idx;
                    break;
                case 4:
                    m_tier4Minions.at(tier4Idx) = card;
                    ++tier4Idx;
                    break;
                case 5:
                    m_tier5Minions.at(tier5Idx) = card;
                    ++tier5Idx;
                    break;
                case 6:
                    m_tier6Minions.at(tier6Idx) = card;
                    ++tier6Idx;
                    break;
                default:
                    break;
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

const std::array<Card, NUM_HEROES_IN_BATTLEGROUNDS>&
Cards::GetCurrentHeroCards()
{
    return m_curHeroes;
}
}  // namespace RosettaStone::Battlegrounds
