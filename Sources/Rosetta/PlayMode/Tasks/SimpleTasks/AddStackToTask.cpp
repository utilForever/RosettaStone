// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/AddStackToTask.hpp>

#include <stdexcept>

namespace RosettaStone::PlayMode::SimpleTasks
{
AddStackToTask::AddStackToTask(EntityType entityType) : ITask(entityType)
{
    // Do nothing
}

TaskStatus AddStackToTask::Impl(Player* player)
{
    switch (m_entityType)
    {
        case EntityType::HAND:
        {
            for (const auto& entity : player->game->taskStack.playables)
            {
                Generic::AddCardToHand(entity->player, entity);
            }
            break;
        }
        case EntityType::ENEMY_HAND:
        {
            for (const auto& entity : player->game->taskStack.playables)
            {
                Generic::AddCardToHand(entity->player->opponent, entity);
            }
            break;
        }
        case EntityType::DECK:
        {
            for (const auto& entity : player->game->taskStack.playables)
            {
                Generic::ShuffleIntoDeck(entity->player, m_source, entity);
            }
            break;
        }
        default:
            throw std::invalid_argument(
                "AddStackToTask::Impl() - Invalid entity type");
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> AddStackToTask::CloneImpl()
{
    return std::make_unique<AddStackToTask>(m_entityType);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
