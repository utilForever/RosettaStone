// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/GetEventNumberTask.hpp>

#include <stdexcept>

namespace RosettaStone::PlayMode::SimpleTasks
{
GetEventNumberTask::GetEventNumberTask(int numIndex) : m_numIndex(numIndex)
{
    // Do nothing
}

TaskStatus GetEventNumberTask::Impl(Player* player)
{
    const auto data = player->game->currentEventData.get();

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

std::unique_ptr<ITask> GetEventNumberTask::CloneImpl()
{
    return std::make_unique<GetEventNumberTask>(m_numIndex);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
