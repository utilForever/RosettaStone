// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Tasks/PlayerTasks/PlayerSettingTask.hpp>

namespace Hearthstonepp::PlayerTasks
{
PlayerSettingTask::PlayerSettingTask(TaskAgent& agent) : m_agent(agent)
{
    // Do nothing
}

TaskID PlayerSettingTask::GetTaskID() const
{
    return TaskID::PLAYER_SETTING;
}

MetaData PlayerSettingTask::Impl(Player& player)
{
    player.SetID(0);
    player.GetOpponent().SetID(1);

    TaskMeta setting = Serializer::CreatePlayerSetting(
        player.GetNickname(), player.GetOpponent().GetNickname());
    m_agent.Notify(std::move(setting));

    return MetaData::PLAYER_SETTING_SUCCESS;
}
}  // namespace Hearthstonepp::PlayerTasks