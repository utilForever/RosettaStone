// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/PutCardDeckTask.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>

#include <utility>

namespace RosettaStone::PlayMode::SimpleTasks
{
PutCardDeckTask::PutCardDeckTask(std::string cardID, DeckPosition position,
                                 int amount)
    : m_cardID(std::move(cardID)), m_position(position), m_amount(amount)
{
    // Do nothing
}

TaskStatus PutCardDeckTask::Impl(Player* player)
{
    for (int i = 0; i < m_amount; ++i)
    {
        if (m_player->GetDeckZone()->IsFull())
        {
            break;
        }

        Card* card = Cards::FindCardByID(m_cardID);
        Playable* playable = Entity::GetFromCard(player, card);

        switch (m_position)
        {
            case DeckPosition::RANDOM:
                Generic::ShuffleIntoDeck(player, m_source, playable);
                break;
            case DeckPosition::TOP:
                m_player->GetDeckZone()->Add(playable);
                break;
            case DeckPosition::BOTTOM:
                m_player->GetDeckZone()->Add(playable, 0);
                break;
        }
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> PutCardDeckTask::CloneImpl()
{
    return std::make_unique<PutCardDeckTask>(m_cardID, m_position, m_amount);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
