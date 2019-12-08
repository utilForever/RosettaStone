// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/GetEventNumberTask.hpp>

namespace RosettaStone::SimpleTasks
{
GetEventNumberTask::GetEventNumberTask(int numIndex) : m_numIndex(numIndex)
{
    // Do nothing
}

TaskStatus GetEventNumberTask::Impl(Player* player)
{
    const auto data = player->game->currentEventData;

    switch (m_numIndex)
    {
        case 0:
            player->game->taskStack.num[0] = data ? data->eventNumber : 0;
            break;
        case 1:
            player->game->taskStack.num[1] = data ? data->eventNumber : 0;
            break;
        default:
            throw std::invalid_argument(
                "GetEventNumberTask::Impl() - Invalid number index");
    }

    return TaskStatus::COMPLETE;
}

ITask* GetEventNumberTask::CloneImpl()
{
    return new GetEventNumberTask(m_numIndex);
}
}  // namespace RosettaStone::SimpleTasks
