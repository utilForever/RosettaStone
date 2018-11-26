// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/BasicTasks/ShuffleTask.hpp>

#include <random>

namespace Hearthstonepp::BasicTasks
{
TaskID ShuffleTask::GetTaskID() const
{
    return TaskID::SHUFFLE;
}

MetaData ShuffleTask::Impl(Player& player)
{
    std::random_device rd;
    std::default_random_engine gen(rd());

    std::shuffle(player.GetDeck().begin(), player.GetDeck().end(), gen);

    return MetaData::SHUFFLE_SUCCESS;
}
}  // namespace Hearthstonepp::BasicTasks