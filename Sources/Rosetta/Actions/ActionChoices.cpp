// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Rosetta/Actions/ActionChoices.hpp>

namespace RosettaStone
{
ActionChoices::ActionChoices() : m_item(InvalidChoice())
{
    // Do nothing
}

ActionChoices::ActionChoices(size_t max) : m_item(ChooseFromNumbers(max))
{
    // Do nothing
}

ActionChoices::ActionChoices(const std::vector<size_t>& cardIDs)
    : m_item(ChooseFromCardIDs(cardIDs))
{
    // Do nothing
}

template <class T>
bool ActionChoices::CheckType() const
{
    return std::holds_alternative<T>(m_item);
}

template <class Comparator>
bool ActionChoices::Compare(const ActionChoices& rhs,
                            Comparator&& comparator) const
{
    return std::visit(
        [&](auto&& arg1, auto&& arg2) -> bool {
            return comparator(std::forward<decltype(arg1)>(arg1),
                              std::forward<decltype(arg2)>(arg2));
        },
        m_item, rhs.m_item);
}

size_t ActionChoices::GetIndex() const
{
    return m_item.index();
}

size_t ActionChoices::Get(size_t idx) const
{
    return std::visit([&](auto&& item) -> int { return item.Get(idx); },
                      m_item);
}

bool ActionChoices::IsEmpty() const
{
    return std::visit([&](auto&& item) { return item.IsEmpty(); }, m_item);
}

size_t ActionChoices::Size() const
{
    return std::visit([&](auto&& item) { return item.Size(); }, m_item);
}

void ActionChoices::Begin()
{
    return std::visit([&](auto&& item) { return item.Begin(); }, m_item);
}

size_t ActionChoices::Get() const
{
    return std::visit([&](auto&& item) { return item.Get(); }, m_item);
}

void ActionChoices::StepNext()
{
    return std::visit([&](auto&& item) { return item.StepNext(); }, m_item);
}

bool ActionChoices::IsEnd() const
{
    return std::visit([&](auto&& item) { return item.IsEnd(); }, m_item);
}
}  // namespace RosettaStone