// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_HAND_ZONE_HPP
#define ROSETTASTONE_BATTLEGROUNDS_HAND_ZONE_HPP

#include <Rosetta/Battlegrounds/Models/Minion.hpp>
#include <Rosetta/Battlegrounds/Models/Spell.hpp>
#include <Rosetta/Common/Constants.hpp>

#include <array>
#include <optional>
#include <variant>

namespace RosettaStone::Battlegrounds
{
using CardData = std::optional<std::variant<Minion, Spell>>;

//!
//! \brief HandZone class.
//!
//! This class is where each player keeps the cards currently available to
//! them. The player can see their hand face-up at the bottom of the screen,
//! while the opponent's hand is shown face-down at the top of the screen.
//!
class HandZone
{
 public:
    //! Adds the specified card into this zone, at the given position.
    //! \param card The card context.
    //! \param zonePos The zone position.
    void Add(const std::variant<Minion, Spell>& card, int zonePos = -1);

    //! Returns the number of entities in this zone.
    //! \return The number of entities in this zone.
    int GetCount() const;

    //! Returns a value indicating whether this zone is full.
    //! \return true if this zone is full, false otherwise.
    bool IsFull() const;

 private:
    std::array<CardData, MAX_HAND_SIZE> m_cards;
    int m_count = 0;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_HAND_ZONE_HPP
