// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_SYNC_BUFFER_H
#define HEARTHSTONEPP_SYNC_BUFFER_H

#include <condition_variable>
#include <mutex>

namespace Hearthstonepp
{
//!
//! \brief SyncBuffer class.
//!
//! This class reads/writes synchronized buffer.
//! \tparam BufferType The type of buffer. (copy-assignable and movable)
//!
template <typename BufferType>
class SyncBuffer
{
 public:
    //! Default constructor.
    SyncBuffer() : m_readable(false)
    {
        // Do nothing
    }

    //! Default destructor.
    ~SyncBuffer() = default;

    //! Deleted copy constructor.
    SyncBuffer(const SyncBuffer&) = delete;

    //! Deleted move constructor.
    SyncBuffer(SyncBuffer&&) = delete;

    //! Deleted copy assignment operator.
    SyncBuffer& operator=(const SyncBuffer&) = delete;

    //! Deleted move assignment operator.
    SyncBuffer& operator=(SyncBuffer&&) = delete;

    //! Writes \p buffer to synchronized buffer.
    //! \param buffer The buffer to write (rvalue ref).
    void WriteBuffer(BufferType&& buffer)
    {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_cond.wait(lock, [=]() { return !m_readable; });

        m_buffer = std::move(buffer);

        m_readable = true;
        m_cond.notify_one();
    }

    //! Writes \p buffer to synchronized buffer.
    //! \param buffer The buffer to write (lvalue ref).
    void WriteBuffer(const BufferType& buffer)
    {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_cond.wait(lock, [=]() { return !m_readable; });

        m_buffer = buffer;

        m_readable = true;
        m_cond.notify_one();
    }

    //! Reads \p buffer from synchronized buffer.
    //! \param buffer The buffer to read.
    void ReadBuffer(BufferType& buffer)
    {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_cond.wait(lock, [=]() { return m_readable; });

        buffer = std::move(m_buffer);

        m_readable = false;
        m_cond.notify_one();
    }

    //! Returns whether it is readable.
    //! \return true if it is readable, and false otherwise.
    bool IsReadable() const
    {
        return m_readable;
    }

 private:
    bool m_readable;
    BufferType m_buffer;

    std::mutex m_mtx;
    std::condition_variable m_cond;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_SYNC_BUFFER_H
