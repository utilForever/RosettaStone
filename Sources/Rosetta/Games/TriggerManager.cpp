// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Games/TriggerManager.hpp>

namespace RosettaStone
{
void TriggerManager::OnStartTurnTrigger(Player* player, Entity* sender) const
{
    if (startTurnTrigger != nullptr)
    {
        startTurnTrigger(player, sender);
    }
}

void TriggerManager::OnEndTurnTrigger(Player* player, Entity* sender) const
{
    if (endTurnTrigger != nullptr)
    {
        endTurnTrigger(player, sender);
    }
}

void TriggerManager::OnPlayCardTrigger(Player* player, Entity* sender) const
{
    if (playCardTrigger != nullptr)
    {
        playCardTrigger(player, sender);
    }
}

void TriggerManager::OnCastSpellTrigger(Player* player, Entity* sender) const
{
    if (castSpellTrigger != nullptr)
    {
        castSpellTrigger(player, sender);
    }
}

void TriggerManager::OnAfterCastTrigger(Player* player, Entity* sender) const
{
    if (afterCastTrigger != nullptr)
    {
        afterCastTrigger(player, sender);
    }
}

void TriggerManager::OnHealTrigger(Player* player, Entity* sender) const
{
    if (healTrigger != nullptr)
    {
        healTrigger(player, sender);
    }
}

void TriggerManager::OnAttackTrigger(Player* player, Entity* sender) const
{
    if (attackTrigger != nullptr)
    {
        attackTrigger(player, sender);
    }
}

void TriggerManager::OnSummonTrigger(Player* player, Entity* sender) const
{
    if (summonTrigger != nullptr)
    {
        summonTrigger(player, sender);
    }
}

void TriggerManager::OnTakeDamageTrigger(Player* player, Entity* sender) const
{
    if (takeDamageTrigger != nullptr)
    {
        takeDamageTrigger(player, sender);
    }
}

void TriggerManager::OnTargetTrigger(Player* player, Entity* sender) const
{
    if (targetTrigger != nullptr)
    {
        targetTrigger(player, sender);
    }
}
}  // namespace RosettaStone
