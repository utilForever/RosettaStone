// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Cards/Entity.h>

namespace Hearthstonepp
{
Entity::Entity(const Card* pCard) : card(pCard)
{
    // Do nothing
}

Entity::Entity(const Entity& ent)
{
    gameTags.clear();
    delete card;

    card = ent.card;
    gameTags = ent.gameTags;
}

Entity* Entity::Clone() const
{
    return new Entity(*this);
}
}  // namespace Hearthstonepp