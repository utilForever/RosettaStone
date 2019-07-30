// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_AGENTS_MCTS_AGENT_HPP
#define ROSETTASTONE_TORCH_AGENTS_MCTS_AGENT_HPP

#include <Agents/MCTSConfig.hpp>
#include <Agents/MCTSRunner.hpp>
#include <MCTS/Selection/TreeNode.hpp>

namespace RosettaTorch::Agents
{
class MCTSAgent
{
 private:
    MCTSConfig m_config;
    const MCTS::TreeNode* m_rootNode;
    const MCTS::TreeNode* m_node;
    std::unique_ptr<MCTSRunner> m_controller;
};
}  // namespace RosettaTorch::Agents

#endif  // ROSETTASTONE_TORCH_AGENTS_MCTS_AGENT_HPP