// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_SPELL_HPP
#define ROSETTASTONE_BATTLEGROUNDS_SPELL_HPP

#include <Rosetta/Battlegrounds/Cards/Card.hpp>

namespace RosettaStone::Battlegrounds
{
//!
//! \brief Spell class.
//!
//! Spell cards are cards that can be played to trigger a one time effect or
//! ability, described in the card's text. Casting a spell consumes the card,
//! producing an immediate effect, although spells with the Secret or Quest
//! ability are delayed until activated by specific events. Spell cards do not
//! have Attack or Health attributes, only a mana cost, shown in the top left
//! corner.
//!
class Spell
{
 public:
    //! Default constructor.
    Spell() = default;

    //! Constructs Minion instance with given \p card.
    //! \param card A card that contains the spell data.
    explicit Spell(Card card);

    //! Returns the value of zone type.
    //! \return The value of zone type.
    ZoneType GetZoneType() const;

    //! Sets the value of zone type.
    //! \param type The value of zone type.
    void SetZoneType(ZoneType type);

    //! Returns the value of zone position.
    //! \return The value of zone position.
    int GetZonePosition() const;

    //! Sets the value of zone position.
    //! \param pos The value of zone position.
    void SetZonePosition(int pos);

 private:
    Card m_card;

    ZoneType m_zoneType = ZoneType::INVALID;
    int m_zonePos = -1;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_SPELL_HPP
