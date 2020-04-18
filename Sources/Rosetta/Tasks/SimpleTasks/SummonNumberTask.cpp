// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/SummonNumberTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/SummonOpTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/SummonTask.hpp>

namespace RosettaStone::SimpleTasks
{
SummonNumberTask::SummonNumberTask(const std::string& cardID, bool opponent)
    : m_card(Cards::FindCardByID(cardID)), m_opponent(opponent)
{
    // Do nothing
}

TaskStatus SummonNumberTask::Impl(Player* player)
{
    TaskStack stack = player->game->taskStack;
    std::unique_ptr<ITask> task;

    if (m_opponent)
    {
        task = std::make_unique<SummonOpTask>(m_card->id, stack.num[0]);
    }
    else
    {
        task = std::make_unique<SummonTask>(m_card->id, stack.num[0]);
    }

    task->SetPlayer(player);
    task->SetSource(m_source);
    task->SetTarget(m_target);

    return task->Run();
}

std::unique_ptr<ITask> SummonNumberTask::CloneImpl()
{
    return std::make_unique<SummonNumberTask>(m_card->id, m_opponent);
}
}  // namespace RosettaStone::SimpleTasks
