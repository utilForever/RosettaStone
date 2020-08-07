// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/BlackTempleCardsGen.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/AddEnchantmentTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ConditionTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DrawStackTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/FilterStackTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ManaCrystalTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/RandomTask.hpp>

using namespace RosettaStone::PlayMode::SimpleTasks;

namespace RosettaStone::PlayMode
{
using SelfCondList = std::vector<std::shared_ptr<SelfCondition>>;

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
    Power power;

    // ----------------------------------------- SPELL - WARRIOR
    // [BT_124] Corsair Cache - COST:2
    // - Set: BLACK_TEMPLE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Draw a weapon.
    //       Give it +1 Durability.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::DECK));
    power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsWeapon()) }));
    power.AddPowerTask(std::make_shared<RandomTask>(EntityType::STACK, 1));
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BT_124e", EntityType::STACK));
    power.AddPowerTask(std::make_shared<DrawStackTask>(1));
    cards.emplace("BT_124", CardDef(power));
}

void BlackTempleCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------------- ENCHANTMENT - WARRIOR
    // [BT_124e] Void Sharpened
    // - Set: BLACK_TEMPLE
    // --------------------------------------------------------
    // Text: +1 Durability.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(std::make_shared<Enchant>(
        std::make_shared<Effect>(GameTag::DURABILITY, EffectOperator::ADD, 1)));
    cards.emplace("BT_124e", CardDef(power));
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
