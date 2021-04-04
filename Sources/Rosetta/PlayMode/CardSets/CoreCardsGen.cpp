// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/CoreCardsGen.hpp>

namespace RosettaStone::PlayMode
{
void CoreCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
}

void CoreCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
}

void CoreCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
}

void CoreCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
}

void CoreCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
}

void CoreCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
}

void CoreCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
}

void CoreCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
}

void CoreCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
}

void CoreCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
}

void CoreCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
}

void CoreCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
}

void CoreCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
}

void CoreCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
}

void CoreCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
}

void CoreCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
}

void CoreCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
}

void CoreCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
}

void CoreCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
}

void CoreCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
}

void CoreCardsGen::AddDemonHunter(std::map<std::string, CardDef>& cards)
{
}

void CoreCardsGen::AddDemonHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void CoreCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
}

void CoreCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
}

void CoreCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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

    AddDemonHunter(cards);
    AddDemonHunterNonCollect(cards);

    AddNeutral(cards);
    AddNeutralNonCollect(cards);
}
}  // namespace RosettaStone::PlayMode