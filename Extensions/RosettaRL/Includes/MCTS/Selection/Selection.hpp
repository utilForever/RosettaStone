// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_SELECTION_HPP
#define ROSETTASTONE_TORCH_MCTS_SELECTION_HPP

#include <MCTS/Commons/Types.hpp>
#include <MCTS/Policies/Selection/ISelectionPolicy.hpp>
#include <MCTS/Selection/TraversedNodesInfo.hpp>
#include <MCTS/Selection/TreeNode.hpp>

#include <Rosetta/Common/Enums/ActionEnums.hpp>
#include <Rosetta/PlayMode/Actions/ActionChoices.hpp>

namespace RosettaTorch::MCTS
{
//!
//! \brief Selection class.
//!
//! This class traverses the nodes, that are already stored in the tree.
//! At each level, the next node is chosen according to the selection policy.
//!
class Selection
{
 public:
    //! Constructs simulation with the specified policy.
    //! \param tree The root node of the tree.
    explicit Selection(TreeNode& tree);

    //! Deleted copy constructor.
    Selection(const Selection&) = delete;

    //! Deleted move constructor.
    Selection(Selection&&) noexcept = delete;

    //! Deleted copy assignment operator.
    Selection& operator=(const Selection&) = delete;

    //! Deleted move assignment operator.
    Selection& operator=(Selection&&) noexcept = delete;

    //! Returns the root node of the tree.
    //! \return The root node of the tree.
    TreeNode* GetRootNode() const;

    //! Starts iteration by initializing variables.
    void StartIteration();

    //! Starts action by checking board and tree node.
    //! \param board The game board.
    void StartAction(const Board& board);

    //! Chooses action according to the policy.
    //! \param actionType The type of action.
    //! \param choices The choices of action.
    //! \return The index of chosen action.
    int ChooseAction(ActionType actionType, ActionChoices& choices);

    // Finishes action by constructing redirect node and checking it has to
    // switch to simulation.
    //! \param board The game board.
    //! \param result The result of the game (player1 and player2).
    bool FinishAction(const Board& board,
                      const std::tuple<PlayState, PlayState>& result);

    //! Applies other actions to the game.
    void ApplyOthersActions();

    //! Finishes iteration to update credit.
    //! \param board The game board.
    //! \param stateValue The value of game state.
    void FinishIteration(const Board& board, StateValue stateValue);

 private:
    TreeNode& m_root;
    bool m_boardChanged = false;
    BoardNodeMap* m_redirectNodeMap = nullptr;
    TraversedNodesInfo m_path;
    ISelectionPolicy* m_policy = nullptr;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_SELECTION_HPP