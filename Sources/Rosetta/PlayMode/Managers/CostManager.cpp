// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/Common/Utils.hpp>
#include <Rosetta/PlayMode/Managers/CostManager.hpp>

#include <stdexcept>

namespace RosettaStone::PlayMode
{
int CostManager::GetCost(int cost)
{
    const int finalCost = m_toBeUpdated ? GetCostInternal(cost) : m_cachedValue;

    return finalCost > 0 ? finalCost : 0;
}

void CostManager::QueueUpdate()
{
    m_toBeUpdated = true;
}

int CostManager::EntityChanged(int newCardCost)
{
    for (const auto& enchantment : m_costEnchantments)
    {
        switch (enchantment.first)
        {
            case EffectOperator::ADD:
                newCardCost += enchantment.second;
                break;
            case EffectOperator::SUB:
                newCardCost -= enchantment.second;
                break;
            case EffectOperator::MUL:
                newCardCost *= enchantment.second;
                break;
            case EffectOperator::SET:
                newCardCost = enchantment.second;
                break;
        }
    }

    newCardCost = GetCostInternal(newCardCost);

    return newCardCost > 0 ? newCardCost : 0;
}

void CostManager::AddCostAura(EffectOperator effectOp, int value)
{
    m_costEffects.emplace_back(std::make_pair(effectOp, value));

    switch (effectOp)
    {
        case EffectOperator::ADD:
            m_cachedValue += value;
            break;
        case EffectOperator::SUB:
            m_cachedValue -= value;
            break;
        case EffectOperator::SET:
            m_cachedValue = value;
            break;
        default:
            throw std::invalid_argument(
                "CostManager::AddCostAura() - Invalid effect operator!");
    }
}

void CostManager::RemoveCostAura(EffectOperator effectOp, int value)
{
    EraseIf(m_costEffects, [=](std::pair<EffectOperator, int> effect) {
        return effectOp == effect.first && value == effect.second;
    });
    switch (effectOp)
    {
        case EffectOperator::ADD:
            m_cachedValue -= value;
            break;
        case EffectOperator::SUB:
            m_cachedValue += value;
            break;
        case EffectOperator::SET:
            m_toBeUpdated = true;
            break;
        default:
            throw std::invalid_argument(
                "CostManager::RemoveCostAura() - Invalid effect operator!");
    }
}

void CostManager::ActivateAdaptiveEffect(AdaptiveCostEffect* effect)
{
    m_adaptiveCostEffect = effect;
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

void CostManager::AddCostEnchantment(EffectOperator effectOp, int value)
{
    switch (effectOp)
    {
        case EffectOperator::ADD:
            m_cachedValue += value;
            break;
        case EffectOperator::SUB:
            m_cachedValue -= value;
            break;
        case EffectOperator::SET:
            m_toBeUpdated = true;
            break;
        default:
            throw std::invalid_argument(
                "CostManager::AddCostEnchantment() - Invalid effect operator!");
    }

    m_costEnchantments.emplace_back(std::make_pair(effectOp, value));
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
    if (m_adaptiveCostEffect)
    {
        cost = m_adaptiveCostEffect->Apply(cost);
    }

    m_cachedValue = cost;
    m_toBeUpdated = false;

    return cost;
}
}  // namespace RosettaStone::PlayMode
