// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Tasks/PlayerTasks/CombatTask.hpp>
#include <hspp/Tasks/SimpleTasks/DestroyTask.hpp>
#include <hspp/Tasks/SimpleTasks/FreezeTask.hpp>
#include <hspp/Tasks/SimpleTasks/PoisonousTask.hpp>

using namespace Hearthstonepp::SimpleTasks;

namespace Hearthstonepp::PlayerTasks
{
CombatTask::CombatTask(TaskAgent& agent, Entity* source, Entity* target)
    : ITask(source, target), m_requirement(TaskID::SELECT_TARGET, agent)
{
    // Do nothing
}

TaskID CombatTask::GetTaskID() const
{
    return TaskID::COMBAT;
}

MetaData CombatTask::Impl(Player& player)
{
    auto [sourceIndex, targetIndex] = CalculateIndex(player);

    // Verify index of the source
    // NOTE: 0 means hero, 1 ~ field.size() means minion
    if (sourceIndex > player.GetField().GetNumOfMinions())
    {
        return MetaData::COMBAT_SRC_IDX_OUT_OF_RANGE;
    }

    // Verify index of the target
    // NOTE: 0 means hero, 1 ~ field.size() means minion
    if (targetIndex > player.GetOpponent().GetField().GetNumOfMinions())
    {
        return MetaData::COMBAT_DST_IDX_OUT_OF_RANGE;
    }

    auto source = (sourceIndex > 0)
                      ? dynamic_cast<Character*>(
                            player.GetField().GetMinion(sourceIndex - 1))
                      : dynamic_cast<Character*>(player.GetHero());
    auto target =
        (targetIndex > 0)
            ? dynamic_cast<Character*>(
                  player.GetOpponent().GetField().GetMinion(targetIndex - 1))
            : dynamic_cast<Character*>(player.GetOpponent().GetHero());

    if (!source->CanAttack() ||
        !source->IsValidCombatTarget(player.GetOpponent(), target))
    {
        return MetaData::COMBAT_SOURCE_CANT_ATTACK;
    }

    const size_t targetAttack = target->GetAttack();
    const size_t sourceAttack = source->GetAttack();

    const size_t targetDamage = target->TakeDamage(*source, sourceAttack);
    const bool isTargetDamaged = targetDamage > 0;

    // Destroy target if attacker is poisonous
    if (isTargetDamaged && source->GetGameTag(GameTag::POISONOUS) == 1)
    {
        PoisonousTask(target).Run(player);
    }

    // Freeze target if attacker is freezer
    if (isTargetDamaged && source->GetGameTag(GameTag::FREEZE) == 1)
    {
        FreezeTask(EntityType::TARGET, target).Run(player);
    }

    // Ignore damage from defenders with 0 attack
    if (targetAttack > 0)
    {
        const size_t sourceDamage = source->TakeDamage(*target, targetAttack);
        const bool isSourceDamaged = sourceDamage > 0;

        // Destroy source if defender is poisonous
        if (isSourceDamaged && !target->isDestroyed &&
            target->GetGameTag(GameTag::POISONOUS) == 1)
        {
            PoisonousTask(source).Run(player);
        }

        // Freeze source if defender is freezer
        if (isSourceDamaged && !target->isDestroyed &&
            target->GetGameTag(GameTag::FREEZE) == 1)
        {
            FreezeTask(EntityType::SOURCE, source).Run(player);
        }
    }

    // Remove stealth ability if attacker has it
    if (!source->isDestroyed && source->GetGameTag(GameTag::STEALTH) == 1)
    {
        source->SetGameTag(GameTag::STEALTH, 0);
    }

    // Remove durability from weapon if hero attack
    const Hero* hero =
        source->isDestroyed ? nullptr : dynamic_cast<Hero*>(source);
    if (hero != nullptr && hero->weapon != nullptr &&
        hero->weapon->GetGameTag(GameTag::IMMUNE) == 0)
    {
        hero->weapon->SetDurability(hero->weapon->GetDurability() - 1);

        // Destroy weapon if durability is 0
        if (hero->weapon->GetDurability() <= 0)
        {
            DestroyTask(EntityType::WEAPON).Run(player);
        }
    }

    source->attackableCount--;

    return MetaData::COMBAT_SUCCESS;
}

std::tuple<BYTE, BYTE> CombatTask::CalculateIndex(Player& player) const
{
    if (m_source != nullptr && m_target != nullptr)
    {
        Minion* minionSource = dynamic_cast<Minion*>(m_source);
        Minion* minionTarget = dynamic_cast<Minion*>(m_target);

        int sourceIndex = -1, targetIndex = -1;

        if (m_source == player.GetHero())
        {
            sourceIndex = 0;
        }
        else
        {
            if (minionSource != nullptr)
            {
                sourceIndex = static_cast<BYTE>(
                    player.GetField().FindMinionPos(*minionSource).value());
                sourceIndex += 1;
            }
        }

        Player& opponent = player.GetOpponent();

        if (m_target == opponent.GetHero())
        {
            targetIndex = 0;
        }
        else
        {
            if (minionTarget != nullptr)
            {
                targetIndex = static_cast<BYTE>(
                    opponent.GetField().FindMinionPos(*minionTarget).value());
                targetIndex += 1;
            }
        }

        if (sourceIndex == -1 || targetIndex == -1)
        {
            throw std::logic_error(
                "CombatTask::CalculateIndex() - Invalid index!");
        }

        return std::make_tuple(static_cast<BYTE>(sourceIndex),
                               static_cast<BYTE>(targetIndex));
    }

    TaskMeta serialized;
    // Get targeting response from game interface
    m_requirement.Interact(player.GetID(), serialized);

    // Get the source and the target
    const auto req = TaskMeta::ConvertTo<FlatData::ResponseTarget>(serialized);
    return std::make_tuple(req->src(), req->dst());
}
}  // namespace Hearthstonepp::PlayerTasks
