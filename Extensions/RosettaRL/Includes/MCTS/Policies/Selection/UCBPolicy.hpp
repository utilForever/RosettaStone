// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_UCB_POLICY_HPP
#define ROSETTASTONE_TORCH_MCTS_UCB_POLICY_HPP

#include <MCTS/Policies/Selection/ISelectionPolicy.hpp>

#include <Rosetta/Common/Enums/ActionEnums.hpp>

namespace RosettaTorch::MCTS
{
//!
//! \brief UCBPolicy class.
//!
//! This class is policy class that selects choice using UCB(Upper Confidence
//! Bound) algorithm. The Upper Confidence Bound algorithm the kind of algorithm
//! that helps us to perform exploitation and exploration together.
//! http://www.aionlinecourse.com/tutorial/machine-learning/upper-confidence-bound-%28ucb%29
//!
class UCBPolicy : public ISelectionPolicy
{
 public:
    //! The value of exploration weight.
    constexpr static double EXPLORE_WEIGHT = 0.2;

    //! Selects choice according to the policy.
    //! \param actionType The type of action.
    //! \param choiceIter An iterator for action choices.
    //! \return The index of choice.
    int SelectChoice(RosettaStone::ActionType actionType,
                     ChoiceIterator choiceIter) override;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_UCB_POLICY_HPP
