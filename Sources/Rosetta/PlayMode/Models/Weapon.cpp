// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/PlayMode/Models/Player.hpp>
#include <Rosetta/PlayMode/Models/Weapon.hpp>

#include <utility>

namespace RosettaStone::PlayMode
{
Weapon::Weapon(Player* player, Card* card, std::map<GameTag, int> tags, int id)
    : Playable(player, card, std::move(tags), id)
{
    // Do nothing
}

Weapon::~Weapon()
{
    player->GetHero()->weapon = nullptr;
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

    // Destroy weapon if durability is 0
    if (GetDurability() <= 0)
    {
        Destroy();
        player->GetHero()->RemoveWeapon();
    }
}

void Weapon::RemoveDurability(int amount)
{
    SetDurability(GetDurability() - amount);
}

bool Weapon::IsImmune() const
{
    return static_cast<bool>(GetGameTag(GameTag::IMMUNE));
}

bool Weapon::HasPoisonous() const
{
    return static_cast<bool>(GetGameTag(GameTag::POISONOUS));
}
}  // namespace RosettaStone::PlayMode
