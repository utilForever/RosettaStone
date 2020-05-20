// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_ISELECTION_POLICY_HPP
#define ROSETTASTONE_TORCH_MCTS_ISELECTION_POLICY_HPP

#include <MCTS/Selection/EdgeAddon.hpp>
#include <MCTS/Selection/TreeNode.hpp>

#include <Rosetta/Common/Enums/ActionEnums.hpp>
#include <Rosetta/PlayMode/Actions/ActionChoices.hpp>

namespace RosettaTorch::MCTS
{
//!
//! \brief ChoiceIterator class.
//!
//! This class is an iterator for action choices.
//!
class ChoiceIterator
{
 public:
    struct Item
    {
        int choice;
        const EdgeAddon* edgeAddon;
    };

    //! Constructs choice iterator with given \p choices and \p children.
    //! \param choices The choices of action.
    //! \param children A container of child nodes.
    ChoiceIterator(ActionChoices& choices, const ChildNodeMap& children);

    //! Performs the same action as std::begin.
    void Begin() const;

    //! Increases iterator to access next item.
    void StepNext() const;

    //! Returns the flag indicates whether the iterator is end.
    //! \return The flag indicates whether the iterator is end.
    bool IsEnd() const;

    //! Gets choice and edge addon to \p item.
    //! \param item The item to get choice and edge addon.
    void Get(Item& item) const;

 private:
    ActionChoices& m_choices;
    const ChildNodeMap& m_children;
};

//!
//! \brief ISelectionPolicy class.
//!
//! This class is policy interface for selection stage.
//!
class ISelectionPolicy
{
 public:
    //! Default virtual destructor.
    virtual ~ISelectionPolicy() = default;

    //! Selects choice according to the policy.
    //! \param actionType The type of action.
    //! \param choiceIter An iterator for action choices.
    //! \return The index of choice.
    virtual int SelectChoice(RosettaStone::ActionType actionType,
                             ChoiceIterator choiceIter) = 0;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_ISELECTION_POLICY_HPP