// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_IAURA_HPP
#define ROSETTASTONE_PLAYMODE_IAURA_HPP

#include <memory>

namespace RosettaStone::PlayMode
{
class Playable;

//!
//! \brief IAura class.
//!
//! This class is interface for effects of enchantments that should be updated
//! during Game::UpdateAura().
//!
class IAura
{
 public:
    //! Default destructor.
    virtual ~IAura() = default;

    //! Activates this effect and add an instance to the game of given entity.
    //! \param owner The entity who owns this effect.
    //! \param cloning The flag to indicate that it is cloned.
    virtual void Activate(Playable* owner, bool cloning = false) = 0;

    //! Updates this effect to apply the effect to recently modified entities.
    virtual void Update() = 0;

    //! Removes this effect from the game to stop affecting entities.
    virtual void Remove() = 0;

    //! Clones aura effect to \p clone.
    //! \param clone The entity to clone aura effect.
    virtual void Clone(Playable* clone) = 0;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_IAURA_HPP
