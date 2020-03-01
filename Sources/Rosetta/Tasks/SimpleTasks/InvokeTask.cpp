// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Tasks/SimpleTasks/InvokeTask.hpp>
#include "Rosetta/Cards/Cards.hpp"

namespace RosettaStone::SimpleTasks
{
TaskStatus InvokeTask::Impl(Player* player)
{
    if (player->galakrond == nullptr)
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
    auto heroPower = Cards::FindCardByDbfID(
        player->galakrond->GetGameTag(GameTag::HERO_POWER));
    auto heroPowerTasks = heroPower->power.GetPowerTask();
    for (auto& task : heroPowerTasks)
    {
        std::unique_ptr<ITask> clonedTask = task->Clone();

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
}  // namespace RosettaStone::SimpleTasks
