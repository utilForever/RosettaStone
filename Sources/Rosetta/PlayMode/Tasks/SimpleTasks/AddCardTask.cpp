// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/AddCardTask.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>

#include <utility>

namespace RosettaStone::PlayMode::SimpleTasks
{
AddCardTask::AddCardTask(EntityType entityType, std::string cardID, int amount)
    : ITask(entityType), m_cardID(std::move(cardID)), m_amount(amount)
{
    // Do nothing
}

TaskStatus AddCardTask::Impl(Player* player)
{
    switch (m_entityType)
    {
        case EntityType::HAND:
        {
            for (int i = 0; i < m_amount; ++i)
            {
                Card* card = Cards::FindCardByID(m_cardID);
                Generic::AddCardToHand(player,
                                       Entity::GetFromCard(player, card));
            }
            break;
        }
        case EntityType::ENEMY_HAND:
        {
            for (int i = 0; i < m_amount; ++i)
            {
                Card* card = Cards::FindCardByID(m_cardID);
                Generic::AddCardToHand(
                    player->opponent,
                    Entity::GetFromCard(player->opponent, card));
            }
            break;
        }
        case EntityType::DECK:
        {
            for (int i = 0; i < m_amount && !player->GetDeckZone()->IsFull();
                 ++i)
            {
                Card* card = Cards::FindCardByID(m_cardID);
                Generic::ShuffleIntoDeck(player, m_source,
                                         Entity::GetFromCard(player, card));
            }
            break;
        }
        case EntityType::ENEMY_DECK:
        {
            for (int i = 0;
                 i < m_amount && !player->opponent->GetDeckZone()->IsFull();
                 ++i)
            {
                Card* card = Cards::FindCardByID(m_cardID);
                Generic::ShuffleIntoDeck(
                    player->opponent, m_source,
                    Entity::GetFromCard(player->opponent, card));
            }
            break;
        }
        default:
            throw std::invalid_argument(
                "AddCardTask::Impl() - Invalid entity type");
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> AddCardTask::CloneImpl()
{
    return std::make_unique<AddCardTask>(m_entityType, m_cardID, m_amount);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
