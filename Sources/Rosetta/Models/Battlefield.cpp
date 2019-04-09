// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Battlefield.hpp>
#include <Rosetta/Models/Player.hpp>

#include <algorithm>

namespace RosettaStone
{
Battlefield::Battlefield()
{
    m_minions.fill(nullptr);
}

Player& Battlefield::GetOwner() const
{
    return *m_owner;
}

void Battlefield::SetOwner(Player& owner)
{
    m_owner = &owner;
}

bool Battlefield::IsFull() const
{
    return GetNumOfMinions() == FIELD_SIZE;
}

std::size_t Battlefield::GetNumOfMinions() const
{
    return m_numMinion;
}

Character* Battlefield::GetMinion(std::size_t pos)
{
    return m_minions.at(pos);
}

std::vector<Character*> Battlefield::GetAllMinions()
{
    std::vector<Character*> ret;
    ret.reserve(m_numMinion);

    for (size_t i = 0; i < m_numMinion; ++i)
    {
        ret.emplace_back(m_minions[i]);
    }

    return ret;
}

std::optional<std::size_t> Battlefield::FindMinionPos(Minion& minion)
{
    const auto iter = std::find(m_minions.begin(), m_minions.end(), &minion);
    if (iter != std::end(m_minions))
    {
        return std::distance(std::begin(m_minions), iter);
    }

    return std::nullopt;
}

std::optional<std::size_t> Battlefield::FindEmptyPos() const
{
    const auto iter = std::find(m_minions.begin(), m_minions.end(), nullptr);
    if (iter != std::end(m_minions))
    {
        return std::distance(std::begin(m_minions), iter);
    }

    return std::nullopt;
}

void Battlefield::AddMinion(Minion& minion, std::size_t pos)
{
    m_minions.at(pos) = &minion;
    ++m_numMinion;

    if (minion.GetGameTag(GameTag::CHARGE) != 1)
    {
        minion.SetGameTag(GameTag::EXHAUSTED, 1);
    }

    minion.orderOfPlay = minion.GetOwner().GetGame()->GetNextOOP();

    ActivateAura(minion);
}

void Battlefield::RemoveMinion(Minion& minion)
{
    RemoveAura(minion);

    std::size_t idx = 0;

    for (; idx < m_numMinion; ++idx)
    {
        if (m_minions[idx] == &minion)
        {
            m_minions[idx] = nullptr;
            break;
        }
    }

    for (; idx < m_numMinion - 1; ++idx)
    {
        m_minions[idx] = m_minions[idx + 1];
        m_minions[idx + 1] = nullptr;
    }

    --m_numMinion;

    for (auto& aura : auras)
    {
        aura->RemoveEntity(minion);
    }
}

void Battlefield::ReplaceMinion(Minion& oldMinion, Minion& newMinion)
{
    const std::size_t pos = FindMinionPos(oldMinion).value();
    m_minions[pos] = &newMinion;

    RemoveAura(oldMinion);
    delete &oldMinion;

    ActivateAura(newMinion);
}

void Battlefield::ActivateAura(Minion& minion)
{
    if (minion.card.power.GetAura().has_value())
    {
        minion.card.power.GetAura().value().Activate(minion);
    }

    const int spellPower = minion.GetSpellPower();
    if (spellPower > 0)
    {
        minion.GetOwner().currentSpellPower += spellPower;
    }
}

void Battlefield::RemoveAura(Minion& minion)
{
    if (minion.onGoingEffect != nullptr)
    {
        minion.onGoingEffect->Remove();
    }

    const int spellPower = minion.GetSpellPower();
    if (minion.GetOwner().currentSpellPower > 0 && spellPower > 0)
    {
        minion.GetOwner().currentSpellPower -= spellPower;
    }
}
}  // namespace RosettaStone
