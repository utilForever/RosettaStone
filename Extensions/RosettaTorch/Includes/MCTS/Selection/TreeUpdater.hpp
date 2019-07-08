// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_TREE_UPDATER_HPP
#define ROSETTASTONE_TORCH_MCTS_TREE_UPDATER_HPP

#include <MCTS/Configs.hpp>
#include <MCTS/Selection/TraversedNodeInfo.hpp>

#include <queue>
#include <unordered_set>

namespace RosettaTorch::MCTS
{
//!
//! \brief TreeUpdater class.
//!
class TreeUpdater
{
 public:
    TreeUpdater() = default;

    TreeUpdater(const TreeUpdater&) = delete;
    TreeUpdater& operator=(const TreeUpdater&) = delete;

    template <class RetType = void>
    auto Update(const std::vector<TraversedNodeInfo>& nodes, float credit)
        -> std::enable_if_t<std::is_same_v<UpdatePolicy, LinearUpdate>, RetType>
    {
        for (const auto& item : nodes)
        {
            auto* edgeAddon = item.edgeAddon;
            if (!edgeAddon)
            {
                continue;
            }

            edgeAddon->AddCredit(credit);
        }

        return;
    }

    template <class RetType = void>
    auto Update(const std::vector<TraversedNodeInfo>& nodes, float credit)
        -> std::enable_if_t<std::is_same_v<UpdatePolicy, TreeUpdate>, RetType>
    {
        if (nodes.empty())
        {
            return;
        }

#ifndef NDEBUG
        m_shouldVisits.clear();
        for (auto const& item : nodes)
        {
            if (item.edgeAddon)
            {
                m_shouldVisits.insert(item.edgeAddon);
            }
        }
#endif

        for (auto it = nodes.crbegin(); it != nodes.crend(); ++it)
        {
            if (!it->edgeAddon)
            {
                continue;
            }

            TreeLikeUpdateWinRate(it->node, it->edgeAddon, credit);
            break;
        }

#ifndef NDEBUG
        assert(m_shouldVisits.empty());
#endif

        return;
    }

 private:
    template <class RetType = void>
    auto TreeLikeUpdateWinRate(TreeNode* startNode, EdgeAddon* startEdge,
                               float credit)
        -> std::enable_if_t<std::is_same_v<UpdatePolicy, TreeUpdate>, RetType>
    {
        assert(startNode);

        assert(m_bfs.empty());
        m_bfs.push({ startNode, startEdge });

        while (!m_bfs.empty())
        {
            auto node = m_bfs.front().node;
            auto* edgeAddon = m_bfs.front().edgeAddon;
            m_bfs.pop();

            if (edgeAddon)
            {
#ifndef NDEBUG
                m_shouldVisits.erase(edgeAddon);
#endif
                edgeAddon->AddCredit(credit);
            }

            // Use BFS to reduce the lock time
            node->addon.leadingNodes.ForEachLeadingNode(
                [&](TreeNode* leadingNode, EdgeAddon* leadingEdge) {
                    m_bfs.push({ leadingNode, leadingEdge });
                    return true;
                });
        }

        return;
    }

    struct Item
    {
        TreeNode* node;
        EdgeAddon* edgeAddon;
    };

    std::queue<Item> m_bfs;

#ifndef NDEBUG
    std::unordered_set<EdgeAddon*> m_shouldVisits;
#endif
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_TREE_UPDATER_HPP