// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddCardTask.hpp>
#include <Rosetta/Zones/DeckZone.hpp>

#include <utility>

namespace RosettaStone::SimpleTasks
{
AddCardTask::AddCardTask(EntityType entityType, std::string cardID, int amount)
    : ITask(entityType), m_cardID(std::move(cardID)), m_amount(amount)
{
    // Do nothing
}

TaskStatus AddCardTask::Impl(Player* player)
{
    std::vector<Entity*> entities;

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
                Generic::ShuffleIntoDeck(player,
                                         Entity::GetFromCard(player, card));
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
}  // namespace RosettaStone::SimpleTasks
