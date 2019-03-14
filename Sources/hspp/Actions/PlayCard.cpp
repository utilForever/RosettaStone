// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Actions/PlayCard.hpp>
#include <hspp/Actions/Targeting.hpp>
#include <hspp/Tasks/PlayerTasks/PlayMinionTask.hpp>
#include <hspp/Tasks/PlayerTasks/PlaySpellTask.hpp>

namespace Hearthstonepp::Generic
{
void PlayCard(Player& player, Entity* source, Entity* target, int fieldPos)
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

    // Erase from player's hand
    player.GetHand().RemoveCard(*source);

    // Set card's owner
    source->SetOwner(player);

    // Pass to sub-logic
    switch (source->card.cardType)
    {
        case CardType::MINION:
            PlayMinion(player, source, target, fieldPos);
            break;
        case CardType::WEAPON:
            PlayWeapon(player, source, target);
            break;
        case CardType::SPELL:
            PlaySpell(player, source, target);
            break;
        default:
            throw std::invalid_argument(
                "Generic::PlayCard() - Invalid card type!");
    }
}

void PlayMinion(Player& player, Entity* source, Entity* target, int fieldPos)
{
    PlayerTasks::PlayMinionTask(source, fieldPos, target).Run(player);
}

void PlayWeapon(Player& player, Entity* source, Entity* target)
{
    (void)target;

    player.GetHero()->weapon = dynamic_cast<Weapon*>(source);
}

void PlaySpell(Player& player, Entity* source, Entity* target)
{
    PlayerTasks::PlaySpellTask(source, target).Run(player);
}
}  // namespace Hearthstonepp::Generic