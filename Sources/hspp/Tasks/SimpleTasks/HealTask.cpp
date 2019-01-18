// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Tasks/SimpleTasks/HealTask.hpp>
#include <hspp/Tasks/SimpleTasks/IncludeTask.hpp>

namespace Hearthstonepp::SimpleTasks
{
HealTask::HealTask(EntityType entityType, int amount)
    : ITask(entityType), m_amount(amount)
{
    // Do nothing
}

TaskID HealTask::GetTaskID() const
{
    return TaskID::HEAL;
}

MetaData HealTask::Impl(Player& player)
{
    auto entities = IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& entity : entities)
    {
        auto character = dynamic_cast<Character*>(entity);
        character->TakeHeal(*character, m_amount);
    }

    return MetaData::HEAL_SUCCESS;
}
}  // namespace Hearthstonepp::SimpleTasks
