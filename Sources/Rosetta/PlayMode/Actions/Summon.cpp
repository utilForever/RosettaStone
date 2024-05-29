// This code is based on Sabberstone project.
// Copyright (c) 2017-2021 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/Summon.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SummonTask.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>

using namespace RosettaStone::PlayMode::SimpleTasks;

namespace RosettaStone::PlayMode::Generic
{
void Summon(Minion* minion, int fieldPos, Entity* summoner)
{
    Game* game = minion->game;

    // Add summoned minion to field zone
    minion->player->GetFieldZone()->Add(minion, fieldPos);

    // Check 'Watch Post'
    if (minion->card->IsWatchPost())
    {
        const int val = minion->player->GetNumWatchPostSummonedThisGame();
        minion->player->SetNumWatchPostSummonedThisGame(val + 1);
    }

    // Check card has dormant
    if (minion->HasDormant())
    {
        minion->SetGameTag(GameTag::UNTOUCHABLE, 1);
    }

    // Set it is summoned minion
    minion->SetSummoned(true);

    game->UpdateAura();

    game->summonedMinions.emplace_back(minion);

    // Process after summon trigger
    game->taskQueue.StartEvent();
    auto tempEventData = std::move(game->currentEventData);
    if (summoner)
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
    int zonePos = SummonTask::GetPosition(minion, SummonSide::DEATHRATTLE,
                                          nullptr, alternateCount);
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

void SummonAppendages(
    const std::vector<std::tuple<std::string, SummonSide>>& appendages,
    Entity* summoner)
{
    for (auto& appendage : appendages)
    {
        const auto appendageMinion = dynamic_cast<Minion*>(Entity::GetFromCard(
            summoner->player, Cards::FindCardByID(std::get<0>(appendage)),
            std::nullopt, summoner->player->GetFieldZone()));
        int alternateCount = 0;
        const int summonPos = SummonTask::GetPosition(
            summoner, std::get<1>(appendage), appendageMinion, alternateCount);

        Summon(appendageMinion, summonPos, summoner);
    }
}
}  // namespace RosettaStone::PlayMode::Generic