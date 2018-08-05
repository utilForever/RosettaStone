/*************************************************************************
> File Name: DestroyWeapon.h
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implement DestroyWeapon
> Created Time: 2018/07/22
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_HEAL_FULL_TASK_H
#define HEARTHSTONEPP_HEAL_FULL_TASK_H

#include <Tasks/Tasks.h>

namespace Hearthstonepp::PowerTask
{
class HealFullTask : public ITask
{
 public:
    HealFullTask(EntityType entityType);

 private:
    EntityType m_entityType;
    MetaData Impl(Player& player1, Player& player2) override;
};
}  // namespace Hearthstonepp::PowerTask

#endif  // HEARTHSTONEPP_HEAL_FULL_TASK_H
