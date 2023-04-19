// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SummonNumberTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SummonOpTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
SummonNumberTask::SummonNumberTask(const std::string& cardID, bool opponent,
                                   SummonSide side)
    : m_card(Cards::FindCardByID(cardID)), m_opponent(opponent), m_side(side)
{
    // Do nothing
}

TaskStatus SummonNumberTask::Impl(Player* player)
{
    const TaskStack stack = player->game->taskStack;
    std::unique_ptr<ITask> task;

    if (m_opponent)
    {
        task = std::make_unique<SummonOpTask>(m_card->id, stack.num[0], m_side);
    }
    else
    {
        task = std::make_unique<SummonTask>(m_card->id, stack.num[0], m_side);
    }

    task->SetPlayer(player);
    task->SetSource(m_source);
    task->SetTarget(m_target);

    return task->Run();
}

std::unique_ptr<ITask> SummonNumberTask::CloneImpl()
{
    return std::make_unique<SummonNumberTask>(m_card->id, m_opponent, m_side);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
