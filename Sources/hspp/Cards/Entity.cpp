// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Cards/Entity.h>

namespace Hearthstonepp
{
Entity::Entity(Card& _card) : card(new Card(_card))
{
    for (auto& mechanic : card->mechanics)
    {
        gameTags.insert(std::make_pair(mechanic, 1));
    }
}

Entity::Entity(const Entity& ent)
{
    FreeMemory();

    card = ent.card;
    gameTags = ent.gameTags;
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
    gameTags = ent.gameTags;

    return *this;
}

Entity* Entity::Clone() const
{
    return new Entity(*this);
}

void Entity::SetAbility(GameTag tag, bool flag)
{
    gameTags.insert_or_assign(tag, flag);
}

void Entity::FreeMemory()
{
    gameTags.clear();

    delete card;
}
}  // namespace Hearthstonepp