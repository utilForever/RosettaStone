// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Cards/Character.h>
#include <hspp/Tasks/BasicTasks/DestroyMinionTask.h>

namespace Hearthstonepp::BasicTasks
{
DestroyMinionTask::DestroyMinionTask(Entity* entity)
    : m_character(dynamic_cast<Character*>(entity))
{
    // Do nothing
}

TaskID DestroyMinionTask::GetTaskID() const
{
    return TaskID::DESTROY;
}

MetaData DestroyMinionTask::Impl(Player& player)
{
    auto& myField = player.field;
    auto& opponentField = player.GetOpponent().field;

    auto fieldIter = std::find(myField.begin(), myField.end(), m_character);
    if (fieldIter != myField.end())
    {
        delete *fieldIter;
        myField.erase(fieldIter);

        return MetaData::DESTROY_MINION_SUCCESS;
    }

    fieldIter =
        std::find(opponentField.begin(), opponentField.end(), m_character);
    if (fieldIter != opponentField.end())
    {
        delete *fieldIter;
        opponentField.erase(fieldIter);

        return MetaData::DESTROY_MINION_SUCCESS;
    }

    return MetaData::DESTROY_MINION_NOT_FOUND;
}
}  // namespace Hearthstonepp::BasicTasks
