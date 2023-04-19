// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/InvokeTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
TaskStatus InvokeTask::Impl(Player* player)
{
    if (!player->galakrond)
    {
        return TaskStatus::COMPLETE;
    }

    // Upgrade Galakrond's Battlecry
    player->IncreaseInvoke();

    if (player->GetInvoke() == 2 || player->GetInvoke() == 4)
    {
        player->UpgradeGalakrond();
    }

    // Activate hero power of Galakrond
    const auto heroPower = Cards::FindCardByDbfID(
        player->galakrond->GetGameTag(GameTag::HERO_POWER));
    const auto heroPowerTasks = heroPower->power.GetPowerTask();

    for (const auto& task : heroPowerTasks)
    {
        const std::unique_ptr<ITask> clonedTask = task->Clone();

        clonedTask->SetPlayer(player);
        clonedTask->SetSource(player);
        clonedTask->SetTarget(nullptr);

        clonedTask->Run();
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> InvokeTask::CloneImpl()
{
    return std::make_unique<InvokeTask>();
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
