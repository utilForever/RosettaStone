/*************************************************************************
> File Name: Combat.h
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implement CombatTask
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_COMBAT_H
#define HEARTHSTONEPP_COMBAT_H

#include <Flatbuffers/generated/FlatData_generated.h>
#include <Tasks/BasicTasks/Requirement.h>
#include <Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
class CombatTask : public ITask
{
 public:
    CombatTask(TaskAgent& agent);

    TaskID GetTaskID() const override;

 private:
    Requirement m_requirement;
    
    MetaData Impl(Player& player1, Player& player2) override;
};
}  // namespace Hearthstonepp::BasicTasks

#endif  // HEARTHSTONEPP_COMBAT_H
