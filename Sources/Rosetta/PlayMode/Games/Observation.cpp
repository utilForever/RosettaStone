// Copyright (c) 2026 Chris Ohk

#include <Rosetta/PlayMode/Games/Observation.hpp>

#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>
#include <Rosetta/PlayMode/Zones/SecretZone.hpp>

#include <utility>

namespace RosettaStone::PlayMode
{
namespace
{
namespace Schema = ObservationSchema;

std::int32_t EncodeValue(int value)
{
    if (!std::in_range<std::int32_t>(value))
    {
        throw std::overflow_error("Observation value exceeds int32");
    }
    return static_cast<std::int32_t>(value);
}

std::int32_t EncodeCardID(const Card* card)
{
    if (!card || card->id.empty() || card->dbfID <= 0 ||
        Cards::FindCardByDbfID(card->dbfID)->id != card->id)
    {
        throw std::invalid_argument("Observation requires a known card ID");
    }
    return EncodeValue(card->dbfID);
}

void CheckCapacity(int count, std::size_t capacity)
{
    if (count < 0 || std::cmp_greater(count, capacity))
    {
        throw std::invalid_argument("Observation zone exceeds v1 capacity");
    }
}

Schema::Card EncodeCard(const Playable& entity, bool includeCost)
{
    Schema::Card row{};
    row[Schema::PRESENT] = 1;
    row[Schema::CARD_ID] = EncodeCardID(entity.card);

    const auto type = entity.card->GetCardType();
    if ((type != CardType::HERO && type != CardType::HERO_POWER &&
         type != CardType::MINION && type != CardType::SPELL &&
         type != CardType::WEAPON) ||
        entity.isDestroyed || entity.HasDormant() ||
        entity.GetGameTag(GameTag::UNTOUCHABLE) != 0 ||
        entity.GetGameTag(GameTag::QUEST) != 0 ||
        entity.GetGameTag(GameTag::SIDEQUEST) != 0 ||
        entity.GetGameTag(GameTag::QUESTLINE) != 0)
    {
        throw std::invalid_argument("Observation cannot represent this card");
    }

    if (includeCost)
    {
        row[Schema::COST] = EncodeValue(entity.GetCost());
    }

    auto& flags = row[Schema::FLAGS];
    flags |= entity.IsExhausted() ? Schema::EXHAUSTED : 0;
    flags |= entity.HasLifesteal() ? Schema::LIFESTEAL : 0;

    if (const auto* character = dynamic_cast<const Character*>(&entity))
    {
        if (character->GetSpellPowerNature() != 0)
        {
            throw std::invalid_argument(
                "Observation cannot represent school-specific Spell Damage");
        }
        row[Schema::ATTACK] = EncodeValue(character->GetAttack());
        row[Schema::HEALTH] = EncodeValue(character->GetHealth());
        row[Schema::MAX_HEALTH] = EncodeValue(character->GetBaseHealth());
        row[Schema::SPELL_POWER] = EncodeValue(character->GetSpellPower());
        row[Schema::ATTACKS_THIS_TURN] =
            EncodeValue(character->GetNumAttacksThisTurn());
        flags |= character->IsFrozen() ? Schema::FROZEN : 0;
        flags |= character->IsImmune() ? Schema::IMMUNE : 0;
        flags |= character->HasStealth() ? Schema::STEALTH : 0;
        flags |= character->HasWindfury() ? Schema::WINDFURY : 0;
        flags |= character->HasMegaWindfury() ? Schema::MEGA_WINDFURY : 0;
        flags |= character->CantAttack() ? Schema::CANT_ATTACK : 0;
        flags |= character->CantAttackHeroes() ? Schema::CANT_ATTACK_HEROES : 0;
    }
    if (const auto* hero = dynamic_cast<const Hero*>(&entity))
    {
        row[Schema::ARMOR] = EncodeValue(hero->GetArmor());
    }
    if (const auto* minion = dynamic_cast<const Minion*>(&entity))
    {
        flags |= minion->HasTaunt() ? Schema::TAUNT : 0;
        flags |= minion->HasDivineShield() ? Schema::DIVINE_SHIELD : 0;
        flags |= minion->HasCharge() ? Schema::CHARGE : 0;
        flags |= minion->HasRush() ? Schema::RUSH : 0;
        flags |= minion->HasPoisonous() ? Schema::POISONOUS : 0;
        flags |= minion->GetGameTag(GameTag::SILENCED) ? Schema::SILENCED : 0;
        flags |= minion->IsAttackableByRush() ? Schema::RUSH_ATTACKABLE : 0;
    }
    if (const auto* weapon = dynamic_cast<const Weapon*>(&entity))
    {
        row[Schema::ATTACK] = EncodeValue(weapon->GetAttack());
        row[Schema::DURABILITY] = EncodeValue(weapon->GetDurability());
        flags |= weapon->IsImmune() ? Schema::IMMUNE : 0;
        flags |= weapon->HasPoisonous() ? Schema::POISONOUS : 0;
    }
    return row;
}
}  // namespace

Observation EncodeObservation(const Game& game)
{
    if (game.state != State::RUNNING || game.step != Step::MAIN_ACTION ||
        !game.taskQueue.IsIdle() || !game.summonedMinions.empty() ||
        !game.deadMinions.empty() || !game.rebornMinions.empty())
    {
        throw std::invalid_argument(
            "Observation requires a quiescent MAIN_ACTION decision");
    }

    const auto* actor = game.GetCurrentPlayer();
    if (!actor->opponent || actor->opponent->choice)
    {
        throw std::invalid_argument("Observation requires the acting player");
    }

    Observation observation;
    observation.turn[Schema::TURN_NUMBER] = EncodeValue(game.GetTurn());
    observation.turn[Schema::DECISION] = Schema::MAIN_ACTION;

    for (const auto* player :
         { actor, static_cast<const Player*>(actor->opponent) })
    {
        const auto index =
            Schema::RelativePlayerIndex(player->playerType, actor->playerType);
        const auto* hero = player->GetHero();
        const auto* board = player->GetFieldZone();
        const auto* hand = player->GetHandZone();
        const auto* secrets = player->GetSecretZone();
        if (player->playState != PlayState::PLAYING || !hero ||
            !hero->heroPower || hero->GetHealth() <= 0)
        {
            throw std::invalid_argument(
                "Observation requires live heroes and hero powers");
        }
        CheckCapacity(board->GetCount(), Schema::BOARD_SLOTS);
        CheckCapacity(hand->GetCount(), Schema::HAND_SLOTS);
        CheckCapacity(secrets->GetCount(), Schema::SECRET_SLOTS);

        // SecretZone also holds public quests; inspect only their category.
        for (const auto* secret : secrets->GetAll())
        {
            if (!secret->IsSecret())
            {
                throw std::invalid_argument(
                    "Observation cannot represent active quests");
            }
        }

        auto& row = observation.players[index];
        row[Schema::MANA_TOTAL] = EncodeValue(player->GetTotalMana());
        row[Schema::MANA_USED] = EncodeValue(player->GetUsedMana());
        row[Schema::MANA_TEMPORARY] = EncodeValue(player->GetTemporaryMana());
        row[Schema::OVERLOAD_LOCKED] = EncodeValue(player->GetOverloadLocked());
        row[Schema::OVERLOAD_OWED] = EncodeValue(player->GetOverloadOwed());
        row[Schema::HAND_COUNT] = EncodeValue(hand->GetCount());
        row[Schema::DECK_COUNT] =
            EncodeValue(player->GetDeckZone()->GetCount());
        row[Schema::SECRET_COUNT] = EncodeValue(secrets->GetCount());
        row[Schema::FATIGUE] = EncodeValue(hero->fatigue);
        row[Schema::CARDS_PLAYED_THIS_TURN] =
            EncodeValue(player->GetNumCardsPlayedThisTurn());
        row[Schema::CHOOSE_BOTH] = player->ChooseBoth();

        observation.heroes[index] = EncodeCard(*hero, false);
        observation.heroPowers[index] = EncodeCard(*hero->heroPower, true);
        if (hero->weapon)
        {
            observation.weapons[index] = EncodeCard(*hero->weapon, false);
        }

        const auto minions = board->GetAll();
        if (std::cmp_not_equal(minions.size(), board->GetCount()))
        {
            throw std::invalid_argument("Observation board is not settled");
        }
        for (std::size_t slot = 0; slot < minions.size(); ++slot)
        {
            if (!dynamic_cast<const Minion*>(minions[slot]))
            {
                throw std::invalid_argument(
                    "Observation supports only minions on the board");
            }
            observation.board[index][slot] = EncodeCard(*minions[slot], false);
        }
    }

    const auto hand = actor->GetHandZone()->GetAll();
    const auto secrets = actor->GetSecretZone()->GetAll();
    if (std::cmp_not_equal(hand.size(), actor->GetHandZone()->GetCount()) ||
        std::cmp_not_equal(secrets.size(), actor->GetSecretZone()->GetCount()))
    {
        throw std::invalid_argument("Observation actor zones are not settled");
    }
    for (std::size_t slot = 0; slot < hand.size(); ++slot)
    {
        observation.hand[slot] = EncodeCard(*hand[slot], true);
        const auto& options = hand[slot]->card->chooseCardIDs;
        if (options.size() > Schema::CHOICE_SLOTS)
        {
            throw std::invalid_argument(
                "Observation has too many Choose One options");
        }
        for (std::size_t option = 0; option < options.size(); ++option)
        {
            observation.chooseOne[slot][option] =
                EncodeCardID(Cards::FindCardByID(options[option]));
        }
    }
    for (std::size_t slot = 0; slot < secrets.size(); ++slot)
    {
        observation.secrets[slot] = EncodeCardID(secrets[slot]->card);
    }

    if (const auto* choice = actor->choice.get())
    {
        if (choice->player != actor ||
            choice->choiceType != ChoiceType::GENERAL ||
            choice->choiceAction != ChoiceAction::HAND || choice->depth != 1 ||
            choice->lastChoice != 0 || choice->nextChoice || choice->source ||
            !choice->entityStack.empty() || choice->choices.empty() ||
            choice->choices.size() > Schema::CHOICE_SLOTS)
        {
            throw std::invalid_argument(
                "Observation cannot represent this choice");
        }
        observation.turn[Schema::DECISION] = Schema::GENERAL_CHOICE;
        for (std::size_t slot = 0; slot < choice->choices.size(); ++slot)
        {
            const auto offered = game.entityList.find(choice->choices[slot]);
            if (offered == game.entityList.end() || !offered->second ||
                offered->second->player != actor ||
                offered->second->GetZoneType() != ZoneType::SETASIDE)
            {
                throw std::invalid_argument(
                    "Observation requires a visible choice offer");
            }
            observation.choices[slot] = EncodeCard(*offered->second, true);
        }
    }
    return observation;
}
}  // namespace RosettaStone::PlayMode
