/*************************************************************************
> File Name: ModifyMana.h
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implement ModifyManaTask
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_MODIFYMANA_H
#define HEARTHSTONEPP_MODIFYMANA_H

#include <Tasks/Tasks.h>

namespace Hearthstonepp
{
enum class NumMode
{
    ADD = 0,
    SUB = 1,
    SET = 2,
};

enum class ManaMode
{
    TOTAL = 0,
    EXIST = 1,
};

namespace BasicTasks
{
MetaData ImplModifyMana(Player &user, NumMode numMode, ManaMode manaMode,
                        BYTE num);

class ModifyManaTask : public ITask
{
 public:
    ModifyManaTask(NumMode numMode, ManaMode manaMode, BYTE num);

    TaskID GetTaskID() const override;

 private:
    NumMode m_numMode;
    ManaMode m_manaMode;
    BYTE m_num;

    MetaData Impl(Player &player1, Player &player2) override;
};
};  // namespace BasicTasks
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_MODIFYMANA_H
