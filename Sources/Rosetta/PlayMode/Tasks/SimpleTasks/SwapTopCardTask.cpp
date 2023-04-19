// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Tasks/SimpleTasks/SwapTopCardTask.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
TaskStatus SwapTopCardTask::Impl(Player* player)
{
    DeckZone* curDeck = player->GetDeckZone();
    DeckZone* opDeck = player->opponent->GetDeckZone();

    Playable* curTopCard = curDeck->Remove(curDeck->GetTopCard());
    Playable* opTopCard = opDeck->Remove(opDeck->GetTopCard());

    if (curTopCard)
    {
        curTopCard->player = player->opponent;
        opDeck->Add(curTopCard);
    }

    if (opTopCard)
    {
        opTopCard->player = player;
        curDeck->Add(opTopCard);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> SwapTopCardTask::CloneImpl()
{
    return std::make_unique<SwapTopCardTask>();
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
