// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_RANDOM_PLAYOUT_POLICY_HPP
#define ROSETTASTONE_TORCH_MCTS_RANDOM_PLAYOUT_POLICY_HPP

#include <MCTS/Commons/Config.hpp>
#include <MCTS/Policies/Simulation/ISimulationPolicy.hpp>

namespace RosettaTorch::MCTS
{
//!
//! \brief RandomPlayoutPolicy class.
//!
//! This class is policy class that selects choice at random.
//!
class RandomPlayoutPolicy : public ISimulationPolicy
{
 public:
    //! Constructs random playout policy.
    //! \param config The config for neural network.
    explicit RandomPlayoutPolicy(const Config& config);

    //! Returns the flag indicates whether cutoff is enabled.
    //! \return The flag indicates whether cutoff is enabled.
    bool IsEnableCutoff() override;

    //! Returns the result of game according to cutoff.
    //! \param board The game board.
    //! \param stateValue The value of game state.
    //! \return The result of game according to cutoff.
    bool GetCutoffResult([[maybe_unused]] const Board& board,
                         [[maybe_unused]] StateValue& stateValue) override;

    //! Starts action according to the policy.
    //! \param board The game board.
    //! \param checker The action valid checker.
    void StartAction(
        [[maybe_unused]] const Board& board,
        [[maybe_unused]] const ActionValidChecker& checker) override;

    //! Returns the choice according to the policy.
    //! \param board The game board.
    //! \param checker The action valid checker.
    //! \param actionType The type of action.
    //! \param getter The choice getter.
    //! \return The choice according to the policy.
    int GetChoice([[maybe_unused]] const Board& board,
                  [[maybe_unused]] const ActionValidChecker& checker,
                  [[maybe_unused]] ActionType actionType,
                  const ChoiceGetter& getter) override;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_RANDOM_PLAYOUT_POLICY_HPP
