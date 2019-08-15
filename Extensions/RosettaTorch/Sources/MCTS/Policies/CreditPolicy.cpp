// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <MCTS/Policies/CreditPolicy.hpp>

namespace RosettaTorch::MCTS
{
float CreditPolicy::GetCredit(const Board& board, StateValue stateValue)
{
    return stateValue.GetValue(board.GetViewType());
}
}  // namespace RosettaTorch::MCTS