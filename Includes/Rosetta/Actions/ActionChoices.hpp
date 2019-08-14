// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_ACTION_CHOICES_HPP
#define ROSETTASTONE_ACTION_CHOICES_HPP

#include <Rosetta/Actions/Choices/ChooseFromNumbers.hpp>
#include <Rosetta/Actions/Choices/InvalidChoice.hpp>

#include <cassert>
#include <variant>
#include <vector>

namespace RosettaStone
{
//!
//! \brief ActionChoices class.
//!
//! This class contains several choice methods for the action such as
//! invalid choice, choose from numeric range or a list of card IDs.
//!
class ActionChoices
{
 public:
    class ChooseFromCardIDs
    {
     public:
        explicit ChooseFromCardIDs(const std::vector<size_t>& cardIDs)
            : m_cardIDs(cardIDs)
        {
            // Do nothing
        }

        size_t Get(size_t idx) const
        {
            assert(idx < m_cardIDs.size());
            return m_cardIDs[idx];
        }

        bool IsEmpty() const
        {
            return m_cardIDs.empty();
        }

        size_t Size() const
        {
            return m_cardIDs.size();
        }

        void Begin()
        {
            m_iter = m_cardIDs.begin();
        }

        size_t Get() const
        {
            return *m_iter;
        }

        void StepNext()
        {
            ++m_iter;
        }

        bool IsEnd() const
        {
            return m_iter == m_cardIDs.end();
        }

     private:
        std::vector<size_t> m_cardIDs;
        std::vector<size_t>::const_iterator m_iter;
    };

    ActionChoices() : m_item(InvalidChoice())
    {
        // Do nothing
    }

    explicit ActionChoices(size_t exclusiveMax)
        : m_item(ChooseFromNumbers(exclusiveMax))
    {
        // Do nothing
    }

    explicit ActionChoices(const std::vector<size_t>& cardIDs)
        : m_item(ChooseFromCardIDs(cardIDs))
    {
        // Do nothing
    }

    template <class T>
    bool CheckType() const
    {
        return std::holds_alternative<T>(m_item);
    }

    template <class Comparator>
    bool Compare(const ActionChoices& rhs, Comparator&& comparator) const
    {
        return std::visit(
            [&](auto&& arg1, auto&& arg2) -> bool {
                return comparator(std::forward<decltype(arg1)>(arg1),
                                  std::forward<decltype(arg2)>(arg2));
            },
            m_item, rhs.m_item);
    }

    size_t GetIndex() const
    {
        return m_item.index();
    }

    size_t Get(size_t idx) const
    {
        return std::visit([&](auto&& item) -> int { return item.Get(idx); },
                          m_item);
    }

    bool IsEmpty() const
    {
        return std::visit([&](auto&& item) { return item.IsEmpty(); }, m_item);
    }

    size_t Size() const
    {
        return std::visit([&](auto&& item) { return item.Size(); }, m_item);
    }

    void Begin()
    {
        return std::visit([&](auto&& item) { return item.Begin(); }, m_item);
    }

    size_t Get() const
    {
        return std::visit([&](auto&& item) { return item.Get(); }, m_item);
    }

    void StepNext()
    {
        return std::visit([&](auto&& item) { return item.StepNext(); }, m_item);
    }

    bool IsEnd() const
    {
        return std::visit([&](auto&& item) { return item.IsEnd(); }, m_item);
    }

 private:
    using ItemType =
        std::variant<InvalidChoice, ChooseFromNumbers, ChooseFromCardIDs>;

    ItemType m_item;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ACTION_CHOICES_HPP
