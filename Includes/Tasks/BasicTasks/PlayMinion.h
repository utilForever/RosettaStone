/*************************************************************************
> File Name: PlayMinion.h
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose:
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_PLAYMINION_H
#define HEARTHSTONEPP_PLAYMINION_H

#include <Tasks/BasicTasks/Requirement.h>
#include <Tasks/TaskAgent.h>
#include <Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
class PlayMinionTask : public ITask
{
 public:
    PlayMinionTask(TaskAgent& agent, Entity* entity);
    TaskID GetTaskID() const override;

 private:
    Entity* m_entity;
    Requirement m_requirement;
    MetaData Impl(Player& player1, Player& player2) const override;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_PLAYMINION_H
