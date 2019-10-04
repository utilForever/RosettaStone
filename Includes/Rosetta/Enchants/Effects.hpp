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
    //! \param n A value indicating how much increases.
    //! \return A pointer to Effect.
    static Effect* AttackN(int n)
    {
        return new Effect(GameTag::ATK, EffectOperator::ADD, n);
    }

    //! Creates effect that increases health by \p n.
    //! \param n A value indicating how much increases.
    //! \return A pointer to Effect.
    static Effect* HealthN(int n)
    {
        return new Effect(GameTag::HEALTH, EffectOperator::ADD, n);
    }

    //! Creates effect that increases durability by \p n.
    //! \param n A value indicating how much increases.
    //! \return A pointer to Effect.
    static Effect* DurabilityN(int n)
    {
        return new Effect(GameTag::DURABILITY, EffectOperator::ADD, n);
    }

    //! Creates effect that increases spell power by \p n.
    //! \param n A value indicating how much increases.
    //! \return A pointer to Effect.
    static Effect* SpellPowerN(int n)
    {
        return new Effect(GameTag::SPELLPOWER, EffectOperator::ADD, n);
    }

    //! Creates effect that increases attack and health by \p n.
    //! \param n A value indicating how much increases.
    //! \return A pointer to Effect.
    static std::vector<Effect*> AttackHealthN(int n)
    {
        return { AttackN(n), HealthN(n) };
    }

    //! Creates effect that sets attack to \p n.
    //! \param n The value representing the value to set.
    //! \return A pointer to Effect.
    static Effect* SetAttack(int n)
    {
        return new Effect(GameTag::ATK, EffectOperator::SET, n);
    }

    //! Creates effect that sets max health to \p n.
    //! \param n The value representing the value to set.
    //! \return A pointer to Effect.
    static Effect* SetMaxHealth(int n)
    {
        return new Effect(GameTag::HEALTH, EffectOperator::SET, n);
    }

    //! Creates effect that sets attack and health to \p n.
    //! \param n The value representing the value to set.
    //! \return A pointer to Effect.
    static std::vector<Effect*> SetAttackHealth(int n)
    {
        return { SetAttack(n), SetMaxHealth(n) };
    }

    //! Creates effect that reduces cost by \p n.
    //! \param n A value indicating how much reduce.
    //! \return A pointer to Effect.
    static Effect* ReduceCost(int n)
    {
        return new Effect(GameTag::COST, EffectOperator::SUB, n);
    }

    //! A minion ability which forces the opposing player to direct any
    //! melee attacks toward enemy targets with this ability.
    inline static Effect* Taunt =
        new Effect(GameTag::TAUNT, EffectOperator::SET, 1);

    //! A minion ability that causes any minion damaged by them to be destroyed.
    inline static Effect* Poisonous =
        new Effect(GameTag::POISONOUS, EffectOperator::SET, 1);

    //! An ability which causes a minion to ignore the next damage it receives.
    inline static Effect* DivineShield =
        new Effect(GameTag::DIVINE_SHIELD, EffectOperator::SET, 1);

    //! An ability which allows a character to attack twice per turn.
    inline static Effect* Windfury =
        new Effect(GameTag::WINDFURY, EffectOperator::SET, 1);

    //! An ability allowing a minion to attack the same turn it is summoned or
    //! brought under a new player's control.
    inline static Effect* Charge =
        new Effect(GameTag::CHARGE, EffectOperator::SET, 1);

    //! A minion ability which prevents that minion from being the target of
    //! enemy attacks, spells and effects until they attack.
    inline static Effect* Stealth =
        new Effect(GameTag::STEALTH, EffectOperator::SET, 1);

    //! An ability that prevents characters from receiving any damage, and
    //! prevents the opponent from specifically targeting them with any type of
    //! action.
    inline static Effect* Immune =
        new Effect(GameTag::IMMUNE, EffectOperator::SET, 1);
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_EFFECTS_HPP
