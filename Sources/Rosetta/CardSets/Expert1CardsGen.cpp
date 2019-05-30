// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/CardSets/Expert1CardsGen.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Conditions/SelfCondition.hpp>
#include <Rosetta/Enchants/Effects.hpp>
#include <Rosetta/Enchants/Enchants.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddAuraEffectTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddEnchantmentTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/CopyTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DamageTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DestroyTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DrawTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/FuncNumberTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/GetGameTagTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/HealTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/MathSubTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/MoveToGraveyardTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/RandomTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/RemoveEnchantmentTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/ReturnHandTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/SetGameTagTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/SummonTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/WeaponTask.hpp>

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

    // ------------------------------------------- SPELL - MAGE
    // [EX1_287] Counterspell - COST:3
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your opponent casts a spell, <b>Counter</b> it.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    // RefTag:
    // - COUNTER = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::CAST_SPELL));
    power.GetTrigger()->tasks = {
        new SetGameTagTask(EntityType::TARGET, GameTag::CANT_PLAY, 1),
        new SetGameTagTask(EntityType::SOURCE, GameTag::REVEALED, 1),
        new MoveToGraveyardTask(EntityType::SOURCE)
    };
    power.GetTrigger()->fastExecution = true;
    cards.emplace("EX1_287", power);
}

void Expert1CardsGen::AddMageNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddPaladin(std::map<std::string, Power>& cards)
{
    Power power;

    // --------------------------------------- MINION - PALADIN
    // [EX1_383] Tirion Fordring - COST:8 [ATK:6/HP:6]
    // - Faction: Neutral, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b><b>Divine Shield</b>,</b> <b>Taunt</b>
    //       <b>Deathrattle:</b> Equip a 5/3 Ashbringer.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // _ DIVINE SHIELD = 1
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(new WeaponTask("EX1_383t"));
    cards.emplace("EX1_383", power);
}

void Expert1CardsGen::AddPaladinNonCollect(std::map<std::string, Power>& cards)
{
    Power power;

    // --------------------------------------- WEAPON - PALADIN
    // [EX1_383t] Ashbringer (*) - COST:5 [ATK:5/HP:0]
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DURABILITY = 3
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("EX1_383t", power);
}

void Expert1CardsGen::AddPriest(std::map<std::string, Power>& cards)
{
    Power power;

    // ----------------------------------------- SPELL - PRIEST
    // [CS1_129] Inner Fire - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Change a minion's Attack to be equal to its Health.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new GetGameTagTask(EntityType::TARGET, GameTag::HEALTH));
    power.AddPowerTask(new MathSubTask(EntityType::TARGET, GameTag::DAMAGE));
    power.AddPowerTask(new AddEnchantmentTask("CS1_129e", EntityType::TARGET));
    cards.emplace("CS1_129", power);

    // ----------------------------------------- SPELL - PRIEST
    // [EX1_621] Circle of Healing - COST:0
    // - Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Restore #4 Health to ALL minions.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new HealTask(EntityType::ALL_MINIONS, 4));
    cards.emplace("EX1_621", power);
}

void Expert1CardsGen::AddPriestNonCollect(std::map<std::string, Power>& cards)
{
    Power power;

    // ----------------------------------------- ENCHANTMENT - PRIEST
    // [CS1_129e] Inner Fire - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Change a minion's Attack to be equal to its Health.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(new Enchant(Enchants::SetAttackScriptTag));
    cards.emplace("CS1_129e", power);
}

void Expert1CardsGen::AddRogue(std::map<std::string, Power>& cards)
{
    Power power;

    // ------------------------------------------ SPELL - ROGUE
    // [CS2_073] Cold Blood - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion +2 Attack. <b>Combo:</b> +4 Attack instead.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("CS2_073e", EntityType::TARGET));
    power.AddComboTask(new AddEnchantmentTask("CS2_073e2", EntityType::TARGET));
    cards.emplace("CS2_073", power);

    // ------------------------------------------ SPELL - ROGUE
    // [EX1_124] Eviscerate - COST:2
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal $2 damage. <b>Combo:</b> Deal $4 damage instead. @spelldmg
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 2, true));
    power.AddComboTask(new DamageTask(EntityType::TARGET, 4, true));
    cards.emplace("EX1_124", power);

    // ----------------------------------------- MINION - ROGUE
    // [EX1_134] SI:7 Agent - COST:3 [ATK:3/HP:3]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Deal 2 damage.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_FOR_COMBO = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddComboTask(new DamageTask(EntityType::TARGET, 2));
    cards.emplace("EX1_134", power);

    // ------------------------------------------ SPELL - ROGUE
    // [EX1_144] Shadowstep - COST:0
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Return a friendly minion to your hand. It costs (2) less.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new ReturnHandTask(EntityType::TARGET));
    power.AddPowerTask(
        new AddAuraEffectTask(Effects::ReduceCost(2), EntityType::TARGET));
    cards.emplace("EX1_144", power);

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
    Power power;

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [CS2_073e] Cold Blood (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("CS2_073e"));
    cards.emplace("CS2_073e", power);

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [CS2_073e2] Cold Blood (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +4 Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("CS2_073e2"));
    cards.emplace("CS2_073e2", power);
}

void Expert1CardsGen::AddShaman(std::map<std::string, Power>& cards)
{
    Power power;

    // ----------------------------------------- SPELL - SHAMAN
    // [CS2_038] Ancestral Spirit - COST:2
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give a minion "<b>Deathrattle:</b> Resummon this minion."
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("CS2_038e", EntityType::TARGET));
    cards.emplace("CS2_038", power);

    // ----------------------------------------- SPELL - SHAMAN
    // [CS2_053] Far Sight - COST:3
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: Draw a card. That card costs (3) less.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DrawTask(1, true));
    power.AddPowerTask(new AddEnchantmentTask("CS2_053e", EntityType::STACK));
    cards.emplace("CS2_053", power);

    // ----------------------------------------- SPELL - SHAMAN
    // [EX1_238] Lightning Bolt - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal $3 damage. <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // - OVERLOAD_OWED = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 3, true));
    cards.emplace("EX1_238", power);

    // ----------------------------------------- SPELL - SHAMAN
    // [EX1_241] Lava Burst - COST:3
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal $5 damage. <b>Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 2
    // - OVERLOAD_OWED = 2
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::TARGET, 5, true));
    cards.emplace("EX1_241", power);

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
    Power power;

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [CS2_038e] Ancestral Spirit (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Resummon this minion.
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(new CopyTask(EntityType::SOURCE, 1));
    power.AddDeathrattleTask(new SummonTask(SummonSide::DEATHRATTLE));

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [CS2_053e] Far Sight (*) - COST:0
    // - Set: expert1,
    // --------------------------------------------------------
    // Text: One of your cards costs (3) less.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(new Enchant(std::vector<Effect*>{
        Effects::ReduceCost(3),
        new Effect(GameTag::DISPLAYED_CREATOR, EffectOperator::SET, 1) }));
    power.AddTrigger(new Trigger(TriggerType::PLAY_CARD));
    power.GetTrigger()->triggerSource = TriggerSource::ENCHANTMENT_TARGET;
    power.GetTrigger()->tasks = { new RemoveEnchantmentTask() };
    power.GetTrigger()->removeAfterTriggered = true;
    cards.emplace("CS2_053e", power);
}

void Expert1CardsGen::AddWarlock(std::map<std::string, Power>& cards)
{
    Power power;

    // --------------------------------------- MINION - WARLOCK
    // [CS2_059] Blood Imp - COST:1 [ATK:0/HP:1]
    // - Race: Demon, Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>. At the end of your turn,
    //       give another random friendly minion +1 Health.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(new Trigger(TriggerType::TURN_END));
    power.GetTrigger()->tasks = {
        new RandomTask(EntityType::MINIONS_NOSOURCE, 1),
        new AddEnchantmentTask("CS2_059o", EntityType::STACK)
    };
    cards.emplace("CS2_059", power);

    // ---------------------------------------- SPELL - WARLOCK
    // [EX1_312] Twisting Nether - COST:8
    // - Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy all minions.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DestroyTask(EntityType::ALL_MINIONS));
    cards.emplace("EX1_312", power);

    // --------------------------------------- MINION - WARLOCK
    // [EX1_313] Pit Lord - COST:4 [ATK:5/HP:6]
    // - Race: Demon, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 5 damage to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::HERO, 5));
    cards.emplace("EX1_313", power);
}

void Expert1CardsGen::AddWarlockNonCollect(std::map<std::string, Power>& cards)
{
    Power power;

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [CS2_059o] Blood Pact (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased Health.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(new Enchant(Effects::HealthN(1)));
    cards.emplace("CS2_059o", power);
}

void Expert1CardsGen::AddWarrior(std::map<std::string, Power>& cards)
{
    Power power;

    // ---------------------------------------- SPELL - WARRIOR
    // [CS2_104] Rampage - COST:2
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a damaged minion +3/+3.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_DAMAGED_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("CS2_104e", EntityType::TARGET));
    cards.emplace("CS2_104", power);
}

void Expert1CardsGen::AddWarriorNonCollect(std::map<std::string, Power>& cards)
{
    Power power;

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [CS2_104e] Rampage (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +3/+3.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("CS2_104e"));
    cards.emplace("CS2_104e", power);
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
    // [CS2_146] Southsea Deckhand - COST:1 [ATK:2/HP:1]
    // - Race: Pirate, Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Has <b>Charge</b> while you have a weapon equipped.
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(
        new AdaptiveEffect(new SelfCondition(SelfCondition::IsWeaponEquipped()),
                           { GameTag::CHARGE }));
    cards.emplace("CS2_146", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_151] Silver Hand Knight - COST:5 [ATK:4/HP:4]
    // - Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 2/2 Squire.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new SummonTask("CS2_152", SummonSide::RIGHT));
    cards.emplace("CS2_151", power);

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
    // [CS2_181] Injured Blademaster - COST:3 [ATK:4/HP:7]
    // - Faction: Horde, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 4 damage to HIMSELF.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::SOURCE, 4, false));
    cards.emplace("CS2_181", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_188] Abusive Sergeant - COST:1 [ATK:1/HP:1]
    // - Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a minion +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new AddEnchantmentTask("CS2_188o", EntityType::TARGET));
    cards.emplace("CS2_188", power);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_231] Wisp - COST:0 [ATK:1/HP:1]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_231", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_005] Big Game Hunter - COST:5 [ATK:4/HP:2]
    // - Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a minion with 7 or more Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_MIN_ATTACK = 7
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DestroyTask(EntityType::TARGET));
    cards.emplace("EX1_005", power);

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
    // [EX1_096] Loot Hoarder - COST:2 [ATK:2/HP:1]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(new DrawTask(1));
    cards.emplace("EX1_096", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_097] Abomination - COST:5 [ATK:4/HP:4]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>. <b>Deathrattle:</b> Deal 2
    //       damage to ALL characters.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(new DamageTask(EntityType::ALL, 2));
    cards.emplace("EX1_097", power);

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
    Power power;

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_152] Squire (*) - COST:1 [ATK:2/HP:2]
    // - Faction: Alliance, Set: Expert1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS2_152", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CS2_188o] Inspired (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: This minion has +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("CS2_188o"));
    cards.emplace("CS2_188o", power);
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
