// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/Attack.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Minion.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>

namespace RosettaStone::PlayMode::Generic
{
void Attack(const Player* player, Character* source, Character* target,
            bool skipPrePhase)
{
    if (!skipPrePhase)
    {
        // Check source can attack and target is valid
        if (!source->CanAttack() ||
            !source->IsValidAttackTarget(player->opponent, target))
        {
            return;
        }
    }

    player->game->currentEventData =
        std::make_unique<EventMetaData>(source, target);

    // Process attack trigger
    player->game->taskQueue.StartEvent();
    player->game->triggerManager.OnAttackTrigger(source);
    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();

    // Validate target trigger
    Trigger::ValidateTriggers(player->game, source, SequenceType::TARGET);

    // Process target trigger
    player->game->taskQueue.StartEvent();
    player->game->triggerManager.OnTargetTrigger(source);
    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();

    // Check source or target is destroyed
    if (source->isDestroyed || target->isDestroyed ||
        (source->zone && source->zone->GetType() != ZoneType::PLAY) ||
        (target->zone && target->zone->GetType() != ZoneType::PLAY))
    {
        player->game->ProcessDestroyAndUpdateAura();
        player->game->currentEventData.reset();
        return;
    }

    const auto hero = dynamic_cast<Hero*>(source);
    const auto minion = dynamic_cast<Minion*>(source);
    const auto realTarget =
        dynamic_cast<Character*>(player->game->currentEventData->eventTarget);
    const auto targetHero = dynamic_cast<Hero*>(realTarget);

    // Set game step to MAIN_COMBAT
    player->game->step = Step::MAIN_COMBAT;

    // Get attack of source and target
    const int targetAttack = realTarget->GetAttack();
    const int sourceAttack = source->GetAttack();

    // Remove durability from weapon if hero attack
    if (hero && hero->HasWeapon() &&
        hero->weapon->GetGameTag(GameTag::IMMUNE) == 0)
    {
        hero->weapon->RemoveDurability(1);
    }

    // Take damage to target
    const int targetDamage = realTarget->TakeDamage(source, sourceAttack);
    const bool isTargetDamaged = targetDamage > 0;

    // Freeze target if attacker is freezer
    if (isTargetDamaged && minion && minion->HasFreeze())
    {
        if (!realTarget->player->CantBeFrozen())
        {
            realTarget->SetGameTag(GameTag::FROZEN, 1);
        }
    }

    // Destroy target if attacker is poisonous
    const bool hasMinionPoisonous =
        (minion && minion->HasPoisonous()) ? true : false;
    const bool hasWeaponPoisonous =
        (hero && hero->HasWeapon() && hero->weapon->HasPoisonous()) ? true
                                                                    : false;
    if (isTargetDamaged && !targetHero &&
        (hasMinionPoisonous || hasWeaponPoisonous) && !realTarget->isDestroyed)
    {
        realTarget->Destroy();
    }

    // Ignore damage from defenders with 0 attack
    if (targetAttack > 0)
    {
        // Take damage to source
        const int sourceDamage = source->TakeDamage(realTarget, targetAttack);
        const bool isSourceDamaged = sourceDamage > 0;

        const auto targetMinion = dynamic_cast<Minion*>(realTarget);

        // Freeze source if defender is freezer
        if (isSourceDamaged && targetMinion && targetMinion->HasFreeze())
        {
            if (!source->player->CantBeFrozen())
            {
                source->SetGameTag(GameTag::FROZEN, 1);
            }
        }

        // Destroy source if defender is poisonous
        const bool hasTargetMinionPoisonous =
            (targetMinion && targetMinion->HasPoisonous());
        if (isSourceDamaged && hasTargetMinionPoisonous && !source->isDestroyed)
        {
            source->Destroy();
        }
    }

    player->game->taskQueue.StartEvent();

    // Check if the source has Honorable Kill
    if (source->HasHonorableKill() && target->GetHealth() == 0)
    {
        TaskList tasks;

        if (hero && hero->HasWeapon())
        {
            tasks = hero->weapon->card->power.GetHonorableKillTask();
        }
        else
        {
            tasks = source->card->power.GetHonorableKillTask();
        }

        for (const auto& task : tasks)
        {
            std::unique_ptr<ITask> clonedTask = task->Clone();

            clonedTask->SetPlayer(source->player);
            if (hero && hero->HasWeapon())
            {
                clonedTask->SetSource(hero->weapon);
            }
            else
            {
                clonedTask->SetSource(source);
            }
            clonedTask->SetTarget(target);

            player->game->taskQueue.Enqueue(std::move(clonedTask));
        }
    }

    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();

    // Remove stealth ability if attacker has it
    if (source->GetGameTag(GameTag::STEALTH) == 1)
    {
        source->SetGameTag(GameTag::STEALTH, 0);
    }

    // Increase the number of attacked
    const int val = source->GetNumAttacksThisTurn();
    source->SetNumAttacksThisTurn(val + 1);

    // Check source is exhausted
    if ((source->GetNumAttacksThisTurn() >= 4 && source->HasMegaWindfury()) ||
        (source->GetNumAttacksThisTurn() >= 2 &&
         (!source->HasMegaWindfury() && source->HasWindfury())) ||
        (source->GetNumAttacksThisTurn() >= 1 &&
         (!source->HasWindfury() && !source->HasMegaWindfury())))
    {
        source->SetExhausted(true);
    }

    // Process after attack trigger
    player->game->taskQueue.StartEvent();
    source->afterAttackTrigger(source);
    player->game->triggerManager.OnAfterAttackTrigger(source);
    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();

    // Process after attacked trigger
    player->game->taskQueue.StartEvent();
    target->afterAttackedTrigger(target);
    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();

    // Process destroy and update aura
    player->game->ProcessDestroyAndUpdateAura();

    player->game->currentEventData.reset();

    // Set game step to MAIN_ACTION
    player->game->step = Step::MAIN_ACTION;
}
}  // namespace RosettaStone::PlayMode::Generic