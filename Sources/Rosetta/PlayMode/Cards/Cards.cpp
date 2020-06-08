// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Common/Constants.hpp>
#include <Rosetta/PlayMode/Cards/Card.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Loaders/CardLoader.hpp>
#include <Rosetta/PlayMode/Loaders/InternalCardLoader.hpp>

namespace RosettaStone::PlayMode
{
Card emptyCard;

std::vector<Card*> Cards::m_cards;
std::array<std::vector<Card*>, NUM_PLAYER_CLASS> Cards::m_standardCards;
std::array<std::vector<Card*>, NUM_PLAYER_CLASS> Cards::m_wildCards;
std::vector<Card*> Cards::m_allStandardCards;
std::vector<Card*> Cards::m_allWildCards;
std::vector<Card*> Cards::m_lackeys;

Cards::Cards()
{
    m_cards.reserve(NUM_ALL_CARDS);

    CardLoader::Load(m_cards);
    InternalCardLoader::Load(m_cards);

    for (Card* card : m_cards)
    {
        card->Initialize();
    }

    for (Card* card : m_cards)
    {
        // NOTE: Subtract 2 because of CardClass::DRUID = 2
        // NOTE: CardClass::DEMONHUNTER = 14
        const auto cardClass = card->GetCardClass() == CardClass::DEMONHUNTER
                                   ? static_cast<int>(card->GetCardClass()) - 5
                                   : static_cast<int>(card->GetCardClass()) - 2;

        if (card->IsCollectible() && card->IsStandardSet() &&
            card->GetCardType() != CardType::HERO)
        {
            if (card->GetCardClass() != CardClass::NEUTRAL)
            {
                m_standardCards[cardClass].emplace_back(card);
            }
            m_allStandardCards.emplace_back(card);
        }

        if (card->IsCollectible() && card->IsWildSet() &&
            card->GetCardType() != CardType::HERO)
        {
            if (card->GetCardClass() != CardClass::NEUTRAL)
            {
                m_wildCards[cardClass].emplace_back(card);
            }
            m_allWildCards.emplace_back(card);
        }

        if (card->IsLackey())
        {
            m_lackeys.emplace_back(card);
        }
    }
}

Cards::~Cards()
{
    for (Card* card : m_cards)
    {
        delete card;
    }

    m_cards.clear();
}

Cards& Cards::GetInstance()
{
    static Cards instance;
    return instance;
}

const std::vector<Card*>& Cards::GetAllCards()
{
    return m_cards;
}

const std::vector<Card*>& Cards::GetStandardCards(CardClass cardClass)
{
    // NOTE: Subtract 2 because of CardClass::DRUID = 2
    return m_standardCards[static_cast<int>(cardClass) - 2];
}

const std::vector<Card*>& Cards::GetWildCards(CardClass cardClass)
{
    // NOTE: Subtract 2 because of CardClass::DRUID = 2
    return m_wildCards[static_cast<int>(cardClass) - 2];
}

const std::vector<Card*>& Cards::GetAllStandardCards()
{
    return m_allStandardCards;
}

const std::vector<Card*>& Cards::GetAllWildCards()
{
    return m_allWildCards;
}

std::vector<Card*> Cards::GetLackeys()
{
    return m_lackeys;
}

Card* Cards::FindCardByID(const std::string_view& id)
{
    for (Card* card : m_cards)
    {
        if (card->id == id)
        {
            return card;
        }
    }

    return &emptyCard;
}

Card* Cards::FindCardByDbfID(int dbfID)
{
    for (Card* card : m_cards)
    {
        if (card->dbfID == dbfID)
        {
            return card;
        }
    }

    return &emptyCard;
}

std::vector<Card*> Cards::FindCardByRarity(Rarity rarity)
{
    std::vector<Card*> result;

    for (Card* card : m_cards)
    {
        if (card->GetRarity() == rarity)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card*> Cards::FindCardByClass(CardClass cardClass)
{
    std::vector<Card*> result;

    for (Card* card : m_cards)
    {
        if (card->GetCardClass() == cardClass)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card*> Cards::FindCardBySet(CardSet cardSet)
{
    std::vector<Card*> result;

    for (Card* card : m_cards)
    {
        if (card->GetCardSet() == cardSet)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card*> Cards::FindCardByType(CardType cardType)
{
    std::vector<Card*> result;

    for (Card* card : m_cards)
    {
        if (card->GetCardType() == cardType)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card*> Cards::FindCardByRace(Race race)
{
    std::vector<Card*> result;

    for (Card* card : m_cards)
    {
        if (card->GetRace() == race)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

Card* Cards::FindCardByName(const std::string_view& name)
{
    for (Card* card : m_cards)
    {
        if (card->name == name && card->IsCollectible())
        {
            return card;
        }
    }

    return &emptyCard;
}

std::vector<Card*> Cards::FindCardByCost(int minVal, int maxVal)
{
    std::vector<Card*> result;

    for (Card* card : m_cards)
    {
        if (card->gameTags.at(GameTag::COST) >= minVal &&
            card->gameTags.at(GameTag::COST) <= maxVal)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card*> Cards::FindCardByAttack(int minVal, int maxVal)
{
    std::vector<Card*> result;

    for (Card* card : m_cards)
    {
        if (!(card->GetCardType() == CardType::MINION) &&
            !(card->GetCardType() == CardType::WEAPON))
        {
            continue;
        }

        if (card->gameTags.at(GameTag::ATK) >= minVal &&
            card->gameTags.at(GameTag::ATK) <= maxVal)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card*> Cards::FindCardByHealth(int minVal, int maxVal)
{
    std::vector<Card*> result;

    for (Card* card : m_cards)
    {
        if (!(card->GetCardType() == CardType::MINION) &&
            !(card->GetCardType() == CardType::HERO))
        {
            continue;
        }

        if (card->gameTags.at(GameTag::HEALTH) >= minVal &&
            card->gameTags.at(GameTag::HEALTH) <= maxVal)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card*> Cards::FindCardBySpellPower(int minVal, int maxVal)
{
    std::vector<Card*> result;

    for (Card* card : m_cards)
    {
        if (card->gameTags.find(GameTag::SPELLPOWER) == card->gameTags.end())
        {
            continue;
        }

        if (card->gameTags.at(GameTag::SPELLPOWER) >= minVal &&
            card->gameTags.at(GameTag::SPELLPOWER) <= maxVal)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<Card*> Cards::FindCardByGameTag(std::vector<GameTag> gameTags)
{
    std::vector<Card*> result;

    for (auto& card : m_cards)
    {
        auto cardGameTags = card->gameTags;

        for (const auto gameTag : gameTags)
        {
            if (cardGameTags.find(gameTag) != cardGameTags.end())
            {
                result.emplace_back(card);
            }
        }
    }

    return result;
}

Card* Cards::GetHeroCard(CardClass cardClass)
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
        case CardClass::DEMONHUNTER:
            return FindCardByID("HERO_10");
        default:
            return &emptyCard;
    }
}

Card* Cards::GetDefaultHeroPower(CardClass cardClass)
{
    switch (cardClass)
    {
        case CardClass::DRUID:
            return FindCardByID("HERO_06bp");
        case CardClass::HUNTER:
            return FindCardByID("HERO_05bp");
        case CardClass::MAGE:
            return FindCardByID("HERO_08bp");
        case CardClass::PALADIN:
            return FindCardByID("HERO_04bp");
        case CardClass::PRIEST:
            return FindCardByID("HERO_09bp");
        case CardClass::ROGUE:
            return FindCardByID("HERO_03bp");
        case CardClass::SHAMAN:
            return FindCardByID("HERO_02bp");
        case CardClass::WARLOCK:
            return FindCardByID("HERO_07bp");
        case CardClass::WARRIOR:
            return FindCardByID("HERO_01bp");
        case CardClass::DEMONHUNTER:
            return FindCardByID("HERO_10bp");
        default:
            return &emptyCard;
    }
}
}  // namespace RosettaStone::PlayMode
