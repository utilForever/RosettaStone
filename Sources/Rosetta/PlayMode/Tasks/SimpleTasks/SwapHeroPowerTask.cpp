// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Tasks/SimpleTasks/SwapHeroPowerTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
TaskStatus SwapHeroPowerTask::Impl(Player* player)
{
    const auto temp = player->GetHero()->heroPower;

    player->GetHero()->heroPower = player->opponent->GetHero()->heroPower;
    player->opponent->GetHero()->heroPower = temp;

    player->GetHero()->heroPower->player = player;
    player->opponent->GetHero()->heroPower->player = player->opponent;

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> SwapHeroPowerTask::CloneImpl()
{
    return std::make_unique<SwapHeroPowerTask>();
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
