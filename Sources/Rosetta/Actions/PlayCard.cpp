// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/CastSpell.hpp>
#include <Rosetta/Actions/PlayCard.hpp>
#include <Rosetta/Actions/Targeting.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::Generic
{
void PlayCard(Player& player, Entity* source, Character* target, int fieldPos,
              int chooseOne)
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
    player.GetHandZone().Remove(*source);

    // Set card's owner
    source->owner = &player;

    // Validate target trigger
    if (target != nullptr)
    {
        Trigger::ValidateTriggers(player.GetGame(), source,
                                  SequenceType::TARGET);
    }

    // Validate play card trigger
    Trigger::ValidateTriggers(player.GetGame(), source,
                              SequenceType::PLAY_CARD);

    // Pass to sub-logic
    switch (source->card.GetCardType())
    {
        case CardType::MINION:
        {
            const auto minion = dynamic_cast<Minion*>(source);
            PlayMinion(player, minion, target, fieldPos, chooseOne);
            break;
        }
        case CardType::SPELL:
        {
            const auto spell = dynamic_cast<Spell*>(source);
            PlaySpell(player, spell, target, chooseOne);
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

void PlayMinion(Player& player, Minion* minion, Character* target, int fieldPos,
                int chooseOne)
{
    const int numMinionsPlayedThisTurn = player.GetNumMinionsPlayedThisTurn();
    player.SetNumMinionsPlayedThisTurn(numMinionsPlayedThisTurn + 1);

    // Add minion to field zone
    player.GetFieldZone().Add(*minion, fieldPos);

    // Apply card mechanics tags
    for (const auto tags : minion->card.gameTags)
    {
        minion->SetGameTag(tags.first, tags.second);
    }

    // Process play card trigger
    player.GetGame()->taskQueue.StartEvent();
    player.GetGame()->triggerManager.OnPlayCardTrigger(&player, minion);
    player.GetGame()->ProcessTasks();
    player.GetGame()->taskQueue.EndEvent();
    player.GetGame()->ProcessDestroyAndUpdateAura();

    // Process summon trigger
    player.GetGame()->taskQueue.StartEvent();
    player.GetGame()->triggerManager.OnSummonTrigger(&player, minion);
    player.GetGame()->ProcessTasks();
    player.GetGame()->taskQueue.EndEvent();

    // Process target trigger
    if (target != nullptr)
    {
        player.GetGame()->taskQueue.StartEvent();
        player.GetGame()->triggerManager.OnTargetTrigger(&player, minion);
        player.GetGame()->ProcessTasks();
        player.GetGame()->taskQueue.EndEvent();
    }

    // Process power or combo tasks
    player.GetGame()->taskQueue.StartEvent();
    if (minion->HasCombo() && player.IsComboActive())
    {
        minion->ActivateTask(PowerType::COMBO, target);
    }
    else
    {
        minion->ActivateTask(PowerType::POWER, target, chooseOne);
    }
    player.GetGame()->ProcessTasks();
    player.GetGame()->taskQueue.EndEvent();
    player.GetGame()->ProcessDestroyAndUpdateAura();
}

void PlaySpell(Player& player, Spell* spell, Character* target, int chooseOne)
{
    // Validate play spell trigger
    Trigger::ValidateTriggers(player.GetGame(), spell,
                              SequenceType::PLAY_SPELL);

    // Process cast spell trigger
    player.GetGame()->taskQueue.StartEvent();
    player.GetGame()->triggerManager.OnCastSpellTrigger(&player, spell);

    // Process play card trigger
    player.GetGame()->triggerManager.OnPlayCardTrigger(&player, spell);
    player.GetGame()->ProcessTasks();
    player.GetGame()->taskQueue.EndEvent();
    player.GetGame()->ProcessDestroyAndUpdateAura();

    // Check spell is countered
    if (spell->IsCountered())
    {
        player.GetGraveyardZone().Add(*spell);
    }
    else
    {
        // Process target trigger
        if (target != nullptr)
        {
            player.GetGame()->taskQueue.StartEvent();
            player.GetGame()->triggerManager.OnTargetTrigger(&player, spell);
            player.GetGame()->ProcessTasks();
            player.GetGame()->taskQueue.EndEvent();
        }

        CastSpell(player, spell, target, chooseOne);
        player.GetGame()->ProcessDestroyAndUpdateAura();
    }

    // Process after cast trigger
    player.GetGame()->taskQueue.StartEvent();
    player.GetGame()->triggerManager.OnAfterCastTrigger(&player, spell);
    player.GetGame()->ProcessTasks();
    player.GetGame()->taskQueue.EndEvent();

    player.GetGame()->ProcessDestroyAndUpdateAura();
}

void PlayWeapon(Player& player, Weapon* weapon, Character* target)
{
    // Process play card trigger
    player.GetGame()->triggerManager.OnPlayCardTrigger(&player, weapon);

    // Process trigger
    if (weapon->card.power.GetTrigger())
    {
        weapon->card.power.GetTrigger()->Activate(weapon);
    }

    // Process aura
    if (weapon->card.power.GetAura())
    {
        weapon->card.power.GetAura()->Activate(weapon);
    }

    // Process target trigger
    if (target != nullptr)
    {
        player.GetGame()->taskQueue.StartEvent();
        player.GetGame()->triggerManager.OnTargetTrigger(&player, weapon);
        player.GetGame()->ProcessTasks();
        player.GetGame()->taskQueue.EndEvent();
    }

    // Process power tasks
    player.GetGame()->taskQueue.StartEvent();
    weapon->ActivateTask(PowerType::POWER, target);
    player.GetGame()->ProcessTasks();
    player.GetGame()->taskQueue.EndEvent();

    player.GetGame()->taskQueue.StartEvent();
    player.GetHero()->AddWeapon(*weapon);
    player.GetGame()->ProcessTasks();
    player.GetGame()->taskQueue.EndEvent();
    player.GetGame()->ProcessDestroyAndUpdateAura();
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
        source->zone != &player.GetHandZone())
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
                if (opField.GetCount() < requirement.second)
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
