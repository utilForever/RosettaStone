// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_SIMULATION_HPP
#define ROSETTASTONE_TORCH_MCTS_SIMULATION_HPP

#include <MCTS/Commons/Config.hpp>
#include <MCTS/Policies/Simulation/ISimulationPolicy.hpp>

#include <Rosetta/Actions/ActionChoices.hpp>
#include <Rosetta/Actions/ActionValidChecker.hpp>

namespace RosettaTorch::MCTS
{
//!
//! \brief Simulation class.
//!
//! This class starts from the last visited state in the tree, play (simulate)
//! the game till the end. No nodes are added to the tree in this phase. Actions
//! for each player are chosen randomly, however, there are extensions of the
//! MCTS algorithm that introduce heuristics in the simulation. This phase is
//! also called "Monte-Carlo phase".
//!
class Simulation
{
 public:
    //! Constructs simulation with the specified policy.
    //! \param config The config for neural network.
    explicit Simulation(const Config& config);

    //! Deleted copy constructor.
    Simulation(const Simulation&) = delete;

    //! Deleted move constructor.
    Simulation(Simulation&&) noexcept = delete;

    //! Deleted copy assignment operator.
    Simulation& operator=(const Simulation&) = delete;

    //! Deleted move assignment operator.
    Simulation& operator=(Simulation&&) noexcept = delete;

    //! Checks cutoff according to the policy.
    //! \param board The game board.
    //! \param stateValue The value of game state.
    //! \return The flag to indicate that it is cutoff.
    bool CutoffCheck(const Board& board, StateValue& stateValue) const;

    //! Starts action according to the policy.
    //! \param board The game board.
    //! \param checker The action valid checker.
    void StartAction(const Board& board,
                     const ActionValidChecker& checker) const;

    //! Chooses action according to the policy.
    //! \param board The game board.
    //! \param checker The action valid checker.
    //! \param actionType The type of action.
    //! \param choices The choices of action.
    //! \return The index of chosen action.
    int ChooseAction(const Board& board, const ActionValidChecker& checker,
                     ActionType actionType, const ActionChoices& choices) const;

 private:
    ISimulationPolicy* m_policy = nullptr;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_SIMULATION_HPP