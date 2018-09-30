#include <hspp/Cards/Character.h>
#include <hspp/Tasks/BasicTasks/DestroyMinionTask.h>

namespace Hearthstonepp::BasicTasks
{
DestroyMinionTask::DestroyMinionTask(Character* character)
    : m_character(character)
{
    // Do nothing
}

TaskID DestroyMinionTask::GetTaskID() const
{
    return TaskID::DESTROY;
}

MetaData DestroyMinionTask::Impl(Player& player1, Player&)
{
    auto& field = player1.field;

    auto ptr = std::find(field.begin(), field.end(), m_character);
    if (ptr != field.end())
    {
        field.erase(ptr);
        return MetaData::DESTROY_MINION_SUCCESS;
    }

    return MetaData::DESTROY_MINION_NOT_FOUND;
}
}  // namespace Hearthstonepp::BasicTasks
