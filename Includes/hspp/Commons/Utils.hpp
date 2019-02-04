// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_UTILS_HPP
#define HEARTHSTONEPP_UTILS_HPP

#include <cstddef>

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
//! \brief Box class.
//!
//! This class is unique_ptr like pointer wrapper.
//! For std::any, base class required copy constructible, it supports both deep
//! copy and move operations.
//!
template <typename T>
class Box
{
 public:
    using value_type = T;
    using size_type = std::size_t;

    using reference = T&;
    using const_reference = const T&;

    using pointer = T*;
    using const_pointer = const T*;

    using iterator = pointer;
    using const_iterator = const_pointer;

    //! Default constructor.
    Box() : m_size(0), m_ptr(nullptr)
    {
        // Do nothing
    }

    //! Constructs box with given /p size.
    //! \param size The size of buffer.
    explicit Box(size_t size) : m_size(size), m_ptr(new T[m_size])
    {
        // Do nothing
    }

    //! Constructs box with given \p ptr and \p size.
    //! \param ptr The pointer that box managing.
    //! \param size The size of buffer.
    Box(T* ptr, size_t size) : m_size(size), m_ptr(ptr)
    {
        // Do nothing
    }

    //! Default destructor.
    ~Box()
    {
        reset();
    }

    //! Copy constructor, deep copying buffer.
    Box(const Box& box) : m_size(box.size()), m_ptr(new T[m_size])
    {
        for (size_t i = 0; i < m_size; ++i)
        {
            m_ptr[i] = box[i];
        }
    }

    //! Move constructor.
    Box(Box&& box) noexcept : m_size(box.size()), m_ptr(box.get())
    {
        box.m_ptr = nullptr;
        box.m_size = 0;
    }

    //! Copy assignment operator, deep copying buffer.
    Box& operator=(const Box& box)
    {
        reset(new T[box.size()], box.size());
        for (size_t i = 0; i < m_size; ++i)
        {
            m_ptr[i] = box[i];
        }
        return *this;
    }

    //! Move assignment operator.
    Box& operator=(Box&& box) noexcept
    {
        reset(box.get(), box.size());

        box.m_ptr = nullptr;
        box.m_size = 0;

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
    //! \param other The pointer that box managing.
    //! \param size The size of buffer.
    void reset(T* other, size_t size) noexcept
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
    size_t size() const
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
    //! \return The index'th element of buffer.
    T& operator[](size_t idx)
    {
        return m_ptr[idx];
    }

    //! Gets the element with given \p idx from buffer.
    //! \param idx The index of buffer.
    //! \return The index'th element of buffer.
    const T& operator[](size_t idx) const
    {
        return m_ptr[idx];
    }

    //! Check the equality of two buffers.
    //! \param other Comparable object.
    //! \return Equality about two buffers.
    bool operator==(const Box& other) const
    {
        if (m_size != other.size())
        {
            return false;
        }

        for (size_t i = 0; i < m_size; ++i)
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
    bool operator!=(const Box& other) const
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
    size_t m_size;
    T* m_ptr;
};

#endif  // HEARTHSTONEPP_UTILS_HPP