// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/SetGameTagTask.hpp>

namespace RosettaStone::SimpleTasks
{
SetGameTagTask::SetGameTagTask(EntityType entityType, GameTag tag, int amount)
    : ITask(entityType), m_gameTag(tag), m_amount(amount)
{
    // Do nothing
}

TaskID SetGameTagTask::GetTaskID() const
{
    return TaskID::SET_GAME_TAG;
}

TaskStatus SetGameTagTask::Impl(Player& player)
{
    auto entities =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& entity : entities)
    {
        entity->SetGameTag(m_gameTag, m_amount);

        // Process windfury
        if (m_gameTag == GameTag::WINDFURY && m_amount == 1)
        {
            auto m = dynamic_cast<Minion*>(entity);
            if (m != nullptr && m->numAttacked == 1 &&
                m->GetGameTag(GameTag::EXHAUSTED) == 1)
            {
                m->SetGameTag(GameTag::EXHAUSTED, 0);
            }
        }
    }

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::SimpleTasks
