// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Rosetta/PlayMode/Actions/ActionChoices.hpp>

namespace RosettaStone::PlayMode
{
ActionChoices::ActionChoices() : m_item(InvalidChoice())
{
    // Do nothing
}

ActionChoices::ActionChoices(std::size_t max) : m_item(ChooseFromNumbers(max))
{
    // Do nothing
}

ActionChoices::ActionChoices(const std::vector<std::size_t>& cardIDs)
    : m_item(ChooseFromCardIDs(cardIDs))
{
    // Do nothing
}

std::size_t ActionChoices::GetIndex() const
{
    return m_item.index();
}

std::size_t ActionChoices::Get(std::size_t idx) const
{
    return std::visit([&](auto&& item) -> int { return item.Get(idx); },
                      m_item);
}

bool ActionChoices::IsEmpty() const
{
    return std::visit([&](auto&& item) { return item.IsEmpty(); }, m_item);
}

std::size_t ActionChoices::Size() const
{
    return std::visit([&](auto&& item) { return item.Size(); }, m_item);
}

void ActionChoices::Begin()
{
    return std::visit([&](auto&& item) { return item.Begin(); }, m_item);
}

std::size_t ActionChoices::Get() const
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
}  // namespace RosettaStone::PlayMode