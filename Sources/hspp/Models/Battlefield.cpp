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

std::vector<Character*> Battlefield::GetAllMinions()
{
    std::vector<Character*> ret(FIELD_SIZE);

    for (auto& minion : m_minions)
    {
        if (minion != nullptr)
        {
            ret.emplace_back(minion);
        }
    }

    return ret;
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