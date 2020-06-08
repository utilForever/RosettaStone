// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_HERO_HPP
#define ROSETTASTONE_BATTLEGROUNDS_HERO_HPP

#include <Rosetta/Battlegrounds/Cards/Card.hpp>

namespace RosettaStone::Battlegrounds
{
//!
//! \brief Hero class.
//!
//! A hero is a character in the Warcraft universe representing the player.
//!
class Hero
{
 public:
    //! Initializes a Hero instance and assigns the information.
    //! \param heroCard The card of a Hero instance.
    void Initialize(const Card& heroCard);

    Card card;
    int health = 0;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_HERO_HPP
