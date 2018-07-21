/*************************************************************************
> File Name: PlayCard.h
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose:
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_PLAYCARD_H
#define HEARTHSTONEPP_PLAYCARD_H

#include <Flatbuffers/generated/FlatData_generated.h>
#include <Tasks/BasicTasks/Requirement.h>
#include <Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
class PlayCardTask : public ITask
{
 public:
    PlayCardTask(TaskAgent& agent);
    TaskID GetTaskID() const override;

 private:
    TaskAgent& m_agent;
    Requirement m_requirement;
    MetaData Impl(Player& player1, Player& player2) const override;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_PLAYCARD_H
