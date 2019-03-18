// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Actions/Attack.hpp>
#include <hspp/Games/Game.hpp>
#include <hspp/Models/Player.hpp>

namespace Hearthstonepp::Generic
{
void Attack(Player& player, Character* source, Character* target)
{
    if (!source->CanAttack() ||
        !source->IsValidCombatTarget(player.GetOpponent(), target))
    {
        return;
    }

    // Set game step to MAIN_COMBAT
    player.GetGame()->step = Step::MAIN_COMBAT;

    const std::size_t targetAttack = target->GetAttack();
    const std::size_t sourceAttack = source->GetAttack();

    const std::size_t targetDamage = target->TakeDamage(*source, sourceAttack);
    const bool isTargetDamaged = targetDamage > 0;

    // Freeze target if attacker is freezer
    if (isTargetDamaged && source->GetGameTag(GameTag::FREEZE) == 1)
    {
        target->SetGameTag(GameTag::FROZEN, 1);
    }

    // Destroy target if attacker is poisonous
    if (isTargetDamaged && source->GetGameTag(GameTag::POISONOUS) == 1)
    {
        target->Destroy();
    }

    // Ignore damage from defenders with 0 attack
    if (targetAttack > 0)
    {
        const std::size_t sourceDamage =
            source->TakeDamage(*target, targetAttack);
        const bool isSourceDamaged = sourceDamage > 0;

        // Freeze source if defender is freezer
        if (isSourceDamaged && target->GetGameTag(GameTag::FREEZE) == 1)
        {
            source->SetGameTag(GameTag::FROZEN, 1);
        }

        // Destroy source if defender is poisonous
        if (isSourceDamaged && target->GetGameTag(GameTag::POISONOUS) == 1)
        {
            source->Destroy();
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
        hero->weapon->durability--;

        // Destroy weapon if durability is 0
        if (hero->weapon->durability == 0)
        {
            hero->weapon->Destroy();
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

    // Set game step to MAIN_ACTION
    player.GetGame()->step = Step::MAIN_ACTION;
}
}  // namespace Hearthstonepp::Generic