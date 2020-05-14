// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_PLAYMODE_INVALID_ACTION_HPP
#define ROSETTASTONE_PLAYMODE_INVALID_ACTION_HPP

#include <cstddef>

namespace RosettaStone::PlayMode
{
//!
//! \brief InvalidChoice class.
//!
//! This class indicates the choice is invalid.
//! Note that all methods will throw exception.
//!
class InvalidChoice
{
 public:
    //! Returns the action choice at \p idx.
    //! \param idx The index of action choices.
    //! \return The action choice at \p idx.
    static std::size_t Get([[maybe_unused]] std::size_t idx);

    //! Returns the flag indicates that action choices are empty.
    //! \return The flag indicates that action choices are empty.
    static bool IsEmpty();

    //! Returns the number of action choices.
    //! \return The number of action choices.
    static std::size_t Size();

    //! Initializes iterator variable.
    static void Begin();

    //! Returns the element that iterator variable points to.
    //! \return The element that iterator variable points to.
    static std::size_t Get();

    //! Processes iterator to point to the next element.
    static void StepNext();

    //! Returns the flag indicates that iterator is in the end position.
    //! \return the flag indicates that iterator is in the end position.
    static bool IsEnd();
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_INVALID_ACTION_HPP
