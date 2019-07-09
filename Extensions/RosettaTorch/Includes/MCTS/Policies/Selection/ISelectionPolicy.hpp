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

#include <Rosetta/Actions/ActionChoices.hpp>
#include <Rosetta/Actions/ActionType.hpp>

namespace RosettaTorch::MCTS
{
//!
//! \brief ChoiceIterator class.
//!
class ChoiceIterator
{
 public:
    struct Item
    {
        int choice;
        const EdgeAddon* edgeAddon;
    };

    ChoiceIterator(ActionChoices& choices, const ChildNodeMap& children)
        : m_choices(choices), m_children(children)
    {
        // Do nothing
    }

    void Begin() const
    {
        m_choices.Begin();
    }

    void StepNext() const
    {
        m_choices.StepNext();
    }

    bool IsEnd() const
    {
        return m_choices.IsEnd();
    }

    void Get(Item& item) const
    {
        item.choice = m_choices.Get();
        assert(item.choice >= 0);
        item.edgeAddon = m_children.Get(item.choice).first;
    }

 private:
    ActionChoices& m_choices;
    const ChildNodeMap& m_children;
};

//!
//! \brief ISelectionPolicy class.
//!
class ISelectionPolicy
{
 public:
    virtual ~ISelectionPolicy() = default;

    virtual int SelectChoice(ActionType actionType,
                             ChoiceIterator choiceIter) = 0;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_ISELECTION_POLICY_HPP