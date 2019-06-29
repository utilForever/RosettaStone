// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_SIMULATION_HPP
#define ROSETTASTONE_TORCH_MCTS_SIMULATION_HPP

#include <MCTS/Policies/RandomPlayoutsPolicy.hpp>

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

    bool CutoffCheck(const Game& game, StateValue& stateValue) const
    {
        if (m_policy->IsEnableCutoff())
        {
            return m_policy->GetCutoffResult(game, stateValue);
        }

        return false;
    }

    void StartAction(const Game& game) const
    {
        m_policy->StartAction(game);
    }

    int ChooseAction(const Game& game, ActionType actionType,
                     const std::vector<int>& choices) const
    {
        assert(!choices.empty());

        if (choices.size() == 1)
        {
            return 0;
        }

        const int choice = m_policy->GetChoice(game, actionType, choices);
        // Always return a valid choice
        assert(choice >= 0);

        return choice;
    }

 private:
    ISimulationPolicy* m_policy = nullptr;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_SIMULATION_HPP