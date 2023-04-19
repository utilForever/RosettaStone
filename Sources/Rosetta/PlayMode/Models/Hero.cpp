// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Hero.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>

#include <utility>

namespace RosettaStone::PlayMode
{
Hero::Hero(Player* _player, Card* _card, std::map<GameTag, int> tags, int id)
    : Character(_player, _card, std::move(tags), id)
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

int Hero::GetHeroPowerDamage() const
{
    return GetGameTag(GameTag::HEROPOWER_DAMAGE);
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

    game->triggerManager.OnEquipWeaponTrigger(weapon);

    for (int i = static_cast<int>(weaponAuras.size()) - 1; i >= 0; --i)
    {
        weaponAuras[i]->NotifyEntityAdded(weapon);
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

    for (int i = static_cast<int>(weaponAuras.size()) - 1; i >= 0; --i)
    {
        weaponAuras[i]->NotifyEntityRemoved(weapon);
    }

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

bool Hero::HasHonorableKill() const
{
    if (HasWeapon())
    {
        return weapon->HasHonorableKill();
    }

    return false;
}
}  // namespace RosettaStone::PlayMode
