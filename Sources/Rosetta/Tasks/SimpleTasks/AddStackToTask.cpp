// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddStackToTask.hpp>

namespace RosettaStone::SimpleTasks
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
            for (auto& entity : player->game->taskStack.playables)
            {
                Generic::AddCardToHand(entity->player, entity);
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
}  // namespace RosettaStone::SimpleTasks
