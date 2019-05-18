// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_ZONE_HPP
#define ROSETTASTONE_ZONE_HPP

#include <Rosetta/Zones/IZone.hpp>

namespace RosettaStone
{
//!
//! \brief Zone class.
//!
//! This class is base implementation of IZone.
//!
template <typename T>
class Zone : public IZone
{
 public:
    //! Adds the specified entity into this zone, at the given position.
    //! \param entity The entity.
    //! \param zonePos The zone position.
    void Add(Entity& entity, int zonePos = -1) override = 0;

    //! Removes the specified entity from this zone.
    //! \param entity The entity.
    //! \return The entity.
    Entity& Remove(Entity& entity) override = 0;

protected:
    std::vector<T> m_entities;
};

//!
//! \brief UnlimitedZone class.
//!
//! This class is base implementation of GraveyardZone and SetasideZone.
//!
class UnlimitedZone : public Zone<Entity*>
{
 public:
    void Add(Entity& entity, int zonePos = -1) override
    {
        (void)entity;
        (void)zonePos;

        // Do nothing
    }

    Entity& Remove(Entity& entity) override
    {
        return entity;
    }
};

//!
//! \brief LimitedZone class.
//!
//! This class is base implementation of zones which have a maximum size.
//!
template <typename T>
class LimitedZone : public Zone<T>
{
    void Add(Entity& entity, int zonePos = -1) override
    {
        (void)entity;
        (void)zonePos;

        // Do nothing
    }

    Entity& Remove(Entity& entity) override
    {
        return entity;
    }
};

//!
//! \brief PositioningZone class.
//!
//! This class is base implementation of zones performing strict recalculation
//! of its containing entities' ZonePosition when any member comes and goes.
//!
template <typename T>
class PositioningZone : public LimitedZone<T>
{
    void Add(Entity& entity, int zonePos = -1) override
    {
        (void)entity;
        (void)zonePos;

        // Do nothing
    }

    Entity& Remove(Entity& entity) override
    {
        return entity;
    }
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_IZONE_HPP
