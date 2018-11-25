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
#if defined(HEARTHSTONEPP_WINDOWS) || defined(HEARTHSTONEPP_LINUX)
    m_attack = card.attack.has_value() ? card.attack.value() : 0;
    m_durability = card.durability.has_value() ? card.durability.value() : 0;
#elif defined(HEARTHSTONEPP_MACOSX)
    m_attack = card.attack.value_or(0);
    m_durability = card.durability.value_or(0);
#endif
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