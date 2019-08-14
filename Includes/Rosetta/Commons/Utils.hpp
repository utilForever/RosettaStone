// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_UTILS_HPP
#define ROSETTASTONE_UTILS_HPP

#include <cstddef>
#include <functional>

template <typename T>
constexpr bool AllCondIsTrue(const T& t)
{
    return t == true;
}

template <typename T, typename... Others>
constexpr bool AllCondIsTrue(const T& t, Others const&... args)
{
    return (t == true) && AllCondIsTrue(args...);
}

//!
//! \brief CombineHash function.
//!
//! It is based on peter1591's hearthstone-ai repository.
//! References: https://github.com/peter1591/hearthstone-ai
//!
template <typename T>
void CombineHash(std::size_t& seed, const T& v)
{
    seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <typename ContainerT, typename PredicateT>
void EraseIf(ContainerT& items, const PredicateT& predicate)
{
    for (auto it = items.begin(); it != items.end();)
    {
        if (predicate(*it))
        {
            it = items.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

//!
//! \brief SizedPtr class.
//!
//! This class is unique_ptr like pointer wrapper.
//! For std::any, base class required copy constructible, it supports both deep
//! copy and move operations.
//!
template <typename T>
class SizedPtr
{
 public:
    using value_type = T;

    using reference = T&;
    using const_reference = const T&;

    using pointer = T*;
    using const_pointer = const T*;

    using iterator = pointer;
    using const_iterator = const_pointer;

    //! Default constructor.
    SizedPtr() : m_size(0), m_ptr(nullptr)
    {
        // Do nothing
    }

    //! Constructs sized ptr with given /p size.
    //! \param size The size of buffer.
    explicit SizedPtr(std::size_t size) : m_size(size), m_ptr(new T[m_size])
    {
        // Do nothing
    }

    //! Constructs sized ptr with given \p ptr and \p size.
    //! \param ptr The pointer that sized ptr managing.
    //! \param size The size of buffer.
    SizedPtr(T* ptr, std::size_t size) : m_size(size), m_ptr(ptr)
    {
        // Do nothing
    }

    //! Default destructor.
    ~SizedPtr()
    {
        reset();
    }

    //! Copy constructor, deep copying buffer.
    SizedPtr(const SizedPtr& ptr) : m_size(ptr.size()), m_ptr(new T[m_size])
    {
        for (std::size_t i = 0; i < m_size; ++i)
        {
            m_ptr[i] = ptr[i];
        }
    }

    //! Move constructor.
    SizedPtr(SizedPtr&& ptr) noexcept : m_size(ptr.size()), m_ptr(ptr.get())
    {
        ptr.m_ptr = nullptr;
        ptr.m_size = 0;
    }

    //! Copy assignment operator, deep copying buffer.
    SizedPtr& operator=(const SizedPtr& ptr)
    {
        reset(new T[ptr.size()], ptr.size());
        for (std::size_t i = 0; i < m_size; ++i)
        {
            m_ptr[i] = ptr[i];
        }
        return *this;
    }

    //! Move assignment operator.
    SizedPtr& operator=(SizedPtr&& ptr) noexcept
    {
        reset(ptr.get(), ptr.size());

        ptr.m_ptr = nullptr;
        ptr.m_size = 0;

        return *this;
    }

    //! Resets buffer.
    void reset() noexcept
    {
        if (m_ptr != nullptr)
        {
            delete[] m_ptr;
        }

        m_ptr = nullptr;
        m_size = 0;
    }

    //! Resets buffer with given \p other and \p size.
    //! \param other The pointer that sized ptr managing.
    //! \param size The size of buffer.
    void reset(T* other, std::size_t size) noexcept
    {
        if (m_ptr != nullptr)
        {
            delete[] m_ptr;
        }

        m_ptr = other;
        m_size = size;
    }

    //! Queries that object has buffer.
    operator bool()
    {
        return m_ptr != nullptr;
    }

    //! Gets buffer pointer.
    //! \return The pointer of buffer.
    T* get()
    {
        return m_ptr;
    }

    //! Gets buffer pointer.
    //! \return The pointer of buffer.
    const T* get() const
    {
        return m_ptr;
    }

    //! Gets size of buffer.
    //! \return The size of buffer.
    std::size_t size() const
    {
        return m_size;
    }

    //! Gets the first element of buffer.
    //! \return The first element of buffer.
    T& operator*()
    {
        return *m_ptr;
    }

    //! Gets the first element of buffer.
    //! \return The first element of buffer.
    const T& operator*() const
    {
        return *m_ptr;
    }

    //! Gets the element with given \p idx from buffer.
    //! \param idx The index of buffer.
    //! \return The element of buffer at idx.
    T& operator[](std::size_t idx)
    {
        return m_ptr[idx];
    }

    //! Gets the element with given \p idx from buffer.
    //! \param idx The index of buffer.
    //! \return The element of buffer at idx.
    const T& operator[](std::size_t idx) const
    {
        return m_ptr[idx];
    }

    //! Check the equality of two buffers.
    //! \param other Comparable object.
    //! \return Equality about two buffers.
    bool operator==(const SizedPtr& other) const
    {
        if (m_size != other.size())
        {
            return false;
        }

        for (std::size_t i = 0; i < m_size; ++i)
        {
            if (m_ptr[i] != other[i])
            {
                return false;
            }
        }

        return true;
    }

    //! Check the inequality of two buffers.
    //! \param other Comparable object.
    //! \return Inequality about two buffers.
    bool operator!=(const SizedPtr& other) const
    {
        return !operator==(other);
    }

    //! Check if the buffer is empty.
    //! \return true if buffer is empty, false otherwise.
    bool operator==(std::nullptr_t) const
    {
        return m_ptr == nullptr;
    }

    //! Check if the buffer is not empty.
    //! \return true if buffer is not empty, false otherwise.
    bool operator!=(std::nullptr_t) const
    {
        return m_ptr != nullptr;
    }

    //! Gets begining iterator of the buffer.
    //! \return The begining iterator.
    iterator begin()
    {
        return m_ptr;
    }

    //! Gets constant begining iterator of the buffer.
    //! \return The constant begining iterator.
    const_iterator begin() const
    {
        return m_ptr;
    }

    //! Gets constant begining iterator of the buffer.
    //! \return The constant begining iterator.
    const_iterator cbegin() const
    {
        return m_ptr;
    }

    //! Gets ending iterator of the buffer.
    //! \return The ending iterator.
    iterator end()
    {
        return m_ptr + m_size;
    }

    //! Gets ending iterator of the buffer.
    //! \return The ending iterator.
    const_iterator end() const
    {
        return m_ptr + m_size;
    }

    //! Gets ending iterator of the buffer.
    //! \return The ending iterator.
    const_iterator cend() const
    {
        return m_ptr + m_size;
    }

 private:
    std::size_t m_size;
    T* m_ptr;
};

#endif  // ROSETTASTONE_UTILS_HPP
