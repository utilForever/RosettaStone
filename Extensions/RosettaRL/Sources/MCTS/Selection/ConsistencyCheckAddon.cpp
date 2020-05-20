// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <MCTS/Selection/ConsistencyCheckAddon.hpp>

namespace RosettaTorch::MCTS
{
bool ConsistencyCheckAddon::LockAndCheckActionType(
    RosettaStone::ActionType actionType) const
{
    std::lock_guard<RosettaStone::SpinLock> lock(m_mutex);
    return CheckActionType(actionType);
}

bool ConsistencyCheckAddon::LockAndCheckBoard(const ReducedBoardView& view)
{
    std::lock_guard<RosettaStone::SpinLock> lock(m_mutex);
    return CheckBoard(view);
}

RosettaStone::ActionType ConsistencyCheckAddon::GetActionType() const
{
    std::lock_guard<RosettaStone::SpinLock> lock(m_mutex);
    return m_actionType;
}

ReducedBoardView* ConsistencyCheckAddon::GetBoard() const
{
    std::lock_guard<RosettaStone::SpinLock> lock(m_mutex);
    return m_boardView.get();
}

bool ConsistencyCheckAddon::CheckActionType(
    RosettaStone::ActionType actionType) const
{
    if (m_actionType == RosettaStone::ActionType::INVALID)
    {
        return true;
    }

    return m_actionType == actionType;
}

bool ConsistencyCheckAddon::CheckBoard(const ReducedBoardView& view)
{
    if (!m_boardView)
    {
        m_boardView.reset(new ReducedBoardView(view));
        return true;
    }

    return *m_boardView == view;
}
}  // namespace RosettaTorch::MCTS