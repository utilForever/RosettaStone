// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/StormwindCardsGen.hpp>

namespace RosettaStone::PlayMode
{
void StormwindCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddDruidNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddPriestNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddRogueNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddShamanNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddDemonHunter(std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddDemonHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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