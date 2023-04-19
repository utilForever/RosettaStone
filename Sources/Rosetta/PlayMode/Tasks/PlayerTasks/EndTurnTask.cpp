// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Managers/GameManager.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/EndTurnTask.hpp>

namespace RosettaStone::PlayMode::PlayerTasks
{
TaskStatus EndTurnTask::Impl(Player* player)
{
    Game* game = player->game;

    game->nextStep = Step::MAIN_END;
    GameManager::ProcessNextStep(*game, game->nextStep);

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> EndTurnTask::CloneImpl()
{
    return std::make_unique<EndTurnTask>();
}
}  // namespace RosettaStone::PlayMode::PlayerTasks
