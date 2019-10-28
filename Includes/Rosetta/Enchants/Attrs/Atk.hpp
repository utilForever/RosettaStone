// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_ATK_HPP
#define ROSETTASTONE_ATK_HPP

#include <Rosetta/Enchants/Attrs/SelfContainedIntAttr.hpp>

namespace RosettaStone
{
class Atk : public SelfContainedIntAttr<Atk, Entity>
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
            auto& effects = entity->game->oneTurnEffects;

            for (int i = static_cast<int>(effects.size()) - 1; i >= 0; --i)
            {
                Entity* ent = effects[i].first;
                IEffect* eff = effects[i].second;

                if (ent != entity ||
                    dynamic_cast<GenericEffect<Playable, Atk>*>(eff) == nullptr)
                {
                    continue;
                }

                effects.erase(effects.begin() + i);
            }
        }

        if (const auto character = dynamic_cast<Character*>(entity); character)
        {
            SelfContainedIntAttr::Apply(character, effectOp, value);
        }
        else
        {
            const auto effect =
                new RosettaStone::Effect(GameTag::ATK, effectOp, value);
            effect->ApplyTo(entity);
        }
    }

 protected:
    int GetValue(Entity* entity) override
    {
        const auto character = dynamic_cast<Character*>(entity);
        return character->GetAttack();
    }

    void SetValue(Entity* entity, int value) override
    {
        auto character = dynamic_cast<Character*>(entity);
        character->SetAttack(value);
    }

    int GetAuraValue(AuraEffects* auraEffects) override
    {
        return auraEffects->GetAttack();
    }

    void SetAuraValue(AuraEffects* auraEffects, int value) override
    {
        auraEffects->SetAttack(value);
    }
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ATK_HPP
