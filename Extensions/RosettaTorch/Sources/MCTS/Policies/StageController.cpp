// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <MCTS/Policies/StageController.hpp>

namespace RosettaTorch::MCTS
{
bool StageController::SwitchToSimulation(bool newNodeCreated,
                                         std::int64_t lastNodeChosenTimes)
{
    if (newNodeCreated)
    {
        return true;
    }
    if (lastNodeChosenTimes < SWITCH_TO_SIMULATION_UNDER_CHOSEN_TIMES)
    {
        return true;
    }

    return false;
}
}  // namespace RosettaTorch::MCTS