// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Enchants/Power.hpp>
#include <Rosetta/Battlegrounds/Models/Minion.hpp>
#include <Rosetta/Battlegrounds/Models/Player.hpp>

#include <utility>
#include <vector>

namespace RosettaStone::Battlegrounds
{
Minion::Minion(Card card, int poolIdx)
    : m_card(std::move(card)),
      m_poolIdx(poolIdx),
      m_attack(m_card.GetAttack()),
      m_health(m_card.GetHealth())
{
    for (const auto& tag : m_card.gameTags)
    {
        switch (tag.first)
        {
            case GameTag::DEATHRATTLE:
                m_hasDeathrattle = true;
                break;
            case GameTag::TAUNT:
                m_hasTaunt = true;
                break;
            case GameTag::DIVINE_SHIELD:
                m_hasDivineShield = true;
                break;
            default:
                break;
        }
    }
}

int Minion::GetIndex() const
{
    return m_index;
}

void Minion::SetIndex(int index)
{
    m_index = index;
}

int Minion::GetPoolIndex() const
{
    return m_poolIdx;
}

std::string_view Minion::GetName() const
{
    return m_card.name;
}

int Minion::GetGameTag(GameTag tag) const
{
    switch (tag)
    {
        case GameTag::ATK:
            return GetAttack();
        default:
            return 0;
    }
}

void Minion::SetGameTag(GameTag tag, int value)
{
    switch (tag)
    {
        case GameTag::DIVINE_SHIELD:
            m_hasDivineShield = value == 1 ? true : false;
            break;
        default:
            break;
    }
}

Race Minion::GetRace() const
{
    return m_card.GetRace();
}

ZoneType Minion::GetZoneType() const
{
    return m_zoneType;
}

void Minion::SetZoneType(ZoneType type)
{
    m_zoneType = type;
}

int Minion::GetZonePosition() const
{
    return m_zonePos;
}

void Minion::SetZonePosition(int pos)
{
    m_zonePos = pos;
}

int Minion::GetLastFieldPos() const
{
    return m_lastFieldPos;
}

void Minion::SetLastFieldPos(int pos)
{
    m_lastFieldPos = pos;
}

int Minion::GetTier() const
{
    return m_card.GetTier();
}

int Minion::GetAttack() const
{
    return m_attack;
}

void Minion::SetAttack(int val)
{
    m_attack = val;
}

int Minion::GetHealth() const
{
    return m_health;
}

void Minion::SetHealth(int val)
{
    m_health = val;
}

bool Minion::HasDeathrattle() const
{
    return m_hasDeathrattle;
}

bool Minion::HasTaunt() const
{
    return m_hasTaunt;
}

bool Minion::HasDivineShield() const
{
    return m_hasDivineShield;
}

void Minion::TakeDamage(Minion& source)
{
    if (HasDivineShield())
    {
        m_hasDivineShield = false;
        return;
    }

    m_health -= source.GetAttack();
    if (m_health <= 0)
    {
        m_isDestroyed = true;
    }
}

void Minion::TakeDamage(int amount)
{
    m_health -= amount;
    if (m_health <= 0)
    {
        m_isDestroyed = true;
    }
}

bool Minion::IsDestroyed() const
{
    return m_isDestroyed;
}

bool Minion::IsPlayableByCardReq(Player& player) const
{
    if (!m_card.IsPlayableByCardReq(player))
    {
        return false;
    }

    if (m_card.mustHaveToTargetToPlay && !HasAnyValidPlayTargets(player))
    {
        return false;
    }

    return true;
}

bool Minion::HasAnyValidPlayTargets(Player& player) const
{
    bool friendlyMinions = false;
    
    switch (m_card.targetingType)
    {
        case TargetingType::FRIENDLY_MINIONS:
            friendlyMinions = true;
            break;
        default:
            break;
    }

    if (friendlyMinions)
    {
        for (auto& minion : player.recruitField.GetAll())
        {
            if (m_card.TargetingRequirements(minion))
            {
                return true;
            }
        }
    }

    return false;
}

bool Minion::IsValidPlayTarget(Player& player, int targetIdx)
{
    if (targetIdx == -1)
    {
        if (m_card.mustHaveToTargetToPlay)
        {
            return false;
        }

        if (m_card.targetingType == TargetingType::NONE)
        {
            return true;
        }

        if (!HasAnyValidPlayTargets(player))
        {
            return true;
        }

        return false;
    }
    else
    {
        Minion& target = player.recruitField[targetIdx];

        if (!CheckTargetingType(target))
        {
            return false;
        }

        if (m_card.TargetingRequirements(target))
        {
            return true;
        }
    }

    return false;
}

bool Minion::CheckTargetingType([[maybe_unused]] Minion& target)
{
    switch (m_card.targetingType)
    {
        case TargetingType::NONE:
            return false;
        case TargetingType::FRIENDLY_MINIONS:
            return true;
        default:
            break;
    }

    return true;
}

void Minion::ActivateTrigger(TriggerType type, Minion& source)
{
    auto& trigger = m_card.power.GetTrigger();
    if (!trigger.has_value())
    {
        return;
    }

    if (trigger.value().GetTriggerType() != type)
    {
        return;
    }

    trigger.value().Run(*this, source);
}

void Minion::ActivateTask(PowerType type, Player& player)
{
    auto tasks = GetTasks(type);
    if (tasks.empty())
    {
        return;
    }

    for (auto& task : tasks)
    {
        if (player.taskStack.isStackingTasks &&
            !std::holds_alternative<RepeatNumberEndTask>(task))
        {
            player.taskStack.tasks.emplace_back(task);
        }
        else
        {
            std::visit([&](auto&& _task) { _task.Run(player, *this); }, task);
        }
    }
}

void Minion::ActivateTask(PowerType type, Player& player, Minion& target)
{
    auto tasks = GetTasks(type);
    if (tasks.empty())
    {
        return;
    }

    for (auto& task : tasks)
    {
        if (player.taskStack.isStackingTasks &&
            !std::holds_alternative<RepeatNumberEndTask>(task))
        {
            player.taskStack.tasks.emplace_back(task);
        }
        else
        {
            std::visit([&](auto&& _task) { _task.Run(player, *this, target); },
                       task);
        }
    }
}

std::vector<TaskType> Minion::GetTasks(PowerType type)
{
    switch (type)
    {
        case PowerType::POWER:
            return m_card.power.GetBattlecryTask();
        case PowerType::DEATHRATTLE:
            return m_card.power.GetDeathrattleTask();
        case PowerType::START_OF_COMBAT:
            return m_card.power.GetStartCombatTask();
        default:
            return std::vector<TaskType>{};
    }
}
}  // namespace RosettaStone::Battlegrounds
