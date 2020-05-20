// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_RANDOM_POLICY_HPP
#define ROSETTASTONE_TORCH_MCTS_RANDOM_POLICY_HPP

#include <MCTS/Policies/Selection/ISelectionPolicy.hpp>

namespace RosettaTorch::MCTS
{
//!
//! \brief RandomPolicy class.
//!
//! This class is policy class that selects choice at random.
//!
class RandomPolicy : public ISelectionPolicy
{
 public:
    //! Selects choice according to the policy.
    //! \param actionType The type of action.
    //! \param choiceIter An iterator for action choices.
    //! \return The index of choice.
    int SelectChoice([[maybe_unused]] RosettaStone::ActionType actionType,
                     ChoiceIterator choiceIter) override;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_RANDOM_POLICY_HPP
