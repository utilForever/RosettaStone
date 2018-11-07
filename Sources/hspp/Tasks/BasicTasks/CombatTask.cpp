// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/BasicTasks/CombatTask.h>
#include <hspp/Tasks/BasicTasks/DamageTask.h>
#include <hspp/Tasks/BasicTasks/DestroyMinionTask.h>
#include <hspp/Tasks/PowerTasks/FreezeTask.h>
#include <hspp/Tasks/PowerTasks/PoisonousTask.h>

namespace Hearthstonepp::BasicTasks
{
CombatTask::CombatTask(TaskAgent& agent)
    : m_requirement(TaskID::SELECT_TARGET, agent)
{
    // Do Nothing
}

TaskID CombatTask::GetTaskID() const
{
    return TaskID::COMBAT;
}

MetaData CombatTask::Impl(Player& player1, Player& player2)
{
    TaskMeta serialized;
    // Get Targeting Response from GameInterface
    m_requirement.Interact(player1.id, serialized);

    auto req = TaskMeta::ConvertTo<FlatData::ResponseTarget>(serialized);
    if (req == nullptr)
    {
        return MetaData::COMBAT_FLATBUFFER_NULLPTR;
    }

    BYTE src = req->src();
    BYTE dst = req->dst();

    // Source Minion Index Verification
    if (src > player1.field.size())
    {
        return MetaData::COMBAT_SRC_IDX_OUT_OF_RANGE;
    }

    // Destination Verification
    // dst == 0 : hero
    // 1 < dst <= field.size : minion
    if (dst > player2.field.size())
    {
        return MetaData::COMBAT_DST_IDX_OUT_OF_RANGE;
    }

    source = (src > 0) ? dynamic_cast<Character*>(player1.field[src - 1])
                       : dynamic_cast<Character*>(player1.hero);
    target = (dst > 0) ? dynamic_cast<Character*>(player2.field[dst - 1])
                       : dynamic_cast<Character*>(player2.hero);

    // Verify attack of source is 0
    if (source->GetAttack() == 0)
    {
        return MetaData::COMBAT_SOURCE_ATTACK_ZERO;
    }

    // Verify source has GameTag::FROZEN
    if (source->GetGameTag(GameTag::FROZEN) == 1)
    {
        return MetaData::COMBAT_SOURCE_FROZEN;
    }

    // Taunt Verification
    if (target->GetGameTag(GameTag::TAUNT) == 0)
    {
        for (auto& item : player2.field)
        {
            if (item->GetGameTag(GameTag::TAUNT) == 1)
            {
                return MetaData::COMBAT_FIELD_HAVE_TAUNT;
            }
        }
    }

    // Stealth Verification
    if (target->GetGameTag(GameTag::STEALTH) == 1)
    {
        return MetaData::COMBAT_TARGET_STEALTH;
    }

    // Immune Verification
    if (target->GetGameTag(GameTag::IMMUNE) == 1)
    {
        return MetaData::COMBAT_TARGET_IMMUNE;
    }

    // Source Minion Verification for Attacked Vector
    if (source->attackableCount == 0)
    {
        return MetaData::COMBAT_ALREADY_ATTACKED;
    }

    source->attackableCount--;

    const size_t sourceAttack = source->GetAttack();
    const size_t targetAttack = target->GetAttack();

    const size_t targetDamage = target->TakeDamage(*source, sourceAttack);
    const size_t sourceDamage = source->TakeDamage(*target, targetAttack);

    (void)targetDamage;
    (void)sourceDamage;

    // Destroy target if attacker is poisonous
    if (source->GetGameTag(GameTag::POISONOUS) == 1)
    {
        PowerTask::PoisonousTask(target).Run(player1, player2);
    }
    // Freeze target if attacker is freezer
    else if (source->GetGameTag(GameTag::FREEZE) == 1)
    {
        PowerTask::FreezeTask(target, TargetType::OPPONENT_MINION)
            .Run(player1, player2);
    }

    // Destroy source if defender is poisonous
    if (target->GetGameTag(GameTag::POISONOUS) == 1)
    {
        PowerTask::PoisonousTask(source).Run(player1, player2);
    }
    // Freeze source if defender is freezer
    else if (target->GetGameTag(GameTag::FREEZE) == 1)
    {
        PowerTask::FreezeTask(source, TargetType::OPPONENT_MINION)
            .Run(player1, player2);
    }

    if (source->GetGameTag(GameTag::STEALTH) == 1)
    {
        source->SetGameTag(GameTag::STEALTH, 0);
    }

    // Source Health Check
    if (source->health <= 0)
    {
        DestroyMinionTask(source).Run(player1, player2);
    }

    // Target Health Check
    if (target->health <= 0)
    {
        DestroyMinionTask(target).Run(player2, player1);
    }

    return MetaData::COMBAT_SUCCESS;
}
}  // namespace Hearthstonepp::BasicTasks
