// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/SimpleTasks/DamageTask.hpp>
#include <hspp/Tasks/SimpleTasks/DestroyTask.hpp>
#include <hspp/Tasks/SimpleTasks/IncludeTask.hpp>

namespace Hearthstonepp::SimpleTasks
{
DamageTask::DamageTask(EntityType entityType, size_t damage)
    : ITask(entityType), m_damage(damage)
{
    // Do Nothing
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
