// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_ENRAGE_EFFECT_HPP
#define ROSETTASTONE_PLAYMODE_ENRAGE_EFFECT_HPP

#include <Rosetta/PlayMode/Auras/Aura.hpp>
#include <Rosetta/PlayMode/Models/Enchantment.hpp>

namespace RosettaStone::PlayMode
{
//!
//! \brief EnrageEffect class.
//!
//! Enrage is the informal name for a minion ability where the stated effect
//! becomes active only when the minion is damaged. If the minion regains
//! undamaged status, either through healing or a forced resetting of its
//! maximum Health, the Enrage effect will be canceled.
//!
class EnrageEffect : public Aura
{
 public:
    //! Constructs enrage effect with given \p type and \p enchantmentID.
    //! \param type The type of aura.
    //! \param enchantmentID The enchantment card ID.
    EnrageEffect(AuraType type, std::string&& enchantmentID);

    //! Create new Aura instance to the owner's game.
    //! \param owner An owner of enrage effect.
    //! \param cloning The flag to indicate that it is cloned.
    void Activate(Playable* owner,
                  [[maybe_unused]] bool cloning = false) override;

    //! Updates this effect to apply the effect to recently modified entities.
    void Update() override;

    //! Clones aura effect to \p clone.
    //! \param clone The entity to clone aura effect.
    void Clone(Playable* clone) override;

 private:
    //! Constructs enrage effect with given \p prototype and \p owner.
    //! \param prototype An enrage effect for prototype.
    //! \param owner An owner of adaptive effect.
    EnrageEffect(const EnrageEffect& prototype, Playable& owner);

    Enchantment* m_curInstance = nullptr;
    Playable* m_target = nullptr;
    bool m_enraged = false;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_ENRAGE_EFFECT_HPP
