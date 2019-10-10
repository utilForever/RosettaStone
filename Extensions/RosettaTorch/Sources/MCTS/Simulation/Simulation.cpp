// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <MCTS/Policies/Simulation/HeuristicPlayoutHeuristicEarlyCutoffPolicy.hpp>
#include <MCTS/Policies/Simulation/RandomCutoffPolicy.hpp>
#include <MCTS/Policies/Simulation/RandomPlayoutHeuristicEarlyCutoffPolicy.hpp>
#include <MCTS/Policies/Simulation/RandomPlayoutPolicy.hpp>
#include <MCTS/Simulation/Simulation.hpp>

namespace RosettaTorch::MCTS
{
Simulation::Simulation(const Config& config)
    : m_policy(new HeuristicPlayoutHeuristicEarlyCutoffPolicy(config))
{
    // Do nothing
}

bool Simulation::CutoffCheck(const Board& board, StateValue& stateValue) const
{
    if (m_policy->IsEnableCutoff())
    {
        return m_policy->GetCutoffResult(board, stateValue);
    }

    return false;
}

void Simulation::StartAction(const Board& board,
                             const ActionValidChecker& checker) const
{
    m_policy->StartAction(board, checker);
}

int Simulation::ChooseAction(const Board& board,
                             const ActionValidChecker& checker,
                             ActionType actionType,
                             const ActionChoices& choices) const
{
    const int choiceSize = choices.Size();
    if (choiceSize == 1)
    {
        return 0;
    }

    const int choice = m_policy->GetChoice(board, checker, actionType,
                                           ChoiceGetter(choiceSize));
    return choice;
}
}  // namespace RosettaTorch::MCTS