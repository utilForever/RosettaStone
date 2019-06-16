// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_SPIN_LOCK_HPP
#define ROSETTASTONE_SPIN_LOCK_HPP

#include <atomic>

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
    SpinLock() = default;

    void Lock()
    {
        while (m_flag.test_and_set(std::memory_order_acquire))
        {
            // Spin
        }
    }

    void Unlock()
    {
        m_flag.clear(std::memory_order_release);
    }

 private:
    std::atomic_flag m_flag;
};

//!
//! \brief SpinLock class.
//!
//! This class is an simple implementation of shared spin lock.
//! It is based on peter1591's hearthstone-ai repository.
//! References: https://github.com/peter1591/hearthstone-ai
//!
class SharedSpinLock
{
 public:
    SharedSpinLock() : m_lock(), m_writer(false), m_readers(0)
    {
        // Do nothing
    }

    void Lock()
    {
        while (true)
        {
            m_lock.Lock();
            if (!m_writer && m_readers == 0)
            {
                break;
            }
            m_lock.Unlock();
        }

        m_writer = true;
        m_lock.Unlock();
    }

    void Unlock()
    {
        m_lock.Lock();
        m_writer = false;
        m_lock.Unlock();
    }

    void LockShared()
    {
        while (true)
        {
            m_lock.Lock();
            if (!m_writer)
            {
                break;
            }
            m_lock.Unlock();
        }

        ++m_readers;
        m_lock.Unlock();
    }

    void UnlockShared()
    {
        m_lock.Lock();
        --m_readers;
        m_lock.Unlock();
    }

 private:
    SpinLock m_lock;
    bool m_writer;
    int m_readers;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_SPIN_LOCK_HPP
