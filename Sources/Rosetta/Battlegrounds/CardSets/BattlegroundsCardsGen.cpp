// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Battlegrounds/CardSets/BattlegroundsCardsGen.hpp>

namespace RosettaStone::Battlegrounds
{
void BattlegroundsCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
}

void BattlegroundsCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
}

void BattlegroundsCardsGen::AddTier1Minions(
    std::map<std::string, CardDef>& cards)
{
}

void BattlegroundsCardsGen::AddTier2Minions(
    std::map<std::string, CardDef>& cards)
{
}

void BattlegroundsCardsGen::AddTier3Minions(
    std::map<std::string, CardDef>& cards)
{
}

void BattlegroundsCardsGen::AddTier4Minions(
    std::map<std::string, CardDef>& cards)
{
}

void BattlegroundsCardsGen::AddTier5Minions(
    std::map<std::string, CardDef>& cards)
{
}

void BattlegroundsCardsGen::AddTier6Minions(
    std::map<std::string, CardDef>& cards)
{
}

void BattlegroundsCardsGen::AddMinionsNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void BattlegroundsCardsGen::AddSpellsNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void BattlegroundsCardsGen::AddAll(std::map<std::string, CardDef>& cards)
{
    AddHeroes(cards);
    AddHeroPowers(cards);

    AddTier1Minions(cards);
    AddTier2Minions(cards);
    AddTier3Minions(cards);
    AddTier4Minions(cards);
    AddTier5Minions(cards);
    AddTier6Minions(cards);

    AddMinionsNonCollect(cards);
    AddSpellsNonCollect(cards);
}
}  // namespace RosettaStone::Battlegrounds
