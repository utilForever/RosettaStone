// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/Common/Constants.hpp>
#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Enchants/OngoingEnchant.hpp>
#include <Rosetta/PlayMode/Models/Enchantment.hpp>
#include <Rosetta/PlayMode/Models/HeroPower.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>
#include <Rosetta/PlayMode/Zones/SecretZone.hpp>
#include <Rosetta/PlayMode/Zones/SetasideZone.hpp>

#include <cmath>

namespace RosettaStone::PlayMode::Generic
{
void TakeDamageToCharacter(Playable* source, Character* target, int amount,
                           bool isSpellDamage)
{
    if (!source)
    {
        throw std::runtime_error("TakeDamageToCharacter() - source is null!");
    }

    if (isSpellDamage)
    {
        amount += source->player->GetCurrentSpellPower();

        if (const auto spell = dynamic_cast<Spell*>(source); spell)
        {
            const SpellSchool spellSchool = spell->GetSpellSchool();
            amount += source->player->GetExtraSpellPower(spellSchool);
        }

        if (const auto value = source->player->playerAuraEffects.GetValue(
                GameTag::SPELLPOWER_DOUBLE);
            value > 0)
        {
            amount *= static_cast<int>(std::pow(2.0, value));
        }
    }
    else if (dynamic_cast<HeroPower*>(source))
    {
        amount += source->player->GetHero()->GetHeroPowerDamage();

        if (const auto value = source->player->playerAuraEffects.GetValue(
                GameTag::HEROPOWER_DAMAGE);
            value > 0)
        {
            amount += value;
        }
    }

    target->TakeDamage(source, amount);

    source->player->game->taskQueue.StartEvent();

    // Check if the source has Honorable Kill
    if (source->HasHonorableKill() && target->GetHealth() == 0)
    {
        const TaskList tasks = source->card->power.GetHonorableKillTask();

        for (auto& task : tasks)
        {
            std::unique_ptr<ITask> clonedTask = task->Clone();

            clonedTask->SetPlayer(source->player);
            clonedTask->SetSource(source);
            clonedTask->SetTarget(target);

            source->game->taskQueue.Enqueue(std::move(clonedTask));
        }
    }

    source->player->game->ProcessTasks();
    source->player->game->taskQueue.EndEvent();
}

bool AddCardToHand(const Player* player, Playable* entity)
{
    // Add card to graveyard if hand is full
    if (player->GetHandZone()->IsFull())
    {
        player->GetGraveyardZone()->Add(entity);
        return false;
    }

    // Add card to hand
    player->GetHandZone()->Add(entity);
    player->game->taskQueue.StartEvent();
    player->game->triggerManager.OnAddCardTrigger(entity);
    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();
    return true;
}

void AddEnchantment(Card* enchantmentCard, Playable* creator, Entity* target,
                    int num1, int num2, int entityID)
{
    Power& power = enchantmentCard->power;

    if (const auto playable = dynamic_cast<Playable*>(target))
    {
        if (const auto ongoingEnchant =
                dynamic_cast<OngoingEnchant*>(playable->ongoingEffect);
            dynamic_cast<OngoingEnchant*>(power.GetEnchant()) && ongoingEnchant)
        {
            // Increment the count of existing ongoing enchant
            const int val = ongoingEnchant->GetCount();
            ongoingEnchant->SetCount(val + 1);
            return;
        }
    }

    if (power.GetAura() || power.GetTrigger() ||
        !power.GetDeathrattleTask().empty())
    {
        // Create Enchantment instance only when it is needed.
        // As an owner entity for auras, triggers or deathrattle tasks.
        const auto enchantment = Enchantment::GetInstance(
            creator, enchantmentCard, target, num1, num2);

        if (const auto aura = power.GetAura(); aura)
        {
            aura->Activate(enchantment.get());
        }

        if (const auto trigger = power.GetTrigger(); trigger)
        {
            trigger->Activate(enchantment.get());
        }

        if (entityID > 0)
        {
            enchantment->SetCapturedCard(
                creator->game->entityList[entityID]->card);
        }
    }

    if (const auto enchant = power.GetEnchant(); enchant)
    {
        enchant->ActivateTo(target, num1, num2);
    }
}

void ChangeEntity(Player* player, Playable* playable, Card* newCard,
                  bool removeEnchantments)
{
    if (removeEnchantments)
    {
        if (!playable->appliedEnchantments.empty())
        {
            const int enchantSize =
                static_cast<int>(playable->appliedEnchantments.size());
            for (int i = enchantSize - 1; i >= 0; --i)
            {
                playable->appliedEnchantments[i]->Remove();
            }
        }

        playable->ResetCost();
    }

    if (playable->activatedTrigger)
    {
        playable->activatedTrigger->Remove();
    }

    if (playable->ongoingEffect)
    {
        playable->ongoingEffect->Remove();
    }

    const auto deck = dynamic_cast<DeckZone*>(playable->zone);
    const auto hand = dynamic_cast<HandZone*>(playable->zone);
    const auto field = dynamic_cast<FieldZone*>(playable->zone);
    const int id = playable->GetGameTag(GameTag::ENTITY_ID);

    if (hand)
    {
        for (const auto& aura : hand->auras)
        {
            aura->Disapply(playable);
        }
    }
    else if (field)
    {
        for (const auto& aura : field->auras)
        {
            aura->Disapply(playable);
        }
    }

    if (playable->card->GetCardType() == newCard->GetCardType())
    {
        playable->Reset();
        playable->card = newCard;

        for (const auto& gameTag : newCard->gameTags)
        {
            playable->SetGameTag(gameTag.first, gameTag.second);
        }

        if (playable->costManager)
        {
            playable->costManager->EntityChanged(newCard->GetCost());
        }
    }
    else
    {
        Playable* entity = nullptr;

        switch (newCard->GetCardType())
        {
            case CardType::HERO:
                entity =
                    new Hero(player, newCard, playable->card->gameTags, id);
                break;
            case CardType::MINION:
            case CardType::LOCATION:
                entity =
                    new Minion(player, newCard, playable->card->gameTags, id);
                break;
            case CardType::SPELL:
                entity =
                    new Spell(player, newCard, playable->card->gameTags, id);
                break;
            case CardType::WEAPON:
                entity =
                    new Weapon(player, newCard, playable->card->gameTags, id);
                break;
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
                    "Generic::ChangeEntity() - Invalid card type");
        }

        if (hand)
        {
            hand->ChangeEntity(playable, entity);
        }
        else if (field)
        {
            field->ChangeEntity(playable, entity);
        }
        else if (deck)
        {
            deck->ChangeEntity(playable, entity);
        }

        player->game->entityList[id] = entity;

        if (playable->costManager)
        {
            playable->costManager->EntityChanged(newCard->GetCost());
        }

        entity->costManager = playable->costManager;
        playable = entity;
    }

    // Set it is transformed playable
    playable->SetTransformed(true);

    // Replay auras
    if (hand)
    {
        if (const auto trigger = playable->card->power.GetTrigger(); trigger)
        {
            trigger->Activate(playable, TriggerActivation::HAND);
        }

        if (const auto effect = dynamic_cast<AdaptiveCostEffect*>(
                playable->card->power.GetAura());
            effect)
        {
            effect->Activate(playable);
        }

        for (const auto& aura : hand->auras)
        {
            aura->NotifyEntityAdded(playable);
        }
    }
    else if (field)
    {
        const auto minion = dynamic_cast<Minion*>(playable);

        if (minion->player == player->game->GetCurrentPlayer())
        {
            if (!minion->HasCharge())
            {
                if (minion->HasRush())
                {
                    minion->SetExhausted(false);
                    minion->SetAttackableByRush(true);
                    player->game->rushMinions.emplace_back(
                        minion->GetGameTag(GameTag::ENTITY_ID));
                }
                else
                {
                    minion->SetExhausted(true);
                }
            }
            else
            {
                minion->SetExhausted(false);
            }
        }
        else
        {
            minion->SetExhausted(true);
        }

        FieldZone::ActivateAura(minion);

        for (const auto& aura : field->auras)
        {
            aura->NotifyEntityAdded(playable);
        }

        for (const auto& aura : field->adjacentAuras)
        {
            aura->SetIsFieldChanged(true);
        }
    }
    else if (deck)
    {
        if (const auto trigger = playable->card->power.GetTrigger(); trigger)
        {
            trigger->Activate(playable, TriggerActivation::DECK);
        }
    }
}

void ShuffleIntoDeck(const Player* player, Entity* sender, Playable* playable)
{
    // Add card to graveyard if deck is full
    if (player->GetDeckZone()->IsFull())
    {
        return;
    }

    // Add card into deck and shuffle it
    player->GetDeckZone()->Add(playable);
    player->GetDeckZone()->Shuffle();

    if (playable)
    {
        std::unique_ptr<EventMetaData> temp =
            std::move(player->game->currentEventData);
        player->game->currentEventData = std::make_unique<EventMetaData>(
            dynamic_cast<Playable*>(sender), playable);
        player->game->triggerManager.OnShuffleIntoDeckTrigger(playable);
        player->game->currentEventData = std::move(temp);
    }
}

void ChangeManaCrystal(Player* player, int amount, bool fill)
{
    // Available and maximum mana are up to a maximum of 10
    if (player->GetTotalMana() + amount > MANA_UPPER_LIMIT)
    {
        // Add mana crystal when fill is true
        if (!fill)
        {
            player->SetUsedMana(player->GetUsedMana() + MANA_UPPER_LIMIT -
                                player->GetTotalMana());
        }
        else
        {
            player->SetUsedMana(player->GetUsedMana() + MANA_UPPER_LIMIT -
                                player->GetTotalMana() - amount);
        }

        player->SetTotalMana(MANA_UPPER_LIMIT);
    }
    // Maximum mana are up to a minimum of 0
    else if (player->GetTotalMana() + amount < 0)
    {
        player->SetTotalMana(0);
    }
    else
    {
        if (!fill)
        {
            player->SetUsedMana(player->GetUsedMana() + amount);
        }

        player->SetTotalMana(player->GetTotalMana() + amount);
    }
}

void TransformMinion(Player* player, Minion* oldMinion, Card* card)
{
    if (const auto newMinion =
            dynamic_cast<Minion*>(Entity::GetFromCard(player, card));
        newMinion)
    {
        player->GetFieldZone()->Replace(oldMinion, newMinion);
    }
}

IZone* GetZone(const Player* player, ZoneType zoneType)
{
    switch (zoneType)
    {
        case ZoneType::PLAY:
            return player->GetFieldZone();
        case ZoneType::DECK:
            return player->GetDeckZone();
        case ZoneType::HAND:
            return player->GetHandZone();
        case ZoneType::GRAVEYARD:
            return player->GetGraveyardZone();
        case ZoneType::SETASIDE:
            return player->GetSetasideZone();
        case ZoneType::SECRET:
            return player->GetSecretZone();
        case ZoneType::INVALID:
        case ZoneType::REMOVEDFROMGAME:
            return nullptr;
    }

    return nullptr;
}
}  // namespace RosettaStone::PlayMode::Generic
