// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DrawStackTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
DrawStackTask::DrawStackTask(std::size_t amount, bool addToStack)
    : m_amount(amount), m_addToStack(addToStack)
{
    // Do nothing
}

TaskStatus DrawStackTask::Impl(Player* player)
{
    auto& stack = player->game->taskStack.playables;
    const std::size_t amount =
        (m_amount <= stack.size()) ? m_amount : stack.size();

    for (std::size_t i = 0; i < amount; ++i)
    {
        Playable* card = stack.at(i);
        Generic::Draw(player, card);
    }

    if (!m_addToStack)
    {
        stack.clear();
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> DrawStackTask::CloneImpl()
{
    return std::make_unique<DrawStackTask>(m_amount, m_addToStack);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
