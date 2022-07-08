// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/RevendrethCardsGen.hpp>

namespace RosettaStone::PlayMode
{
void RevendrethCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
}

void RevendrethCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
}

void RevendrethCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
}

void RevendrethCardsGen::AddDruidNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void RevendrethCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
}

void RevendrethCardsGen::AddHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void RevendrethCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
}

void RevendrethCardsGen::AddMageNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void RevendrethCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
}

void RevendrethCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void RevendrethCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
}

void RevendrethCardsGen::AddPriestNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void RevendrethCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
}

void RevendrethCardsGen::AddRogueNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void RevendrethCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
}

void RevendrethCardsGen::AddShamanNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void RevendrethCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
}

void RevendrethCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void RevendrethCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
}

void RevendrethCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void RevendrethCardsGen::AddDemonHunter(std::map<std::string, CardDef>& cards)
{
}

void RevendrethCardsGen::AddDemonHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void RevendrethCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
}

void RevendrethCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void RevendrethCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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