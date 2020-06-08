// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_CONSISTENCY_CHECK_ADDON_HPP
#define ROSETTASTONE_TORCH_MCTS_CONSISTENCY_CHECK_ADDON_HPP

#include <MCTS/Selection/BoardNodeMap.hpp>

#include <Rosetta/Common/Enums/ActionEnums.hpp>
#include <Rosetta/Common/SpinLocks.hpp>
#include <Rosetta/PlayMode/Actions/ActionChoices.hpp>

#include <mutex>

namespace RosettaTorch::MCTS
{
//!
//! \brief ConsistencyCheckAddon class.
//!
//! This class is addon class to check consistency of board and action type.
//!
class ConsistencyCheckAddon
{
 public:
    //! Sets spin lock and checks action type.
    //! \param actionType The type of action.
    //! \return The flag indicates action type is consistent.
    bool LockAndCheckActionType(RosettaStone::ActionType actionType) const;

    //! Sets spin lock and checks action type and choices.
    //! \param actionType The type of action.
    //! \param choices The choices of action.
    //! \return The flag indicates action type and choices are consistent.
    bool LockAndCheckActionTypeAndChoices(RosettaStone::ActionType actionType,
                                          const ActionChoices& choices)
    {
        std::lock_guard<RosettaStone::SpinLock> lock(m_mutex);
        return CheckActionTypeAndChoices(actionType, choices);
    }

    //! Sets spin lock and checks board.
    //! \param view The reduced board view.
    //! \return The flag indicates board is consistent.
    bool LockAndCheckBoard(const ReducedBoardView& view);

    //! Returns the type of action.
    //! \return The type of action.
    RosettaStone::ActionType GetActionType() const;

    //! Returns the reduced board view.
    //! \return The reduced board view.
    ReducedBoardView* GetBoard() const;

    //! Checks action type.
    //! \param actionType The type of action.
    //! \return The flag indicates action type is consistent.
    bool CheckActionType(RosettaStone::ActionType actionType) const;

 private:
    //! Checks action type and choices.
    //! \param actionType The type of action.
    //! \param choices The choices of action.
    //! \return The flag indicates action type and choices are consistent.
    bool CheckActionTypeAndChoices(RosettaStone::ActionType actionType,
                                   const ActionChoices& choices)
    {
        if (m_actionType == RosettaStone::ActionType::INVALID)
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

                if (std::is_same_v<Type1, ChooseFromCardIDs>)
                {
                    return true;
                }

                if (std::is_same_v<Type1, ChooseFromNumbers>)
                {
                    return lhs.Size() == rhs.Size();
                }

                if (std::is_same_v<Type1, InvalidChoice>)
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

    //! Checks board.
    //! \param view The reduced board view.
    //! \return The flag indicates board is consistent.
    bool CheckBoard(const ReducedBoardView& view);

    mutable RosettaStone::SpinLock m_mutex{};
    std::unique_ptr<ReducedBoardView> m_boardView;
    RosettaStone::ActionType m_actionType{};
    ActionChoices m_actionChoices;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_CONSISTENCY_CHECK_ADDON_HPP