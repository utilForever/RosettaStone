// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/CastSpell.hpp>
#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Actions/PlayCard.hpp>
#include <Rosetta/PlayMode/Actions/Summon.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>
#include <Rosetta/PlayMode/Zones/SetasideZone.hpp>

namespace RosettaStone::PlayMode::Generic
{
void PlayCard(Player* player, Playable* source, Character* target, int fieldPos,
              int chooseOne)
{
    if (!source)
    {
        throw std::invalid_argument("PlayCard() - Source cannot be nullptr!");
    }

    // Check battlefield is full
    if (source->card->GetCardType() == CardType::MINION &&
        player->GetFieldZone()->IsFull())
    {
        return;
    }

    // Check if we can play this card and the target is valid
    if (!source->IsPlayableByPlayer() ||
        !source->IsPlayableByCardReq(chooseOne) ||
        !source->IsValidPlayTarget(target, chooseOne))
    {
        return;
    }

    player->game->currentEventData =
        std::make_unique<EventMetaData>(source, target);

    // Spend mana to play cards
    const int cost = source->GetCost();
    if (cost > 0)
    {
        source->SetGameTag(GameTag::TAG_LAST_KNOWN_COST_IN_HAND, cost);

        const int tempUsed =
            std::min(player->GetTemporaryMana(), source->GetCost());
        player->SetTemporaryMana(player->GetTemporaryMana() - tempUsed);
        player->SetUsedMana(player->GetUsedMana() + source->GetCost() -
                            tempUsed);
    }

    // Process keyword 'Corrupt'
    for (const auto& playable : player->GetHandZone()->GetAll())
    {
        if (playable->HasCorrupt() && source->GetCost() > playable->GetCost())
        {
            Card* newCard = Cards::FindCardByDbfID(
                playable->GetGameTag(GameTag::CORRUPTEDCARD));
            if (newCard && !newCard->name.empty())
            {
                ChangeEntity(player, playable, newCard, true);
            }
        }
    }

    // Erase from player's hand
    player->GetHandZone()->Remove(source);

    // Increase the number of cards played this turn
    const int val = player->GetNumCardsPlayedThisTurn();
    player->SetNumCardsPlayedThisTurn(val + 1);
    player->playHistory.emplace_back(
        PlayHistory(source, target, player->game->GetTurn(), chooseOne));

    // Record played cards for effect of cards
    // (i.e. Obsidian Shard and Lynessa Sunsorrow)
    player->cardsPlayedThisTurn.emplace_back(source->card);

    // Increase the number of cards played this game
    // that didn't start in your deck
    if (source->GetGameTag(GameTag::ENTITY_ID) >
        player->GetDeckZone()->GetCount() +
            player->opponent->GetDeckZone()->GetCount() + 7)
    {
        player->IncreaseNumCardsPlayedThisGameNotStartInDeck();
    }

    // Set card's owner
    source->player = player;

    // Set card target and validate target trigger
    if (target)
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
        case CardType::LOCATION:
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
        case CardType::INVALID:
        case CardType::GAME:
        case CardType::PLAYER:
        case CardType::ENCHANTMENT:
        case CardType::ITEM:
        case CardType::TOKEN:
        case CardType::HERO_POWER:
        case CardType::BLANK:
        case CardType::GAME_MODE_BUTTON:
        case CardType::MOVE_MINION_HOVER_TARGET:
        case CardType::LETTUCE_ABILITY:
        case CardType::BATTLEGROUND_HERO_BUDDY:
        case CardType::BATTLEGROUND_QUEST_REWARD:
            throw std::invalid_argument(
                "Generic::PlayCard() - Invalid card type!");
    }

    // Process after play card trigger
    player->game->taskQueue.StartEvent();
    player->game->triggerManager.OnAfterPlayCardTrigger(source);
    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();
    player->game->ProcessDestroyAndUpdateAura();

    // Process echo card
    if (source->HasEcho())
    {
        if (const auto spell = dynamic_cast<Spell*>(source);
            spell && spell->IsCountered())
        {
            // Do nothing
        }
        else
        {
            std::map<GameTag, int> tags;
            tags.emplace(GameTag::GHOSTLY, 1);

            const Playable* playable = Entity::GetFromCard(
                player, source->card, tags, player->GetHandZone());

            player->game->UpdateAura();
            player->game->ghostlyCards.emplace_back(
                playable->GetGameTag(GameTag::ENTITY_ID));
        }
    }

    // Reset transformed/summoned minions
    for (const auto& minion : player->GetFieldZone()->GetAll())
    {
        minion->SetTransformed(false);
        minion->SetSummoned(false);
    }

    // Set combo active to true
    if (!player->IsComboActive() && !player->choice)
    {
        player->SetComboActive(true);
    }
}

void PlayHero(Player* player, Hero* hero, Character* target, int chooseOne)
{
    Hero* oldHero = player->GetHero();

    // Transfer values from old hero to new hero
    hero->SetZoneType(ZoneType::PLAY);
    hero->SetBaseHealth(oldHero->GetBaseHealth());
    hero->SetDamage(oldHero->GetDamage());
    hero->SetArmor(oldHero->GetArmor() + hero->card->gameTags[GameTag::ARMOR]);
    hero->SetExhausted(oldHero->IsExhausted());

    // Transfer weapon and hero power
    player->GetSetasideZone()->Add(oldHero);
    player->GetSetasideZone()->Add(oldHero->heroPower);
    hero->weapon = oldHero->weapon;
    hero->heroPower = dynamic_cast<HeroPower*>(Entity::GetFromCard(
        player, Cards::FindCardByDbfID(hero->GetGameTag(GameTag::HERO_POWER))));

    player->SetHero(hero);

    // Process hero power trigger
    if (const auto trigger = hero->heroPower->card->power.GetTrigger(); trigger)
    {
        trigger->Activate(hero->heroPower);
    }

    // Process hero trigger
    if (const auto trigger = hero->card->power.GetTrigger(); trigger)
    {
        trigger->Activate(hero);
    }

    // Process play card trigger
    player->game->taskQueue.StartEvent();
    player->game->triggerManager.OnPlayCardTrigger(hero);
    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();
    player->game->ProcessDestroyAndUpdateAura();

    // Process power tasks
    player->game->taskQueue.StartEvent();
    hero->ActivateTask(PowerType::POWER, target, chooseOne);

    // If player has extra battlecry, activate power task again
    if (player->ExtraBattlecry())
    {
        hero->ActivateTask(PowerType::POWER, target, chooseOne);
    }

    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();
    player->game->ProcessDestroyAndUpdateAura();
}

void PlayMinion(Player* player, Minion* minion, Character* target, int fieldPos,
                int chooseOne)
{
    // Increase the number of minions that played this turn
    int val = player->GetNumMinionsPlayedThisTurn();
    player->SetNumMinionsPlayedThisTurn(val + 1);

    // Check the keyword 'Taunt'
    if (minion->HasTaunt())
    {
        val = player->GetNumTauntMinionsPlayedThisTurn();
        player->SetNumTauntMinionsPlayedThisTurn(val + 1);
    }

    // Check the race 'Elemental'
    if (minion->card->GetRace() == Race::ELEMENTAL)
    {
        val = player->GetNumElementalPlayedThisTurn();
        player->SetNumElementalPlayedThisTurn(val + 1);
    }

    // Check 'Watch Post'
    if (minion->card->IsWatchPost())
    {
        val = player->GetNumWatchPostSummonedThisGame();
        player->SetNumWatchPostSummonedThisGame(val + 1);
    }

    // Validate play minion trigger
    Trigger::ValidateTriggers(player->game, minion, SequenceType::PLAY_MINION);

    // Store the position of card in hand zone
    // to check the condition of outcast task
    const int handPos = minion->GetZonePosition();

    // Add minion to field zone
    player->GetFieldZone()->Add(minion, fieldPos);

    // Apply card mechanics tags
    for (const auto& tags : minion->GetGameTags())
    {
        minion->SetGameTag(tags.first, tags.second);
    }

    // Check 'Colossal'
    if (minion->card->IsColossal())
    {
        SummonAppendages(minion->card->appendages, minion);
    }

    // Process play card trigger
    player->game->taskQueue.StartEvent();
    player->game->triggerManager.OnPlayMinionTrigger(minion);
    player->game->triggerManager.OnPlayCardTrigger(minion);
    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();
    player->game->ProcessDestroyAndUpdateAura();

    // Process summon trigger
    player->game->taskQueue.StartEvent();
    player->game->triggerManager.OnSummonTrigger(minion);
    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();

    // Process target trigger
    if (target)
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

    player->game->taskQueue.StartEvent();

    // Process outcast tasks
    if (minion->HasOutcast() &&
        (handPos == 0 || handPos == player->GetHandZone()->GetCount()))
    {
        minion->ActivateTask(PowerType::OUTCAST, target);
    }

    // Process power or combo tasks
    if (minion->HasCombo() && player->IsComboActive())
    {
        minion->ActivateTask(PowerType::COMBO, target);
    }
    else
    {
        minion->ActivateTask(PowerType::POWER, target, chooseOne);
    }

    // If player has extra battlecry, activate power task again
    if (player->ExtraBattlecry() && minion->HasBattlecry())
    {
        minion->ActivateTask(PowerType::POWER, target, chooseOne);
    }

    // Check card has dormant
    if (minion->HasDormant())
    {
        minion->SetGameTag(GameTag::UNTOUCHABLE, 1);
    }

    // Check card has overload
    if (minion->HasOverload())
    {
        const int amount = minion->GetOverload();
        player->SetOverloadOwed(player->GetOverloadOwed() + amount);
    }

    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();

    player->game->ProcessDestroyAndUpdateAura();

    // Validate after play minion trigger
    Trigger::ValidateTriggers(player->game, minion,
                              SequenceType::AFTER_PLAY_MINION);

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
    // Increase the number of spells that casted this turn
    const int val = player->GetNumSpellsCastThisTurn();
    player->SetNumSpellsCastThisTurn(val + 1);

    // Increase the number of spells that played this turn
    player->IncreaseNumSpellsPlayedThisGame();

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

    // Store minions in field to process spellburst task
    const auto minions = player->GetFieldZone()->GetAll();

    // Check spell is countered
    if (spell->IsCountered())
    {
        player->GetGraveyardZone()->Add(spell);
    }
    else
    {
        // Process target trigger
        if (target)
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

    // Validate after play spell trigger
    Trigger::ValidateTriggers(player->game, spell,
                              SequenceType::AFTER_PLAY_SPELL);

    // Process after cast trigger
    player->game->taskQueue.StartEvent();
    player->game->triggerManager.OnAfterCastTrigger(spell);
    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();

    // Process spellburst tasks
    player->game->taskQueue.StartEvent();

    for (auto& minion : minions)
    {
        if (minion->CanActivateSpellburst())
        {
            minion->ActivateTask(PowerType::SPELLBURST);
            minion->SetGameTag(GameTag::SPELLBURST, 0);
        }
    }

    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();

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
    if (target)
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

    player->game->taskQueue.StartEvent();

    // Process power or combo tasks
    if (weapon->HasCombo() && player->IsComboActive())
    {
        weapon->ActivateTask(PowerType::COMBO, target);
    }
    else
    {
        weapon->ActivateTask(PowerType::POWER, target);
    }

    // If player has extra battlecry, activate power task again
    if (player->ExtraBattlecry() && weapon->HasBattlecry())
    {
        weapon->ActivateTask(PowerType::POWER, target);
    }

    const int handPos = weapon->GetZonePosition();

    // Process outcast tasks
    if (weapon->HasOutcast() &&
        (handPos == 0 || handPos == player->GetHandZone()->GetCount()))
    {
        weapon->ActivateTask(PowerType::OUTCAST, target);
    }

    // Check card has overload
    if (weapon->HasOverload())
    {
        const int amount = weapon->GetOverload();
        player->SetOverloadOwed(player->GetOverloadOwed() + amount);
    }

    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();

    player->game->taskQueue.StartEvent();
    player->GetHero()->AddWeapon(*weapon);
    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();
    player->game->ProcessDestroyAndUpdateAura();
}
}  // namespace RosettaStone::PlayMode::Generic
