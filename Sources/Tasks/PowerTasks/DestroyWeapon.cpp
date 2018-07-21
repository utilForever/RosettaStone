/*************************************************************************
> File Name: DestroyWeapon.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: 
> Created Time: 2018/07/22
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Tasks/PowerTasks/DestroyWeapon.h>

namespace Hearthstonepp::PowerTask
{
PowerTaskType DestroyWeapon::GetPowerType() const
{
    return PowerTaskType::DESTROY_OPPONENT_WEAPON;
}

MetaData DestroyWeapon::Impl(Player& player1, Player& player2) const
{
    player2.weapon = nullptr;
    return MetaData::INVALID;
}
}