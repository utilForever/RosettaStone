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

#include <Rosetta/Actions/ActionChoices.hpp>
#include <Rosetta/Actions/ActionParams.hpp>

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
    explicit SOMCTS(TreeNode& tree, Statistics<>& statistics)
        : m_actionParams(*this),
          m_stage(Stage::SELECTION),
          m_selectionStage(tree),
          m_statistics(statistics)
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

    bool PerformAction(const Board& board, StateValue& stateValue)
    {
        PlayState result;

        m_actionParams.Initialize(board);

        if (m_stage == Stage::SIMULATION)
        {
            if (m_simulationStage.CutoffCheck(board, stateValue))
            {
                return true;
            }

            m_simulationStage.StartAction(board, m_actionParams.GetChecker());

            result = board.ApplyAction(m_actionParams);

            constexpr bool isSimulation = true;
            m_statistics.ApplyActionSucceeded(isSimulation);
        }
        else
        {
            m_selectionStage.StartAction(board);

            result = board.ApplyAction(m_actionParams);

            constexpr bool isSimulation = false;
            m_statistics.ApplyActionSucceeded(isSimulation);

            if (m_selectionStage.FinishAction(board, result))
            {
                m_stage = Stage::SIMULATION;
            }
        }

        if (result != PlayState::PLAYING)
        {
            stateValue.SetValue(board.GetViewType(), result);
            return true;
        }

        return false;
    }

    void ApplyOthersActions(const Board& board)
    {
        if (m_stage == Stage::SIMULATION)
        {
            return;
        }

        assert(m_stage == Stage::SELECTION);
        m_selectionStage.ApplyOthersActions(board);
    }

    void FinishIteration(const Board& board, StateValue stateValue)
    {
        m_selectionStage.FinishIteration(board, stateValue);
    }

    int ChooseAction(const Board& board, ActionType actionType,
                     ActionChoices& choices)
    {
        assert(!choices.IsEmpty());

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

            const int choice = m_simulationStage.ChooseAction(
                board, m_actionParams.GetChecker(), actionType, choices);
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

    class ActionParams : public RosettaStone::ActionParams
    {
     public:
        explicit ActionParams(SOMCTS& callback)
            : m_board(nullptr), m_callback(callback)
        {
            // Do nothing
        }

        ActionParams(const ActionParams&) = delete;
        ActionParams& operator=(const ActionParams&) = delete;

        void Initialize(const Board& board)
        {
            m_board = &board;
            RosettaStone::ActionParams::Initialize(
                m_board->GetCurrentPlayerStateRefView().GetActionValidGetter());
        }

        size_t GetNumber(ActionType actionType, ActionChoices& choices) final
        {
            if (actionType != ActionType::MAIN_ACTION)
            {
                if (choices.Size() == 1)
                {
                    return choices.Get(0);
                }
            }

            return m_callback.ChooseAction(*m_board, actionType, choices);
        }

     private:
        const Board* m_board;
        SOMCTS& m_callback;
    };

    ActionParams m_actionParams;
    Stage m_stage;
    Selection m_selectionStage;
    Simulation m_simulationStage;
    Statistics<>& m_statistics;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_SOMCTS_HPP