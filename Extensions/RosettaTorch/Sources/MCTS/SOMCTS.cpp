// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <MCTS/Commons/Config.hpp>
#include <MCTS/SOMCTS.hpp>

#include <tuple>

namespace RosettaTorch::MCTS
{
SOMCTS::SOMCTS(TreeNode& tree, Statistics<>& statistics, const Config& config)
    : m_actionParams(*this),
      m_stage(Stage::SELECTION),
      m_selectionStage(tree),
      m_simulationStage(config),
      m_statistics(statistics)
{
    // Do nothing
}

TreeNode* SOMCTS::GetRootNode() const
{
    return m_selectionStage.GetRootNode();
}

void SOMCTS::StartIteration()
{
    m_selectionStage.StartIteration();
    m_stage = Stage::SELECTION;
}

bool SOMCTS::PerformAction(const Board& board, StateValue& stateValue)
{
    std::tuple<PlayState, PlayState> result;

    m_actionParams.Init(board);

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

    auto& [p1Result, p2Result] = result;
    if (p1Result != PlayState::PLAYING && p2Result != PlayState::PLAYING)
    {
        stateValue.SetValue(board.GetViewType(), result);
        return true;
    }

    return false;
}

void SOMCTS::ApplyOthersActions()
{
    if (m_stage == Stage::SIMULATION)
    {
        return;
    }

    m_selectionStage.ApplyOthersActions();
}

void SOMCTS::FinishIteration(const Board& board, StateValue stateValue)
{
    m_selectionStage.FinishIteration(board, stateValue);
}

int SOMCTS::ChooseAction(const Board& board, ActionType actionType,
                         ActionChoices& choices)
{
    if (m_stage == Stage::SELECTION)
    {
        const int choice = m_selectionStage.ChooseAction(actionType, choices);
        return choice;
    }
    else
    {
        const int choice = m_simulationStage.ChooseAction(
            board, m_actionParams.GetChecker(), actionType, choices);
        return choice;
    }
}

SOMCTS::ActionParams::ActionParams(SOMCTS& callback)
    : m_board(nullptr), m_callback(callback)
{
    // Do nothing
}

void SOMCTS::ActionParams::Init(const Board& board)
{
    m_board = &board;
    RosettaStone::ActionParams::Initialize(
        m_board->GetCurPlayerStateRefView().GetActionValidGetter());
}

std::size_t SOMCTS::ActionParams::GetNumber(ActionType actionType,
                                            ActionChoices& choices)
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
}  // namespace RosettaTorch::MCTS