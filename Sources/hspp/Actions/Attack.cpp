// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Actions/Attack.hpp>
#include <hspp/Tasks/SimpleTasks/DestroyTask.hpp>
#include <hspp/Tasks/SimpleTasks/FreezeTask.hpp>
#include <hspp/Tasks/SimpleTasks/PoisonousTask.hpp>

namespace Hearthstonepp::Generic
{
void Attack(Player& player, Character* source, Character* target)
{
    if (!source->CanAttack() ||
        !source->IsValidCombatTarget(player.GetOpponent(), target))
    {
        return;
    }

    const std::size_t targetAttack = target->GetAttack();
    const std::size_t sourceAttack = source->GetAttack();

    const std::size_t targetDamage = target->TakeDamage(*source, sourceAttack);
    const bool isTargetDamaged = targetDamage > 0;

    // Destroy target if attacker is poisonous
    if (isTargetDamaged && source->GetGameTag(GameTag::POISONOUS) == 1)
    {
        SimpleTasks::PoisonousTask(target).Run(player);
    }

    // Freeze target if attacker is freezer
    if (isTargetDamaged && source->GetGameTag(GameTag::FREEZE) == 1)
    {
        SimpleTasks::FreezeTask(EntityType::TARGET, target).Run(player);
    }

    // Ignore damage from defenders with 0 attack
    if (targetAttack > 0)
    {
        const std::size_t sourceDamage =
            source->TakeDamage(*target, targetAttack);
        const bool isSourceDamaged = sourceDamage > 0;

        // Destroy source if defender is poisonous
        if (isSourceDamaged && target->GetGameTag(GameTag::POISONOUS) == 1)
        {
            SimpleTasks::PoisonousTask(source).Run(player);
        }

        // Freeze source if defender is freezer
        if (isSourceDamaged && target->GetGameTag(GameTag::FREEZE) == 1)
        {
            SimpleTasks::FreezeTask(EntityType::SOURCE, source).Run(player);
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
        hero->weapon->durability -= 1;

        // Destroy weapon if durability is 0
        if (hero->weapon->durability == 0)
        {
            SimpleTasks::DestroyTask(EntityType::WEAPON).Run(player);
        }
    }

    source->numAttacked++;

    if ((source->numAttacked >= 1 &&
         source->GetGameTag(GameTag::WINDFURY) == 0) ||
        (source->numAttacked >= 2 &&
         source->GetGameTag(GameTag::WINDFURY) == 1))
    {
        source->SetGameTag(GameTag::EXHAUSTED, 1);
    }

    if (source->isDestroyed)
    {
        source->Destroy();
    }

    if (target->isDestroyed)
    {
        target->Destroy();
    }
}
}  // namespace Hearthstonepp::Generic