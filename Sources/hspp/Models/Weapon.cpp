// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Models/Player.hpp>
#include <hspp/Models/Weapon.hpp>

namespace Hearthstonepp
{
Weapon::Weapon(Player& _owner, Card& _card) : Entity(_owner, _card)
{
    m_attack = _card.attack ? *_card.attack : 0;
    m_durability = _card.durability ? *_card.durability : 0;
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

void Weapon::Destroy()
{
    GetOwner().GetHero()->weapon = nullptr;
    delete this;
}
}  // namespace Hearthstonepp