// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Tasks/SimpleTasks/DamageWeaponTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
DamageWeaponTask::DamageWeaponTask(bool opponent, int amount)
    : m_opponent(opponent), m_amount(amount)
{
    // Do nothing
}

TaskStatus DamageWeaponTask::Impl(Player* player)
{
    Weapon* weapon = m_opponent ? player->opponent->GetHero()->weapon
                                : player->GetHero()->weapon;

    if (!weapon)
    {
        return TaskStatus::COMPLETE;
    }

    if (weapon->GetDurability() < m_amount)
    {
        m_amount = weapon->GetDurability();
    }

    weapon->SetDurability(weapon->GetDurability() - m_amount);

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> DamageWeaponTask::CloneImpl()
{
    return std::make_unique<DamageWeaponTask>(m_opponent, m_amount);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
