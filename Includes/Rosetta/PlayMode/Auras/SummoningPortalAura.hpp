// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_SUMMONING_PORTAL_AURA_HPP
#define ROSETTASTONE_PLAYMODE_SUMMONING_PORTAL_AURA_HPP

#include <Rosetta/PlayMode/Auras/Aura.hpp>

namespace RosettaStone::PlayMode
{
//!
//! \brief SummoningPortalAura class.
//!
//! This class is an aura for card 'Summoning Portal'.
//!
class SummoningPortalAura : public Aura
{
 public:
    //! Default constructor.
    SummoningPortalAura();

    //! Create new Aura instance to the owner's game.
    //! \param owner An owner of enrage effect.
    //! \param cloning The flag to indicate that it is cloned.
    void Activate(Playable* owner, bool cloning = false) override;

    //! Apply this aura to the target entities or remove this aura
    //! if the owner is nullified.
    void Update() override;

    //! Clones aura effect to \p clone.
    //! \param clone The entity to clone aura effect.
    void Clone(Playable* clone) override;

    //! Applies aura's effect(s) to target playable.
    //! \param playable The playable to apply aura's effect(s).
    void Apply(Playable* playable) override;

    //! Disapplies aura's effect(s) to target playable.
    //! \param playable The playable to disapply aura's effect(s).
    void Disapply(Playable* playable) override;

 private:
    //! Constructs switching aura with given \p prototype, \p owner.
    //! \param prototype An enrage effect for prototype.
    //! \param owner An owner of adaptive effect.
    SummoningPortalAura(const SummoningPortalAura& prototype, Playable& owner);

    //! Applies this aura to all entities.
    void AddAll();

    //! Removes this aura from all entities.
    void RemoveAll();

    //! Calculates the cost.
    //! \param playable The playable to calculate cost.
    void CalculateCost(Playable* playable) const;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_SUMMONING_PORTAL_AURA_HPP
