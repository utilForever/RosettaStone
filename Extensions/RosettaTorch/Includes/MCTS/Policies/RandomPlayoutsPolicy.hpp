// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_RANDOM_PLAYOUTS_POLICY_HPP
#define ROSETTASTONE_TORCH_MCTS_RANDOM_PLAYOUTS_POLICY_HPP

#include <MCTS/Policies/ISimulationPolicy.hpp>

namespace RosettaTorch::MCTS
{
class RandomPlayoutsPolicy : public ISimulationPolicy
{
 public:
    bool IsEnableCutoff() override
    {
        return true;
    }

    bool GetCutoffResult(const RosettaStone::Game& game,
                         StateValue& stateValue) override
    {
        return true;
    }

    void StartAction(const RosettaStone::Game& game) override
    {
    }

    int GetChoice(const RosettaStone::Game& game,
                  RosettaStone::ActionType actionType,
                  const std::vector<int>& choices) override
    {
        return 0;
    }
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_RANDOM_PLAYOUTS_POLICY_HPP
