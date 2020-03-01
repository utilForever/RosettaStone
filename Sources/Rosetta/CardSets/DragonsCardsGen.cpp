// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Auras/AdaptiveEffect.hpp>
#include <Rosetta/CardSets/DragonsCardsGen.hpp>
#include <Rosetta/Conditions/RelaCondition.hpp>
#include <Rosetta/Enchants/Enchants.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddEnchantmentTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddLackeyTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddStackToTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/ConditionTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DamageTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DestroyTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DrawStackTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DrawTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/EnqueueTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/FilterStackTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/FlagTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/InvokeTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/QuestProgressTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/RandomCardTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/RandomTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/SummonTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/WeaponTask.hpp>

using namespace RosettaStone::SimpleTasks;

namespace RosettaStone
{
using PlayReqs = std::map<PlayReq, int>;
using ChooseCardIDs = std::vector<std::string>;
using Entourages = std::vector<std::string>;
using TaskList = std::vector<std::shared_ptr<ITask>>;
using EntityTypeList = std::vector<EntityType>;
using SelfCondList = std::vector<std::shared_ptr<SelfCondition>>;
using RelaCondList = std::vector<std::shared_ptr<RelaCondition>>;
using EffectList = std::vector<std::shared_ptr<IEffect>>;

void DragonsCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------------- HERO - WARLOCK
    // [DRG_600] Galakrond, the Wretched - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon 1 random Demon. <i>(@)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 2
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55807
    // - 676 = 1
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<RandomCardTask>(
        CardType::MINION, CardClass::INVALID, Race::DEMON));
    power.AddPowerTask(std::make_shared<SummonTask>());
    cards.emplace("DRG_600", CardDef(power, 0, 55807));

    // ----------------------------------------- HERO - WARLOCK
    // [DRG_600t2] Galakrond, the Apocalypse (*) - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon 2 random Demons. <i>(@)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 2
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55807
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{ std::make_shared<RandomCardTask>(
                      CardType::MINION, CardClass::INVALID, Race::DEMON),
                  std::make_shared<SummonTask>() },
        2));
    cards.emplace("DRG_600t2", CardDef(power, 0, 55807));

    // ----------------------------------------- HERO - WARLOCK
    // [DRG_600t3] Galakrond, Azeroth's End (*) - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon 4 random Demons.
    //       Equip a 5/2 Claw.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55807
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{ std::make_shared<RandomCardTask>(
                      CardType::MINION, CardClass::INVALID, Race::DEMON),
                  std::make_shared<SummonTask>() },
        4));
    power.AddPowerTask(std::make_shared<WeaponTask>("DRG_238ht"));
    cards.emplace("DRG_600t3", CardDef(power, 0, 55807));

    // ------------------------------------------- HERO - ROGUE
    // [DRG_610] Galakrond, the Nightmare - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw 1 card. It costs (0).
    //       <i>(@)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 2
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55806
    // - 676 = 1
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DrawTask>(1, true));
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DRG_610e", EntityType::STACK));
    cards.emplace("DRG_610", CardDef(power, 0, 55806));

    // ------------------------------------------- HERO - ROGUE
    // [DRG_610t2] Galakrond, the Apocalypse (*) - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw 2 cards. They cost (0).
    //       <i>(@)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 2
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55806
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DrawTask>(2, true));
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DRG_610e", EntityType::STACK));
    cards.emplace("DRG_610t2", CardDef(power, 0, 55806));

    // ------------------------------------------- HERO - ROGUE
    // [DRG_610t3] Galakrond, Azeroth's End (*) - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw 4 cards. They cost (0).
    //       Equip a 5/2 Claw.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55806
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DrawTask>(4, true));
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DRG_610e", EntityType::STACK));
    power.AddPowerTask(std::make_shared<WeaponTask>("DRG_238ht"));
    cards.emplace("DRG_610t3", CardDef(power, 0, 55806));

    // ------------------------------------------ HERO - SHAMAN
    // [DRG_620] Galakrond, the Tempest - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two 2/2 Storms with <b>Rush</b>.
    //       <i>(@)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 2
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55808
    // - 676 = 1
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<SummonTask>("DRG_620t4", 2));
    cards.emplace("DRG_620", CardDef(power, 0, 55808));

    // ------------------------------------------ HERO - SHAMAN
    // [DRG_620t2] Galakrond, the Apocalypse (*) - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two 4/4 Storms with <b>Rush</b>.
    //       <i>(@)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 2
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55808
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<SummonTask>("DRG_620t5", 2));
    cards.emplace("DRG_620t2", CardDef(power, 0, 55808));

    // ------------------------------------------ HERO - SHAMAN
    // [DRG_620t3] Galakrond, Azeroth's End (*) - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two 8/8 Storms with <b>Rush</b>.
    //       Equip a 5/2 Claw.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55808
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<SummonTask>("DRG_620t6", 2));
    power.AddPowerTask(std::make_shared<WeaponTask>("DRG_238ht"));
    cards.emplace("DRG_620t3", CardDef(power, 0, 55808));

    // ----------------------------------------- HERO - WARRIOR
    // [DRG_650] Galakrond, the Unbreakable - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw 1 minion. Give it +4/+4.
    //       <i>(@)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 2
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55805
    // - 676 = 1
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::DECK));
    power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsMinion()) }));
    power.AddPowerTask(std::make_shared<RandomTask>(EntityType::STACK, 1));
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DRG_650e", EntityType::STACK));
    power.AddPowerTask(std::make_shared<DrawStackTask>(1));
    cards.emplace("DRG_650", CardDef(power, 0, 55805));

    // ----------------------------------------- HERO - WARRIOR
    // [DRG_650t2] Galakrond, the Apocalypse (*) - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw 2 minions. Give them +4/+4.
    //       <i>(@)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 2
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55805
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::DECK));
    power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsMinion()) }));
    power.AddPowerTask(std::make_shared<RandomTask>(EntityType::STACK, 2));
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DRG_650e2", EntityType::STACK));
    power.AddPowerTask(std::make_shared<DrawStackTask>(2));
    cards.emplace("DRG_650t2", CardDef(power, 0, 55805));

    // ----------------------------------------- HERO - WARRIOR
    // [DRG_650t3] Galakrond, Azeroth's End (*) - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw 4 minions. Give them +4/+4.
    //       Equip a 5/2 Claw.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55805
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::DECK));
    power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsMinion()) }));
    power.AddPowerTask(std::make_shared<RandomTask>(EntityType::STACK, 4));
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DRG_650e3", EntityType::STACK));
    power.AddPowerTask(std::make_shared<DrawStackTask>(4));
    power.AddPowerTask(std::make_shared<WeaponTask>("DRG_238ht"));
    cards.emplace("DRG_650t3", CardDef(power, 0, 55805));

    // ------------------------------------------ HERO - PRIEST
    // [DRG_660] Galakrond, the Unspeakable - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy 1 random enemy minion.
    //       <i>(@)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 2
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55810
    // - 676 = 1
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::ENEMY_MINIONS));
    power.AddPowerTask(std::make_shared<RandomTask>(EntityType::STACK, 1));
    power.AddPowerTask(std::make_shared<DestroyTask>(EntityType::STACK));
    cards.emplace("DRG_660", CardDef(power, 0, 55810));

    // ------------------------------------------ HERO - PRIEST
    // [DRG_660t2] Galakrond, the Apocalypse (*) - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy 2 random enemy minions.
    //       <i>(@)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 2
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55810
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::ENEMY_MINIONS));
    power.AddPowerTask(std::make_shared<RandomTask>(EntityType::STACK, 2));
    power.AddPowerTask(std::make_shared<DestroyTask>(EntityType::STACK));
    cards.emplace("DRG_660t2", CardDef(power, 0, 55810));

    // ------------------------------------------ HERO - PRIEST
    // [DRG_660t3] Galakrond, Azeroth's End (*) - COST:7 [ATK:0/HP:30]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy 4 random enemy minions.
    //       Equip a 5/2 Claw.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 55810
    // - GALAKROND_HERO_CARD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::ENEMY_MINIONS));
    power.AddPowerTask(std::make_shared<RandomTask>(EntityType::STACK, 4));
    power.AddPowerTask(std::make_shared<DestroyTask>(EntityType::STACK));
    power.AddPowerTask(std::make_shared<WeaponTask>("DRG_238ht"));
    cards.emplace("DRG_660t3", CardDef(power, 0, 55810));
}

void DragonsCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------- HERO_POWER - WARRIOR
    // [DRG_238p] Galakrond's Might (*) - COST:2
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Give your hero +3 Attack this turn.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DRG_238t10e", EntityType::HERO));
    cards.emplace("DRG_238p", CardDef(power));

    // ------------------------------------- HERO_POWER - ROGUE
    // [DRG_238p2] Galakrond's Guile (*) - COST:2
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Add a <b>Lackey</b> to your hand.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<AddLackeyTask>(1));
    cards.emplace("DRG_238p2", CardDef(power));

    // ----------------------------------- HERO_POWER - WARLOCK
    // [DRG_238p3] Galakrond's Malice (*) - COST:2
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Summon two 1/1 Imps.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<SummonTask>("DRG_238t12t2", 2));
    cards.emplace("DRG_238p3", CardDef(power));

    // ------------------------------------ HERO_POWER - SHAMAN
    // [DRG_238p4] Galakrond's Fury (*) - COST:2
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Summon a 2/1 Elemental with <b>Rush</b>.
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<SummonTask>("DRG_238t14t3", 1));
    cards.emplace("DRG_238p4", CardDef(power));

    // ------------------------------------ HERO_POWER - PRIEST
    // [DRG_238p5] Galakrond's Wit (*) - COST:2
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Add a random Priest minion to your hand.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<RandomCardTask>(CardType::MINION, CardClass::PRIEST));
    power.AddPowerTask(std::make_shared<AddStackToTask>(EntityType::HAND));
    cards.emplace("DRG_238p5", CardDef(power));
}

void DragonsCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ SPELL - DRUID
    // [DRG_051] Strength in Numbers - COST:1
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Sidequest:</b> Spend 10 Mana on minions.
    //       <b>Reward:</b> Summon a minion from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - QUEST_PROGRESS_TOTAL = 10
    // - SIDEQUEST = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [DRG_311] Treenforcements - COST:1
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Give a minion +2 Health and
    //       <b>Taunt</b>; or Summon a 2/2 Treant.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [DRG_312] Shrubadier - COST:2 [ATK:1/HP:1]
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 2/2 Treant.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [DRG_313] Emerald Explorer - COST:6 [ATK:4/HP:8]
    // - Race: Dragon, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> <b>Discover</b> a Dragon.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [DRG_314] Aeroponics - COST:5
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: Draw 2 cards.
    //       Costs (2) less for each Treant you control.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [DRG_315] Embiggen - COST:0
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: Give all minions in your deck +2/+2.
    //       They cost (1) more <i>(up to 10)</i>.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [DRG_317] Secure the Deck - COST:1
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Sidequest:</b> Attack twice with your hero.
    //       <b>Reward:</b> Add 3 'Claw' spells to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - QUEST_PROGRESS_TOTAL = 2
    // - SIDEQUEST = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [DRG_318] Breath of Dreams - COST:2
    // - Faction: Neutral, Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: Draw a card. If you're holding a Dragon,
    //       gain an empty Mana Crystal.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [DRG_319] Goru the Mightree - COST:7 [ATK:5/HP:10]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Taunt</b> <b>Battlecry:</b> For the rest of
    //       the game, your Treants have +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [DRG_320] Ysera, Unleashed - COST:9 [ATK:4/HP:12]
    // - Race: Dragon, Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Shuffle 7 Dream Portals into your deck.
    //       When drawn, summon a random Dragon.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void DragonsCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ SPELL - DRUID
    // [DRG_311a] Spin 'em Up (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Summon a 2/2 Treant.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [DRG_311b] Small Repairs (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Give a minion +2 Health and <b>Taunt</b>.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [DRG_311t] Treant (*) - COST:2 [ATK:2/HP:2]
    // - Faction: Neutral, Set: Dragons
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [DRG_315e] Embiggened (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [DRG_315e2] Costly Embiggening (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Costs (1) more.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [DRG_320t] Dream Portal (*) - COST:9
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Casts When Drawn</b> Summon a random Dragon.
    // --------------------------------------------------------
    // GameTag:
    // - TOPDECK = 1
    // --------------------------------------------------------
    // RefTag:
    // - CASTSWHENDRAWN = 1
    // --------------------------------------------------------
}

void DragonsCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------------- SPELL - HUNTER
    // [DRG_006] Corrosive Breath - COST:2
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 3 damage to a minion. If you're holding
    //       a Dragon, it also hits the enemy hero.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsHoldingRace(Race::DRAGON)) }));
    power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{
            std::make_shared<DamageTask>(EntityType::TARGET, 3, true),
            std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 3, true) }));
    power.AddPowerTask(std::make_shared<FlagTask>(
        false,
        TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 3, true) }));
    cards.emplace(
        "DRG_006",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));

    // ---------------------------------------- WEAPON - HUNTER
    // [DRG_007] Stormhammer - COST:3 [ATK:3/HP:0]
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: Doesn't lose Durability while you control a Dragon.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(std::make_shared<AdaptiveEffect>(
        std::make_shared<SelfCondition>(
            SelfCondition::IsControllingRace(Race::DRAGON)),
        GameTag::IMMUNE));
    cards.emplace("DRG_007", CardDef(power));

    // ---------------------------------------- MINION - HUNTER
    // [DRG_010] Diving Gryphon - COST:3 [ATK:4/HP:1]
    // - Race: Beast, Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b> <b>Battlecry:</b> Draw a
    //       <b>Rush</b> minion from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - RUSH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::DECK));
    power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRush()) }));
    power.AddPowerTask(std::make_shared<RandomTask>(EntityType::STACK, 1));
    power.AddPowerTask(std::make_shared<DrawStackTask>(1));
    cards.emplace("DRG_010", CardDef(power));

    // ---------------------------------------- MINION - HUNTER
    // [DRG_095] Veranus - COST:6 [ATK:7/HP:6]
    // - Race: Dragon, Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Change the Health of all enemy minions to 1.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [DRG_251] Clear the Way - COST:1
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Sidequest:</b> Summon 3 <b>Rush</b> minions.
    //       <b>Reward:</b> Summon a 4/4 Gryphon with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - QUEST_PROGRESS_TOTAL = 3
    // - SIDEQUEST = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [DRG_252] Phase Stalker - COST:2 [ATK:2/HP:3]
    // - Race: Beast, Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you use your Hero Power,
    //       cast a <b>Secret</b> from your deck.
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [DRG_253] Dwarven Sharpshooter - COST:1 [ATK:1/HP:3]
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: Your Hero Power can target minions.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [DRG_254] Primordial Explorer - COST:3 [ATK:2/HP:3]
    // - Race: Dragon, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    //       <b>Battlecry:</b> <b>Discover</b> a Dragon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - POISONOUS = 1
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [DRG_255] Toxic Reinforcements - COST:1
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Sidequest:</b> Use your Hero Power three times.
    //       <b>Reward:</b> Summon three 1/1 Leper Gnomes.
    // --------------------------------------------------------
    // GameTag:
    // - QUEST_PROGRESS_TOTAL = 3
    // - QUEST_REWARD_DATABASE_ID = 41127
    // - SIDEQUEST = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::USE_HERO_POWER));
    power.GetTrigger()->tasks = { std::make_shared<QuestProgressTask>(
        TaskList{ std::make_shared<SummonTask>("DRG_255t2", 3) }) };
    cards.emplace("DRG_255", CardDef(power, 3, 0));

    // ---------------------------------------- MINION - HUNTER
    // [DRG_256] Dragonbane - COST:4 [ATK:3/HP:5]
    // - Race: Mechanical, Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you use your Hero Power,
    //       deal 5 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
}

void DragonsCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- ENCHANTMENT - HUNTER
    // [DRG_095e] Intimidated (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Health changed to 1.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [DRG_251t] Gryphon (*) - COST:4 [ATK:4/HP:4]
    // - Race: Beast, Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
}

void DragonsCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ MINION - MAGE
    // [DRG_102] Azure Explorer - COST:4 [ATK:2/HP:3]
    // - Race: Dragon, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Spell Damage +2</b>
    //       <b>Battlecry:</b> <b>Discover</b> a Dragon.
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 2
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [DRG_104] Chenvaala - COST:3 [ATK:2/HP:5]
    // - Race: Elemental, Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you cast three spells in a turn,
    //       summon a 5/5 Elemental.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [DRG_106] Arcane Breath - COST:1
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 2 damage to a minion. If you're holding a Dragon,
    //       <b>Discover</b> a spell.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [DRG_107] Violet Spellwing - COST:1 [ATK:1/HP:1]
    // - Race: Elemental, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add an 'Arcane Missiles' spell
    //       to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [DRG_109] Mana Giant - COST:8 [ATK:8/HP:8]
    // - Race: Elemental, Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: Costs (1) less for each card you've played this
    //       game that didn't start in your deck.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [DRG_270] Malygos, Aspect of Magic - COST:5 [ATK:2/HP:8]
    // - Race: Dragon, Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       <b>Discover</b> an upgraded Mage spell.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [DRG_321] Rolling Fireball - COST:5
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 8 damage to a minion. Any excess damage
    //       continues to the left or right.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [DRG_322] Dragoncaster - COST:6 [ATK:4/HP:4]
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       your next spell this turn costs (0).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [DRG_323] Learn Draconic - COST:1
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Sidequest:</b> Spend 8 Mana on spells.
    //       <b>Reward:</b> Summon a 6/6 Dragon.
    // --------------------------------------------------------
    // GameTag:
    // - QUEST_PROGRESS_TOTAL = 8
    // - QUEST_REWARD_DATABASE_ID = 55282
    // - SIDEQUEST = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [DRG_324] Elemental Allies - COST:1
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Sidequest:</b> Play an Elemental 2 turns in a row.
    //       <b>Reward:</b> Draw 3 spells from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - QUEST_PROGRESS_TOTAL = 2
    // - QUEST_REWARD_DATABASE_ID = 395
    // - SIDEQUEST = 1
    // --------------------------------------------------------
}

void DragonsCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ MINION - MAGE
    // [DRG_104t2] Snow Elemental (*) - COST:5 [ATK:5/HP:5]
    // - Race: Elemental, Set: Dragons
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [DRG_270t1] Malygos's Intellect (*) - COST:3
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Draw 4 cards.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [DRG_270t2] Malygos's Tome (*) - COST:1
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Add 3 random Mage spells to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [DRG_270t4] Malygos's Explosion (*) - COST:2
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Deal 2 damage to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [DRG_270t5] Malygos's Nova (*) - COST:1
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Freeze</b> all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [DRG_270t6] Malygos's Polymorph (*) - COST:1
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Transform a minion into a 1/1 Sheep.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [DRG_270t6t] Malygos's Sheep (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Faction: Neutral, Set: Dragons
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [DRG_270t7] Malygos's Flamestrike (*) - COST:7
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Deal 8 damage to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [DRG_270t8] Malygos's Frostbolt (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Deal 3 damage to a character and <b>Freeze</b> it.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [DRG_270t9] Malygos's Fireball (*) - COST:4
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Deal 8 damage.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [DRG_270t11] Malygos's Missiles (*) - COST:1
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Deal 6 damage randomly split among all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------

    // ------------------------------------- ENCHANTMENT - MAGE
    // [DRG_322e] Draconic Magic (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: The next spell you cast this turn costs (0).
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [DRG_323t] Draconic Emissary (*) - COST:6 [ATK:6/HP:6]
    // - Race: Dragon, Set: Dragons
    // --------------------------------------------------------
}

void DragonsCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------------- SPELL - PALADIN
    // [DRG_008] Righteous Cause - COST:1
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Sidequest:</b> Summon 5 minions.
    //       <b>Reward:</b> Give your minions +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - QUEST_PROGRESS_TOTAL = 5
    // - SIDEQUEST = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::SUMMON));
    power.GetTrigger()->tasks = { std::make_shared<QuestProgressTask>(
        TaskList{ std::make_shared<AddEnchantmentTask>(
            "DRG_008e", EntityType::MINIONS) }) };
    cards.emplace("DRG_008", CardDef(power, 5, 0));

    // --------------------------------------- MINION - PALADIN
    // [DRG_225] Sky Claw - COST:3 [ATK:1/HP:2]
    // - Race: Mechanical, Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: Your other Mechs have +1 Attack.
    //       <b>Battlecry:</b> Summon two 1/1 Microcopters.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - AURA = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [DRG_226] Amber Watcher - COST:5 [ATK:4/HP:6]
    // - Race: Dragon, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 8 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [DRG_229] Bronze Explorer - COST:3 [ATK:2/HP:3]
    // - Race: Dragon, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    //       <b>Battlecry:</b> <b>Discover</b> a Dragon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - LIFESTEAL = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [DRG_231] Lightforged Crusader - COST:7 [ATK:7/HP:7]
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck has no Neutral cards,
    //       add 5 random Paladin cards to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [DRG_232] Lightforged Zealot - COST:4 [ATK:4/HP:2]
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck has no Neutral cards,
    //       equip a 4/2 Truesilver_Champion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [DRG_233] Sand Breath - COST:1
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion +1/+2. Give it <b>Divine Shield</b>
    //       if you're holding a Dragon.
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [DRG_235] Dragonrider Talritha - COST:3 [ATK:3/HP:3]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give a Dragon in your hand +3/+3
    //       and this <b>Deathrattle</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [DRG_258] Sanctuary - COST:2
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Sidequest:</b> Take no damage for a turn.
    //       <b>Reward:</b> Summon a 3/6 minion with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - QUEST_PROGRESS_TOTAL = 1
    // - QUEST_REWARD_DATABASE_ID = 57723
    // - SIDEQUEST = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [DRG_309] Nozdormu the Timeless - COST:4 [ATK:8/HP:8]
    // - Race: Dragon, Faction: Neutral, Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Set each player to 10 Mana Crystals.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void DragonsCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - PALADIN
    // [DRG_225t] Microcopter (*) - COST:1 [ATK:1/HP:1]
    // - Race: Mechanical, Set: Dragons
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - PALADIN
    // [DRG_232t] Truesilver Champion (*) - COST:4 [ATK:4/HP:0]
    // - Faction: Neutral, Set: Dragons, Rarity: Free
    // --------------------------------------------------------
    // Text: Whenever your hero attacks, restore 2 Health to it.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [DRG_258t] Indomitable Champion (*) - COST:4 [ATK:3/HP:6]
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
}

void DragonsCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------------- MINION - PRIEST
    // [DRG_090] Murozond the Infinite - COST:8 [ATK:8/HP:8]
    // - Race: Dragon, Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Play all cards your opponent
    //       played last turn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [DRG_246] Time Rip - COST:5
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: Destroy a minion. <b>Invoke</b> Galakrond.
    // --------------------------------------------------------
    // GameTag:
    // - 676 = 1
    // - EMPOWER = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [DRG_300] Fate Weaver - COST:4 [ATK:3/HP:6]
    // - Race: Dragon, Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you've <b>Invoked</b> twice,
    //       reduce the Cost of cards in your hand by (1).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - 676 = 1
    // --------------------------------------------------------
    // RefTag:
    // - EMPOWER = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [DRG_301] Whispers of EVIL - COST:0
    // - Faction: Neutral, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: Add a <b>Lackey</b> to your hand.
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [DRG_302] Grave Rune - COST:4
    // - Faction: Neutral, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion "<b>Deathrattle:</b> Summon 2 copies of this."
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [DRG_303] Disciple of Galakrond - COST:1 [ATK:1/HP:2]
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Invoke</b> Galakrond.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - 676 = 1
    // - EMPOWER = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<InvokeTask>());
    cards.emplace("DRG_303", CardDef(power));

    // ---------------------------------------- MINION - PRIEST
    // [DRG_304] Chronobreaker - COST:5 [ATK:4/HP:5]
    // - Race: Dragon, Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> If you're holding a Dragon,
    //       deal 3 damage to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [DRG_306] Envoy of Lazul - COST:2 [ATK:2/HP:2]
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Look at 3 cards.
    //       Guess which one is in your opponent's hand
    //       to get a copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [DRG_307] Breath of the Infinite - COST:3
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 2 damage to all minions.
    //       If you're holding a Dragon, only damage enemies.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [DRG_308] Mindflayer Kaahrj - COST:3 [ATK:3/HP:3]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose an enemy minion.
    //       <b>Deathrattle:</b> Summon a new copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void DragonsCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- ENCHANTMENT - PRIEST
    // [DRG_300e] Draconic Fate (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------
}

void DragonsCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- MINION - ROGUE
    // [DRG_027] Umbral Skulker - COST:4 [ATK:3/HP:3]
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you've <b>Invoked</b> twice,
    //       add 3 Coins to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - 676 = 1
    // --------------------------------------------------------
    // RefTag:
    // - EMPOWER = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [DRG_028] Dragon's Hoard - COST:1
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Discover</b> a <b>Legendary</b> minion
    //       from another class.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [DRG_030] Praise Galakrond! - COST:1
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion +1 Attack. <b>Invoke</b> Galakrond.
    // --------------------------------------------------------
    // GameTag:
    // - 676 = 1
    // - EMPOWER = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [DRG_031] Necrium Apothecary - COST:5 [ATK:2/HP:5]
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Draw a <b>Deathrattle</b> minion
    //       from your deck and gain its <b>Deathrattle</b>.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [DRG_033] Candle Breath - COST:6
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: Draw 3 cards.
    //       Costs (3) less while you're holding a Dragon.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [DRG_034] Stowaway - COST:5 [ATK:4/HP:4]
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If there are cards in your deck
    //       that didn't start there, draw 2 of them.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [DRG_035] Bloodsail Flybooter - COST:1 [ATK:1/HP:1]
    // - Race: Pirate, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add two 1/1 Pirates to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [DRG_036] Waxadred - COST:5 [ATK:7/HP:5]
    // - Race: Dragon, Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Shuffle a Candle into your deck
    //       that resummons Waxadred when drawn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [DRG_037] Flik Skyshiv - COST:6 [ATK:4/HP:4]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a minion and all copies
    //       of it <i>(wherever they are)</i>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [DRG_247] Seal Fate - COST:3
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 3 damage to an undamaged character.
    //       <b>Invoke</b> Galakrond.
    // --------------------------------------------------------
    // GameTag:
    // - 676 = 1
    // - EMPOWER = 1
    // --------------------------------------------------------
}

void DragonsCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [DRG_030e] Praise Galakrond! (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [DRG_035t] Sky Pirate (*) - COST:1 [ATK:1/HP:1]
    // - Race: Pirate, Set: Dragons
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [DRG_036t] Waxadred's Candle (*) - COST:5
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Casts When Drawn</b> Summon Waxadred.
    // --------------------------------------------------------
    // GameTag:
    // - TOPDECK = 1
    // --------------------------------------------------------
    // RefTag:
    // - CASTSWHENDRAWN = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [DRG_074e] Camouflaged (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Stealthed until your next turn.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [DRG_610e] Galakrond's Wonder (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Costs (0).
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(std::make_shared<Enchant>(Effects::SetCost(0)));
    cards.emplace("DRG_610e", CardDef(power));
}

void DragonsCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- MINION - SHAMAN
    // [DRG_096] Bandersmosh - COST:5 [ATK:5/HP:5]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Each turn this is in your hand, transform it into a
    //       5/5 copy of a random <b>Legendary</b> minion.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [DRG_211] Squallhunter - COST:4 [ATK:5/HP:7]
    // - Race: Dragon, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Spell Damage +2</b> <b>Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 2
    // - OVERLOAD = 2
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [DRG_215] Storm's Wrath - COST:1
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give your minions +1/+1. <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [DRG_216] Surging Tempest - COST:1 [ATK:1/HP:3]
    // - Race: Elemental, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: Has +1 Attack while you have <b>Overloaded</b>
    //       Mana Crystals.
    // --------------------------------------------------------
    // RefTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [DRG_217] Dragon's Pack - COST:5
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: Summon two 2/3 Spirit Wolves with <b>Taunt</b>.
    //       If you've <b>Invoked</b> twice, give them +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - 676 = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // - EMPOWER = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [DRG_218] Corrupt Elementalist - COST:5 [ATK:3/HP:3]
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Invoke</b> Galakrond twice.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - 676 = 1
    // - EMPOWER = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [DRG_219] Lightning Breath - COST:3
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 4 damage to a minion. If you're holding
    //       a Dragon, also damage its neighbors.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [DRG_223] Cumulo-Maximus - COST:5 [ATK:5/HP:5]
    // - Race: Elemental, Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you have <b>Overloaded</b>
    //       Mana Crystals, deal 5 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [DRG_224] Nithogg - COST:6 [ATK:5/HP:5]
    // - Race: Dragon, Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two 0/3 Eggs.
    //       Next turn they hatch into 4/4 Drakes with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [DRG_248] Invocation of Frost - COST:2
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Freeze</b> an enemy. <b>Invoke</b> Galakrond.
    // --------------------------------------------------------
    // GameTag:
    // - 676 = 1
    // - EMPOWER = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------
}

void DragonsCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [DRG_068e] Toasty (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Can't be <b>Frozen</b>.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [DRG_096e2] Smoshing (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: 5/5.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [DRG_216e] Surging (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [DRG_217t] Spirit Wolf (*) - COST:2 [ATK:2/HP:3]
    // - Faction: Neutral, Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [DRG_224t] Storm Egg (*) - COST:1 [ATK:0/HP:3]
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: At the start of your turn, transform into
    //       a 4/4 Storm Drake with <b>Rush</b>.
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [DRG_224t2] Storm Drake (*) - COST:4 [ATK:4/HP:4]
    // - Race: Dragon, Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [DRG_238t14t3] Windswept Elemental (*) - COST:2 [ATK:2/HP:1]
    // - Race: Elemental, Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("DRG_238t14t3", CardDef(power));

    // ---------------------------------------- MINION - SHAMAN
    // [DRG_620t4] Brewing Storm (*) - COST:2 [ATK:2/HP:2]
    // - Race: Elemental, Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("DRG_620t4", CardDef(power));

    // ---------------------------------------- MINION - SHAMAN
    // [DRG_620t5] Living Storm (*) - COST:4 [ATK:4/HP:4]
    // - Race: Elemental, Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("DRG_620t5", CardDef(power));

    // ---------------------------------------- MINION - SHAMAN
    // [DRG_620t6] Raging Storm (*) - COST:8 [ATK:8/HP:8]
    // - Race: Elemental, Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("DRG_620t6", CardDef(power));
}

void DragonsCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - WARLOCK
    // [DRG_201] Crazed Netherwing - COST:5 [ATK:5/HP:5]
    // - Race: Dragon, Faction: Neutral, Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       deal 3 damage to all other characters.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [DRG_202] Dragonblight Cultist - COST:3 [ATK:1/HP:1]
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Invoke</b> Galakrond.
    //       Gain +1 Attack for each other friendly minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - 676 = 1
    // - EMPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [DRG_203] Veiled Worshipper - COST:4 [ATK:5/HP:4]
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you've <b>Invoked</b> twice,
    //       draw 3 cards.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - 676 = 1
    // --------------------------------------------------------
    // RefTag:
    // - EMPOWER = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [DRG_204] Dark Skies - COST:3
    // - Faction: Neutral, Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 1 damage to a random minion.
    //       Repeat for each card in your hand.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [DRG_205] Nether Breath - COST:2
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 2 damage. If you're holding a Dragon,
    //       deal 4 damage with <b>Lifesteal</b> instead.
    // --------------------------------------------------------
    // RefTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [DRG_206] Rain of Fire - COST:1
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 1 damage to all characters.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [DRG_207] Abyssal Summoner - COST:6 [ATK:2/HP:2]
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a Demon with <b>Taunt</b>
    //       and stats equal to your hand size.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [DRG_208] Valdris Felgorge - COST:7 [ATK:4/HP:4]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Increase your maximum hand size
    //       to 12. Draw 4 cards.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [DRG_209] Zzeraku the Warped - COST:8 [ATK:4/HP:12]
    // - Race: Dragon, Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever your hero takes damage,
    //       summon a 6/6 Nether Drake.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [DRG_250] Fiendish Rites - COST:4
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Invoke</b> Galakrond.
    //       Give your minions +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - 676 = 1
    // - EMPOWER = 1
    // --------------------------------------------------------
}

void DragonsCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [DRG_202e] Power of the Cult (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [DRG_207t] Abyssal Destroyer (*) - COST:1 [ATK:1/HP:1]
    // - Race: Demon, Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [DRG_209t] Nether Drake (*) - COST:6 [ATK:6/HP:6]
    // - Race: Dragon, Set: Dragons
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [DRG_238t12t2] Draconic Imp (*) - COST:1 [ATK:1/HP:1]
    // - Race: Demon, Set: Dragons
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("DRG_238t12t2", CardDef(power));
}

void DragonsCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - WARRIOR
    // [DRG_019] Scion of Ruin - COST:4 [ATK:3/HP:2]
    // - Race: Dragon, Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Rush</b>. <b>Battlecry:</b> If you've
    //       <b>Invoked</b> twice, summon 2 copies of this.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - 676 = 1
    // - RUSH = 1
    // --------------------------------------------------------
    // RefTag:
    // - EMPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [DRG_020] EVIL Quartermaster - COST:3 [ATK:2/HP:3]
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a <b>Lackey</b> to your hand.
    //       Gain 3 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [DRG_021] Ritual Chopper - COST:2 [ATK:1/HP:0]
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Invoke</b> Galakrond.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - BATTLECRY = 1
    // - 676 = 1
    // - EMPOWER = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [DRG_022] Ramming Speed - COST:3
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: Force a minion to attack one of its neighbors.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [DRG_023] Skybarge - COST:3 [ATK:2/HP:5]
    // - Race: Mechanical, Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you summon a Pirate,
    //       deal 2 damage to a random enemy.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [DRG_024] Sky Raider - COST:1 [ATK:1/HP:2]
    // - Race: Pirate, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a random Pirate to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [DRG_025] Ancharrr - COST:3 [ATK:2/HP:0]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After your hero attacks, draw a Pirate from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DURABILITY = 2
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [DRG_026] Deathwing, Mad Aspect - COST:8 [ATK:12/HP:12]
    // - Race: Dragon, Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Attack ALL other minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [DRG_249] Awaken! - COST:3
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Invoke</b> Galakrond. Deal 1 damage to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - 676 = 1
    // - EMPOWER = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [DRG_500] Molten Breath - COST:4
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 5 damage to a minion.
    //       If you're holding a Dragon, gain 5 Armor.
    // --------------------------------------------------------
}

void DragonsCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [DRG_238t10e] Galakrond's Might (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +3 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("DRG_238t10e"));
    cards.emplace("DRG_238t10e", CardDef(power));
}

void DragonsCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    Power power;

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_049] Tasty Flyfish - COST:2 [ATK:2/HP:2]
    // - Race: Murloc, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give a Dragon in your hand +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_050] Devoted Maniac - COST:4 [ATK:2/HP:2]
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Battlecry:</b> <b>Invoke</b> Galakrond.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - 676 = 1
    // - RUSH = 1
    // - EMPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_054] Big Ol' Whelp - COST:5 [ATK:5/HP:5]
    // - Race: Dragon, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_055] Hoard Pillager - COST:4 [ATK:4/HP:2]
    // - Race: Pirate, Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Equip one of your destroyed weapons.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_056] Parachute Brigand - COST:2 [ATK:2/HP:2]
    // - Race: Pirate, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: After you play a Pirate,
    //       summon this minion from your hand.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_057] Hot Air Balloon - COST:1 [ATK:1/HP:2]
    // - Race: Mechanical, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: At the start of your turn, gain +1 Health.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_058] Wing Commander - COST:4 [ATK:2/HP:5]
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: Has +2 Attack for each Dragon in your hand.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_059] Goboglide Tech - COST:3 [ATK:3/HP:3]
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a Mech,
    //       gain +1/+1 and <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_060] Fire Hawk - COST:3 [ATK:1/HP:3]
    // - Race: Elemental, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain +1 Attack for each card
    //       in your opponent's hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_061] Gyrocopter - COST:6 [ATK:4/HP:5]
    // - Race: Mechanical, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b> <b>Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - WINDFURY = 1
    // - RUSH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("DRG_061", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_062] Wyrmrest Purifier - COST:2 [ATK:3/HP:2]
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Transform all Neutral cards
    //       in your deck into random cards from your class.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_063] Dragonmaw Poacher - COST:4 [ATK:4/HP:4]
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your opponent controls a Dragon,
    //       gain +4/+4 and <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_064] Zul'Drak Ritualist - COST:4 [ATK:3/HP:9]
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b> <b>Battlecry:</b> Summon three
    //       random 1-Cost minions for your opponent.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_065] Hippogryph - COST:4 [ATK:2/HP:6]
    // - Race: Beast, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b> <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - RUSH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("DRG_065", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_066] Evasive Chimaera - COST:2 [ATK:2/HP:1]
    // - Race: Beast, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    //       Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // - POISONOUS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_067] Troll Batrider - COST:4 [ATK:3/HP:3]
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage to a random enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_068] Living Dragonbreath - COST:3 [ATK:3/HP:4]
    // - Race: Elemental, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: Your minions can't be <b>Frozen</b>.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_069] Platebreaker - COST:5 [ATK:5/HP:5]
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy your opponent's Armor.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_070] Dragon Breeder - COST:2 [ATK:2/HP:3]
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a friendly Dragon.
    //       Add a copy of it to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_071] Bad Luck Albatross - COST:3 [ATK:4/HP:3]
    // - Race: Beast, Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Shuffle two 1/1 Albatross
    //       into your opponent's deck.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_072] Skyfin - COST:5 [ATK:3/HP:3]
    // - Race: Murloc, Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       summon 2 random Murlocs.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_073] Evasive Feywing - COST:4 [ATK:5/HP:4]
    // - Race: Dragon, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_074] Camouflaged Dirigible - COST:6 [ATK:6/HP:6]
    // - Race: Mechanical, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your other Mechs
    //       <b>Stealth</b> until your next turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_075] Cobalt Spellkin - COST:5 [ATK:3/HP:5]
    // - Race: Dragon, Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add two 1-Cost spells from
    //       your class to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_076] Faceless Corruptor - COST:5 [ATK:5/HP:4]
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b>. <b>Battlecry:</b> Transform
    //       one of your minions into a copy of this.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_077] Utgarde Grapplesniper - COST:6 [ATK:5/HP:5]
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Both players draw a card.
    //       If it's a Dragon, summon it.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_078] Depth Charge - COST:1 [ATK:0/HP:5]
    // - Set: Dragons, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       deal 5 damage to ALL minions.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_079] Evasive Wyrm - COST:6 [ATK:5/HP:3]
    // - Race: Dragon, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>. <b>Rush</b>.
    //       Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // - RUSH = 1
    // - 1211 = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_081] Scalerider - COST:3 [ATK:3/HP:3]
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       deal 2 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_082] Kobold Stickyfinger - COST:5 [ATK:4/HP:4]
    // - Race: Pirate, Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Steal your opponent's weapon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_084] Tentacled Menace - COST:5 [ATK:6/HP:5]
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Each player draws a card.
    //       Swap their Costs.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_086] Chromatic Egg - COST:5 [ATK:0/HP:3]
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Secretly <b>Discover</b>
    //       a Dragon to hatch into. <b>Deathrattle:</b> Hatch!
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_088] Dread Raven - COST:3 [ATK:3/HP:4]
    // - Race: Beast, Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: Has +3 Attack for each other Dread Raven you control.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_089] Dragonqueen Alexstrasza - COST:9 [ATK:8/HP:8]
    // - Race: Dragon, Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck has no duplicates,
    //       add 2 other random Dragons to your hand. They cost (0).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_091] Shu'ma - COST:7 [ATK:1/HP:7]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       fill your board with 1/1 Tentacles.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_092] Transmogrifier - COST:2 [ATK:2/HP:3]
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: Whenever you draw a card,
    //       transform it into a random <b>Legendary</b> minion.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_099] Kronx Dragonhoof - COST:6 [ATK:6/HP:6]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw Galakrond.
    //       If you're already Galakrond, unleash a Devastation.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - 676 = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_213] Twin Tyrant - COST:8 [ATK:4/HP:10]
    // - Race: Dragon, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 4 damage to two random enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_239] Blazing Battlemage - COST:1 [ATK:2/HP:2]
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("DRG_239", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_242] Shield of Galakrond - COST:5 [ATK:4/HP:5]
    // - Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> <b>Invoke</b> Galakrond.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // - 676 = 1
    // - EMPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_257] Frizz Kindleroost - COST:4 [ATK:5/HP:4]
    // - Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Reduce the Cost of Dragons
    //       in your deck by (2).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_310] Evasive Drakonid - COST:7 [ATK:7/HP:7]
    // - Race: Dragon, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_401] Grizzled Wizard - COST:2 [ATK:3/HP:2]
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Swap Hero Powers with your opponent
    //       until your next turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_402] Sathrovarr - COST:9 [ATK:5/HP:5]
    // - Race: Demon, Set: Dragons, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a friendly minion.
    //       Add a copy of it to your hand, deck, and battlefield.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_403] Blowtorch Saboteur - COST:3 [ATK:3/HP:4]
    // - Set: Dragons, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your opponent's next
    //       Hero Power costs (3).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void DragonsCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_008e] Righteous Cause (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("DRG_008e"));
    cards.emplace("DRG_008e", CardDef(power));

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_049e] Well Fed (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_052] Draconic Lackey (*) - COST:1 [ATK:1/HP:1]
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a Dragon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - MARK_OF_EVIL = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_058e] Commanding (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_059e] Gobogliding (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_063e] Poaching (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +4/+4 and <b>Rush</b>.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_084e] Tentacle Confusion (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Cost swapped by Tentacled Menace.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_086e] What's in the Egg? (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: It's a mystery...@{0} is inside!
    //       <i>(Only you can see this.)</i>
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_088e] Conspiracy of Ravens (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +3 Attack for each other Dread Raven.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_089e] A Queen's Discount (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Costs (0).
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_091t] Tentacle (*) - COST:1 [ATK:1/HP:1]
    // - Set: Dragons
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [DRG_099t1] Decimation (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Deal 5 damage to the enemy hero.
    //       Restore 5 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // - 1200 = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [DRG_099t2] Reanimation (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Summon an 8/8 Dragon with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - 1200 = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [DRG_099t3] Domination (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Give your other minions +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - 1200 = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [DRG_099t4] Annihilation (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Deal 5 damage to all other minions.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // - 1200 = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_096e] Smoshing (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Transforming into random <b>Legendary</b> minions.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_099t2t] Reanimated Dragon (*) - COST:8 [ATK:8/HP:8]
    // - Race: Dragon, Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_099t3e] Dominating (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_215e] Storm's Wrath (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_217e] Galakrond's Power (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +3/+3.
    // --------------------------------------------------------
    // GameTag:
    // - HIDE_WATERMARK = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_225e] Mechanical Might (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +1 Attack from Sky Claw.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_233e] Sand Breath (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +1/+2.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [DRG_235d] Dragonrider Talritha Effect Dummy (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // GameTag:
    // - HIDE_WATERMARK = 1
    // - 1200 = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_235e] Rider Talritha (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +3/+3 and <b>Deathrattle:</b> Give a Dragon in your hand this
    // enchant.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_250e] Fiendish Rites (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DRG_255t2] Leper Gnome (*) - COST:1 [ATK:1/HP:1]
    // - Faction: Neutral, Set: Dragons, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 2 damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 2, false));
    cards.emplace("DRG_255t2", CardDef(power));

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_257e3] Ready to Hatch! (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Reduced Cost.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_308e] Shadowborn (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon {0}.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_311e] Spore Hardened (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +2 Health and <b>Taunt</b>.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_319e4] Treant Powerup (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Your Treants have +1/+1.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [DRG_401d] Grizzled Power Dummy (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Dummy Hook Up for DRG_401e
    // --------------------------------------------------------
    // GameTag:
    // - HIDE_WATERMARK = 1
    // - 1200 = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_401e] Grizzled Power (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Swap Hero Powers with your opponent next turn.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_403e] Hot Hot Hot! (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: Costs (3).
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_650e] Galakrond's Strength (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +4/+4.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("DRG_650e"));
    cards.emplace("DRG_650e", CardDef(power));

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_650e2] Galakrond's Strength (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +4/+4.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("DRG_650e2"));
    cards.emplace("DRG_650e2", CardDef(power));

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DRG_650e3] Galakrond's Strength (*) - COST:0
    // - Set: Dragons
    // --------------------------------------------------------
    // Text: +4/+4.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("DRG_650e3"));
    cards.emplace("DRG_650e3", CardDef(power));
}

void DragonsCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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
