// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Tasks/SimpleTasks/HealTask.hpp>

namespace Hearthstonepp::SimpleTasks
{
HealTask::HealTask(EntityType entityType, int amount)
    : m_entityType(entityType), m_amount(amount)
{
    // Do nothing
}

TaskID HealTask::GetTaskID() const
{
    return TaskID::HEAL;
}

TaskStatus HealTask::Impl(Player& player)
{
    if (m_entityType == +EntityType::HERO)
    {
        if (player.GetHero()->health + m_amount <= player.GetHero()->maxHealth)
        {
            player.GetHero()->health += m_amount;
        }
        else
        {
            player.GetHero()->health = player.GetHero()->maxHealth;
        }

        return TaskStatus::HEAL_SUCCESS;
    }

    return TaskStatus::HEAL_SUCCESS;
}
}  // namespace Hearthstonepp::SimpleTasks