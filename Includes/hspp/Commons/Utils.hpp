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

    Box() : m_size(0), m_ptr(nullptr)
    {
        // Do nothing
    }

    explicit Box(size_t size) : m_size(size), m_ptr(new T[m_size])
    {
        // Do nothing
    }

    Box(T* ptr, size_t size) : m_size(size), m_ptr(ptr)
    {
        // Do nothing
    }

    ~Box()
    {
        reset();
    }

    Box(const Box& box) : m_size(box.size()), m_ptr(new T[m_size])
    {
        for (size_t i = 0; i < m_size; ++i)
        {
            m_ptr[i] = box[i];
        }
    }

    Box(Box&& box) noexcept : m_size(box.size()), m_ptr(box.get())
    {
        box.m_ptr = nullptr;
        box.m_size = 0;
    }

    Box& operator=(const Box& box)
    {
        reset(new T[box.size()], box.size());
        for (size_t i = 0; i < m_size; ++i)
        {
            m_ptr[i] = box[i];
        }
        return *this;
    }

    Box& operator=(Box&& box) noexcept
    {
        reset(box.get(), box.size());
        box.m_ptr = nullptr;
        box.m_size = 0;
        return *this;
    }

    void reset() noexcept
    {
        if (m_ptr != nullptr)
        {
            delete[] m_ptr;
        }
        m_ptr = nullptr;
        m_size = 0;
    }

    void reset(T* other, size_t size) noexcept
    {
        if (m_ptr != nullptr)
        {
            delete[] m_ptr;
        }
        m_ptr = other;
        m_size = size;
    }

    operator bool()
    {
        return m_ptr != nullptr;
    }

    T* get()
    {
        return m_ptr;
    }

    const T* get() const
    {
        return m_ptr;
    }

    size_t size() const
    {
        return m_size;
    }

    T& operator*()
    {
        return *m_ptr;
    }

    const T& operator*() const
    {
        return *m_ptr;
    }

    T& operator[](size_t idx)
    {
        return m_ptr[idx];
    }

    const T& operator[](size_t idx) const
    {
        return m_ptr[idx];
    }

    bool operator==(const Box& other) const
    {
        if (m_size == other.size())
        {
            for (size_t i = 0; i < m_size; ++i)
            {
                if (m_ptr[i] != other[i])
                {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    bool operator!=(const Box& other) const
    {
        return !operator==(other);
    }

    bool operator==(std::nullptr_t) const
    {
        return m_ptr == nullptr;
    }

    bool operator!=(std::nullptr_t) const
    {
        return m_ptr != nullptr;
    }

    iterator begin()
    {
        return m_ptr;
    }

    const_iterator begin() const
    {
        return m_ptr;
    }

    const_iterator cbegin() const
    {
        return m_ptr;
    }

    iterator end()
    {
        return m_ptr + m_size;
    }

    const_iterator end() const
    {
        return m_ptr + m_size;
    }

    const_iterator cend() const
    {
        return m_ptr + m_size;
    }

 private:
    size_t m_size;
    T* m_ptr;
};

#endif  // HEARTHSTONEPP_UTILS_HPP