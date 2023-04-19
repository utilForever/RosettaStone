// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DrawStackTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
DrawStackTask::DrawStackTask(bool addToStack) : m_addToStack(addToStack)
{
    // Do nothing
}

TaskStatus DrawStackTask::Impl(Player* player)
{
    std::vector<Playable*>& playables = player->game->taskStack.playables;

    for (const auto& card : playables)
    {
        Generic::Draw(player, card);
    }

    if (!m_addToStack)
    {
        playables.clear();
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> DrawStackTask::CloneImpl()
{
    return std::make_unique<DrawStackTask>(m_addToStack);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
