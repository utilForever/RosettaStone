// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Playable.hpp>
#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Tasks/ITask.hpp>

#include <utility>
#include "Rosetta/Zones/FieldZone.hpp"

namespace RosettaStone
{
Playable::Playable(Player* _player, Card* _card, std::map<GameTag, int> _tags)
    : Entity(_player->game, _card, std::move(_tags))
{
    player = _player;
}

Playable::~Playable()
{
    delete onGoingEffect;
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

    if (const auto effect = dynamic_cast<AdaptiveCostEffect*>(onGoingEffect);
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

std::vector<Character*> Playable::GetValidPlayTargets()
{
    return card->GetValidPlayTargets(player);
}

bool Playable::IsValidPlayTarget(Character* target)
{
    // Get valid play targets
    auto targetList = GetValidTargets(source);

    // Return if source needs a target, but target is null and list is not empty
    if (IsSourceNeedsTarget(source) && target == nullptr && !targetList.empty())
    {
        return false;
    }

    // Check source must require a target
    bool requiresTarget = false;
    for (auto& requirement : source->card->playRequirements)
    {
        if (requirement.first == PlayReq::REQ_TARGET_TO_PLAY)
        {
            requiresTarget = true;
            break;
        }
    }

    // Return if source must require a target, but target is null
    if (requiresTarget && target == nullptr)
    {
        return false;
    }

    // Return if target is exist, but not exist in target list
    if (target != nullptr && std::find(targetList.begin(), targetList.end(),
                                       target) == targetList.end())
    {
        return false;
    }

    return true;
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

bool Playable::CheckRequirements(Character* target)
{
    for (auto& requirement : source->card->playRequirements)
    {
        const PlayReq req = requirement.first;
        const int param = requirement.second;

        switch (req)
        {
            case PlayReq::REQ_MINION_TARGET:
            {
                if (dynamic_cast<Minion*>(target) == nullptr)
                {
                    return false;
                }
                break;
            }
            case PlayReq::REQ_FRIENDLY_TARGET:
                if (target->player != source->player)
                {
                    return false;
                }
                break;
            case PlayReq::REQ_ENEMY_TARGET:
            {
                if (target->player == source->player)
                {
                    return false;
                }
                break;
            }
            case PlayReq::REQ_DAMAGED_TARGET:
            {
                if (target->GetDamage() == 0)
                {
                    return false;
                }
                break;
            }
            case PlayReq::REQ_TARGET_MAX_ATTACK:
            {
                if (target->GetAttack() > param)
                {
                    return false;
                }
                break;
            }
            case PlayReq::REQ_NONSELF_TARGET:
            {
                if (source == target)
                {
                    return false;
                }
                break;
            }
            case PlayReq::REQ_TARGET_WITH_RACE:
            {
                if (target->card->GetRace() != static_cast<Race>(param))
                {
                    return false;
                }
                break;
            }
            case PlayReq::REQ_TARGET_MIN_ATTACK:
            {
                if (target->GetAttack() < param)
                {
                    return false;
                }
                break;
            }
            case PlayReq::REQ_UNDAMAGED_TARGET:
            {
                if (target->GetDamage() > 0)
                {
                    return false;
                }
                break;
            }
            case PlayReq::REQ_MUST_TARGET_TAUNTER:
                if (dynamic_cast<Minion*>(target) == nullptr ||
                    target->GetGameTag(GameTag::TAUNT) == 0)
                {
                    return false;
                }
                break;
            case PlayReq::REQ_TARGET_TO_PLAY:
            case PlayReq::REQ_TARGET_IF_AVAILABLE:
                break;
            default:
                break;
        }
    }

    return true;
}
}  // namespace RosettaStone
