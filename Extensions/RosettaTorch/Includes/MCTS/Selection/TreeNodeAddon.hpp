// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_TREE_NODE_ADDON_HPP
#define ROSETTASTONE_TORCH_MCTS_TREE_NODE_ADDON_HPP

#include <MCTS/Commons/Constants.hpp>
#include <MCTS/Selection/BoardNodeMap.hpp>
#include <MCTS/Selection/EdgeAddon.hpp>

#include <Rosetta/Commons/SpinLocks.hpp>
#include <Rosetta/Commons/Utils.hpp>

#include <mutex>

namespace RosettaTorch::MCTS
{
//!
//! \brief LeadingNodesItem struct.
//!
//! This struct contains tree node and edge addon.
//!
struct LeadingNodesItem
{
    //! Operator overloading: operator==.
    bool operator==(const LeadingNodesItem& rhs) const;

    //! Operator overloading: operator!=.
    bool operator!=(const LeadingNodesItem& rhs) const;

    TreeNode* node;
    EdgeAddon* edgeAddon;
};
}  // namespace RosettaTorch::MCTS

namespace std
{
//! \brief Template specialization of std::hash for LeadingNodesItem.
template <>
struct hash<RosettaTorch::MCTS::LeadingNodesItem>
{
    std::size_t operator()(
        const RosettaTorch::MCTS::LeadingNodesItem& rhs) const noexcept
    {
        std::size_t result =
            std::hash<RosettaTorch::MCTS::TreeNode*>()(rhs.node);
        CombineHash(result, rhs.edgeAddon);

        return result;
    }
};
}  // namespace std

namespace RosettaTorch::MCTS
{
//!
//! \brief ConsistencyCheckAddons class.
//!
//! This class is addon class to check consistency of board and action type.
//!
class ConsistencyCheckAddons
{
 public:
    //! Sets spin lock and checks action type.
    //! \param actionType The type of action.
    //! \return The flag indicates action type is consistent.
    bool LockAndCheckActionType(ActionType actionType) const;

    //! Sets spin lock and checks action type and choices.
    //! \param actionType The type of action.
    //! \param choices The choices of action.
    //! \return The flag indicates action type and choices are consistent.
    bool LockAndCheckActionTypeAndChoices(ActionType actionType,
                                          const ActionChoices& choices)
    {
        std::lock_guard<SpinLock> lock(m_mutex);
        return CheckActionTypeAndChoices(actionType, choices);
    }

    //! Sets spin lock and checks board.
    //! \param view The reduced board view.
    //! \return The flag indicates board is consistent.
    bool LockAndCheckBoard(const ReducedBoardView& view);

    //! Returns the type of action.
    //! \return The type of action.
    ActionType GetActionType() const;

    //! Returns the reduced board view.
    //! \return The reduced board view.
    ReducedBoardView* GetBoard() const;

 private:
    //! Checks action type.
    //! \param actionType The type of action.
    //! \return The flag indicates action type is consistent.
    bool CheckActionType(ActionType actionType) const;

    //! Checks action type and choices.
    //! \param actionType The type of action.
    //! \param choices The choices of action.
    //! \return The flag indicates action type and choices are consistent.
    bool CheckActionTypeAndChoices(ActionType actionType,
                                   const ActionChoices& choices)
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

                if (std::is_same_v<Type1,
                                   ActionChoices::ChooseFromZeroToExclusiveMax>)
                {
                    return lhs.Size() == rhs.Size();
                }

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

    //! Checks board.
    //! \param view The reduced board view.
    //! \return The flag indicates board is consistent.
    bool CheckBoard(const ReducedBoardView& view);

    mutable SpinLock m_mutex{};
    std::unique_ptr<ReducedBoardView> m_boardView;
    ActionType m_actionType{};
    ActionChoices m_actionChoices;
};

//!
//! \brief LeadingNodes class.
//!
class LeadingNodes
{
 public:
    void AddLeadingNodes(TreeNode* node, EdgeAddon* edgeAddon)
    {
        std::lock_guard<SharedSpinLock> lock(m_mutex);
        for (const auto& item : m_items)
        {
            if (item.node == node && item.edgeAddon == edgeAddon)
            {
                return;
            }
        }

        m_items.push_back(LeadingNodesItem{ node, edgeAddon });
    }

    template <class Functor>
    void ForEachLeadingNode(Functor&& op)
    {
        std::shared_lock<SharedSpinLock> lock(m_mutex);
        for (const auto& item : m_items)
        {
            if (!op(item.node, item.edgeAddon))
            {
                break;
            }
        }
    }

 private:
    mutable SharedSpinLock m_mutex;
    std::vector<LeadingNodesItem> m_items;
};

//!
//! \brief TreeNodeAddon struct.
//!
struct TreeNodeAddon
{
    struct Dummy
    {
        // Do nothing
    };

    ConsistencyCheckAddons consistencyChecker;
    BoardNodeMap boardNodeMap;
    std::conditional_t<RECORD_LEADING_NODES, LeadingNodes, Dummy> leadingNodes;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_TREE_NODE_ADDON_HPP