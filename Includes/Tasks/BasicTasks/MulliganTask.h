/*************************************************************************
> File Name: Mulligan.h
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implement MulliganTask
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_MULLIGAN_H
#define HEARTHSTONEPP_MULLIGAN_H

#include <Tasks/BasicTasks/RequirementTask.h>
#include <Tasks/TaskAgent.h>
#include <Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
class MulliganTask : public ITask
{
 public:
    MulliganTask(TaskAgent& agent);
    TaskID GetTaskID() const override;

 private:
    TaskAgent& m_agent;
    Requirement m_requirement;

    MetaData Impl(Player& player1, Player& player2) override;
};
}  // namespace Hearthstonepp::BasicTasks

#endif  // HEARTHSTONEPP_MULLIGAN_H
