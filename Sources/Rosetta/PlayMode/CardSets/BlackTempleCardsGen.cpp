// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/BlackTempleCardsGen.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ManaCrystalTask.hpp>

using namespace RosettaStone::PlayMode::SimpleTasks;

namespace RosettaStone::PlayMode
{
void BlackTempleCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------------------ SPELL - DRUID
    // [BT_130] Overgrowth - COST:4
    // - Faction: Neutral, Set: Core, Rarity: Common
    // --------------------------------------------------------
    // Text: Gain two empty Mana Crystals.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<ManaCrystalTask>(2, false));
    cards.emplace("BT_130", CardDef(power));
}

void BlackTempleCardsGen::AddDruidNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddMageNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddPriestNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddRogueNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddShamanNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddDemonHunter(std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddDemonHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void BlackTempleCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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
