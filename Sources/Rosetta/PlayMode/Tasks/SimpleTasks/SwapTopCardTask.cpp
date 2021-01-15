// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/Tasks/SimpleTasks/SwapTopCardTask.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
TaskStatus SwapTopCardTask::Impl(Player* player)
{
    DeckZone* deck = player->GetDeckZone();
    DeckZone* opDeck = player->opponent->GetDeckZone();

    Playable* topCard = deck->Remove(deck->GetTopCard());
    Playable* opTopCard = opDeck->Remove(opDeck->GetTopCard());

    if (opTopCard != nullptr)
    {
        opTopCard->player = player;
        deck->Add(opTopCard);
    }

    if (topCard != nullptr)
    {
        topCard->player = player->opponent;
        opDeck->Add(topCard);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> SwapTopCardTask::CloneImpl()
{
    return std::make_unique<SwapTopCardTask>();
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
