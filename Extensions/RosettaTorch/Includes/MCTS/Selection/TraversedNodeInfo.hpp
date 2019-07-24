// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_TRAVERSED_NODE_INFO_HPP
#define ROSETTASTONE_TORCH_MCTS_TRAVERSED_NODE_INFO_HPP

#include <MCTS/Selection/TreeNode.hpp>

namespace RosettaTorch::MCTS
{
//!
//! \brief TraversedNodeInfo struct.
//!
struct TraversedNodeInfo
{
    TraversedNodeInfo(TreeNode* _node, EdgeAddon* _edgeAddon, int _choice)
        : node(_node), edgeAddon(_edgeAddon), choice(_choice)
    {
        // Do nothing
    }

    TreeNode* node;
    EdgeAddon* edgeAddon;
    int choice;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_TRAVERSED_NODE_INFO_HPP