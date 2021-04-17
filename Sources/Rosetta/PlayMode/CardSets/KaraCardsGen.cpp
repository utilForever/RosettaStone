// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/KaraCardsGen.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks.hpp>

namespace RosettaStone::PlayMode
{
void KaraCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
}

void KaraCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
}

void KaraCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
}

void KaraCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
}

void KaraCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
}

void KaraCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
}

void KaraCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
}

void KaraCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
}

void KaraCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
}

void KaraCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
}

void KaraCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
}

void KaraCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
}

void KaraCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
}

void KaraCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
}

void KaraCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
}

void KaraCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
}

void KaraCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
}

void KaraCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
}

void KaraCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
}

void KaraCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
}

void KaraCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
}

void KaraCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
}

void KaraCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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