// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_COST_MANAGER_HPP
#define ROSETTASTONE_PLAYMODE_COST_MANAGER_HPP

#include <Rosetta/PlayMode/Auras/AdaptiveCostEffect.hpp>

#include <optional>

namespace RosettaStone::PlayMode
{
//!
//! \brief CostManager class.
//!
//! This class manages the cost of the card. It is affected by cost aura,
//! adaptive effect and enchantment.
//!
class CostManager
{
 public:
    //! Default constructor.
    CostManager() = default;

    //! Calculates the value of the cost by considering the factors
    //! such as cost aura, adaptive effect and enchantment.
    //! \return cost The original value of the cost.
    //! \return The final value of the cost.
    int GetCost(int cost);

    //! Queues the update.
    void QueueUpdate();

    //! Applies older entity's cost enchantments to the new one.
    //! \param newCardCost The cost of new card.
    //! \return The applied value of the cost.
    int EntityChanged(int newCardCost);

    //! Adds the aura that affects the cost.
    //! \param effectOp The effect operator to affect the cost value.
    //! \param value The value to affect the cost value.
    void AddCostAura(EffectOperator effectOp, int value);

    //! Removes the aura that affects the cost.
    //! \param effectOp The effect operator to affect the cost value.
    //! \param value The value to affect the cost value.
    void RemoveCostAura(EffectOperator effectOp, int value);

    //! Activates the adaptive effect that affects the cost.
    //! \param effect The adaptive cost effect to change the cost value.
    void ActivateAdaptiveEffect(AdaptiveCostEffect* effect);

    //! Updates the adaptive effect that affects the cost.
    //! \param value The value that affects the cost value to update.
    void UpdateAdaptiveEffect(int value = -1);

    //! Deactivates the adaptive effect that affects the cost.
    void DeactivateAdaptiveEffect();

    //! Adds the enchantment that affects the cost.
    //! \param effectOp The effect operator to affect the cost value.
    //! \param value The value to affect the cost value.
    void AddCostEnchantment(EffectOperator effectOp, int value);

 private:
    //! Internal method of GetCost().
    //! \return cost The original value of the cost.
    //! \return The final value of the cost.
    int GetCostInternal(int cost);

    std::vector<std::pair<EffectOperator, int>> m_costEffects;
    std::vector<std::pair<EffectOperator, int>> m_costEnchantments;

    int m_cachedValue = 0;
    bool m_toBeUpdated = true;
    AdaptiveCostEffect* m_adaptiveCostEffect = nullptr;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_COST_MANAGER_HPP
