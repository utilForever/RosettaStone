/*************************************************************************
> File Name: ModifyMana.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implement ModifyManaTask
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Tasks/BasicTasks/ModifyManaTask.h>

#include <algorithm>

namespace Hearthstonepp::BasicTasks
{
MetaData ImplModifyMana(Player& user, NumMode numMode, ManaMode manaMode,
                        BYTE num)
{
    auto get = [](Player& user, ManaMode mode) -> BYTE& {
        if (mode == ManaMode::EXIST)
            return user.existMana;
        else if (mode == ManaMode::TOTAL)
            return user.totalMana;
        else
            throw std::runtime_error("ImplModifyMana : Invalid ManaMode");
    };

    BYTE& mana = get(user, manaMode);
    switch (numMode)
    {
        case NumMode::ADD:
            mana += num;
            break;
        case NumMode::SUB:
            mana -= num;
            break;
        case NumMode::SYNC:
            mana = num;
            break;
    }

    // Mana overflow
    if (mana > 10)
    {
        mana = 10;
    }
    // Mana underflow
    else if (mana < 0)
    {
        mana = 0;
    }

    return MetaData::MODIFY_MANA_SUCCESS;
}

ModifyManaTask::ModifyManaTask(NumMode numMode, ManaMode manaMode, BYTE num)
    : m_numMode(numMode), m_manaMode(manaMode), m_num(num)
{
    // Do Nothing
}

TaskID ModifyManaTask::GetTaskID() const
{
    return TaskID::MODIFY_MANA;
}

MetaData ModifyManaTask::Impl(Player& player1, Player&)
{
    return ImplModifyMana(player1, m_numMode, m_manaMode, m_num);
}

ModifyManaByRef::ModifyManaByRef(NumMode numMode, ManaMode manaMode,
                                 const BYTE& ref)
    : m_numMode(numMode), m_manaMode(manaMode), m_num(ref)
{
    // Do Nothing
}

TaskID ModifyManaByRef::GetTaskID() const
{
    return TaskID::MODIFY_MANA;
}

MetaData ModifyManaByRef::Impl(Player& player1, Player&)
{
    return ImplModifyMana(player1, m_numMode, m_manaMode, m_num);
}
}  // namespace Hearthstonepp::BasicTasks