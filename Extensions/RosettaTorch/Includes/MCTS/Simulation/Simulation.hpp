// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_SIMULATION_HPP
#define ROSETTASTONE_TORCH_MCTS_SIMULATION_HPP

#include <MCTS/Policies/Simulation/ISimulationPolicy.hpp>
#include <MCTS/Policies/Simulation/RandomCutoffPolicy.hpp>
#include <MCTS/Policies/Simulation/RandomPlayoutsPolicy.hpp>

#include <Rosetta/Actions/ActionValidChecker.hpp>

namespace RosettaTorch::MCTS
{
//!
//! \brief Simulation class.
//!
class Simulation
{
 public:
    Simulation() : m_policy(new RandomPlayoutsPolicy())
    {
        // Do nothing
    }

    Simulation(const Simulation&) = delete;
    Simulation& operator=(const Simulation&) noexcept = delete;

    Simulation(Simulation&&) = delete;
    Simulation& operator=(Simulation&&) noexcept = delete;

    bool CutoffCheck(const Board& board, StateValue& stateValue) const
    {
        if (m_policy->IsEnableCutoff())
        {
            return m_policy->GetCutoffResult(board, stateValue) !=
                   PlayState::PLAYING;
        }

        return false;
    }

    void StartAction(const Board& board,
                     const ActionValidChecker& checker) const
    {
        m_policy->StartAction(board, checker);
    }

    int ChooseAction(const Board& board, const ActionValidChecker& checker,
                     ActionType actionType, const ActionChoices& choices) const
    {
        assert(!choices.IsEmpty());

        const int choiceSize = choices.Size();
        if (choiceSize == 1)
        {
            return 0;
        }

        const int choice = m_policy->GetChoice(board, checker, actionType,
                                               ChoiceGetter(choiceSize));
        // Always return a valid choice
        assert(choice >= 0);

        return choice;
    }

 private:
    ISimulationPolicy* m_policy = nullptr;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_SIMULATION_HPP