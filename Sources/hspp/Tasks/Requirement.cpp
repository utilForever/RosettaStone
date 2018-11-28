// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/Requirement.hpp>

namespace Hearthstonepp
{
Requirement::Requirement(TaskID request, TaskAgent& agent)
    : m_request(request), m_agent(agent)
{
    // Do nothing
}

void Requirement::Interact(BYTE userID, TaskMeta& meta) const
{
    meta = Serializer::CreateRequire(m_request, userID);

    // Notify TaskMeta to main channel
    m_agent.Notify(std::move(meta));
    // Read TaskMeta from side channel
    m_agent.Read(meta, true);
}
}  // namespace Hearthstonepp