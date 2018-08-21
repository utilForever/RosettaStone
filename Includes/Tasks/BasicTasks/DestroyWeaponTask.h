/*************************************************************************
> File Name: DestroyWeaponTask.h
> Project Name: Hearthstonepp
> Author: SeungHyun Jeon
> Purpose: Implement DestroyWeapon
> Created Time: 2018/08/21
> Copyright (c) 2018, SeungHyun Jeon
*************************************************************************/
#ifndef HEARTHSTONEPP_DESTROYWEAPONTASK_H
#define HEARTHSTONEPP_DESTROYWEAPONTASK_H

#include <Cards/Hero.h>
#include <Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
class DestroyWeaponTask : public ITask
{
 public:
    DestroyWeaponTask();

    TaskID GetTaskID() const override;

 private:
    MetaData Impl(Player& player1, Player& player2) override;
};
}  // namespace Hearthstonepp::BasicTask

#endif //HEARTHSTONEPP_DESTROYWEAPONTASK_H
