// Copyright (c) 2017-2024 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Entity.hpp>
#include <Rosetta/PlayMode/Models/Location.hpp>
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
    m_gameTags.clear();
}

int Entity::GetNativeGameTag(GameTag tag) const
{
    return m_gameTags.contains(tag) ? m_gameTags.at(tag) : 0;
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
    using enum GameTag;

    m_gameTags.erase(DAMAGE);
    m_gameTags.erase(EXHAUSTED);
    m_gameTags.erase(ATK);
    m_gameTags.erase(HEALTH);
    m_gameTags.erase(COST);
    m_gameTags.erase(TAUNT);
    m_gameTags.erase(FROZEN);
    m_gameTags.erase(CHARGE);
    m_gameTags.erase(WINDFURY);
    m_gameTags.erase(DIVINE_SHIELD);
    m_gameTags.erase(STEALTH);
    m_gameTags.erase(SPELLBURST);
    m_gameTags.erase(NUM_ATTACKS_THIS_TURN);
    m_gameTags.erase(INFUSE);
    m_gameTags.erase(INFUSED);
    m_gameTags.erase(INFUSE_COUNTER);
}

Playable* Entity::GetFromCard(Player* player, Card* card,
                              std::optional<std::map<GameTag, int>> cardTags,
                              const IZone* zone, int id)
{
    using enum CardType;

    std::map<GameTag, int> tags;
    if (cardTags.has_value())
    {
        tags = cardTags.value();
    }

    tags[GameTag::CONTROLLER] = player->playerID;
    tags[GameTag::ZONE] = zone ? std::to_underlying(zone->GetType()) : 0;

    std::unique_ptr<Playable> result;

    switch (card->GetCardType())
    {
        case HERO:
            result = std::make_unique<Hero>(player, card, tags, id);
            break;
        case HERO_POWER:
            tags[GameTag::ZONE] = std::to_underlying(ZoneType::PLAY);
            result = std::make_unique<HeroPower>(player, card, tags, id);
            break;
        case MINION:
            result = std::make_unique<Minion>(player, card, tags, id);
            break;
        case LOCATION:
            result = std::make_unique<Location>(player, card, tags, id);
            break;
        case SPELL:
            result = std::make_unique<Spell>(player, card, tags, id);
            break;
        case WEAPON:
            result = std::make_unique<Weapon>(player, card, tags, id);
            break;
        case INVALID:
        case GAME:
        case PLAYER:
        case ENCHANTMENT:
        case ITEM:
        case TOKEN:
        case BLANK:
        case GAME_MODE_BUTTON:
        case MOVE_MINION_HOVER_TARGET:
        case LETTUCE_ABILITY:
        case BATTLEGROUND_HERO_BUDDY:
        case BATTLEGROUND_QUEST_REWARD:
            throw std::invalid_argument(
                "Generic::DrawCard() - Invalid card type!");
    }

    // Add entity to list
    player->game->entityList.emplace(result->GetGameTag(GameTag::ENTITY_ID),
                                     result.get());

    return result.release();
}
}  // namespace RosettaStone::PlayMode
