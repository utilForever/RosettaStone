// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/CardSets/CoreCardsGen.hpp>
#include <Rosetta/Enchants/Effects.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddEnchantmentTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/ControlTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DamageTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DestroyTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DiscardTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DrawTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/EnqueueTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/HealFullTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/HealTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/RandomTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/SetGameTagTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/SummonTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/TransformTask.hpp>

using namespace RosettaStone::SimpleTasks;

namespace RosettaStone
{
void CoreCardsGen::AddHeroes(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void CoreCardsGen::AddHeroPowers(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void CoreCardsGen::AddDruid(std::map<std::string, Power>& cards)
{
    Power power;

    // ------------------------------------------ SPELL - DRUID
    // [CS2_007] Healing Touch - COST:3
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Restore #8 Health.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new HealTask(EntityType::TARGET, 8));
    cards.emplace("CS2_007", power);
}

void CoreCardsGen::AddDruidNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void CoreCardsGen::AddHunter(std::map<std::string, Power>& cards)
{
    Power power;

    // ----------------------------------------- SPELL - HUNTER
    // [DS1_185] Arcane Shot - COST:1
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $2 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 2));
    cards.emplace("DS1_185", power);
}

void CoreCardsGen::AddHunterNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void CoreCardsGen::AddMage(std::map<std::string, Power>& cards)
{
    // ------------------------------------------- SPELL - MAGE
    // [CS2_029] Fireball - COST:4
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $6 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    Power power;
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 6));
    cards.emplace("CS2_029", power);

    // ------------------------------------------- SPELL - MAGE
    // [CS2_025] Arcane Explosion - COST:2
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $1 damage to all enemy minions.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::ENEMY_FIELD, 1));
    cards.emplace("CS2_025", power);

    // ------------------------------------------- SPELL - MAGE
    // [CS2_024] Frostbolt - COST:2
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $3 damage to a_character and <b>Freeze</b> it.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 3));
    power.AddPowerTask(
        new SetGameTagTask(EntityType::TARGET, GameTag::FROZEN, 1));
    cards.emplace("CS2_024", power);

    // ------------------------------------------- SPELL - MAGE
    // [CS2_026] Frost Nova - COST:3
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Freeze</b> all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        new SetGameTagTask(EntityType::ENEMY_FIELD, GameTag::FROZEN, 1));
    cards.emplace("CS2_026", power);

    // ------------------------------------------- SPELL - MAGE
    // [CS2_032] Flamestrike - COST:7
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $4 damage to all enemy minions.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::ENEMY_FIELD, 4));
    cards.emplace("CS2_032", power);

    // ------------------------------------------- SPELL - MAGE
    // [CS2_023] Arcane Intellect - COST:3
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Draw 2 cards.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DrawTask(2));
    cards.emplace("CS2_023", power);

    // ------------------------------------------- SPELL - MAGE
    // [EX1_277] Arcane Missiles - COST:1
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $3 damage randomly split among all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new EnqueueTask({ new RandomTask(EntityType::ENEMIES, 1),
                                         new DamageTask(EntityType::STACK, 1) },
                                       3));
    cards.emplace("EX1_277", power);

    // ------------------------------------------- SPELL - MAGE
    // [CS2_027] Mirror Image - COST:1
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Summon two 0/2 minions with <b>Taunt</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new SummonTask("CS2_mirror", 2));
    cards.emplace("CS2_027", power);

    // ------------------------------------------- SPELL - MAGE
    // [CS2_022] Polymorph - COST:4
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Transform a minion
    //       into a 1/1 Sheep.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new TransformTask(EntityType::TARGET, "CS2_tk1"));
    cards.emplace("CS2_022", power);
}

void CoreCardsGen::AddMageNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void CoreCardsGen::AddPaladin(std::map<std::string, Power>& cards)
{
    Power power;

    // --------------------------------------- MINION - PALADIN
    // [CS2_088] Guardian of Kings - COST:7 [ATK:5/HP:6]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 6 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new HealTask(EntityType::HERO, 6));
    cards.emplace("CS2_088", power);

    // ---------------------------------------- SPELL - PALADIN
    // [CS2_093] Consecration - COST:4
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $2 damage to all enemies.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::ENEMIES, 2));
    cards.emplace("CS2_093", power);

    // ---------------------------------------- SPELL - PALADIN
    // [CS2_094] Hammer of Wrath - COST:4
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $3 damage.
    //       Draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 3));
    power.AddPowerTask(new DrawTask(1));
    cards.emplace("CS2_094", power);

    // ---------------------------------------- SPELL - PALADIN
    // [EX1_371] Hand of Protection - COST:1
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Give a minion <b>Divine Shield</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        new SetGameTagTask(EntityType::TARGET, GameTag::DIVINE_SHIELD, 1));
    cards.emplace("EX1_371", power);

    // ---------------------------------------- SPELL - PALADIN
    // [CS2_089] Holy Light - COST:2
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Restore #6 Health.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new HealTask(EntityType::TARGET, 6));
    cards.emplace("CS2_089", power);
}

void CoreCardsGen::AddPaladinNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void CoreCardsGen::AddPriest(std::map<std::string, Power>& cards)
{
    Power power;

    // ----------------------------------------- SPELL - PRIEST
    // [CS1_112] Holy Nova - COST:5
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $2 damage to all enemies.
    //       Restore #2 Health to all friendly characters.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::ENEMIES, 2));
    power.AddPowerTask(new HealTask(EntityType::FRIENDS, 2));
    cards.emplace("CS1_112", power);

    // ----------------------------------------- SPELL - PRIEST
    // [CS1_113] Mind Control - COST:10
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Take control of an enemy minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new ControlTask(EntityType::TARGET));
    cards.emplace("CS1_113", power);

    // ----------------------------------------- SPELL - PRIEST
    // [DS1_233] Mind Blast - COST:2
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $5 damage to the enemy hero.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::ENEMY_HERO, 5));
    cards.emplace("DS1_233", power);

    // ----------------------------------------- SPELL - PRIEST
    // [CS1_130] Holy Smite - COST:1
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $2 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 2));
    cards.emplace("CS1_130", power);
}

void CoreCardsGen::AddPriestNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void CoreCardsGen::AddRogue(std::map<std::string, Power>& cards)
{
    Power power;

    // ------------------------------------------ SPELL - ROGUE
    // [EX1_129] Fan of Knives - COST:3
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $1 damage to all enemy minions.
    //       Draw a card.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::ENEMY_FIELD, 1));
    power.AddPowerTask(new DrawTask(1u));
    cards.emplace("EX1_129", power);
}

void CoreCardsGen::AddRogueNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void CoreCardsGen::AddShaman(std::map<std::string, Power>& cards)
{
    // ----------------------------------------- SPELL - SHAMAN
    // [CS2_041] Ancestral Healing - COST:0
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Restore a minion
    //       to full Health and
    //       give it <b>Taunt</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // Tag:
    // - TAUNT = 1
    // --------------------------------------------------------
    Power power;
    power.AddPowerTask(new HealFullTask(EntityType::TARGET));
    power.AddPowerTask(new AddEnchantmentTask("CS2_041e", EntityType::TARGET));
    cards.emplace("CS2_041", power);

    // ----------------------------------------- SPELL - SHAMAN
    // [CS2_037] Frost Shock - COST:1
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $1 damage to an enemy character and <b>Freeze</b> it.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 1));
    power.AddPowerTask(
        new SetGameTagTask(EntityType::TARGET, GameTag::FROZEN, 1));
    cards.emplace("CS2_037", power);
}

void CoreCardsGen::AddShamanNonCollect(std::map<std::string, Power>& cards)
{
    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [CS2_041e] Ancestral Infusion (*) - COST:0
    // - Set: Core,
    // --------------------------------------------------------
    // Text: Taunt.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    Power power;
    power.AddEnchant(Enchant(Effects::Taunt));
    cards.emplace("CS2_041e", power);
}

void CoreCardsGen::AddWarlock(std::map<std::string, Power>& cards)
{
    Power power;

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_306] Succubus - COST:2 [ATK:4/HP:3]
    // - Faction: Horde, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Discard a random card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DiscardTask(EntityType::HAND));
    cards.emplace("EX1_306", power);

    // ---------------------------------------- SPELL - WARLOCK
    // [CS2_062] Hellfire - COST:4
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $3 damage to all characters.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::ALL, 3));
    cards.emplace("CS2_062", power);

    // ---------------------------------------- SPELL - WARLOCK
    // [CS2_057] Shadow Bolt - COST:3
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: Deal $4 damage
    //       to a minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 4));
    cards.emplace("CS2_057", power);
}

void CoreCardsGen::AddWarlockNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void CoreCardsGen::AddWarrior(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void CoreCardsGen::AddWarriorNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void CoreCardsGen::AddNeutral(std::map<std::string, Power>& cards)
{
    // --------------------------------------- MINION - NEUTRAL
    // [EX1_066] Acidic Swamp Ooze - COST:2 [ATK:3/HP:2]
    // - Faction: Alliance, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy your opponent's weapon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    Power power;
    power.AddPowerTask(new DestroyTask(EntityType::ENEMY_WEAPON));
    cards.emplace("EX1_066", power);
}

void CoreCardsGen::AddNeutralNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void CoreCardsGen::AddAll(std::map<std::string, Power>& cards)
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
