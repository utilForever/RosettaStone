// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Conditions/SelfCondition.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Zones/FieldZone.hpp>
#include <Rosetta/Zones/HandZone.hpp>
#include <Rosetta/Zones/SecretZone.hpp>

#include <string>
#include <utility>

namespace RosettaStone
{
SelfCondition::SelfCondition(std::function<bool(Playable*)> func)
    : m_func(std::move(func))
{
    // Do nothing
}

SelfCondition SelfCondition::IsHeroPowerCard(const std::string& cardID)
{
    return SelfCondition([=](Playable* playable) -> bool {
        return playable->player->GetHero()->heroPower->card->id == cardID;
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

SelfCondition SelfCondition::IsControllingSecret()
{
    return SelfCondition([=](Playable* playable) -> bool {
        return !playable->player->GetSecretZone()->IsEmpty();
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

SelfCondition SelfCondition::IsSecret()
{
    return SelfCondition([=](Playable* playable) -> bool {
        return dynamic_cast<Spell*>(playable) != nullptr &&
               playable->GetGameTag(GameTag::SECRET) == 1;
    });
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
        if (playable->player->currentSpellPower > 0)
        {
            return true;
        }
        return false;
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

SelfCondition SelfCondition::MinionsPlayedThisTurn(int num)
{
    return SelfCondition([=](Playable* playable) -> bool {
        return playable->player->GetNumMinionsPlayedThisTurn() == num;
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

SelfCondition SelfCondition::IsProposedDefender(CardType cardType)
{
    return IsEventTargetIs(cardType);
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

SelfCondition SelfCondition::IsUnspentMana()
{
    return SelfCondition([=](Playable* playable) -> bool {
        return playable->player->GetRemainingMana();
    });
}

bool SelfCondition::Evaluate(Playable* owner) const
{
    return m_func(owner);
}
}  // namespace RosettaStone
