// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_HEALTH_HPP
#define ROSETTASTONE_HEALTH_HPP

#include <Rosetta/Enchants/Attrs/SelfContainedIntAttr.hpp>

#include <memory>

namespace RosettaStone
{
//!
//! \brief Health class.
//!
//! This class is an attribute for health and inherits from SelfContainedIntAttr
//! class. It uses CRTP(Curiously Recurring Template Pattern) technique.
//!
class Health : public SelfContainedIntAttr<Health, Entity>
{
 public:
    //! Generates new effect for health attribute.
    //! \param effectOp The effect operator of the effect.
    //! \param value The value of the effect.
    //! \return The effect that is dynamically allocated.
    static std::unique_ptr<IEffect> Effect(EffectOperator effectOp, int value)
    {
        return SelfContainedIntAttr::Effect(effectOp, value);
    }

    //! Applies the effect that affects the attribute.
    //! \param entity The entity to apply the effect.
    //! \param effectOp The effect operator to change the attribute.
    //! \param value The value to change the attribute.
    void Apply(Entity* entity, EffectOperator effectOp, int value) override
    {
        if (effectOp == EffectOperator::SET)
        {
            if (auto hero = dynamic_cast<Hero*>(entity); hero)
            {
                const int heroHealth = hero->GetMaxHealth();

                if (heroHealth > value)
                {
                    hero->SetDamage(heroHealth - value);
                }
                else
                {
                    hero->SetHealth(value);
                }

                return;
            }

            if (auto minion = dynamic_cast<Minion*>(entity); minion)
            {
                minion->SetHealth(value);
                return;
            }
        }

        SelfContainedIntAttr::Apply(entity, effectOp, value);
    }

    //! Removes the aura that affects the attribute.
    //! \param entity The entity to remove the aura.
    //! \param effectOp The effect operator to change the attribute.
    //! \param value The value to change the attribute.
    void RemoveAura(Entity* entity, EffectOperator effectOp, int value) override
    {
        SelfContainedIntAttr::RemoveAura(entity, effectOp, value);

        if (effectOp == EffectOperator::ADD)
        {
            auto character = dynamic_cast<Character*>(entity);
            character->SetDamage(character->GetDamage() - value);
        }
    }

 protected:
    //! Returns the value of the attribute of the entity.
    //! \param entity The entity to get the value of the attribute.
    //! \return The value of the attribute of the entity.
    int GetValue(Entity* entity) override
    {
        const auto character = dynamic_cast<Character*>(entity);
        return character->GetHealth();
    }

    //! Sets the value of the attribute of the entity.
    //! \param entity The entity to set the value of the attribute.
    //! \param value The value of the attribute of the entity.
    void SetValue(Entity* entity, int value) override
    {
        auto character = dynamic_cast<Character*>(entity);
        character->SetHealth(value);
    }

    //! Returns the value the attribute that is affected by the aura effect.
    //! \param auraEffects The aura effects that affects the attribute.
    //! \return The value the attribute that is affected by the aura effect.
    int GetAuraValue(AuraEffects* auraEffects) override
    {
        return auraEffects->GetHealth();
    }

    //! Sets the value the attribute that is affected by the aura effect.
    //! \param auraEffects The aura effects that affects the attribute.
    //! \param value The value the attribute that is affected by the aura effect.
    void SetAuraValue(AuraEffects* auraEffects, int value) override
    {
        auraEffects->SetHealth(value);
    }
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_HEALTH_HPP
