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
using CardData = std::variant<Minion, Spell>;

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
    //! Operator overloading for operator[].
    //! \param zonePos The zone position of card.
    //! \return The card at \p zonePos.
    CardData& operator[](int zonePos);

    //! Adds the specified card into this zone, at the given position.
    //! \param card The card context to add.
    //! \param zonePos The zone position.
    void Add(CardData card, int zonePos = -1);

    //! Removes the specified card from this zone.
    //! \param card The card context to remove.
    //! \return The removed card.
    const CardData Remove(CardData& card);

    //! Repositions all cards by \p zonePos.
    //! \param zonePos The position of card to add or remove.
    void Reposition(int zonePos = 0);

    //! Returns the number of cards in this zone.
    //! \return The number of cards in this zone.
    int GetCount() const;

    //! Returns a value indicating whether this zone is full.
    //! \return true if this zone is full, false otherwise.
    bool IsFull() const;

    //! Runs \p functor on each card.
    //! \param functor A function to run for each card.
    template <typename Functor>
    void ForEach(Functor&& functor)
    {
        for (auto& card : m_cards)
        {
            if (card.has_value())
            {
                functor(card);
            }
        }
    }

    //! Runs \p functor on each card.
    //! \param functor A function to run for each card.
    template <typename Functor>
    void ForEach(Functor&& functor) const
    {
        for (const auto& card : m_cards)
        {
            if (card.has_value())
            {
                functor(card);
            }
        }
    }

 private:
    const ZoneType m_type = ZoneType::HAND;

    std::array<std::optional<CardData>, MAX_HAND_SIZE> m_cards;
    int m_count = 0;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_HAND_ZONE_HPP
