/*************************************************************************
> File Name: PoisonousTask.h
> Project Name: Hearthstonepp
> Author: Seung-Hyun Jeon
> Purpose: Implement Poisonous
> Created Time: 2018/08/12
> Copyright (c) 2018, Seung-Hyun Jeon
*************************************************************************/
#ifndef HEARTHSTONEPP_POISONOUS_TASK_H
#define HEARTHSTONEPP_POISONOUS_TASK_H

#include <Tasks/Tasks.h>

namespace Hearthstonepp::PowerTask
{
class PoisonousTask : public ITask
{
 public:
    PoisonousTask(Character* source, Character* target);

    TaskID GetTaskID() const override;

 private:
    Character* m_source;
    Character* m_target;

    MetaData Impl(Player& player1, Player& player2) override;
};
}  // namespace Hearthstonepp::PowerTask

#endif  // HEARTHSTONEPP_POISONOUS_TASK_H
