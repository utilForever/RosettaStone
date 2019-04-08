// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Entity.hpp>
#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Models/Spell.hpp>

namespace RosettaStone
{
Entity::Entity(Player& _owner, Card& _card) : card(_card), m_owner(&_owner)
{
    auraEffects = new AuraEffects(this);

    for (auto& gameTag : _card.gameTags)
    {
        Entity::SetGameTag(gameTag.first, gameTag.second);
    }
}

Entity::Entity(const Entity& ent) : m_owner(ent.m_owner)
{
    FreeMemory();

    card = ent.card;
    m_owner = ent.m_owner;

    auraEffects = ent.auraEffects;
    onGoingEffect = ent.onGoingEffect;
    m_gameTags = ent.m_gameTags;
}

Entity::Entity(Entity&& ent) noexcept : m_owner(ent.m_owner)
{
    FreeMemory();

    card = ent.card;
    m_owner = ent.m_owner;

    auraEffects = ent.auraEffects;
    onGoingEffect = ent.onGoingEffect;
    m_gameTags = ent.m_gameTags;
}

Entity::~Entity()
{
    FreeMemory();
}

Entity& Entity::operator=(const Entity& ent)
{
    if (this == &ent)
    {
        return *this;
    }

    FreeMemory();

    card = ent.card;
    m_owner = ent.m_owner;

    auraEffects = ent.auraEffects;
    onGoingEffect = ent.onGoingEffect;
    m_gameTags = ent.m_gameTags;

    return *this;
}

Entity& Entity::operator=(Entity&& ent) noexcept
{
    if (this == &ent)
    {
        return *this;
    }

    FreeMemory();

    card = ent.card;
    m_owner = ent.m_owner;

    auraEffects = ent.auraEffects;
    onGoingEffect = ent.onGoingEffect;
    m_gameTags = ent.m_gameTags;

    return *this;
}

Player& Entity::GetOwner() const
{
    return *m_owner;
}

void Entity::SetOwner(Player& owner)
{
    m_owner = &owner;
}

int Entity::GetGameTag(GameTag tag) const
{
    if (m_gameTags.find(tag) == m_gameTags.end())
    {
        return 0;
    }

    if (auraEffects != nullptr)
    {
        return m_gameTags.at(tag) + auraEffects->GetGameTag(tag);
    }

    return m_gameTags.at(tag);
}

void Entity::SetGameTag(GameTag tag, int value)
{
    m_gameTags.insert_or_assign(tag, value);
}

void Entity::Destroy()
{
    isDestroyed = true;
}

Entity* Entity::GetFromCard(Player& player, Card&& card)
{
    Entity* result;

    switch (card.cardType)
    {
        case CardType::HERO:
            result = new Hero(player, card);
            break;
        case CardType::HERO_POWER:
            result = new HeroPower(player, card);
            break;
        case CardType::MINION:
            result = new Minion(player, card);
            break;
        case CardType::SPELL:
            result = new Spell(player, card);
            break;
        case CardType::WEAPON:
            result = new Weapon(player, card);
            break;
        default:
            throw std::invalid_argument(
                "Generic::DrawCard() - Invalid card type!");
    }

    // Set entity ID
    result->id = player.GetGame()->GetNextID();

    return result;
}

void Entity::FreeMemory()
{
    delete auraEffects;
    delete onGoingEffect;

    m_gameTags.clear();
}
}  // namespace RosettaStone
