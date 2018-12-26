// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Cards/Character.hpp>
#include <hspp/Tasks/SimpleTasks/DestroyMinionTask.hpp>

namespace Hearthstonepp::SimpleTasks
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
    auto& myField = player.GetField();
    auto& opField = player.GetOpponent().GetField();

    auto fieldIter = std::find(myField.begin(), myField.end(), m_character);
    if (fieldIter != myField.end())
    {
        delete *fieldIter;
        myField.erase(fieldIter);

        return MetaData::DESTROY_MINION_SUCCESS;
    }

    fieldIter = std::find(opField.begin(), opField.end(), m_character);
    if (fieldIter != opField.end())
    {
        delete *fieldIter;
        opField.erase(fieldIter);

        return MetaData::DESTROY_MINION_SUCCESS;
    }

    return MetaData::DESTROY_MINION_NOT_FOUND;
}
}  // namespace Hearthstonepp::SimpleTasks
