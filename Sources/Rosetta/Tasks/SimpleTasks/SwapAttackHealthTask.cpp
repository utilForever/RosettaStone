// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/SwapAttackHealthTask.hpp>

#include <utility>

namespace RosettaStone::SimpleTasks
{
SwapAttackHealthTask::SwapAttackHealthTask(EntityType entityType,
                                           std::string enchantmentID)
    : ITask(entityType), m_enchantmentID(std::move(enchantmentID))
{
    // Do nothing
}

TaskID SwapAttackHealthTask::GetTaskID() const
{
    return TaskID::SWAP_ATTACK_HEALTH;
}

TaskStatus SwapAttackHealthTask::Impl(Player& player)
{
    auto entities =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& entity : entities)
    {
        const auto minion = dynamic_cast<Minion*>(entity);
        const int attack = minion->GetAttack();
        const int health = minion->GetHealth();

        const auto attackEffect =
            new Effect(GameTag::ATK, EffectOperator::SET, health);
        const auto healthEffect =
            new Effect(GameTag::HEALTH, EffectOperator::SET, attack);

        attackEffect->Apply(entity);
        healthEffect->Apply(entity);
    }

    return TaskStatus::COMPLETE;
}

ITask* SwapAttackHealthTask::CloneImpl()
{
    return new SwapAttackHealthTask(m_entityType, m_enchantmentID);
}
}  // namespace RosettaStone::SimpleTasks
