// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/CastSpell.hpp>
#include <Rosetta/Actions/PlayCard.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Zones/FieldZone.hpp>
#include <Rosetta/Zones/GraveyardZone.hpp>
#include <Rosetta/Zones/HandZone.hpp>
#include <Rosetta/Zones/SetasideZone.hpp>

namespace RosettaStone::Generic
{
void PlayCard(Player* player, Playable* source, Character* target, int fieldPos,
              int chooseOne)
{
    if (source == nullptr)
    {
        throw std::invalid_argument("PlayCard() - Source cannot be nullptr!");
    }

    // Check battlefield is full
    if (dynamic_cast<Minion*>(source) != nullptr &&
        player->GetFieldZone()->IsFull())
    {
        return;
    }

    // Check if we can play this card and the target is valid
    if (!source->IsPlayableByPlayer() || !source->IsPlayableByCardReq() ||
        !source->IsValidPlayTarget(target))
    {
        return;
    }

    player->game->currentEventData =
        std::make_unique<EventMetaData>(source, target);

    // Check card has overload
    if (source->HasOverload())
    {
        const int amount = source->GetOverload();
        player->SetOverloadOwed(player->GetOverloadOwed() + amount);
    }

    // Spend mana to play cards
    if (source->GetCost() > 0)
    {
        const int tempUsed =
            std::min(player->GetTemporaryMana(), source->GetCost());
        player->SetTemporaryMana(player->GetTemporaryMana() - tempUsed);
        player->SetUsedMana(player->GetUsedMana() + source->GetCost() -
                            tempUsed);
    }

    // Erase from player's hand
    player->GetHandZone()->Remove(source);

    // Increase the number of cards played this turn
    const int val = player->GetNumCardsPlayedThisTurn();
    player->SetNumCardsPlayedThisTurn(val + 1);

    // Set card's owner
    source->player = player;

    // Set card target and validate target trigger
    if (target != nullptr)
    {
        source->SetCardTarget(target->GetGameTag(GameTag::ENTITY_ID));
        Trigger::ValidateTriggers(player->game, source, SequenceType::TARGET);
    }

    // Validate play card trigger
    Trigger::ValidateTriggers(player->game, source, SequenceType::PLAY_CARD);

    // Pass to sub-logic
    switch (source->card->GetCardType())
    {
        case CardType::HERO:
        {
            const auto hero = dynamic_cast<Hero*>(source);
            PlayHero(player, hero, target, chooseOne);
            break;
        }
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
    if (!player->IsComboActive())
    {
        player->SetComboActive(true);
    }
}

void PlayHero(Player* player, Hero* hero, Character* target, int chooseOne)
{
    Hero* oldHero = player->GetHero();

    hero->SetZoneType(ZoneType::PLAY);
    hero->SetHealth(oldHero->GetMaxHealth());
    hero->SetDamage(oldHero->GetDamage());
    hero->SetArmor(oldHero->GetArmor() + hero->card->gameTags[GameTag::ARMOR]);
    hero->SetExhausted(oldHero->IsExhausted());

    player->GetSetasideZone()->Add(oldHero);
    hero->weapon = oldHero->weapon;
    player->GetSetasideZone()->Add(oldHero->heroPower);
    hero->heroPower = dynamic_cast<HeroPower*>(Entity::GetFromCard(
        player, Cards::FindCardByDbfID(hero->GetGameTag(GameTag::HERO_POWER))));
    if (auto trigger = hero->heroPower->card->power.GetTrigger(); trigger)
    {
        trigger->Activate(hero->heroPower);
    }

    player->SetHero(hero);
    if (auto trigger = hero->card->power.GetTrigger(); trigger)
    {
        trigger->Activate(hero);
    }

    player->game->taskQueue.StartEvent();
    player->game->triggerManager.OnPlayCardTrigger(hero);
    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();
    player->game->ProcessDestroyAndUpdateAura();

    player->game->taskQueue.StartEvent();
    hero->ActivateTask(PowerType::POWER, target, chooseOne);
    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();
    player->game->ProcessDestroyAndUpdateAura();
}

void PlayMinion(Player* player, Minion* minion, Character* target, int fieldPos,
                int chooseOne)
{
    // Validate play minion trigger
    Trigger::ValidateTriggers(player->game, minion, SequenceType::PLAY_MINION);

    int val = player->GetNumMinionsPlayedThisTurn();
    player->SetNumMinionsPlayedThisTurn(val + 1);

    // Add minion to field zone
    player->GetFieldZone()->Add(minion, fieldPos);

    // Apply card mechanics tags
    for (const auto tags : minion->GetGameTags())
    {
        minion->SetGameTag(tags.first, tags.second);
    }

    // Process play card trigger
    player->game->taskQueue.StartEvent();
    player->game->triggerManager.OnPlayMinionTrigger(minion);
    player->game->triggerManager.OnPlayCardTrigger(minion);
    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();
    player->game->ProcessDestroyAndUpdateAura();

    // Check the race of minion
    if (minion->card->GetRace() == Race::ELEMENTAL)
    {
        val = player->GetNumElementalPlayedThisTurn();
        player->SetNumElementalPlayedThisTurn(val + 1);
    }

    // Process summon trigger
    player->game->taskQueue.StartEvent();
    player->game->triggerManager.OnSummonTrigger(minion);
    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();

    // Process target trigger
    if (target != nullptr)
    {
        player->game->taskQueue.StartEvent();
        player->game->triggerManager.OnTargetTrigger(minion);
        player->game->ProcessTasks();
        player->game->taskQueue.EndEvent();

        if (minion->GetCardTarget() != target->GetGameTag(GameTag::ENTITY_ID))
        {
            target = dynamic_cast<Character*>(
                minion->game->entityList[minion->GetCardTarget()]);
        }
    }

    // Process power or combo tasks
    player->game->taskQueue.StartEvent();
    if (minion->HasCombo() && player->IsComboActive())
    {
        minion->ActivateTask(PowerType::COMBO, target);
    }
    else
    {
        minion->ActivateTask(PowerType::POWER, target, chooseOne);
    }
    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();

    player->game->ProcessDestroyAndUpdateAura();

    // Process after play minion trigger
    player->game->taskQueue.StartEvent();
    player->game->triggerManager.OnAfterPlayMinionTrigger(minion);
    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();

    // Process after summon trigger
    player->game->taskQueue.StartEvent();
    player->game->triggerManager.OnAfterSummonTrigger(minion);
    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();

    player->game->ProcessDestroyAndUpdateAura();
}

void PlaySpell(Player* player, Spell* spell, Character* target, int chooseOne)
{
    // Validate play spell trigger
    Trigger::ValidateTriggers(player->game, spell, SequenceType::PLAY_SPELL);

    // Process cast spell trigger
    player->game->taskQueue.StartEvent();
    player->game->triggerManager.OnCastSpellTrigger(spell);

    // Process play card trigger
    player->game->triggerManager.OnPlayCardTrigger(spell);
    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();
    player->game->ProcessDestroyAndUpdateAura();

    // Check spell is countered
    if (spell->IsCountered())
    {
        player->GetGraveyardZone()->Add(spell);
    }
    else
    {
        // Process target trigger
        if (target != nullptr)
        {
            player->game->taskQueue.StartEvent();
            player->game->triggerManager.OnTargetTrigger(spell);
            player->game->ProcessTasks();
            player->game->taskQueue.EndEvent();

            if (spell->GetCardTarget() ==
                target->GetGameTag(GameTag::ENTITY_ID))
            {
                target = dynamic_cast<Character*>(
                    spell->game->entityList[spell->GetCardTarget()]);
            }
        }

        CastSpell(player, spell, target, chooseOne);
        player->game->ProcessDestroyAndUpdateAura();
    }

    // Process after cast trigger
    player->game->taskQueue.StartEvent();
    player->game->triggerManager.OnAfterCastTrigger(spell);
    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();

    player->IncreaseNumSpellsPlayedThisGame();

    player->game->ProcessDestroyAndUpdateAura();
}

void PlayWeapon(Player* player, Weapon* weapon, Character* target)
{
    // Process play card trigger
    player->game->triggerManager.OnPlayCardTrigger(weapon);

    // Process trigger
    if (weapon->card->power.GetTrigger())
    {
        weapon->card->power.GetTrigger()->Activate(weapon);
    }

    // Process aura
    if (weapon->card->power.GetAura())
    {
        weapon->card->power.GetAura()->Activate(weapon);
    }

    // Process target trigger
    if (target != nullptr)
    {
        player->game->taskQueue.StartEvent();
        player->game->triggerManager.OnTargetTrigger(weapon);
        player->game->ProcessTasks();
        player->game->taskQueue.EndEvent();

        if (weapon->GetCardTarget() != target->GetGameTag(GameTag::ENTITY_ID))
        {
            target = dynamic_cast<Character*>(
                weapon->game->entityList[weapon->GetCardTarget()]);
        }
    }

    // Process power tasks
    player->game->taskQueue.StartEvent();
    if (weapon->HasCombo() && player->IsComboActive())
    {
        weapon->ActivateTask(PowerType::COMBO, target);
    }
    else
    {
        weapon->ActivateTask(PowerType::POWER, target);
    }
    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();

    player->game->taskQueue.StartEvent();
    player->GetHero()->AddWeapon(*weapon);
    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();
    player->game->ProcessDestroyAndUpdateAura();
}
}  // namespace RosettaStone::Generic
