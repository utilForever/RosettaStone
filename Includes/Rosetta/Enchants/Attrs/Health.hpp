// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_HEALTH_HPP
#define ROSETTASTONE_HEALTH_HPP

#include <Rosetta/Enchants/Attrs/SelfContainedIntAttr.hpp>

namespace RosettaStone
{
class Health : public SelfContainedIntAttr<Health, Entity>
{
 public:
    static IEffect* Effect(EffectOperator effectOp, int value)
    {
        return SelfContainedIntAttr::Effect(effectOp, value);
    }

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
    int GetValue(Entity* entity) override
    {
        const auto character = dynamic_cast<Character*>(entity);
        return character->GetHealth();
    }

    void SetValue(Entity* entity, int value) override
    {
        auto character = dynamic_cast<Character*>(entity);
        character->SetHealth(value);
    }

    int GetAuraValue(AuraEffects* auraEffects) override
    {
        return auraEffects->GetHealth();
    }

    void SetAuraValue(AuraEffects* auraEffects, int value) override
    {
        auraEffects->SetHealth(value);
    }
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_HEALTH_HPP
