// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_SOMCTS_HPP
#define ROSETTASTONE_TORCH_SOMCTS_HPP

#include <MCTS/Selection/Selection.hpp>
#include <MCTS/Selection/TreeNode.hpp>
#include <MCTS/Simulation/Simulation.hpp>

namespace RosettaTorch::MCTS
{
//!
//! \brief SOMCTS class.
//!
//! This class is single observer MCTS.
//!
class SOMCTS
{
 public:
    explicit SOMCTS(TreeNode& tree)
        : m_stage(Stage::SELECTION), m_selectionStage(tree)
    {
        // Do nothing
    }

    SOMCTS(const SOMCTS&) = delete;
    SOMCTS& operator=(const SOMCTS&) = delete;

    auto GetRootNode() const
    {
        return m_selectionStage.GetRootNode();
    }

    void StartIteration()
    {
        m_selectionStage.StartIteration();
        m_stage = Stage::SELECTION;
    }

    void StartActions()
    {
        // Do nothing
    }

    bool PerformAction(const RosettaStone::Game& game, StateValue& stateValue)
    {
        PlayState result{};

        if (m_stage == Stage::SIMULATION)
        {
            if (m_simulationStage.CutoffCheck(game, stateValue))
            {
                return true;
            }

            m_simulationStage.StartAction(game);
        }
        else
        {
            assert(m_stage == Stage::SELECTION);

            m_selectionStage.StartAction(game);

            if (m_selectionStage.FinishAction(game, result))
            {
                m_stage = Stage::SIMULATION;
            }
        }

        if (result != PlayState::PLAYING)
        {
            stateValue.SetValue(result);
            return true;
        }

        return false;
    }

    void ApplyOthersActions(const RosettaStone::Game& game)
    {
        if (m_stage == Stage::SIMULATION)
        {
            return;
        }

        assert(m_stage == Stage::SELECTION);
        m_selectionStage.ApplyOthersActions(game);
    }

    void FinishIteration(const RosettaStone::Game& game, StateValue stateValue)
    {
        m_selectionStage.FinishIteration(game, stateValue);
    }

    int ChooseAction(const RosettaStone::Game& game,
                     RosettaStone::ActionType actionType,
                     std::vector<int>& choices)
    {
        assert(!choices.empty());

        if (m_stage == Stage::SELECTION)
        {
            const int choice =
                m_selectionStage.ChooseAction(actionType, choices);
            assert(choice >= 0);
            return choice;
        }
        else
        {
            assert(m_stage == Stage::SIMULATION);

            const int choice =
                m_simulationStage.ChooseAction(game, actionType, choices);
            assert(choice >= 0);
            return choice;
        }
    }

 private:
    enum class Stage
    {
        SELECTION,
        SIMULATION
    };

    Stage m_stage;
    Selection m_selectionStage;
    Simulation m_simulationStage{};
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_SOMCTS_HPP