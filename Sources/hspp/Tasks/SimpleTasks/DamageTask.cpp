// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Tasks/SimpleTasks/DamageTask.hpp>
#include <hspp/Tasks/SimpleTasks/DestroyTask.hpp>
#include <hspp/Tasks/SimpleTasks/IncludeTask.hpp>

namespace Hearthstonepp::SimpleTasks
{
DamageTask::DamageTask(EntityType entityType, size_t damage)
    : ITask(entityType), m_damage(damage)
{
    // Do nothing
}

TaskID DamageTask::GetTaskID() const
{
    return TaskID::DAMAGE;
}

MetaData DamageTask::Impl(Player& player)
{
    auto entities = IncludeTask::GetEntities(m_entityType, player);

    for (auto& entity : entities)
    {
        auto character = dynamic_cast<Character*>(entity);
        character->TakeDamage(*character, m_damage);
    }

    return MetaData::DAMAGE_SUCCESS;
}
}  // namespace Hearthstonepp::SimpleTasks
