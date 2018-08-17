/*************************************************************************
> File Name: DiscardTask.h
> Project Name: Hearthstonepp
> Author: Sungkuk Park
> Purpose: Implement DiscardTask
> Created Time: 2018/08/15
> Copyright (c) 2018, Sungkuk Park
*************************************************************************/
#ifndef HEARTHSTONEPP_DISCARD_TASK_H
#define HEARTHSTONEPP_DISCARD_TASK_H

#include <Tasks/Tasks.h>

namespace Hearthstonepp::PowerTask
{
class DiscardTask : public ITask
{
 public:
    DiscardTask(EntityType entityType);

    TaskID GetTaskID() const override;

 private:
    EntityType m_entityType;

    MetaData Impl(Player& player1, Player& player2) override;
};
}  // namespace Hearthstonepp::PowerTask

#endif  // HEARTHSTONEPP_DISCARD_TASK_H