// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/TheBarrensCardsGen.hpp>

namespace RosettaStone::PlayMode
{
void TheBarrensCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
}

void TheBarrensCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
}

void TheBarrensCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
}

void TheBarrensCardsGen::AddDruidNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void TheBarrensCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
}

void TheBarrensCardsGen::AddHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void TheBarrensCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
}

void TheBarrensCardsGen::AddMageNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void TheBarrensCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
}

void TheBarrensCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void TheBarrensCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
}

void TheBarrensCardsGen::AddPriestNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void TheBarrensCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
}

void TheBarrensCardsGen::AddRogueNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void TheBarrensCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
}

void TheBarrensCardsGen::AddShamanNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void TheBarrensCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
}

void TheBarrensCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void TheBarrensCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
}

void TheBarrensCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void TheBarrensCardsGen::AddDemonHunter(std::map<std::string, CardDef>& cards)
{
}

void TheBarrensCardsGen::AddDemonHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void TheBarrensCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - NEUTRAL
    // [BAR_080] Shadow Hunter Vol'jin - COST:5 [ATK:3/HP:6]
    // - Set: THE_BARRENS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a minion.
    //       Swap it with a random one in its owners hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void TheBarrensCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void TheBarrensCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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