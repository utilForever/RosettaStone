// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Models/Hero.hpp>
#include <Rosetta/Models/Player.hpp>

namespace RosettaStone
{
Hero::Hero(Player& _owner, Card& _card) : Character(_owner, _card)
{
    // Do nothing
}

Hero::~Hero()
{
    delete weapon;
    delete heroPower;
}

void Hero::Destroy()
{
    // Do nothing
}

void Hero::AddWeapon(Weapon& _weapon)
{
    RemoveWeapon();

    weapon = &_weapon;
}

void Hero::RemoveWeapon()
{
    if (!HasWeapon())
    {
        return;
    }

    GetOwner().GetGraveyard().AddCard(*weapon);

    weapon = nullptr;
}

bool Hero::HasWeapon() const
{
    return weapon != nullptr;
}

std::size_t Hero::GetAttack() const
{
    return HasWeapon() ? attack + weapon->attack : attack;
}
}  // namespace RosettaStone
