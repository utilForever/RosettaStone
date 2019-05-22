// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_SECRET_ZONE_HPP
#define ROSETTASTONE_SECRET_ZONE_HPP

#include <Rosetta/Models/Spell.hpp>
#include <Rosetta/Zones/Zone.hpp>

namespace RosettaStone
{
//!
//! \brief SecretZone class.
//!
//! The zone containing all played secrets by this player. Can be empty.
//!
class SecretZone : public LimitedZone<Spell>
{
 public:
    //! Default constructor.
    SecretZone(Player* player);

    //! Adds the specified entity into this zone, at the given position.
    //! \param entity The entity.
    //! \param zonePos The zone position.
    void Add(Entity& entity, int zonePos = -1) override;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_SECRET_ZONE_HPP
