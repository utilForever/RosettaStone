// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <MCTS/Selection/TreeNodeAddon.hpp>

namespace RosettaTorch::MCTS
{
bool LeadingNodesItem::operator==(const LeadingNodesItem& rhs) const
{
    if (node != rhs.node)
    {
        return false;
    }
    if (edgeAddon != rhs.edgeAddon)
    {
        return false;
    }

    return true;
}

bool LeadingNodesItem::operator!=(const LeadingNodesItem& rhs) const
{
    return !(*this == rhs);
}

bool ConsistencyCheckAddons::LockAndCheckActionType(ActionType actionType) const
{
    std::lock_guard<SpinLock> lock(m_mutex);
    return CheckActionType(actionType);
}

bool ConsistencyCheckAddons::LockAndCheckBoard(const ReducedBoardView& view)
{
    std::lock_guard<SpinLock> lock(m_mutex);
    return CheckBoard(view);
}

ActionType ConsistencyCheckAddons::GetActionType() const
{
    std::lock_guard<SpinLock> lock(m_mutex);
    return m_actionType;
}

ReducedBoardView* ConsistencyCheckAddons::GetBoard() const
{
    std::lock_guard<SpinLock> lock(m_mutex);
    return m_boardView.get();
}

bool ConsistencyCheckAddons::CheckActionType(ActionType actionType) const
{
    if (m_actionType == ActionType::INVALID)
    {
        return true;
    }

    return m_actionType == actionType;
}

bool ConsistencyCheckAddons::CheckBoard(const ReducedBoardView& view)
{
    if (!m_boardView)
    {
        m_boardView.reset(new ReducedBoardView(view));
        return true;
    }

    return *m_boardView == view;
}
}  // namespace RosettaTorch::MCTS