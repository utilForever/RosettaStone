// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Models/Minion.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SwapAttackHealthTask.hpp>

#include <utility>

namespace RosettaStone::PlayMode::SimpleTasks
{
SwapAttackHealthTask::SwapAttackHealthTask(EntityType entityType,
                                           std::string enchantmentID)
    : ITask(entityType), m_enchantmentID(std::move(enchantmentID))
{
    // Do nothing
}

TaskStatus SwapAttackHealthTask::Impl(Player* player)
{
    const auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        const auto minion = dynamic_cast<Minion*>(playable);
        const int attack = minion->GetAttack();
        const int health = minion->GetHealth();

        const auto attackEffect =
            new Effect(GameTag::ATK, EffectOperator::SET, health);
        const auto healthEffect =
            new Effect(GameTag::HEALTH, EffectOperator::SET, attack);

        attackEffect->ApplyTo(playable);
        healthEffect->ApplyTo(playable);

        delete attackEffect;
        delete healthEffect;
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> SwapAttackHealthTask::CloneImpl()
{
    return std::make_unique<SwapAttackHealthTask>(m_entityType,
                                                  m_enchantmentID);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
