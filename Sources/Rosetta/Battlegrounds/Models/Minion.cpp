// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

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

void Minion::ActivateTrigger(TriggerType type,
                             std::initializer_list<TriggerSource> sources,
                             Player& player)
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

    for (const auto& source : sources)
    {
        if (trigger.value().GetTriggerSource() == source)
        {
            trigger.value().Run(player, *this);
        }
    }
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
