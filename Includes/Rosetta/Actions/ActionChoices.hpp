// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_ACTION_CHOICES_HPP
#define ROSETTASTONE_ACTION_CHOICES_HPP

#include <cassert>
#include <utility>
#include <variant>
#include <vector>

namespace RosettaStone
{
//!
//! \brief ActionChoices class.
//!
class ActionChoices
{
 public:
    class InvalidChoice
    {
     public:
        int Get([[maybe_unused]] size_t idx) const
        {
            throw std::exception();
        }

        bool IsEmpty() const
        {
            throw std::exception();
        }

        int Size() const
        {
            throw std::exception();
        }

        void Begin()
        {
            throw std::exception();
        }

        int Get() const
        {
            throw std::exception();
        }

        void StepNext()
        {
            throw std::exception();
        }

        bool IsEnd() const
        {
            throw std::exception();
        }
    };

    class ChooseFromZeroToExclusiveMax
    {
     public:
        ChooseFromZeroToExclusiveMax(int exclusiveMax)
            : m_exclusiveMax(exclusiveMax), m_iter(0)
        {
            // Do nothing
        }

        int Get(size_t idx) const
        {
            assert(static_cast<int>(idx) < m_exclusiveMax);
            return static_cast<int>(idx);
        }

        bool IsEmpty() const
        {
            return m_exclusiveMax <= 0;
        }

        int Size() const
        {
            return m_exclusiveMax;
        }

        void Begin()
        {
            m_iter = 0;
        }

        int Get() const
        {
            return m_iter;
        }

        void StepNext()
        {
            ++m_iter;
        }

        bool IsEnd() const
        {
            return m_iter >= m_exclusiveMax;
        }

     private:
        int m_exclusiveMax;
        int m_iter;
    };

    class ChooseFromCardIDs
    {
     public:
        ChooseFromCardIDs(std::vector<int> cardIDs)
            : m_cardIDs(std::move(cardIDs))
        {
            // Do nothing
        }

        int Get(size_t idx) const
        {
            assert(idx < m_cardIDs.size());
            return static_cast<int>(m_cardIDs[idx]);
        }

        bool IsEmpty() const
        {
            return m_cardIDs.empty();
        }

        int Size() const
        {
            return m_cardIDs.size();
        }

        void Begin()
        {
            m_iter = m_cardIDs.begin();
        }

        int Get() const
        {
            return static_cast<int>(*m_iter);
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
        std::vector<int> m_cardIDs;
        std::vector<int>::const_iterator m_iter;
    };

    ActionChoices() : m_item(InvalidChoice())
    {
        // Do nothing
    }

    explicit ActionChoices(const ChooseFromZeroToExclusiveMax& val)
        : m_item(val)
    {
        // Do nothing
    }

    explicit ActionChoices(const ChooseFromCardIDs& val) : m_item(val)
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

    int Get(size_t idx) const
    {
        return std::visit([&](auto&& item) -> int { return item.Get(idx); },
                          m_item);
    }

    bool IsEmpty() const
    {
        return std::visit([&](auto&& item) { return item.IsEmpty(); }, m_item);
    }

    int Size() const
    {
        return std::visit([&](auto&& item) { return item.Size(); }, m_item);
    }

    void Begin()
    {
        return std::visit([&](auto&& item) { return item.Begin(); }, m_item);
    }

    int Get() const
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
    using ItemType = std::variant<InvalidChoice, ChooseFromZeroToExclusiveMax,
                                  ChooseFromCardIDs>;

    ItemType m_item;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ACTION_CHOICES_HPP
