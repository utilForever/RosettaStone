/*************************************************************************
> File Name: PlayWeapon.h
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implement PlayWeapon
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_PLAYWEAPON_H
#define HEARTHSTONEPP_PLAYWEAPON_H

#include <Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
class PlayWeaponTask : public ITask
{
 public:
    PlayWeaponTask(Entity* entity);

    TaskID GetTaskID() const override;

 private:
    Entity* m_entity;

    MetaData Impl(Player& player1, Player& player2) override;
};
}  // namespace Hearthstonepp::BasicTasks

#endif  // HEARTHSTONEPP_PLAYWEAPON_H
