// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_ISIMULATION_POLICY_HPP
#define ROSETTASTONE_TORCH_MCTS_ISIMULATION_POLICY_HPP

#include <MCTS/Types.hpp>

#include <Rosetta/Actions/ActionValidChecker.hpp>
#include <Rosetta/Views/Board.hpp>

namespace RosettaTorch::MCTS
{
//!
//! \brief ISimulationPolicy class.
//!
class ISimulationPolicy
{
 public:
    virtual ~ISimulationPolicy() = default;

    virtual bool IsEnableCutoff() = 0;

    virtual bool GetCutoffResult(const Board& board,
                                 StateValue& stateValue) = 0;

    virtual void StartAction(const Board& board,
                             const ActionValidChecker& checker) = 0;

    virtual int GetChoice(const Board& board, const ActionValidChecker& checker,
                          ActionType actionType,
                          const std::vector<int>& choices) = 0;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_ISIMULATION_POLICY_HPP