// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_LEADING_NODES_HPP
#define ROSETTASTONE_TORCH_MCTS_LEADING_NODES_HPP

#include <MCTS/Selection/BoardNodeMap.hpp>
#include <MCTS/Selection/EdgeAddon.hpp>

#include <Rosetta/Common/SpinLocks.hpp>
#include <Rosetta/Common/Utils.hpp>

#include <mutex>

namespace RosettaTorch::MCTS
{
//!
//! \brief LeadingNodesItem struct.
//!
//! This struct contains tree node and edge addon.
//!
struct LeadingNodesItem
{
    //! Operator overloading: operator==.
    bool operator==(const LeadingNodesItem& rhs) const;

    //! Operator overloading: operator!=.
    bool operator!=(const LeadingNodesItem& rhs) const;

    TreeNode* node;
    EdgeAddon* edgeAddon;
};
}  // namespace RosettaTorch::MCTS

namespace std
{
//! \brief Template specialization of std::hash for LeadingNodesItem.
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
//! This class represents the lead of the tree node.
//!
class LeadingNodes
{
 public:
    //! Adds the leading node to items.
    //! \param node A pointer pointing to add the leading node.
    //! \param edgeAddon The edge addon of the leading node.
    void AddLeadingNodes(TreeNode* node, EdgeAddon* edgeAddon);

    //! Iterates something for each leading node.
    //! \param functor A function to run for each leading node.
    template <typename Functor>
    void ForEachLeadingNode(Functor&& functor)
    {
        std::shared_lock<RosettaStone::SharedSpinLock> lock(m_mutex);
        for (const auto& item : m_items)
        {
            if (!functor(item.node, item.edgeAddon))
            {
                break;
            }
        }
    }

 private:
    mutable RosettaStone::SharedSpinLock m_mutex;
    std::vector<LeadingNodesItem> m_items;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_LEADING_NODES_HPP