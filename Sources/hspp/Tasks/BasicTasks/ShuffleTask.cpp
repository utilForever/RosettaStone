// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/BasicTasks/ShuffleTask.h>

#include <random>

namespace Hearthstonepp::BasicTasks
{
TaskID ShuffleTask::GetTaskID() const
{
    return TaskID::SHUFFLE;
}

MetaData ShuffleTask::Impl(Player& player1, Player&)
{
    std::random_device rd;
    std::default_random_engine gen(rd());

    std::shuffle(player1.cards.begin(), player1.cards.end(), gen);

    return MetaData::SHUFFLE_SUCCESS;
}
}  // namespace Hearthstonepp::BasicTasks