// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_HERO_POWER_HPP
#define ROSETTASTONE_HERO_POWER_HPP

#include <Rosetta/Models/Playable.hpp>

namespace RosettaStone
{
//!
//! \brief HeroPower class.
//!
//! This class inherits from Playable class.
//!
class HeroPower : public Playable
{
 public:
    //! Constructs hero power with given \p player, \p card and \p tags.
    //! \param player The owner of the card.
    //! \param card The card.
    //! \param tags The game tags.
    HeroPower(Player* player, Card* card, std::map<GameTag, int> tags);

    //! Default destructor.
    ~HeroPower() = default;

    //! Deleted copy constructor.
    HeroPower(const HeroPower&) = delete;

    //! Deleted copy assignment operator.
    HeroPower& operator=(const HeroPower&) = delete;

    //! Deleted move constructor.
    HeroPower(HeroPower&&) noexcept = delete;

    //! Deleted move assignment operator.
    HeroPower& operator=(HeroPower&&) noexcept = delete;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_HERO_POWER_HPP
