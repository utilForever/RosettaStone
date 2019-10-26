// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_COST_HPP
#define ROSETTASTONE_COST_HPP

#include <Rosetta/Enchants/Attrs/SelfContainedIntAttr.hpp>

namespace RosettaStone
{
class Cost : public SelfContainedIntAttr<Cost, Entity>
{
 public:
    static IEffect* Effect(EffectOperator effectOp, int value)
    {
        return SelfContainedIntAttr::Effect(effectOp, value);
    }

    void Apply(Entity* entity, EffectOperator effectOp, int value) override
    {
        SelfContainedIntAttr::Apply(entity, effectOp, value);

        const auto playable = dynamic_cast<Playable*>(entity);

        if (auto* costManager = playable->costManager; costManager)
        {
            costManager->AddCostEnchantment(effectOp, value);
        }
    }

    void ApplyAura(Entity* entity, EffectOperator effectOp, int value) override
    {
        const auto playable = dynamic_cast<Playable*>(entity);

        CostManager* costManager = playable->costManager;
        if (costManager == nullptr)
        {
            costManager = new CostManager();
            playable->costManager = costManager;
        }

        costManager->AddCostAura(effectOp, value);
    }

    void RemoveAura(Entity* entity, EffectOperator effectOp, int value) override
    {
        const auto playable = dynamic_cast<Playable*>(entity);

        if (auto* costManager = playable->costManager; costManager)
        {
            costManager->RemoveCostAura(effectOp, value);
        }
    }

 protected:
    int GetValue(Entity* entity) override
    {
        const auto playable = dynamic_cast<Playable*>(entity);
        return playable->GetCost();
    }

    void SetValue(Entity* entity, int value) override
    {
        auto playable = dynamic_cast<Playable*>(entity);
        playable->SetCost(value);
    }

    int GetAuraValue([[maybe_unused]] AuraEffects* auraEffects) override
    {
        throw std::logic_error("Cost::GetAuraValue() - Not implemented!");
    }

    void SetAuraValue([[maybe_unused]] AuraEffects* auraEffects,
                      [[maybe_unused]] int value) override
    {
        throw std::logic_error("Cost::GetAuraValue() - Not implemented!");
    }
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_SELF_CONTAINED_INT_ATTR_HPP
