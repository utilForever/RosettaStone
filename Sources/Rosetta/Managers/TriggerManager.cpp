// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Managers/TriggerManager.hpp>

namespace RosettaStone
{
void TriggerManager::OnStartTurnTrigger(Entity* sender) const
{
    if (startTurnTrigger != nullptr)
    {
        startTurnTrigger(sender);
    }
}

void TriggerManager::OnEndTurnTrigger(Entity* sender) const
{
    if (endTurnTrigger != nullptr)
    {
        endTurnTrigger(sender);
    }
}

void TriggerManager::OnPlayCardTrigger(Entity* sender) const
{
    if (playCardTrigger != nullptr)
    {
        playCardTrigger(sender);
    }
}

void TriggerManager::OnPlayMinionTrigger(Entity* sender) const
{
    if (playMinionTrigger != nullptr)
    {
        playMinionTrigger(sender);
    }
}

void TriggerManager::OnAfterPlayMinionTrigger(Entity* sender) const
{
    if (afterPlayMinionTrigger != nullptr)
    {
        afterPlayMinionTrigger(sender);
    }
}

void TriggerManager::OnCastSpellTrigger(Entity* sender) const
{
    if (castSpellTrigger != nullptr)
    {
        castSpellTrigger(sender);
    }
}

void TriggerManager::OnAfterCastTrigger(Entity* sender) const
{
    if (afterCastTrigger != nullptr)
    {
        afterCastTrigger(sender);
    }
}

void TriggerManager::OnSecretRevealedTrigger(Entity* sender) const
{
    if (secretRevealedTrigger != nullptr)
    {
        secretRevealedTrigger(sender);
    }
}

void TriggerManager::OnGiveHealTrigger(Entity* sender) const
{
    if (giveHealTrigger != nullptr)
    {
        giveHealTrigger(sender);
    }
}

void TriggerManager::OnTakeHealTrigger(Entity* sender) const
{
    if (takeHealTrigger != nullptr)
    {
        takeHealTrigger(sender);
    }
}

void TriggerManager::OnAttackTrigger(Entity* sender) const
{
    if (attackTrigger != nullptr)
    {
        attackTrigger(sender);
    }
}

void TriggerManager::OnSummonTrigger(Entity* sender) const
{
    if (summonTrigger != nullptr)
    {
        summonTrigger(sender);
    }
}

void TriggerManager::OnAfterSummonTrigger(Entity* sender) const
{
    if (afterSummonTrigger != nullptr)
    {
        afterSummonTrigger(sender);
    }
}

void TriggerManager::OnDealDamageTrigger(Entity* sender) const
{
    if (dealDamageTrigger != nullptr)
    {
        dealDamageTrigger(sender);
    }
}

void TriggerManager::OnTakeDamageTrigger(Entity* sender) const
{
    if (takeDamageTrigger != nullptr)
    {
        takeDamageTrigger(sender);
    }
}

void TriggerManager::OnTargetTrigger(Entity* sender) const
{
    if (targetTrigger != nullptr)
    {
        targetTrigger(sender);
    }
}

void TriggerManager::OnDeathTrigger(Entity* sender) const
{
    if (deathTrigger != nullptr)
    {
        deathTrigger(sender);
    }
}

void TriggerManager::OnUseHeroPowerTrigger(Entity* sender) const
{
    if (useHeroPowerTrigger != nullptr)
    {
        useHeroPowerTrigger(sender);
    }
}
}  // namespace RosettaStone
