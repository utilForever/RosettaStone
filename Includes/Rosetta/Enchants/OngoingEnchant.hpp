// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_ONGOING_ENCHANT_HPP
#define ROSETTASTONE_ONGOING_ENCHANT_HPP

#include <Rosetta/Enchants/Enchant.hpp>
#include <Rosetta/Auras/IAura.hpp>

namespace RosettaStone
{
//!
//! \brief OngoingEnchant class.
//!
//! This class is implementation of a kind of enchantment that its effect
//! gradually grows due to a trigger. OngoingEnchant is narrowly used when the
//! source of the trigger and the target of the Enchantment is identical.
//! (e.g. Mana Wyrm)
//!
class OngoingEnchant : public Enchant, public IAura
{
 public:
    //! Constructs ongoing enchant with given \p effects.
    //! \param effects A list of effect.
    OngoingEnchant(std::vector<IEffect*> effects);

    //! Activates enchant to \p entity.
    //! \param entity An entity to which enchant is activated.
    //! \param num1 The number of GameTag::TAG_SCRIPT_DATA_NUM_1.
    //! \param num2 The number of GameTag::TAG_SCRIPT_DATA_NUM_2.
    void ActivateTo(Entity* entity, int num1 = 0, int num2 = -1) override;

    //! Clones aura effect to \p clone.
    //! \param clone The entity to clone ongoing enchant.
    void Clone(Playable* clone) override;

 private:
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ONGOING_ENCHANT_HPP
