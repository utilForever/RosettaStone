#include <Tasks/PowerTasks/HealFullTask.h>

namespace Hearthstonepp::PowerTask
{
HealFullTask::HealFullTask(EntityType entityType) : m_entityType(entityType)
{
    // Do nothing
}

TaskID HealFullTask::GetTaskID() const
{
    return TaskID::HEAL_FULL;
}

MetaData HealFullTask::Impl(Player&, Player&)
{
    target->health = target->maxHealth;

    return MetaData::HEAL_FULL_SUCCESS;
}
}  // namespace Hearthstonepp::PowerTask