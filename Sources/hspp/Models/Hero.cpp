// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Models/Hero.hpp>

namespace Hearthstonepp
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

void Hero::Summon(std::size_t pos)
{
    (void)pos;
    // Do nothing
}

void Hero::Destroy()
{
    // Do nothing
}

bool Hero::HasWeapon() const
{
    return weapon != nullptr;
}

std::size_t Hero::GetAttack() const
{
    return weapon != nullptr ? attack + weapon->attack : attack;
}
}  // namespace Hearthstonepp