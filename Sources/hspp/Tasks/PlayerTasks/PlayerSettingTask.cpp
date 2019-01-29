// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Tasks/PlayerTasks/PlayerSettingTask.hpp>

namespace Hearthstonepp::PlayerTasks
{
TaskID PlayerSettingTask::GetTaskID() const
{
    return TaskID::PLAYER_SETTING;
}

MetaData PlayerSettingTask::Impl(Player& player)
{
    player.SetID(0);
    player.GetOpponent().SetID(1);

    return MetaData::PLAYER_SETTING_SUCCESS;
}
}  // namespace Hearthstonepp::PlayerTasks