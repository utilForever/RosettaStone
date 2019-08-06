// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_TREE_NODE_ADDON_HPP
#define ROSETTASTONE_TORCH_MCTS_TREE_NODE_ADDON_HPP

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
    bool operator==(const LeadingNodesItem& v) const;

    //! Operator overloading: operator!=.
    bool operator!=(const LeadingNodesItem& v) const;

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
class ConsistencyCheckAddons
{
 public:
    bool SetAndCheck(ActionType actionType, ActionChoices const& choices)
    {
        std::lock_guard<SpinLock> lock(m_mutex);

        assert(actionType != ActionType::INVALID);

        return CheckActionTypeAndChoices(actionType, choices);
    }

    bool SetAndCheckBoard(ReducedBoardView const& newView)
    {
        std::lock_guard<SpinLock> lock(m_mutex);
        return LockedSetAndCheckBoard(newView);
    }

    bool CheckBoard(ReducedBoardView const& newView) const
    {
        std::lock_guard<SpinLock> lock(m_mutex);

        if (!m_boardView)
        {
            return true;
        }

        return *m_boardView == newView;
    }

    bool CheckActionType(ActionType actionType) const
    {
        std::lock_guard<SpinLock> lock(m_mutex);
        return LockedCheckActionType(actionType);
    }

    auto GetActionType() const
    {
        std::lock_guard<SpinLock> lock(m_mutex);
        return m_actionType;
    }

    auto GetBoard() const
    {
        std::lock_guard<SpinLock> lock(m_mutex);
        return m_boardView.get();
    }

 private:
    bool LockedSetAndCheckBoard(ReducedBoardView const& newView)
    {
        if (!m_boardView)
        {
            m_boardView.reset(new ReducedBoardView(newView));
            return true;
        }

        return *m_boardView == newView;
    }

    bool LockedCheckActionType(ActionType action_type) const
    {
        if (m_actionType == ActionType::INVALID)
            return true;
        return m_actionType == action_type;
    }

    bool CheckActionTypeAndChoices(ActionType actionType,
                                   ActionChoices const& choices)
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
        assert(node);

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