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

#include <vector>

namespace RosettaTorch::MCTS
{
//!
//! \brief TraversedNodesInfo class.
//!
//! This class stores a list of traversed node and contains utility methods such
//! as construction, update and addition path or leading node.
//!
class TraversedNodesInfo
{
 public:
    //! Constructs traversed nodes info.
    TraversedNodesInfo();

    //! Deleted copy constructor.
    TraversedNodesInfo(const TraversedNodesInfo&) = delete;

    //! Deleted move constructor.
    TraversedNodesInfo(TraversedNodesInfo&&) noexcept = delete;

    //! Deleted copy assignment operator.
    TraversedNodesInfo& operator=(const TraversedNodesInfo&) = delete;

    //! Deleted move assignment operator.
    TraversedNodesInfo& operator=(TraversedNodesInfo&&) noexcept = delete;

    //! Resets variables such as paths and current node.
    //! \param node The node to reset current node.
    void Restart(TreeNode* node);

    //! Returns the current node.
    //! \return The current node.
    TreeNode* GetCurrentNode() const;

    //! Sets pending choice to \p choice.
    //! \param choice The choice to set pending choice.
    void MakeChoiceForCurrentNode(int choice);

    //! Returns the current node has pending choice.
    //! \return The flag indicates that the current node has pending choice.
    bool HasCurrentNodeMadeChoice() const;

    //! Constructs new node.
    void ConstructNode();

    //! Constructs redirect node.
    //! \param redirectNodeMap The board node map to get the next node.
    //! \param board The game board.
    //! \param result The result of the game (player1 and player2).
    void ConstructRedirectNode(
        BoardNodeMap* redirectNodeMap, const Board& board,
        std::tuple<RosettaStone::PlayState, RosettaStone::PlayState> result);

    //! Jumps current node to next node.
    //! \param board The game board.
    void JumpToNode(const Board& board);

    //! Updates traversed node to \p credit.
    //! \param credit The value that regarding how long ago they were visited.
    void Update(float credit);

    //! Returns the path of nodes.
    //! \return The path of nodes.
    const std::vector<TraversedNodeInfo>& GetPath() const;

    //! Returns the current node is newly created.
    //! \return The flag indicates that the current node is newly created.
    bool HasNewNodeCreated() const;

 private:
    //! Adds path nodes and sets the current node to next node.
    //! \param node A pointer pointing to parent node.
    //! \param choice The index of the node.
    //! \param edgeAddon The edge addon of the node.
    //! \param childNode A pointer pointing to child node.
    void AddPathNode(TreeNode* node, int choice, EdgeAddon* edgeAddon,
                     TreeNode* nextNode);

    //! Adds leading nodes that connecting parent and child.
    //! \param node A pointer pointing to parent node.
    //! \param edgeAddon The edge addon of the node.
    //! \param childNode A pointer pointing to child node.
    //! \return The flag indicates recording leading nodes.
    template <class Dummy = void>
    auto AddLeadingNodes([[maybe_unused]] TreeNode* node,
                         [[maybe_unused]] EdgeAddon* edgeAddon,
                         [[maybe_unused]] TreeNode* childNode)
        -> std::enable_if_t<!RECORD_LEADING_NODES, Dummy>;

    //! Adds leading nodes that connecting parent and child.
    //! \param node A pointer pointing to parent node.
    //! \param edgeAddon The edge addon of the node.
    //! \param childNode A pointer pointing to child node.
    //! \return The flag indicates recording leading nodes.
    template <class Dummy = void>
    auto AddLeadingNodes(TreeNode* node, EdgeAddon* edgeAddon,
                         TreeNode* childNode)
        -> std::enable_if_t<RECORD_LEADING_NODES, Dummy>;

    std::vector<TraversedNodeInfo> m_path;
    bool m_newNodeCreated;
    TreeNode* m_currentNode;
    int m_pendingChoice;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_TRAVERSED_NODES_INFO_HPP