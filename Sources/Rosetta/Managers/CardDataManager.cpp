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
PowersType CardDataManager::m_powers;
PlayReqsType CardDataManager::m_playReqs;
EntouragesType CardDataManager::m_entourages;

CardDataManager::CardDataManager()
{
    //CoreCardsGen::AddAll(m_powers, m_playReqs, m_entourages);
    //Expert1CardsGen::AddAll(m_powers, m_playReqs, m_entourages);
    //HoFCardsGen::AddAll(m_powers, m_playReqs, m_entourages);
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

Power CardDataManager::FindPowerByCardID(const std::string_view& cardID)
{
    for (auto& power : m_powers)
    {
        if (power.first == cardID)
        {
            return std::move(power.second);
        }
    }

    return Power();
}

PlayReqs CardDataManager::FindPlayReqsByCardID(const std::string_view& cardID)
{
    for (auto& playReqs : m_playReqs)
    {
        if (playReqs.first == cardID)
        {
            return playReqs.second;
        }
    }

    return PlayReqs();
}

Entourages CardDataManager::FindEntouragesByCardID(
    const std::string_view& cardID)
{
    for (auto& entourages : m_entourages)
    {
        if (entourages.first == cardID)
        {
            return entourages.second;
        }
    }

    return Entourages();
}
}  // namespace RosettaStone
