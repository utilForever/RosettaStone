// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PRIORITY_QUEUE_HPP
#define ROSETTASTONE_PRIORITY_QUEUE_HPP

#include <algorithm>
#include <map>
#include <ranges>
#include <stdexcept>
#include <utility>

namespace RosettaStone
{
//!
//! \brief PriorityQueue class.
//!
//! This class is a custom priority queue implementation for convenience.
//!
template <typename T>
class PriorityQueue
{
 public:
    PriorityQueue() = default;
    ~PriorityQueue() = default;
    PriorityQueue(const PriorityQueue&) = default;
    PriorityQueue(PriorityQueue&&) noexcept = default;
    PriorityQueue& operator=(const PriorityQueue&) = default;
    PriorityQueue& operator=(PriorityQueue&&) noexcept = default;

    //! Gets the count of the elements.
    //! \return The count of the elements.
    std::size_t GetCount() const
    {
        return m_elements.size();
    }

    //! Inserts element and sorts the underlying container.
    //! \param value The value of the element to push.
    //! \param priority The priority of the element to push.
    void Push(T value, int priority)
    {
        m_elements.emplace(priority, std::move(value));
    }

    //! Removes the top element from the priority queue.
    //! \return The top element that is removed.
    T Pop()
    {
        if (IsEmpty())
        {
            throw std::out_of_range("Cannot pop from an empty priority queue");
        }

        auto node = m_elements.extract(m_elements.begin());
        return std::move(node.mapped());
    }

    //! Checks if the value of the element exists.
    //! \param value The value of the element to check.
    //! \return true if the the value of the element exists, false otherwise.
    bool IsExist(const T& value) const
    {
        return std::ranges::contains(m_elements | std::views::values, value);
    }

    //! Checks if the underlying container has no elements.
    //! \return true if the underlying container is empty, false otherwise.
    bool IsEmpty() const
    {
        return m_elements.empty();
    }

 private:
    std::multimap<int, T> m_elements;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_PRIORITY_QUEUE_HPP
