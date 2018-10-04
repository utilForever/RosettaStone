// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Cards/Character.h>
#include <hspp/Commons/Macros.h>

namespace Hearthstonepp
{
Character::Character(const Card* pCard) : Entity(pCard)
{
    if (pCard != nullptr)
    {
#ifndef HEARTHSTONEPP_MACOSX
        attack = pCard->attack.has_value() ? pCard->attack.value() : 0;
        health = pCard->health.has_value() ? pCard->health.value() : 0;
#else
        attack = (pCard->attack != std::experimental::nullopt)
                     ? *(pCard->attack)
                     : 0;
        health = (pCard->health != std::experimental::nullopt)
                     ? *(pCard->health)
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

Character* Character::Clone() const
{
    return new Character(*this);
}
}  // namespace Hearthstonepp