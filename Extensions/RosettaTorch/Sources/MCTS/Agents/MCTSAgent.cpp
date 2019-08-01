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

void MCTSAgent::Think(const GameConfig& gameConfig)
{
    m_agent.BeforeThink();

    m_controller.reset(new MCTSRunner(m_config));
    m_controller->Run(gameConfig);

    while (true)
    {
        uint64_t iterations =
            m_controller->GetStatistics().GetSuccededIterates();
        m_agent.Think(iterations);

        if (iterations >= static_cast<uint64_t>(m_config.iterationsPerAction))
        {
            break;
        }

        std::this_thread::sleep_for(
            std::chrono::milliseconds(m_config.callbackInterval));
    }

    m_controller->WaitUntilStopped();

    m_agent.AfterThink(m_controller->GetStatistics().GetSuccededIterates());

    m_node = m_controller->GetRootNode(gameConfig.startPlayer);
    m_rootNode = m_node;
}
}  // namespace RosettaTorch::Agents