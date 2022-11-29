// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYMODE_LOCATION_HPP
#define ROSETTASTONE_PLAYMODE_LOCATION_HPP

#include <Rosetta/PlayMode/Models/Playable.hpp>
#include <Rosetta/PlayMode/Models/Placeable.hpp>

namespace RosettaStone::PlayMode
{
//!
//! \brief Location class.
//!
//! Locations are a type of card first introduced in the Murder at Castle
//! Nathria expansion. Locations are played onto the battlefield for an initial
//! cost, and then have an ability that can be activated for free on the
//! player's turns. Each activation costs 1 durability and has a cooldown of 1
//! turn where it cannot be used.
//!
class Location : public Playable, public Placeable
{
 public:
    //! Constructs location with given \p _player, \p _card, \p tags and \p id.
    //! \param _player The owner of the card.
    //! \param _card The card.
    //! \param tags The game tags.
    //! \param id The card ID.
    Location(Player* _player, Card* _card, std::map<GameTag, int> tags,
             int id = -1);

    //! Default destructor.
    ~Location() = default;

    //! Deleted copy constructor.
    Location(const Location&) = delete;

    //! Deleted copy assignment operator.
    Location& operator=(const Location&) = delete;

    //! Deleted move constructor.
    Location(Location&&) noexcept = delete;

    //! Deleted move assignment operator.
    Location& operator=(Location&&) noexcept = delete;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_LOCATION_HPP
