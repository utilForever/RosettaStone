// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_IZONE_HPP
#define ROSETTASTONE_PLAYMODE_IZONE_HPP

#include <Rosetta/Common/Enums/CardEnums.hpp>

namespace RosettaStone::PlayMode
{
class Playable;

//!
//! \brief IZone class.
//!
//! This class is interface of an abstract area where entity objects reside.
//! A zone is owned by a controller and isn't shared.
//!
class IZone
{
 public:
    //! Default destructor.
    virtual ~IZone() = default;

    //! Adds the specified entity into this zone, at the given position.
    //! \param entity The entity.
    //! \param zonePos The zone position.
    virtual void Add(Playable* entity, int zonePos = -1) = 0;

    //! Removes the specified entity from this zone.
    //! \param entity The entity.
    //! \return The entity.
    virtual Playable* Remove(Playable* entity) = 0;

    //! Returns the type of zone.
    ZoneType GetType() const
    {
        return m_type;
    }

    //! Returns a value indicating whether this zone is full.
    //! \return true if this zone is full, false otherwise.
    virtual bool IsFull() const = 0;

 protected:
    //! Gets the kind of zone.
    ZoneType m_type = ZoneType::INVALID;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_IZONE_HPP
