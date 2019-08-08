// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_TREE_NODE_ADDON_HPP
#define ROSETTASTONE_TORCH_MCTS_TREE_NODE_ADDON_HPP

#include <MCTS/Commons/Constants.hpp>
#include <MCTS/Selection/BoardNodeMap.hpp>
#include <MCTS/Selection/ConsistencyCheckAddon.hpp>
#include <MCTS/Selection/LeadingNodes.hpp>

namespace RosettaTorch::MCTS
{
//!
//! \brief TreeNodeAddon struct.
//!
//! This struct contains consistency check addon, board node map and
//! conditional leading nodes for recording.
//!
struct TreeNodeAddon
{
    struct Dummy
    {
        // Do nothing
    };

    ConsistencyCheckAddon consistencyChecker;
    BoardNodeMap boardNodeMap;
    std::conditional_t<RECORD_LEADING_NODES, LeadingNodes, Dummy> leadingNodes;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_TREE_NODE_ADDON_HPP