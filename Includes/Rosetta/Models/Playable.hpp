// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYABLE_HPP
#define ROSETTASTONE_PLAYABLE_HPP

#include <Rosetta/Models/Entity.hpp>

namespace RosettaStone
{
//!
//! \brief Playable class.
//!
//! This class is an entity which can be played from hand zone into play zone.
//! In other words, the entity can be played.
//!
class Playable : public Entity
{
    //! Constructs entity with given \p _player, \p _card and \p _tags.
    //! \param _player The player.
    //! \param _card The card.
    //! \param _tags The game tags.
    Playable(Player* _player, Card* _card, std::map<GameTag, int> _tags);
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_PLAYABLE_HPP