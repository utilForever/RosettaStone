// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Games/TriggerManager.hpp>

namespace RosettaStone
{
void TriggerManager::OnHealTrigger(Player* player, Entity* sender)
{
    if (healTrigger != nullptr)
    {
        healTrigger(player, sender);
    }
}

void TriggerManager::OnStartTurnTrigger(Player* player, Entity* sender)
{
    if (startTurnTrigger != nullptr)
    {
        startTurnTrigger(player, sender);
    }
}
}  // namespace RosettaStone
