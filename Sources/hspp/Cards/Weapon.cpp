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
    m_attack = card.attack.has_value() ? card.attack.value() : 0;
    m_durability = card.durability.has_value() ? card.durability.value() : 0;
#else
    m_attack = card.attack.value_or(0);
    m_durability = card.durability.value_or(0);
#endif
}

Weapon::Weapon(const Weapon& weapon) : Entity(weapon)
{
    m_attack = weapon.m_attack;
    m_durability = weapon.m_durability;
}

Weapon& Weapon::operator=(const Weapon& weapon)
{
    if (this == &weapon)
    {
        return *this;
    }

    m_attack = weapon.m_attack;
    m_durability = weapon.m_durability;

    return *this;
}

size_t Weapon::GetAttack() const
{
    return m_attack;
}

void Weapon::SetAttack(size_t attack)
{
    m_attack = attack;
}

size_t Weapon::GetDurability() const
{
    return m_durability;
}

void Weapon::SetDurability(size_t durability)
{
    m_durability = durability;
}

Weapon* Weapon::Clone() const
{
    return new Weapon(*this);
}
}  // namespace Hearthstonepp