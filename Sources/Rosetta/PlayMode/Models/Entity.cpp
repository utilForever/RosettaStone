// Copyright (c) 2017-2021 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Entity.hpp>
#include <Rosetta/PlayMode/Models/Minion.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>
#include <Rosetta/PlayMode/Models/Spell.hpp>
#include <Rosetta/PlayMode/Zones/SetasideZone.hpp>

#include <utility>

namespace RosettaStone::PlayMode
{
Entity::Entity(Game* _game, Card* _card, std::map<GameTag, int> _tags, int _id)
    : game(_game), card(_card), m_gameTags(std::move(_tags))
{
    for (const auto& gameTag : _card->gameTags)
    {
        Entity::SetGameTag(gameTag.first, gameTag.second);
    }

    Entity::SetGameTag(GameTag::ENTITY_ID, _id < 0 ? game->GetNextID() : _id);
}

Entity::~Entity()
{
    delete auraEffects;

    m_gameTags.clear();
}

int Entity::GetNativeGameTag(GameTag tag) const
{
    return m_gameTags.find(tag) == m_gameTags.end() ? 0 : m_gameTags.at(tag);
}

void Entity::SetNativeGameTag(GameTag tag, int value)
{
    m_gameTags.insert_or_assign(tag, value);
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
        if (card)
        {
            const auto cardVal = card->gameTags.find(tag);
            if (cardVal != card->gameTags.end())
            {
                value = cardVal->second;
            }
        }

        if (auraEffects)
        {
            value += auraEffects->GetGameTag(tag);
        }
    }
    else
    {
        value += entityVal->second;

        if (auraEffects)
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
    m_gameTags.erase(GameTag::SPELLBURST);
    m_gameTags.erase(GameTag::NUM_ATTACKS_THIS_TURN);
    m_gameTags.erase(GameTag::INFUSE);
    m_gameTags.erase(GameTag::INFUSED);
    m_gameTags.erase(GameTag::INFUSE_COUNTER);
}

Playable* Entity::GetFromCard(Player* player, Card* card,
                              std::optional<std::map<GameTag, int>> cardTags,
                              const IZone* zone, int id)
{
    std::map<GameTag, int> tags;
    if (cardTags.has_value())
    {
        tags = cardTags.value();
    }

    tags[GameTag::CONTROLLER] = player->playerID;
    tags[GameTag::ZONE] = zone ? static_cast<int>(zone->GetType()) : 0;

    Playable* result = nullptr;

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
        case CardType::LOCATION:
            result = new Minion(player, card, tags, id);
            break;
        case CardType::SPELL:
            result = new Spell(player, card, tags, id);
            break;
        case CardType::WEAPON:
            result = new Weapon(player, card, tags, id);
            break;
        case CardType::INVALID:
        case CardType::GAME:
        case CardType::PLAYER:
        case CardType::ENCHANTMENT:
        case CardType::ITEM:
        case CardType::TOKEN:
        case CardType::BLANK:
        case CardType::GAME_MODE_BUTTON:
        case CardType::MOVE_MINION_HOVER_TARGET:
        case CardType::LETTUCE_ABILITY:
        case CardType::BATTLEGROUND_HERO_BUDDY:
        case CardType::BATTLEGROUND_QUEST_REWARD:
            throw std::invalid_argument(
                "Generic::DrawCard() - Invalid card type!");
    }

    // Add entity to list
    player->game->entityList.emplace(result->GetGameTag(GameTag::ENTITY_ID),
                                     result);

    return result;
}
}  // namespace RosettaStone::PlayMode
