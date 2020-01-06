// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_ALPHA_ZERO_TRAINING_DATA_HPP
#define ROSETTASTONE_TORCH_ALPHA_ZERO_TRAINING_DATA_HPP

#include <AlphaZero/Training/TrainingDataItem.hpp>
#include <AlphaZero/Utils/CircularArray.hpp>
#include <AlphaZero/Utils/SharedPtrItem.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaTorch::AlphaZero
{
//!
//! \brief TrainingData class.
//!
//! This class holds training data using circular array and std::shared_ptr.
//!
class TrainingData
{
 public:
    //! Initializes the training data and its size.
    //! \param capacity The capacity of the training data.
    void Initialize(std::size_t capacity);

    //! Gets the capacity of the training data.
    //! \return The capacity of the training data.
    std::size_t Capacity() const;

    //! Gets the size of the training data.
    //! \return The size of the training data.
    std::size_t Size() const;

    //! Pushes the item to the training data.
    //! \param item The item to push.
    void Push(std::shared_ptr<TrainingDataItem> item);

    //! Fetches the item according the size and runs callback.
    //! \param callback The callback to run.
    //! \return true if reading the training data success, false otherwise.
    template <typename Callback>
    bool GetRandom(Callback&& callback)
    {
        // Fetch the item according to the size. This increase the probability
        // to actually fetch an item which is already written by a writer. But
        // noted that we still has a chance to get an empty (or very old data)
        // if the writer is slow.
        const std::size_t idx = Random::get<std::size_t>(0, m_size.load() - 1);

        // Acquire ownership, so it will not be rotated out.
        const auto sharedPtrItem = m_data.GetRandom(idx).Get();

        // We still has a chance to read an empty data.
        if (!sharedPtrItem)
        {
            return false;
        }

        callback(*sharedPtrItem);

        return true;
    }

 private:
    CircularArray<SharedPtrItem<TrainingDataItem>> m_data;
    std::atomic<std::size_t> m_size = 0;
};
}  // namespace RosettaTorch::AlphaZero

#endif  // ROSETTASTONE_TORCH_ALPHA_ZERO_TRAINING_DATA_HPP