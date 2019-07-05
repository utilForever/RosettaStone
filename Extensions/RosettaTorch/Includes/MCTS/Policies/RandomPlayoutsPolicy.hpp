// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_RANDOM_PLAYOUTS_POLICY_HPP
#define ROSETTASTONE_TORCH_MCTS_RANDOM_PLAYOUTS_POLICY_HPP

#include <MCTS/Policies/ISimulationPolicy.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaTorch::MCTS
{
class RandomPlayoutsPolicy : public ISimulationPolicy
{
 public:
    bool IsEnableCutoff() override
    {
        return true;
    }

    bool GetCutoffResult([[maybe_unused]] const Board& board,
                         [[maybe_unused]] StateValue& stateValue) override
    {
        return true;
    }

    void StartAction(
        [[maybe_unused]] const Board& board,
        [[maybe_unused]] const ActionValidChecker& checker) override
    {
        // Do nothing
    }

    int GetChoice([[maybe_unused]] const Board& board,
                  [[maybe_unused]] const ActionValidChecker& checker,
                  [[maybe_unused]] ActionType actionType,
                  const std::vector<int>& choices) override
    {
        const size_t count = choices.size();
        const auto randIdx = Random::get<size_t>(0, count - 1);
        const int result = choices[randIdx];

        return result;
    }
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_RANDOM_PLAYOUTS_POLICY_HPP
