// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_EFFECTS_HPP
#define ROSETTASTONE_EFFECTS_HPP

#include <Rosetta/Enchants/Effect.hpp>

namespace RosettaStone
{
//!
//! \brief Effects class.
//!
//! This class lists specific effects such as Taunt, Poisonous and Stealth.
//!
class Effects
{
 public:
    //! Creates effect that increases attack by \p n.
    static Effect AttackN(int n)
    {
        return Effect(GameTag::ATK, EffectOperator::ADD, n);
    }

    //! Creates effect that increases health by \p n.
    static Effect HealthN(int n)
    {
        return Effect(GameTag::HEALTH, EffectOperator::ADD, n);
    }

    //! A minion ability which forces the opposing player to direct any melee
    //! attacks toward enemy targets with this ability.
    inline static Effect Taunt = Effect(GameTag::TAUNT, EffectOperator::SET, 1);

    //! A minion ability that causes any minion damaged by them to be destroyed.
    inline static Effect Poisonous =
        Effect(GameTag::POISONOUS, EffectOperator::SET, 1);

    //! An ability which causes a minion to ignore the next damage it receives.
    inline static Effect DivineShield =
        Effect(GameTag::DIVINE_SHIELD, EffectOperator::SET, 1);

    //! An ability which allows a character to attack twice per turn.
    inline static Effect Windfury =
        Effect(GameTag::WINDFURY, EffectOperator::SET, 1);

    //! An ability allowing a minion to attack the same turn it is summoned or
    //! brought under a new player's control.
    inline static Effect Charge =
        Effect(GameTag::CHARGE, EffectOperator::SET, 1);

    //! A minion ability which prevents that minion from being the target of
    //! enemy attacks, spells and effects until they attack.
    inline static Effect Stealth =
        Effect(GameTag::STEALTH, EffectOperator::SET, 1);
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_EFFECTS_HPP
