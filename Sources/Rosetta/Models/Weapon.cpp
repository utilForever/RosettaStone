// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Models/Weapon.hpp>

namespace RosettaStone
{
Weapon::Weapon(Player& _owner, Card& _card) : Entity(_owner, _card)
{
    durability = _card.durability ? *_card.durability : 0;
}

Weapon::~Weapon()
{
    GetOwner().GetHero()->weapon = nullptr;
}

int Weapon::GetAttack() const
{
    return GetGameTag(GameTag::ATK);
}

void Weapon::SetAttack(int attack)
{
    SetGameTag(GameTag::ATK, attack);
}
}  // namespace RosettaStone
