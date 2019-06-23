// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_TREE_NODE_ADDON_HPP
#define ROSETTASTONE_TORCH_MCTS_TREE_NODE_ADDON_HPP

namespace RosettaTorch::MCTS
{
//!
//! \brief LeadingNodesItem struct.
//!
struct LeadingNodesItem
{
    bool operator==(const LeadingNodesItem& v) const
    {
        if (node != v.node)
        {
            return false;
        }
        if (edgeAddon != v.edgeAddon)
        {
            return false;
        }
        return true;
    }

    bool operator!=(const LeadingNodesItem& v) const
    {
        return !(*this == v);
    }

    TreeNode* node;
    EdgeAddon* edgeAddon;
};
}  // namespace RosettaTorch::MCTS

namespace std
{
template <>
struct hash<RosettaTorch::MCTS::LeadingNodesItem>
{
    std::size_t operator()(
        const RosettaTorch::MCTS::LeadingNodesItem& rhs) const noexcept
    {
        std::size_t result =
            std::hash<RosettaTorch::MCTS::TreeNode*>()(rhs.node);
        CombineHash(result, rhs.edgeAddon);

        return result;
    }
};
}  // namespace std

namespace RosettaTorch::MCTS
{
//!
//! \brief LeadingNodes class.
//!
class LeadingNodes
{
 public:
    void AddLeadingNodes(TreeNode* node, EdgeAddon* edge_addon)
    {
        std::lock_guard<RosettaStone::SharedSpinLock> lock(m_mutex);
        assert(node);

        for (const auto& item : m_items)
        {
            if (item.node == node && item.edgeAddon == edge_addon)
            {
                return;
            }
        }

        m_items.push_back(LeadingNodesItem{ node, edge_addon });
    }

    template <class Functor>
    void ForEachLeadingNode(Functor&& op)
    {
        std::shared_lock<RosettaStone::SharedSpinLock> lock(m_mutex);
        for (const auto& item : m_items)
        {
            if (!op(item.node, item.edgeAddon))
            {
                break;
            }
        }
    }

 private:
    mutable RosettaStone::SharedSpinLock m_mutex;
    std::vector<LeadingNodesItem> m_items;
};

//!
//! \brief TreeNodeAddon struct.
//!
struct TreeNodeAddon
{
    struct Dummy
    {
        // Do nothing
    };

    BoardNodeMap boardNodeMap;
    std::conditional_t<Configs::RECORD_LEADING_NODES, LeadingNodes, Dummy>
        leadingNodes;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_TREE_NODE_ADDON_HPP