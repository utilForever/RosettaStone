// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/Actions/Summon.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SummonTask.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>

using namespace RosettaStone::PlayMode::SimpleTasks;

namespace RosettaStone::PlayMode::Generic
{
void Summon(Minion* minion, int fieldPos, Entity* summoner)
{
    Game* game = minion->game;

    minion->player->GetFieldZone()->Add(minion, fieldPos);

    game->UpdateAura();

    game->summonedMinions.emplace_back(minion);

    // Process after summon trigger
    game->taskQueue.StartEvent();
    auto tempEventData = std::move(game->currentEventData);
    if (summoner != nullptr)
    {
        game->currentEventData = std::make_unique<EventMetaData>(
            dynamic_cast<Playable*>(summoner), minion);
    }
    game->triggerManager.OnAfterSummonTrigger(minion);
    game->ProcessTasks();
    game->currentEventData.reset();
    game->currentEventData = std::move(tempEventData);
    game->taskQueue.EndEvent();
}

void SummonReborn(Minion* minion)
{
    int alternateCount = 0;
    int zonePos = SummonTask::GetPosition(minion, SummonSide::DEATHRATTLE, nullptr,
                                          alternateCount);
    if (zonePos > minion->player->GetFieldZone()->GetCount())
    {
        zonePos = minion->player->GetFieldZone()->GetCount();
    }

    const auto copy = dynamic_cast<Minion*>(
        Entity::GetFromCard(minion->player, minion->card, minion->GetGameTags(),
                            minion->player->GetFieldZone()));

    // When the minion is first destroyed, it loses the visual effect but
    // retains the keyword. The keyword is then functionally meaningless.
    copy->SetDamage(copy->GetHealth() - 1);
    copy->SetGameTag(GameTag::REBORN, 0);

    Summon(copy, zonePos, minion);
}
}  // namespace RosettaStone::PlayMode::Generic