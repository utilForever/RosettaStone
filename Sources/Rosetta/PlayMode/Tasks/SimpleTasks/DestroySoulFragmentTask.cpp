// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DestroySoulFragmentTask.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
TaskStatus DestroySoulFragmentTask::Impl(Player* player)
{
    for (const auto& deckCard : player->GetDeckZone()->GetAll())
    {
        if (deckCard->card->dbfID == 59723)
        {
            deckCard->player->GetDeckZone()->Remove(deckCard);
            deckCard->player->GetGraveyardZone()->Add(deckCard);
            break;
        }
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> DestroySoulFragmentTask::CloneImpl()
{
    return std::make_unique<DestroySoulFragmentTask>();
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
