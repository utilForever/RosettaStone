// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/UngoroCardsGen.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks.hpp>

namespace RosettaStone::PlayMode
{
void UngoroCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
}

void UngoroCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
}

void UngoroCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
}

void UngoroCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
}

void UngoroCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
}

void UngoroCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
}

void UngoroCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
}

void UngoroCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
}

void UngoroCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
}

void UngoroCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
}

void UngoroCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
}

void UngoroCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
}

void UngoroCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
}

void UngoroCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
}

void UngoroCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
}

void UngoroCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
}

void UngoroCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
}

void UngoroCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
}

void UngoroCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
}

void UngoroCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
}

void UngoroCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
}

void UngoroCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
}

void UngoroCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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