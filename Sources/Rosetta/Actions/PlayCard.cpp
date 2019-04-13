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
    // Verify mana is sufficient
    if (source->GetCost() > player.currentMana)
    {
        return;
    }

    // Check if we can play this card and the target is valid
    if (!IsPlayableByCardReq(source) || !IsValidTarget(source, target))
    {
        return;
    }

    // Spend mana to play cards
    if (source->GetCost() > 0)
    {
        player.currentMana -= source->GetCost();
    }

    // Erase from player's hand
    player.GetHand().RemoveCard(*source);

    // Set card's owner
    source->SetOwner(player);

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
    (void)target;

    // Add minion to battlefield
    player.GetField().AddMinion(*minion, fieldPos);

    // Apply card mechanics tags
    for (const auto tags : minion->card.gameTags)
    {
        minion->SetGameTag(tags.first, tags.second);
    }

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
        powerTask->SetSource(spell);
        powerTask->SetTarget(target);
        powerTask->Run(player);
    }

    player.GetGraveyard().AddCard(*spell);

    player.GetGame()->ProcessDestroyAndUpdateAura();
}

void PlayWeapon(Player& player, Weapon* weapon, Character* target)
{
    (void)target;

    player.GetHero()->AddWeapon(*weapon);
}

bool IsPlayableByCardReq(Entity* source)
{
    for (auto& requirement : source->card.playRequirements)
    {
        switch (requirement.first)
        {
            case PlayReq::REQ_MINIMUM_ENEMY_MINIONS:
            {
                auto& opField = source->GetOwner().GetOpponent().GetField();
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
