// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_SWITCHING_AURA_HPP
#define ROSETTASTONE_PLAYMODE_SWITCHING_AURA_HPP

#include <Rosetta/PlayMode/Auras/Aura.hpp>
#include <Rosetta/PlayMode/Triggers/Trigger.hpp>

#include <memory>

namespace RosettaStone::PlayMode
{
//!
//! \brief SwitchingAura class.
//!
//! This class is an aura that can switch between on and off.
//! e.g. Pint-Sized Summoner and Kalecgos.
//!
class SwitchingAura : public Aura
{
 public:
    //! Constructs adjacent aura with given \p type, \p offCondition,
    //! \p offTrigger and \p effects.
    //! \param type The type of aura.
    //! \param activateCondition The condition to activate an aura.
    //! \param offTrigger The trigger to switch off.
    //! \param effects A list of effect.
    SwitchingAura(AuraType type, SelfCondition activateCondition,
                  TriggerType offTrigger,
                  std::vector<std::shared_ptr<IEffect>> effects);

    //! Constructs adjacent aura with given \p type, \p offCondition,
    //! \p offTrigger and \p enchantmentID.
    //! \param type The type of aura.
    //! \param activateCondition The condition to activate an aura.
    //! \param offTrigger The trigger to switch off.
    //! \param enchantmentID The enchantment card ID.
    SwitchingAura(AuraType type, SelfCondition activateCondition,
                  TriggerType offTrigger, std::string&& enchantmentID);

    //! Create new Aura instance to the owner's game.
    //! \param owner An owner of enrage effect.
    //! \param cloning The flag to indicate that it is cloned.
    void Activate(Playable* owner, bool cloning = false) override;

    //! Removes this effect from the game to stop affecting entities.
    void Remove() override;

 private:
    //! Constructs switching aura with given \p prototype, \p owner.
    //! \param prototype An enrage effect for prototype.
    //! \param owner An owner of adaptive effect.
    SwitchingAura(const SwitchingAura& prototype, Playable& owner);

    //! Internal method of Remove().
    void RemoveInternal() override;

    SelfCondition m_activateCondition;
    TriggerType m_offTrigger;

    TriggerEventHandler m_onHandler;
    TriggerEventHandler m_offHandler;

    bool m_isRemoved = false;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_SWITCHING_AURA_HPP
