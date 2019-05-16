// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_IZONE_HPP
#define ROSETTASTONE_IZONE_HPP

#include <Rosetta/Enums/CardEnums.hpp>

namespace RosettaStone
{
class Entity;

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
    virtual void Add(Entity& entity, int zonePos = -1) = 0;

    //! Removes the specified entity from this zone.
    //! \param entity The entity.
    //! \return The entity.
    virtual Entity& Remove(Entity& entity) = 0;

    //! Returns the type of zone.
    Zone GetType() const
    {
        return m_type;
    }

 protected:
    //! Gets the kind of zone.
    Zone m_type = Zone::INVALID;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_IZONE_HPP
