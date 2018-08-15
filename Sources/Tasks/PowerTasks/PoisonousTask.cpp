/*************************************************************************
> File Name: PoisonousTask.cpp
> Project Name: Hearthstonepp
> Author: Seung-Hyun Jeon
> Purpose: Implement Poisonous
> Created Time: 2018/08/12
> Copyright (c) 2018, Seung-Hyun Jeon
*************************************************************************/
#include <Tasks/PowerTasks/PoisonousTask.h>

namespace Hearthstonepp::PowerTask
{
PoisonousTask::PoisonousTask(Character* source, Character* target): m_source(source), m_target(target)
{
    // Do nothing
}

TaskID PoisonousTask::GetTaskID() const
{
    return TaskID::POISONOUS;
}

MetaData PoisonousTask::Impl(Player&, Player&)
{
    if (m_source->attack <= 0)
    {
        return MetaData::POISONOUS_IGNORE;
    }

    m_target->health = static_cast<size_t>(0);

    return MetaData::POISONOUS_SUCCESS;
}
}  // namespace Hearthstonepp::PowerTask