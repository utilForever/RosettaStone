// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <MCTS/Selection/LeadingNodes.hpp>

namespace RosettaTorch::MCTS
{
bool LeadingNodesItem::operator==(const LeadingNodesItem& rhs) const
{
    if (node != rhs.node)
    {
        return false;
    }
    if (edgeAddon != rhs.edgeAddon)
    {
        return false;
    }

    return true;
}

bool LeadingNodesItem::operator!=(const LeadingNodesItem& rhs) const
{
    return !(*this == rhs);
}

void LeadingNodes::AddLeadingNodes(TreeNode* node, EdgeAddon* edgeAddon)
{
    std::lock_guard<SharedSpinLock> lock(m_mutex);
    for (const auto& item : m_items)
    {
        if (item.node == node && item.edgeAddon == edgeAddon)
        {
            return;
        }
    }

    m_items.push_back(LeadingNodesItem{ node, edgeAddon });
}
}  // namespace RosettaTorch::MCTS