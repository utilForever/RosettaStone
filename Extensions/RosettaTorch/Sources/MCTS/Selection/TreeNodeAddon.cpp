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

bool ConsistencyCheckAddons::SetAndCheck(ActionType actionType,
                                         const ActionChoices& choices)
{
    std::lock_guard<SpinLock> lock(m_mutex);
    return LockedCheckActionTypeAndChoices(actionType, choices);
}

bool ConsistencyCheckAddons::SetAndCheckBoard(const ReducedBoardView& view)
{
    std::lock_guard<SpinLock> lock(m_mutex);
    return LockedSetAndCheckBoard(view);
}

bool ConsistencyCheckAddons::CheckBoard(const ReducedBoardView& view) const
{
    std::lock_guard<SpinLock> lock(m_mutex);

    if (!m_boardView)
    {
        return true;
    }

    return *m_boardView == view;
}

bool ConsistencyCheckAddons::CheckActionType(ActionType actionType) const
{
    std::lock_guard<SpinLock> lock(m_mutex);
    return LockedCheckActionType(actionType);
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

bool ConsistencyCheckAddons::LockedSetAndCheckBoard(
    const ReducedBoardView& view)
{
    if (!m_boardView)
    {
        m_boardView.reset(new ReducedBoardView(view));
        return true;
    }

    return *m_boardView == view;
}

bool ConsistencyCheckAddons::LockedCheckActionType(ActionType actionType) const
{
    if (m_actionType == ActionType::INVALID)
    {
        return true;
    }

    return m_actionType == actionType;
}

bool ConsistencyCheckAddons::LockedCheckActionTypeAndChoices(
    ActionType actionType, const ActionChoices& choices)
{
    if (m_actionType == ActionType::INVALID)
    {
        m_actionType = actionType;
        m_actionChoices = choices;

        return true;
    }

    if (m_actionType != actionType)
    {
        return false;
    }

    if (m_actionChoices.GetIndex() != choices.GetIndex())
    {
        return false;
    }

    if (!m_actionChoices.Compare(choices, [](auto&& lhs, auto&& rhs) {
            using Type1 = std::decay_t<decltype(lhs)>;
            using Type2 = std::decay_t<decltype(rhs)>;

            if (!std::is_same_v<Type1, Type2>)
            {
                return false;
            }

            if (std::is_same_v<Type1, ActionChoices::ChooseFromCardIDs>)
            {
                return true;
            }

            //if (std::is_same_v<Type1,
            //                   ActionChoices::ChooseFromZeroToExclusiveMax>)
            //{
            //    return lhs.Size() == rhs.Size();
            //}

            if (std::is_same_v<Type1, ActionChoices::InvalidChoice>)
            {
                return false;
            }

            return false;
        }))
    {
        return false;
    }

    return true;
}
}  // namespace RosettaTorch::MCTS