// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_ALPHA_ZERO_CIRCULAR_ARRAY_HPP
#define ROSETTASTONE_TORCH_ALPHA_ZERO_CIRCULAR_ARRAY_HPP

#include <atomic>
#include <cassert>
#include <vector>

namespace RosettaTorch::AlphaZero
{
//!
//! \brief CircularArray class.
//!
//! This class is a lockless circular array.
//! Note it is thread-safe with two restrictions:
//! 1. Capacity must be a power of 2, since we use lower bits to be the index.
//! 2. Item type T is exposed as it is. It should be thread-safe.
//!
template <typename T>
class CircularArray
{
 public:
    //! Initializes the circular array.
    //! \param _capacity The capacity of the circular array.
    void Initialize(std::size_t _capacity)
    {
        // Make sure index type is large enough
        assert(8 * sizeof(m_head) > _capacity);

        std::size_t capacity = static_cast<std::size_t>(1) << _capacity;
        m_indexMask = capacity - 1;
        m_head = 0;
        m_items.resize(capacity);
    }

    //! Gets the capacity of the circular array.
    //! \return The capacity of the circular array.
    std::size_t Capacity() const
    {
        return m_items.size();
    }

    //! Allocates the next item. It is thread-safe if
    //! the number of concurrent callers less than array size.
    //! \return The next item that is allocated.
    T& AllocateNext()
    {
        const std::size_t idx = m_head.fetch_add(1);
        T& ret = m_items[Index(idx)];
        return ret;
    }

    //! Gets the item at \p idx.
    //! \param idx The index of the circular array.
    //! \return The item at \p idx.
    const T& Get(std::size_t idx) const
    {
        idx += m_head.load();
        return m_items[Index(idx)];
    }

    //! Gets the random item at \p idx.
    //! Don't need to fetch head index, since we're fetching a random item.
    //! \param idx The index of the circular array.
    //! \return The random item at \p idx.
    const T& GetRandom(std::size_t idx) const
    {
        return m_items[Index(idx)];
    }

 private:
    //! Gets the index of the circular array after it is converted.
    //! \param idx The index of the circular array.
    //! \return The converted index of the circular array.
    std::size_t Index(std::size_t idx) const
    {
        return idx & m_indexMask;
    }

    std::atomic<std::size_t> m_head = 0;
    std::size_t m_indexMask = 0;
    std::vector<T> m_items;
};
}  // namespace RosettaTorch::AlphaZero

#endif  // ROSETTASTONE_TORCH_ALPHA_ZERO_CIRCULAR_ARRAY_HPP