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

Cards::Cards()
{
    CardLoader::Load(m_cards);

    std::size_t heroIdx = 0;

    for (auto& card : m_cards)
    {
        if (card.GetCardType() == CardType::HERO && card.isCurHero)
        {
            m_curHeroes.at(heroIdx) = card;
            ++heroIdx;
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

const std::array<Card, NUM_HEROES_IN_BATTLEGROUNDS>&
Cards::GetCurrentHeroCards()
{
    return m_curHeroes;
}
}  // namespace RosettaStone::Battlegrounds
