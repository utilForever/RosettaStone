// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/PlayCard.hpp>
#include <Rosetta/Actions/Targeting.hpp>
#include <Rosetta/Tasks/Tasks.hpp>

namespace RosettaStone::Generic
{
void PlayCard(Player& player, Entity* source, Character* target, int fieldPos)
{
    // Verify mana is sufficient
    if (source->card.cost > player.currentMana)
    {
        return;
    }

    // Verify target is valid
    if (!IsValidTarget(source, target))
    {
        return;
    }

    // Spend mana to play cards
    if (source->card.cost > 0)
    {
        player.currentMana -= source->card.cost;
    }

    // Erase from player's hand
    player.GetHand().RemoveCard(*source);

    // Set card's owner
    source->SetOwner(player);

    // Pass to sub-logic
    switch (source->card.cardType)
    {
        case CardType::MINION:
        {
            const auto minion = dynamic_cast<Minion*>(source);
            PlayMinion(player, minion, target, fieldPos);
            break;
        }
        case CardType::SPELL:
        {
            const auto spell = dynamic_cast<Spell*>(source);
            PlaySpell(player, spell, target);
            break;
        }
        case CardType::WEAPON:
        {
            const auto weapon = dynamic_cast<Weapon*>(source);
            PlayWeapon(player, weapon, target);
            break;
        }
        default:
            throw std::invalid_argument(
                "Generic::PlayCard() - Invalid card type!");
    }
}

void PlayMinion(Player& player, Minion* minion, Character* target, int fieldPos)
{
    (void)target;

    // Add minion to battlefield
    player.GetField().AddMinion(*minion, fieldPos);

    // Apply card mechanics tags
    for (const auto tags : minion->card.mechanics)
    {
        minion->SetGameTag(tags, 1);
    }

    // Process power tasks
    for (auto& power : minion->card.power.GetPowerTask())
    {
        if (power == nullptr)
        {
            continue;
        }

        power->Run(player);
    }
}

void PlaySpell(Player& player, Spell* spell, Character* target)
{
    // Process power tasks
    for (auto& powerTask : spell->card.power.GetPowerTask())
    {
        powerTask->SetSource(spell);
        powerTask->SetTarget(target);
        powerTask->Run(player);
    }
}

void PlayWeapon(Player& player, Weapon* weapon, Character* target)
{
    (void)target;

    player.GetHero()->AddWeapon(*weapon);
}
}  // namespace RosettaStone::Generic
