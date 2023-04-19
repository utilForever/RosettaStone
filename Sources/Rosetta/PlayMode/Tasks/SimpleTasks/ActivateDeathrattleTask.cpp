// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Enchantment.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ActivateDeathrattleTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
ActivateDeathrattleTask::ActivateDeathrattleTask(EntityType entityType)
    : ITask(entityType)
{
    // Do nothing
}

TaskStatus ActivateDeathrattleTask::Impl(Player* player)
{
    const auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        playable->ActivateTask(PowerType::DEATHRATTLE);

        for (const auto& enchantment : playable->appliedEnchantments)
        {
            auto tasks = enchantment->card->power.GetDeathrattleTask();

            for (const auto& task : tasks)
            {
                std::unique_ptr<ITask> clonedTask = task->Clone();

                clonedTask->SetPlayer(player);
                clonedTask->SetSource(m_source);
                clonedTask->SetTarget(m_target);

                player->game->taskQueue.Enqueue(std::move(clonedTask));
            }
        }
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> ActivateDeathrattleTask::CloneImpl()
{
    return std::make_unique<ActivateDeathrattleTask>(m_entityType);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
