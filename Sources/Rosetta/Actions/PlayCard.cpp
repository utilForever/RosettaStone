// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/PlayCard.hpp>
#include <Rosetta/Actions/Targeting.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/Tasks.hpp>

namespace RosettaStone::Generic
{
void PlayCard(Player& player, Entity* source, Character* target, int fieldPos)
{
    // Check battlefield is full
    if (dynamic_cast<Minion*>(source) != nullptr && player.GetField().IsFull())
    {
        return;
    }

    // Check if we can play this card and the target is valid
    if (!IsPlayableByPlayer(player, source) || !IsPlayableByCardReq(source) ||
        !IsValidTarget(source, target))
    {
        return;
    }

    // Spend mana to play cards
    if (source->GetCost() > 0)
    {
        int tempUsed = std::min(player.GetTemporaryMana(), source->GetCost());
        player.SetTemporaryMana(player.GetTemporaryMana() - tempUsed);
        player.SetUsedMana(player.GetUsedMana() + source->GetCost() - tempUsed);
    }

    // Erase from player's hand
    player.GetHand().RemoveCard(*source);

    // Set card's owner
    source->owner = &player;

    // Pass to sub-logic
    switch (source->card.GetCardType())
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
    // Add minion to battlefield
    player.GetField().AddMinion(*minion, fieldPos);

    // Apply card mechanics tags
    for (const auto tags : minion->card.gameTags)
    {
        minion->SetGameTag(tags.first, tags.second);
    }

    // Process summon trigger
    player.GetGame()->triggerManager.OnSummonTrigger(&player, minion);
    player.GetGame()->ProcessTasks();

    // Process power tasks
    for (auto& powerTask : minion->card.power.GetPowerTask())
    {
        if (powerTask == nullptr)
        {
            continue;
        }

        powerTask->SetSource(minion);
        powerTask->SetTarget(target);
        powerTask->Run(player);
    }

    player.GetGame()->ProcessDestroyAndUpdateAura();
}

void PlaySpell(Player& player, Spell* spell, Character* target)
{
    // Process power tasks
    for (auto& powerTask : spell->card.power.GetPowerTask())
    {
        if (powerTask == nullptr)
        {
            continue;
        }

        powerTask->SetSource(spell);
        powerTask->SetTarget(target);
        powerTask->Run(player);
    }

    player.GetGraveyard().AddCard(*spell);

    player.GetGame()->ProcessDestroyAndUpdateAura();
}

void PlayWeapon(Player& player, Weapon* weapon, Character* target)
{
    // Process trigger
    if (weapon->card.power.GetTrigger().has_value())
    {
        weapon->card.power.GetTrigger().value().Activate(*weapon);
    }

    // Process aura
    if (weapon->card.power.GetAura().has_value())
    {
        weapon->card.power.GetAura().value().Activate(*weapon);
    }

    // Process power tasks
    for (auto& powerTask : weapon->card.power.GetPowerTask())
    {
        if (powerTask == nullptr)
        {
            continue;
        }

        powerTask->SetSource(weapon);
        powerTask->SetTarget(target);
        powerTask->Run(player);
    }

    player.GetHero()->AddWeapon(*weapon);
}

bool IsPlayableByPlayer(Player& player, Entity* source)
{
    // Verify mana is sufficient
    if (source->GetCost() > player.GetRemainingMana())
    {
        return false;
    }

    // Check if player is on turn
    if (&player != &player.GetGame()->GetCurrentPlayer())
    {
        return false;
    }

    // Check if entity is in hand to be played
    if (dynamic_cast<HeroPower*>(source) == nullptr &&
        player.GetHand().FindCardPos(*source) == std::nullopt)
    {
        return false;
    }

    return true;
}

bool IsPlayableByCardReq(Entity* source)
{
    for (auto& requirement : source->card.playRequirements)
    {
        switch (requirement.first)
        {
            case PlayReq::REQ_WEAPON_EQUIPPED:
                if (!source->owner->GetHero()->HasWeapon())
                {
                    return false;
                }
                break;
            case PlayReq::REQ_MINIMUM_ENEMY_MINIONS:
            {
                auto& opField = source->owner->opponent->GetField();
                if (static_cast<int>(opField.GetNumOfMinions()) <
                    requirement.second)
                {
                    return false;
                }
                break;
            }
            case PlayReq::REQ_MINION_TARGET:
            case PlayReq::REQ_ENEMY_TARGET:
            case PlayReq::REQ_NONSELF_TARGET:
                break;
            default:
                break;
        }
    }

    return true;
}
}  // namespace RosettaStone::Generic
