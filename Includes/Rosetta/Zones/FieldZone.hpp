// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_FIELD_ZONE_HPP
#define ROSETTASTONE_FIELD_ZONE_HPP

#include <Rosetta/Auras/AdjacentAura.hpp>
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
    //! Constructs field zone with given \p player.
    //! \param player The player.
    explicit FieldZone(Player* player);

    //! Copies the contents from reference \p rhs.
    //! \param rhs The source to copy the content.
    void RefCopy(FieldZone* rhs) const;

    //! Returns all entities in board zone.
    //! \return A list of entity in board zone.
    std::vector<Minion*> GetAll() override;

    //! Returns all entities in board zone.
    //! \return A list of entity in board zone.
    std::vector<Minion*> GetAll() const override;

    //! Adds the specified entity into this zone, at the given position.
    //! \param entity The entity.
    //! \param zonePos The zone position.
    void Add(Playable* entity, int zonePos = -1) override;

    //! Removes the specified entity from this zone.
    //! \param entity The entity.
    //! \return The entity.
    Playable* Remove(Playable* entity) override;

    //! Replaces minion with another.
    //! \param oldEntity The entity to be replaced.
    //! \param newEntity The new entity.
    void Replace(Minion* oldEntity, Minion* newEntity);

    //! Finds the index of the minion.
    //! \param minion The minion to find.
    //! \return The index of the minion if it is found, -1 otherwise.
    int FindIndex(Minion* minion) const;

    std::vector<AdjacentAura*> adjacentAuras;

 private:
    static void ActivateAura(Minion* entity);

    static void RemoveAura(Minion* entity);
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_FIELD_ZONE_HPP
