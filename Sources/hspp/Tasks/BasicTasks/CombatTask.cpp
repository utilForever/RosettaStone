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
CombatTask::CombatTask(TaskAgent& agent)
    : m_requirement(TaskID::SELECT_TARGET, agent)
{
    // Do nothing
}

TaskID CombatTask::GetTaskID() const
{
    return TaskID::COMBAT;
}

MetaData CombatTask::Impl(Player& player1, Player& player2)
{
    TaskMeta serialized;
    // Get targeting response from game interface
    m_requirement.Interact(player1.id, serialized);

    // Get the source and the target
    const auto req = TaskMeta::ConvertTo<FlatData::ResponseTarget>(serialized);
    if (req == nullptr)
    {
        return MetaData::COMBAT_FLATBUFFER_NULLPTR;
    }

    const BYTE sourceIndex = req->src();
    const BYTE targetIndex = req->dst();

    // Verify index of the source
    // NOTE: 0 means hero, 1 ~ field.size() means minion
    if (sourceIndex > player1.field.size())
    {
        return MetaData::COMBAT_SRC_IDX_OUT_OF_RANGE;
    }

    // Verify index of the target
    // NOTE: 0 means hero, 1 ~ field.size() means minion
    if (targetIndex > player2.field.size())
    {
        return MetaData::COMBAT_DST_IDX_OUT_OF_RANGE;
    }

    source = (sourceIndex > 0)
                 ? dynamic_cast<Character*>(player1.field[sourceIndex - 1])
                 : dynamic_cast<Character*>(player1.hero);
    target = (targetIndex > 0)
                 ? dynamic_cast<Character*>(player2.field[targetIndex - 1])
                 : dynamic_cast<Character*>(player2.hero);

    if (!source->CanAttack() || !source->IsValidAttackTarget(player2, target))
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
        PowerTask::PoisonousTask(target).Run(player1, player2);
    }

    // Freeze target if attacker is freezer
    if (isTargetDamaged && source->GetGameTag(GameTag::FREEZE) == 1)
    {
        PowerTask::FreezeTask(target, EntityType::TARGET)
            .Run(player1, player2);
    }

    // Ignore damage from defenders with 0 attack
    if (targetAttack > 0)
    {
        const size_t sourceDamage = source->TakeDamage(*target, targetAttack);
        const bool isSourceDamaged = sourceDamage > 0;

        // Destroy source if defender is poisonous
        if (isSourceDamaged && target->GetGameTag(GameTag::POISONOUS) == 1)
        {
            PowerTask::PoisonousTask(source).Run(player1, player2);
        }

        // Freeze source if defender is freezer
        if (isSourceDamaged && target->GetGameTag(GameTag::FREEZE) == 1)
        {
            PowerTask::FreezeTask(source, EntityType::SOURCE)
                .Run(player1, player2);
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
            DestroyWeaponTask().Run(player1, player2);
        }
    }

    source->attackableCount--;

    // Destroy source minion if health less than 0
    if (source->health <= 0)
    {
        DestroyMinionTask(source).Run(player1, player2);
    }

    // Destroy target minion if health less than 0
    if (target->health <= 0)
    {
        DestroyMinionTask(target).Run(player2, player1);
    }

    return MetaData::COMBAT_SUCCESS;
}
}  // namespace Hearthstonepp::BasicTasks
