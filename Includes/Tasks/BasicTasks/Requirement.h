/*************************************************************************
> File Name: Requirement.h
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: 
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_REQUIREMENT_H
#define HEARTHSTONEPP_REQUIREMENT_H

#include <Enums/TaskEnums.h>
#include <Tasks/TaskAgent.h>

namespace Hearthstonepp::BasicTasks
{
class Requirement
{
public:
    Requirement(TaskID request, TaskAgent& agent);

    void Interact(BYTE userID, TaskMeta& meta) const;

private:
    TaskID m_request;
    TaskAgent& m_agent;
};
}

#endif //HEARTHSTONEPP_REQUIREMENT_H
