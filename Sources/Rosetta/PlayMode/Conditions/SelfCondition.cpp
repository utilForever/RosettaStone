// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Conditions/SelfCondition.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>
#include <Rosetta/PlayMode/Zones/SecretZone.hpp>

#include <limits>
#include <string>
#include <utility>

namespace RosettaStone::PlayMode
{
SelfCondition::SelfCondition(std::function<bool(Playable*)> func)
    : m_func(std::move(func))
{
    // Do nothing
}

SelfCondition SelfCondition::IsFriendly()
{
    return SelfCondition([](const Playable* playable) {
        const auto iter =
            playable->game->entityList.find(playable->GetCardTarget());
        return playable->player == iter->second->player;
    });
}

SelfCondition SelfCondition::IsNotCardClass(CardClass cardClass)
{
    return SelfCondition([cardClass](const Playable* playable) {
        return playable->card->GetCardClass() != cardClass;
    });
}

SelfCondition SelfCondition::IsNotStartInDeck()
{
    return SelfCondition([](const Playable* playable) {
        const auto entityID = playable->GetGameTag(GameTag::ENTITY_ID);
        const auto curDeckCount = playable->player->GetDeckZone()->GetCount();
        const auto opDeckCount =
            playable->player->opponent->GetDeckZone()->GetCount();
        return entityID > curDeckCount + opDeckCount + 7;
    });
}

SelfCondition SelfCondition::IsHandEmpty()
{
    return SelfCondition([](const Playable* playable) {
        return playable->player->GetHandZone()->IsEmpty();
    });
}

SelfCondition SelfCondition::IsHandFull()
{
    return SelfCondition([](const Playable* playable) {
        return playable->player->GetHandZone()->IsFull();
    });
}

SelfCondition SelfCondition::IsHandNotFull()
{
    return SelfCondition([](const Playable* playable) {
        return !playable->player->GetHandZone()->IsFull();
    });
}

SelfCondition SelfCondition::IsDeckEmpty()
{
    return SelfCondition([](const Playable* playable) {
        return playable->player->GetDeckZone()->IsEmpty();
    });
}

SelfCondition SelfCondition::IsSecretFull()
{
    return SelfCondition([](const Playable* playable) {
        return playable->player->GetSecretZone()->IsFull();
    });
}

SelfCondition SelfCondition::IsHeroPowerCard(const std::string& cardID)
{
    return SelfCondition([cardID](const Playable* playable) {
        return playable->player->GetHero()->heroPower->card->id == cardID;
    });
}

SelfCondition SelfCondition::IsBattlecryCard()
{
    return SelfCondition(
        [](const Playable* playable) { return playable->HasBattlecry(); });
}

SelfCondition SelfCondition::IsDeathrattleCard()
{
    return SelfCondition(
        [](const Playable* playable) { return playable->HasDeathrattle(); });
}

SelfCondition SelfCondition::IsDiscoverCard()
{
    return SelfCondition(
        [](const Playable* playable) { return playable->HasDiscover(); });
}

SelfCondition SelfCondition::IsGalakrondHero()
{
    return SelfCondition(
        [](const Playable* playable) { return playable->card->IsGalakrond(); });
}

SelfCondition SelfCondition::IsAwaken()
{
    return SelfCondition([](const Playable* playable) {
        if (const auto minion = dynamic_cast<const Minion*>(playable))
        {
            return minion->HasDormant() &&
                   minion->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1) ==
                       minion->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2);
        }

        return false;
    });
}

SelfCondition SelfCondition::IsDead()
{
    return SelfCondition(
        [](const Playable* playable) { return playable->isDestroyed; });
}

SelfCondition SelfCondition::IsNotDead()
{
    return SelfCondition(
        [](const Playable* playable) { return !playable->isDestroyed; });
}

SelfCondition SelfCondition::IsNotImmune()
{
    return SelfCondition([](const Playable* playable) {
        if (const auto character = dynamic_cast<const Character*>(playable))
        {
            return !character->IsImmune();
        }

        return false;
    });
}

SelfCondition SelfCondition::IsNotUntouchable()
{
    return SelfCondition([](const Playable* playable) {
        return !playable->card->IsUntouchable();
    });
}

SelfCondition SelfCondition::IsFieldCount(int value, RelaSign relaSign)
{
    return SelfCondition([value, relaSign](const Playable* playable) {
        const int val =
            playable->player->GetFieldZone()->GetCountExceptUntouchables();

        return (relaSign == RelaSign::EQ && val == value) ||
               (relaSign == RelaSign::GEQ && val >= value) ||
               (relaSign == RelaSign::LEQ && val <= value);
    });
}

SelfCondition SelfCondition::IsOpFieldCount(int value, RelaSign relaSign)
{
    return SelfCondition([value, relaSign](const Playable* playable) {
        const int val = playable->player->opponent->GetFieldZone()
                            ->GetCountExceptUntouchables();

        return (relaSign == RelaSign::EQ && val == value) ||
               (relaSign == RelaSign::GEQ && val >= value) ||
               (relaSign == RelaSign::LEQ && val <= value);
    });
}

SelfCondition SelfCondition::IsFieldFull()
{
    return SelfCondition([](const Playable* playable) {
        return playable->player->GetFieldZone()->IsFull();
    });
}

SelfCondition SelfCondition::IsFieldNotFull()
{
    return SelfCondition([](const Playable* playable) {
        return !playable->player->GetFieldZone()->IsFull();
    });
}

SelfCondition SelfCondition::IsOpFieldNotFull()
{
    return SelfCondition([](const Playable* playable) {
        return !playable->player->opponent->GetFieldZone()->IsFull();
    });
}

SelfCondition SelfCondition::IsFieldNotEmpty()
{
    return SelfCondition([](const Playable* playable) {
        return !playable->player->GetFieldZone()->IsEmpty();
    });
}

SelfCondition SelfCondition::IsDamaged()
{
    return SelfCondition([](const Playable* playable) {
        if (const auto character = dynamic_cast<const Character*>(playable))
        {
            return character->GetDamage() > 0;
        }

        return false;
    });
}

SelfCondition SelfCondition::IsUndamaged()
{
    return SelfCondition([](const Playable* playable) {
        if (const auto character = dynamic_cast<const Character*>(playable))
        {
            return character->GetDamage() == 0;
        }

        return false;
    });
}

SelfCondition SelfCondition::IsWeaponEquipped()
{
    return SelfCondition([](const Playable* playable) {
        return playable->player->GetHero()->HasWeapon();
    });
}

SelfCondition SelfCondition::IsTreant()
{
    return SelfCondition([](const Playable* playable) {
        return playable->card->name == "Treant";
    });
}

SelfCondition SelfCondition::IsLackey()
{
    return SelfCondition(
        [](const Playable* playable) { return playable->card->IsLackey(); });
}

SelfCondition SelfCondition::IsPoison()
{
    return SelfCondition(
        [](const Playable* playable) { return playable->card->IsPoison(); });
}

SelfCondition SelfCondition::IsSilverHandRecruit()
{
    return SelfCondition([](const Playable* playable) {
        return playable->card->id == "CS2_101t";
    });
}

SelfCondition SelfCondition::IsRace(Race race)
{
    return SelfCondition([race](const Playable* playable) {
        return playable->card->GetRace() == race;
    });
}

SelfCondition SelfCondition::IsNotRace(Race race)
{
    return SelfCondition([race](const Playable* playable) {
        return playable->card->GetRace() != race;
    });
}

SelfCondition SelfCondition::IsControllingRace(Race race)
{
    return SelfCondition([race](const Playable* playable) {
        auto minions = playable->player->GetFieldZone()->GetAll();

        return std::any_of(minions.begin(), minions.end(),
                           [&](const Minion* minion) {
                               return minion->card->GetRace() == race;
                           });
    });
}

SelfCondition SelfCondition::IsOpControllingRace(Race race)
{
    return SelfCondition([race](const Playable* playable) {
        auto minions = playable->player->opponent->GetFieldZone()->GetAll();

        return std::any_of(minions.begin(), minions.end(),
                           [&](const Minion* minion) {
                               return minion->card->GetRace() == race;
                           });
    });
}

SelfCondition SelfCondition::IsControllingSecret()
{
    return SelfCondition([](const Playable* playable) {
        return !playable->player->GetSecretZone()->IsEmpty();
    });
}

SelfCondition SelfCondition::IsControllingQuest()
{
    return SelfCondition([](const Playable* playable) {
        return playable->player->GetSecretZone()->quest;
    });
}

SelfCondition SelfCondition::IsControllingStealthedMinion()
{
    return SelfCondition([](const Playable* playable) {
        auto minions = playable->player->GetFieldZone()->GetAll();

        return std::any_of(
            minions.begin(), minions.end(),
            [&](const Minion* minion) { return minion->HasStealth(); });
    });
}

SelfCondition SelfCondition::IsControllingLackey()
{
    return SelfCondition([](const Playable* playable) {
        auto minions = playable->player->GetFieldZone()->GetAll();

        return std::any_of(
            minions.begin(), minions.end(),
            [&](const Minion* minion) { return minion->card->IsLackey(); });
    });
}

SelfCondition SelfCondition::IsControllingColaqueShell()
{
    return SelfCondition([](const Playable* playable) {
        auto minions = playable->player->GetFieldZone()->GetAll();

        return std::any_of(minions.begin(), minions.end(),
                           [&](const Minion* minion) {
                               return minion->card->id == "TSC_026t";
                           });
    });
}

SelfCondition SelfCondition::IsHoldingSecret()
{
    return SelfCondition([](const Playable* playable) {
        auto cards = playable->player->GetHandZone()->GetAll();

        return std::any_of(cards.begin(), cards.end(),
                           [&](const Playable* handCard) {
                               return handCard->card->IsSecret();
                           });
    });
}

SelfCondition SelfCondition::IsHoldingRace(Race race)
{
    return SelfCondition([race](const Playable* playable) {
        auto cards = playable->player->GetHandZone()->GetAll();

        return std::any_of(
            cards.begin(), cards.end(), [&](const Playable* handCard) {
                return handCard->card->GetCardType() == CardType::MINION &&
                       handCard->card->GetRace() == race;
            });
    });
}

SelfCondition SelfCondition::IsHoldingSpell(SpellSchool spellSchool)
{
    return SelfCondition([spellSchool](const Playable* playable) {
        auto cards = playable->player->GetHandZone()->GetAll();

        return std::any_of(
            cards.begin(), cards.end(), [&](const Playable* handCard) {
                return handCard->card->GetCardType() == CardType::SPELL &&
                       handCard->card->GetSpellSchool() == spellSchool;
            });
    });
}

SelfCondition SelfCondition::IsAnotherClassCard()
{
    return SelfCondition([](const Playable* playable) {
        if (playable->card->GetCardClass() != CardClass::NEUTRAL &&
            playable->card->GetCardClass() !=
                playable->player->GetHero()->card->GetCardClass())
        {
            return true;
        }
        return false;
    });
}

SelfCondition SelfCondition::IsHoldingAnotherClassCard()
{
    return SelfCondition([](const Playable* playable) {
        auto cards = playable->player->GetHandZone()->GetAll();

        return std::any_of(
            cards.begin(), cards.end(), [&](const Playable* handCard) {
                return handCard->card->GetCardClass() != CardClass::NEUTRAL &&
                       handCard->card->GetCardClass() !=
                           playable->player->GetHero()->card->GetCardClass();
            });
    });
}

SelfCondition SelfCondition::IsHoldingAnyNonClassCard(CardClass cardClass)
{
    return SelfCondition([&cardClass](const Playable* playable) {
        auto cards = playable->player->GetHandZone()->GetAll();

        return std::any_of(
            cards.begin(), cards.end(), [&](const Playable* handCard) {
                return handCard->card->GetCardClass() != cardClass;
            });
    });
}

SelfCondition SelfCondition::IsCardID(std::string_view cardID)
{
    return SelfCondition([cardID](const Playable* playable) {
        return playable->card->id == cardID;
    });
}

SelfCondition SelfCondition::IsMinion()
{
    return SelfCondition([](const Playable* playable) {
        return dynamic_cast<const Minion*>(playable);
    });
}

SelfCondition SelfCondition::IsSpell()
{
    return SelfCondition([](const Playable* playable) {
        return dynamic_cast<const Spell*>(playable);
    });
}

SelfCondition SelfCondition::IsNatureSpell()
{
    return SelfCondition([](const Playable* playable) {
        if (const auto spell = dynamic_cast<const Spell*>(playable))
        {
            return spell->GetSpellSchool() == SpellSchool::NATURE;
        }

        return false;
    });
}

SelfCondition SelfCondition::IsFrostSpell()
{
    return SelfCondition([](const Playable* playable) {
        if (const auto spell = dynamic_cast<const Spell*>(playable))
        {
            return spell->GetSpellSchool() == SpellSchool::FROST;
        }

        return false;
    });
}

SelfCondition SelfCondition::IsHolySpell()
{
    return SelfCondition([](const Playable* playable) {
        if (const auto spell = dynamic_cast<const Spell*>(playable))
        {
            return spell->GetSpellSchool() == SpellSchool::HOLY;
        }

        return false;
    });
}

SelfCondition SelfCondition::IsShadowSpell()
{
    return SelfCondition([](const Playable* playable) {
        if (const auto spell = dynamic_cast<const Spell*>(playable))
        {
            return spell->GetSpellSchool() == SpellSchool::SHADOW;
        }

        return false;
    });
}

SelfCondition SelfCondition::IsFelSpell()
{
    return SelfCondition([](const Playable* playable) {
        if (const auto spell = dynamic_cast<const Spell*>(playable))
        {
            return spell->GetSpellSchool() == SpellSchool::FEL;
        }

        return false;
    });
}

SelfCondition SelfCondition::IsWeapon()
{
    return SelfCondition([](const Playable* playable) {
        return dynamic_cast<const Weapon*>(playable);
    });
}

SelfCondition SelfCondition::IsSecret()
{
    return SelfCondition([](const Playable* playable) {
        return dynamic_cast<const Spell*>(playable) &&
               playable->GetGameTag(GameTag::SECRET) == 1;
    });
}

SelfCondition SelfCondition::IsChooseOneCard()
{
    return SelfCondition(
        [](const Playable* playable) { return playable->HasChooseOne(); });
}

SelfCondition SelfCondition::IsOutcastCard()
{
    return SelfCondition(
        [](const Playable* playable) { return playable->HasOutcast(); });
}

SelfCondition SelfCondition::IsFrozen()
{
    return SelfCondition([](const Playable* playable) {
        if (const auto character = dynamic_cast<const Character*>(playable))
        {
            return character->IsFrozen();
        }

        return false;
    });
}

SelfCondition SelfCondition::HasHeroArmor()
{
    return SelfCondition([](const Playable* playable) {
        return playable->player->GetHero()->GetArmor() > 0;
    });
}

SelfCondition SelfCondition::HasSpellPower()
{
    return SelfCondition([](const Playable* playable) {
        if (const auto minion = dynamic_cast<const Minion*>(playable))
        {
            return minion->GetSpellPower() > 0;
        }

        return false;
    });
}

SelfCondition SelfCondition::HasTaunt()
{
    return SelfCondition([](const Playable* playable) {
        if (const auto minion = dynamic_cast<const Minion*>(playable))
        {
            return minion->HasTaunt();
        }

        return false;
    });
}

SelfCondition SelfCondition::HasRush()
{
    return SelfCondition([](const Playable* playable) {
        if (const auto minion = dynamic_cast<const Minion*>(playable))
        {
            return minion->HasRush();
        }

        return false;
    });
}

SelfCondition SelfCondition::HasDeathrattle()
{
    return SelfCondition([](const Playable* playable) {
        if (const auto minion = dynamic_cast<const Minion*>(playable))
        {
            return minion->HasDeathrattle();
        }

        return false;
    });
}

SelfCondition SelfCondition::HasNotStealth()
{
    return SelfCondition([](const Playable* playable) {
        if (const auto minion = dynamic_cast<const Minion*>(playable))
        {
            return !minion->HasStealth();
        }

        return false;
    });
}

SelfCondition SelfCondition::HasWindfury()
{
    return SelfCondition([](const Playable* playable) {
        if (const auto character = dynamic_cast<const Character*>(playable))
        {
            return character->HasWindfury();
        }

        return false;
    });
}

SelfCondition SelfCondition::HasReborn()
{
    return SelfCondition([](const Playable* playable) {
        if (const auto minion = dynamic_cast<const Minion*>(playable))
        {
            return minion->HasReborn();
        }

        return false;
    });
}

SelfCondition SelfCondition::HasFrenzy()
{
    return SelfCondition([](const Playable* playable) {
        if (const auto minion = dynamic_cast<const Minion*>(playable))
        {
            return minion->HasFrenzy();
        }

        return false;
    });
}

SelfCondition SelfCondition::HasInvokedTwice()
{
    return SelfCondition([](const Playable* playable) {
        return playable->player->GetInvoke() >= 2;
    });
}

SelfCondition SelfCondition::HasMinionInHand()
{
    return SelfCondition([](const Playable* playable) {
        auto cards = playable->player->GetHandZone()->GetAll();

        return std::any_of(
            cards.begin(), cards.end(), [&](const Playable* handCard) {
                return handCard->card->GetCardType() == CardType::MINION;
            });
    });
}

SelfCondition SelfCondition::IsOverloadCard()
{
    return SelfCondition([](const Playable* playable) {
        if (playable->GetGameTag(GameTag::OVERLOAD) >= 1)
        {
            return true;
        }

        return false;
    });
}

SelfCondition SelfCondition::IsComboCard()
{
    return SelfCondition([](const Playable* playable) {
        if (playable->GetGameTag(GameTag::COMBO) == 1)
        {
            return true;
        }

        return false;
    });
}

SelfCondition SelfCondition::IsLowestCostMinion()
{
    return SelfCondition([](const Playable* playable) {
        int lowestCost = std::numeric_limits<int>::max();

        for (const auto& handCard : playable->player->GetHandZone()->GetAll())
        {
            if (handCard->card->GetCardType() == CardType::MINION &&
                handCard->GetCost() < lowestCost)
            {
                lowestCost = handCard->GetCost();
            }
        }

        return playable->card->GetCardType() == CardType::MINION &&
               playable->GetCost() == lowestCost;
    });
}

SelfCondition SelfCondition::HasPlayerSpellPower()
{
    return SelfCondition([](const Playable* playable) {
        return playable->player->GetCurrentSpellPower() > 0;
    });
}

SelfCondition SelfCondition::IsAttackThisTurn()
{
    return SelfCondition([](const Playable* playable) {
        return playable->GetGameTag(GameTag::NUM_ATTACKS_THIS_TURN) > 0;
    });
}

SelfCondition SelfCondition::IsCastSpellLastTurn()
{
    return SelfCondition([](const Playable* playable) {
        return playable->player->GetGameTag(
                   GameTag::NUM_SPELLS_CAST_LAST_TURN) > 0;
    });
}

SelfCondition SelfCondition::CardsPlayedThisTurn(int num)
{
    return SelfCondition([num](const Playable* playable) {
        return playable->player->GetNumCardsPlayedThisTurn() == num;
    });
}

SelfCondition SelfCondition::MinionsPlayedThisTurn(int num)
{
    return SelfCondition([num](const Playable* playable) {
        return playable->player->GetNumMinionsPlayedThisTurn() == num;
    });
}

SelfCondition SelfCondition::TauntMinionsPlayedThisTurn(int num)
{
    return SelfCondition([num](const Playable* playable) {
        return playable->player->GetNumTauntMinionsPlayedThisTurn() == num;
    });
}

SelfCondition SelfCondition::SpellsCastThisTurn(int num)
{
    return SelfCondition([num](const Playable* playable) {
        return playable->player->GetNumSpellsCastThisTurn() == num;
    });
}

SelfCondition SelfCondition::HealthRestoredThisTurn()
{
    return SelfCondition([](const Playable* playable) {
        return playable->player->GetAmountHealedThisTurn() > 0;
    });
}

SelfCondition SelfCondition::IsPlayElementalMinionLastTurn()
{
    return SelfCondition([](const Playable* playable) {
        return playable->player->GetNumElementalPlayedLastTurn() > 0;
    });
}

SelfCondition SelfCondition::IsNotPlayElementalMinionThisTurn()
{
    return SelfCondition([](const Playable* playable) {
        return playable->player->GetNumElementalPlayedThisTurn() == 0;
    });
}

SelfCondition SelfCondition::IsCost(int value, RelaSign relaSign)
{
    return SelfCondition([value, relaSign](const Playable* playable) {
        const int val = playable->GetCost();

        return (relaSign == RelaSign::EQ && val == value) ||
               (relaSign == RelaSign::GEQ && val >= value) ||
               (relaSign == RelaSign::LEQ && val <= value);
    });
}

SelfCondition SelfCondition::IsTagValue(GameTag tag, int value,
                                        RelaSign relaSign)
{
    return SelfCondition([tag, value, relaSign](const Playable* playable) {
        return (relaSign == RelaSign::EQ &&
                playable->GetGameTag(tag) == value) ||
               (relaSign == RelaSign::GEQ &&
                playable->GetGameTag(tag) >= value) ||
               (relaSign == RelaSign::LEQ &&
                playable->GetGameTag(tag) <= value);
    });
}

SelfCondition SelfCondition::IsName(const std::string& name, bool isEqual)
{
    return SelfCondition([name, isEqual](const Playable* playable) {
        return !((playable->card->name == name) ^ isEqual);
    });
}

SelfCondition SelfCondition::IsStackNum(int value, RelaSign relaSign, int index)
{
    return SelfCondition([value, relaSign, index](const Playable* playable) {
        const auto& stack = playable->game->taskStack;
        const auto num = index == 0 ? stack.num[0] : stack.num[1];

        return (relaSign == RelaSign::EQ && num == value) ||
               (relaSign == RelaSign::GEQ && num >= value) ||
               (relaSign == RelaSign::LEQ && num <= value);
    });
}

SelfCondition SelfCondition::IsOddAttackMinion()
{
    return SelfCondition([](const Playable* playable) {
        if (const auto minion = dynamic_cast<const Minion*>(playable))
        {
            return minion->GetAttack() % 2 == 1;
        }

        return false;
    });
}

SelfCondition SelfCondition::IsAttack(int value, RelaSign relaSign)
{
    return SelfCondition([value, relaSign](const Playable* playable) {
        if (const auto character = dynamic_cast<const Character*>(playable))
        {
            return (relaSign == RelaSign::EQ &&
                    character->GetAttack() == value) ||
                   (relaSign == RelaSign::GEQ &&
                    character->GetAttack() >= value) ||
                   (relaSign == RelaSign::LEQ &&
                    character->GetAttack() <= value);
        }

        return false;
    });
}

SelfCondition SelfCondition::IsEventSourceAttack(int value, RelaSign relaSign)
{
    return SelfCondition([value, relaSign](const Playable* playable) {
        if (const auto eventData = playable->game->currentEventData.get();
            eventData)
        {
            if (const auto character =
                    dynamic_cast<Character*>(eventData->eventSource))
            {
                return (relaSign == RelaSign::EQ &&
                        character->GetAttack() == value) ||
                       (relaSign == RelaSign::GEQ &&
                        character->GetAttack() >= value) ||
                       (relaSign == RelaSign::LEQ &&
                        character->GetAttack() <= value);
            }
        }

        return false;
    });
}

SelfCondition SelfCondition::IsHealth(int value, RelaSign relaSign)
{
    return SelfCondition([value, relaSign](const Playable* playable) {
        if (const auto character = dynamic_cast<const Character*>(playable))
        {
            return (relaSign == RelaSign::EQ &&
                    character->GetHealth() == value) ||
                   (relaSign == RelaSign::GEQ &&
                    character->GetHealth() >= value) ||
                   (relaSign == RelaSign::LEQ &&
                    character->GetHealth() <= value);
        }

        return false;
    });
}

SelfCondition SelfCondition::HasTarget()
{
    return SelfCondition(
        [](const Playable* playable) { return playable->GetCardTarget() > 0; });
}

SelfCondition SelfCondition::IsProposedDefender(CardType cardType)
{
    return IsEventTargetIs(cardType);
}

SelfCondition SelfCondition::IsDefenderDead()
{
    return SelfCondition([](const Playable* playable) {
        if (const auto eventData = playable->game->currentEventData.get();
            eventData)
        {
            if (const auto eventTarget = eventData->eventTarget; eventTarget)
            {
                return eventTarget->isDestroyed;
            }
        }

        return false;
    });
}

SelfCondition SelfCondition::IsHeroFatalPreDamaged()
{
    return SelfCondition([](const Playable* playable) {
        if (const auto eventData = playable->game->currentEventData.get();
            eventData)
        {
            return eventData->eventNumber >=
                   playable->player->GetHero()->GetHealth();
        }

        return false;
    });
}

SelfCondition SelfCondition::IsEventSourceFriendly()
{
    return SelfCondition([](const Playable* playable) {
        if (const auto eventData = playable->game->currentEventData.get();
            eventData)
        {
            return eventData->eventSource->player == playable->player;
        }

        return false;
    });
}

SelfCondition SelfCondition::IsEventTargetIs(CardType cardType)
{
    return SelfCondition([cardType](const Playable* playable) {
        if (const auto eventData = playable->game->currentEventData.get();
            eventData)
        {
            return eventData->eventTarget->card->GetCardType() == cardType;
        }

        return false;
    });
}

SelfCondition SelfCondition::IsEventTargetFieldNotFull()
{
    return SelfCondition([](const Playable* playable) {
        if (const auto eventData = playable->game->currentEventData.get();
            eventData)
        {
            return !eventData->eventTarget->player->GetFieldZone()->IsFull();
        }

        return false;
    });
}

SelfCondition SelfCondition::IsSpellTargetingMinion()
{
    return SelfCondition([](const Playable* playable) {
        const auto iter =
            playable->game->entityList.find(playable->GetCardTarget());

        return playable->card->GetCardType() == CardType::SPELL &&
               iter->second->card->GetCardType() == CardType::MINION;
    });
}

SelfCondition SelfCondition::IsInZone(ZoneType zone)
{
    return SelfCondition([zone](const Playable* playable) {
        return playable->GetZoneType() == zone;
    });
}

SelfCondition SelfCondition::IsMyTurn()
{
    return SelfCondition([](const Playable* playable) {
        return playable->player == playable->game->GetCurrentPlayer();
    });
}

SelfCondition SelfCondition::IsEnemyTurn()
{
    return SelfCondition([](const Playable* playable) {
        return playable->player != playable->game->GetCurrentPlayer();
    });
}

SelfCondition SelfCondition::IsMyHeroUndamagedEnemyTurn()
{
    return SelfCondition([](const Playable* playable) {
        return playable->player != playable->game->GetCurrentPlayer() &&
               playable->player->GetHero()->damageTakenThisTurn == 0;
    });
}

SelfCondition SelfCondition::IsOverloaded()
{
    return SelfCondition([](const Playable* playable) {
        return playable->player->GetOverloadLocked() > 0 ||
               playable->player->GetOverloadOwed() > 0;
    });
}

SelfCondition SelfCondition::HasAtLeastManaCrystal(int num)
{
    return SelfCondition([num](const Playable* playable) {
        return playable->player->GetTotalMana() >= num;
    });
}

SelfCondition SelfCondition::IsManaCrystalFull()
{
    return SelfCondition([](const Playable* playable) {
        return playable->player->GetTotalMana() == 10;
    });
}

SelfCondition SelfCondition::IsUnspentMana()
{
    return SelfCondition([](const Playable* playable) {
        return playable->player->GetRemainingMana() > 0;
    });
}

SelfCondition SelfCondition::IsUsedHeroPowerThisTurn()
{
    return SelfCondition([](const Playable* playable) {
        return playable->player->GetHero()->heroPower->IsExhausted();
    });
}

SelfCondition SelfCondition::IsNoDuplicateInDeck()
{
    return SelfCondition([](const Playable* playable) {
        auto cards = playable->player->GetDeckZone()->GetAll();
        std::map<std::string, int> result;

        std::for_each(
            cards.begin(), cards.end(),
            [&result](const Playable* val) { result[val->card->id]++; });

        return std::none_of(result.begin(), result.end(),
                            [&](const std::pair<const std::string, int>& ret) {
                                return ret.second >= 2;
                            });
    });
}

SelfCondition SelfCondition::HasNoMinionsInDeck()
{
    return SelfCondition([](const Playable* playable) {
        auto cards = playable->player->GetDeckZone()->GetAll();

        return std::none_of(
            cards.begin(), cards.end(), [&](const Playable* deckCard) {
                return deckCard->card->GetCardType() == CardType::MINION;
            });
    });
}

SelfCondition SelfCondition::MaximumCardsInDeck(int value)
{
    return SelfCondition([value](const Playable* playable) {
        return playable->player->GetDeckZone()->GetCount() <= value;
    });
}

SelfCondition SelfCondition::HasNoNeutralCardsInDeck()
{
    return SelfCondition([](const Playable* playable) {
        auto cards = playable->player->GetDeckZone()->GetAll();

        return std::none_of(
            cards.begin(), cards.end(), [&](const Playable* deckCard) {
                return deckCard->card->GetCardClass() == CardClass::NEUTRAL;
            });
    });
}

SelfCondition SelfCondition::HasAtLeastCardInHand(int num)
{
    return SelfCondition([num](const Playable* playable) {
        return playable->player->GetHandZone()->GetCount() >= num;
    });
}

SelfCondition SelfCondition::IsLeftOrRightMostCardInHand()
{
    return SelfCondition([](const Playable* playable) {
        return playable->GetGameTag(GameTag::LEFT_OR_RIGHT_MOST_CARD_IN_HAND) >
               0;
    });
}

SelfCondition SelfCondition::HasNotSpellDamageOnHero()
{
    return SelfCondition([](const Playable* playable) {
        return playable->player->GetCurrentSpellPower() == 0;
    });
}

SelfCondition SelfCondition::Has5MoreCostSpellInHand()
{
    return SelfCondition([](const Playable* playable) {
        auto cards = playable->player->GetHandZone()->GetAll();

        return std::any_of(
            cards.begin(), cards.end(), [&](const Playable* handCard) {
                return handCard->card->GetCardType() == CardType::SPELL &&
                       handCard->GetCost() >= 5;
            });
    });
}

SelfCondition SelfCondition::Has5MoreCostDemonInHand()
{
    return SelfCondition([](const Playable* playable) {
        auto cards = playable->player->GetHandZone()->GetAll();

        return std::any_of(
            cards.begin(), cards.end(), [&](const Playable* handCard) {
                return handCard->card->GetCardType() == CardType::MINION &&
                       handCard->card->GetRace() == Race::DEMON &&
                       handCard->GetCost() >= 5;
            });
    });
}

SelfCondition SelfCondition::Cast5MoreCostSpellInThisTurn()
{
    return SelfCondition([](const Playable* playable) {
        auto cards = playable->player->cardsPlayedThisTurn;

        return std::any_of(cards.begin(), cards.end(), [&](const Card* card) {
            return card->GetCardType() == CardType::SPELL &&
                   card->GetCost() >= 5;
        });
    });
}

SelfCondition SelfCondition::CastFelSpellInThisTurn()
{
    return SelfCondition([](const Playable* playable) {
        auto cards = playable->player->cardsPlayedThisTurn;

        return std::any_of(cards.begin(), cards.end(), [&](const Card* card) {
            return card->GetCardType() == CardType::SPELL &&
                   card->GetSpellSchool() >= SpellSchool::FEL;
        });
    });
}

SelfCondition SelfCondition::ControlThisCard(int num)
{
    return SelfCondition([num](const Playable* playable) {
        int count = 0;

        for (const auto& deckCard : playable->player->GetFieldZone()->GetAll())
        {
            if (playable->card->dbfID == deckCard->card->dbfID)
            {
                ++count;
            }
        }

        return count >= num;
    });
}

SelfCondition SelfCondition::HasSoulFragmentInDeck()
{
    return SelfCondition([](const Playable* playable) {
        auto cards = playable->player->GetDeckZone()->GetAll();

        return std::any_of(cards.begin(), cards.end(),
                           [&](const Playable* deckCard) {
                               return deckCard->card->dbfID == 59723;
                           });
    });
}

SelfCondition SelfCondition::NotExistInSecretZone()
{
    return SelfCondition([](const Playable* playable) {
        auto secrets = playable->player->GetSecretZone()->GetAll();

        return std::none_of(
            secrets.begin(), secrets.end(), [&](const Spell* secretCard) {
                return secretCard->card->dbfID == playable->card->dbfID;
            });
    });
}

SelfCondition SelfCondition::CheckThreshold(RelaSign relaSign)
{
    return SelfCondition([relaSign](const Playable* playable) {
        const int thresholdTagID =
            playable->GetGameTag(GameTag::PLAYER_TAG_THRESHOLD_TAG_ID);
        const int thresholdValue =
            playable->GetGameTag(GameTag::PLAYER_TAG_THRESHOLD_VALUE);

        int currentValue = 0;
        if (thresholdTagID == 958)
        {
            currentValue = playable->player->GetAmountHealedThisGame();
        }

        if (relaSign == RelaSign::GEQ)
        {
            return currentValue >= thresholdValue;
        }
        else if (relaSign == RelaSign::EQ)
        {
            return currentValue == thresholdValue;
        }
        else
        {
            return currentValue <= thresholdValue;
        }
    });
}

bool SelfCondition::Evaluate(Playable* owner) const
{
    return m_func(owner);
}
}  // namespace RosettaStone::PlayMode
