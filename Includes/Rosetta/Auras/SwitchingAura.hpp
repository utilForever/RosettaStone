// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_SWITCHING_AURA_HPP
#define ROSETTASTONE_SWITCHING_AURA_HPP

#include <Rosetta/Auras/Aura.hpp>
#include <Rosetta/Enchants/Trigger.hpp>

#include <memory>

namespace RosettaStone
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
    //! Constructs adjacent aura with given \p type, \p initCondition,
    //! \p offTrigger and \p effects.
    //! \param type The type of aura.
    //! \param initCondition The condition to switch on.
    //! \param offTrigger The trigger to switch off.
    //! \param effects A list of effect.
    SwitchingAura(AuraType type, SelfCondition initCondition,
                  TriggerType offTrigger,
                  std::vector<std::shared_ptr<IEffect>> effects);

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
    SwitchingAura(SwitchingAura& prototype, Playable& owner);

    //! Internal method of Remove().
    void RemoveInternal() override;

    SelfCondition m_initCondition;
    TriggerType m_offTrigger;

    std::function<void(Entity*)> m_onHandler;
    std::function<void(Entity*)> m_offHandler;

    bool m_isRemoved = false;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_SWITCHING_AURA_HPP
