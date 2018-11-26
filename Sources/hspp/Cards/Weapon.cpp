// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Cards/Weapon.hpp>
#include <hspp/Commons/Macros.hpp>

namespace Hearthstonepp
{
Weapon::Weapon(Card& card) : Entity(card)
{
    m_attack = card.attack ? *card.attack : 0;
    m_durability = card.durability ? *card.durability : 0;
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
}  // namespace Hearthstonepp