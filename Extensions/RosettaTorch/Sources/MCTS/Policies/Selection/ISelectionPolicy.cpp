// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <MCTS/Policies/Selection/ISelectionPolicy.hpp>

namespace RosettaTorch::MCTS
{
ChoiceIterator::ChoiceIterator(ActionChoices& choices,
                             const ChildNodeMap& children)
    : m_choices(choices), m_children(children)
{
    // Do nothing
}

void ChoiceIterator::Begin() const
{
    m_choices.Begin();
}

void ChoiceIterator::StepNext() const
{
    m_choices.StepNext();
}

bool ChoiceIterator::IsEnd() const
{
    return m_choices.IsEnd();
}

void ChoiceIterator::Get(Item& item) const
{
    item.choice = m_choices.Get();
    item.edgeAddon = m_children.Get(item.choice).first;
}
}  // namespace RosettaTorch::MCTS