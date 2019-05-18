// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/PlayCard.hpp>
#include <Rosetta/Actions/Targeting.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::Generic
{
void PlayCard(Player& player, Entity* source, Character* target, int fieldPos)
{
    // Check battlefield is full
    if (dynamic_cast<Minion*>(source) != nullptr &&
        player.GetFieldZone().IsFull())
    {
        return;
    }

    // Check if we can play this card and the target is valid
    if (!IsPlayableByPlayer(player, source) || !IsPlayableByCardReq(source) ||
        !IsValidTarget(source, target))
    {
        return;
    }

    // Check card has overload
    if (source->HasOverload())
    {
        const int amount = source->GetOverload();
        player.SetOverloadOwed(player.GetOverloadOwed() + amount);
    }

    // Spend mana to play cards
    if (source->GetCost() > 0)
    {
        int tempUsed = std::min(player.GetTemporaryMana(), source->GetCost());
        player.SetTemporaryMana(player.GetTemporaryMana() - tempUsed);
        player.SetUsedMana(player.GetUsedMana() + source->GetCost() - tempUsed);
    }

    // Erase from player's hand
    player.GetHandZone().RemoveCard(*source);

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

    // Set combo active to true
    if (!player.IsComboActive())
    {
        player.SetComboActive(true);
    }
}

void PlayMinion(Player& player, Minion* minion, Character* target, int fieldPos)
{
    // Add minion to battlefield
    player.GetFieldZone().AddMinion(*minion, fieldPos);

    // Apply card mechanics tags
    for (const auto tags : minion->card.gameTags)
    {
        minion->SetGameTag(tags.first, tags.second);
    }

    // Process play card trigger
    player.GetGame()->triggerManager.OnPlayCardTrigger(&player, minion);
    player.GetGame()->ProcessTasks();
    player.GetGame()->ProcessDestroyAndUpdateAura();

    // Process summon trigger
    player.GetGame()->triggerManager.OnSummonTrigger(&player, minion);
    player.GetGame()->ProcessTasks();

    // Process power or combo tasks
    if (minion->HasCombo() && player.IsComboActive())
    {
        for (auto& comboTask : minion->card.power.GetComboTask())
        {
            if (comboTask == nullptr)
            {
                continue;
            }

            comboTask->SetSource(minion);
            comboTask->SetTarget(target);
            comboTask->Run(player);
        }
    }
    else
    {
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
    }

    player.GetGame()->ProcessDestroyAndUpdateAura();
}

void PlaySpell(Player& player, Spell* spell, Character* target)
{
    // Process cast spell trigger
    player.GetGame()->triggerManager.OnCastSpellTrigger(&player, spell);

    // Process play card trigger
    player.GetGame()->triggerManager.OnPlayCardTrigger(&player, spell);
    player.GetGame()->ProcessTasks();
    player.GetGame()->ProcessDestroyAndUpdateAura();

    // Check spell is countered
    if (spell->IsCountered())
    {
        player.GetGraveyardZone().AddCard(*spell);
    }
    else
    {
        if (spell->IsSecret())
        {
            // Process trigger
            if (spell->card.power.GetTrigger().has_value())
            {
                spell->card.power.GetTrigger().value().Activate(*spell);
            }

            spell->SetExhausted(true);
        }
        else
        {
            // Process trigger
            if (spell->card.power.GetTrigger().has_value())
            {
                spell->card.power.GetTrigger().value().Activate(*spell);
            }

            // Process aura
            if (spell->card.power.GetAura().has_value())
            {
                spell->card.power.GetAura().value().Activate(*spell);
            }

            // Process power or combo tasks
            if (spell->HasCombo() && player.IsComboActive())
            {
                for (auto& comboTask : spell->card.power.GetComboTask())
                {
                    if (comboTask == nullptr)
                    {
                        continue;
                    }

                    comboTask->SetSource(spell);
                    comboTask->SetTarget(target);
                    comboTask->Run(player);
                }
            }
            else
            {
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
            }

            player.GetGraveyardZone().AddCard(*spell);
            player.GetGame()->ProcessDestroyAndUpdateAura();
        }
    }
}

void PlayWeapon(Player& player, Weapon* weapon, Character* target)
{
    // Process play card trigger
    player.GetGame()->triggerManager.OnPlayCardTrigger(&player, weapon);
    player.GetGame()->ProcessTasks();
    player.GetGame()->ProcessDestroyAndUpdateAura();

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
        player.GetHandZone().FindCardPos(*source) == std::nullopt)
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
            case PlayReq::REQ_NUM_MINION_SLOTS:
                if (source->owner->GetFieldZone().IsFull())
                {
                    return false;
                }
                break;
            case PlayReq::REQ_WEAPON_EQUIPPED:
                if (!source->owner->GetHero()->HasWeapon())
                {
                    return false;
                }
                break;
            case PlayReq::REQ_MINIMUM_ENEMY_MINIONS:
            {
                auto& opField = source->owner->opponent->GetFieldZone();
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
