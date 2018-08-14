/*************************************************************************
> File Name: FreezeTask.h
> Project Name: Hearthstonepp
> Author: Seung-Hyun Jeon
> Purpose: Implement Freeze
> Created Time: 2018/08/14
> Copyright (c) 2018, Seung-Hyun Jeon
*************************************************************************/
#ifndef HEARTHSTONEPP_FREEZE_TASK_H
#define HEARTHSTONEPP_FREEZE_TASK_H

#include <Tasks/Tasks.h>

namespace Hearthstonepp::PowerTask
{
    class FreezeTask : public ITask
    {
    public:
        FreezeTask(Character* target, int turn);

        TaskID GetTaskID() const override;

    private:
        Character* m_target;
        int m_turn;

        MetaData Impl(Player& player1, Player& player2) override;
    };
}  // namespace Hearthstonepp::PowerTask

#endif  // HEARTHSTONEPP_FREEZE_TASK_H
