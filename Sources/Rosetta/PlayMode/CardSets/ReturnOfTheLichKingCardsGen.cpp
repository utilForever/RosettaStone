// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/ReturnOfTheLichKingCardsGen.hpp>

namespace RosettaStone::PlayMode
{
void ReturnOfTheLichKingCardsGen::AddHeroes(
    std::map<std::string, CardDef>& cards)
{
}

void ReturnOfTheLichKingCardsGen::AddHeroPowers(
    std::map<std::string, CardDef>& cards)
{
}

void ReturnOfTheLichKingCardsGen::AddDruid(
    std::map<std::string, CardDef>& cards)
{
}

void ReturnOfTheLichKingCardsGen::AddDruidNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void ReturnOfTheLichKingCardsGen::AddHunter(
    std::map<std::string, CardDef>& cards)
{
}

void ReturnOfTheLichKingCardsGen::AddHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void ReturnOfTheLichKingCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
}

void ReturnOfTheLichKingCardsGen::AddMageNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void ReturnOfTheLichKingCardsGen::AddPaladin(
    std::map<std::string, CardDef>& cards)
{
}

void ReturnOfTheLichKingCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void ReturnOfTheLichKingCardsGen::AddPriest(
    std::map<std::string, CardDef>& cards)
{
}

void ReturnOfTheLichKingCardsGen::AddPriestNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void ReturnOfTheLichKingCardsGen::AddRogue(
    std::map<std::string, CardDef>& cards)
{
}

void ReturnOfTheLichKingCardsGen::AddRogueNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void ReturnOfTheLichKingCardsGen::AddShaman(
    std::map<std::string, CardDef>& cards)
{
}

void ReturnOfTheLichKingCardsGen::AddShamanNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void ReturnOfTheLichKingCardsGen::AddWarlock(
    std::map<std::string, CardDef>& cards)
{
}

void ReturnOfTheLichKingCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void ReturnOfTheLichKingCardsGen::AddWarrior(
    std::map<std::string, CardDef>& cards)
{
}

void ReturnOfTheLichKingCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void ReturnOfTheLichKingCardsGen::AddDemonHunter(
    std::map<std::string, CardDef>& cards)
{
}

void ReturnOfTheLichKingCardsGen::AddDemonHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void ReturnOfTheLichKingCardsGen::AddNeutral(
    std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- SPELL - NEUTRAL
    // [RLK_590] The Sunwell - COST:9
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Fill your hand with random spells.
    //       Costs (1) less for each other card in your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
}

void ReturnOfTheLichKingCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void ReturnOfTheLichKingCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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
