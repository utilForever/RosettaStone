// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/CardSets/CoreCardsGen.hpp>
#include <hspp/Enchants/Powers.hpp>

namespace Hearthstonepp
{
Powers::Powers()
{
    CoreCardsGen::AddAll(m_powers);
}

Powers::~Powers()
{
    for (const auto& power : m_powers)
    {
        delete power.second;
    }

    m_powers.clear();
}

Powers& Powers::GetInstance()
{
    static Powers instance;
    return instance;
}

Power* Powers::FindPowerByCardID(std::string cardID) const
{
    const auto res = m_powers.find(cardID);
    if (res != m_powers.end())
    {
        return res->second;
    }

    return nullptr;
}
}  // namespace Hearthstonepp
