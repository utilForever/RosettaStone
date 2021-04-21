// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/GilneasCardsGen.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks.hpp>

namespace RosettaStone::PlayMode
{
void GilneasCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
}

void GilneasCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
}

void GilneasCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
}

void GilneasCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GilneasCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
}

void GilneasCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GilneasCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
}

void GilneasCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GilneasCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
}

void GilneasCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GilneasCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
}

void GilneasCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GilneasCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
}

void GilneasCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GilneasCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
}

void GilneasCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GilneasCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
}

void GilneasCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GilneasCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
}

void GilneasCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GilneasCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
}

void GilneasCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GilneasCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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