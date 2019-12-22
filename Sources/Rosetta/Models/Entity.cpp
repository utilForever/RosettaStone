// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Entity.hpp>
#include <Rosetta/Models/Minion.hpp>
#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Models/Spell.hpp>
#include <Rosetta/Zones/SetasideZone.hpp>

#include <utility>

namespace RosettaStone
{
Entity::Entity(Game* _game, Card* _card, std::map<GameTag, int> _tags, int _id)
    : game(_game), card(_card), m_gameTags(std::move(_tags))
{
    for (auto& gameTag : _card->gameTags)
    {
        Entity::SetGameTag(gameTag.first, gameTag.second);
    }

    id = _id < 0 ? static_cast<int>(game->GetNextID()) : _id;
}

Entity::~Entity()
{
    delete auraEffects;

    m_gameTags.clear();
}

std::map<GameTag, int> Entity::GetGameTags() const
{
    return m_gameTags;
}

int Entity::GetGameTag(GameTag tag) const
{
    int value = 0;

    const auto entityVal = m_gameTags.find(tag);
    if (entityVal == m_gameTags.end())
    {
        if (card != nullptr)
        {
            const auto cardVal = card->gameTags.find(tag);
            if (cardVal != card->gameTags.end())
            {
                value = cardVal->second;
            }
        }

        if (auraEffects != nullptr)
        {
            value += auraEffects->GetGameTag(tag);
        }
    }
    else
    {
        value += entityVal->second;

        if (auraEffects != nullptr)
        {
            value += auraEffects->GetGameTag(tag);
        }
    }

    return value > 0 ? value : 0;
}

void Entity::SetGameTag(GameTag tag, int value)
{
    m_gameTags.insert_or_assign(tag, value);
}

int Entity::GetCardTarget() const
{
    return GetGameTag(GameTag::CARD_TARGET);
}

void Entity::SetCardTarget(int value)
{
    SetGameTag(GameTag::CARD_TARGET, value);
}

void Entity::Reset()
{
    m_gameTags.erase(GameTag::DAMAGE);
    m_gameTags.erase(GameTag::EXHAUSTED);
    m_gameTags.erase(GameTag::ATK);
    m_gameTags.erase(GameTag::HEALTH);
    m_gameTags.erase(GameTag::COST);
    m_gameTags.erase(GameTag::TAUNT);
    m_gameTags.erase(GameTag::FROZEN);
    m_gameTags.erase(GameTag::CHARGE);
    m_gameTags.erase(GameTag::WINDFURY);
    m_gameTags.erase(GameTag::DIVINE_SHIELD);
    m_gameTags.erase(GameTag::STEALTH);
    m_gameTags.erase(GameTag::NUM_ATTACKS_THIS_TURN);
}

Playable* Entity::GetFromCard(Player* player, Card* card,
                              std::optional<std::map<GameTag, int>> cardTags,
                              IZone* zone, int id)
{
    std::map<GameTag, int> tags;
    if (cardTags.has_value())
    {
        tags = cardTags.value();
    }

    tags[GameTag::CONTROLLER] = player->playerID;
    tags[GameTag::ZONE] =
        zone != nullptr ? static_cast<int>(zone->GetType()) : 0;

    Playable* result;

    switch (card->GetCardType())
    {
        case CardType::HERO:
            result = new Hero(player, card, tags, id);
            break;
        case CardType::HERO_POWER:
            tags[GameTag::ZONE] = static_cast<int>(ZoneType::PLAY);
            result = new HeroPower(player, card, tags, id);
            break;
        case CardType::MINION:
            result = new Minion(player, card, tags, id);
            break;
        case CardType::SPELL:
            result = new Spell(player, card, tags, id);
            break;
        case CardType::WEAPON:
            result = new Weapon(player, card, tags, id);
            break;
        default:
            throw std::invalid_argument(
                "Generic::DrawCard() - Invalid card type!");
    }

    if (result->HasChooseOne())
    {
        delete result->chooseOneCard[0];
        delete result->chooseOneCard[1];

        result->chooseOneCard[0] =
            GetFromCard(player, Cards::FindCardByID(result->card->id + "a"),
                        std::nullopt, player->GetSetasideZone());
        result->chooseOneCard[1] =
            GetFromCard(player, Cards::FindCardByID(result->card->id + "b"),
                        std::nullopt, player->GetSetasideZone());
    }

    return result;
}
}  // namespace RosettaStone
