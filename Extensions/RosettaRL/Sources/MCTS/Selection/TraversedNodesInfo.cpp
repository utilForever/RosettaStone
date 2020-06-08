// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <MCTS/Selection/TraversedNodesInfo.hpp>

#include <tuple>

namespace RosettaTorch::MCTS
{
TraversedNodesInfo::TraversedNodesInfo()
    : m_newNodeCreated(false), m_currentNode(nullptr), m_pendingChoice(-1)
{
    // Do nothing
}

void TraversedNodesInfo::Restart(TreeNode* node)
{
    m_path.clear();
    m_currentNode = node;
    m_newNodeCreated = false;
    m_pendingChoice = -1;
}

TreeNode* TraversedNodesInfo::GetCurrentNode() const
{
    return m_currentNode;
}

void TraversedNodesInfo::MakeChoiceForCurrentNode(int choice)
{
    m_pendingChoice = choice;
}

bool TraversedNodesInfo::HasCurrentNodeMadeChoice() const
{
    return m_pendingChoice >= 0;
}

void TraversedNodesInfo::ConstructNode()
{
    const auto& [newNodeCreated, edgeAddon, node] =
        m_currentNode->children.GetOrCreateNewNode(
            m_pendingChoice, std::make_unique<TreeNode>());

    AddPathNode(m_currentNode, m_pendingChoice, edgeAddon, node);

    if (newNodeCreated)
    {
        m_newNodeCreated = true;
    }
}

void TraversedNodesInfo::ConstructRedirectNode(
    BoardNodeMap* redirectNodeMap, const Board& board,
    std::tuple<RosettaStone::PlayState, RosettaStone::PlayState> result)
{
    const auto& [newNodeCreated, edgeAddon, node] =
        m_currentNode->children.GetOrCreateRedirectNode(m_pendingChoice);

    if (newNodeCreated)
    {
        m_newNodeCreated = true;
    }

    auto& [p1Result, p2Result] = result;
    if (p1Result != RosettaStone::PlayState::PLAYING &&
        p2Result != RosettaStone::PlayState::PLAYING)
    {
        // Don't need to construct a node for leaf nodes.
        // We only need the edge to record win-rate, which is already
        // got before.
        AddPathNode(m_currentNode, m_pendingChoice, edgeAddon, node);
    }
    else
    {
        TreeNode* nextNode =
            redirectNodeMap->GetOrCreateNode(board, &m_newNodeCreated);
        AddPathNode(m_currentNode, m_pendingChoice, edgeAddon, nextNode);
    }
}

void TraversedNodesInfo::JumpToNode(const Board& board)
{
    TreeNode* nextNode =
        m_currentNode->addon.boardNodeMap.GetOrCreateNode(board);
    AddPathNode(m_currentNode, -1, nullptr, nextNode);
}

void TraversedNodesInfo::Update(float credit)
{
    if constexpr (VIRTUAL_LOSS != 0)
    {
        static_assert(VIRTUAL_LOSS > 0);

        for (const auto& path : m_path)
        {
            if (path.edgeAddon)
            {
                path.edgeAddon->AddCredit(1.0, VIRTUAL_LOSS);
            }
        }
    }

    TreeUpdater updater;
    updater.Update(m_path, credit);
}

const std::vector<TraversedNodeInfo>& TraversedNodesInfo::GetPath() const
{
    return m_path;
}

bool TraversedNodesInfo::HasNewNodeCreated() const
{
    return m_newNodeCreated;
}

void TraversedNodesInfo::AddPathNode(TreeNode* node, int choice,
                                     EdgeAddon* edgeAddon, TreeNode* nextNode)
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

template <class Dummy>
auto TraversedNodesInfo::AddLeadingNodes([[maybe_unused]] TreeNode* node,
                                         [[maybe_unused]] EdgeAddon* edgeAddon,
                                         [[maybe_unused]] TreeNode* childNode)
    -> std::enable_if_t<!RECORD_LEADING_NODES, Dummy>
{
    return;
}

template <class Dummy>
auto TraversedNodesInfo::AddLeadingNodes(TreeNode* node, EdgeAddon* edgeAddon,
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
}  // namespace RosettaTorch::MCTS