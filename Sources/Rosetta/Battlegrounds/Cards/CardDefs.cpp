// This code is based on Sabberstone project.
// Copyright (c) 2017-2021 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2024 Chris Ohk

#include <Rosetta/Battlegrounds/CardSets/BattlegroundsCardsGen.hpp>
#include <Rosetta/Battlegrounds/Cards/CardDefs.hpp>

namespace RosettaStone::Battlegrounds
{
std::map<std::string, CardDef> CardDefs::m_data;

CardDefs::CardDefs()
{
    BattlegroundsCardsGen::AddAll(m_data);
}

CardDefs::~CardDefs()
{
    m_data.clear();
}

CardDefs& CardDefs::GetInstance()
{
    static CardDefs instance;
    return instance;
}

CardDef CardDefs::FindCardDefByID(const std::string_view& id)
{
    for (auto& data : m_data)
    {
        if (data.first == id)
        {
            return data.second;
        }
    }

    return CardDef();
}
}  // namespace RosettaStone::Battlegrounds
