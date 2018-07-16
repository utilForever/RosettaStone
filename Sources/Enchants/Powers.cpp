/*************************************************************************
> File Name: Powers.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Powers class that stores power in every card.
> Created Time: 2018/06/23
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <CardSets/BasicCardsGen.h>
#include <Enchants/Powers.h>

namespace Hearthstonepp
{
Powers* Powers::m_instance = nullptr;

Powers* Powers::GetInstance()
{
    if (m_instance == nullptr)
    {
        m_instance = new Powers();
    }

    return m_instance;
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

Powers::Powers()
{
    BasicCardsGen::AddAll(m_powers);
}
}
