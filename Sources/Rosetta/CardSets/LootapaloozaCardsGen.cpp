// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/CardSets/LootapaloozaCardsGen.hpp>

namespace RosettaStone
{
void LootapaloozaCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddDruidNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddMageNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddPriestNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddRogueNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddShamanNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void LootapaloozaCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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
}  // namespace RosettaStone
