/*************************************************************************
> File Name: Requirement.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implement Requirement, Interact with GameInterface
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Tasks/BasicTasks/Requirement.h>

namespace Hearthstonepp::BasicTasks
{
Requirement::Requirement(TaskID request, TaskAgent &agent)
    : m_request(request), m_agent(agent)
{
    // Do Nothing
}

void Requirement::Interact(BYTE userID, TaskMeta &meta) const
{
    meta = Serializer::CreateRequire(m_request, userID);

    // Notify TaskMeta to main channel
    m_agent.Notify(std::move(meta));
    // Read TaskMeta from side channel
    m_agent.Read(meta, true);
}
}  // namespace Hearthstonepp::BasicTasks