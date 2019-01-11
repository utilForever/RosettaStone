// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Cards/Hero.hpp>

namespace Hearthstonepp
{
Hero::Hero(GameAgent* gameAgent, Card& card) : Character(gameAgent, card)
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

size_t Hero::GetAttack() const
{
    return weapon != nullptr ? m_attack + weapon->GetAttack() : m_attack;
}
}  // namespace Hearthstonepp