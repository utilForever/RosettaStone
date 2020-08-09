// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/ScholomanceCardsGen.hpp>
#include <Rosetta/PlayMode/Enchants/Enchants.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/AddEnchantmentTask.hpp>

using namespace RosettaStone::PlayMode::SimpleTasks;

namespace RosettaStone::PlayMode
{
void ScholomanceCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
}

void ScholomanceCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
}

void ScholomanceCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
}

void ScholomanceCardsGen::AddDruidNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void ScholomanceCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
}

void ScholomanceCardsGen::AddHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void ScholomanceCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
}

void ScholomanceCardsGen::AddMageNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void ScholomanceCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
}

void ScholomanceCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void ScholomanceCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
}

void ScholomanceCardsGen::AddPriestNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void ScholomanceCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
}

void ScholomanceCardsGen::AddRogueNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void ScholomanceCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
}

void ScholomanceCardsGen::AddShamanNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void ScholomanceCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
}

void ScholomanceCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void ScholomanceCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
}

void ScholomanceCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void ScholomanceCardsGen::AddDemonHunter(std::map<std::string, CardDef>& cards)
{
}

void ScholomanceCardsGen::AddDemonHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void ScholomanceCardsGen::AddDual(std::map<std::string, CardDef>& cards)
{
}

void ScholomanceCardsGen::AddDualNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void ScholomanceCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    Power power;

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_231] Intrepid Initiate - COST:1 [ATK:1/HP:2]
    // - Set: Scholomance, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Spellburst:</b> Gain +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddSpellburstTask(
        std::make_shared<AddEnchantmentTask>("SCH_231e", EntityType::SOURCE));
    cards.emplace("SCH_231", CardDef(power));
}

void ScholomanceCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SCH_231e] Ready for School (*) - COST:0
    // - Set: Scholomance
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("SCH_231e"));
    cards.emplace("SCH_231e", CardDef(power));
}

void ScholomanceCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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

    AddDual(cards);
    AddDualNonCollect(cards);

    AddNeutral(cards);
    AddNeutralNonCollect(cards);
}
}  // namespace RosettaStone::PlayMode
