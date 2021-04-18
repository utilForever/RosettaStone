// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/OgCardsGen.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks.hpp>

namespace RosettaStone::PlayMode
{
void OgCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
}

void OgCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
}

void OgCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
}

void OgCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
}

void OgCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
}

void OgCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
}

void OgCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
}

void OgCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
}

void OgCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
}

void OgCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
}

void OgCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
}

void OgCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
}

void OgCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
}

void OgCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
}

void OgCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
}

void OgCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
}

void OgCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
}

void OgCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
}

void OgCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
}

void OgCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
}

void OgCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
}

void OgCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
}

void OgCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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