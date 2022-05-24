// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/GangsCardsGen.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks.hpp>

namespace RosettaStone::PlayMode
{
void GangsCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
}

void GangsCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
}

void GangsCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
}

void GangsCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GangsCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
}

void GangsCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GangsCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
}

void GangsCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GangsCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
}

void GangsCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GangsCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
}

void GangsCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GangsCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
}

void GangsCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GangsCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
}

void GangsCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GangsCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
}

void GangsCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GangsCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
}

void GangsCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GangsCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
}

void GangsCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GangsCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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