// This code is based on Sabberstone project.
// Copyright (c) 2017-2021 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2021 Chris Ohk

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
    return SelfCondition([](Playable* playable) {
        const auto iter =
            playable->game->entityList.find(playable->GetCardTarget());
        return playable->player == iter->second->player;
    });
}

SelfCondition SelfCondition::IsNotStartInDeck()
{
    return SelfCondition([](Playable* playable) {
        const auto entityID = playable->GetGameTag(GameTag::ENTITY_ID);
        const auto curDeckCount = playable->player->GetDeckZone()->GetCount();
        const auto opDeckCount =
            playable->player->opponent->GetDeckZone()->GetCount();
        return entityID > curDeckCount + opDeckCount + 7;
    });
}

SelfCondition SelfCondition::IsHandEmpty()
{
    return SelfCondition([](Playable* playable) {
        return playable->player->GetHandZone()->IsEmpty();
    });
}

SelfCondition SelfCondition::IsHandFull()
{
    return SelfCondition([](Playable* playable) {
        return playable->player->GetHandZone()->IsFull();
    });
}

SelfCondition SelfCondition::IsHandNotFull()
{
    return SelfCondition([](Playable* playable) {
        return !playable->player->GetHandZone()->IsFull();
    });
}

SelfCondition SelfCondition::IsDeckEmpty()
{
    return SelfCondition([](Playable* playable) {
        return playable->player->GetDeckZone()->IsEmpty();
    });
}

SelfCondition SelfCondition::IsSecretFull()
{
    return SelfCondition([](Playable* playable) {
        return playable->player->GetSecretZone()->IsFull();
    });
}

SelfCondition SelfCondition::IsHeroPowerCard(const std::string& cardID)
{
    return SelfCondition([cardID](Playable* playable) {
        return playable->player->GetHero()->heroPower->card->id == cardID;
    });
}

SelfCondition SelfCondition::IsBattlecryCard()
{
    return SelfCondition(
        [](Playable* playable) { return playable->HasBattlecry(); });
}

SelfCondition SelfCondition::IsDeathrattleCard()
{
    return SelfCondition(
        [](Playable* playable) { return playable->HasDeathrattle(); });
}

SelfCondition SelfCondition::IsDiscoverCard()
{
    return SelfCondition(
        [](Playable* playable) { return playable->HasDiscover(); });
}

SelfCondition SelfCondition::IsGalakrondHero()
{
    return SelfCondition(
        [](Playable* playable) { return playable->card->IsGalakrond(); });
}

SelfCondition SelfCondition::IsAwaken()
{
    return SelfCondition([](Playable* playable) {
        const auto minion = dynamic_cast<Minion*>(playable);
        if (minion)
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
        [](Playable* playable) { return playable->isDestroyed; });
}

SelfCondition SelfCondition::IsNotDead()
{
    return SelfCondition(
        [](Playable* playable) { return !playable->isDestroyed; });
}

SelfCondition SelfCondition::IsNotImmune()
{
    return SelfCondition([](Playable* playable) {
        const auto character = dynamic_cast<Character*>(playable);
        if (!character)
        {
            return false;
        }

        return !character->IsImmune();
    });
}

SelfCondition SelfCondition::IsNotUntouchable()
{
    return SelfCondition(
        [](Playable* playable) { return !playable->card->IsUntouchable(); });
}

SelfCondition SelfCondition::IsFieldCount(int value, RelaSign relaSign)
{
    return SelfCondition([value, relaSign](Playable* playable) {
        const int val =
            playable->player->GetFieldZone()->GetCountExceptUntouchables();

        return (relaSign == RelaSign::EQ && val == value) ||
               (relaSign == RelaSign::GEQ && val >= value) ||
               (relaSign == RelaSign::LEQ && val <= value);
    });
}

SelfCondition SelfCondition::IsOpFieldCount(int value, RelaSign relaSign)
{
    return SelfCondition([value, relaSign](Playable* playable) {
        const int val = playable->player->opponent->GetFieldZone()
                            ->GetCountExceptUntouchables();

        return (relaSign == RelaSign::EQ && val == value) ||
               (relaSign == RelaSign::GEQ && val >= value) ||
               (relaSign == RelaSign::LEQ && val <= value);
    });
}

SelfCondition SelfCondition::IsFieldFull()
{
    return SelfCondition([](Playable* playable) {
        return playable->player->GetFieldZone()->IsFull();
    });
}

SelfCondition SelfCondition::IsFieldNotFull()
{
    return SelfCondition([](Playable* playable) {
        return !playable->player->GetFieldZone()->IsFull();
    });
}

SelfCondition SelfCondition::IsOpFieldNotFull()
{
    return SelfCondition([](Playable* playable) {
        return !playable->player->opponent->GetFieldZone()->IsFull();
    });
}

SelfCondition SelfCondition::IsFieldNotEmpty()
{
    return SelfCondition([](Playable* playable) {
        return !playable->player->GetFieldZone()->IsEmpty();
    });
}

SelfCondition SelfCondition::IsDamaged()
{
    return SelfCondition([](Playable* playable) {
        const auto character = dynamic_cast<Character*>(playable);
        if (!character)
        {
            return false;
        }

        return character->GetDamage() > 0;
    });
}

SelfCondition SelfCondition::IsUndamaged()
{
    return SelfCondition([](Playable* playable) {
        const auto character = dynamic_cast<Character*>(playable);
        if (!character)
        {
            return false;
        }

        return character->GetDamage() == 0;
    });
}

SelfCondition SelfCondition::IsWeaponEquipped()
{
    return SelfCondition([](Playable* playable) {
        return playable->player->GetHero()->HasWeapon();
    });
}

SelfCondition SelfCondition::IsTreant()
{
    return SelfCondition(
        [](Playable* playable) { return playable->card->name == "Treant"; });
}

SelfCondition SelfCondition::IsLackey()
{
    return SelfCondition(
        [](Playable* playable) { return playable->card->IsLackey(); });
}

SelfCondition SelfCondition::IsPoison()
{
    return SelfCondition(
        [](Playable* playable) { return playable->card->IsPoison(); });
}

SelfCondition SelfCondition::IsSilverHandRecruit()
{
    return SelfCondition(
        [](Playable* playable) { return playable->card->id == "CS2_101t"; });
}

SelfCondition SelfCondition::IsRace(Race race)
{
    return SelfCondition([race](Playable* playable) {
        return playable->card->GetRace() == race;
    });
}

SelfCondition SelfCondition::IsNotRace(Race race)
{
    return SelfCondition([race](Playable* playable) {
        return playable->card->GetRace() != race;
    });
}

SelfCondition SelfCondition::IsControllingRace(Race race)
{
    return SelfCondition([race](Playable* playable) {
        for (auto& minion : playable->player->GetFieldZone()->GetAll())
        {
            if (minion->card->GetRace() == race)
            {
                return true;
            }
        }

        return false;
    });
}

SelfCondition SelfCondition::IsOpControllingRace(Race race)
{
    return SelfCondition([race](Playable* playable) {
        for (auto& minion :
             playable->player->opponent->GetFieldZone()->GetAll())
        {
            if (minion->card->GetRace() == race)
            {
                return true;
            }
        }

        return false;
    });
}

SelfCondition SelfCondition::IsControllingSecret()
{
    return SelfCondition([](Playable* playable) {
        return !playable->player->GetSecretZone()->IsEmpty();
    });
}

SelfCondition SelfCondition::IsControllingQuest()
{
    return SelfCondition([](Playable* playable) {
        return playable->player->GetSecretZone()->quest != nullptr;
    });
}

SelfCondition SelfCondition::IsControllingStealthedMinion()
{
    return SelfCondition([](Playable* playable) {
        for (auto& minion : playable->player->GetFieldZone()->GetAll())
        {
            if (minion->HasStealth() == true)
            {
                return true;
            }
        }

        return false;
    });
}

SelfCondition SelfCondition::IsControllingLackey()
{
    return SelfCondition([](Playable* playable) {
        for (auto& minion : playable->player->GetFieldZone()->GetAll())
        {
            if (minion->card->IsLackey())
            {
                return true;
            }
        }

        return false;
    });
}

SelfCondition SelfCondition::IsControllingColaqueShell()
{
    return SelfCondition([](Playable* playable) {
        for (auto& minion : playable->player->GetFieldZone()->GetAll())
        {
            if (minion->card->id == "TSC_026t")
            {
                return true;
            }
        }

        return false;
    });
}

SelfCondition SelfCondition::IsHoldingSecret()
{
    return SelfCondition([](Playable* playable) {
        for (auto& handCard : playable->player->GetHandZone()->GetAll())
        {
            if (handCard->card->IsSecret() == true)
            {
                return true;
            }
        }

        return false;
    });
}

SelfCondition SelfCondition::IsHoldingRace(Race race)
{
    return SelfCondition([race](Playable* playable) {
        for (auto& handCard : playable->player->GetHandZone()->GetAll())
        {
            if (handCard->card->GetCardType() == CardType::MINION &&
                handCard->card->GetRace() == race)
            {
                return true;
            }
        }

        return false;
    });
}

SelfCondition SelfCondition::IsHoldingSpell(SpellSchool spellSchool)
{
    return SelfCondition([spellSchool](Playable* playable) {
        for (auto& handCard : playable->player->GetHandZone()->GetAll())
        {
            if (handCard->card->GetCardType() == CardType::SPELL &&
                handCard->card->GetSpellSchool() == spellSchool)
            {
                return true;
            }
        }

        return false;
    });
}

SelfCondition SelfCondition::IsAnotherClassCard()
{
    return SelfCondition([](Playable* playable) {
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
    return SelfCondition([](Playable* playable) {
        for (auto& handCard : playable->player->GetHandZone()->GetAll())
        {
            if (handCard->card->GetCardClass() != CardClass::NEUTRAL &&
                handCard->card->GetCardClass() !=
                    playable->player->GetHero()->card->GetCardClass())
            {
                return true;
            }
        }

        return false;
    });
}

SelfCondition SelfCondition::IsCardID(std::string_view cardID)
{
    return SelfCondition(
        [cardID](Playable* playable) { return playable->card->id == cardID; });
}

SelfCondition SelfCondition::IsMinion()
{
    return SelfCondition([](Playable* playable) {
        return dynamic_cast<Minion*>(playable) != nullptr;
    });
}

SelfCondition SelfCondition::IsSpell()
{
    return SelfCondition([](Playable* playable) {
        return dynamic_cast<Spell*>(playable) != nullptr;
    });
}

SelfCondition SelfCondition::IsNatureSpell()
{
    return SelfCondition([](Playable* playable) {
        auto spell = dynamic_cast<Spell*>(playable);
        if (!spell)
        {
            return false;
        }

        return spell->GetSpellSchool() == SpellSchool::NATURE;
    });
}

SelfCondition SelfCondition::IsFrostSpell()
{
    return SelfCondition([](Playable* playable) {
        auto spell = dynamic_cast<Spell*>(playable);
        if (!spell)
        {
            return false;
        }

        return spell->GetSpellSchool() == SpellSchool::FROST;
    });
}

SelfCondition SelfCondition::IsHolySpell()
{
    return SelfCondition([](Playable* playable) {
        auto spell = dynamic_cast<Spell*>(playable);
        if (!spell)
        {
            return false;
        }

        return spell->GetSpellSchool() == SpellSchool::HOLY;
    });
}

SelfCondition SelfCondition::IsShadowSpell()
{
    return SelfCondition([](Playable* playable) {
        auto spell = dynamic_cast<Spell*>(playable);
        if (!spell)
        {
            return false;
        }

        return spell->GetSpellSchool() == SpellSchool::SHADOW;
    });
}

SelfCondition SelfCondition::IsFelSpell()
{
    return SelfCondition([](Playable* playable) {
        auto spell = dynamic_cast<Spell*>(playable);
        if (!spell)
        {
            return false;
        }

        return spell->GetSpellSchool() == SpellSchool::FEL;
    });
}

SelfCondition SelfCondition::IsWeapon()
{
    return SelfCondition([](Playable* playable) {
        return dynamic_cast<Weapon*>(playable) != nullptr;
    });
}

SelfCondition SelfCondition::IsSecret()
{
    return SelfCondition([](Playable* playable) {
        return dynamic_cast<Spell*>(playable) != nullptr &&
               playable->GetGameTag(GameTag::SECRET) == 1;
    });
}

SelfCondition SelfCondition::IsChooseOneCard()
{
    return SelfCondition(
        [](Playable* playable) { return playable->HasChooseOne(); });
}

SelfCondition SelfCondition::IsOutcastCard()
{
    return SelfCondition(
        [](Playable* playable) { return playable->HasOutcast(); });
}

SelfCondition SelfCondition::IsFrozen()
{
    return SelfCondition([](Playable* playable) {
        const auto character = dynamic_cast<Character*>(playable);
        if (!character)
        {
            return false;
        }

        return character->IsFrozen();
    });
}

SelfCondition SelfCondition::HasHeroArmor()
{
    return SelfCondition([](Playable* playable) {
        return playable->player->GetHero()->GetArmor() > 0;
    });
}

SelfCondition SelfCondition::HasSpellPower()
{
    return SelfCondition([](Playable* playable) {
        const auto minion = dynamic_cast<Minion*>(playable);
        if (!minion)
        {
            return false;
        }

        return minion->GetSpellPower() > 0;
    });
}

SelfCondition SelfCondition::HasTaunt()
{
    return SelfCondition([](Playable* playable) {
        const auto minion = dynamic_cast<Minion*>(playable);
        if (!minion)
        {
            return false;
        }

        return minion->HasTaunt();
    });
}

SelfCondition SelfCondition::HasRush()
{
    return SelfCondition([](Playable* playable) {
        const auto minion = dynamic_cast<Minion*>(playable);
        if (!minion)
        {
            return false;
        }

        return minion->HasRush();
    });
}

SelfCondition SelfCondition::HasDeathrattle()
{
    return SelfCondition([](Playable* playable) {
        const auto minion = dynamic_cast<Minion*>(playable);
        if (!minion)
        {
            return false;
        }

        return minion->HasDeathrattle();
    });
}

SelfCondition SelfCondition::HasNotStealth()
{
    return SelfCondition([](Playable* playable) {
        const auto minion = dynamic_cast<Minion*>(playable);
        if (!minion)
        {
            return false;
        }

        return !minion->HasStealth();
    });
}

SelfCondition SelfCondition::HasWindfury()
{
    return SelfCondition([](Playable* playable) {
        const auto character = dynamic_cast<Character*>(playable);
        if (!character)
        {
            return false;
        }

        return character->HasWindfury();
    });
}

SelfCondition SelfCondition::HasReborn()
{
    return SelfCondition([](Playable* playable) {
        const auto minion = dynamic_cast<Minion*>(playable);
        if (!minion)
        {
            return false;
        }

        return minion->HasReborn();
    });
}

SelfCondition SelfCondition::HasFrenzy()
{
    return SelfCondition([](Playable* playable) {
        const auto minion = dynamic_cast<Minion*>(playable);
        if (!minion)
        {
            return false;
        }

        return minion->HasFrenzy();
    });
}

SelfCondition SelfCondition::HasInvokedTwice()
{
    return SelfCondition(
        [](Playable* playable) { return playable->player->GetInvoke() >= 2; });
}

SelfCondition SelfCondition::HasMinionInHand()
{
    return SelfCondition([](Playable* playable) {
        for (auto& card : playable->player->GetHandZone()->GetAll())
        {
            if (dynamic_cast<Minion*>(card) != nullptr)
            {
                return true;
            }
        }

        return false;
    });
}

SelfCondition SelfCondition::IsOverloadCard()
{
    return SelfCondition([](Playable* playable) {
        if (playable->GetGameTag(GameTag::OVERLOAD) >= 1)
        {
            return true;
        }

        return false;
    });
}

SelfCondition SelfCondition::IsComboCard()
{
    return SelfCondition([](Playable* playable) {
        if (playable->GetGameTag(GameTag::COMBO) == 1)
        {
            return true;
        }

        return false;
    });
}

SelfCondition SelfCondition::IsLowestCostMinion()
{
    return SelfCondition([](Playable* playable) {
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
    return SelfCondition([](Playable* playable) {
        return playable->player->GetCurrentSpellPower() > 0;
    });
}

SelfCondition SelfCondition::IsAttackThisTurn()
{
    return SelfCondition([](Playable* playable) {
        return playable->GetGameTag(GameTag::NUM_ATTACKS_THIS_TURN) > 0;
    });
}

SelfCondition SelfCondition::IsCastSpellLastTurn()
{
    return SelfCondition([](Playable* playable) {
        return playable->player->GetGameTag(
                   GameTag::NUM_SPELLS_CAST_LAST_TURN) > 0;
    });
}

SelfCondition SelfCondition::CardsPlayedThisTurn(int num)
{
    return SelfCondition([num](Playable* playable) {
        return playable->player->GetNumCardsPlayedThisTurn() == num;
    });
}

SelfCondition SelfCondition::MinionsPlayedThisTurn(int num)
{
    return SelfCondition([num](Playable* playable) {
        return playable->player->GetNumMinionsPlayedThisTurn() == num;
    });
}

SelfCondition SelfCondition::TauntMinionsPlayedThisTurn(int num)
{
    return SelfCondition([num](Playable* playable) {
        return playable->player->GetNumTauntMinionsPlayedThisTurn() == num;
    });
}

SelfCondition SelfCondition::SpellsCastThisTurn(int num)
{
    return SelfCondition([num](Playable* playable) {
        return playable->player->GetNumSpellsCastThisTurn() == num;
    });
}

SelfCondition SelfCondition::HealthRestoredThisTurn()
{
    return SelfCondition([](Playable* playable) {
        return playable->player->GetAmountHealedThisTurn() > 0;
    });
}

SelfCondition SelfCondition::IsPlayElementalMinionLastTurn()
{
    return SelfCondition([](Playable* playable) {
        return playable->player->GetNumElementalPlayedLastTurn() > 0;
    });
}

SelfCondition SelfCondition::IsNotPlayElementalMinionThisTurn()
{
    return SelfCondition([](Playable* playable) {
        return playable->player->GetNumElementalPlayedThisTurn() == 0;
    });
}

SelfCondition SelfCondition::IsCost(int value, RelaSign relaSign)
{
    return SelfCondition([value, relaSign](Playable* playable) {
        const int val = playable->GetCost();

        return (relaSign == RelaSign::EQ && val == value) ||
               (relaSign == RelaSign::GEQ && val >= value) ||
               (relaSign == RelaSign::LEQ && val <= value);
    });
}

SelfCondition SelfCondition::IsTagValue(GameTag tag, int value,
                                        RelaSign relaSign)
{
    return SelfCondition([tag, value, relaSign](Playable* playable) {
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
    return SelfCondition([name, isEqual](Playable* playable) {
        return !((playable->card->name == name) ^ isEqual);
    });
}

SelfCondition SelfCondition::IsStackNum(int value, RelaSign relaSign, int index)
{
    return SelfCondition([value, relaSign, index](Playable* playable) {
        auto& stack = playable->game->taskStack;
        const auto num = index == 0 ? stack.num[0] : stack.num[1];

        return (relaSign == RelaSign::EQ && num == value) ||
               (relaSign == RelaSign::GEQ && num >= value) ||
               (relaSign == RelaSign::LEQ && num <= value);
    });
}

SelfCondition SelfCondition::IsOddAttackMinion()
{
    return SelfCondition([](Playable* playable) {
        if (auto minion = dynamic_cast<Minion*>(playable); minion)
        {
            return minion->GetAttack() % 2 == 1;
        }

        return false;
    });
}

SelfCondition SelfCondition::IsAttack(int value, RelaSign relaSign)
{
    return SelfCondition([value, relaSign](Playable* playable) {
        if (const auto character = dynamic_cast<Character*>(playable);
            character)
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
    return SelfCondition([value, relaSign](Playable* playable) {
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
    return SelfCondition([value, relaSign](Playable* playable) {
        if (const auto character = dynamic_cast<Character*>(playable);
            character)
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
        [](Playable* playable) { return playable->GetCardTarget() > 0; });
}

SelfCondition SelfCondition::IsProposedDefender(CardType cardType)
{
    return IsEventTargetIs(cardType);
}

SelfCondition SelfCondition::IsDefenderDead()
{
    return SelfCondition([](Playable* playable) {
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
    return SelfCondition([](Playable* playable) {
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
    return SelfCondition([](Playable* playable) {
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
    return SelfCondition([cardType](Playable* playable) {
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
    return SelfCondition([](Playable* playable) {
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
    return SelfCondition([](Playable* playable) {
        const auto iter =
            playable->game->entityList.find(playable->GetCardTarget());

        return playable->card->GetCardType() == CardType::SPELL &&
               iter->second->card->GetCardType() == CardType::MINION;
    });
}

SelfCondition SelfCondition::IsInZone(ZoneType zone)
{
    return SelfCondition(
        [zone](Playable* playable) { return playable->GetZoneType() == zone; });
}

SelfCondition SelfCondition::IsMyTurn()
{
    return SelfCondition([](Playable* playable) {
        return playable->player == playable->game->GetCurrentPlayer();
    });
}

SelfCondition SelfCondition::IsEnemyTurn()
{
    return SelfCondition([](Playable* playable) {
        return playable->player != playable->game->GetCurrentPlayer();
    });
}

SelfCondition SelfCondition::IsMyHeroUndamagedEnemyTurn()
{
    return SelfCondition([](Playable* playable) {
        return playable->player != playable->game->GetCurrentPlayer() &&
               playable->player->GetHero()->damageTakenThisTurn == 0;
    });
}

SelfCondition SelfCondition::IsOverloaded()
{
    return SelfCondition([](Playable* playable) {
        return playable->player->GetOverloadLocked() > 0 ||
               playable->player->GetOverloadOwed() > 0;
    });
}

SelfCondition SelfCondition::HasAtLeastManaCrystal(int num)
{
    return SelfCondition([num](Playable* playable) {
        return playable->player->GetTotalMana() >= num;
    });
}

SelfCondition SelfCondition::IsManaCrystalFull()
{
    return SelfCondition([](Playable* playable) {
        return playable->player->GetTotalMana() == 10;
    });
}

SelfCondition SelfCondition::IsUnspentMana()
{
    return SelfCondition([](Playable* playable) {
        return playable->player->GetRemainingMana() > 0;
    });
}

SelfCondition SelfCondition::IsUsedHeroPowerThisTurn()
{
    return SelfCondition([](Playable* playable) {
        return playable->player->GetHero()->heroPower->IsExhausted();
    });
}

SelfCondition SelfCondition::IsNoDuplicateInDeck()
{
    return SelfCondition([](Playable* playable) {
        auto cards = playable->player->GetDeckZone()->GetAll();
        std::map<std::string, int> result;

        std::for_each(cards.begin(), cards.end(),
                      [&result](Playable* val) { result[val->card->id]++; });

        for (auto& res : result)
        {
            if (res.second >= 2)
            {
                return false;
            }
        }

        return true;
    });
}

SelfCondition SelfCondition::HasNoMinionsInDeck()
{
    return SelfCondition([](Playable* playable) {
        auto cards = playable->player->GetDeckZone()->GetAll();

        for (auto& card : cards)
        {
            if (card->card->GetCardType() == CardType::MINION)
            {
                return false;
            }
        }

        return true;
    });
}

SelfCondition SelfCondition::MaximumCardsInDeck(int value)
{
    return SelfCondition([value](Playable* playable) {
        return playable->player->GetDeckZone()->GetCount() <= value;
    });
}

SelfCondition SelfCondition::HasNoNeutralCardsInDeck()
{
    return SelfCondition([](Playable* playable) {
        auto cards = playable->player->GetDeckZone()->GetAll();

        for (auto& card : cards)
        {
            if (card->card->GetCardClass() == CardClass::NEUTRAL)
            {
                return false;
            }
        }

        return true;
    });
}

SelfCondition SelfCondition::HasAtLeastCardInHand(int num)
{
    return SelfCondition([num](Playable* playable) {
        return playable->player->GetHandZone()->GetCount() >= num;
    });
}

SelfCondition SelfCondition::IsLeftOrRightMostCardInHand()
{
    return SelfCondition([](Playable* playable) {
        return playable->GetGameTag(GameTag::LEFT_OR_RIGHT_MOST_CARD_IN_HAND) >
               0;
    });
}

SelfCondition SelfCondition::HasNotSpellDamageOnHero()
{
    return SelfCondition([](Playable* playable) {
        return playable->player->GetCurrentSpellPower() == 0;
    });
}

SelfCondition SelfCondition::Has5MoreCostSpellInHand()
{
    return SelfCondition([](Playable* playable) {
        for (auto& handCard : playable->player->GetHandZone()->GetAll())
        {
            if (handCard->card->GetCardType() == CardType::SPELL &&
                handCard->GetCost() >= 5)
            {
                return true;
            }
        }

        return false;
    });
}

SelfCondition SelfCondition::Has5MoreCostDemonInHand()
{
    return SelfCondition([](Playable* playable) {
        for (auto& handCard : playable->player->GetHandZone()->GetAll())
        {
            if (auto minion = dynamic_cast<Minion*>(handCard); minion)
            {
                if (minion->card->GetRace() == Race::DEMON &&
                    minion->GetCost() >= 5)
                {
                    return true;
                }
            }
        }

        return false;
    });
}

SelfCondition SelfCondition::Cast5MoreCostSpellInThisTurn()
{
    return SelfCondition([](Playable* playable) {
        for (auto& card : playable->player->cardsPlayedThisTurn)
        {
            if (card->GetCardType() == CardType::SPELL && card->GetCost() >= 5)
            {
                return true;
            }
        }

        return false;
    });
}

SelfCondition SelfCondition::CastFelSpellInThisTurn()
{
    return SelfCondition([](Playable* playable) {
        for (auto& card : playable->player->cardsPlayedThisTurn)
        {
            if (card->GetCardType() == CardType::SPELL &&
                card->GetSpellSchool() == SpellSchool::FEL)
            {
                return true;
            }
        }

        return false;
    });
}

SelfCondition SelfCondition::ControlThisCard(int num)
{
    return SelfCondition([num](Playable* playable) {
        int count = 0;

        for (auto& deckCard : playable->player->GetFieldZone()->GetAll())
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
    return SelfCondition([](Playable* playable) {
        for (auto& deckCard : playable->player->GetDeckZone()->GetAll())
        {
            if (deckCard->card->dbfID == 59723)
            {
                return true;
            }
        }

        return false;
    });
}

SelfCondition SelfCondition::NotExistInSecretZone()
{
    return SelfCondition([](Playable* playable) {
        for (auto& secretCard : playable->player->GetSecretZone()->GetAll())
        {
            if (playable->card->dbfID == secretCard->card->dbfID)
            {
                return false;
            }
        }

        return true;
    });
}

SelfCondition SelfCondition::CheckThreshold(RelaSign relaSign)
{
    return SelfCondition([relaSign](Playable* playable) {
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
