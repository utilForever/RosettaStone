// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Managers/CostManager.hpp>

namespace RosettaStone
{
int CostManager::GetCost(int cost)
{
    const int finalCost =
        m_toBeUpdated ? GetCostInternal(cost) : m_cachedValue.value();

    return finalCost > 0 ? finalCost : 0;
}

void CostManager::ActivateAdaptiveEffect(AdaptiveCostEffect* adaptiveCostEffect)
{
    m_adaptiveCostEffect = adaptiveCostEffect;
}

void CostManager::UpdateAdaptiveEffect(int value)
{
    if (value > 0)
    {
        m_cachedValue = value;
    }
    else
    {
        m_toBeUpdated = true;
    }
}

void CostManager::DeactivateAdaptiveEffect()
{
    m_adaptiveCostEffect = nullptr;
}

int CostManager::GetCostInternal(int cost)
{
    // 1. Get cost with enchantments first (cost)
    // e.g. Emperor Thaurissan

    // 2. Apply cost aura effects next
    // e.g. Naga Sea Witch, Sorcerer's Apprentice
    for (const auto& effect : m_costEffects)
    {
        switch (effect.first)
        {
            case EffectOperator::ADD:
                cost += effect.second;
                break;
            case EffectOperator::SUB:
                cost -= effect.second;
                break;
            case EffectOperator::MUL:
                cost *= effect.second;
                break;
            case EffectOperator::SET:
                cost = effect.second;
                break;
        }
    }

    // 3. Lastly apply Adaptive Cost Effect (e.g. Giants)
    if (m_adaptiveCostEffect != nullptr)
    {
        cost = m_adaptiveCostEffect->Apply(cost);
    }

    m_cachedValue = cost;
    m_toBeUpdated = false;

    return cost;
}
}  // namespace RosettaStone
