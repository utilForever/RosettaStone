// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/PlayMode/Managers/TriggerManager.hpp>

namespace RosettaStone::PlayMode
{
void TriggerManager::OnStartGameTrigger()
{
    startGameTrigger(nullptr);
}

void TriggerManager::OnStartTurnTrigger(Entity* sender)
{
    startTurnTrigger(sender);
}

void TriggerManager::OnEndTurnTrigger(Entity* sender)
{
    endTurnTrigger(sender);
}

void TriggerManager::OnAddCardTrigger(Entity* sender)
{
    addCardTrigger(sender);
}

void TriggerManager::OnDrawCardTrigger(Entity* sender)
{
    drawCardTrigger(sender);
}

void TriggerManager::OnAfterDrawCardTrigger(Entity* sender)
{
    afterDrawCardTrigger(sender);
}

void TriggerManager::OnPlayCardTrigger(Entity* sender)
{
    playCardTrigger(sender);
}

void TriggerManager::OnAfterPlayCardTrigger(Entity* sender)
{
    afterPlayCardTrigger(sender);
}

void TriggerManager::OnPlayMinionTrigger(Entity* sender)
{
    playMinionTrigger(sender);
}

void TriggerManager::OnAfterPlayMinionTrigger(Entity* sender)
{
    afterPlayMinionTrigger(sender);
}

void TriggerManager::OnCastSpellTrigger(Entity* sender)
{
    castSpellTrigger(sender);
}

void TriggerManager::OnAfterCastTrigger(Entity* sender)
{
    afterCastTrigger(sender);
}

void TriggerManager::OnSecretRevealedTrigger(Entity* sender)
{
    secretRevealedTrigger(sender);
}

void TriggerManager::OnZoneTrigger(Entity* sender)
{
    zoneTrigger(sender);
}

void TriggerManager::OnGiveHealTrigger(Entity* sender)
{
    giveHealTrigger(sender);
}

void TriggerManager::OnTakeHealTrigger(Entity* sender)
{
    takeHealTrigger(sender);
}

void TriggerManager::OnAttackTrigger(Entity* sender)
{
    attackTrigger(sender);
}

void TriggerManager::OnAfterAttackTrigger(Entity* sender)
{
    afterAttackTrigger(sender);
}

void TriggerManager::OnSummonTrigger(Entity* sender)
{
    summonTrigger(sender);
}

void TriggerManager::OnAfterSummonTrigger(Entity* sender)
{
    afterSummonTrigger(sender);
}

void TriggerManager::OnDealDamageTrigger(Entity* sender)
{
    dealDamageTrigger(sender);
}

void TriggerManager::OnTakeDamageTrigger(Entity* sender)
{
    takeDamageTrigger(sender);
}

void TriggerManager::OnTargetTrigger(Entity* sender)
{
    targetTrigger(sender);
}

void TriggerManager::OnDiscardTrigger(Entity* sender)
{
    discardTrigger(sender);
}

void TriggerManager::OnDeathTrigger(Entity* sender)
{
    deathTrigger(sender);
}

void TriggerManager::OnInspireTrigger(Entity* sender)
{
    inspireTrigger(sender);
}

void TriggerManager::OnEquipWeaponTrigger(Entity* sender)
{
    equipWeaponTrigger(sender);
}

void TriggerManager::OnShuffleIntoDeckTrigger(Entity* sender)
{
    shuffleIntoDeckTrigger(sender);
}

void TriggerManager::OnManaCrystalTrigger(Entity* sender)
{
    manaCrystalTrigger(sender);
}
}  // namespace RosettaStone::PlayMode
