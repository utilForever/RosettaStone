// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/BasicTasks/CombatTask.h>
#include <hspp/Tasks/BasicTasks/DestroyMinionTask.h>
#include <hspp/Tasks/BasicTasks/DestroyWeaponTask.h>
#include <hspp/Tasks/PowerTasks/FreezeTask.h>
#include <hspp/Tasks/PowerTasks/PoisonousTask.h>

namespace Hearthstonepp::BasicTasks
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
    if (sourceIndex > player.field.size())
    {
        return MetaData::COMBAT_SRC_IDX_OUT_OF_RANGE;
    }

    // Verify index of the target
    // NOTE: 0 means hero, 1 ~ field.size() means minion
    if (targetIndex > player.GetOpponent().field.size())
    {
        return MetaData::COMBAT_DST_IDX_OUT_OF_RANGE;
    }

    auto source = (sourceIndex > 0)
                      ? dynamic_cast<Character*>(player.field[sourceIndex - 1])
                      : dynamic_cast<Character*>(player.hero);
    auto target = (targetIndex > 0)
                      ? dynamic_cast<Character*>(
                            player.GetOpponent().field[targetIndex - 1])
                      : dynamic_cast<Character*>(player.GetOpponent().hero);

    if (!source->CanAttack() ||
        !source->IsValidAttackTarget(player.GetOpponent(), target))
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
        PowerTask::PoisonousTask(target).Run(player);
    }

    // Freeze target if attacker is freezer
    if (isTargetDamaged && source->GetGameTag(GameTag::FREEZE) == 1)
    {
        PowerTask::FreezeTask(target, EntityType::TARGET).Run(player);
    }

    // Ignore damage from defenders with 0 attack
    if (targetAttack > 0)
    {
        const size_t sourceDamage = source->TakeDamage(*target, targetAttack);
        const bool isSourceDamaged = sourceDamage > 0;

        // Destroy source if defender is poisonous
        if (isSourceDamaged && target->GetGameTag(GameTag::POISONOUS) == 1)
        {
            PowerTask::PoisonousTask(source).Run(player);
        }

        // Freeze source if defender is freezer
        if (isSourceDamaged && target->GetGameTag(GameTag::FREEZE) == 1)
        {
            PowerTask::FreezeTask(source, EntityType::SOURCE).Run(player);
        }
    }

    // Remove stealth ability if attacker has it
    if (source->GetGameTag(GameTag::STEALTH) == 1)
    {
        source->SetGameTag(GameTag::STEALTH, 0);
    }

    // Remove durability from weapon if hero attack
    const Hero* hero = dynamic_cast<Hero*>(source);
    if (hero != nullptr && hero->weapon != nullptr &&
        hero->weapon->GetGameTag(GameTag::IMMUNE) == 0)
    {
        hero->weapon->SetDurability(hero->weapon->GetDurability() - 1);

        // Destroy weapon if durability is 0
        if (hero->weapon->GetDurability() <= 0)
        {
            DestroyWeaponTask().Run(player);
        }
    }

    source->attackableCount--;

    // Destroy source minion if health less than 0
    if (source->health <= 0)
    {
        DestroyMinionTask(source).Run(player);
    }

    // Destroy target minion if health less than 0
    if (target->health <= 0)
    {
        DestroyMinionTask(target).Run(player);
    }

    return MetaData::COMBAT_SUCCESS;
}

std::tuple<BYTE, BYTE> CombatTask::CalculateIndex(Player& player)
{
    if (m_source != nullptr && m_target != nullptr)
    {
        BYTE sourceIndex, targetIndex;

        if (m_source == player.hero)
        {
            sourceIndex = 0;
        }
        else
        {
            const auto sourceIter =
                std::find(player.field.begin(), player.field.end(), m_source);
            sourceIndex = static_cast<BYTE>(
                std::distance(player.field.begin(), sourceIter) + 1);
        }

        Player& opponent = player.GetOpponent();

        if (m_target == opponent.hero)
        {
            targetIndex = 0;
        }
        else
        {
            const auto targetIter = std::find(opponent.field.begin(),
                                              opponent.field.end(), m_target);
            targetIndex = static_cast<BYTE>(
                std::distance(opponent.field.begin(), targetIter) + 1);
        }

        return std::make_tuple(sourceIndex, targetIndex);
    }

    TaskMeta serialized;
    // Get targeting response from game interface
    m_requirement.Interact(player.id, serialized);

    // Get the source and the target
    const auto req = TaskMeta::ConvertTo<FlatData::ResponseTarget>(serialized);
    return std::make_tuple(req->src(), req->dst());
}
}  // namespace Hearthstonepp::BasicTasks
