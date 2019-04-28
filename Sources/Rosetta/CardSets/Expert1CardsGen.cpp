// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/CardSets/Expert1CardsGen.hpp>
#include <Rosetta/Tasks/SimpleTasks/DamageTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DrawTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/HealTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/SetGameTagTask.hpp>

using namespace RosettaStone::SimpleTasks;

namespace RosettaStone
{
void Expert1CardsGen::AddHeroes(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddHeroPowers(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddDruid(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddDruidNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddHunter(std::map<std::string, Power>& cards)
{
    Power power;

    // ---------------------------------------- MINION - HUNTER
    // [EX1_543] King Krush - COST:9 [ATK:8/HP:8]
    // - Race: Beast, Faction: Neutral, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CHARGE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_543", power);
}

void Expert1CardsGen::AddHunterNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddMage(std::map<std::string, Power>& cards)
{
    Power power;

    // ------------------------------------------- SPELL - MAGE
    // [CS2_028] Blizzard - COST:6
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal $2 damage to all enemy minions and <b>Freeze</b> them.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::ENEMY_MINIONS, 2, true));
    power.AddPowerTask(
        new SetGameTagTask(EntityType::ENEMY_MINIONS, GameTag::FROZEN, 1));
    cards.emplace("CS2_028", power);
}

void Expert1CardsGen::AddMageNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddPaladin(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddPaladinNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddPriest(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddPriestNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddRogue(std::map<std::string, Power>& cards)
{
    Power power;

    // ----------------------------------------- MINION - ROGUE
    // [EX1_522] Patient Assassin - COST:2 [ATK:1/HP:1]
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //        <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // - POISONOUS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_522", power);
}

void Expert1CardsGen::AddRogueNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddShaman(std::map<std::string, Power>& cards)
{
    Power power;

    // ---------------------------------------- MINION - SHAMAN
    // [NEW1_010] Al'Akir the Windlord - COST:8 [ATK:3/HP:5]
    // - Race: Elemental, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Charge, Divine Shield, Taunt, Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - WINDFURY = 1
    // - TAUNT = 1
    // - DIVINE_SHIELD = 1
    // - CHARGE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("NEW1_010", power);
}

void Expert1CardsGen::AddShamanNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddWarlock(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddWarlockNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddWarrior(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddWarriorNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddNeutral(std::map<std::string, Power>& cards)
{
    Power power;

    // --------------------------------------- MINION - NEUTRAL
    // [CS1_069] Fen Creeper - COST:5 [ATK:3/HP:6]
    // - Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS1_069", power);

	// --------------------------------------- MINION - NEUTRAL
    // [CS2_117] Earthen Ring Farseer - COST:3 [ATK:3/HP:3]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 3 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new HealTask(EntityType::TARGET, 3));
    cards.emplace("CS2_117", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_161] Ravenholdt Assassin - COST:7 [ATK:7/HP:5]
    // - Faction: Alliance, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_161", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_169] Young Dragonhawk - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Faction: Horde, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - WINDFURY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_169", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_231] Wisp - COST:0 [ATK:1/HP:1]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_231", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_008] Argent Squire - COST:1 [ATK:1/HP:1]
    // - Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_008", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_010] Worgen Infiltrator - COST:1 [ATK:2/HP:1]
    // - Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_010", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_012] Bloodmage Thalnos - COST:2 [ATK:1/HP:1]
    // - Fac: neutral, Set: expert1, Rarity: legendary
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    //       <b>Deathrattle:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - SPELLPOWER = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(new DrawTask(1));
    cards.emplace("EX1_012", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_017] Jungle Panther - COST:3 [ATK:4/HP:2]
    // - Race: Beast, Faction: Horde, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_017", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_020] Scarlet Crusader - COST:3 [ATK:3/HP:1]
    // - Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_020", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_021] Thrallmar Farseer - COST:3 [ATK:2/HP:3]
    // - Faction: Horde, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - WINDFURY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_021", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_023] Silvermoon Guardian - COST:4 [ATK:3/HP:3]
    // - Faction: Horde, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_023", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_028] Stranglethorn Tiger - COST:5 [ATK:5/HP:5]
    // - Race: Beast, Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_028", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_032] Sunwalker - COST:6 [ATK:4/HP:5]
    // - Faction: Alliance, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_032", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_033] Windfury Harpy - COST:6 [ATK:4/HP:5]
    // - Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - WINDFURY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_033", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_067] Argent Commander - COST:6 [ATK:4/HP:2]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    //       <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // - CHARGE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_067", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_170] Emperor Cobra - COST:3 [ATK:2/HP:3]
    // - Race: Beast, Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - POISONOUS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_170", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_396] Mogu'shan Warden - COST:4 [ATK:1/HP:7]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_396", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_405] Shieldbearer - COST:1 [ATK:0/HP:4]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_405", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_563] Malygos - COST:9 [ATK:4/HP:12]
    // - Race: Dragon, Faction: Neutral, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Spell Damage +5</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - SPELLPOWER = 5
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_563", power);
}

void Expert1CardsGen::AddNeutralNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddAll(std::map<std::string, Power>& cards)
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
