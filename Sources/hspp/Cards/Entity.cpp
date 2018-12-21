// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Cards/Entity.hpp>

namespace Hearthstonepp
{
Entity::Entity(GameAgent* gameAgent, Card& _card)
    : card(new Card(_card)), m_gameAgent(gameAgent)
{
    for (auto& mechanic : _card.mechanics)
    {
        Entity::SetGameTag(mechanic, 1);
    }
}

Entity::Entity(const Entity& ent) : m_gameAgent(ent.m_gameAgent)
{
    FreeMemory();

    card = ent.card;
    m_gameAgent = ent.m_gameAgent;
    m_gameTags = ent.m_gameTags;
}

Entity::Entity(Entity&& ent) noexcept : m_gameAgent(ent.m_gameAgent)
{
    FreeMemory();

    card = ent.card;
    m_gameAgent = ent.m_gameAgent;
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
    m_gameAgent = ent.m_gameAgent;
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
    m_gameAgent = ent.m_gameAgent;
    m_gameTags = ent.m_gameTags;

    return *this;
}

GameAgent* Entity::GetGameAgent() const
{
    return m_gameAgent;
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

void Entity::FreeMemory()
{
    m_gameTags.clear();

    delete card;
}
}  // namespace Hearthstonepp