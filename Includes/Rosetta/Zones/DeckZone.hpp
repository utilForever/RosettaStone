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
class DeckZone : public LimitedZone<Entity>
{
 public:
    //! Default constructor.
    explicit DeckZone(Player* player);

    //! Returns the top card from deck.
    //! \return The top card of deck.
    Entity* GetTopCard() const;

    //! Adds the specified entity into this zone, at the given position.
    //! \param entity The entity.
    //! \param zonePos The zone position.
    void Add(Entity& entity, int zonePos = -1) override;

    //! Shuffles cards in deck.
    void Shuffle();
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_DECK_ZONE_HPP
