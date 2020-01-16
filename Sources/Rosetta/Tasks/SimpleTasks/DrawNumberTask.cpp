// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Draw.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/DrawNumberTask.hpp>

namespace RosettaStone::SimpleTasks
{
TaskStatus DrawNumberTask::Impl(Player* player)
{
    std::vector<Entity*> cards;

    for (int i = 0; i < player->game->taskStack.num[0]; ++i)
    {
        Entity* card = Generic::Draw(player, nullptr);
        cards.emplace_back(card);
    }

    if (cards.empty() || cards.at(0) == nullptr)
    {
        return TaskStatus::COMPLETE;
    }

    return TaskStatus::COMPLETE;
}

ITask* DrawNumberTask::CloneImpl()
{
    return new DrawNumberTask();
}
}  // namespace RosettaStone::SimpleTasks
