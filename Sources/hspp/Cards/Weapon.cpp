// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Cards/Weapon.h>
#include <hspp/Commons/Macros.h>

namespace Hearthstonepp
{
Weapon::Weapon(Card& card) : Entity(card)
{
#ifndef HEARTHSTONEPP_MACOSX
    attack = card.attack.has_value() ? card.attack.value() : 0;
    durability = card.durability.has_value() ? card.durability.value() : 0;
#else
    attack = card.attack.value_or(0);
    durability = card.durability.value_or(0);
#endif
}

Weapon::Weapon(const Weapon& weapon) : Entity(weapon)
{
    attack = weapon.attack;
    durability = weapon.durability;
}

Weapon& Weapon::operator=(const Weapon& weapon)
{
    if (this == &weapon)
    {
        return *this;
    }

    attack = weapon.attack;
    durability = weapon.durability;

    return *this;
}

Weapon* Weapon::Clone() const
{
    return new Weapon(*this);
}
}  // namespace Hearthstonepp