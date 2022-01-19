// This code is based on Sabberstone project.
// Copyright (c) 2017-2021 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2021 Chris Ohk

#include <Rosetta/PlayMode/CardSets/AlteracValleyCardsGen.hpp>
#include <Rosetta/PlayMode/Enchants/Enchants.hpp>
#include <Rosetta/PlayMode/Tasks/ComplexTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks.hpp>

using namespace RosettaStone::PlayMode::SimpleTasks;

namespace RosettaStone::PlayMode
{
using PlayReqs = std::map<PlayReq, int>;
using SelfCondList = std::vector<std::shared_ptr<SelfCondition>>;
using EffectList = std::vector<std::shared_ptr<IEffect>>;

void AlteracValleyCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ HERO - HUNTER
    // [AV_113] Beaststalker Tavish - COST:6
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> and
    //       cast 2 Improved <b>Secrets</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // -------------------------------------------- HERO - MAGE
    // [AV_200] Magister Dawngrasp - COST:7
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Recast a spell from
    //       each spell school you've cast this game.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- HERO - WARRIOR
    // [AV_202] Rokara, the Valorous - COST:7
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Equip a 5/2 Unstoppable Force.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------- HERO - ROGUE
    // [AV_203] Shadowcrafter Scabbs - COST:7
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Return all minions to
    //       their owner's hands. Summon two 4/2 Shadows
    //       with <b>Stealth</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ------------------------------------- HERO - DEMONHUNTER
    // [AV_204] Kurtrus, Demon-Render - COST:6
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two 1/4 Demons with <b>Rush</b>.
    //       <i>(Improved by your hero attacks this game.)</i>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ------------------------------------------- HERO - DRUID
    // [AV_205] Wildheart Guff - COST:5
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Set your maximum Mana to 20.
    //       Gain a Mana Crystal. Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- HERO - PALADIN
    // [AV_206] Lightforged Cariel - COST:7
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 2 damage to all enemies.
    //       Equip a 2/5 Immovable Object.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ HERO - PRIEST
    // [AV_207] Xyrella, the Devout - COST:8
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Trigger the <b>Deathrattle</b>
    //       of every friendly minion that died this game.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------------------ HERO - SHAMAN
    // [AV_258] Bru'kan of the Elements - COST:8
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Call upon the power of two Elements!
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- HERO - WARLOCK
    // [AV_316] Dreadlich Tamsin - COST:6
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage to all minions.
    //       Shuffle 3 Rifts into your deck. Draw 3 cards.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------ HERO_POWER - HUNTER
    // [AV_113p] Summon Pet - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Summon an Animal Companion.
    // --------------------------------------------------------

    // -------------------------------------- HERO_POWER - MAGE
    // [AV_200p2] Arcane Burst - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Deal 2 damage.
    //       <b>Honorable Kill:</b> Gain +2 damage.
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // --------------------------------------------------------

    // ----------------------------------- HERO_POWER - WARRIOR
    // [AV_202p] Grand Slam - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Deal 2 damage.
    //       <b>Honorable Kill:</b> Gain 4 Armor.
    // --------------------------------------------------------
    // RefTag:
    // - HONORABLEKILL = 1
    // --------------------------------------------------------

    // ------------------------------------- HERO_POWER - ROGUE
    // [AV_203p] Sleight of Hand - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power.</b>
    //       The next card you play this turn costs (2) less.
    // --------------------------------------------------------

    // ------------------------------- HERO_POWER - DEMONHUNTER
    // [AV_204p] Ashfallen's Fury - COST:1
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       +2 Attack this turn.
    //       After a friendly minion attacks, refresh this.
    // --------------------------------------------------------

    // ------------------------------------- HERO_POWER - DRUID
    // [AV_205p] Nurture - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       <b>Choose One -</b> Draw a card;
    //       or Gain a Mana Crystal.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------

    // ----------------------------------- HERO_POWER - PALADIN
    // [AV_206p] Blessing of Queens - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Give a random minion in your hand +4/+4.
    // --------------------------------------------------------

    // ------------------------------------ HERO_POWER - PRIEST
    // [AV_207p] Holy Touch - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Restore 5 Health. Flip each turn.
    // --------------------------------------------------------

    // ------------------------------------ HERO_POWER - PRIEST
    // [AV_207p2] Void Spike - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Deal 5 damage. Flip each turn.
    // --------------------------------------------------------

    // ------------------------------------ HERO_POWER - SHAMAN
    // [AV_258p] Elemental Mastery - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Call upon a different Element every turn!
    // --------------------------------------------------------

    // ------------------------------------ HERO_POWER - SHAMAN
    // [AV_258p2] Water Invocation - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Restore 6 health to all friendly characters.
    //       Swaps each turn.
    // --------------------------------------------------------

    // ------------------------------------ HERO_POWER - SHAMAN
    // [AV_258pt] Earth Invocation - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Summon two 2/3 Elementals with <b>Taunt</b>.
    //       Swaps each turn.
    // --------------------------------------------------------

    // ------------------------------------ HERO_POWER - SHAMAN
    // [AV_258pt3] Fire Invocation - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Deal 6 damage to the enemy hero.
    //       Swaps each turn.
    // --------------------------------------------------------

    // ------------------------------------ HERO_POWER - SHAMAN
    // [AV_258pt4] Lightning Invocation - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Deal 2 damage to all enemy minions.
    //       Swaps each turn.
    // --------------------------------------------------------

    // ------------------------------------ HERO_POWER - SHAMAN
    // [AV_258pt7] Command the Elements - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Call upon a different Element every turn!
    // --------------------------------------------------------

    // ----------------------------------- HERO_POWER - WARLOCK
    // [AV_316hp] Chains of Dread - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Shuffle a Rift into your deck. Draw a card.
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------------- MINION - DRUID
    // [AV_210] Pathmaker - COST:3 [ATK:3/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Cast the other choice from
    //       the last <b>Choose One</b> spell you've cast.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [AV_211] Dire Frostwolf - COST:4 [ATK:4/HP:4]
    // - Race: Beast, Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //       <b>Deathrattle:</b> Summon a 2/2 Wolf with <b>Stealth</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - STEALTH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(
        std::make_shared<SummonTask>("AV_211t", SummonSide::DEATHRATTLE));
    cards.emplace("AV_211", CardDef(power));

    // ----------------------------------------- MINION - DRUID
    // [AV_291] Frostsaber Matriarch - COST:7 [ATK:4/HP:5]
    // - Race: Beast, Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Taunt</b>. Costs (1) less for each Beast
    //       you've summoned this game.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [AV_292] Heart of the Wild - COST:3
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion +2/+2, then give your Beasts +1/+1.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [AV_293] Wing Commander Mulverick - COST:4 [ATK:2/HP:5]
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Rush</b>.
    //       Your minions have "<b>Honorable Kill:</b>
    //       Summon a 2/2 Wyvern with <b>Rush</b>."
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AURA = 1
    // - RUSH = 1
    // --------------------------------------------------------
    // RefTag:
    // - HONORABLEKILL = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [AV_294] Clawfury Adept - COST:2 [ATK:2/HP:3]
    // - Race: Beast, Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give all other friendly characters
    //       +1 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [AV_295] Capture Coldtooth Mine - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Draw your lowest Cost card;
    //       or Draw your highest Cost card.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [AV_296] Pride Seeker - COST:3 [ATK:2/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your next <b>Choose One</b> card
    //       costs (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [AV_360] Frostwolf Kennels - COST:3
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn, summon a 2/2 Wolf
    //       with <b>Stealth</b>. Lasts 3 turns.
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "AV_211t", SummonSide::SPELL) };
    power.GetTrigger()->lastTurn = 3;
    cards.emplace("AV_360", CardDef(power));
}

void AlteracValleyCardsGen::AddDruidNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ SPELL - DRUID
    // [AV_205a] Ice Blossom - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Gain a Mana Crystal.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [AV_205pb] Valley Root - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Draw a card.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [AV_210e] Path Tracker - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Tracking Sub-Spell.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [AV_292e] Pack Alpha - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [AV_292e2] Pack Member - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [AV_293e] Air Strike - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Honorable Kill:</b> Summon a 2/2 Wyvern
    //       with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [AV_293t] Strike Wyvern - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [AV_294e] Snowcapped - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +1 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [AV_295a] More Resources - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Draw your lowest Cost card.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [AV_295b] More Supplies - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Draw your highest Cost card.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [AV_296e] Grown Up - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Your next Choose One card costs (2) less.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [AV_296e2] Proud - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------------- SPELL - HUNTER
    // [AV_147] Dun Baldar Bunker - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn, draw a <b>Secret</b>
    //       and set its Cost to (1). Lasts 3 turns.
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    power.GetTrigger()->tasks = { ComplexTask::DrawCardFromDeck(
        1,
        SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsSecret()) },
        true) };
    power.GetTrigger()->tasks.emplace_back(
        std::make_shared<AddEnchantmentTask>("AV_147e", EntityType::STACK));
    power.GetTrigger()->lastTurn = 3;
    cards.emplace("AV_147", CardDef(power));

    // ----------------------------------------- SPELL - HUNTER
    // [AV_224] Spring the Trap - COST:4
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 3 damage to a minion and cast a <b>Secret</b>
    //       from your deck. <b>Honorable Kill:</b> Cast 2.
    // --------------------------------------------------------
    // RefTag:
    // - HONORABLEKILL = 1
    // - SECRET = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [AV_226] Ice Trap - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your opponent casts a spell,
    //       return it to their hand instead. It costs (1) more.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - HUNTER
    // [AV_244] Bloodseeker - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Honorable Kill:</b> Gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddHonorableKillTask(
        std::make_shared<AddEnchantmentTask>("AV_244e", EntityType::WEAPON));
    cards.emplace("AV_244", CardDef(power));

    // ----------------------------------------- SPELL - HUNTER
    // [AV_333] Revive Pet - COST:3
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: <b>Discover</b> a friendly Beast that died this game.
    //       Summon it.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [AV_334] Stormpike Battle Ram - COST:4 [ATK:4/HP:3]
    // - Race: Beast, Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Deathrattle:</b> Your next Beast costs (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - RUSH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(
        std::make_shared<AddEnchantmentTask>("AV_334e2", EntityType::SOURCE));
    cards.emplace("AV_334", CardDef(power));

    // ---------------------------------------- MINION - HUNTER
    // [AV_335] Ram Tamer - COST:3 [ATK:4/HP:3]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a <b>Secret</b>,
    //       gain +1/+1 and <b>Stealth</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // - STEALTH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsControllingSecret()) }));
    power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                            "AV_335e", EntityType::SOURCE),
                        std::make_shared<SetGameTagTask>(
                            EntityType::SOURCE, GameTag::STEALTH, 1) }));
    cards.emplace("AV_335", CardDef(power));

    // ---------------------------------------- MINION - HUNTER
    // [AV_336] Wing Commander Ichman - COST:9 [ATK:5/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a Beast from your deck
    //       and give it <b>Rush</b>.
    //       If it kills a minion this turn, repeat.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [AV_337] Mountain Bear - COST:7 [ATK:5/HP:6]
    // - Race: Beast, Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Summon two 2/4 Cubs with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(
        std::make_shared<SummonTask>("AV_337t", 2, SummonSide::DEATHRATTLE));
    cards.emplace("AV_337", CardDef(power));
}

void AlteracValleyCardsGen::AddHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------------- SPELL - HUNTER
    // [AV_113t1] Improved Explosive Trap - COST:2
    // - Set: ALTERAC_VALLEY
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your hero is attacked,
    //       deal 3 damage to all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - SECRET = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [AV_113t2] Improved Freezing Trap - COST:2
    // - Set: ALTERAC_VALLEY
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When an enemy minion attacks,
    //       return it to its owner's hand. It costs (4) more.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - SECRET = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [AV_113t2e] Freezing - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (4) more.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [AV_113t3] Improved Snake Trap - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When one of your minions is attacked,
    //       summon three 2/2 Snakes.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - SECRET = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [AV_113t3t2] Snake - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Set: ALTERAC_VALLEY
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [AV_113t7] Improved Pack Tactics - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When a friendly minion is attacked,
    //       summon two 3/3 copies.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - SECRET = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [AV_113t8] Improved Open the Cages - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your turn starts, if you control
    //       two minions, summon two Animal Companions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - SECRET = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [AV_113t9] Improved Ice Trap - COST:2
    // - Set: ALTERAC_VALLEY
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your opponent casts a spell,
    //       return it to their hand instead. It costs (2) more.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - SECRET = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [AV_113t9e] Mega Frosty - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (2) more.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [AV_147e] Cloaked Secrets - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (1).
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(std::make_shared<Enchant>(Effects::SetCost(1)));
    cards.emplace("AV_147e", CardDef(power));

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [AV_226e] Frosty - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (1) more.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [AV_244e] Bloodseeking - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(
        std::make_shared<Enchant>(std::vector<std::shared_ptr<IEffect>>(
            { Effects::AttackN(1), Effects::DurabilityN(1) })));
    cards.emplace("AV_244e", CardDef(power));

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [AV_334e] Ready for Battle - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [AV_334e2] Battle Ready - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------
    power.ClearData();
    power.AddAura(std::make_shared<Aura>(AuraType::HAND,
                                         EffectList{ Effects::ReduceCost(2) }));
    {
        const auto aura = dynamic_cast<Aura*>(power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::BEAST));
        aura->removeTrigger = { TriggerType::PLAY_MINION,
                                std::make_shared<SelfCondition>(
                                    SelfCondition::IsRace(Race::BEAST)) };
    }
    cards.emplace("AV_334e2", CardDef(power));

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [AV_335e] Sneaking Up - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("AV_335e"));
    cards.emplace("AV_335e", CardDef(power));

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [AV_336e] Frightful Pack - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: If this kills a minion this turn, summon a
    //       random Beast from your deck and give it <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [AV_337t] Mountain Cub - COST:3 [ATK:2/HP:4]
    // - Race: Beast, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("AV_337t", CardDef(power));
}

void AlteracValleyCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------------------ MINION - MAGE
    // [AV_114] Shivering Sorceress - COST:1 [ATK:2/HP:2]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Reduce the Cost of the highest
    //       Cost spell in your hand by (1).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [AV_115] Amplified Snowflurry - COST:2 [ATK:2/HP:3]
    // - Race: Elemental, Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your next Hero Power costs (0)
    //       and <b>Freezes</b> the target.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [AV_116] Arcane Brilliance - COST:4
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Add a copy of a 7, 8, 9, and 10-Cost spell
    //       in your deck to your hand.
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [AV_212] Siphon Mana - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Deal 2 damage. <b>Honorable Kill</b>: Reduce
    //       the Cost of spells in your hand by (1).
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [AV_218] Mass Polymorph - COST:7
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Transform all minions into 1/1 Sheep.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<TransformTask>(EntityType::ALL_MINIONS, "CS2_tk1"));
    cards.emplace("AV_218", CardDef(power));

    // ------------------------------------------- SPELL - MAGE
    // [AV_282] Build a Snowman - COST:3
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: Summon a 3/3 Snowman that <b>Freezes</b>.
    //       Add "Build a Snowbrute" to your hand.
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [AV_283] Rune of the Archmage - COST:9
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: Cast 20 Mana worth of Mage spells at enemies.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [AV_284] Balinda Stonehearth - COST:6 [ATK:5/HP:5]
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw 2 spells.
    //       Swap their Costs with this minion's stats.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [AV_290] Iceblood Tower - COST:10
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn, cast another spell
    //       from your deck. Lasts 3 turns.
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddMageNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ------------------------------------- ENCHANTMENT - MAGE
    // [AV_114e] Shocking - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ------------------------------------- ENCHANTMENT - MAGE
    // [AV_115e5] Icy - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Your Hero Power costs (0) and
    //       <b>Freezes</b> the target.
    // --------------------------------------------------------

    // ------------------------------------- ENCHANTMENT - MAGE
    // [AV_212e] Kablow! - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [AV_282t] Snowman - COST:3 [ATK:3/HP:3]
    // - Race: Elemental, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Freeze</b> any character damaged by this minion.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [AV_282t2] Build a Snowbrute - COST:6
    // - Set: ALTERAC_VALLEY
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: Summon a 6/6 Snowbrute that <b>Freezes</b>.
    //       Add "Build a Snowgre" to your hand.
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [AV_282t3] Snowbrute - COST:6 [ATK:6/HP:6]
    // - Race: Elemental, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Freeze</b> any character damaged by this minion.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [AV_282t4] Build a Snowgre - COST:9
    // - Set: ALTERAC_VALLEY
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: Summon a 9/9 Snowgre that <b>Freezes</b>.
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [AV_282t5] Snowgre - COST:9 [ATK:9/HP:9]
    // - Race: Elemental, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Freeze</b> any character damaged by this minion.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ------------------------------------- ENCHANTMENT - MAGE
    // [AV_284e] Arcane Swap - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Cost swapped.
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- SPELL - PALADIN
    // [AV_213] Vitality Surge - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Draw a minion.
    //       Restore Health to your hero equal to its Cost.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [AV_338] Hold the Bridge - COST:3
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Give a minion +2/+1 and <b>Divine Shield</b>.
    //       It gains <b>Lifesteal</b> until end of turn.
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [AV_339] Templar Captain - COST:8 [ATK:8/HP:8]
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b>. After this attacks a minion,
    //       summon a 5/5 Defender with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [AV_340] Brasswing - COST:8 [ATK:9/HP:7]
    // - Race: Dragon, Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: At the end of your turn, deal 2 damage to all enemies.
    //       <b>Honorable Kill:</b> Restore 4 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - PALADIN
    // [AV_341] Cavalry Horn - COST:5
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon the lowest Cost minion
    //       in your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [AV_342] Protect the Innocent - COST:5
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon a 5/5 Defender with <b>Taunt</b>.
    //       If your hero was healed this turn, summon another.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [AV_343] Stonehearth Vindicator - COST:3 [ATK:3/HP:1]
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a spell that costs (3) or less.
    //       It costs (0) this turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [AV_344] Dun Baldar Bridge - COST:4
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you summon a minion, give it +2/+2.
    //       Lasts 3 turns.
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [AV_345] Saidan the Scarlet - COST:3 [ATK:2/HP:2]
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Rush.</b> Whenever this minion gains Attack or
    //       Health, double that amount <i>(wherever this is)</i>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - RUSH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- WEAPON - PALADIN
    // [AV_146] The Immovable Object - COST:7
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: This doesn't lose Durability.
    //       Your hero takes half damage, rounded up.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [AV_146e] Tough - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Take half damage, rounded up.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [AV_146e2] Resilient Weapon - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: No durability loss.
    // --------------------------------------------------------
    // GameTag:
    // - ENCHANTMENT_INVISIBLE = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [AV_206pe] Blessing of Queens - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +4/+4.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [AV_338e] High Morale - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [AV_338e2] High Morale - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [AV_342t] Stormpike Defender - COST:5 [ATK:5/HP:5]
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [AV_343e] Stone Fortitude - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (3) less this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [AV_344e] Coldtooth Supplies - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- SPELL - PRIEST
    // [AV_315] Deliverance - COST:3
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Deal 3 damage to a minion.
    //       <b>Honorable Kill:</b> Summon a new 3/3 copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [AV_324] Shadow Word: Devour - COST:1
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Choose a minion.
    //       It steals 1 Health from ALL other minions.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [AV_325] Undying Disciple - COST:6 [ATK:3/HP:7]
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Deal damage equal to
    //       this minion's Attack to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [AV_326] Luminous Geode - COST:2 [ATK:1/HP:4]
    // - Race: Elemental, Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: After a friendly minion is healed, give it +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [AV_328] Spirit Guide - COST:5 [ATK:5/HP:5]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Draw a Holy spell and
    //       a Shadow spell.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [AV_329] Bless - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Give a minion +2 Health, then set its Attack
    //       to be equal to its Health.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [AV_330] Gift of the Naaru - COST:1
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Restore 3 Health to all characters.
    //       If any are still damaged, draw a card.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [AV_331] Najak Hexxen - COST:4 [ATK:1/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Take control of an enemy minion.
    //       <b>Deathrattle:</b> Give the minion back.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [AV_664] Stormpike Aid Station - COST:3
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       give your minions +2 Health. Lasts 3 turns.
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddPriestNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- ENCHANTMENT - PRIEST
    // [AV_315e2] Salvation - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Attack and Health set to 3.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [AV_324e2] Superior - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Increased Health.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [AV_324e2b] Superior - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Increased Health.
    // --------------------------------------------------------
    // GameTag:
    // - ENCHANTMENT_INVISIBLE = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [AV_324e3] Inferior - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Reduced Health.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [AV_324eb] Inferior - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Reduced Health.
    // --------------------------------------------------------
    // GameTag:
    // - ENCHANTMENT_INVISIBLE = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [AV_326e] Illuminated - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [AV_329e] Blessed - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2 Health and this minion's Attack is equal to
    //       its Health.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [AV_329e2] Blessed - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2 Health.
    // --------------------------------------------------------
    // GameTag:
    // - ENCHANTMENT_INVISIBLE = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [AV_331e] Dark Concoction - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Give this back when Najak is destroyed.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [AV_331e2] Dark Concoction - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Took control of {0}.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [AV_664e2] Restored - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2 Health.
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------------- MINION - ROGUE
    // [AV_201] Coldtooth Yeti - COST:3 [ATK:1/HP:5]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Gain +3 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddComboTask(
        std::make_shared<AddEnchantmentTask>("AV_201e", EntityType::SOURCE));
    cards.emplace("AV_201", CardDef(power));

    // ----------------------------------------- MINION - ROGUE
    // [AV_298] Wildpaw Gnoll - COST:5 [ATK:4/HP:5]
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       Costs (1) less for each card you've added to
    //       your hand from another class.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [AV_400] Snowfall Graveyard - COST:3
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Your <b>Deathrattles</b> trigger twice. Lasts 3 turns.
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- WEAPON - ROGUE
    // [AV_402] The Lobotomizer - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Honorable Kill:</b> Get a copy of the top card
    //       of your opponent's deck.
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [AV_403] Cera'thine Fleetrunner - COST:5 [ATK:5/HP:5]
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Replace your minions in hand and
    //       deck with ones from other classes.
    //       They cost (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [AV_405] Contraband Stash - COST:5
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Replay 5 cards from other classes
    //       you've played this game.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [AV_601] Forsaken Lieutenant - COST:2 [ATK:2/HP:2]
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b><b>Stealth</b>.</b>
    //       After you play a <b>Deathrattle</b> minion,
    //       become a 2/2 copy of it with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [AV_710] Reconnaissance - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Discover</b> a <b>Deathrattle</b> minion from
    //       another class. It costs (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [AV_711] Double Agent - COST:3 [ATK:3/HP:3]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a card from
    //       another class, summon a copy of this.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddRogueNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [AV_201e] Yeti Rage - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +3 Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("AV_201e"));
    cards.emplace("AV_201e", CardDef(power));

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [AV_203pe] Sleight of Hand - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: The next card you play this turn costs (2) less.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [AV_203po] Sleight of Hand - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: The next card you play this turn costs (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [AV_203t] Shadow - COST:3 [ATK:4/HP:2]
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [AV_400e] Bunkered Up - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Deathrattles trigger twice.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [AV_403e2] Quickfooted - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [AV_601e] Forsaken - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: 2/2.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [AV_710e] Contracted - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------------- SPELL - SHAMAN
    // [AV_107] Glaciate - COST:6
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Discover</b> an 8-Cost minion.
    //       Summon and <b>Freeze</b> it.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [AV_250] Snowball Fight! - COST:3
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: Deal 1 damage to a minion and <b>Freeze</b> it.
    //       If it survives, repeat this on another minion!
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [AV_251] Cheaty Snobold - COST:3 [ATK:3/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: After an enemy is <b>Frozen</b>, deal 3 damage to it.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [AV_255] Snowfall Guardian - COST:6 [ATK:3/HP:3]
    // - Race: Elemental, Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Freeze</b> all other minions.
    //       Gain +1/+1 for each <b>Frozen</b> minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [AV_257] Bearon Gla'shear - COST:7 [ATK:6/HP:6]
    // - Race: Elemental, Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> For each Frost spell
    //       you've cast this game, summon a 3/4 Elemental
    //       that <b>Freezes</b>. <i>(@)</i>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [AV_259] Frostbite - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: Deal 3 damage. <b>Honorable Kill:</b>
    //       Your opponent's next spell costs (2) more.
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [AV_260] Sleetbreaker - COST:2 [ATK:3/HP:2]
    // - Race: Elemental, Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a Windchill to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "AV_266"));
    cards.emplace("AV_260", CardDef(power));

    // ----------------------------------------- SPELL - SHAMAN
    // [AV_266] Windchill - COST:1
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Freeze</b> a minion. Draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<FreezeTask>(EntityType::TARGET));
    power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace(
        "AV_266",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 } }));

    // ----------------------------------------- SPELL - SHAMAN
    // [AV_268] Wildpaw Cavern - COST:4
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn, summon a 3/4 Elemental
    //       that <b>Freezes</b>. Lasts 3 turns.
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "AV_257t", SummonSide::SPELL) };
    power.GetTrigger()->lastTurn = 3;
    cards.emplace("AV_268", CardDef(power));
}

void AlteracValleyCardsGen::AddShamanNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [AV_255e] Chilled - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [AV_257t] Frozen Stagguard - COST:3 [ATK:3/HP:4]
    // - Race: Elemental, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Freeze</b> any character damaged by this minion.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("AV_257t", CardDef(power));

    // ----------------------------------------- SPELL - SHAMAN
    // [AV_258t] Earth Invocation - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Summon two 2/3 Elementals with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [AV_258t2] Water Invocation - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Restore #6 Health to all friendly characters.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [AV_258t3] Fire Invocation - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Deal 6 damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [AV_258t4] Lightning Invocation - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Deal 2 damage to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [AV_258t6] Earthen Guardian - COST:2 [ATK:2/HP:3]
    // - Race: Elemental, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- SPELL - WARLOCK
    // [AV_277] Seeds of Destruction - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Shuffle four Rifts into your deck.
    //       They summon a 3/3 Dread Imp when drawn.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [AV_281] Felfire in the Hole! - COST:5
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Draw a spell and deal 2 damage to all enemies.
    //       If it's a Fel spell, deal 1 more.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [AV_285] Full-Blown Evil - COST:3
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Deal 5 damage randomly split among all enemy minions.
    //       Repeatable this turn.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [AV_286] Felwalker - COST:6 [ATK:3/HP:7]
    // - Race: Demon, Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>.
    //       <b>Battlecry</b>: Cast the highest Cost Fel spell
    //       from your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [AV_308] Grave Defiler - COST:1 [ATK:2/HP:1]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Copy a Fel spell in your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [AV_312] Sacrificial Summoner - COST:3 [ATK:3/HP:3]
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a friendly minion.
    //       Summon a minion from your deck that costs (1) more.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [AV_313] Hollow Abomination - COST:5 [ATK:2/HP:8]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage to all enemy minions.
    //       <b>Honorable Kill:</b> Gain the minion's Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - HONORABLEKILL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [AV_317] Tamsin's Phylactery - COST:4
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: <b>Discover</b> a friendly <b>Deathrattle</b>
    //       minion that died this game.
    //       Give your minions its <b>Deathrattle</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DISCOVER = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [AV_657] Desecrated Graveyard - COST:3
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn, destroy your lowest
    //       Attack minion to summon a 4/4 Shade. Lasts 3 turns.
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [AV_286e2] Felgorged - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [AV_313e] Consumed - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Increased attack.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [AV_316t] Dread Imp - COST:3 [ATK:3/HP:3]
    // - Race: Demon, Set: ALTERAC_VALLEY
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [AV_316t4] Fel Rift - COST:3
    // - Set: ALTERAC_VALLEY
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: <b>Casts When Drawn</b>
    //       Summon a 3/3 Dread Imp.
    // --------------------------------------------------------
    // GameTag:
    // - TOPDECK = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [AV_317e] Lich Perfume - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Copied <b>Deathrattle</b> from {0}.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [AV_657e] Sacrificing - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Sacrifice this at end of turn.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [AV_657t] Desecrated Shade - COST:4 [ATK:4/HP:4]
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------------- SPELL - WARRIOR
    // [AV_108] Shield Shatter - COST:10
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: Deal 5 damage to all minions.
    //       Costs (1) less for each Armor you have.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [AV_109] Frozen Buckler - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: Gain 10 Armor.
    //       At the start of your next turn, lose 5 Armor.
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<ArmorTask>(10));
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("AV_109e", EntityType::SOURCE));
    cards.emplace("AV_109", CardDef(power));

    // ---------------------------------------- SPELL - WARRIOR
    // [AV_119] To the Front! - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Your minions cost (2) less this turn
    //       <i>(but not less than 1)</i>.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [AV_145] Captain Galvangar - COST:6 [ATK:6/HP:6]
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you have gained 15 or
    //       more Armor this game, gain +3/+3 and <b>Charge</b>.
    //       <i>({0} left!)</i> <i>(Ready!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [AV_321] Glory Chaser - COST:3 [ATK:4/HP:3]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: After you play a <b>Taunt</b> minion, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::AFTER_PLAY_MINION));
    power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::HasTaunt())
    };
    power.GetTrigger()->tasks = { std::make_shared<DrawTask>(1) };
    cards.emplace("AV_321", CardDef(power));

    // ---------------------------------------- SPELL - WARRIOR
    // [AV_322] Snowed In - COST:3
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: Destroy a damaged minion.
    //       <b>Freeze</b> all other minions.
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_DAMAGED_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DestroyTask>(EntityType::TARGET));
    power.AddPowerTask(
        std::make_shared<FreezeTask>(EntityType::ALL_MINIONS_NOTARGET));
    cards.emplace(
        "AV_322",
        CardDef(power, PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                 { PlayReq::REQ_MINION_TARGET, 0 },
                                 { PlayReq::REQ_DAMAGED_TARGET, 0 } }));

    // --------------------------------------- MINION - WARRIOR
    // [AV_323] Scrapsmith - COST:3 [ATK:2/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Add two 2/4 Grunts
    //       with <b>Taunt</b> to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "AV_323t", 2));
    cards.emplace("AV_323", CardDef(power));

    // --------------------------------------- MINION - WARRIOR
    // [AV_565] Axe Berserker - COST:4 [ATK:3/HP:5]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>. <b>Honorable Kill:</b> Draw a weapon.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    // RefTag:
    // - HONORABLEKILL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddHonorableKillTask(std::make_shared<DrawWeaponTask>(1));
    cards.emplace("AV_565", CardDef(power));

    // ---------------------------------------- SPELL - WARRIOR
    // [AV_660] Iceblood Garrison - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       deal 1 damage to all minions. Lasts 3 turns.
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [AV_109e] Chilly - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Lose 5 Armor next turn.
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_START));
    power.GetTrigger()->tasks = { std::make_shared<ArmorTask>(-5) };
    power.GetTrigger()->removeAfterTriggered = true;
    cards.emplace("AV_109e", CardDef(power));

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [AV_119e] Frontlined - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Your minions cost (2) less this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [AV_145e] Fury of the Frostwolf - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +3/+3 and <b>Charge</b>.
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [AV_202t2] The Unstoppable Force - COST:7
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: After you attack a minion,
    //       smash it into the enemy hero!
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [AV_323t] Scrappy Grunt - COST:3 [ATK:2/HP:4]
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("AV_323t", CardDef(power));
}

void AlteracValleyCardsGen::AddDemonHunter(
    std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- MINION - DEMONHUNTER
    // [AV_118] Battleworn Vanguard - COST:2 [ATK:2/HP:2]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: After your hero attacks, summon two 1/1 Felwings.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------- WEAPON - DEMONHUNTER
    // [AV_209] Dreadprison Glaive - COST:1
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Honorable Kill:</b> Deal damage equal to
    //       your hero's Attack to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [AV_261] Flag Runner - COST:3 [ATK:1/HP:6]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever a friendly minion dies, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [AV_262] Warden of Chains - COST:4 [ATK:2/HP:6]
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> If you're holding a Demon that
    //       costs (5) or more, gain +1/+2.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [AV_264] Sigil of Reckoning - COST:5
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: At the start of your next turn,
    //       summon a random Demon from your hand.
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [AV_265] Ur'zul Giant - COST:13 [ATK:8/HP:8]
    // - Race: Demon, Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: Costs (1) less for each friendly minion
    //       that died this game.
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [AV_267] Caria Felsoul - COST:6 [ATK:6/HP:6]
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Transform into a 6/6 copy
    //       of a Demon in your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [AV_269] Flanking Maneuver - COST:4
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon a 4/2 Demon with <b>Rush</b>.
    //       If it dies this turn, summon another.
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [AV_661] Field of Strife - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Your minions have +1 Attack. Lasts 3 turns.
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddDemonHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [AV_204e] Ashfallen's Power - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [AV_204t2] Felbat Shrieker - COST:3 [ATK:1/HP:4]
    // - Race: Demon, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [AV_261e] Team Player - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +1 Attack
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [AV_262e2] Terrifying - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +1/+2.
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [AV_267e2] Demonic - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Attack and Health set to 6.
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [AV_269e] Woe Is Me - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: If this dies summon another.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_SILENCED = 1
    // - ENCHANTMENT_INVISIBLE = 1
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [AV_269t] Snowy Satyr - COST:3 [ATK:4/HP:2]
    // - Race: Demon, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [AV_661e2] Empowered - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +1 Attack from {0}.
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    Power power;

    // --------------------------------------- MINION - NEUTRAL
    // [AV_100] Drek'Thar - COST:4 [ATK:4/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry</b>: If this costs more than
    //       every minion in your deck, summon 2 of them.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_101] Herald of Lokholar - COST:4 [ATK:3/HP:5]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a Frost spell.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DrawSpellTask>(SpellSchool::FROST, 1));
    cards.emplace("AV_101", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [AV_102] Popsicooler - COST:3 [ATK:3/HP:3]
    // - Race: Mechanical, Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> <b>Freeze</b> two random
    //       enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_112] Snowblind Harpy - COST:3 [ATK:3/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Frost spell,
    //       gain 5 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE,
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsHoldingSpell(SpellSchool::FROST)) }));
    power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<ArmorTask>(5) }));
    cards.emplace("AV_112", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [AV_121] Gnome Private - COST:1 [ATK:1/HP:3]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Honorable Kill:</b> Gain +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddHonorableKillTask(
        std::make_shared<AddEnchantmentTask>("AV_121e", EntityType::SOURCE));
    cards.emplace("AV_121", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [AV_122] Corporal - COST:2 [ATK:2/HP:3]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Honorable Kill:</b> Give your other minions
    //       <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddHonorableKillTask(std::make_shared<SetGameTagTask>(
        EntityType::MINIONS_NOSOURCE, GameTag::DIVINE_SHIELD, 1));
    cards.emplace("AV_122", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [AV_123] Sneaky Scout - COST:2 [ATK:3/HP:2]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //       <b>Honorable Kill:</b> Your next Hero Power costs (0).
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // - STEALTH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_124] Direwolf Commander - COST:3 [ATK:2/HP:5]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Honorable Kill:</b> Summon a 2/2 Wolf
    //       with <b>Stealth</b>.
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddHonorableKillTask(
        std::make_shared<SummonTask>("AV_211t", SummonSide::RIGHT));
    cards.emplace("AV_124", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [AV_125] Tower Sergeant - COST:4 [ATK:4/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control at least
    //       2 other minions, gain +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_126] Bunker Sergeant - COST:3 [ATK:2/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your opponent has 2 or
    //       more minions, deal 1 damage to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_127] Ice Revenant - COST:4 [ATK:4/HP:5]
    // - Race: Elemental, Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever you cast a Frost spell, gain +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_128] Frozen Mammoth - COST:4 [ATK:6/HP:7]
    // - Race: Beast, Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: This is <b>Frozen</b> until you cast a Fire spell.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_129] Blood Guard - COST:5 [ATK:4/HP:7]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever this minion takes damage,
    //       give your minions +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_130] Legionnaire - COST:6 [ATK:9/HP:3]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give all minions in your hand +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_131] Knight-Captain - COST:5 [ATK:3/HP:3]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage.
    //       <b>Honorable Kill:</b> Gain +3/+3.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - HONORABLEKILL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_132] Troll Centurion - COST:8 [ATK:8/HP:8]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>. <b>Honorable Kill:</b>
    //       Deal 8 damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_133] Icehoof Protector - COST:6 [ATK:2/HP:10]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Freeze</b> any character damaged by this minion.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_134] Frostwolf Warmaster - COST:4 [ATK:3/HP:3]
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Costs (1) less for each card you've played this turn.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_135] Stormpike Marshal - COST:4 [ATK:2/HP:6]
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       If you took 5 or more damage on your opponent's turn,
    //       this costs (1).
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_136] Kobold Taskmaster - COST:3 [ATK:2/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add 2 Armor Scraps to your hand
    //       that give +2 Health to a minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_137] Irondeep Trogg - COST:1 [ATK:1/HP:2]
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: After your opponent casts a spell,
    //       summon another Irondeep Trogg.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_138] Grimtotem Bounty Hunter - COST:3 [ATK:4/HP:2]
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy an enemy
    //       <b>Legendary</b> minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_139] Abominable Lieutenant - COST:8 [ATK:3/HP:5]
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       eat a random enemy minion and gain its stats.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_141t] Lokholar the Ice Lord - COST:10 [ATK:8/HP:8]
    // - Race: Elemental, Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Rush</b>, <b>Windfury</b>
    //       Costs (5) less if you have 15 Health or less.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - RUSH = 1
    // - WINDFURY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_142t] Ivus, the Forest Lord - COST:1 [ATK:1/HP:1]
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Spend the rest of your Mana
    //       and gain +2/+2, <b>Rush</b>, <b>Divine Shield</b>,
    //       or <b>Taunt</b> at random for each.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // - RUSH = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_143] Korrak the Bloodrager - COST:4 [ATK:3/HP:5]
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> If this
    //       wasn't <b>Honorably Killed</b>,
    //       resummon Korrak.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - HONORABLEKILL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_215] Frantic Hippogryph - COST:5 [ATK:3/HP:7]
    // - Race: Beast, Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>. <b>Honorable Kill</b>:
    //        Gain <b>Windfury</b>.
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // - RUSH = 1
    // --------------------------------------------------------
    // RefTag:
    // - WINDFURY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_219] Ram Commander - COST:2 [ATK:2/HP:2]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add two 1/1 Rams with <b>Rush</b>
    //       to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_222] Spammy Arcanist - COST:5 [ATK:3/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage to all other minions.
    //       If any die, repeat this.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_223] Vanndar Stormpike - COST:4 [ATK:4/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry</b>: If this costs less than
    //       every minion in your deck, reduce their Cost by (3).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_238] Gankster - COST:2 [ATK:4/HP:2]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //       After your opponent plays a minion, attack it.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_256] Reflecto Engineer - COST:3 [ATK:2/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Swap the Attack and Health
    //       of all minions in both players' hands.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_309] Piggyback Imp - COST:3 [ATK:4/HP:1]
    // - Race: Demon, Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 4/1 Imp.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_401] Stormpike Quartermaster - COST:2 [ATK:2/HP:2]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: After you cast a spell,
    //       give a random minion in your hand +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_704] Humongous Owl - COST:7 [ATK:8/HP:4]
    // - Race: Beast, Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 8 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_121e] Gnome's Honor - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("AV_121e"));
    cards.emplace("AV_121e", CardDef(power));

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_123e] Scouted - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Your Hero Power costs (0).
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_125e] Shielded - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_127e] Frosty Spirit - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_128e] Unthawed - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Frozen</b> until you cast a Fire spell.
    // --------------------------------------------------------
    // GameTag:
    // - ENCHANTMENT_INVISIBLE = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_129e] Incited - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_130e] Marching Orders - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_131e] Armed to the Teeth - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +3/+3
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_136e] Rusted Armor - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2 Health.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [AV_136t] Armor Scrap - COST:1
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Give a minion
    //       +2 Health.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_139e] Tummy Feel Funny - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Increased Stats
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_142e] Crystalskin - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_142e2] Uprooted - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Rush</b>.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_142e3] Forestguard - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_142e4] Imposing - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Taunt</b>.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_211t] Frostwolf Cub - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("AV_211t", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [AV_218t] Sheep - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_219t] Battle Ram - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_223e] Occupy the Keep - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (3) less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_256e] Reflected - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Attack and Health have been swapped.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_259e2] Frostbitten - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (2) more.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_284e2] Magical Shift - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Swapped Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_284e3] Magical Shift - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Swapped Heatlh,
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_309t] Backpiggy Imp - COST:3 [ATK:4/HP:1]
    // - Race: Demon, Set: ALTERAC_VALLEY
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_401e] Quartered - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [AV_COIN1] The Coin - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Gain 1 Mana Crystal this turn only.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [AV_COIN2] The Coin - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Gain 1 Mana Crystal this turn only.
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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