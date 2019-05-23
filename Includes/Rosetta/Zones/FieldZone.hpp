// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_FIELD_ZONE_HPP
#define ROSETTASTONE_FIELD_ZONE_HPP

#include <Rosetta/Models/Minion.hpp>
#include <Rosetta/Zones/Zone.hpp>

namespace RosettaStone
{
//!
//! \brief FieldZone class.
//!
//! This class is where the action takes place, representing the board on which
//! each game is played out. Around the battlefield are various important UI
//! elements, such as each player's hand, deck and Mana Crystals, as well as the
//! two heroes themselves. Each battlefield features its own design and numerous
//! interactive elements, but play is in no way affected or determined by
//! battlefield selection. Battlefields are chosen at random and are independent
//! of the heroes chosen by players or used by the Innkeeper.
//!
class FieldZone : public PositioningZone<Minion>
{
 public:
    //! Default constructor.
    explicit FieldZone(Player* player);

    //! Returns all entities in board zone.
    //! \return A list of entity in board zone.
    std::vector<Minion*> GetAll() override;

    //! Adds the specified entity into this zone, at the given position.
    //! \param entity The entity.
    //! \param zonePos The zone position.
    void Add(Entity& entity, int zonePos = -1) override;

    //! Removes the specified entity from this zone.
    //! \param entity The entity.
    //! \return The entity.
    Entity& Remove(Entity& entity) override;

    //! Replaces minion with another.
    //! \param oldEntity The entity to be replaced.
    //! \param newEntity The new entity.
    void Replace(Entity& oldEntity, Entity& newEntity);

 private:
    static void ActivateAura(Entity& entity);
    static void RemoveAura(Entity& entity);
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_FIELD_ZONE_HPP
