// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/NaxxCardsGen.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks.hpp>

namespace RosettaStone::PlayMode
{
void NaxxCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
}

void NaxxCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
}

void NaxxCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
}

void NaxxCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
}

void NaxxCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
}

void NaxxCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
}

void NaxxCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
}

void NaxxCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
}

void NaxxCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
}

void NaxxCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
}

void NaxxCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
}

void NaxxCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
}

void NaxxCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
}

void NaxxCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
}

void NaxxCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
}

void NaxxCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
}

void NaxxCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
}

void NaxxCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
}

void NaxxCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
}

void NaxxCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
}

void NaxxCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
}

void NaxxCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
}

void NaxxCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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