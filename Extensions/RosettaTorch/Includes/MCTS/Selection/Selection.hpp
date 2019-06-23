// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_SELECTION_HPP
#define ROSETTASTONE_TORCH_MCTS_SELECTION_HPP

#include "../Configs.hpp"
#include "../Types.hpp"
#include "TraversedNodesInfo.hpp"
#include "TreeNode.hpp"

#include <random>

namespace RosettaTorch::MCTS
{
//!
//! \brief Selection class.
//!
class Selection
{
 public:
    Selection(TreeNode& tree, std::mt19937& rand)
        : m_root(tree),
          m_boardChanged(false),
          m_redirectNodeMap(nullptr),
          m_random(rand)
    {
        // Do nothing
    }

    Selection(Selection const&) = delete;
    Selection& operator=(Selection const&) = delete;

    auto GetRootNode() const
    {
        return &m_root;
    }

    void StartIteration()
    {
        m_path.Restart(&m_root);
        m_boardChanged = false;
        m_redirectNodeMap = nullptr;
    }

    void StartAction(const RosettaStone::Game& game)
    {
        if (m_boardChanged)
        {
            m_path.JumpToNode(game);
            m_boardChanged = false;
        }

        auto currentNode = m_path.GetCurrentNode();
        assert(currentNode);

        if (m_redirectNodeMap == nullptr)
        {
            m_redirectNodeMap = &currentNode->addon.boardNodeMap;
            assert(m_redirectNodeMap);
        }
    }

    int ChooseAction(engine::ActionType actionType,
                     engine::ActionChoices& choices)
    {
        assert(!choices.Empty());

        if (actionType.IsChosenRandomly())
        {
            assert(choices.CheckType<
                   engine::ActionChoices::ChooseFromZeroToExclusiveMax>());
            return m_random.GetRandom(choices.Size());
        }

        assert(actionType.IsChosenManually());
        if (m_path.HasCurrentNodeMadeChoice())
        {
            m_path.ConstructNode();
            assert(!m_path.HasCurrentNodeMadeChoice());
        }

        TreeNode* currentNode = m_path.GetCurrentNode();
        int nextChoice = m_policy.SelectChoice(
            actionType, ChoiceIterator(choices, currentNode->children));

        assert(nextChoice >= 0);  // should report a valid action
        m_path.MakeChoiceForCurrentNode(nextChoice);

        return nextChoice;
    }

    bool FinishAction(const RosettaStone::Game& game,
                      RosettaStone::PlayState result)
    {
        assert(m_path.HasCurrentNodeMadeChoice());

        // We tackle the randomness by using a board node map.
        // This flatten tree structure, and effectively forgot the history
        // (Note that history here referring to the parent nodes of this node)
        assert(m_redirectNodeMap);
        m_path.ConstructRedirectNode(m_redirectNodeMap, game, result);

        bool switchToSimulation = false;
        if (result == PlayState::PLAYING)
        {
            switchToSimulation = Configs::StageController::SwitchToSimulation(
                m_path.HasNewNodeCreated(),
                m_path.GetPath().back().edgeAddon->GetChosenTimes());
        }

        return switchToSimulation;
    }

    void ApplyOthersActions([[maybe_unused]] const RosettaStone::Game& game)
    {
        m_boardChanged = true;

        // Preserve the history when any other player performed their actions
        // So we need another redirect node
        m_redirectNodeMap = nullptr;
    }

    void FinishIteration(const RosettaStone::Game& game, StateValue stateValue)
    {
        const float credit = Configs::CreditPolicy::GetCredit(game, stateValue);
        m_path.Update(credit);
    }

 private:
    TreeNode& m_root;
    bool m_boardChanged;
    BoardNodeMap* m_redirectNodeMap;
    TraversedNodesInfo m_path;
    Configs::SelectionPhaseRandomActionPolicy m_random;
    Configs::SelectionPhaseSelectActionPolicy m_policy;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_SELECTION_HPP