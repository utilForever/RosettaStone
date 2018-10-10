// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Cards/Character.h>
#include <hspp/Commons/Macros.h>

namespace Hearthstonepp
{
Character::Character(Card& card) : Entity(card)
{
    if (!card.id.empty())
    {
#ifndef HEARTHSTONEPP_MACOSX
        attack = card.attack.has_value() ? card.attack.value() : 0;
        health = card.health.has_value() ? card.health.value() : 0;
#else
        attack = (card.attack != std::experimental::nullopt)
                     ? card.attack
                     : 0;
        health = card.health != std::experimental::nullopt)
                     ? card.health
                     : 0;
#endif
        maxHealth = health;
    }
}

Character::Character(const Character& c) : Entity(c)
{
    attack = c.attack;
    attackableCount = c.attackableCount;
    health = c.health;
    maxHealth = c.maxHealth;
}

Character& Character::operator=(const Character& c)
{
    if (this == &c)
    {
        return *this;
    }

    attack = c.attack;
    attackableCount = c.attackableCount;
    health = c.health;
    maxHealth = c.maxHealth;

    return *this;
}

Character* Character::Clone() const
{
    return new Character(*this);
}
}  // namespace Hearthstonepp