// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/CardSets/AlteracValleyCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/BlackTempleCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/BoomsdayCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/BrmCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/CoreCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/DalaranCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/DarkmoonFaireCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/DemonHunterInitCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/DragonsCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/Expert1CardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/GangsCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/GilneasCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/GvgCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/IcecrownCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/KaraCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/LegacyCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/LoECardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/LootapaloozaCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/NaxxCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/OgCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/Placeholder202204CardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/ReturnOfTheLichKingCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/RevendrethCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/ScholomanceCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/StormwindCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/TgtCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/TheBarrensCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/TheSunkenCityCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/TrollCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/UldumCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/UngoroCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/VanillaCardsGen.hpp>
#include <Rosetta/PlayMode/CardSets/YoDCardsGen.hpp>
#include <Rosetta/PlayMode/Cards/CardDefs.hpp>

namespace RosettaStone::PlayMode
{
std::map<std::string, CardDef> CardDefs::m_data;

CardDefs::CardDefs()
{
    AlteracValleyCardsGen::AddAll(m_data);
    VanillaCardsGen::AddAll(m_data);
    CoreCardsGen::AddAll(m_data);
    LegacyCardsGen::AddAll(m_data);
    Expert1CardsGen::AddAll(m_data);
    DemonHunterInitCardsGen::AddAll(m_data);
    NaxxCardsGen::AddAll(m_data);
    GvgCardsGen::AddAll(m_data);
    BrmCardsGen::AddAll(m_data);
    TgtCardsGen::AddAll(m_data);
    LoECardsGen::AddAll(m_data);
    OgCardsGen::AddAll(m_data);
    KaraCardsGen::AddAll(m_data);
    GangsCardsGen::AddAll(m_data);
    UngoroCardsGen::AddAll(m_data);
    IcecrownCardsGen::AddAll(m_data);
    LootapaloozaCardsGen::AddAll(m_data);
    GilneasCardsGen::AddAll(m_data);
    BoomsdayCardsGen::AddAll(m_data);
    TrollCardsGen::AddAll(m_data);
    DalaranCardsGen::AddAll(m_data);
    UldumCardsGen::AddAll(m_data);
    DragonsCardsGen::AddAll(m_data);
    YoDCardsGen::AddAll(m_data);
    BlackTempleCardsGen::AddAll(m_data);
    ScholomanceCardsGen::AddAll(m_data);
    DarkmoonFaireCardsGen::AddAll(m_data);
    TheBarrensCardsGen::AddAll(m_data);
    StormwindCardsGen::AddAll(m_data);
    TheSunkenCityCardsGen::AddAll(m_data);
    RevendrethCardsGen::AddAll(m_data);
    ReturnOfTheLichKingCardsGen::AddAll(m_data);
    Placeholder202204CardsGen::AddAll(m_data);
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
