// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_TREE_UPDATER_HPP
#define ROSETTASTONE_TORCH_MCTS_TREE_UPDATER_HPP

#include <MCTS/Commons/Constants.hpp>
#include <MCTS/Selection/TraversedNodeInfo.hpp>

#include <queue>

namespace RosettaTorch::MCTS
{
//!
//! \brief TreeUpdater class.
//!
//! This class updates node info by adding credit.
//!
class TreeUpdater
{
 public:
    //! Default constructor.
    TreeUpdater() = default;

    //! Deleted copy constructor.
    TreeUpdater(const TreeUpdater&) = delete;

    //! Deleted move constructor.
    TreeUpdater(TreeUpdater&&) noexcept = delete;

    //! Deleted copy assignment operator.
    TreeUpdater& operator=(const TreeUpdater&) = delete;

    //! Deleted move assignment operator.
    TreeUpdater& operator=(TreeUpdater&&) noexcept = delete;

    //! Updates node info by adding credit for linear update.
    //! \param nodes A list of node to update.
    //! \param credit The value of credit to update.
    template <class RetType = void>
    auto Update(const std::vector<TraversedNodeInfo>& nodes, float credit)
        -> std::enable_if_t<std::is_same_v<UpdaterPolicy, LinearUpdate>,
                            RetType>
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

    //! Updates node info by adding credit for tree update.
    //! \param nodes A list of node to update.
    //! \param credit The value of credit to update.
    template <class RetType = void>
    auto Update(const std::vector<TraversedNodeInfo>& nodes, float credit)
        -> std::enable_if_t<std::is_same_v<UpdaterPolicy, TreeUpdate>, RetType>
    {
        if (nodes.empty())
        {
            return;
        }

        for (auto it = nodes.crbegin(); it != nodes.crend(); ++it)
        {
            if (!it->edgeAddon)
            {
                continue;
            }

            TreeLikeUpdateWinRate(it->node, it->edgeAddon, credit);
            break;
        }

        return;
    }

 private:
    //! Pushes start node/edge to BFS and iterates until it is empty.
    //! \param startNode The start node to push to BFS.
    //! \param startEdge The start edge to push to BFS.
    //! \param credit The value of credit to update.
    template <class RetType = void>
    auto TreeLikeUpdateWinRate(TreeNode* startNode, EdgeAddon* startEdge,
                               float credit)
        -> std::enable_if_t<std::is_same_v<UpdaterPolicy, TreeUpdate>, RetType>
    {
        m_bfs.push({ startNode, startEdge });

        while (!m_bfs.empty())
        {
            auto node = m_bfs.front().node;
            auto* edgeAddon = m_bfs.front().edgeAddon;
            m_bfs.pop();

            if (edgeAddon)
            {
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
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_TREE_UPDATER_HPP