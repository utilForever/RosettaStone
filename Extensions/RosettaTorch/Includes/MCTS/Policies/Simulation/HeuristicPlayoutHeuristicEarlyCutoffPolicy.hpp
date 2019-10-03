// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_HEURISTIC_PLAYOUT_HEURISTIC_EARLY_CUTOFF_POLICY_HPP
#define ROSETTASTONE_TORCH_MCTS_HEURISTIC_PLAYOUT_HEURISTIC_EARLY_CUTOFF_POLICY_HPP

#include <MCTS/Commons/Config.hpp>
#include <MCTS/Policies/NeuralNetworkStateValue.hpp>
#include <MCTS/Policies/Simulation/ISimulationPolicy.hpp>

namespace RosettaTorch::MCTS
{
//!
//! \brief HeuristicPlayoutHeuristicEarlyCutoffPolicy class.
//!
//! This class is policy class that selects choice based on heuristic with
//! heuristic early cutoff.
//!
class HeuristicPlayoutHeuristicEarlyCutoffPolicy : public ISimulationPolicy
{
 public:
    // Simulation cutoff:
    // For each simulation choice, a small probability is defined so the
    // simulation ends here,
    //    and the game result is defined by a heuristic state-value function.
    // Assume the cutoff probability is p,
    //    The expected number of simulation runs is 1/p.
    //    So, if the expected number of runs is N, the probability p = 1.0 / N
    constexpr static double CUTOFF_EXPECTED_RUNS = 0.5;
    constexpr static double CUTOFF_PROBABILITY = 1.0 / CUTOFF_EXPECTED_RUNS;
    constexpr static bool RANDOMLY_PUT_MINIONS = true;

    //! Constructs heuristic playout heuristic early cutoff policy.
    //! \param config The config for neural network.
    explicit HeuristicPlayoutHeuristicEarlyCutoffPolicy(const Config& config);

    //! Returns the flag indicates whether cutoff is enabled.
    //! \return The flag indicates whether cutoff is enabled.
    bool IsEnableCutoff() override;

    //! Returns the result of game according to cutoff.
    //! \param board The game board.
    //! \param stateValue The value of game state.
    //! \return The result of game according to cutoff.
    bool GetCutoffResult(const Board& board, StateValue& stateValue) override;

    //! Starts action according to the policy.
    //! \param board The game board.
    //! \param checker The action valid checker.
    void StartAction(const Board& board,
                     const ActionValidChecker& checker) override;

    //! Returns the choice according to the policy.
    //! \param board The game board.
    //! \param checker The action valid checker.
    //! \param actionType The type of action.
    //! \param getter The choice getter.
    //! \return The choice according to the policy.
    int GetChoice([[maybe_unused]] const Board& board,
                  const ActionValidChecker& checker,
                  [[maybe_unused]] ActionType actionType,
                  const ChoiceGetter& getter) override;

 private:
    //! Starts new action.
    //! \param board The game board.
    //! \param checker The action valid checker.
    void StartNewAction(const Board& board, const ActionValidChecker& checker);

    //! Processes DFS for best state value.
    //! \param board The game board.
    //! \param checker The action valid checker.
    void DFSBestStateValue(const Board& board,
                           const ActionValidChecker& checker);

    //! Returns the choice for main action.
    //! \param checker The action valid checker.
    //! \param getter The choice getter.
    //! \return The choice for main action.
    int GetChoiceForMainAction(const ActionValidChecker& checker,
                               const ChoiceGetter& getter);

    //! Returns the choice at random.
    //! \param checker The action valid checker.
    //! \param getter The choice getter.
    //! \return The choice at random.
    int GetChoiceRandomly([[maybe_unused]] const ActionValidChecker& checker,
                          const ChoiceGetter& getter);

    NeuralNetworkStateValue m_stateValue;
    std::vector<int> m_decision{};
    std::size_t m_decisionIdx;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_HEURISTIC_PLAYOUT_HEURISTIC_EARLY_CUTOFF_POLICY_HPP
