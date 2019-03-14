// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Actions/PlayCard.hpp>
#include <hspp/Actions/Targeting.hpp>
#include <hspp/Tasks/PlayerTasks/PlayMinionTask.hpp>

namespace Hearthstonepp::Generic
{
void PlayCard(Player& player, Entity* source, Character* target, int fieldPos)
{
    // Verify mana is sufficient
    if (source->card.cost > player.currentMana)
    {
        return;
    }

    // Verify target is valid
    if (!Generic::IsValidTarget(source, target))
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
            auto minion = dynamic_cast<Minion*>(source);
            PlayMinion(player, minion, target, fieldPos);
            break;
        }
        case CardType::WEAPON:
        {
            auto weapon = dynamic_cast<Weapon*>(source);
            PlayWeapon(player, weapon, target);
            break;
        }
        case CardType::SPELL:
        {
            auto spell = dynamic_cast<Spell*>(source);
            PlaySpell(player, spell, target);
            break;
        }
        default:
            throw std::invalid_argument(
                "Generic::PlayCard() - Invalid card type!");
    }
}

void PlayMinion(Player& player, Minion* minion, Character* target, int fieldPos)
{
    (void)player;
    (void)minion;
    (void)target;
    (void)fieldPos;
}

void PlayWeapon(Player& player, Weapon* weapon, Character* target)
{
    (void)target;

    player.GetHero()->weapon = weapon;
}

void PlaySpell(Player& player, Spell* spell, Character* target)
{
    // Process power tasks
    for (auto& powerTask : spell->card.power.GetPowerTask())
    {
        powerTask->SetTarget(target);
        powerTask->Run(player);
    }
}
}  // namespace Hearthstonepp::Generic