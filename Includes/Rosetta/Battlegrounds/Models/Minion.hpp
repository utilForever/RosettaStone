// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_MINION_HPP
#define ROSETTASTONE_BATTLEGROUNDS_MINION_HPP

#include <Rosetta/Battlegrounds/Cards/Card.hpp>

namespace RosettaStone::Battlegrounds
{
//!
//! \brief Minion class.
//!
//! Minions are persistent creatures on the battlefield that will fight for
//! their hero. Minion cards can be recognized by their Attack (a number
//! displayed on a yellow sword, in the bottom left corner) and Health (a number
//! displayed on a red blood drop, in the bottom right corner).
//!
class Minion
{
 public:
    //! Default constructor.
    Minion() = default;

    //! Constructs Minion instance with given \p card.
    //! \param card A card that contains the minion data.
    Minion(Card card);

    //! Returns the tier of the minion.
    int GetTier() const;

 private:
    Card m_card;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_MINION_HPP
