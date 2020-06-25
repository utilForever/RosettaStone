// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Battlegrounds/CardSets/BattlegroundsCardsGen.hpp>
#include <Rosetta/Battlegrounds/Tasks/SimpleTasks/SummonTask.hpp>

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
    Power power;

    // --------------------------------- MINION - BATTLEGROUNDS
    // [CFM_315] Alleycat - TIER:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Gangs, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 1/1 Cat.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddBattlecryTask(SummonTask{ "CFM_315t", 1 });
    cards.emplace("CFM_315", CardDef{ std::move(power) });
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
    // --------------------------------- MINION - BATTLEGROUNDS
    // [CFM_315t] Tabbycat (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Gangs
    // --------------------------------------------------------
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
