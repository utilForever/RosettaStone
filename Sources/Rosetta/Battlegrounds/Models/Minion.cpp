// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Enchants/Power.hpp>
#include <Rosetta/Battlegrounds/Models/Minion.hpp>

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

int Minion::GetHealth() const
{
    return m_health;
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

bool Minion::IsDestroyed() const
{
    return m_isDestroyed;
}

void Minion::ActivateTask(PowerType type, Player& player)
{
    std::vector<TaskType> tasks;
    switch (type)
    {
        case PowerType::POWER:
            tasks = m_card.power.GetBattlecryTask();
            break;
        default:
            break;
    }

    if (tasks.empty())
    {
        return;
    }

    for (auto& task : tasks)
    {
        std::visit([&](auto&& _task) { _task.Run(player, *this); }, task);
    }
}

void Minion::ActivateTask(PowerType type, Player& player, Minion& target)
{
    std::vector<TaskType> tasks;
    switch (type)
    {
        case PowerType::POWER:
            tasks = m_card.power.GetBattlecryTask();
            break;
        default:
            break;
    }

    if (tasks.empty())
    {
        return;
    }

    for (auto& task : tasks)
    {
        std::visit([&](auto&& _task) { _task.Run(player, *this, target); },
                   task);
    }
}
}  // namespace RosettaStone::Battlegrounds
