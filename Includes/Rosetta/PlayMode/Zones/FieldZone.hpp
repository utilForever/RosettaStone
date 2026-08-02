// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYMODE_FIELD_ZONE_HPP
#define ROSETTASTONE_PLAYMODE_FIELD_ZONE_HPP

#include <Rosetta/PlayMode/Auras/AdjacentAura.hpp>
#include <Rosetta/PlayMode/Models/Location.hpp>
#include <Rosetta/PlayMode/Models/Minion.hpp>
#include <Rosetta/PlayMode/Zones/Zone.hpp>

namespace RosettaStone::PlayMode
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
class FieldZone : public PositioningZone<Character>
{
 public:
    //! Constructs field zone with given \p player.
    //! \param player The player.
    explicit FieldZone(Player* player);

    //! Returns the minion at \p zonePos.
    //! \param zonePos The zone position of minion.
    //! \return The minion at \p zonePos, or nullptr for another field entity.
    Minion* operator[](int zonePos);

    //! Returns the number of minions except untouchables.
    //! \return The number of minions except untouchables.
    int GetCountExceptUntouchables() const;

    //! Returns the number of minions.
    //! \return The number of minions.
    int GetMinionCount() const;

    //! Returns all minions in board zone.
    //! \return A list of minions in board zone.
    std::vector<Minion*> GetMinions() const;

    //! Returns all locations in board zone.
    //! \return A list of locations in board zone.
    std::vector<Location*> GetLocations() const;

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

    //! Activates a minion's trigger and aura and
    //! applies it's spell power increment.
    //! \param entity The entity to activate aura.
    static void ActivateAura(Playable* entity);

    //! Registers an adjacent aura on this field.
    //! \param aura The adjacent aura.
    void AddAdjacentAura(AdjacentAura* aura);

    //! Marks every adjacent aura for an update.
    void MarkAdjacentAurasDirty();

 private:
    //! Removes a minion's trigger and aura and
    //! applies it's spell power increment.
    //! \param entity The entity to remove aura.
    static void RemoveAura(const Playable* entity);

    std::vector<AdjacentAura*> m_adjacentAuras;
    int m_untouchableCount = 0;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_FIELD_ZONE_HPP
