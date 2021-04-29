// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/LoECardsGen.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks.hpp>

namespace RosettaStone::PlayMode
{
void LoECardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
}

void LoECardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
}

void LoECardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
}

void LoECardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
}

void LoECardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
}

void LoECardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
}

void LoECardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
}

void LoECardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
}

void LoECardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
}

void LoECardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
}

void LoECardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
}

void LoECardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
}

void LoECardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
}

void LoECardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
}

void LoECardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
}

void LoECardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
}

void LoECardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
}

void LoECardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
}

void LoECardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
}

void LoECardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
}

void LoECardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
}

void LoECardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
}

void LoECardsGen::AddAll(std::map<std::string, CardDef>& cards)
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