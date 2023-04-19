// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DrawOpTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
DrawOpTask::DrawOpTask(int amount, bool toStack)
    : m_amount(amount), m_toStack(toStack)
{
    // Do nothing
}

TaskStatus DrawOpTask::Impl(Player* player)
{
    std::vector<Playable*> cards;

    for (int i = 0; i < m_amount; ++i)
    {
        Playable* card = Generic::Draw(player->opponent, nullptr);
        cards.emplace_back(card);
    }

    if (m_toStack)
    {
        for (auto& card : cards)
        {
            player->game->taskStack.playables.emplace_back(card);
        }
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> DrawOpTask::CloneImpl()
{
    return std::make_unique<DrawOpTask>(m_amount, m_toStack);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks