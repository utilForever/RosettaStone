// This code is based on Sabberstone project.
// Copyright (c) 2017-2021 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2021 Chris Ohk

#include <Rosetta/PlayMode/Actions/Choose.hpp>
#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Auras/AdaptiveEffect.hpp>
#include <Rosetta/PlayMode/Auras/AdjacentAura.hpp>
#include <Rosetta/PlayMode/Auras/EnrageEffect.hpp>
#include <Rosetta/PlayMode/CardSets/CoreCardsGen.hpp>
#include <Rosetta/PlayMode/Enchants/Effects.hpp>
#include <Rosetta/PlayMode/Enchants/Enchants.hpp>
#include <Rosetta/PlayMode/Tasks/ComplexTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

using namespace RosettaStone::PlayMode::SimpleTasks;

namespace RosettaStone::PlayMode
{
using TagValues = std::vector<TagValue>;
using PlayReqs = std::map<PlayReq, int>;
using ChooseCardIDs = std::vector<std::string>;
using SelfCondList = std::vector<std::shared_ptr<SelfCondition>>;
using RelaCondList = std::vector<std::shared_ptr<RelaCondition>>;
using EffectList = std::vector<std::shared_ptr<IEffect>>;

void CoreCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------------- HERO - WARLOCK
    // [CORE_EX1_323] Lord Jaraxxus - COST:9
    // - Set: CORE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Equip a 3/8 Blood Fury.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<WeaponTask>("EX1_323w"));
    cards.emplace("CORE_EX1_323", CardDef(power, 0, 1178));
}

void CoreCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void CoreCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------------------ SPELL - DRUID
    // [CORE_CS2_009] Mark of the Wild - COST:2
    // - Set: CORE, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Give a minion <b>Taunt</b> and +2/+3.<i>
    //       (+2 Attack/+3 Health)</i>
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_009e", EntityType::TARGET));
    cards.emplace(
        "CORE_CS2_009",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));

    // ------------------------------------------ SPELL - DRUID
    // [CORE_CS2_013] Wild Growth - COST:3
    // - Set: CORE, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Gain an empty Mana Crystal.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<ManaCrystalTask>(1, false));
    cards.emplace("CORE_CS2_013", CardDef(power));

    // ------------------------------------------ SPELL - DRUID
    // [CORE_EX1_158] Soul of the Forest - COST:4
    // - Set: CORE, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Give your minions
    //       "<b>Deathrattle:</b> Summon a 2/2 Treant."
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_158e", EntityType::MINIONS));
    cards.emplace("CORE_EX1_158", CardDef(power));

    // ------------------------------------------ SPELL - DRUID
    // [CORE_EX1_160] Power of the Wild - COST:2
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Give your minions +1/+1;
    //       or Summon a 3/2 Panther.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CORE_EX1_160",
                  CardDef(power, ChooseCardIDs{ "EX1_160a", "EX1_160b" }));

    // ------------------------------------------ SPELL - DRUID
    // [CORE_EX1_164] Nourish - COST:5
    // - Set: CORE, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Gain 2 Mana Crystals;
    //       or Draw 3 cards.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CORE_EX1_164",
                  CardDef(power, ChooseCardIDs{ "EX1_164a", "EX1_164b" }));

    // ----------------------------------------- MINION - DRUID
    // [CORE_EX1_165] Druid of the Claw - COST:5 [ATK:5/HP:4]
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Transform into a 5/4
    //       with <b>Rush</b>; or a 5/6 with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<TransformTask>(EntityType::SOURCE, "OG_044a"));
    cards.emplace("CORE_EX1_165",
                  CardDef(power, ChooseCardIDs{ "EX1_165a", "EX1_165b" }));

    // ------------------------------------------ SPELL - DRUID
    // [CORE_EX1_169] Innervate - COST:0
    // - Set: CORE, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Gain 1 Mana Crystal this turn only.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<TempManaTask>(1));
    cards.emplace("CORE_EX1_169", CardDef(power));

    // ------------------------------------------ SPELL - DRUID
    // [CORE_EX1_571] Force of Nature - COST:5
    // - Set: CORE, Rarity: Epic
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Summon three 2/2 Treants.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<SummonTask>("EX1_tk9", 3));
    cards.emplace(
        "CORE_EX1_571",
        CardDef(power, PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } }));

    // ----------------------------------------- MINION - DRUID
    // [CORE_EX1_573] Cenarius - COST:8 [ATK:5/HP:8]
    // - Set: CORE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Give your other minions +2/+2;
    //       or Summon two 2/2 Treants with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CORE_EX1_573",
                  CardDef(power, ChooseCardIDs{ "EX1_573a", "EX1_573b" }));

    // ------------------------------------------ SPELL - DRUID
    // [CORE_OG_047] Feral Rage - COST:3
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Give your hero +4 Attack this turn;
    //       or Gain 8 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CORE_OG_047",
                  CardDef(power, ChooseCardIDs{ "OG_047a", "OG_047b" }));

    // ------------------------------------------ SPELL - DRUID
    // [CORE_TRL_243] Pounce - COST:0
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: Give your hero +2 Attack this turn.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("TRL_243e", EntityType::HERO));
    cards.emplace("CORE_TRL_243", CardDef(power));
}

void CoreCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void CoreCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------------- SPELL - HUNTER
    // [CORE_BRM_013] Quick Shot - COST:2
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 3 damage. If your hand is empty, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsHandEmpty()) }));
    power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DrawTask>(1) }));
    cards.emplace(
        "CORE_BRM_013",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } }));

    // ----------------------------------------- SPELL - HUNTER
    // [CORE_DS1_184] Tracking - COST:1
    // - Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Discover</b> a card from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DiscoverTask>(DiscoverType::DECK));
    cards.emplace("CORE_DS1_184", CardDef(power));

    // ----------------------------------------- SPELL - HUNTER
    // [CORE_DS1_185] Arcane Shot - COST:1
    // - Set: CORE, Rarity: Rare
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Deal 2 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, true));
    cards.emplace(
        "CORE_DS1_185",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } }));

    // ---------------------------------------- MINION - HUNTER
    // [CORE_EX1_534] Savannah Highmane - COST:6 [ATK:6/HP:5]
    // - Race: Beast, Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon two 2/2 Hyenas.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(
        std::make_shared<SummonTask>("EX1_534t", 2, SummonSide::DEATHRATTLE));
    cards.emplace("CORE_EX1_534", CardDef(power));

    // ---------------------------------------- MINION - HUNTER
    // [CORE_EX1_543] King Krush - COST:9 [ATK:8/HP:8]
    // - Race: Beast, Faction: Neutral, Set: CORE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CHARGE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CORE_EX1_543", CardDef(power));

    // ----------------------------------------- SPELL - HUNTER
    // [CORE_EX1_554] Snake Trap - COST:2
    // - Faction: Neutral, Set: CORE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When one of your minions is attacked,
    //       summon three 1/1 Snakes.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    power.GetTrigger()->triggerSource = TriggerSource::ENEMY;
    power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsProposedDefender(CardType::MINION)) };
    power.GetTrigger()->tasks = ComplexTask::ActivateSecret(
        TaskList{ std::make_shared<SummonTask>("EX1_554t", 3) });
    cards.emplace("CORE_EX1_554", CardDef(power));

    // ----------------------------------------- SPELL - HUNTER
    // [CORE_EX1_610] Explosive Trap - COST:2
    // - Set: CORE, Rarity: Common
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your hero is attacked,
    //       deal 2 damage to all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    power.GetTrigger()->triggerSource = TriggerSource::ENEMY;
    power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsProposedDefender(CardType::HERO)) };
    power.GetTrigger()->tasks = ComplexTask::ActivateSecret(
        TaskList{ std::make_shared<DamageTask>(EntityType::ENEMIES, 2, true) });
    cards.emplace("CORE_EX1_610", CardDef(power));

    // ----------------------------------------- SPELL - HUNTER
    // [CORE_EX1_611] Freezing Trap - COST:2
    // - Faction: Neutral, Set: CORE, Rarity: Common
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When an enemy minion attacks,
    //       return it to its owner's hand. It costs (2) more.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    power.GetTrigger()->triggerSource = TriggerSource::ENEMY_MINIONS;
    power.GetTrigger()->tasks = {
        std::make_shared<ConditionTask>(
            EntityType::TARGET, SelfCondList{ std::make_shared<SelfCondition>(
                                    SelfCondition::IsNotDead()) }),
        std::make_shared<FlagTask>(
            true, ComplexTask::ActivateSecret(TaskList{
                      std::make_shared<ReturnHandTask>(EntityType::TARGET),
                      std::make_shared<AddAuraEffectTask>(
                          Effects::AddCost(2), EntityType::TARGET) }))
    };
    cards.emplace("CORE_EX1_611", CardDef(power));

    // ----------------------------------------- SPELL - HUNTER
    // [CORE_EX1_617] Deadly Shot - COST:3
    // - Faction: Neutral, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: Destroy a random enemy minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_ENEMY_MINIONS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(ComplexTask::DestroyRandomEnemyMinion(1));
    cards.emplace(
        "CORE_EX1_617",
        CardDef(power, PlayReqs{ { PlayReq::REQ_MINIMUM_ENEMY_MINIONS, 1 } }));

    // ----------------------------------------- SPELL - HUNTER
    // [CORE_GIL_828] Dire Frenzy - COST:4
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a Beast +3/+3.
    //       Shuffle 3 copies into your deck with +3/+3.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_WITH_RACE = 20
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("GIL_828e", EntityType::TARGET));
    power.AddPowerTask(std::make_shared<CopyTask>(EntityType::TARGET,
                                                  ZoneType::DECK, 3, true));
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("GIL_828e", EntityType::STACK));
    cards.emplace(
        "CORE_GIL_828",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 },
                                 { PlayReq::REQ_TARGET_WITH_RACE, 20 } }));

    // ---------------------------------------- MINION - HUNTER
    // [CS3_015] Selective Breeder - COST:2 [ATK:1/HP:3]
    // - Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a copy of a Beast
    //       in your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::SELECTIVE_BREEDER));
    cards.emplace("CS3_015", CardDef(power));
}

void CoreCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void CoreCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------------------- SPELL - MAGE
    // [CORE_BOT_453] Shooting Star - COST:1
    // - Set: CORE, Rarity: Common
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Deal 1 damage to a minion and the minions next to it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<IncludeAdjacentTask>(EntityType::TARGET, true));
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::STACK, 1, true));
    cards.emplace(
        "CORE_BOT_453",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));

    // ------------------------------------------- SPELL - MAGE
    // [CORE_CS2_023] Arcane Intellect - COST:3
    // - Set: CORE, Rarity: Common
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Draw 2 cards.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DrawTask>(2));
    cards.emplace("CORE_CS2_023", CardDef(power));

    // ------------------------------------------- SPELL - MAGE
    // [CORE_CS2_029] Fireball - COST:4
    // - Set: CORE, Rarity: Common
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Deal 6 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 6, true));
    cards.emplace(
        "CORE_CS2_029",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } }));

    // ------------------------------------------- SPELL - MAGE
    // [CORE_CS2_032] Flamestrike - COST:7
    // - Set: CORE, Rarity: Epic
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Deal 5 damage to all enemy minions.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 5, true));
    cards.emplace("CORE_CS2_032", CardDef(power));

    // ------------------------------------------- SPELL - MAGE
    // [CORE_EX1_275] Cone of Cold - COST:3
    // - Set: CORE, Rarity: Common
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Freeze</b> a minion and the minions next to it,
    //       and deal 1 damage to them.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<IncludeAdjacentTask>(EntityType::TARGET, true));
    power.AddPowerTask(std::make_shared<FreezeTask>(EntityType::STACK));
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::STACK, 1, true));
    cards.emplace(
        "CORE_EX1_275",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));

    // ------------------------------------------- SPELL - MAGE
    // [CORE_EX1_287] Counterspell - COST:3
    // - Set: CORE, Rarity: Rare
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your opponent casts a spell,
    //       <b>Counter</b> it.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    // RefTag:
    // - COUNTER = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    power.GetTrigger()->triggerSource = TriggerSource::ENEMY_SPELLS;
    power.GetTrigger()->tasks =
        ComplexTask::ActivateSecret(TaskList{ std::make_shared<SetGameTagTask>(
            EntityType::TARGET, GameTag::CANT_PLAY, 1) });
    power.GetTrigger()->fastExecution = true;
    cards.emplace("CORE_EX1_287", CardDef(power));

    // ------------------------------------------- SPELL - MAGE
    // [CORE_EX1_289] Ice Barrier - COST:3
    // - Set: CORE, Rarity: Common
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your hero is attacked,
    //       gain 8 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsProposedDefender(CardType::HERO)) };
    power.GetTrigger()->tasks =
        ComplexTask::ActivateSecret(TaskList{ std::make_shared<ArmorTask>(8) });
    cards.emplace("CORE_EX1_289", CardDef(power));

    // ------------------------------------------- SPELL - MAGE
    // [CORE_GIL_801] Snap Freeze - COST:1
    // - Set: CORE, Rarity: Common
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Freeze</b> a minion.
    //       If it's already <b>Frozen</b>, destroy it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::TARGET, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsFrozen()) }));
    power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DestroyTask>(EntityType::TARGET) }));
    power.AddPowerTask(std::make_shared<FlagTask>(
        false, TaskList{ std::make_shared<FreezeTask>(EntityType::TARGET) }));
    cards.emplace(
        "CORE_GIL_801",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));

    // ------------------------------------------ MINION - MAGE
    // [CORE_KAR_009] Babbling Book - COST:1 [ATK:1/HP:1]
    // - Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a random Mage spell to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<RandomCardTask>(CardType::SPELL, CardClass::MAGE));
    power.AddPowerTask(std::make_shared<AddStackToTask>(EntityType::HAND));
    cards.emplace("CORE_KAR_009", CardDef(power));

    // ------------------------------------------ MINION - MAGE
    // [CORE_LOE_003] Ethereal Conjurer - COST:5 [ATK:6/HP:4]
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry: Discover</b> a spell.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DiscoverTask>(DiscoverType::SPELL));
    cards.emplace("CORE_LOE_003", CardDef(power));

    // ------------------------------------------ MINION - MAGE
    // [CORE_UNG_020] Arcanologist - COST:2 [ATK:2/HP:3]
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a <b>Secret</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(ComplexTask::DrawCardFromDeck(
        1, SelfCondList{
               std::make_shared<SelfCondition>(SelfCondition::IsSecret()) }));
    cards.emplace("CORE_UNG_020", CardDef(power));

    // ------------------------------------------ MINION - MAGE
    // [CS3_001] Aegwynn, the Guardian - COST:5 [ATK:5/HP:5]
    // - Set: CORE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Spell Damage +2</b>
    //       <b>Deathrattle:</b> The next minion you draw
    //       inherits these powers.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - SPELLPOWER = 1
    // --------------------------------------------------------
}

void CoreCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------- ENCHANTMENT - MAGE
    // [CS3_001e] Guardian's Legacy - COST:0
    // - Set: CORE
    // --------------------------------------------------------
    // Text: <b>Spell Damage +2</b> and
    //       "<b>Deathrattle:</b> Pass on the Guardian's Legacy."
    // --------------------------------------------------------

    // ------------------------------------- ENCHANTMENT - MAGE
    // [CS3_001e2] Guardian's Legacy (player) - COST:0
    // - Set: CORE
    // --------------------------------------------------------
    // Text: The next minion you draw inherits the Guardian's Legacy.
    // --------------------------------------------------------
}

void CoreCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    Power power;

    // --------------------------------------- MINION - PALADIN
    // [CORE_AT_075] Warhorse Trainer - COST:3 [ATK:3/HP:4]
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: Your Silver Hand Recruits have +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(
        std::make_shared<Aura>(AuraType::FIELD_EXCEPT_SOURCE, "AT_075e"));
    {
        const auto aura = dynamic_cast<Aura*>(power.GetAura());
        aura->condition = std::make_shared<SelfCondition>(
            SelfCondition::IsSilverHandRecruit());
    }
    cards.emplace("CORE_AT_075", CardDef(power));

    // ---------------------------------------- SPELL - PALADIN
    // [CORE_CS2_092] Blessing of Kings - COST:4
    // - Set: CORE, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Give a minion +4/+4. <i>(+4 Attack/+4 Health)</i>
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_092e", EntityType::TARGET));
    cards.emplace(
        "CORE_CS2_092",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));

    // ---------------------------------------- SPELL - PALADIN
    // [CORE_CS2_093] Consecration - COST:4
    // - Set: CORE, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Deal 2 damage to all enemies.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMIES, 2, true));
    cards.emplace("CORE_CS2_093", CardDef(power));

    // --------------------------------------- WEAPON - PALADIN
    // [CORE_CS2_097] Truesilver Champion - COST:4 [ATK:4/HP:0]
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever your hero attacks, restore 2 Health to it.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    power.GetTrigger()->triggerSource = TriggerSource::HERO;
    power.GetTrigger()->tasks = { std::make_shared<HealTask>(EntityType::HERO,
                                                             2) };
    cards.emplace("CORE_CS2_097", CardDef(power));

    // ---------------------------------------- SPELL - PALADIN
    // [CORE_EX1_130] Noble Sacrifice - COST:1
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When an enemy attacks,
    //       summon a 2/1 Defender as the new target.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    power.GetTrigger()->triggerSource = TriggerSource::ENEMY;
    power.GetTrigger()->tasks = ComplexTask::ActivateSecret(TaskList{
        std::make_shared<SummonTask>("EX1_130a", SummonSide::SPELL, true),
        std::make_shared<ChangeAttackingTargetTask>(EntityType::TARGET,
                                                    EntityType::STACK) });
    cards.emplace("CORE_EX1_130", CardDef(power));

    // --------------------------------------- MINION - PALADIN
    // [CORE_EX1_362] Argent Protector - COST:2 [ATK:3/HP:2]
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion
    //       <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_NONSELF_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<SetGameTagTask>(
        EntityType::TARGET, GameTag::DIVINE_SHIELD, 1));
    cards.emplace(
        "CORE_EX1_362",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 },
                                 { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                                 { PlayReq::REQ_NONSELF_TARGET, 0 } }));

    // --------------------------------------- MINION - PALADIN
    // [CORE_EX1_382] Aldor Peacekeeper - COST:3 [ATK:3/HP:3]
    // - Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Change an enemy minion's Attack to 1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_ENEMY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_382e", EntityType::TARGET));
    cards.emplace(
        "CORE_EX1_382",
        CardDef(power, PlayReqs{ { PlayReq::REQ_ENEMY_TARGET, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 },
                                 { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } }));

    // --------------------------------------- MINION - PALADIN
    // [CORE_EX1_383] Tirion Fordring - COST:8 [ATK:6/HP:6]
    // - Set: CORE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b><b>Divine Shield</b>,</b> <b>Taunt</b>
    //       <b>Deathrattle:</b> Equip a 5/3 Ashbringer.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DIVINE_SHIELD = 1
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(std::make_shared<WeaponTask>("EX1_383t"));
    cards.emplace("CORE_EX1_383", CardDef(power));

    // ---------------------------------------- SPELL - PALADIN
    // [CORE_EX1_619] Equality - COST:2
    // - Set: CORE, Rarity: Rare
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Change the Health of all minions to 1.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "EX1_619e", EntityType::ALL_MINIONS));
    cards.emplace("CORE_EX1_619", CardDef(power));

    // ---------------------------------------- SPELL - PALADIN
    // [CORE_FP1_020] Avenge - COST:1
    // - Set: CORE, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When one of your minions dies,
    //       give a random friendly minion +3/+2.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::DEATH));
    power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsFieldCount(2, RelaSign::GEQ)) };
    power.GetTrigger()->tasks = { ComplexTask::ActivateSecret(
        ComplexTask::GiveBuffToRandomMinionInField("FP1_020e")) };
    cards.emplace("CORE_FP1_020", CardDef(power));

    // --------------------------------------- MINION - PALADIN
    // [CORE_ICC_038] Righteous Protector - COST:1 [ATK:1/HP:1]
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CORE_ICC_038", CardDef(power));

    // ---------------------------------------- SPELL - PALADIN
    // [CORE_OG_273] Stand Against Darkness - COST:5
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: Summon five 1/1 Silver Hand Recruits.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<SummonTask>("CS2_101t", 5, SummonSide::SPELL));
    cards.emplace(
        "CORE_OG_273",
        CardDef(power, PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } }));

    // ---------------------------------------- SPELL - PALADIN
    // [CS3_016] Reckoning - COST:1
    // - Set: CORE, Rarity: Epic
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After an enemy minion deals 3 or
    //       more damage, destroy it.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
}

void CoreCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------- ENCHANTMENT - PALADIN
    // [CS3_029e] Pursuit of Justice - COST:0
    // - Set: CORE
    // --------------------------------------------------------
    // Text: Your Silver Hand Recruits have +1 Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [CS3_029e2] Pursuit of Justice - COST:0
    // - Set: CORE
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------
}

void CoreCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------------- SPELL - PRIEST
    // [CORE_AT_055] Flash Heal - COST:1
    // - Set: CORE, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Restore 5 Health.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<HealTask>(EntityType::TARGET, 5));
    cards.emplace(
        "CORE_AT_055",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } }));

    // ----------------------------------------- SPELL - PRIEST
    // [CORE_CS1_112] Holy Nova - COST:4
    // - Set: CORE, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Deal 2 damage to all enemy minions.
    //       Restore 2 Health to all friendly characters.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 2, true));
    power.AddPowerTask(std::make_shared<HealTask>(EntityType::FRIENDS, 2));
    cards.emplace("CORE_CS1_112", CardDef(power));

    // ----------------------------------------- SPELL - PRIEST
    // [CORE_CS1_130] Holy Smite - COST:1
    // - Set: CORE, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Deal 3 damage to a minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    cards.emplace(
        "CORE_CS1_130",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));

    // ---------------------------------------- MINION - PRIEST
    // [CORE_EX1_193] Psychic Conjurer - COST:1 [ATK:1/HP:1]
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Copy a card in your opponent's deck
    //       and add it to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<RandomTask>(EntityType::ENEMY_DECK, 1));
    power.AddPowerTask(
        std::make_shared<CopyTask>(EntityType::STACK, ZoneType::HAND));
    cards.emplace("CORE_EX1_193", CardDef(power));

    // ----------------------------------------- SPELL - PRIEST
    // [CORE_EX1_194] Power Infusion - COST:4
    // - Set: CORE, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Give a minion +2/+6.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_194e", EntityType::TARGET));
    cards.emplace(
        "CORE_EX1_194",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));

    // ---------------------------------------- MINION - PRIEST
    // [CORE_EX1_195] Kul Tiran Chaplain - COST:2 [ATK:2/HP:3]
    // - Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion +2 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_195e", EntityType::TARGET));
    cards.emplace(
        "CORE_EX1_195",
        CardDef(power, PlayReqs{ { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 },
                                 { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } }));

    // ----------------------------------------- SPELL - PRIEST
    // [CORE_EX1_197] Shadow Word: Ruin - COST:4
    // - Set: CORE, Rarity: Epic
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Destroy all minions with 5 or more Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::ALL_MINIONS));
    power.AddPowerTask(std::make_shared<FilterStackTask>(
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsTagValue(GameTag::ATK, 5, RelaSign::GEQ)) }));
    power.AddPowerTask(std::make_shared<DestroyTask>(EntityType::STACK));
    cards.emplace("CORE_EX1_197", CardDef(power));

    // ----------------------------------------- SPELL - PRIEST
    // [CORE_EX1_622] Shadow Word: Death - COST:2
    // - Set: CORE, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Destroy a minion with 5 or more Attack.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_MIN_ATTACK = 5
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DestroyTask>(EntityType::TARGET));
    cards.emplace(
        "CORE_EX1_622",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 },
                                 { PlayReq::REQ_TARGET_MIN_ATTACK, 5 } }));

    // ---------------------------------------- MINION - PRIEST
    // [CS3_013] Shadowed Spirit - COST:3 [ATK:4/HP:3]
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 3 damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 3));
    cards.emplace("CS3_013", CardDef(power));

    // ----------------------------------------- SPELL - PRIEST
    // [CS3_027] Focused Will - COST:1
    // - Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Silence</b> a minion, then give it +3 Health.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - SILENCE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<SilenceTask>(EntityType::TARGET));
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS3_027e", EntityType::TARGET));
    cards.emplace(
        "CS3_027",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));

    // ----------------------------------------- SPELL - PRIEST
    // [CS3_028] Thrive in the Shadows - COST:2
    // - Set: CORE, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: <b>Discover</b> a spell from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::SPELL_FROM_DECK));
    cards.emplace("CS3_028", CardDef(power));
}

void CoreCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [CS3_014e] Holy Affinity - COST:0
    // - Set: CORE
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("CS3_014e"));
    cards.emplace("CS3_014e", CardDef(power));

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [CS3_027e] Focused Will - COST:0
    // - Set: CORE
    // --------------------------------------------------------
    // Text: +3 Health.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("CS3_027e"));
    cards.emplace("CS3_027e", CardDef(power));
}

void CoreCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------------------ SPELL - ROGUE
    // [CORE_CS2_072] Backstab - COST:0
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 2 damage to an undamaged minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_UNDAMAGED_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, true));
    cards.emplace(
        "CORE_CS2_072",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 },
                                 { PlayReq::REQ_UNDAMAGED_TARGET, 0 } }));

    // ------------------------------------------ SPELL - ROGUE
    // [CORE_CS2_073] Cold Blood - COST:2
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion +2 Attack.
    //       <b>Combo:</b> +4 Attack instead.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_073e", EntityType::TARGET));
    power.AddComboTask(
        std::make_shared<AddEnchantmentTask>("CS2_073e2", EntityType::TARGET));
    cards.emplace(
        "CORE_CS2_073",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));

    // ------------------------------------------ SPELL - ROGUE
    // [CORE_CS2_074] Deadly Poison - COST:1
    // - Set: CORE, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Give your weapon +2 Attack.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_WEAPON_EQUIPPED = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_074e", EntityType::WEAPON));
    cards.emplace(
        "CORE_CS2_074",
        CardDef(power, PlayReqs{ { PlayReq::REQ_WEAPON_EQUIPPED, 0 } }));

    // ------------------------------------------ SPELL - ROGUE
    // [CORE_CS2_075] Sinister Strike - COST:1
    // - Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 3 damage to the enemy hero.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 3, true));
    cards.emplace("CORE_CS2_075", CardDef(power));

    // ------------------------------------------ SPELL - ROGUE
    // [CORE_CS2_076] Assassinate - COST:4
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: Destroy an enemy minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DestroyTask>(EntityType::TARGET));
    cards.emplace("CORE_CS2_076",
                  CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                           { PlayReq::REQ_MINION_TARGET, 0 },
                                           { PlayReq::REQ_ENEMY_TARGET, 0 } }));

    // ------------------------------------------ SPELL - ROGUE
    // [CORE_CS2_077] Sprint - COST:6
    // - Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Draw 4 cards.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DrawTask>(4));
    cards.emplace("CORE_CS2_077", CardDef(power));

    // ----------------------------------------- WEAPON - ROGUE
    // [CORE_CS2_080] Assassin's Blade - COST:4
    // - Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 5
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CORE_CS2_080", CardDef(power));

    // ----------------------------------------- MINION - ROGUE
    // [CORE_EX1_134] SI:7 Agent - COST:3 [ATK:3/HP:3]
    // - Set: CORE, Rarity: Rare
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
    power.AddComboTask(std::make_shared<DamageTask>(EntityType::TARGET, 2));
    cards.emplace(
        "CORE_EX1_134",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_FOR_COMBO, 0 } }));

    // ------------------------------------------ SPELL - ROGUE
    // [CORE_EX1_144] Shadowstep - COST:0
    // - Set: CORE, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Return a friendly minion to your hand.
    //       It costs (2) less.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<ReturnHandTask>(EntityType::TARGET));
    power.AddPowerTask(std::make_shared<AddAuraEffectTask>(
        Effects::ReduceCost(2), EntityType::TARGET));
    cards.emplace(
        "CORE_EX1_144",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 },
                                 { PlayReq::REQ_FRIENDLY_TARGET, 0 } }));

    // ------------------------------------------ SPELL - ROGUE
    // [CORE_EX1_145] Preparation - COST:0
    // - Set: CORE, Rarity: Epic
    // --------------------------------------------------------
    // Text: The next spell you cast this turn costs (2) less.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_145o", EntityType::PLAYER));
    cards.emplace("CORE_EX1_145", CardDef(power));

    // ----------------------------------------- MINION - ROGUE
    // [CORE_ICC_809] Plague Scientist - COST:3 [ATK:2/HP:3]
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Give a friendly minion <b>Poisonous</b>.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_TARGET_FOR_COMBO = 0
    // --------------------------------------------------------
    // RefTag:
    // - POISONOUS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddComboTask(
        std::make_shared<AddEnchantmentTask>("ICC_809e", EntityType::TARGET));
    cards.emplace(
        "CORE_ICC_809",
        CardDef(power, PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                                 { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                                 { PlayReq::REQ_TARGET_FOR_COMBO, 0 } }));

    // ----------------------------------------- MINION - ROGUE
    // [CORE_KAR_069] Swashburglar - COST:1 [ATK:1/HP:1]
    // - Race: Pirate, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a random card
    //       from another class to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<RandomCardTask>(EntityType::ENEMY_HERO));
    power.AddPowerTask(std::make_shared<AddStackToTask>(EntityType::HAND));
    cards.emplace("CORE_KAR_069", CardDef(power));

    // ----------------------------------------- MINION - ROGUE
    // [CORE_LOE_012] Tomb Pillager - COST:4 [ATK:5/HP:4]
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a Coin to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "GAME_005"));
    cards.emplace("CORE_LOE_012", CardDef(power));

    // ----------------------------------------- MINION - ROGUE
    // [CS3_005] Vanessa VanCleef - COST:2 [ATK:2/HP:3]
    // - Set: CORE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Add a copy of the last card your
    //       opponent played to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - COMBO = 1
    // --------------------------------------------------------
}

void CoreCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void CoreCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------------- MINION - SHAMAN
    // [CORE_BOT_533] Menacing Nimbus - COST:2 [ATK:2/HP:2]
    // - Race: Elemental, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a random Elemental to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<RandomCardTask>(
        CardType::MINION, CardClass::INVALID, Race::ELEMENTAL));
    power.AddPowerTask(std::make_shared<AddStackToTask>(EntityType::HAND));
    cards.emplace("CORE_BOT_533", CardDef(power));

    // ---------------------------------------- MINION - SHAMAN
    // [CORE_CS2_042] Fire Elemental - COST:6 [ATK:6/HP:5]
    // - Race: Elemental, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 4 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DamageTask>(EntityType::TARGET, 4));
    cards.emplace(
        "CORE_CS2_042",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } }));

    // ----------------------------------------- SPELL - SHAMAN
    // [CORE_CS2_045] Rockbiter Weapon - COST:2
    // - Set: CORE, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Give a friendly character +3 Attack this turn.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_045e", EntityType::TARGET));
    cards.emplace(
        "CORE_CS2_045",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_FRIENDLY_TARGET, 0 } }));

    // ----------------------------------------- SPELL - SHAMAN
    // [CORE_EX1_238] Lightning Bolt - COST:1
    // - Set: CORE, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Deal 3 damage. <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // - OVERLOAD_OWED = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    cards.emplace(
        "CORE_EX1_238",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } }));

    // ----------------------------------------- SPELL - SHAMAN
    // [CORE_EX1_246] Hex - COST:4
    // - Set: CORE, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Transform a minion into a 0/1 Frog with <b>Taunt</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<TransformTask>(EntityType::TARGET, "hexfrog"));
    cards.emplace(
        "CORE_EX1_246",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));

    // ----------------------------------------- SPELL - SHAMAN
    // [CORE_EX1_248] Feral Spirit - COST:3
    // - Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon two 2/3 Spirit Wolves with <b>Taunt</b>.
    //       <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // - OVERLOAD_OWED = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<SummonTask>("EX1_tk11", 2));
    cards.emplace(
        "CORE_EX1_248",
        CardDef(power, PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } }));

    // ----------------------------------------- SPELL - SHAMAN
    // [CORE_EX1_259] Lightning Storm - COST:3
    // - Set: CORE, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Deal 3 damage to all enemy minions.
    //       <b>Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 2
    // - OVERLOAD_OWED = 2
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 3, true));
    cards.emplace("CORE_EX1_259", CardDef(power));

    // ---------------------------------------- WEAPON - SHAMAN
    // [CORE_EX1_567] Doomhammer - COST:5
    // - Set: CORE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Windfury, Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 8
    // - WINDFURY = 1
    // - OVERLOAD = 2
    // - OVERLOAD_OWED = 2
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CORE_EX1_567", CardDef(power));

    // ---------------------------------------- MINION - SHAMAN
    // [CORE_EX1_575] Mana Tide Totem - COST:3 [ATK:0/HP:3]
    // - Race: Totem, Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    power.GetTrigger()->tasks = { std::make_shared<DrawTask>(1) };
    cards.emplace("CORE_EX1_575", CardDef(power));

    // ---------------------------------------- MINION - SHAMAN
    // [CORE_NEW1_010] Al'Akir the Windlord - COST:8 [ATK:3/HP:6]
    // - Race: Elemental, Set: CORE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Charge, Divine Shield, Taunt, Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CHARGE = 1
    // - DIVINE_SHIELD = 1
    // - TAUNT = 1
    // - WINDFURY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CORE_NEW1_010", CardDef(power));

    // ----------------------------------------- SPELL - SHAMAN
    // [CORE_UNG_817] Tidal Surge - COST:3
    // - Set: CORE, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    //       Deal 4 damage to a minion.
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 4, true));
    cards.emplace(
        "CORE_UNG_817",
        CardDef(power, PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                                 { PlayReq::REQ_TARGET_TO_PLAY, 0 } }));

    // ---------------------------------------- MINION - SHAMAN
    // [CS3_007] Novice Zapper - COST:1 [ATK:3/HP:2]
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    //       <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // - OVERLOAD_OWED = 1
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS3_007", CardDef(power));
}

void CoreCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void CoreCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    Power power;

    // --------------------------------------- MINION - WARLOCK
    // [CORE_AT_021] Tiny Knight of Evil - COST:2 [ATK:3/HP:2]
    // - Race: Demon, Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you discard a card, gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::DISCARD));
    power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "AT_021e", EntityType::SOURCE) };
    cards.emplace("CORE_AT_021", CardDef(power));

    // ---------------------------------------- SPELL - WARLOCK
    // [CORE_CS2_062] Hellfire - COST:4
    // - Set: CORE, Rarity: Common
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Deal 3 damage to all characters.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DamageTask>(EntityType::ALL, 3, true));
    cards.emplace("CORE_CS2_062", CardDef(power));

    // ---------------------------------------- SPELL - WARLOCK
    // [CORE_EX1_302] Mortal Coil - COST:1
    // - Set: CORE, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Deal 1 damage to a minion.
    //       If that kills it, draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1, true));
    power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::TARGET, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsDead()) }));
    power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DrawTask>(1) }));
    cards.emplace(
        "CORE_EX1_302",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));

    // --------------------------------------- MINION - WARLOCK
    // [CORE_EX1_304] Void Terror - COST:3 [ATK:3/HP:4]
    // - Race: Demon, Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy both adjacent minions
    //       and gain their Attack and Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<IncludeAdjacentTask>(EntityType::SOURCE));
    power.AddPowerTask(std::make_shared<GetGameTagTask>(EntityType::STACK,
                                                        GameTag::ATK, 0, 1));
    power.AddPowerTask(std::make_shared<GetGameTagTask>(EntityType::STACK,
                                                        GameTag::ATK, 1, 2));
    power.AddPowerTask(
        std::make_shared<MathNumberIndexTask>(1, 2, MathOperation::ADD));
    power.AddPowerTask(std::make_shared<GetGameTagTask>(EntityType::STACK,
                                                        GameTag::HEALTH, 0, 3));
    power.AddPowerTask(std::make_shared<GetGameTagTask>(EntityType::STACK,
                                                        GameTag::HEALTH, 1, 4));
    power.AddPowerTask(
        std::make_shared<MathNumberIndexTask>(3, 4, MathOperation::ADD, 1));
    power.AddPowerTask(std::make_shared<DestroyTask>(EntityType::STACK));
    power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "EX1_304e", EntityType::SOURCE, true));
    cards.emplace("CORE_EX1_304", CardDef(power));

    // ---------------------------------------- SPELL - WARLOCK
    // [CORE_EX1_309] Siphon Soul - COST:5
    // - Set: CORE, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Destroy a minion. Restore 3 Health to your hero.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DestroyTask>(EntityType::TARGET));
    power.AddPowerTask(std::make_shared<HealTask>(EntityType::HERO, 3));
    cards.emplace(
        "CORE_EX1_309",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));

    // ---------------------------------------- SPELL - WARLOCK
    // [CORE_EX1_312] Twisting Nether - COST:8
    // - Set: CORE, Rarity: Epic
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Destroy all minions.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DestroyTask>(EntityType::ALL_MINIONS));
    cards.emplace("CORE_EX1_312", CardDef(power));

    // --------------------------------------- MINION - WARLOCK
    // [CORE_EX1_319] Flame Imp - COST:1 [ATK:3/HP:2]
    // - Race: Demon, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DamageTask>(EntityType::HERO, 3));
    cards.emplace("CORE_EX1_319", CardDef(power));

    // ---------------------------------------- SPELL - WARLOCK
    // [CORE_GIL_191] Fiendish Circle - COST:3
    // - Set: CORE, Rarity: Common
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Summon four 1/1 Imps.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<SummonTask>("CORE_GIL_191t", 4));
    cards.emplace(
        "CORE_GIL_191",
        CardDef(power, PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } }));

    // ---------------------------------------- SPELL - WARLOCK
    // [CORE_ICC_055] Drain Soul - COST:2
    // - Set: CORE, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    //       Deal 3 damage to a minion.
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    cards.emplace(
        "CORE_ICC_055",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));

    // --------------------------------------- MINION - WARLOCK
    // [CORE_UNG_833] Lakkari Felhound - COST:4 [ATK:3/HP:8]
    // - Race: Demon, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Discard your two lowest-Cost cards.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DiscardTask>(2, DiscardType::LOWEST_COST));
    cards.emplace("CORE_UNG_833", CardDef(power));

    // --------------------------------------- MINION - WARLOCK
    // [CS3_003] Felsoul Jailer - COST:5 [ATK:4/HP:6]
    // - Race: Demon, Set: CORE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your opponent discards a minion.
    //       <b>Deathrattle:</b> Return it.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DiscardTask>(1, DiscardType::ENEMY_MINION, true));
    power.AddDeathrattleTask(std::make_shared<CustomTask>(
        [](Player* player, Entity* source, [[maybe_unused]] Playable* target) {
            const int entityID =
                source->GetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_1);
            if (entityID > 0)
            {
                Playable* playable = player->game->entityList[entityID];
                player->opponent->GetGraveyardZone()->Remove(playable);
                player->opponent->GetHandZone()->Add(playable);
            }
        }));
    cards.emplace("CS3_003", CardDef(power));
}

void CoreCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
    Power power;

    // --------------------------------------- MINION - WARLOCK
    // [CORE_GIL_191t] Imp - COST:1 [ATK:1/HP:1]
    // - Race: Demon, Set: CORE
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CORE_GIL_191t", CardDef(power));

    // --------------------------------------- MINION - WARLOCK
    // [CS3_002t] Demonic Tyrant - COST:5 [ATK:5/HP:5]
    // - Race: Demon, Set: CORE
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS3_002t", CardDef(power));
}

void CoreCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    Power power;

    // --------------------------------------- WEAPON - WARRIOR
    // [CORE_CS2_106] Fiery War Axe - COST:3
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CORE_CS2_106", CardDef(power));

    // ---------------------------------------- SPELL - WARRIOR
    // [CORE_CS2_108] Execute - COST:1
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: Destroy a damaged enemy minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // - REQ_DAMAGED_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DestroyTask>(EntityType::TARGET));
    cards.emplace(
        "CORE_CS2_108",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 },
                                 { PlayReq::REQ_ENEMY_TARGET, 0 },
                                 { PlayReq::REQ_DAMAGED_TARGET, 0 } }));

    // ---------------------------------------- SPELL - WARRIOR
    // [CORE_EX1_391] Slam - COST:2
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 2 damage to a minion. If it survives, draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, true));
    power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::TARGET, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsNotDead()) }));
    power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DrawTask>(1) }));
    cards.emplace(
        "CORE_EX1_391",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));

    // ---------------------------------------- SPELL - WARRIOR
    // [CORE_EX1_400] Whirlwind - COST:1
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 1 damage to all minions.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ALL_MINIONS, 1, true));
    cards.emplace("CORE_EX1_400", CardDef(power));

    // --------------------------------------- MINION - WARRIOR
    // [CORE_EX1_402] Armorsmith - COST:2 [ATK:1/HP:4]
    // - Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever a friendly minion takes damage, gain 1 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::TAKE_DAMAGE));
    power.GetTrigger()->triggerSource = TriggerSource::MINIONS;
    power.GetTrigger()->tasks = { std::make_shared<ArmorTask>(1) };
    cards.emplace("CORE_EX1_402", CardDef(power));

    // ---------------------------------------- SPELL - WARRIOR
    // [CORE_EX1_407] Brawl - COST:5
    // - Set: CORE, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy all minions except one.
    //       <i>(chosen randomly)</i>
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_TOTAL_MINIONS = 2
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::ALL_MINIONS, 1));
    power.AddPowerTask(std::make_shared<IncludeTask>(
        EntityType::ALL_MINIONS, std::vector<EntityType>{ EntityType::STACK }));
    power.AddPowerTask(std::make_shared<DestroyTask>(EntityType::STACK));
    cards.emplace(
        "CORE_EX1_407",
        CardDef(power, PlayReqs{ { PlayReq::REQ_MINIMUM_TOTAL_MINIONS, 2 } }));

    // ---------------------------------------- SPELL - WARRIOR
    // [CORE_EX1_410] Shield Slam - COST:1
    // - Set: CORE, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 1 damage to a minion for each Armor you have.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::HERO, GameTag::ARMOR));
    power.AddPowerTask(
        std::make_shared<DamageNumberTask>(EntityType::TARGET, true));
    cards.emplace(
        "CORE_EX1_410",
        CardDef(power, PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                                 { PlayReq::REQ_TARGET_TO_PLAY, 0 } }));

    // --------------------------------------- WEAPON - WARRIOR
    // [CORE_EX1_411] Gorehowl - COST:7
    // - Set: CORE, Rarity: Epic
    // --------------------------------------------------------
    // Text: Attacking a minion costs 1 Attack instead of 1 Durability.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::TARGET));
    power.GetTrigger()->triggerSource = TriggerSource::HERO;
    power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsProposedDefender(CardType::MINION)) };
    power.GetTrigger()->fastExecution = true;
    power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_411e", EntityType::SOURCE) };
    cards.emplace("CORE_EX1_411", CardDef(power));

    // --------------------------------------- MINION - WARRIOR
    // [CORE_EX1_414] Grommash Hellscream - COST:8 [ATK:4/HP:9]
    // - Set: CORE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    //       Has +6 Attack while damaged.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CHARGE = 1
    // - ENRAGED = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(std::make_shared<EnrageEffect>(AuraType::SELF, "EX1_414e"));
    cards.emplace("CORE_EX1_414", CardDef(power));

    // --------------------------------------- MINION - WARRIOR
    // [CORE_EX1_603] Cruel Taskmaster - COST:2 [ATK:2/HP:2]
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage to a minion
    //       and give it +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_NONSELF_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DamageTask>(EntityType::TARGET, 1));
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_603e", EntityType::TARGET));
    cards.emplace(
        "CORE_EX1_603",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 },
                                 { PlayReq::REQ_NONSELF_TARGET, 0 } }));

    // --------------------------------------- MINION - WARRIOR
    // [CORE_EX1_604] Frothing Berserker - COST:3 [ATK:2/HP:4]
    // - Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever a minion takes damage, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::TAKE_DAMAGE));
    power.GetTrigger()->triggerSource = TriggerSource::ALL_MINIONS;
    power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_604o", EntityType::SOURCE) };
    cards.emplace("CORE_EX1_604", CardDef(power));

    // --------------------------------------- MINION - WARRIOR
    // [CORE_GVG_053] Shieldmaiden - COST:5 [ATK:5/HP:5]
    // - Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain 5 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<ArmorTask>(5));
    cards.emplace("CORE_GVG_053", CardDef(power));

    // --------------------------------------- MINION - WARRIOR
    // [CS3_008] Bloodsail Deckhand - COST:1 [ATK:2/HP:1]
    // - Race: Pirate, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> The next weapon you play costs
    //       (1) less.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS3_008e", EntityType::PLAYER));
    cards.emplace("CS3_008", CardDef(power));
}

void CoreCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [CS3_008e] To Arrrms! - COST:0
    // - Set: CORE
    // --------------------------------------------------------
    // Text: Your next weapon costs (1) less.
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(std::make_shared<Aura>(AuraType::HAND,
                                         EffectList{ Effects::ReduceCost(1) }));
    {
        const auto aura = dynamic_cast<Aura*>(power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsWeapon());
        aura->removeTrigger = { TriggerType::EQUIP_WEAPON, nullptr };
    }
    cards.emplace("CS3_008e", CardDef(power));
}

void CoreCardsGen::AddDemonHunter(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------------ SPELL - DEMONHUNTER
    // [CORE_BT_035] Chaos Strike - COST:2
    // - Set: CORE, Rarity: Common
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Give your hero +2 Attack this turn. Draw a card.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BT_035e", EntityType::HERO));
    power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace("CORE_BT_035", CardDef(power));

    // ------------------------------------ SPELL - DEMONHUNTER
    // [CORE_BT_036] Coordinated Strike - COST:3
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: Summon three 1/1 Illidari with <b>Rush</b>.
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<SummonTask>("BT_036t", 3));
    cards.emplace("CORE_BT_036", CardDef(power));

    // ------------------------------------ SPELL - DEMONHUNTER
    // [CORE_BT_235] Chaos Nova - COST:5
    // - Set: CORE, Rarity: Common
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Deal 4 damage to all minions.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ALL_MINIONS, 4, true));
    cards.emplace("CORE_BT_235", CardDef(power));

    // ----------------------------------- MINION - DEMONHUNTER
    // [CORE_BT_323] Sightless Watcher - COST:2 [ATK:3/HP:2]
    // - Race: Demon, Faction: Horde, Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Look at 3 cards in your deck.
    //       Choose one to put on top.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<RandomTask>(EntityType::DECK, 3));
    power.AddPowerTask(std::make_shared<FuncNumberTask>([](Playable* playable) {
        auto playables = playable->game->taskStack.playables;

        std::vector<int> ids;
        ids.reserve(3);

        for (auto& p : playables)
        {
            ids.emplace_back(p->GetGameTag(GameTag::ENTITY_ID));
        }

        Generic::CreateChoice(playable->player, playable, ChoiceType::GENERAL,
                              ChoiceAction::SIGHTLESS_WATCHER, ids);

        return 0;
    }));
    cards.emplace("CORE_BT_323", CardDef(power));

    // ----------------------------------- MINION - DEMONHUNTER
    // [CORE_BT_351] Battlefiend - COST:1 [ATK:1/HP:2]
    // - Race: Demon, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: After your hero attacks, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    power.GetTrigger()->triggerSource = TriggerSource::HERO;
    power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "BT_351e", EntityType::SOURCE) };
    cards.emplace("CORE_BT_351", CardDef(power));

    // ----------------------------------- MINION - DEMONHUNTER
    // [CORE_BT_416] Raging Felscreamer - COST:4 [ATK:4/HP:4]
    // - Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> The next Demon you play costs (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BT_416e", EntityType::SOURCE));
    cards.emplace("CORE_BT_416", CardDef(power));

    // ------------------------------------ SPELL - DEMONHUNTER
    // [CORE_BT_427] Feast of Souls - COST:2
    // - Set: CORE, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Draw a card for each friendly minion that died this turn.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<CustomTask>(
        [](Player* player, [[maybe_unused]] Entity* source,
           [[maybe_unused]] Playable* target) {
            const int num = player->GetNumFriendlyMinionsDiedThisTurn();

            for (int i = 0; i < num; ++i)
            {
                Generic::Draw(player, nullptr);
            }
        }));
    cards.emplace("CORE_BT_427", CardDef(power));

    // ----------------------------------- MINION - DEMONHUNTER
    // [CORE_BT_480] Crimson Sigil Runner - COST:1 [ATK:1/HP:1]
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Outcast:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - OUTCAST = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddOutcastTask(std::make_shared<DrawTask>(1));
    cards.emplace("CORE_BT_480", CardDef(power));

    // ------------------------------------ SPELL - DEMONHUNTER
    // [CORE_BT_491] Spectral Sight - COST:2
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: Draw a card.
    //       <b>Outcast:</b> Draw another.
    // --------------------------------------------------------
    // GameTag:
    // - OUTCAST = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DrawTask>(1));
    power.AddOutcastTask(std::make_shared<DrawTask>(1));
    cards.emplace("CORE_BT_491", CardDef(power));

    // ------------------------------------ SPELL - DEMONHUNTER
    // [CORE_BT_801] Eye Beam - COST:3
    // - Set: CORE, Rarity: Epic
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>. Deal 3 damage to a minion.
    //       <b>Outcast:</b> This costs (1).
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // - OUTCAST = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    power.AddAura(std::make_shared<AdaptiveCostEffect>([](Playable* playable) {
        if (playable->GetZonePosition() == 0 ||
            playable->GetZonePosition() ==
                playable->player->GetHandZone()->GetCount() - 1)
        {
            return playable->GetGameTag(GameTag::COST) - 1;
        }

        return 0;
    }));
    cards.emplace(
        "CORE_BT_801",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));

    // ----------------------------------- WEAPON - DEMONHUNTER
    // [CORE_BT_921] Aldrachi Warblades - COST:3 [ATK:2/HP:0]
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // - DURABILITY = 2
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CORE_BT_921", CardDef(power));

    // ----------------------------------- MINION - DEMONHUNTER
    // [CS3_017] Gan'arg Glaivesmith - COST:3 [ATK:3/HP:2]
    // - Race: Demon, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Outcast:</b> Give your hero +3 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - OUTCAST = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddOutcastTask(
        std::make_shared<AddEnchantmentTask>("CS3_017e", EntityType::HERO));
    cards.emplace("CS3_017", CardDef(power));

    // ----------------------------------- MINION - DEMONHUNTER
    // [CS3_019] Kor'vas Bloodthorn - COST:2 [ATK:2/HP:2]
    // - Set: CORE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Charge</b>, <b>Lifesteal</b>
    //       After you play a card with <b>Outcast</b>,
    //       return this to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CHARGE = 1
    // - LIFESTEAL = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - OUTCAST = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::AFTER_PLAY_CARD));
    power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsOutcastCard())
    };
    power.GetTrigger()->tasks = { std::make_shared<ReturnHandTask>(
        EntityType::SOURCE) };
    cards.emplace("CS3_019", CardDef(power));

    // ----------------------------------- MINION - DEMONHUNTER
    // [CS3_020] Illidari Inquisitor - COST:8 [ATK:8/HP:8]
    // - Race: Demon, Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b>. After your hero attacks an enemy,
    //       this attacks it too.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    power.GetTrigger()->triggerSource = TriggerSource::HERO;
    power.GetTrigger()->tasks = { std::make_shared<AttackTask>(
        EntityType::SOURCE, EntityType::EVENT_TARGET) };
    cards.emplace("CS3_020", CardDef(power));
}

void CoreCardsGen::AddDemonHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [CS3_017e] Felfist - COST:0
    // - Set: CORE
    // --------------------------------------------------------
    // Text: +3 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("CS3_017e"));
    cards.emplace("CS3_017e", CardDef(power));
}

void CoreCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    Power power;

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_AT_092] Ice Rager - COST:3 [ATK:5/HP:2]
    // - Race: Elemental, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CORE_AT_092", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_BOT_083] Toxicologist - COST:2 [ATK:2/HP:2]
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your weapon +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BOT_083e", EntityType::WEAPON));
    cards.emplace("CORE_BOT_083", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_CS2_117] Earthen Ring Farseer - COST:3 [ATK:3/HP:3]
    // - Set: CORE, Rarity: Common
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
    power.AddPowerTask(std::make_shared<HealTask>(EntityType::TARGET, 3));
    cards.emplace(
        "CORE_CS2_117",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } }));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_CS2_120] River Crocolisk - COST:2 [ATK:2/HP:3]
    // - Race: Beast, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CORE_CS2_120", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_CS2_122] Raid Leader - COST:3 [ATK:2/HP:3]
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: Your other minions have +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(
        std::make_shared<Aura>(AuraType::FIELD_EXCEPT_SOURCE, "CS2_122e"));
    cards.emplace("CORE_CS2_122", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_CS2_142] Kobold Geomancer - COST:2 [ATK:2/HP:2]
    // - Faction: Horde, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CORE_CS2_142", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_CS2_179] Sen'jin Shieldmasta - COST:4 [ATK:3/HP:5]
    // - Faction: Horde, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CORE_CS2_179", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_CS2_182] Chillwind Yeti - COST:4 [ATK:4/HP:5]
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CORE_CS2_182", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_CS2_188] Abusive Sergeant - COST:1 [ATK:1/HP:1]
    // - Faction: Alliance, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a minion +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_188o", EntityType::TARGET));
    cards.emplace(
        "CORE_CS2_188",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_CS2_189] Elven Archer - COST:1 [ATK:1/HP:1]
    // - Faction: Horde, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_NONSELF_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DamageTask>(EntityType::TARGET, 1));
    cards.emplace(
        "CORE_CS2_189",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                                 { PlayReq::REQ_NONSELF_TARGET, 0 } }));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_CS2_203] Ironbeak Owl - COST:3 [ATK:2/HP:1]
    // - Race: Beast, Faction: Horde, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Silence</b> a minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - SILENCE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<SilenceTask>(EntityType::TARGET));
    cards.emplace(
        "CORE_CS2_203",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_CS2_222] Stormwind Champion - COST:7 [ATK:7/HP:7]
    // - Faction: Alliance, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: Your other minions have +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(
        std::make_shared<Aura>(AuraType::FIELD_EXCEPT_SOURCE, "CS2_222o"));
    cards.emplace("CORE_CS2_222", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_DAL_086] Sunreaver Spy - COST:2 [ATK:2/HP:3]
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a <b>Secret</b>,
    //       gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsControllingSecret()) }));
    power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "DAL_086e", EntityType::SOURCE) }));
    cards.emplace("CORE_DAL_086", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_EX1_005] Big Game Hunter - COST:4 [ATK:4/HP:2]
    // - Set: CORE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a minion
    //       with 7 or more Attack.
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
    power.AddPowerTask(std::make_shared<DestroyTask>(EntityType::TARGET));
    cards.emplace(
        "CORE_EX1_005",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 },
                                 { PlayReq::REQ_TARGET_MIN_ATTACK, 7 } }));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_EX1_010] Worgen Infiltrator - COST:1 [ATK:2/HP:1]
    // - Faction: Alliance, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CORE_EX1_010", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_EX1_011] Voodoo Doctor - COST:1 [ATK:2/HP:1]
    // - Faction: Horde, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 2 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<HealTask>(EntityType::TARGET, 2));
    cards.emplace(
        "CORE_EX1_011",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } }));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_EX1_012] Bloodmage Thalnos - COST:2 [ATK:1/HP:1]
    // - Set: CORE, Rarity: Legendary
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
    power.AddDeathrattleTask(std::make_shared<DrawTask>(1));
    cards.emplace("CORE_EX1_012", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_EX1_017] Jungle Panther - COST:3 [ATK:4/HP:2]
    // - Race: Beast, Faction: Horde, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CORE_EX1_017", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_EX1_028] Stranglethorn Tiger - COST:5 [ATK:5/HP:5]
    // - Race: Beast, Faction: Alliance, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CORE_EX1_028", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_EX1_046] Dark Iron Dwarf - COST:4 [ATK:4/HP:4]
    // - Faction: Alliance, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a minion +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_046e", EntityType::TARGET));
    cards.emplace(
        "CORE_EX1_046",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_EX1_049] Youthful Brewmaster - COST:2 [ATK:3/HP:2]
    // - Faction: Alliance, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Return a friendly minion
    //       from the battlefield to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_NONSELF_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<ReturnHandTask>(EntityType::TARGET));
    cards.emplace(
        "CORE_EX1_049",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                                 { PlayReq::REQ_NONSELF_TARGET, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 },
                                 { PlayReq::REQ_FRIENDLY_TARGET, 0 } }));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_EX1_059] Crazed Alchemist - COST:2 [ATK:2/HP:2]
    // - Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Swap the Attack and Health of a minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<SwapAttackHealthTask>(EntityType::TARGET, "EX1_059e"));
    cards.emplace(
        "CORE_EX1_059",
        CardDef(power, PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                                 { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } }));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_EX1_066] Acidic Swamp Ooze - COST:2 [ATK:3/HP:2]
    // - Faction: Alliance, Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy your opponent's weapon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DestroyTask>(EntityType::ENEMY_WEAPON));
    cards.emplace("CORE_EX1_066", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_EX1_082] Mad Bomber - COST:2 [ATK:3/HP:2]
    // - Faction: Alliance, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage randomly split
    //       between all other characters.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{ std::make_shared<RandomTask>(EntityType::ALL_NOSOURCE, 1),
                  std::make_shared<DamageTask>(EntityType::STACK, 1) },
        3, false));
    cards.emplace("CORE_EX1_082", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_EX1_093] Defender of Argus - COST:4 [ATK:3/HP:3]
    // - Faction: Alliance, Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give adjacent minions +1/+1
    //       and <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::MINIONS));
    power.AddPowerTask(std::make_shared<FilterStackTask>(
        EntityType::SOURCE, RelaCondList{ std::make_shared<RelaCondition>(
                                RelaCondition::IsSideBySide()) }));
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_093e", EntityType::STACK));
    cards.emplace("CORE_EX1_093", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_EX1_095] Gadgetzan Auctioneer - COST:6 [ATK:4/HP:4]
    // - Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you cast a spell, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    power.GetTrigger()->tasks = { std::make_shared<DrawTask>(1) };
    cards.emplace("CORE_EX1_095", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_EX1_096] Loot Hoarder - COST:2 [ATK:2/HP:1]
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(std::make_shared<DrawTask>(1));
    cards.emplace("CORE_EX1_096", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_EX1_103] Coldlight Seer - COST:3 [ATK:2/HP:3]
    // - Race: Murloc, Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your other Murlocs +2 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::MINIONS_NOSOURCE));
    power.AddPowerTask(std::make_shared<FilterStackTask>(
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsRace(Race::MURLOC)) }));
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_103e", EntityType::STACK));
    cards.emplace("CORE_EX1_103", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_EX1_110] Cairne Bloodhoof - COST:6 [ATK:5/HP:5]
    // - Faction: Alliance, Set: CORE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 5/5 Baine Bloodhoof.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(
        std::make_shared<SummonTask>("EX1_110t", SummonSide::DEATHRATTLE));
    cards.emplace("CORE_EX1_110", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_EX1_162] Dire Wolf Alpha - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: Adjacent minions have +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ADJACENT_BUFF = 1
    // - AURA = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(std::make_shared<AdjacentAura>("EX1_162o"));
    cards.emplace("CORE_EX1_162", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_EX1_186] SI:7 Infiltrator - COST:4 [ATK:5/HP:4]
    // - Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a random enemy <b>Secret</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::ENEMY_SECRETS, 1));
    power.AddPowerTask(
        std::make_shared<MoveToGraveyardTask>(EntityType::STACK));
    cards.emplace("CORE_EX1_186", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_EX1_187] Arcane Devourer - COST:8 [ATK:4/HP:8]
    // - Race: Elemental, Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you cast a spell, gain +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_187e", EntityType::SOURCE) };
    cards.emplace("CORE_EX1_187", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_EX1_249] Baron Geddon - COST:7 [ATK:7/HP:7]
    // - Race: Elemental, Set: CORE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       deal 2 damage to all other characters.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    power.GetTrigger()->tasks = { std::make_shared<DamageTask>(
        EntityType::ALL_NOSOURCE, 2) };
    cards.emplace("CORE_EX1_249", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_EX1_399] Gurubashi Berserker - COST:5 [ATK:2/HP:8]
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever this minion takes damage, gain +3 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::TAKE_DAMAGE));
    power.GetTrigger()->triggerSource = TriggerSource::SELF;
    power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_399e", EntityType::SOURCE) };
    cards.emplace("CORE_EX1_399", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_EX1_506] Murloc Tidehunter - COST:2 [ATK:2/HP:1]
    // - Race: Murloc, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 1/1 Murloc Scout.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<SummonTask>("CORE_EX1_506a", SummonSide::RIGHT));
    cards.emplace("CORE_EX1_506", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_EX1_509] Murloc Tidecaller - COST:1 [ATK:1/HP:2]
    // - Race: Murloc, Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you summon a Murloc, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::SUMMON));
    power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::MURLOC))
    };
    power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_509e", EntityType::SOURCE) };
    cards.emplace("CORE_EX1_509", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_EX1_564] Faceless Manipulator - COST:5 [ATK:3/HP:3]
    // - Set: CORE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a minion and become a copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_NONSELF_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<TransformCopyTask>());
    cards.emplace(
        "CORE_EX1_564",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 },
                                 { PlayReq::REQ_NONSELF_TARGET, 0 } }));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_FP1_007] Nerubian Egg - COST:2 [ATK:0/HP:2]
    // - Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 4/4 Nerubian.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(
        std::make_shared<SummonTask>("FP1_007t", SummonSide::DEATHRATTLE));
    cards.emplace("CORE_FP1_007", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_GVG_013] Cogmaster - COST:1 [ATK:1/HP:2]
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: Has +2 Attack while you have a Mech.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(std::make_shared<AdaptiveEffect>(
        GameTag::ATK, EffectOperator::ADD, [=](Playable* playable) {
            auto minions = playable->player->GetFieldZone()->GetAll();

            for (auto& minion : minions)
            {
                if (minion->card->GetRace() == Race::MECHANICAL)
                {
                    return 2;
                }
            }

            return 0;
        }));
    cards.emplace("CORE_GVG_013", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_GVG_044] Spider Tank - COST:3 [ATK:3/HP:4]
    // - Race: Mechanical, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CORE_GVG_044", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_GVG_076] Explosive Sheep - COST:2 [ATK:1/HP:1]
    // - Race: Mechanical, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 2 damage to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(
        std::make_shared<DamageTask>(EntityType::ALL_MINIONS, 2));
    cards.emplace("CORE_GVG_076", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_GVG_085] Annoy-o-Tron - COST:2 [ATK:1/HP:2]
    // - Race: Mechanical, Set: CORE, Rarity: Common
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
    cards.emplace("CORE_GVG_085", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_ICC_026] Grim Necromancer - COST:4 [ATK:2/HP:4]
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two 1/1 Skeletons.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<SummonTask>("ICC_026t", SummonSide::LEFT));
    power.AddPowerTask(
        std::make_shared<SummonTask>("ICC_026t", SummonSide::RIGHT));
    cards.emplace("CORE_ICC_026", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_LOEA10_3] Murloc Tinyfin - COST:0 [ATK:1/HP:1]
    // - Race: Murloc, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CORE_LOEA10_3", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_LOOT_124] Lone Champion - COST:3 [ATK:2/HP:4]
    // - Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control no other minions,
    //       gain <b>Taunt</b> and <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsFieldCount(1)) }));
    power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "LOOT_124e", EntityType::SOURCE) }));
    cards.emplace("CORE_LOOT_124", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_LOOT_125] Stoneskin Basilisk - COST:3 [ATK:1/HP:1]
    // - Race: Beast, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    //       <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // - POISONOUS = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CORE_LOOT_125", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_LOOT_137] Sleepy Dragon - COST:9 [ATK:4/HP:12]
    // - Race: Dragon, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CORE_LOOT_137", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_NEW1_018] Bloodsail Raider - COST:2 [ATK:2/HP:3]
    // - Race: Pirate, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain Attack equal to the Attack
    //       of your weapon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::WEAPON, GameTag::ATK));
    power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "NEW1_018e", EntityType::SOURCE, true));
    cards.emplace("CORE_NEW1_018", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_NEW1_026] Violet Teacher - COST:4 [ATK:3/HP:5]
    // - Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you cast a spell,
    //       summon a 1/1 Violet Apprentice.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "NEW1_026t", SummonSide::RIGHT) };
    cards.emplace("CORE_NEW1_026", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_NEW1_027] Southsea Captain - COST:3 [ATK:3/HP:3]
    // - Race: Pirate, Set: CORE, Rarity: Epic
    // --------------------------------------------------------
    // Text: Your other Pirates have +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(
        std::make_shared<Aura>(AuraType::FIELD_EXCEPT_SOURCE, "NEW1_027e"));
    {
        const auto aura = dynamic_cast<Aura*>(power.GetAura());
        aura->condition = std::make_shared<SelfCondition>(
            SelfCondition::IsRace(Race::PIRATE));
    }
    cards.emplace("CORE_NEW1_027", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_tt_004] Flesheating Ghoul - COST:3 [ATK:3/HP:3]
    // - Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever a minion dies, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::DEATH));
    power.GetTrigger()->triggerSource = TriggerSource::ALL_MINIONS;
    power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "tt_004o", EntityType::SOURCE) };
    cards.emplace("CORE_tt_004", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_UNG_813] Stormwatcher - COST:7 [ATK:4/HP:8]
    // - Race: Elemental, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - WINDFURY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CORE_UNG_813", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_UNG_844] Humongous Razorleaf - COST:3 [ATK:4/HP:8]
    // - Faction: Alliance, Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Can't attack.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_ATTACK = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CORE_UNG_844", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CS3_022] Fogsail Freebooter - COST:2 [ATK:2/HP:2]
    // - Race: Pirate, Set: CORE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you have a weapon equipped,
    //       deal 2 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsWeaponEquipped()) }));
    power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 2) }));
    cards.emplace(
        "CS3_022",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } }));

    // --------------------------------------- MINION - NEUTRAL
    // [CS3_024] Taelan Fordring - COST:5 [ATK:3/HP:3]
    // - Set: CORE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b><b>Taunt</b>, Divine Shield</b>
    //       <b>Deathrattle:</b> Draw your highest Cost minion.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - DIVINE_SHIELD = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(std::make_shared<DrawMinionTask>(
        DrawMinionType::HIGHEST_COST, 1, false));
    cards.emplace("CS3_024", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CS3_025] Overlord Runthak - COST:5 [ATK:3/HP:6]
    // - Set: CORE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Rush</b>. Whenever this attacks,
    //       give +1/+1 to all minions in your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - RUSH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    power.GetTrigger()->triggerSource = TriggerSource::SELF;
    power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "CS3_025e", EntityType::HAND, false, false,
        SelfCondition::IsMinion()) };
    cards.emplace("CS3_025", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CS3_031] Alexstrasza the Life-Binder - COST:9 [ATK:8/HP:8]
    // - Race: Dragon, Set: CORE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry</b>: Choose a character.
    //       If it's friendly, restore 8 Health.
    //       If it's an enemy, deal 8 damage.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsFriendly()) }));
    power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<HealTask>(EntityType::TARGET, 8) }));
    power.AddPowerTask(std::make_shared<FlagTask>(
        false,
        TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 8) }));
    cards.emplace(
        "CS3_031",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } }));

    // --------------------------------------- MINION - NEUTRAL
    // [CS3_032] Onyxia the Broodmother - COST:9 [ATK:8/HP:8]
    // - Race: Dragon, Set: CORE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of each turn,
    //       fill your board with 1/1 Whelps.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    power.GetTrigger()->eitherTurn = true;
    power.GetTrigger()->tasks = { std::make_shared<EnqueueTask>(
        TaskList{ std::make_shared<SummonTask>("EX1_116t", SummonSide::RIGHT),
                  std::make_shared<SummonTask>("EX1_116t", SummonSide::LEFT) },
        3) };
    cards.emplace("CS3_032", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CS3_033] Ysera the Dreamer - COST:9 [ATK:4/HP:12]
    // - Race: Dragon, Set: CORE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add one of each Dream card
    //       to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "DREAM_05"));
    power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "DREAM_04"));
    power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "DREAM_01"));
    power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "DREAM_02"));
    power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "DREAM_03"));
    cards.emplace("CS3_033", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CS3_034] Malygos the Spellweaver - COST:9 [ATK:4/HP:12]
    // - Race: Dragon, Set: CORE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw spells until your hand is full.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::DECK));
    power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsSpell()) }));
    power.AddPowerTask(std::make_shared<CustomTask>(
        [](Player* player, Entity* source, [[maybe_unused]] Playable* target) {
            auto& taskStack = source->game->taskStack;
            if (taskStack.playables.empty())
            {
                return;
            }

            const int freeSpace = player->GetHandZone()->GetFreeSpace();
            const int numPlayables =
                static_cast<int>(taskStack.playables.size());

            for (int i = 0; i < numPlayables && i < freeSpace; ++i)
            {
                Generic::Draw(player, taskStack.playables[i]);
            }
        }));
    cards.emplace("CS3_034", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CS3_035] Nozdormu the Eternal - COST:7 [ATK:8/HP:8]
    // - Race: Dragon, Set: CORE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Start of Game:</b> If this is in both players'
    //       decks, turns are only 15 seconds long.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - START_OF_GAME = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CS3_036] Deathwing the Destroyer - COST:10 [ATK:12/HP:12]
    // - Race: Dragon, Set: CORE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy all other minions.
    //       Discard a card for each destroyed.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<CountTask>(EntityType::ALL_MINIONS_NOSOURCE));
    power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::ALL_MINIONS_NOSOURCE));
    power.AddPowerTask(std::make_shared<CustomTask>(
        [](Player* player, Entity* source, Playable* target) {
            const int count = player->game->taskStack.num[0];

            const auto& discardTask = std::make_shared<DiscardTask>(count);
            discardTask->SetPlayer(player);
            discardTask->SetSource(source);
            discardTask->SetTarget(target);

            discardTask->Run();

            return TaskStatus::COMPLETE;
        }));
    cards.emplace("CS3_036", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CS3_037] Emerald Skytalon - COST:1 [ATK:2/HP:1]
    // - Race: Beast, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS3_037", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [CS3_038] Redgill Razorjaw - COST:2 [ATK:3/HP:1]
    // - Race: Murloc, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CS3_038", CardDef(power));
}

void CoreCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
    Power power;

    // --------------------------------------- MINION - NEUTRAL
    // [CORE_EX1_506a] Murloc Scout - COST:1 [ATK:1/HP:1]
    // - Race: Murloc, Set: CORE, Rarity: Common
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("CORE_EX1_506a", CardDef(power));

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CS3_025e] Rallying Cry - COST:0
    // - Set: CORE
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("CS3_025e"));
    cards.emplace("CS3_025e", CardDef(power));

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CS3_035e] Nozdormu Time - COST:0
    // - Set: CORE
    // --------------------------------------------------------
    // Text: Turns are 15 seconds long.
    // --------------------------------------------------------
}

void CoreCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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