// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/IcecrownCardsGen.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks.hpp>

namespace RosettaStone::PlayMode
{
void IcecrownCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
}

void IcecrownCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
}

void IcecrownCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
}

void IcecrownCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
}

void IcecrownCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
}

void IcecrownCardsGen::AddHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void IcecrownCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
}

void IcecrownCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
}

void IcecrownCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
}

void IcecrownCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void IcecrownCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
}

void IcecrownCardsGen::AddPriestNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void IcecrownCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
}

void IcecrownCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
}

void IcecrownCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
}

void IcecrownCardsGen::AddShamanNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void IcecrownCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
}

void IcecrownCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void IcecrownCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
}

void IcecrownCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void IcecrownCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
}

void IcecrownCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void IcecrownCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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