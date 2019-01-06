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
}  // namespace Hearthstonepp