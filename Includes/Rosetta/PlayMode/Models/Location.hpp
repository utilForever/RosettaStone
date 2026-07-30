// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYMODE_LOCATION_HPP
#define ROSETTASTONE_PLAYMODE_LOCATION_HPP

#include <Rosetta/PlayMode/Models/Character.hpp>

namespace RosettaStone::PlayMode
{
//!
//! \brief Location class.
//!
//! Locations are a type of card first introduced in the Murder at Castle
//! Nathria expansion. Locations are played onto the battlefield for an initial
//! cost, and then have an ability that can be activated for free on the
//! player's turns. Each activation costs 1 Health and has a cooldown of 1
//! turn where it cannot be used.
//!
class Location : public Character
{
 public:
    //! Constructs location with given \p _player, \p _card, \p tags and \p id.
    Location(Player* _player, Card* _card, std::map<GameTag, int> tags,
             int id = -1);

    //! Default destructor.
    ~Location() override = default;

    //! Returns whether this location is on cooldown.
    bool IsOnCooldown() const;

    //! Sets whether this location is on cooldown.
    void SetOnCooldown(bool onCooldown);

    //! Returns false because locations cannot attack.
    bool CanAttack() const override;

    //! Consumes one Health and starts the cooldown.
    void Use();

    //! Removes the location from the battlefield.
    void Destroy() override;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_LOCATION_HPP
