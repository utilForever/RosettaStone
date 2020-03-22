// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_DECK_ZONE_HPP
#define ROSETTASTONE_DECK_ZONE_HPP

#include <Rosetta/Models/Entity.hpp>
#include <Rosetta/Zones/Zone.hpp>

namespace RosettaStone
{
//!
//! \brief DeckZone class.
//!
//! This class stores a deck. A deck is a collection of exactly 30 cards
//! assembled before a match, as well as the zone which players draw cards from
//! (and sometimes add cards to) during game play. Each deck is tied to a
//! specific class.
//!
class DeckZone : public LimitedZone<Playable>
{
 public:
    //! Constructs deck zone with given \p player.
    //! \param player The player.
    explicit DeckZone(Player* player);

    //! Copies the contents from reference \p rhs.
    //! \param rhs The source to copy the content.
    void RefCopy(DeckZone* rhs) const;

    //! Returns the top card from deck.
    //! \return The top card of deck.
    Playable* GetTopCard() const;

    //! Adds the specified entity into this zone, at the given position.
    //! \param entity The entity.
    //! \param zonePos The zone position.
    void Add(Playable* entity, int zonePos = -1) override;

    //! Replaces an entity in the given position internally.
    //! \param oldEntity The old entity.
    //! \param newEntity The new entity.
    void ChangeEntity(Playable* oldEntity, Playable* newEntity) override;

    //! Shuffles cards in deck.
    void Shuffle() const;

    //! Sets an new entity.
    //! \param index The position of entity.
    //! \param newEntity The new entity.
    void SetEntity(int index, Playable* newEntity);
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_DECK_ZONE_HPP
