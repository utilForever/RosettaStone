// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/BrmCardsGen.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks.hpp>

namespace RosettaStone::PlayMode
{
void BrmCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
}

void BrmCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
}

void BrmCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
}

void BrmCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
}

void BrmCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
}

void BrmCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
}

void BrmCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
}

void BrmCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
}

void BrmCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
}

void BrmCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
}

void BrmCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
}

void BrmCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
}

void BrmCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
}

void BrmCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
}

void BrmCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
}

void BrmCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
}

void BrmCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
}

void BrmCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
}

void BrmCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
}

void BrmCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
}

void BrmCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
}

void BrmCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
}

void BrmCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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