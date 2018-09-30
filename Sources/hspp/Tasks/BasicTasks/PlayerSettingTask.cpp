#include <hspp/Tasks/BasicTasks/PlayerSettingTask.h>

namespace Hearthstonepp::BasicTasks
{
PlayerSettingTask::PlayerSettingTask(TaskAgent& agent) : m_agent(agent)
{
    // Do Nothing
}

TaskID PlayerSettingTask::GetTaskID() const
{
    return TaskID::PLAYER_SETTING;
}

MetaData PlayerSettingTask::Impl(Player& player1, Player& player2)
{
    player1.id = 0;
    player2.id = 1;

    TaskMeta setting =
        Serializer::CreatePlayerSetting(player1.email, player2.email);
    m_agent.Notify(std::move(setting));

    return MetaData::PLAYER_SETTING_SUCCESS;
}
}  // namespace Hearthstonepp::BasicTasks