// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYMODE_EVENT_META_DATA_HPP
#define ROSETTASTONE_PLAYMODE_EVENT_META_DATA_HPP

#include <Rosetta/PlayMode/Models/Playable.hpp>

namespace RosettaStone::PlayMode
{
//!
//! \brief EventMetaData struct.
//!
//! This struct is temporary meta data for event.
//!
struct EventMetaData
{
    //! Default constructor.
    EventMetaData() = default;

    //! Constructs event meta data with given \p source, \p target
    //! and \p number.
    //! \param source The source of the event.
    //! \param target The target of the event.
    //! \param number The number of the event.
    EventMetaData(Playable* source, Playable* target, int number = 0)
        : eventSource(source), eventTarget(target), eventNumber(number)
    {
        // Do nothing
    }

    Playable* eventSource = nullptr;
    Playable* eventTarget = nullptr;
    int eventNumber = 0;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_EVENT_META_DATA_HPP
