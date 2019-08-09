// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_CREDIT_POLICY_HPP
#define ROSETTASTONE_TORCH_MCTS_CREDIT_POLICY_HPP

#include <MCTS/Commons/Types.hpp>

#include <Rosetta/Views/Board.hpp>

namespace RosettaTorch::MCTS
{
//!
//! \brief CreditPolicy class.
//!
//! This class is policy interface for getting credit value.
//!
class CreditPolicy
{
 public:
    //! Return the credit value to update the tree nodes.
    //! If the first player has 100% to win, the credit should be 1.0.
    //! If the first player has 100% to loss, the credit should be -1.0.
    //! If the first player has 50% to win, the credit should be 0.0.
    //! \return The credit value in range [-1.0, 1.0].
    static float GetCredit(const Board& board, StateValue stateValue);
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_CREDIT_POLICY_HPP