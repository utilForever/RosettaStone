// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_TRAVERSED_NODES_INFO_HPP
#define ROSETTASTONE_TORCH_MCTS_TRAVERSED_NODES_INFO_HPP

#include <MCTS/Selection/BoardNodeMap.hpp>
#include <MCTS/Selection/TraversedNodeInfo.hpp>
#include <MCTS/Selection/TreeUpdater.hpp>

#include <Rosetta/Games/Game.hpp>

#include <memory>
#include <vector>

namespace RosettaTorch::MCTS
{
//!
//! \brief TraversedNodesInfo class.
//!
class TraversedNodesInfo
{
 public:
    TraversedNodesInfo()
        : m_newNodeCreated(false), m_currentNode(nullptr), m_pendingChoice(-1)
    {
        // Do nothing
    }

    TraversedNodesInfo(const TraversedNodesInfo&) = delete;
    TraversedNodesInfo& operator=(const TraversedNodesInfo&) = delete;

    void Restart(TreeNode* node)
    {
        m_path.clear();
        m_currentNode = node;
        assert(m_currentNode);
        m_newNodeCreated = false;
        m_pendingChoice = -1;
    }

    TreeNode* GetCurrentNode() const
    {
        return m_currentNode;
    }

    void MakeChoiceForCurrentNode(int choice)
    {
        m_pendingChoice = choice;
    }

    bool HasCurrentNodeMadeChoice() const
    {
        return m_pendingChoice >= 0;
    }

    void ConstructNode()
    {
        assert(m_currentNode);
        assert(m_pendingChoice >= 0);

        auto result = m_currentNode->children.GetOrCreateNewNode(
            m_pendingChoice, std::make_unique<TreeNode>());
        const bool newNodeCreated = std::get<0>(result);
        const auto edgeAddon = std::get<1>(result);
        const auto node = std::get<2>(result);

        assert(node);

        AddPathNode(m_currentNode, m_pendingChoice, edgeAddon, node);
        if (newNodeCreated)
        {
            m_newNodeCreated = true;
        }
    }

    void ConstructRedirectNode(BoardNodeMap* redirectNodeMap,
                               const RosettaStone::Game& game,
                               RosettaStone::PlayState result)
    {
        assert(m_currentNode);
        assert(m_pendingChoice >= 0);

        auto childResult =
            m_currentNode->children.GetOrCreateRedirectNode(m_pendingChoice);
        const bool newNodeCreated = std::get<0>(childResult);
        const auto edgeAddon = std::get<1>(childResult);

        if (newNodeCreated)
        {
            m_newNodeCreated = true;
        }

        if (result != RosettaStone::PlayState::PLAYING)
        {
            // Don't need to construct a node for leaf nodes.
            // We only need the edge to record win-rate, which is already
            // got before.
            TreeNode* nextNode = nullptr;
            AddPathNode(m_currentNode, m_pendingChoice, edgeAddon, nextNode);
        }
        else
        {
            TreeNode* nextNode =
                redirectNodeMap->GetOrCreateNode(game, &m_newNodeCreated);
            assert(nextNode);
            AddPathNode(m_currentNode, m_pendingChoice, edgeAddon, nextNode);
        }
    }

    void JumpToNode(const RosettaStone::Game& game)
    {
        assert(m_currentNode);
        assert(m_pendingChoice < 0);
        TreeNode* nextNode =
            m_currentNode->addon.boardNodeMap.GetOrCreateNode(game);
        AddPathNode(m_currentNode, -1, nullptr, nextNode);
    }

    void Update(float credit)
    {
        for (const auto& path : m_path)
        {
            if (path.edgeAddon)
            {
                if constexpr (VIRTUAL_LOSS != 0)
                {
                    static_assert(VIRTUAL_LOSS > 0);
                    path.edgeAddon->AddCredit(1.0, VIRTUAL_LOSS);
                    assert(path.edgeAddon->GetAverageCredit() >= -1.0);
                    assert(path.edgeAddon->GetAverageCredit() <= 1.0);
                }
            }
        }

        TreeUpdater updater;
        updater.Update(m_path, credit);
    }

    const auto& GetPath() const
    {
        return m_path;
    }

    bool HasNewNodeCreated() const
    {
        return m_newNodeCreated;
    }

 private:
    void AddPathNode(TreeNode* node, int choice, EdgeAddon* edgeAddon,
                     TreeNode* nextNode)
    {
        if (edgeAddon)
        {
            edgeAddon->AddChosenTimes(1);

            if constexpr (VIRTUAL_LOSS != 0)
            {
                static_assert(VIRTUAL_LOSS > 0);
                edgeAddon->AddCredit(0.0, VIRTUAL_LOSS);
            }
        }

        AddLeadingNodes(node, edgeAddon, nextNode);

        m_path.emplace_back(node, edgeAddon, choice);

        m_currentNode = nextNode;
        m_pendingChoice = -1;
    }

    template <class Dummy = void>
    auto AddLeadingNodes([[maybe_unused]] TreeNode* node,
                         [[maybe_unused]] EdgeAddon* edgeAddon,
                         [[maybe_unused]] TreeNode* childNode)
        -> std::enable_if_t<!RECORD_LEADING_NODES, Dummy>
    {
        return;
    }
    template <class Dummy = void>
    auto AddLeadingNodes(TreeNode* node, EdgeAddon* edgeAddon,
                         TreeNode* childNode)
        -> std::enable_if_t<RECORD_LEADING_NODES, Dummy>
    {
        if (!childNode)
        {
            return;
        }

        childNode->addon.leadingNodes.AddLeadingNodes(node, edgeAddon);

        return;
    }

    std::vector<TraversedNodeInfo> m_path;
    bool m_newNodeCreated;
    TreeNode* m_currentNode;
    int m_pendingChoice;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_TRAVERSED_NODES_INFO_HPP