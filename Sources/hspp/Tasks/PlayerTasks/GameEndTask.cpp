// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Tasks/PlayerTasks/GameEndTask.hpp>

namespace Hearthstonepp::PlayerTasks
{
TaskID GameEndTask::GetTaskID() const
{
    return TaskID::GAME_END;
}

MetaData GameEndTask::Impl(Player&)
{
    return MetaData::GAME_END;
}
}  // namespace Hearthstonepp::PlayerTasks