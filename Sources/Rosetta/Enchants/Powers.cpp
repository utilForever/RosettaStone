// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/CardSets/CoreCardsGen.hpp>
#include <Rosetta/CardSets/Expert1CardsGen.hpp>
#include <Rosetta/Enchants/Powers.hpp>

namespace RosettaStone
{
Powers::Powers()
{
    CoreCardsGen::AddAll(m_powers);
    Expert1CardsGen::AddAll(m_powers);
}

Powers::~Powers()
{
    m_powers.clear();
}

Powers& Powers::GetInstance()
{
    static Powers instance;
    return instance;
}

Power Powers::FindPowerByCardID(const std::string& cardID)
{
    const auto res = m_powers.find(cardID);
    if (res != m_powers.end())
    {
        return res->second;
    }

    return Power();
}
}  // namespace RosettaStone
