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
    //! Constructs hero power with given \p player, \p card, \p tags and \p id.
    //! \param player The owner of the card.
    //! \param card The card.
    //! \param tags The game tags.
    //! \param id The ID.
    HeroPower(Player* player, Card* card, std::map<GameTag, int> tags,
              int id = -1);

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

    //! Calculates if a target is valid by testing the game state for each
    //! hardcoded requirement.
    //! \param target The proposed target.
    //! \return true if the proposed target is valid, false otherwise.
    bool TargetingRequirements(Character* target) const override;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_HERO_POWER_HPP
