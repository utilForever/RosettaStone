/*************************************************************************
> File Name: ModifyHealth.h
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implement ModifyHealthTask
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_MODIFYHEALTH_H
#define HEARTHSTONEPP_MODIFYHEALTH_H

#include <Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
class ModifyHealthTask : public ITask
{
 public:
    ModifyHealthTask(Character* character, BYTE damage);
    TaskID GetTaskID() const override;

 private:
    Character* m_character;
    BYTE m_damage;

    MetaData Impl(Player& player1, Player& player2) override;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_MODIFYHEALTH_H
