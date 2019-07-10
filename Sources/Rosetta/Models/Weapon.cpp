// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Models/Weapon.hpp>

#include <utility>

namespace RosettaStone
{
Weapon::Weapon(Player& _owner, Card* _card, std::map<GameTag, int> tags)
    : Entity(_owner, _card, std::move(tags))
{
    // Do nothing
}

Weapon::~Weapon()
{
    owner->GetHero()->weapon = nullptr;
}

int Weapon::GetAttack() const
{
    return GetGameTag(GameTag::ATK);
}

void Weapon::SetAttack(int attack)
{
    SetGameTag(GameTag::ATK, attack);
}

int Weapon::GetDurability() const
{
    return GetGameTag(GameTag::DURABILITY);
}

void Weapon::SetDurability(int durability)
{
    SetGameTag(GameTag::DURABILITY, durability);
}
}  // namespace RosettaStone
