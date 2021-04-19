// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/TrollCardsGen.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks.hpp>

namespace RosettaStone::PlayMode
{
void TrollCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
}

void TrollCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
}

void TrollCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
}

void TrollCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
}

void TrollCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
}

void TrollCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
}

void TrollCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
}

void TrollCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
}

void TrollCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
}

void TrollCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
}

void TrollCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
}

void TrollCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
}

void TrollCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
}

void TrollCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
}

void TrollCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
}

void TrollCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
}

void TrollCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
}

void TrollCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
}

void TrollCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
}

void TrollCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
}

void TrollCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
}

void TrollCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
}

void TrollCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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