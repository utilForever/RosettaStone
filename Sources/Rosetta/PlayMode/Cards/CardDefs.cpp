// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/BlackTempleCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/BoomsdayCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/CoreCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/DalaranCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/DemonHunterInitCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/DragonsCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/Expert1CardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/GvgCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/HoFCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/LootapaloozaCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/UldumCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/YoDCardsGen.hpp>
#include <Rosetta/PlayMode/Cards/CardDefs.hpp>

namespace RosettaStone::PlayMode
{
std::map<std::string, CardDef> CardDefs::m_data;

CardDefs::CardDefs()
{
    CoreCardsGen::AddAll(m_data);
    Expert1CardsGen::AddAll(m_data);
    DemonHunterInitCardsGen::AddAll(m_data);
    HoFCardsGen::AddAll(m_data);
    GvgCardsGen::AddAll(m_data);
    LootapaloozaCardsGen::AddAll(m_data);
    BoomsdayCardsGen::AddAll(m_data);
    DalaranCardsGen::AddAll(m_data);
    UldumCardsGen::AddAll(m_data);
    DragonsCardsGen::AddAll(m_data);
    YoDCardsGen::AddAll(m_data);
    BlackTempleCardsGen::AddAll(m_data);
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
}  // namespace RosettaStone::PlayMode
