// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

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
        delete *ptr;
        field.erase(ptr);

        return MetaData::DESTROY_MINION_SUCCESS;
    }

    return MetaData::DESTROY_MINION_NOT_FOUND;
}
}  // namespace Hearthstonepp::BasicTasks
