// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_ALPHA_ZERO_SHARED_PTR_ITEM_HPP
#define ROSETTASTONE_TORCH_ALPHA_ZERO_SHARED_PTR_ITEM_HPP

#include <atomic>
#include <memory>

namespace RosettaTorch::AlphaZero
{
//!
//! \brief SharedPtrItem class.
//!
//! This class holds a lock-free item.
//!
template <typename T>
class SharedPtrItem
{
 public:
    //! Writes a lock-free item by calling std::atomic_exchange.
    //! If no reader is holding item, it is destroyed and pointed to.
    //! NOTE: Destroy since no variable catching return value.
    //! If a reader is holding item, the lifetime is transferred automatically.
    //! \param item A lock-free item to write.
    void Write(std::shared_ptr<T> item)
    {
        std::atomic_exchange(&m_item, item);
    }

    //! Gets a lock-free item.
    //! \return A lock-free item.
    std::shared_ptr<T> Get() const
    {
        return m_item;
    }

 private:
    std::shared_ptr<T> m_item;
};
}  // namespace RosettaTorch::AlphaZero

#endif  // ROSETTASTONE_TORCH_ALPHA_ZERO_SHARED_PTR_ITEM_HPP