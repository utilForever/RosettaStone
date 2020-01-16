// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Summon.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Zones/FieldZone.hpp>

namespace RosettaStone::Generic
{
void Summon(Minion* minion, int fieldPos, Entity* summoner)
{
    Game* game = minion->game;

    minion->player->GetFieldZone()->Add(minion, fieldPos);

    game->UpdateAura();

    game->summonedMinions.emplace_back(minion);

    // Process after summon trigger
    game->taskQueue.StartEvent();
    EventMetaData* temp = game->currentEventData;
    if (summoner != nullptr)
    {
        game->currentEventData =
            new EventMetaData(dynamic_cast<Playable*>(summoner), minion);
    }
    game->triggerManager.OnAfterSummonTrigger(minion);
    game->ProcessTasks();
    delete game->currentEventData;
    game->currentEventData = temp;
    game->taskQueue.EndEvent();
}
}  // namespace RosettaStone::Generic