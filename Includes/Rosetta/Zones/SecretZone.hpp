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
    //! Constructs secret zone with given \p player.
    //! \param player The player.
    explicit SecretZone(Player* player);

    //! Copies the contents from reference \p rhs.
    //! \param rhs The source to copy the content.
    void RefCopy(const SecretZone& rhs) const;

    //! Adds the specified entity into this zone, at the given position.
    //! \param entity The entity.
    //! \param zonePos The zone position.
    void Add(Playable* entity, int zonePos = -1) override;

    //! Removes the specified entity from this zone.
    //! \param entity The entity.
    //! \return The entity.
    Playable* Remove(Playable* entity) override;

    //! Returns whether the secret card exists in this zone.
    //! \param entity The spell to check whether it exists.
    //! \return The flag that indicates whether the spell exists.
    bool Exist(Playable* entity) const;

    Spell* quest = nullptr;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_SECRET_ZONE_HPP
