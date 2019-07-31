// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_AGENTS_MCTS_AGENT_HPP
#define ROSETTASTONE_TORCH_AGENTS_MCTS_AGENT_HPP

#include <Agents/IAgent.hpp>
#include <Agents/MCTSConfig.hpp>
#include <Agents/MCTSRunner.hpp>
#include <MCTS/Selection/TreeNode.hpp>

namespace RosettaTorch::Agents
{
//!
//! \brief MCTSAgent class.
//!
//! This class is simple agent to run MCTS runner.
//!
class MCTSAgent
{
 public:
    //! Constructs MCTS agent with given \p config and \p agent.
    //! \param config The MCTS config.
    //! \param agent The agent to define Think() related methods.
    MCTSAgent(const MCTSConfig& config, IAgent& agent);

    //! Deleted copy constructor.
    MCTSAgent(const MCTSAgent&) = delete;

    //! Deleted move constructor.
    MCTSAgent(MCTSAgent&&) noexcept = delete;

    //! Deleted copy assignment operator.
    MCTSAgent& operator=(const MCTSAgent&) = delete;

    //! Deleted move assignment operator.
    MCTSAgent& operator=(MCTSAgent&&) noexcept = delete;

    //! Process Think() related methods.
    void Think();

    //! Returns action according to \p actionType and \p choices.
    //! \param actionType The type of action.
    //! \param choices The choices of action.
    //! \return The index of chosen action.
    int GetAction(ActionType actionType, ActionChoices choices);

 private:
    MCTSConfig m_config;
    const MCTS::TreeNode* m_rootNode = nullptr;
    const MCTS::TreeNode* m_node = nullptr;
    std::unique_ptr<MCTSRunner> m_controller = nullptr;
    IAgent& m_agent;
};
}  // namespace RosettaTorch::Agents

#endif  // ROSETTASTONE_TORCH_AGENTS_MCTS_AGENT_HPP