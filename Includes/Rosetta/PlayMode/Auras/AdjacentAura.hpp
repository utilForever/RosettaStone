// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_ADJACENT_AURA_HPP
#define ROSETTASTONE_PLAYMODE_ADJACENT_AURA_HPP

#include <Rosetta/PlayMode/Auras/Aura.hpp>

#include <memory>

namespace RosettaStone::PlayMode
{
class FieldZone;
class Minion;

//!
//! \brief AdjacentAura class.
//!
//! This class is an aura for adjacent type. Note that some auras only affect
//! adjacent minions, e.g. Dire Wolf Alpha and Flametongue Totem.
//!
class AdjacentAura : public IAura
{
 public:
    //! Constructs adjacent aura with given \p enchantmentID.
    //! \param enchantmentID The enchantment card ID.
    explicit AdjacentAura(std::string&& enchantmentID);

    //! Create new Aura instance to the owner's game.
    //! \param owner An owner of enrage effect.
    //! \param cloning The flag to indicate that it is cloned.
    void Activate(Playable* owner,
                  [[maybe_unused]] bool cloning = false) override;

    //! Updates this effect to apply the effect to recently modified entities.
    void Update() override;

    //! Removes this effect from the game to stop affecting entities.
    void Remove() override;

    //! Clones aura effect to \p clone.
    //! \param clone The entity to clone aura effect.
    void Clone(Playable* clone) override;

    //! Sets the flag whether the field zone is changed.
    //! \param isFieldChanged The flag whether the field zone is changed.
    void SetIsFieldChanged(bool isFieldChanged);

 private:
    //! Constructs adjacent aura with given \p prototype, \p owner
    //! and \p cloning.
    //! \param prototype An adjacent aura for prototype.
    //! \param owner An owner of adaptive effect.
    //! \param cloning The flag to indicate that it is cloned.
    AdjacentAura(const AdjacentAura& prototype, Minion& owner, bool cloning);

    //! Applies aura's effect(s) to target minion.
    //! \param minion The minion to apply aura's effect(s).
    void Apply(Minion* minion) const;

    //! Disapplies aura's effect(s) to target minion.
    //! \param minion The minion to disapply aura's effect(s).
    void Disapply(Minion* minion) const;

    Minion* m_owner = nullptr;
    Card* m_enchantmentCard = nullptr;
    std::vector<std::shared_ptr<IEffect>> m_effects;

    FieldZone* m_fieldZone = nullptr;
    Minion* m_left = nullptr;
    Minion* m_right = nullptr;

    bool m_isFieldChanged = false;
    bool m_toBeRemoved = false;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_ADJACENT_AURA_HPP
