/*************************************************************************
> File Name: SyncBuffer.h
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Synchronized Buffer
> Created Time: 2018/05/20
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_SYNCBUFFER_H
#define HEARTHSTONEPP_SYNCBUFFER_H

#include <condition_variable>
#include <mutex>

namespace Hearthstonepp
{
// BufferType must be copy-assignable and movable
template <typename BufferType>
class SyncBuffer
{
 public:
    SyncBuffer() : m_readable(false)
    {
        // Do Nothing
    }

    // Not copy-assignable
    SyncBuffer(SyncBuffer&&) = delete;

    SyncBuffer(const SyncBuffer&) = delete;

    SyncBuffer& operator=(SyncBuffer&&) = delete;

    SyncBuffer& operator=(const SyncBuffer&) = delete;

    void WriteBuffer(BufferType&& buffer)
    {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_cond.wait(lock, [=]() { return !m_readable; });

        m_buffer = std::move(buffer);

        m_readable = true;
        m_cond.notify_one();
    }

    void WriteBuffer(const BufferType& buffer)
    {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_cond.wait(lock, [=]() { return !m_readable; });

        m_buffer = buffer;

        m_readable = true;
        m_cond.notify_one();
    }

    void ReadBuffer(BufferType& buffer)
    {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_cond.wait(lock, [=]() { return m_readable; });

        buffer = std::move(m_buffer);

        m_readable = false;
        m_cond.notify_one();
    }

    bool isReadable() const
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

#endif  // HEARTHSTONEPP_SYNCBUFFER_H
