// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DestroyDeckCardTask.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
DestroyDeckCardTask::DestroyDeckCardTask(int amount, bool isOpponent)
    : m_amount(amount), m_isOpponent(isOpponent)
{
    // Do nothing
}

TaskStatus DestroyDeckCardTask::Impl(Player* player)
{
    const Player* owner = m_isOpponent ? player->opponent : player;

    for (int i = 0; i < m_amount; ++i)
    {
        if (owner->GetDeckZone()->IsEmpty())
        {
            break;
        }

        Playable* topCard = owner->GetDeckZone()->GetTopCard();

        owner->GetDeckZone()->Remove(topCard);
        owner->GetGraveyardZone()->Add(topCard);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> DestroyDeckCardTask::CloneImpl()
{
    return std::make_unique<DestroyDeckCardTask>(m_amount, m_isOpponent);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
