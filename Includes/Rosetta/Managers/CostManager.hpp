// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_COST_MANAGER_HPP
#define ROSETTASTONE_COST_MANAGER_HPP

#include <Rosetta/Auras/AdaptiveCostEffect.hpp>

#include <optional>

namespace RosettaStone
{
//!
//! \brief CostManager class.
//!
//! This class manages the cost of the card.
//!
class CostManager
{
 public:
    //! Default constructor.
    CostManager() = default;

    int GetCost(int cost);

    void AddCostAura(EffectOperator effectOp, int value);

    void RemoveCostAura(EffectOperator effectOp, int value);

    void ActivateAdaptiveEffect(AdaptiveCostEffect* adaptiveCostEffect);

    void UpdateAdaptiveEffect(int value = -1);

    void DeactivateAdaptiveEffect();

    void AddCostEnchantment(EffectOperator effectOp, int value);

 private:
    int GetCostInternal(int cost);

    std::vector<std::pair<EffectOperator, int>> m_costEffects;
    std::vector<std::pair<EffectOperator, int>> m_costEnchantments;

    std::optional<int> m_cachedValue = std::nullopt;
    bool m_toBeUpdated = true;
    AdaptiveCostEffect* m_adaptiveCostEffect = nullptr;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_COST_MANAGER_HPP
