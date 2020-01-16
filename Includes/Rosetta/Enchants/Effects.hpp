// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_EFFECTS_HPP
#define ROSETTASTONE_EFFECTS_HPP

#include <Rosetta/Enchants/Attrs/Atk.hpp>
#include <Rosetta/Enchants/Attrs/Cost.hpp>
#include <Rosetta/Enchants/Attrs/Health.hpp>
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
    //! \return A dynamically allocated Effect instance.
    static IEffect* AttackN(int n)
    {
        return Atk::Effect(EffectOperator::ADD, n);
    }

    //! Creates effect that increases health by \p n.
    //! \param n A value indicating how much increases.
    //! \return A dynamically allocated Effect instance.
    static IEffect* HealthN(int n)
    {
        return Health::Effect(EffectOperator::ADD, n);
    }

    //! Creates effect that increases durability by \p n.
    //! \param n A value indicating how much increases.
    //! \return A dynamically allocated Effect instance.
    static IEffect* DurabilityN(int n)
    {
        return new Effect(GameTag::DURABILITY, EffectOperator::ADD, n);
    }

    //! Creates effect that increases spell power by \p n.
    //! \param n A value indicating how much increases.
    //! \return A dynamically allocated Effect instance.
    static IEffect* SpellPowerN(int n)
    {
        return new Effect(GameTag::SPELLPOWER, EffectOperator::ADD, n);
    }

    //! Creates effect that increases attack and health by \p n.
    //! \param n A value indicating how much increases.
    //! \return A dynamically allocated Effects instance.
    static std::vector<IEffect*> AttackHealthN(int n)
    {
        return { AttackN(n), HealthN(n) };
    }

    //! Creates effect that sets attack to \p n.
    //! \param n The value to set.
    //! \return A dynamically allocated Effect instance.
    static IEffect* SetAttack(int n)
    {
        return Atk::Effect(EffectOperator::SET, n);
    }

    //! Creates effect that sets max health to \p n.
    //! \param n The value to set.
    //! \return A dynamically allocated Effect instance.
    static IEffect* SetMaxHealth(int n)
    {
        return Health::Effect(EffectOperator::SET, n);
    }

    //! Creates effect that sets attack and health to \p n.
    //! \param n The value to set.
    //! \return A dynamically allocated Effects instance.
    static std::vector<IEffect*> SetAttackHealth(int n)
    {
        return { SetAttack(n), SetMaxHealth(n) };
    }

    //! Creates effect that adds cost by \p n.
    //! \param n A value indicating how much add.
    //! \return A dynamically allocated Effect instance.
    static IEffect* AddCost(int n)
    {
        return Cost::Effect(EffectOperator::ADD, n);
    }

    //! Creates effect that reduces cost by \p n.
    //! \param n A value indicating how much reduce.
    //! \return A dynamically allocated Effect instance.
    static IEffect* ReduceCost(int n)
    {
        return Cost::Effect(EffectOperator::SUB, n);
    }

    //! Creates effect that sets cost to \p n.
    //! \param n A value indicating how much set.
    //! \return A dynamically allocated Effect instance.
    static IEffect* SetCost(int n)
    {
        return Cost::Effect(EffectOperator::SET, n);
    }

    //! A minion ability which forces the opposing player to direct any
    //! melee attacks toward enemy targets with this ability.
    inline static IEffect* Taunt =
        new Effect(GameTag::TAUNT, EffectOperator::SET, 1);

    //! A minion ability that causes any minion damaged by them to be destroyed.
    inline static IEffect* Poisonous =
        new Effect(GameTag::POISONOUS, EffectOperator::SET, 1);

    //! An ability which causes a minion to ignore the next damage it receives.
    inline static IEffect* DivineShield =
        new Effect(GameTag::DIVINE_SHIELD, EffectOperator::SET, 1);

    //! An ability which allows a character to attack twice per turn.
    inline static IEffect* Windfury =
        new Effect(GameTag::WINDFURY, EffectOperator::SET, 1);

    //! An ability allowing a minion to attack the same turn it is summoned or
    //! brought under a new player's control.
    inline static IEffect* Charge =
        new Effect(GameTag::CHARGE, EffectOperator::SET, 1);

    //! A minion ability which prevents that minion from being the target of
    //! enemy attacks, spells and effects until they attack.
    inline static IEffect* Stealth =
        new Effect(GameTag::STEALTH, EffectOperator::SET, 1);

    //! An ability that prevents characters from receiving any damage, and
    //! prevents the opponent from specifically targeting them with any type of
    //! action.
    inline static IEffect* Immune =
        new Effect(GameTag::IMMUNE, EffectOperator::SET, 1);
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_EFFECTS_HPP
