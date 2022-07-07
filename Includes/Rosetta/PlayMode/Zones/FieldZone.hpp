// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYMODE_FIELD_ZONE_HPP
#define ROSETTASTONE_PLAYMODE_FIELD_ZONE_HPP

#include <Rosetta/PlayMode/Auras/AdjacentAura.hpp>
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
class FieldZone : public PositioningZone<Minion>
{
 public:
    //! Constructs field zone with given \p player.
    //! \param player The player.
    explicit FieldZone(Player* player);

    //! Returns the number of minions except untouchables.
    //! \return The number of minions except untouchables.
    int GetCountExceptUntouchables() const;

    //! Returns all entities in board zone.
    //! \return A list of entity in board zone.
    std::vector<Minion*> GetAll() override;

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
    static void ActivateAura(Minion* entity);

    std::vector<AdjacentAura*> adjacentAuras;

 private:
    //! Removes a minion's trigger and aura and
    //! applies it's spell power increment.
    //! \param entity The entity to remove aura.
    static void RemoveAura(const Minion* entity);

    int m_untouchableCount = 0;
    bool m_hasUntouchables = false;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_FIELD_ZONE_HPP
