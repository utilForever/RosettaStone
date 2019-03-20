// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Cards/Card.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Loaders/CardLoader.hpp>
#include <Rosetta/Loaders/PowerLoader.hpp>

namespace Hearthstonepp
{
Cards::Cards()
{
    CardLoader::Load(m_cards);
    PowerLoader::Load(m_cards);
}

Cards::~Cards()
{
    m_cards.clear();
}

Cards& Cards::GetInstance()
{
    static Cards instance;
    return instance;
}

const std::vector<Card>& Cards::GetAllCards() const
{
    return m_cards;
}

Card Cards::FindCardByID(const std::string& id)
{
    for (auto card : m_cards)
    {
        if (card.id == id)
        {
            return card;
        }
    }

    return Card();
}

std::vector<Card> Cards::FindCardByRarity(Rarity rarity)
{
    std::vector<Card> result;

    for (auto card : m_cards)
    {
        if (card.rarity == rarity)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card> Cards::FindCardByClass(CardClass cardClass)
{
    std::vector<Card> result;

    for (auto card : m_cards)
    {
        if (card.cardClass == cardClass)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card> Cards::FindCardBySet(CardSet cardSet)
{
    std::vector<Card> result;

    for (auto card : m_cards)
    {
        if (card.cardSet == cardSet)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card> Cards::FindCardByType(CardType cardType)
{
    std::vector<Card> result;

    for (auto card : m_cards)
    {
        if (card.cardType == cardType)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card> Cards::FindCardByRace(Race race)
{
    std::vector<Card> result;

    for (auto card : m_cards)
    {
        if (card.race == race)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

Card Cards::FindCardByName(const std::string& name)
{
    for (auto card : m_cards)
    {
        if (card.name == name)
        {
            return card;
        }
    }

    return Card();
}

std::vector<Card> Cards::FindCardByCost(std::size_t minVal, std::size_t maxVal)
{
    std::vector<Card> result;

    for (auto card : m_cards)
    {
        if (card.cost >= minVal && card.cost <= maxVal)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card> Cards::FindCardByAttack(std::size_t minVal,
                                          std::size_t maxVal)
{
    std::vector<Card> result;

    for (auto card : m_cards)
    {
        if (!card.attack)
        {
            continue;
        }

        if (*card.attack >= minVal && *card.attack <= maxVal)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card> Cards::FindCardByHealth(std::size_t minVal,
                                          std::size_t maxVal)
{
    std::vector<Card> result;

    for (auto card : m_cards)
    {
        if (!card.health)
        {
            continue;
        }

        if (*card.health >= minVal && *card.health <= maxVal)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card> Cards::FindCardBySpellDamage(std::size_t minVal,
                                               std::size_t maxVal)
{
    std::vector<Card> result;

    for (auto card : m_cards)
    {
        if (!card.spellDamage)
        {
            continue;
        }

        if (*card.spellDamage >= minVal && *card.spellDamage <= maxVal)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card> Cards::FindCardByMechanics(std::vector<GameTag> mechanics)
{
    std::vector<Card> result;

    for (auto card : m_cards)
    {
        auto mechanicsInCard = card.mechanics;

        for (const auto mechanic : mechanics)
        {
            if (std::find(mechanicsInCard.begin(), mechanicsInCard.end(),
                          mechanic) != mechanicsInCard.end())
            {
                result.emplace_back(card);
            }
        }
    }

    return result;
}

Card Cards::GetHeroCard(CardClass cardClass)
{
    switch (cardClass)
    {
        case CardClass::DRUID:
            return FindCardByID("HERO_06");
        case CardClass::HUNTER:
            return FindCardByID("HERO_05");
        case CardClass::MAGE:
            return FindCardByID("HERO_08");
        case CardClass::PALADIN:
            return FindCardByID("HERO_04");
        case CardClass::PRIEST:
            return FindCardByID("HERO_09");
        case CardClass::ROGUE:
            return FindCardByID("HERO_03");
        case CardClass::SHAMAN:
            return FindCardByID("HERO_02");
        case CardClass::WARLOCK:
            return FindCardByID("HERO_07");
        case CardClass::WARRIOR:
            return FindCardByID("HERO_01");
        default:
            return Card();
    }
}

Card Cards::GetDefaultHeroPower(CardClass cardClass)
{
    switch (cardClass)
    {
        case CardClass::DRUID:
            return FindCardByID("CS2_017");
        case CardClass::HUNTER:
            return FindCardByID("DS1h_292");
        case CardClass::MAGE:
            return FindCardByID("CS2_034");
        case CardClass::PALADIN:
            return FindCardByID("CS2_101");
        case CardClass::PRIEST:
            return FindCardByID("CS1h_001");
        case CardClass::ROGUE:
            return FindCardByID("CS2_083b");
        case CardClass::SHAMAN:
            return FindCardByID("CS2_049");
        case CardClass::WARLOCK:
            return FindCardByID("CS2_056");
        case CardClass::WARRIOR:
            return FindCardByID("CS2_102");
        default:
            return Card();
    }
}
}  // namespace Hearthstonepp
