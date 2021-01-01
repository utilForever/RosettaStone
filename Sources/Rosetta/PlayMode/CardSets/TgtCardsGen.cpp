// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/TgtCardsGen.hpp>

namespace RosettaStone::PlayMode
{
void TgtCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddAll(std::map<std::string, CardDef>& cards)
{
    AddHeroes(cards);
    AddHeroPowers(cards);

    AddDruid(cards);
    AddDruidNonCollect(cards);

    AddHunter(cards);
    AddHunterNonCollect(cards);

    AddMage(cards);
    AddMageNonCollect(cards);

    AddPaladin(cards);
    AddPaladinNonCollect(cards);

    AddPriest(cards);
    AddPriestNonCollect(cards);

    AddRogue(cards);
    AddRogueNonCollect(cards);

    AddShaman(cards);
    AddShamanNonCollect(cards);

    AddWarlock(cards);
    AddWarlockNonCollect(cards);

    AddWarrior(cards);
    AddWarriorNonCollect(cards);

    AddNeutral(cards);
    AddNeutralNonCollect(cards);
}
}  // namespace RosettaStone::PlayMode
