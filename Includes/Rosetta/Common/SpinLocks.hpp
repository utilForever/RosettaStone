// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_SPIN_LOCK_HPP
#define ROSETTASTONE_SPIN_LOCK_HPP

#include <atomic>
#include <thread>

namespace RosettaStone
{
//!
//! \brief SpinLock class.
//!
//! This class is an simple implementation of spin lock.
//! It is based on peter1591's hearthstone-ai repository.
//! References: https://github.com/peter1591/hearthstone-ai
//!
class SpinLock
{
 public:
    //! Default constructor.
    SpinLock() = default;

    //! Acquires ownership of the spinlock.
    void lock()
    {
        while (m_flag.test_and_set(std::memory_order_acquire))
        {
            std::this_thread::yield();
        }
    }

    //! Releases ownership of the spinlock.
    void unlock()
    {
        m_flag.clear(std::memory_order_release);
    }

 private:
    std::atomic_flag m_flag;
};

//!
//! \brief SharedSpinLock class.
//!
//! This class is an simple implementation of shared spin lock.
//! It is based on peter1591's hearthstone-ai repository.
//! References: https://github.com/peter1591/hearthstone-ai
//!
class SharedSpinLock
{
 public:
    //! Default constructor.
    SharedSpinLock() : m_lock(), m_writer(false), m_readers(0)
    {
        // Do nothing
    }

    //! Acquires ownership of the spinlock.
    void lock()
    {
        while (true)
        {
            m_lock.lock();
            if (!m_writer && m_readers == 0)
            {
                break;
            }
            m_lock.unlock();
        }

        m_writer = true;
        m_lock.unlock();
    }

    //! Releases ownership of the spinlock.
    void unlock()
    {
        m_lock.lock();
        m_writer = false;
        m_lock.unlock();
    }

    //! Acquires shared ownership of the spinlock.
    void lock_shared()
    {
        while (true)
        {
            m_lock.lock();
            if (!m_writer)
            {
                break;
            }
            m_lock.unlock();
        }

        ++m_readers;
        m_lock.unlock();
    }

    //! Releases shared ownership of the spinlock.
    void unlock_shared()
    {
        m_lock.lock();
        --m_readers;
        m_lock.unlock();
    }

 private:
    SpinLock m_lock;
    bool m_writer;
    int m_readers;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_SPIN_LOCK_HPP
