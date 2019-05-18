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

int Hero::GetAttack() const
{
    return HasWeapon() ? Character::GetAttack() + weapon->GetAttack()
                       : Character::GetAttack();
}

int Hero::GetArmor() const
{
    return GetGameTag(GameTag::ARMOR);
}

void Hero::SetArmor(int armor)
{
    SetGameTag(GameTag::ARMOR, armor);
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

    owner->GetGraveyardZone().AddCard(*weapon);

    weapon = nullptr;
}

bool Hero::HasWeapon() const
{
    return weapon != nullptr;
}

void Hero::GainArmor(int amount)
{
    SetArmor(GetArmor() + amount);
}
}  // namespace RosettaStone
