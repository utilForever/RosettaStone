// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

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

namespace RosettaStone::PlayMode::Generic
{
void TakeDamageToCharacter(Playable* source, Character* target, int amount,
                           bool isSpellDamage)
{
    if (isSpellDamage)
    {
        if (const auto value = source->player->playerAuraEffects.GetValue(
                GameTag::SPELLPOWER_DOUBLE);
            value > 0)
        {
            amount *= static_cast<int>(std::pow(2.0, value));
        }
    }
    else if (dynamic_cast<HeroPower*>(source))
    {
        // TODO: Process GameTag::HEROPOWER_DAMAGE
    }

    target->TakeDamage(source, amount);
}

bool AddCardToHand(Player* player, Playable* entity)
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

    const auto playable = dynamic_cast<Playable*>(target);
    if (playable)
    {
        if (auto ongoingEnchant =
                dynamic_cast<OngoingEnchant*>(playable->ongoingEffect);
            dynamic_cast<OngoingEnchant*>(power.GetEnchant()) && ongoingEnchant)
        {
            // Increment the count of existing OngoingEnchant
            const int val = ongoingEnchant->GetCount();
            ongoingEnchant->SetCount(val + 1);
            return;
        }
    }

    if (power.GetAura() != nullptr || power.GetTrigger() != nullptr ||
        !power.GetDeathrattleTask().empty())
    {
        // Create Enchantment instance Only when it is needed.
        // As an owner entity for auras, triggers or deathrattle tasks.
        auto enchantment = Enchantment::GetInstance(
            creator->player, enchantmentCard, target, num1, num2);

        if (auto aura = power.GetAura(); aura)
        {
            aura->Activate(enchantment.get());
        }

        if (auto trigger = power.GetTrigger(); trigger)
        {
            trigger->Activate(enchantment.get());
        }

        if (entityID > 0)
        {
            enchantment->SetCapturedCard(
                creator->game->entityList[entityID]->card);
        }
    }

    if (auto enchant = power.GetEnchant(); enchant)
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

    auto hand = dynamic_cast<HandZone*>(playable->zone);
    auto field = dynamic_cast<FieldZone*>(playable->zone);
    int id = playable->GetGameTag(GameTag::ENTITY_ID);

    if (hand != nullptr)
    {
        for (auto& aura : hand->auras)
        {
            aura->Disapply(playable);
        }
    }
    else if (field != nullptr)
    {
        for (auto& aura : field->auras)
        {
            aura->Disapply(playable);
        }
    }

    if (playable->card->GetCardType() == newCard->GetCardType())
    {
        playable->card = newCard;

        if (playable->costManager != nullptr)
        {
            playable->costManager->EntityChanged(newCard->GetCost());
        }
    }
    else
    {
        Playable* entity;

        switch (newCard->GetCardType())
        {
            case CardType::HERO:
                entity =
                    new Hero(player, newCard, playable->card->gameTags, id);
                break;
            case CardType::MINION:
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
            default:
                throw std::invalid_argument(
                    "Generic::ChangeEntity() - Invalid card type");
        }

        if (hand != nullptr)
        {
            hand->ChangeEntity(playable, entity);
        }
        else if (field != nullptr)
        {
            field->ChangeEntity(playable, entity);
        }
        else if (auto deck = dynamic_cast<DeckZone*>(playable->zone); deck)
        {
            deck->ChangeEntity(playable, entity);
        }

        player->game->entityList[id] = entity;

        if (playable->costManager != nullptr)
        {
            playable->costManager->EntityChanged(newCard->GetCost());
        }

        entity->costManager = playable->costManager;
        playable = entity;
    }

    // Replay auras
    if (hand != nullptr)
    {
        if (auto trigger = playable->card->power.GetTrigger(); trigger)
        {
            trigger->Activate(playable, TriggerActivation::HAND);
        }

        if (auto effect = dynamic_cast<AdaptiveCostEffect*>(
                playable->card->power.GetAura());
            effect)
        {
            effect->Activate(playable);
        }

        for (auto& aura : hand->auras)
        {
            aura->NotifyEntityAdded(playable);
        }
    }
    else if (field != nullptr)
    {
        auto minion = dynamic_cast<Minion*>(playable);
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

        for (auto& aura : field->auras)
        {
            aura->NotifyEntityAdded(playable);
        }

        for (auto& aura : field->adjacentAuras)
        {
            aura->SetIsFieldChanged(true);
        }
    }
    else if (auto deck = dynamic_cast<DeckZone*>(playable->zone); deck)
    {
        if (auto trigger = playable->card->power.GetTrigger(); trigger)
        {
            trigger->Activate(playable, TriggerActivation::DECK);
        }
    }
}

void ShuffleIntoDeck(Player* player, Entity* sender, Playable* playable)
{
    // Add card to graveyard if deck is full
    if (player->GetDeckZone()->IsFull())
    {
        return;
    }

    // Add card into deck and shuffle it
    player->GetDeckZone()->Add(playable);
    player->GetDeckZone()->Shuffle();

    if (auto p = dynamic_cast<Playable*>(sender); playable)
    {
        std::unique_ptr<EventMetaData> temp =
            std::move(player->game->currentEventData);
        player->game->currentEventData =
            std::make_unique<EventMetaData>(p, playable);
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
    const auto newMinion =
        dynamic_cast<Minion*>(Entity::GetFromCard(player, card));
    if (newMinion == nullptr)
    {
        return;
    }

    player->GetFieldZone()->Replace(oldMinion, newMinion);
}

IZone* GetZone(Player* player, ZoneType zoneType)
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
