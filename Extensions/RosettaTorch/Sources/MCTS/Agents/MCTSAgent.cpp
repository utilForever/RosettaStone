// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Agents/MCTSAgent.hpp>

namespace RosettaTorch::Agents
{
MCTSAgent::MCTSAgent(const MCTSConfig& config, IAgent& agent)
    : m_config(config), m_agent(agent)
{
    // Do nothing
}

void MCTSAgent::Think()
{
    m_agent.BeforeThink();

    m_controller.reset(new MCTSRunner(m_config));
    m_controller->Run();

    while (true)
    {
        uint64_t iterations =
            m_controller->GetStatistics().GetSuccededIterates();
    }
}
}  // namespace RosettaTorch::Agents