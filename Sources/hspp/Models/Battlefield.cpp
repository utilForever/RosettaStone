// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Models/Battlefield.hpp>

namespace Hearthstonepp
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

std::size_t Battlefield::GetNumOfMinions() const
{
    std::size_t ret = 0;

    for (auto& minion : m_minions)
    {
        if (minion != nullptr)
        {
            ++ret;
        }
    }

    return ret;
}

Character* Battlefield::GetMinion(std::size_t pos)
{
    return m_minions.at(pos);
}

std::vector<Character*> Battlefield::GetAllMinions()
{
    std::vector<Character*> ret;

    for (auto& minion : m_minions)
    {
        if (minion != nullptr)
        {
            ret.emplace_back(minion);
        }
    }

    return ret;
}

optional<std::size_t> Battlefield::FindMinionPos(Minion& minion)
{
    const auto iter = std::find(m_minions.begin(), m_minions.end(), &minion);
    if (iter != std::end(m_minions))
    {
        return std::distance(std::begin(m_minions), iter);
    }

    return nullopt;
}

optional<std::size_t> Battlefield::FindEmptyPos() const
{
    const auto iter = std::find(m_minions.begin(), m_minions.end(), nullptr);
    if (iter != std::end(m_minions))
    {
        return std::distance(std::begin(m_minions), iter);
    }

    return nullopt;
}

void Battlefield::AddMinion(Minion& minion, std::size_t pos)
{
    m_minions.at(pos) = &minion;
}

void Battlefield::RemoveMinion(Minion& minion)
{
    const auto iter = std::find(m_minions.begin(), m_minions.end(), &minion);
    if (iter != std::end(m_minions))
    {
        delete *iter;
    }
}
}  // namespace Hearthstonepp