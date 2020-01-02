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
//! This struct stores traversed node information such as a pointer pointing to
//! traversed node, the edge addon and the index of the node.
//!
struct TraversedNodeInfo
{
    //! Constructs node info with given \p _node, \p _edgeAddon and \p _choice.
    //! \param _node A pointer pointing to traversed node.
    //! \param _edgeAddon The edge addon of the node.
    //! \param _choice The index of the node.
    TraversedNodeInfo(TreeNode* _node, EdgeAddon* _edgeAddon, int _choice);

    TreeNode* node;
    EdgeAddon* edgeAddon;
    int choice;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_TRAVERSED_NODE_INFO_HPP