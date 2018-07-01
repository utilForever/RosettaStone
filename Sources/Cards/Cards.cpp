/*************************************************************************
> File Name: Cards.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Cards class that stores a list of cards.
> Created Time: 2017/10/10
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <Loaders/CardLoader.h>
#include <Cards/Cards.h>
#include <Cards/Character.h>

namespace Hearthstonepp
{
Cards* Cards::m_instance = nullptr;

Cards::Cards()
{
    CardLoader loader;
    loader.LoadData(m_cards);
}

Cards::~Cards()
{
    for (auto card : m_cards)
    {
        delete card;
    }

    m_cards.clear();
}

Cards* Cards::GetInstance()
{
    if (m_instance == nullptr)
    {
        m_instance = new Cards();
    }

    return m_instance;
}

std::vector<Card*> Cards::GetAllCards() const
{
    return m_cards;
}

const Card* Cards::FindCardByID(const std::string& id)
{
    for (auto card : m_cards)
    {
        if (card->id == id)
        {
            return card;
        }
    }

    return nullptr;
}

std::vector<Card*> Cards::FindCardByRarity(Rarity rarity)
{
    std::vector<Card*> result;

    for (auto card : m_cards)
    {
        if (card->rarity == rarity)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card*> Cards::FindCardByClass(CardClass cardClass)
{
    std::vector<Card*> result;

    for (auto card : m_cards)
    {
        if (card->cardClass == cardClass)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card*> Cards::FindCardByType(CardType cardType)
{
    std::vector<Card*> result;

    for (auto card : m_cards)
    {
        if (card->cardType == cardType)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card*> Cards::FindCardByRace(Race race)
{
    std::vector<Card*> result;

    for (auto card : m_cards)
    {
        if (card->race == race)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

Card* Cards::FindCardByName(const std::string& name)
{
    for (auto card : m_cards)
    {
        if (card->name == name)
        {
            return card;
        }
    }

    return nullptr;
}

std::vector<Card*> Cards::FindCardByCost(size_t minVal, size_t maxVal)
{
    std::vector<Card*> result;

    for (auto card : m_cards)
    {
        if (card->cost >= minVal && card->cost <= maxVal)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card*> Cards::FindCardByAttack(size_t minVal, size_t maxVal)
{
    std::vector<Card*> result;

    for (auto card : m_cards)
    {
        const Character* character = dynamic_cast<Character*>(card);
        if (character == nullptr)
        {
            continue;
        }

        if (character->attack >= minVal && character->attack <= maxVal)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card*> Cards::FindCardByHealth(size_t minVal, size_t maxVal)
{
    std::vector<Card*> result;

    for (auto card : m_cards)
    {
        const Character* character = dynamic_cast<Character*>(card);
        if (character == nullptr)
        {
            continue;
        }

        if (character->health >= minVal && character->health <= maxVal)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card*> Cards::FindCardByMechanics(std::vector<GameTag> mechanics)
{
    std::vector<Card*> result;

    for (auto card : m_cards)
    {
        auto mechanicsInCard = card->mechanics;

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

const Card* Cards::GetHeroCard(CardClass cardClass)
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
            return nullptr;
    }
}

const Card* Cards::GetDefaultHeroPower(CardClass cardClass)
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
            return nullptr;
    }
}
}
