// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/VanillaCardsGen.hpp>

namespace RosettaStone::PlayMode
{
void VanillaCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
}

void VanillaCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
}

void VanillaCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
}

void VanillaCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
}

void VanillaCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
}

void VanillaCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
}

void VanillaCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
}

void VanillaCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
}

void VanillaCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
}

void VanillaCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void VanillaCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
}

void VanillaCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
}

void VanillaCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
}

void VanillaCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
}

void VanillaCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
}

void VanillaCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
}

void VanillaCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
}

void VanillaCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void VanillaCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
}

void VanillaCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void VanillaCardsGen::AddDemonHunter(std::map<std::string, CardDef>& cards)
{
}

void VanillaCardsGen::AddDemonHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void VanillaCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
}

void VanillaCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void VanillaCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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