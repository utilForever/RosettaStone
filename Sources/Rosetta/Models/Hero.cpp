// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Hero.hpp>
#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Zones/GraveyardZone.hpp>

#include <utility>

namespace RosettaStone
{
Hero::Hero(Player* player, Card* card, std::map<GameTag, int> tags, int id)
    : Character(player, card, std::move(tags), id)
{
    // Do nothing
}

Hero::~Hero()
{
    delete weapon;
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
    weapon->orderOfPlay = game->GetNextOOP();
    weapon->SetZoneType(ZoneType::PLAY);
    weapon->SetZonePosition(0);

    if (weapon->GetGameTag(GameTag::WINDFURY) == 1 && IsExhausted() &&
        GetNumAttacksThisTurn() == 1)
    {
        SetExhausted(false);
    }
}

void Hero::RemoveWeapon()
{
    if (!HasWeapon())
    {
        return;
    }

    if (weapon->HasDeathrattle())
    {
        weapon->ActivateTask(PowerType::DEATHRATTLE);
    }
    game->ProcessTasks();

    game->triggerManager.OnDeathTrigger(weapon);

    player->GetGraveyardZone()->Add(weapon);

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

bool Hero::HasLifesteal() const
{
    if (HasWeapon())
    {
        return weapon->HasLifesteal();
    }

    return false;
}
}  // namespace RosettaStone
