// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Models/Entity.hpp>
#include <hspp/Models/Player.hpp>

namespace Hearthstonepp
{
Entity::Entity(Player& _owner, Card& _card)
    : card(new Card(_card)), m_owner(&_owner)
{
    for (auto& mechanic : _card.mechanics)
    {
        Entity::SetGameTag(mechanic, 1);
    }
}

Entity::Entity(const Entity& ent) : m_owner(ent.m_owner)
{
    FreeMemory();

    card = ent.card;
    m_owner = ent.m_owner;
    m_gameTags = ent.m_gameTags;
}

Entity::Entity(Entity&& ent) noexcept : m_owner(ent.m_owner)
{
    FreeMemory();

    card = ent.card;
    m_owner = ent.m_owner;
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

    return m_gameTags.at(tag);
}

void Entity::SetGameTag(GameTag tag, int value)
{
    m_gameTags.insert_or_assign(tag, value);
}

void Entity::Destroy()
{
    // Do nothing
}

Entity* Entity::GetFromCard(Player& player, Card card)
{
    Entity* result;

    switch (card.cardType)
    {
        case +CardType::MINION:
            result = new Minion(player, card);
            break;
        case +CardType::SPELL:
            result = new Spell(player, card);
            break;
        case +CardType::WEAPON:
            result = new Weapon(player, card);
            break;
        default:
            throw std::invalid_argument(
                "Generic::DrawCard() - Invalid card type!");
    }

    return result;
}

void Entity::FreeMemory()
{
    m_gameTags.clear();

    delete card;
}
}  // namespace Hearthstonepp