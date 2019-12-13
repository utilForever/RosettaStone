// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/CardSets/CoreCardsGen.hpp>
#include <Rosetta/CardSets/Expert1CardsGen.hpp>
#include <Rosetta/CardSets/HoFCardsGen.hpp>
#include <Rosetta/Managers/CardDataManager.hpp>

namespace RosettaStone
{
std::map<std::string, Power> CardDataManager::m_powers;

CardDataManager::CardDataManager()
{
    CoreCardsGen::AddAll(m_powers);
    Expert1CardsGen::AddAll(m_powers);
    HoFCardsGen::AddAll(m_powers);
}

CardDataManager::~CardDataManager()
{
    m_powers.clear();
}

CardDataManager& CardDataManager::GetInstance()
{
    static CardDataManager instance;
    return instance;
}

Power CardDataManager::FindPowerByCardID(const std::string& cardID)
{
    const auto res = m_powers.find(cardID);
    if (res != m_powers.end())
    {
        return res->second;
    }

    return Power();
}
}  // namespace RosettaStone
