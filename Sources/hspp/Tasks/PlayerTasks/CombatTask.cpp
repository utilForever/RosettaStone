// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Commons/Utils.hpp>
#include <hspp/Policy/Policy.hpp>
#include <hspp/Tasks/PlayerTasks/CombatTask.hpp>
#include <hspp/Tasks/SimpleTasks/DestroyMinionTask.hpp>
#include <hspp/Tasks/SimpleTasks/DestroyWeaponTask.hpp>
#include <hspp/Tasks/SimpleTasks/FreezeTask.hpp>
#include <hspp/Tasks/SimpleTasks/PoisonousTask.hpp>

using namespace Hearthstonepp::SimpleTasks;

namespace Hearthstonepp::PlayerTasks
{
CombatTask::CombatTask(Entity* source, Entity* target) : ITask(source, target)
{
    // Do nothing
}

TaskID CombatTask::GetTaskID() const
{
    return TaskID::COMBAT;
}

TaskStatus CombatTask::Impl(Player& player)
{
    auto [sourceIndex, targetIndex] = CalculateIndex(player);

    // Verify index of the source
    // NOTE: 0 means hero, 1 ~ field.size() means minion
    if (sourceIndex > player.GetField().size())
    {
        return TaskStatus::COMBAT_SRC_IDX_OUT_OF_RANGE;
    }

    // Verify index of the target
    // NOTE: 0 means hero, 1 ~ field.size() means minion
    if (targetIndex > player.GetOpponent().GetField().size())
    {
        return TaskStatus::COMBAT_DST_IDX_OUT_OF_RANGE;
    }

    auto source =
        (sourceIndex > 0)
            ? dynamic_cast<Character*>(player.GetField()[sourceIndex - 1])
            : dynamic_cast<Character*>(player.GetHero());
    auto target =
        (targetIndex > 0)
            ? dynamic_cast<Character*>(
                  player.GetOpponent().GetField()[targetIndex - 1])
            : dynamic_cast<Character*>(player.GetOpponent().GetHero());

    if (!source->CanAttack() ||
        !source->IsValidAttackTarget(player.GetOpponent(), target))
    {
        return TaskStatus::COMBAT_SOURCE_CANT_ATTACK;
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
        FreezeTask(target, EntityType::TARGET).Run(player);
    }

    // Ignore damage from defenders with 0 attack
    if (targetAttack > 0)
    {
        const size_t sourceDamage = source->TakeDamage(*target, targetAttack);
        const bool isSourceDamaged = sourceDamage > 0;

        // Destroy source if defender is poisonous
        if (isSourceDamaged && target->GetGameTag(GameTag::POISONOUS) == 1)
        {
            PoisonousTask(source).Run(player);
        }

        // Freeze source if defender is freezer
        if (isSourceDamaged && target->GetGameTag(GameTag::FREEZE) == 1)
        {
            FreezeTask(source, EntityType::SOURCE).Run(player);
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

    return TaskStatus::COMBAT_SUCCESS;
}

std::tuple<BYTE, BYTE> CombatTask::CalculateIndex(Player& player) const
{
    if (m_source != nullptr && m_target != nullptr)
    {
        BYTE sourceIndex, targetIndex;

        if (m_source == player.GetHero())
        {
            sourceIndex = 0;
        }
        else
        {
            const auto sourceIter = std::find(
                player.GetField().begin(), player.GetField().end(), m_source);
            sourceIndex = static_cast<BYTE>(
                std::distance(player.GetField().begin(), sourceIter) + 1);
        }

        Player& opponent = player.GetOpponent();

        if (m_target == opponent.GetHero())
        {
            targetIndex = 0;
        }
        else
        {
            const auto targetIter =
                std::find(opponent.GetField().begin(),
                          opponent.GetField().end(), m_target);
            targetIndex = static_cast<BYTE>(
                std::distance(opponent.GetField().begin(), targetIter) + 1);
        }

        return std::make_tuple(sourceIndex, targetIndex);
    }

    TaskMeta req = player.GetPolicy().Require(player, TaskID::COMBAT);
    Box<BYTE> obj = req.MoveObject<Box<BYTE>>();
    return std::make_tuple(obj[0], obj[1]);
}
}  // namespace Hearthstonepp::PlayerTasks
