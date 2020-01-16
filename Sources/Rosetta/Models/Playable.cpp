// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Playable.hpp>
#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Tasks/ITask.hpp>
#include <Rosetta/Zones/FieldZone.hpp>

#include <utility>

namespace RosettaStone
{
Playable::Playable(Player* _player, Card* _card, std::map<GameTag, int> _tags,
                   int _id)
    : Entity(_player->game, _card, std::move(_tags), _id)
{
    player = _player;
}

Playable::~Playable()
{
    delete ongoingEffect;
}

ZoneType Playable::GetZoneType() const
{
    return static_cast<ZoneType>(GetGameTag(GameTag::ZONE));
}

void Playable::SetZoneType(ZoneType type)
{
    SetGameTag(GameTag::ZONE, static_cast<int>(type));
}

int Playable::GetZonePosition() const
{
    return GetGameTag(GameTag::ZONE_POSITION) - 1;
}

void Playable::SetZonePosition(int value)
{
    SetGameTag(GameTag::ZONE_POSITION, value + 1);
}

int Playable::GetCost() const
{
    const int value =
        GetGameTag(GameTag::COST) < 0 ? 0 : GetGameTag(GameTag::COST);

    if (costManager != nullptr)
    {
        return costManager->GetCost(value);
    }

    return value;
}

void Playable::SetCost(int cost)
{
    SetGameTag(GameTag::COST, cost);
}

bool Playable::IsExhausted() const
{
    // Consider windfury
    if (GetGameTag(GameTag::WINDFURY) == 1 &&
        GetGameTag(GameTag::NUM_ATTACKS_THIS_TURN) == 1)
    {
        return false;
    }

    // Consider charge
    if (GetGameTag(GameTag::CHARGE) == 1 &&
        GetGameTag(GameTag::NUM_ATTACKS_THIS_TURN) == 0)
    {
        return false;
    }

    return GetGameTag(GameTag::EXHAUSTED) == 1;
}

void Playable::SetExhausted(bool exhausted)
{
    SetGameTag(GameTag::EXHAUSTED, static_cast<int>(exhausted));
}

bool Playable::HasCombo() const
{
    return GetGameTag(GameTag::COMBO) == 1;
}

bool Playable::HasOverload() const
{
    return GetGameTag(GameTag::OVERLOAD) > 0;
}

int Playable::GetOverload() const
{
    return GetGameTag(GameTag::OVERLOAD);
}

bool Playable::HasDeathrattle() const
{
    return GetGameTag(GameTag::DEATHRATTLE) == 1;
}

bool Playable::HasChooseOne() const
{
    return GetGameTag(GameTag::CHOOSE_ONE) == 1;
}

void Playable::ResetCost()
{
    costManager = nullptr;
    SetCost(card->gameTags[GameTag::COST]);

    if (const auto effect = dynamic_cast<AdaptiveCostEffect*>(ongoingEffect);
        effect != nullptr)
    {
        effect->Remove();
    }
}

void Playable::Destroy()
{
    isDestroyed = true;
}

bool Playable::IsPlayable()
{
    return IsPlayableByPlayer() && IsPlayableByCardReq();
}

bool Playable::TargetingRequirements(Character* target) const
{
    return card->TargetingRequirements(player, target);
}

bool Playable::IsPlayableByPlayer()
{
    // Check if player has enough mana to play card
    if (player->GetRemainingMana() < GetCost())
    {
        return false;
    }

    // Check if player is on turn
    if (player != game->GetCurrentPlayer())
    {
        return false;
    }

    // Check if entity is in hand to be played
    if (dynamic_cast<HeroPower*>(this) == nullptr &&
        GetZoneType() != ZoneType::HAND)
    {
        return false;
    }

    return true;
}

bool Playable::IsPlayableByCardReq() const
{
    for (auto& requirement : card->playRequirements)
    {
        switch (requirement.first)
        {
            case PlayReq::REQ_NUM_MINION_SLOTS:
                if (player->GetFieldZone()->IsFull())
                {
                    return false;
                }
                break;
            case PlayReq::REQ_WEAPON_EQUIPPED:
                if (!player->GetHero()->HasWeapon())
                {
                    return false;
                }
                break;
            case PlayReq::REQ_MINIMUM_ENEMY_MINIONS:
            {
                const auto opField = player->opponent->GetFieldZone();
                if (opField->GetCount() < requirement.second)
                {
                    return false;
                }
                break;
            }
            case PlayReq::REQ_ENTIRE_ENTOURAGE_NOT_IN_PLAY:
            {
                auto curField = player->GetFieldZone();
                auto& entourages = card->entourages;
                std::size_t entourageCount = 0;

                for (auto& minion : curField->GetAll())
                {
                    for (auto& entourage : entourages)
                    {
                        if (minion->card->id == entourage)
                        {
                            ++entourageCount;
                        }
                    }
                }

                if (entourageCount == entourages.size())
                {
                    return false;
                }

                break;
            }
            case PlayReq::REQ_MINIMUM_TOTAL_MINIONS:
            {
                const int fieldCount =
                    player->GetFieldZone()->GetCount() +
                    player->opponent->GetFieldZone()->GetCount();
                if (fieldCount < requirement.second)
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

std::vector<Character*> Playable::GetValidPlayTargets() const
{
    return card->GetValidPlayTargets(player);
}

bool Playable::IsValidPlayTarget(Character* target)
{
    if (target == nullptr)
    {
        if (card->mustHaveToTargetToPlay)
        {
            return false;
        }

        if (card->targetingType == TargetingType::NONE)
        {
            return true;
        }

        if (!HasAnyValidPlayTargets())
        {
            return true;
        }

        return false;
    }

    switch (card->targetingType)
    {
        case TargetingType::NONE:
            return false;
        case TargetingType::ALL:
            break;
        case TargetingType::FRIENDLY_CHARACTERS:
            if (target->player != player)
            {
                return false;
            }
            break;
        case TargetingType::ENEMY_CHARACTERS:
            if (target->player == player)
            {
                return false;
            }
            break;
        case TargetingType::ALL_MINIONS:
            if (dynamic_cast<Hero*>(target) != nullptr)
            {
                return false;
            }
            break;
        case TargetingType::FRIENDLY_MINIONS:
            if (dynamic_cast<Hero*>(target) != nullptr ||
                target->player != player)
            {
                return false;
            }
            break;
        case TargetingType::ENEMY_MINIONS:
            if (dynamic_cast<Hero*>(target) != nullptr ||
                target->player == player)
            {
                return false;
            }
            break;
        case TargetingType::HEROES:
            if (dynamic_cast<Minion*>(target) != nullptr)
            {
                return false;
            }
            break;
    }

    if (TargetingRequirements(target))
    {
        return true;
    }

    return false;
}

bool Playable::HasAnyValidPlayTargets() const
{
    bool friendlyMinions = false, enemyMinions = false;
    bool hero = false, enemyHero = false;

    switch (card->targetingType)
    {
        case TargetingType::NONE:
            return false;
        case TargetingType::ALL:
            friendlyMinions = true;
            enemyMinions = true;
            hero = true;
            enemyHero = true;
            break;
        case TargetingType::FRIENDLY_CHARACTERS:
            friendlyMinions = true;
            hero = true;
            break;
        case TargetingType::ENEMY_CHARACTERS:
            enemyMinions = true;
            enemyHero = true;
            break;
        case TargetingType::ALL_MINIONS:
            friendlyMinions = true;
            enemyMinions = true;
            break;
        case TargetingType::FRIENDLY_MINIONS:
            friendlyMinions = true;
            break;
        case TargetingType::ENEMY_MINIONS:
            enemyMinions = true;
            break;
        case TargetingType::HEROES:
            hero = true;
            enemyHero = true;
            break;
    }

    if (friendlyMinions)
    {
        for (auto& minion : player->GetFieldZone()->GetAll())
        {
            if (TargetingRequirements(minion))
            {
                return true;
            }
        }
    }

    if (enemyMinions)
    {
        for (auto& minion : player->opponent->GetFieldZone()->GetAll())
        {
            if (TargetingRequirements(minion))
            {
                return true;
            }
        }
    }

    if (hero && TargetingRequirements(player->GetHero()))
    {
        return true;
    }

    if (enemyHero && TargetingRequirements(player->opponent->GetHero()))
    {
        return true;
    }

    return false;
}

void Playable::ActivateTask(PowerType type, Character* target, int chooseOne,
                            Playable* chooseBase)
{
    if (HasChooseOne())
    {
        if (chooseOne > 0)
        {
            chooseOneCard[chooseOne - 1]->ActivateTask(type, target, chooseOne,
                                                       this);
            return;
        }
    }

    std::vector<ITask*> tasks;
    switch (type)
    {
        case PowerType::POWER:
            tasks = card->power.GetPowerTask();
            break;
        case PowerType::DEATHRATTLE:
            tasks = card->power.GetDeathrattleTask();
            break;
        case PowerType::COMBO:
            tasks = card->power.GetComboTask();
            break;
    }

    if (tasks.empty() || tasks[0] == nullptr)
    {
        return;
    }

    for (auto& task : tasks)
    {
        ITask* clonedTask = task->Clone();

        clonedTask->SetPlayer(player);
        clonedTask->SetSource(chooseBase == nullptr ? this : chooseBase);
        clonedTask->SetTarget(target);

        game->taskQueue.Enqueue(clonedTask);
    }
}
}  // namespace RosettaStone
