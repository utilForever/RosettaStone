// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Summon.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Zones/FieldZone.hpp>

namespace RosettaStone::Generic
{
void Summon(Player* player, Minion* minion, int fieldPos)
{
    player->GetFieldZone()->Add(minion, fieldPos);

    player->game->UpdateAura();

    player->game->summonedMinions.emplace_back(minion);

    // Process after summon trigger
    player->game->taskQueue.StartEvent();
    player->game->triggerManager.OnAfterSummonTrigger(player, minion);
    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();
}
}  // namespace RosettaStone::Generic