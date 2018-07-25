/*************************************************************************
> File Name: DestroyWeapon.h
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implement DestroyWeapon
> Created Time: 2018/07/22
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_DESTROYWEAPON_H
#define HEARTHSTONEPP_DESTROYWEAPON_H

#include <Tasks/PowerTask.h>

namespace Hearthstonepp::PowerTask
{
class DestroyWeapon : public IPower
{
 public:
    PowerTaskType GetPowerType() const override;

 private:
    MetaData Impl(Player& player1, Player& player2) const override;
};
}  // namespace Hearthstonepp::PowerTask

#endif  // HEARTHSTONEPP_DESTROYWEAPON_H
