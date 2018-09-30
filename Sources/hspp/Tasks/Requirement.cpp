#include <hspp/Tasks/Requirement.h>

namespace Hearthstonepp::BasicTasks
{
Requirement::Requirement(TaskID request, TaskAgent& agent)
    : m_request(request), m_agent(agent)
{
    // Do Nothing
}

void Requirement::Interact(BYTE userID, TaskMeta& meta) const
{
    meta = Serializer::CreateRequire(m_request, userID);

    // Notify TaskMeta to main channel
    m_agent.Notify(std::move(meta));
    // Read TaskMeta from side channel
    m_agent.Read(meta, true);
}
}  // namespace Hearthstonepp::BasicTasks