// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <MCTS/Policies/CreditPolicy.hpp>
#include <MCTS/Policies/Selection/RandomPolicy.hpp>
#include <MCTS/Policies/Selection/UCBPolicy.hpp>
#include <MCTS/Policies/StageController.hpp>
#include <MCTS/Selection/Selection.hpp>

#include <tuple>

namespace RosettaTorch::MCTS
{
Selection::Selection(TreeNode& tree) : m_root(tree), m_policy(new UCBPolicy())
{
    // Do nothing
}

TreeNode* Selection::GetRootNode() const
{
    return &m_root;
}

void Selection::StartIteration()
{
    m_path.Restart(&m_root);
    m_boardChanged = false;
    m_redirectNodeMap = nullptr;
}

void Selection::StartAction(const Board& board)
{
    if (m_boardChanged)
    {
        m_path.JumpToNode(board);
        m_boardChanged = false;
    }

    auto currentNode = m_path.GetCurrentNode();

    if (m_redirectNodeMap == nullptr)
    {
        m_redirectNodeMap = &currentNode->addon.boardNodeMap;
    }
}

int Selection::ChooseAction(ActionType actionType, ActionChoices& choices)
{
    if (m_path.HasCurrentNodeMadeChoice())
    {
        m_path.ConstructNode();
    }

    TreeNode* currentNode = m_path.GetCurrentNode();
    const int nextChoice = m_policy->SelectChoice(
        actionType, ChoiceIterator(choices, currentNode->children));

    // Should report a valid action
    m_path.MakeChoiceForCurrentNode(nextChoice);

    return nextChoice;
}

bool Selection::FinishAction(const Board& board,
                             const std::tuple<PlayState, PlayState>& result)
{
    // We tackle the randomness by using a board node map.
    // This flatten tree structure, and effectively forgot the history
    // (Note that history here referring to the parent nodes of this node)
    m_path.ConstructRedirectNode(m_redirectNodeMap, board, result);

    auto& [p1Result, p2Result] = result;
    bool switchToSimulation = false;

    if (p1Result == PlayState::PLAYING && p2Result == PlayState::PLAYING)
    {
        switchToSimulation = StageController::SwitchToSimulation(
            m_path.HasNewNodeCreated(),
            m_path.GetPath().back().edgeAddon->GetChosenTimes());
    }

    return switchToSimulation;
}

void Selection::ApplyOthersActions()
{
    m_boardChanged = true;

    // Preserve the history when any other player performed their actions
    // So we need another redirect node
    m_redirectNodeMap = nullptr;
}

void Selection::FinishIteration(const Board& board, StateValue stateValue)
{
    const float credit = CreditPolicy::GetCredit(board, stateValue);
    m_path.Update(credit);
}
}  // namespace RosettaTorch::MCTS