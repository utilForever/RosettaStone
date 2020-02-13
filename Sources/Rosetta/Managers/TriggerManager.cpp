// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Managers/TriggerManager.hpp>

namespace RosettaStone
{
void TriggerManager::OnStartTurnTrigger(Entity* sender) const
{
    startTurnTrigger(sender);
}

void TriggerManager::OnEndTurnTrigger(Entity* sender) const
{
    endTurnTrigger(sender);
}

void TriggerManager::OnPlayCardTrigger(Entity* sender) const
{
    playCardTrigger(sender);
}

void TriggerManager::OnPlayMinionTrigger(Entity* sender) const
{
    playMinionTrigger(sender);
}

void TriggerManager::OnAfterPlayMinionTrigger(Entity* sender) const
{
    afterPlayMinionTrigger(sender);
}

void TriggerManager::OnCastSpellTrigger(Entity* sender) const
{
    castSpellTrigger(sender);
}

void TriggerManager::OnAfterCastTrigger(Entity* sender) const
{
    afterCastTrigger(sender);
}

void TriggerManager::OnSecretRevealedTrigger(Entity* sender) const
{
    secretRevealedTrigger(sender);
}

void TriggerManager::OnGiveHealTrigger(Entity* sender) const
{
    giveHealTrigger(sender);
}

void TriggerManager::OnTakeHealTrigger(Entity* sender) const
{
    takeHealTrigger(sender);
}

void TriggerManager::OnAttackTrigger(Entity* sender) const
{
    attackTrigger(sender);
}

void TriggerManager::OnSummonTrigger(Entity* sender) const
{
    summonTrigger(sender);
}

void TriggerManager::OnAfterSummonTrigger(Entity* sender) const
{
    afterSummonTrigger(sender);
}

void TriggerManager::OnDealDamageTrigger(Entity* sender) const
{
    dealDamageTrigger(sender);
}

void TriggerManager::OnTakeDamageTrigger(Entity* sender) const
{
    takeDamageTrigger(sender);
}

void TriggerManager::OnTargetTrigger(Entity* sender) const
{
    targetTrigger(sender);
}

void TriggerManager::OnDeathTrigger(Entity* sender) const
{
    deathTrigger(sender);
}

void TriggerManager::OnUseHeroPowerTrigger(Entity* sender) const
{
    useHeroPowerTrigger(sender);
}
}  // namespace RosettaStone
