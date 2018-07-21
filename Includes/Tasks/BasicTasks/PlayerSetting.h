/*************************************************************************
> File Name: PlayerSetting.h
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose:
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_PLAYERSETTING_H
#define HEARTHSTONEPP_PLAYERSETTING_H

#include <Tasks/BasicTasks/Requirement.h>
#include <Tasks/TaskAgent.h>
#include <Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
class PlayerSettingTask : public ITask
{
 public:
    PlayerSettingTask(TaskAgent& agent);
    TaskID GetTaskID() const override;

 private:
    TaskAgent& m_agent;
    MetaData Impl(Player& player1, Player& player2) const override;
};
}  // namespace Hearthstonepp::BasicTasks

#endif  // HEARTHSTONEPP_PLAYERSETTING_H
