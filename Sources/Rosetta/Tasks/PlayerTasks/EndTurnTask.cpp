// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Games/GameManager.hpp>
#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Tasks/PlayerTasks/EndTurnTask.hpp>

namespace RosettaStone::PlayerTasks
{
TaskID EndTurnTask::GetTaskID() const
{
    return TaskID::END_TURN;
}

ITask* EndTurnTask::CloneImpl()
{
    return new EndTurnTask();
}

TaskStatus EndTurnTask::Impl(Player& player)
{
    auto game = player.GetGame();

    game->nextStep = Step::MAIN_END;
    GameManager::ProcessNextStep(*game, game->nextStep);

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::PlayerTasks
