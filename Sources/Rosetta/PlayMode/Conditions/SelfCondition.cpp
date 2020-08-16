// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/Conditions/SelfCondition.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>
#include <Rosetta/PlayMode/Zones/SecretZone.hpp>

#include <string>
#include <utility>

namespace RosettaStone::PlayMode
{
SelfCondition::SelfCondition(std::function<bool(Playable*)> func)
    : m_func(std::move(func))
{
    // Do nothing
}

SelfCondition SelfCondition::IsCurrentPlayer()
{
    return SelfCondition([=](Playable* playable) -> bool {
        return playable->game->GetCurrentPlayer() == playable->player;
    });
}

SelfCondition SelfCondition::IsNotStartInDeck()
{
    return SelfCondition([=](Playable* playable) -> bool {
        const auto entityID = playable->GetGameTag(GameTag::ENTITY_ID);
        const auto curDeckCount = playable->player->GetDeckZone()->GetCount();
        const auto opDeckCount =
            playable->player->opponent->GetDeckZone()->GetCount();
        return entityID > curDeckCount + opDeckCount + 7;
    });
}

SelfCondition SelfCondition::IsDeckEmpty()
{
    return SelfCondition([=](Playable* playable) -> bool {
        return playable->player->GetDeckZone()->IsEmpty();
    });
}

SelfCondition SelfCondition::IsHeroPowerCard(const std::string& cardID)
{
    return SelfCondition([=](Playable* playable) -> bool {
        return playable->player->GetHero()->heroPower->card->id == cardID;
    });
}

SelfCondition SelfCondition::IsBattlecryCard()
{
    return SelfCondition([=](Playable* playable) -> bool {
        return playable->GetGameTag(GameTag::BATTLECRY) == 1;
    });
}

SelfCondition SelfCondition::IsGalakrondHero()
{
    return SelfCondition([=](Playable* playable) -> bool {
        return playable->card->IsGalakrond();
    });
}

SelfCondition SelfCondition::IsDead()
{
    return SelfCondition(
        [=](Playable* playable) -> bool { return playable->isDestroyed; });
}

SelfCondition SelfCondition::IsNotDead()
{
    return SelfCondition(
        [=](Playable* playable) -> bool { return !playable->isDestroyed; });
}

SelfCondition SelfCondition::IsNotImmune()
{
    return SelfCondition([=](Playable* playable) -> bool {
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
    return SelfCondition([=](Playable* playable) -> bool {
        return !playable->card->IsUntouchable();
    });
}

SelfCondition SelfCondition::IsFieldFull()
{
    return SelfCondition([=](Playable* playable) -> bool {
        return playable->player->GetFieldZone()->IsFull();
    });
}

SelfCondition SelfCondition::IsFieldNotFull()
{
    return SelfCondition([=](Playable* playable) -> bool {
        return !playable->player->GetFieldZone()->IsFull();
    });
}

SelfCondition SelfCondition::IsOpFieldNotFull()
{
    return SelfCondition([=](Playable* playable) -> bool {
        return !playable->player->opponent->GetFieldZone()->IsFull();
    });
}

SelfCondition SelfCondition::IsFieldNotEmpty()
{
    return SelfCondition([=](Playable* playable) -> bool {
        return !playable->player->GetFieldZone()->IsEmpty();
    });
}

SelfCondition SelfCondition::IsDamaged()
{
    return SelfCondition([=](Playable* playable) -> bool {
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
    return SelfCondition([=](Playable* playable) -> bool {
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
    return SelfCondition([=](Playable* playable) -> bool {
        return playable->player->GetHero()->HasWeapon();
    });
}

SelfCondition SelfCondition::IsTreant()
{
    return SelfCondition([=](Playable* playable) -> bool {
        return playable->card->name == "Treant";
    });
}

SelfCondition SelfCondition::IsRace(Race race)
{
    return SelfCondition([=](Playable* playable) -> bool {
        return playable->card->GetRace() == race;
    });
}

SelfCondition SelfCondition::IsControllingRace(Race race)
{
    return SelfCondition([=](Playable* playable) -> bool {
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
    return SelfCondition([=](Playable* playable) -> bool {
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
    return SelfCondition([=](Playable* playable) -> bool {
        return !playable->player->GetSecretZone()->IsEmpty();
    });
}

SelfCondition SelfCondition::IsControllingLackey()
{
    return SelfCondition([=](Playable* playable) -> bool {
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

SelfCondition SelfCondition::IsHoldingRace(Race race)
{
    return SelfCondition([=](Playable* playable) -> bool {
        for (auto& minion : playable->player->GetHandZone()->GetAll())
        {
            if (minion->card->GetRace() == race)
            {
                return true;
            }
        }

        return false;
    });
}

SelfCondition SelfCondition::IsAnotherClassCard()
{
    return SelfCondition([=](Playable* playable) -> bool {
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
    return SelfCondition([=](Playable* playable) -> bool {
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
    return SelfCondition([=](Playable* playable) -> bool {
        return playable->card->id == cardID;
    });
}

SelfCondition SelfCondition::IsMinion()
{
    return SelfCondition([=](Playable* playable) -> bool {
        return dynamic_cast<Minion*>(playable) != nullptr;
    });
}

SelfCondition SelfCondition::IsSpell()
{
    return SelfCondition([=](Playable* playable) -> bool {
        return dynamic_cast<Spell*>(playable) != nullptr;
    });
}

SelfCondition SelfCondition::IsWeapon()
{
    return SelfCondition([=](Playable* playable) -> bool {
        return dynamic_cast<Weapon*>(playable) != nullptr;
    });
}

SelfCondition SelfCondition::IsSecret()
{
    return SelfCondition([=](Playable* playable) -> bool {
        return dynamic_cast<Spell*>(playable) != nullptr &&
               playable->GetGameTag(GameTag::SECRET) == 1;
    });
}

SelfCondition SelfCondition::IsChooseOneCard()
{
    return SelfCondition(
        [=](Playable* playable) -> bool { return playable->HasChooseOne(); });
}

SelfCondition SelfCondition::IsFrozen()
{
    return SelfCondition([=](Playable* playable) -> bool {
        const auto character = dynamic_cast<Character*>(playable);
        if (!character)
        {
            return false;
        }

        return character->IsFrozen();
    });
}

SelfCondition SelfCondition::HasRush()
{
    return SelfCondition([=](Playable* playable) -> bool {
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
    return SelfCondition([=](Playable* playable) -> bool {
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
    return SelfCondition([=](Playable* playable) -> bool {
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
    return SelfCondition([=](Playable* playable) -> bool {
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
    return SelfCondition([=](Playable* playable) -> bool {
        const auto minion = dynamic_cast<Minion*>(playable);
        if (!minion)
        {
            return false;
        }

        return minion->HasReborn();
    });
}

SelfCondition SelfCondition::HasSpellPower()
{
    return SelfCondition([=](Playable* playable) -> bool {
        return playable->player->GetCurrentSpellPower() > 0;
    });
}

SelfCondition SelfCondition::HasInvokedTwice()
{
    return SelfCondition([=](Playable* playable) -> bool {
        return playable->player->GetInvoke() >= 2;
    });
}

SelfCondition SelfCondition::HasMinionInHand()
{
    return SelfCondition([=](Playable* playable) -> bool {
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
    return SelfCondition([=](Playable* playable) -> bool {
        if (playable->GetGameTag(GameTag::OVERLOAD) >= 1)
        {
            return true;
        }

        return false;
    });
}

SelfCondition SelfCondition::IsComboCard()
{
    return SelfCondition([=](Playable* playable) -> bool {
        if (playable->GetGameTag(GameTag::COMBO) == 1)
        {
            return true;
        }

        return false;
    });
}

SelfCondition SelfCondition::IsAttackThisTurn()
{
    return SelfCondition([=](Playable* playable) -> bool {
        return playable->GetGameTag(GameTag::NUM_ATTACKS_THIS_TURN) > 0;
    });
}

SelfCondition SelfCondition::MinionsPlayedThisTurn(int num)
{
    return SelfCondition([=](Playable* playable) -> bool {
        return playable->player->GetNumMinionsPlayedThisTurn() == num;
    });
}

SelfCondition SelfCondition::SpellsPlayedThisTurn(int num)
{
    return SelfCondition([=](Playable* playable) -> bool {
        return playable->player->GetNumSpellsPlayedThisTurn() == num;
    });
}

SelfCondition SelfCondition::IsNotPlayElementalMinionThisTurn()
{
    return SelfCondition([=](Playable* playable) -> bool {
        return playable->player->GetNumElementalPlayedThisTurn() == 0;
    });
}

SelfCondition SelfCondition::IsCost(int value, RelaSign relaSign)
{
    return SelfCondition([=](Playable* playable) -> bool {
        const int val = playable->GetCost();

        return (relaSign == RelaSign::EQ && val == value) ||
               (relaSign == RelaSign::GEQ && val >= value) ||
               (relaSign == RelaSign::LEQ && val <= value);
    });
}

SelfCondition SelfCondition::IsTagValue(GameTag tag, int value,
                                        RelaSign relaSign)
{
    return SelfCondition([=](Playable* playable) -> bool {
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
    return SelfCondition([=](Playable* playable) -> bool {
        return !((playable->card->name == name) ^ isEqual);
    });
}

SelfCondition SelfCondition::IsStackNum(int value, RelaSign relaSign, int index)
{
    return SelfCondition([=](Playable* playable) -> bool {
        auto& stack = playable->game->taskStack;
        const auto num = index == 0 ? stack.num[0] : stack.num[1];

        return (relaSign == RelaSign::EQ && num == value) ||
               (relaSign == RelaSign::GEQ && num >= value) ||
               (relaSign == RelaSign::LEQ && num <= value);
    });
}

SelfCondition SelfCondition::IsHealth(int value, RelaSign relaSign)
{
    return SelfCondition([=](Playable* playable) -> bool {
        const auto character = dynamic_cast<Character*>(playable);
        if (character == nullptr)
        {
            return false;
        }

        return (relaSign == RelaSign::EQ && character->GetHealth() == value) ||
               (relaSign == RelaSign::GEQ && character->GetHealth() >= value) ||
               (relaSign == RelaSign::LEQ && character->GetHealth() <= value);
    });
}

SelfCondition SelfCondition::HasTarget()
{
    return SelfCondition([=](Playable* playable) -> bool {
        return playable->GetCardTarget() > 0;
    });
}

SelfCondition SelfCondition::IsProposedDefender(CardType cardType)
{
    return IsEventTargetIs(cardType);
}

SelfCondition SelfCondition::IsDefenderDead()
{
    return SelfCondition([=](Playable* playable) -> bool {
        if (playable->game->currentEventData)
        {
            return playable->game->currentEventData->eventTarget->isDestroyed;
        }

        return false;
    });
}

SelfCondition SelfCondition::IsEventSourceFriendly()
{
    return SelfCondition([=](Playable* playable) -> bool {
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
    return SelfCondition([=](Playable* playable) -> bool {
        if (const auto eventData = playable->game->currentEventData.get();
            eventData)
        {
            return eventData->eventTarget->card->GetCardType() == cardType;
        }

        return false;
    });
}

SelfCondition SelfCondition::IsSpellTargetingMinion()
{
    return SelfCondition([=](Playable* playable) -> bool {
        const auto iter =
            playable->game->entityList.find(playable->GetCardTarget());

        return playable->card->GetCardType() == CardType::SPELL &&
               iter->second->card->GetCardType() == CardType::MINION;
    });
}

SelfCondition SelfCondition::IsInZone(ZoneType zone)
{
    return SelfCondition([=](Playable* playable) -> bool {
        return playable->GetZoneType() == zone;
    });
}

SelfCondition SelfCondition::IsEnemyTurn()
{
    return SelfCondition([=](Playable* playable) -> bool {
        return playable->player != playable->game->GetCurrentPlayer();
    });
}

SelfCondition SelfCondition::IsMyHeroUndamagedEnemyTurn()
{
    return SelfCondition([=](Playable* playable) -> bool {
        return playable->player != playable->game->GetCurrentPlayer() &&
               playable->player->GetHero()->damageTakenThisTurn == 0;
    });
}

SelfCondition SelfCondition::IsOverloaded()
{
    return SelfCondition([=](Playable* playable) -> bool {
        return playable->player->GetOverloadLocked() > 0 ||
               playable->player->GetOverloadOwed() > 0;
    });
}

SelfCondition SelfCondition::IsManaCrystalFull()
{
    return SelfCondition([=](Playable* playable) -> bool {
        return playable->player->GetTotalMana() == 10;
    });
}

SelfCondition SelfCondition::IsUnspentMana()
{
    return SelfCondition([=](Playable* playable) -> bool {
        return playable->player->GetRemainingMana() > 0;
    });
}

SelfCondition SelfCondition::IsNoDuplicateInDeck()
{
    return SelfCondition([=](Playable* playable) -> bool {
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

SelfCondition SelfCondition::HasNoNeutralCardsInDeck()
{
    return SelfCondition([=](Playable* playable) -> bool {
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

SelfCondition SelfCondition::IsLeftOrRightMostCardInHand()
{
    return SelfCondition([=](Playable* playable) -> bool {
        return playable->GetGameTag(GameTag::LEFT_OR_RIGHT_MOST_CARD_IN_HAND) >
               0;
    });
}

SelfCondition SelfCondition::HasNotSpellDamageOnHero()
{
    return SelfCondition([=](Playable* playable) -> bool {
        return playable->player->GetCurrentSpellPower() == 0;
    });
}

SelfCondition SelfCondition::Has5MoreCostSpellInHand()
{
    return SelfCondition([=](Playable* playable) -> bool {
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

SelfCondition SelfCondition::Cast5MoreCostSpellInThisTurn()
{
    return SelfCondition([=](Playable* playable) -> bool {
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

SelfCondition SelfCondition::CheckThreshold(RelaSign relaSign)
{
    return SelfCondition([=](Playable* playable) -> bool {
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
