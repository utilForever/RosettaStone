// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/CardSets/DalaranCardsGen.hpp>
#include <Rosetta/Tasks/SimpleTasks/HealTask.hpp>

using namespace RosettaStone::SimpleTasks;

namespace RosettaStone
{
void DalaranCardsGen::AddHeroes(PowersType& powers, PlayReqsType& playReqs,
                                EntouragesType& entourages)
{
    (void)powers;
}

void DalaranCardsGen::AddHeroPowers(PowersType& powers, PlayReqsType& playReqs,
                                    EntouragesType& entourages)
{
    (void)powers;
}

void DalaranCardsGen::AddDruid(PowersType& powers, PlayReqsType& playReqs,
                               EntouragesType& entourages)
{
    // ------------------------------------------ SPELL - DRUID
    // [DAL_256] The Forest's Aid - COST:8
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Twinspell</b> Summon five 2/2 Treants.
    // --------------------------------------------------------
    // GameTag:
    // - TWINSPELL_COPY = 52821
    // - TWINSPELL = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [DAL_350] Crystal Power - COST:1
    // - Faction: Neutral, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Deal 2 damage to a minion;
    //       or Restore 5 Health.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [DAL_351] Blessing of the Ancients - COST:3
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Twinspell</b> Give your minions +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - TWINSPELL_COPY = 54128
    // - TWINSPELL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [DAL_352] Crystalsong Portal - COST:2
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Discover</b> a Druid minion.
    //       If your hand has no minions, keep all 3.
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [DAL_354] Acornbearer - COST:1 [ATK:2/HP:1]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add two 1/1 Squirrels to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [DAL_355] Lifeweaver - COST:3 [ATK:2/HP:5]
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you restore Health,
    //       add a random Druid spell to your hand.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [DAL_357] Lucentbark - COST:8 [ATK:4/HP:8]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Go dormant.
    //       Restore 5 Health to awaken this minion.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [DAL_732] Keeper Stalladris - COST:2 [ATK:2/HP:3]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you cast a <b>Choose One</b> spell,
    //       add copies of both choices to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [DAL_733] Dreamway Guardians - COST:2
    // - Faction: Neutral, Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon two 1/2 Dryads with <b>Lifesteal</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [DAL_799] Crystal Stag - COST:5 [ATK:4/HP:4]
    // - Race: Beast, Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Rush</b>. <b>Battlecry:</b> If you've restored
    //       5 Health this game, summon a copy of this.
    //       @ <i>({0} left!)</i>@ <i>(Ready!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - RUSH = 1
    // - PLAYER_TAG_THRESHOLD_TAG_ID = 958
    // - PLAYER_TAG_THRESHOLD_VALUE = 5
    // --------------------------------------------------------
}

void DalaranCardsGen::AddDruidNonCollect(PowersType& powers,
                                         PlayReqsType& playReqs,
                                         EntouragesType& entourages)
{
    // ----------------------------------------- MINION - DRUID
    // [DAL_256t2] Treant (*) - COST:2 [ATK:2/HP:2]
    // - Set: Dalaran
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [DAL_256ts] The Forest's Aid (*) - COST:8
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon five 2/2 Treants.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [DAL_350a] Piercing Thorns (*) - COST:1
    // - Faction: Neutral, Set: Dalaran
    // --------------------------------------------------------
    // Text: Deal 2 damage to a minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [DAL_350b] Healing Blossom (*) - COST:1
    // - Faction: Neutral, Set: Dalaran,
    // --------------------------------------------------------
    // Text: Restore 5 Health.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [DAL_351ts] Blessing of the Ancients (*) - COST:3
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: Give your minions +1/+1.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [DAL_354t] Squirrel (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Dalaran
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [DAL_357t] Spirit of Lucentbark (*) - COST:11 [ATK:0/HP:1]
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: When you restore 5 Health, awaken this minion.
    //       <i>(@ left!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_1 = 5
    // - HIDE_STATS = 1
    // - UNTOUCHABLE = 1
    // - SCORE_VALUE_1 = 5
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [DAL_733t] Crystal Dryad (*) - COST:1 [ATK:1/HP:2]
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
}

void DalaranCardsGen::AddHunter(PowersType& powers, PlayReqsType& playReqs,
                                EntouragesType& entourages)
{
    // ----------------------------------------- SPELL - HUNTER
    // [DAL_371] Marked Shot - COST:4
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 4 damage to a minion. <b>Discover</b> a spell.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [DAL_372] Arcane Fletcher - COST:4 [ATK:3/HP:3]
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: Whenever you play a 1-Cost minion,
    //       draw a spell from your deck.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [DAL_373] Rapid Fire - COST:1
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Twinspell</b> Deal 1 damage.
    // --------------------------------------------------------
    // GameTag:
    // - TWINSPELL_COPY = 54143
    // - TWINSPELL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [DAL_376] Oblivitron - COST:6 [ATK:3/HP:4]
    // - Race: Mechanical, Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a Mech from your hand
    //       and trigger its <b>Deathrattle</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [DAL_377] Nine Lives - COST:3
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Discover</b> a friendly <b>Deathrattle</b> minion that
    //       died this game. Also trigger its <b>Deathrattle</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_FRIENDLY_DEATHRATTLE_MINION_DIED_THIS_GAME = 0
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [DAL_378] Unleash the Beast - COST:6
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Twinspell</b> Summon a 5/5 Wyvern with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TWINSPELL_COPY = 54145
    // - TWINSPELL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [DAL_379] Vereesa Windrunner - COST:7 [ATK:5/HP:6]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Equip Thori'dal, the Stars' Fury.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [DAL_587] Shimmerfly - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Dalaran, Rarity: rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a random Hunter spell to your hand.
    // --------------------------------------------------------
    // Entourage: NEW1_032, NEW1_033, NEW1_034
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [DAL_589] Hunting Party - COST:5
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Copy all Beasts in your hand.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [DAL_604] Ursatron - COST:3 [ATK:3/HP:3]
    // - Race: Mechanical, Faction: Neutral, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Draw a Mech from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
}

void DalaranCardsGen::AddHunterNonCollect(PowersType& powers,
                                          PlayReqsType& playReqs,
                                          EntouragesType& entourages)
{
    // ----------------------------------------- SPELL - HUNTER
    // [DAL_373ts] Rapid Fire (*) - COST:1
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 1 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [DAL_378t1] Wyvern (*) - COST:5 [ATK:5/HP:5]
    // - Race: Beast, Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [DAL_378ts] Unleash the Beast (*) - COST:6
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon a 5/5 Wyvern with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - HIDE_ATTACK = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [DAL_379e] Stars' Fury (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: You have <b>Spell Damage +2</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - HUNTER
    // [DAL_379t] Thori'dal, the Stars' Fury (*) - COST:3 [ATK:2/HP:0]
    // - Set: Dalaran,
    // --------------------------------------------------------
    // Text: After your hero attacks, gain <b>Spell Damage +2</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DURABILITY = 3
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
}

void DalaranCardsGen::AddMage(PowersType& powers, PlayReqsType& playReqs,
                              EntouragesType& entourages)
{
    // ------------------------------------------ MINION - MAGE
    // [DAL_163] Messenger Raven - COST:3 [ATK:3/HP:2]
    // - Race: Beast, Faction: Neutral, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a Mage minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [DAL_177] Conjurer's Calling - COST:3
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Twinspell</b> Destroy a minion.
    //       Summon 2 minions of the same Cost to replace it.
    // --------------------------------------------------------
    // GameTag:
    // - TWINSPELL_COPY = 52637
    // - TWINSPELL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [DAL_182] Magic Dart Frog - COST:2 [ATK:1/HP:3]
    // - Race: Beast, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: After you cast a spell, deal 1 damage to a random enemy minion.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [DAL_575] Khadgar - COST:2 [ATK:2/HP:2]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Your cards that summon minions summon twice as many.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [DAL_576] Kirin Tor Tricaster - COST:4 [ATK:3/HP:3]
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Spell Damage +3</b> Your spells cost (1) more.
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 3
    // - AURA = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [DAL_577] Ray of Frost - COST:1
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Twinspell</b> <b>Freeze</b> a minion.
    //       If it's already <b>Frozen</b>, deal 2 damage to it.
    // --------------------------------------------------------
    // GameTag:
    // - TWINSPELL_COPY = 54193
    // - TWINSPELL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [DAL_578] Power of Creation - COST:8
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Discover</b> a 6-Cost minion. Summon two copies of it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [DAL_603] Mana Cyclone - COST:2 [ATK:2/HP:2]
    // - Race: Elemental, Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> For each spell you've cast this turn,
    //       add a random Mage spell to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [DAL_608] Magic Trick - COST:1
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Discover</b> a spell that costs (3) or less.
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [DAL_609] Kalecgos - COST:10 [ATK:4/HP:12]
    // - Race: Dragon, Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Your first spell each turn costs (0).
    //       <b>Battlecry:</b> <b>Discover</b> a spell.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - AURA = 1
    // - DISCOVER = 1
    // --------------------------------------------------------
}

void DalaranCardsGen::AddMageNonCollect(PowersType& powers,
                                        PlayReqsType& playReqs,
                                        EntouragesType& entourages)
{
    // ------------------------------------------- SPELL - MAGE
    // [DAL_177ts] Conjurer's Calling (*) - COST:3
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Destroy a minion. Summon 2 minions of the same Cost to replace it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [DAL_577ts] Ray of Frost (*) - COST:1
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Freeze</b> a minion.
    //       If it's already <b>Frozen</b>, deal 2 damage to it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------
}

void DalaranCardsGen::AddPaladin(PowersType& powers, PlayReqsType& playReqs,
                                 EntouragesType& entourages)
{
    // ---------------------------------------- SPELL - PALADIN
    // [DAL_141] Desperate Measures - COST:1
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Twinspell</b> Cast a random Paladin <b>Secret</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TWINSPELL_COPY = 54129
    // - TWINSPELL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_SECRET_ZONE_CAP_FOR_NON_SECRET = 0
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [DAL_146] Bronze Herald - COST:3 [ATK:3/HP:2]
    // - Race: Dragon, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add two 4/4 Dragons to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [DAL_147] Dragon Speaker - COST:5 [ATK:3/HP:5]
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give all Dragons in your hand +3/+3.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [DAL_568] Lightforged Blessing - COST:2
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Twinspell</b> Give a friendly minion <b>Lifesteal</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TWINSPELL_COPY = 54189
    // - TWINSPELL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [DAL_570] Never Surrender! - COST:1
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your opponent casts a spell,
    //       give your minions +2 Health.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - PALADIN
    // [DAL_571] Mysterious Blade - COST:2 [ATK:2/HP:0]
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a
    //       <b>Secret</b>, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [DAL_573] Commander Rhyssa - COST:3 [ATK:4/HP:3]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Your <b>Secrets</b> trigger twice.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [DAL_581] Nozari - COST:10 [ATK:4/HP:12]
    // - Race: Dragon, Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore both heroes to full Health.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - AFFECTED_BY_HEALING_DOES_DAMAGE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [DAL_727] Call to Adventure - COST:3
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Draw the lowest Cost minion from your deck. Give it +2/+2.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [DAL_731] Duel! - COST:5
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: Summon a minion from each player's deck. They fight!
    // --------------------------------------------------------
}

void DalaranCardsGen::AddPaladinNonCollect(PowersType& powers,
                                           PlayReqsType& playReqs,
                                           EntouragesType& entourages)
{
    // ---------------------------------------- SPELL - PALADIN
    // [DAL_141ts] Desperate Measures (*) - COST:1
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Cast a random Paladin <b>Secret</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_SECRET_ZONE_CAP_FOR_NON_SECRET = 0
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [DAL_146t] Bronze Dragon (*) - COST:4 [ATK:4/HP:4]
    // - Race: Dragon, Set: Dalaran
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [DAL_568e] Lightforged Blessing (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [DAL_568ts] Lightforged Blessing (*) - COST:2
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a friendly minion <b>Lifesteal</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [DAL_571e] Mysterious (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------
}

void DalaranCardsGen::AddPriest(PowersType& powers, PlayReqsType& playReqs,
                                EntouragesType& entourages)
{
    // ----------------------------------------- SPELL - PRIEST
    // [DAL_011] Lazul's Scheme - COST:0
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: Reduce the Attack of an enemy minion by
    //       @ until your next turn. <i>(Upgrades each turn!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_1 = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [DAL_030] Shadowy Figure - COST:2 [ATK:2/HP:2]
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Transform into a 2/2 copy of
    //       a friendly <b>Deathrattle</b> minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_TARGET_WITH_DEATHRATTLE = 0
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [DAL_039] Convincing Infiltrator - COST:5 [ATK:2/HP:6]
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Destroy a random enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [DAL_040] Hench-Clan Shadequill - COST:4 [ATK:4/HP:7]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Restore 5 Health to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - AFFECTED_BY_HEALING_DOES_DAMAGE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [DAL_065] Unsleeping Soul - COST:4
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Silence</b> a friendly minion, then summon a copy of it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - SILENCE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [DAL_413] EVIL Conscripter - COST:2 [ATK:2/HP:2]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a <b>Lackey</b> to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [DAL_721] Catrina Muerte - COST:8 [ATK:6/HP:8]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of your turn, summon a friendly minion
    //       that died this game.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [DAL_723] Forbidden Words - COST:0
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Spend all your Mana. Destroy a minion with that
    //       much Attack or less.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ85 = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [DAL_724] Mass Resurrection - COST:9
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon 3 friendly minions that died this game.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // - REQ_FRIENDLY_MINION_DIED_THIS_GAME = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [DAL_729] Madame Lazul - COST:3 [ATK:3/HP:2]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a
    //       copy of a card in your opponent's hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
}

void DalaranCardsGen::AddPriestNonCollect(PowersType& powers,
                                          PlayReqsType& playReqs,
                                          EntouragesType& entourages)
{
    // ----------------------------------- ENCHANTMENT - PRIEST
    // [DAL_030e] Shade (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: 2/2.
    // --------------------------------------------------------
}

void DalaranCardsGen::AddRogue(PowersType& powers, PlayReqsType& playReqs,
                               EntouragesType& entourages)
{
    // ------------------------------------------ SPELL - ROGUE
    // [DAL_010] Togwaggle's Scheme - COST:1
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Choose a minion. Shuffle @ (copy, copies) of it into your deck.
    //       <i>(Upgrades each turn!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_1 = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [DAL_366] Unidentified Contract - COST:6
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy a minion. Gains a bonus effect in your hand.
    // --------------------------------------------------------
    // Entourage: DAL_366t1, DAL_366t2, DAL_366t3, DAL_366t4
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [DAL_415] EVIL Miscreant - COST:3 [ATK:1/HP:5]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Add two random <b>Lackeys</b> to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [DAL_416] Hench-Clan Burglar - COST:4 [ATK:4/HP:3]
    // - Race: Pirate, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a spell from another class.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [DAL_417] Heistbaron Togwaggle - COST:6 [ATK:5/HP:5]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a_<b>Lackey</b>,
    //       choose a fantastic treasure.
    // --------------------------------------------------------
    // Entourage: LOOT_998h, LOOT_998j, LOOT_998l, LOOT_998k
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - MULTIPLY_BUFF_VALUE = 1
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [DAL_714] Underbelly Fence - COST:2 [ATK:2/HP:3]
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a card from
    //       another class, gain +1/+1 and <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [DAL_716] Vendetta - COST:4
    // - Faction: Neutral, Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 4 damage to a minion. Costs (0) if you're
    //       holding a card from another class.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [DAL_719] Tak Nozwhisker - COST:7 [ATK:6/HP:6]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever you shuffle a card into your deck,
    //       add a copy to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ----------------------------------------- WEAPON - ROGUE
    // [DAL_720] Waggle Pick - COST:4 [ATK:4/HP:0]
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Return a random friendly
    //       minion to your hand. It costs (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [DAL_728] Daring Escape - COST:1
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: Return all friendly minions to your hand.
    // --------------------------------------------------------
}

void DalaranCardsGen::AddRogueNonCollect(PowersType& powers,
                                         PlayReqsType& playReqs,
                                         EntouragesType& entourages)
{
    // ------------------------------------------ SPELL - ROGUE
    // [DAL_366t1] Assassin's Contract (*) - COST:6
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy a minion. Summon a 1/1 Patient Assassin.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [DAL_366t2] Recruitment Contract (*) - COST:6
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy a minion. Add a copy of it to your hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [DAL_366t3] Lucrative Contract (*) - COST:6
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy a minion. Add 2 Coins to your hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [DAL_366t4] Turncoat Contract (*) - COST:6
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy a minion. It deals its damage to adjacent minions.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
}

void DalaranCardsGen::AddShaman(PowersType& powers, PlayReqsType& playReqs,
                                EntouragesType& entourages)
{
    // ----------------------------------------- SPELL - SHAMAN
    // [DAL_009] Hagatha's Scheme - COST:5
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal @ damage to all minions.
    //       <i>(Upgrades each turn!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_1 = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [DAL_047] Walking Fountain - COST:8 [ATK:4/HP:8]
    // - Race: Elemental, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>, <b>Rush</b>, <b>Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - WINDFURY = 1
    // - LIFESTEAL = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [DAL_049] Underbelly Angler - COST:2 [ATK:2/HP:3]
    // - Race: Murloc, Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you play a Murloc, add a random Murloc to your hand.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [DAL_052] Muckmorpher - COST:5 [ATK:4/HP:4]
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Transform into a 4/4 copy of
    //       a different minion in your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [DAL_071] Mutate - COST:0
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: Transform a friendly minion into a random one
    //       that costs (1) more.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [DAL_431] Swampqueen Hagatha - COST:7 [ATK:5/HP:5]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a 5/5 Horror to your hand.
    //       Teach it two Shaman spells.
    // --------------------------------------------------------
    // Entourage: DAL_431t
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [DAL_432] Witch's Brew - COST:2
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: Restore 4 Health. Repeatable this turn.
    // --------------------------------------------------------
    // GameTag:
    // - NON_KEYWORD_ECHO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [DAL_433] Sludge Slurper - COST:1 [ATK:2/HP:1]
    // - Race: Murloc, Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a <b>Lackey</b> to your hand.
    //       <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [DAL_710] Soul of the Murloc - COST:2
    // - Faction: Neutral, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: Give your minions "<b>Deathrattle:</b> Summon a 1/1 Murloc."
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [DAL_726] Scargil - COST:4 [ATK:4/HP:4]
    // - Race: Murloc, Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Your Murlocs cost (1).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AURA = 1
    // --------------------------------------------------------
}

void DalaranCardsGen::AddShamanNonCollect(PowersType& powers,
                                          PlayReqsType& playReqs,
                                          EntouragesType& entourages)
{
    // ---------------------------------------- MINION - SHAMAN
    // [DAL_431t] Drustvar Horror (*) - COST:5 [ATK:5/HP:5]
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Cast {0} and {1}.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [DAL_710e] Soul of the Murloc (*) - COST:0
    // - Faction: Neutral, Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 1/1 Murloc.
    // --------------------------------------------------------
}

void DalaranCardsGen::AddWarlock(PowersType& powers, PlayReqsType& playReqs,
                                 EntouragesType& entourages)
{
    // ---------------------------------------- SPELL - WARLOCK
    // [DAL_007] Rafaam's Scheme - COST:3
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: Summon @ 1/1 (Imp, Imps). <i>(Upgrades each turn!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_1 = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [DAL_173] Darkest Hour - COST:6
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy all friendly minions.
    //       For each one, summon a random minion from your deck.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [DAL_185] Aranasi Broodmother - COST:6 [ATK:4/HP:6]
    // - Race: Demon, Faction: Neutral, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b> When you draw this,
    //       restore 4 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - TOPDECK = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [DAL_422] Arch-Villain Rafaam - COST:7 [ATK:7/HP:8]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Taunt</b> <b>Battlecry:</b> Replace your hand
    //       and deck with <b>Legendary</b> minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [DAL_561] Jumbo Imp - COST:10 [ATK:8/HP:8]
    // - Race: Demon, Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: Costs (1) less whenever a friendly Demon dies
    //       while this is in your hand.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [DAL_563] Eager Underling - COST:4 [ATK:2/HP:2]
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give two random friendly minions +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [DAL_602] Plot Twist - COST:2
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Shuffle your hand into your deck. Draw that many cards.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [DAL_605] Impferno - COST:3
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give your Demons +1 Attack.
    //       Deal 1 damage to all enemy minions.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_WITH_RACE = 15
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [DAL_606] EVIL Genius - COST:2 [ATK:2/HP:2]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a friendly minion
    //       to add 2 random <b>Lackeys</b> to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [DAL_607] Fel Lord Betrug - COST:8 [ATK:5/HP:7]
    // - Race: Demon, Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever you draw a minion, summon a copy
    //       with <b>Rush</b> that dies at end of turn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
}

void DalaranCardsGen::AddWarlockNonCollect(PowersType& powers,
                                           PlayReqsType& playReqs,
                                           EntouragesType& entourages)
{
    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [DAL_605e] Imptastic (*) - COST:2
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------
}

void DalaranCardsGen::AddWarrior(PowersType& powers, PlayReqsType& playReqs,
                                 EntouragesType& entourages)
{
    // ---------------------------------------- SPELL - WARRIOR
    // [DAL_008] Dr. Boom's Scheme - COST:4
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: Gain @ Armor. <i>(Upgrades each turn!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_1 = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [DAL_059] Dimensional Ripper - COST:10
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon 2 copies of a minion in your deck.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [DAL_060] Clockwork Goblin - COST:3 [ATK:3/HP:3]
    // - Race: Mechanical, Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Shuffle a Bomb into your opponent's deck.
    //       When drawn, it explodes for 5 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [DAL_062] Sweeping Strikes - COST:2
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give a minion "Also damages minions next to whomever this attacks."
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [DAL_063] Wrenchcalibur - COST:4 [ATK:3/HP:0]
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: After your hero attacks, shuffle a Bomb
    //       into your opponent's deck.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [DAL_064] Blastmaster Boom - COST:7 [ATK:7/HP:7]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two 1/1 Boom Bots
    //       for each Bomb in your opponent's deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [DAL_070] The Boom Reaver - COST:10 [ATK:7/HP:9]
    // - Race: Mechanical, Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a copy of a minion in your deck.
    //       Give it <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [DAL_759] Vicious Scraphound - COST:2 [ATK:2/HP:2]
    // - Race: Mechanical, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever this minion deals damage, gain that much Armor.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [DAL_769] Improve Morale - COST:1
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 1 damage to a minion.
    //       If it survives, add a <b>Lackey</b> to your hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [DAL_770] Omega Devastator - COST:4 [ATK:4/HP:5]
    // - Race: Mechanical, Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you have 10 Mana Crystals,
    //       deal 10 damage to a minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_MANA_CRYSTAL = 10
    // --------------------------------------------------------
}

void DalaranCardsGen::AddWarriorNonCollect(PowersType& powers,
                                           PlayReqsType& playReqs,
                                           EntouragesType& entourages)
{
    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [DAL_062e] Sweeping Strikes (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: Damages minions adjacent to defender.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [DAL_070e] Reaving (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: Has <b>Rush</b>.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [DAL_742e] Whirling (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Mega-Windfury</b>
    // --------------------------------------------------------
}

void DalaranCardsGen::AddNeutral(PowersType& powers, PlayReqsType& playReqs,
                                 EntouragesType& entourages)
{
    Power power;

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_058] Hecklebot - COST:4 [ATK:3/HP:8]
    // - Race: Mechanical, Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b> <b>Battlecry:</b> Your opponent
    //       summons a minion from their deck.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_077] Toxfin - COST:1 [ATK:1/HP:2]
    // - Race: Murloc, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly Murloc <b>Poisonous</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_TARGET_WITH_RACE = 14
    // --------------------------------------------------------
    // RefTag:
    // - POISONOUS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_078] Traveling Healer - COST:4 [ATK:3/HP:2]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b> <b>Battlecry:</b> Restore 3 Health.
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new HealTask(EntityType::TARGET, 3));
    powers.emplace("DAL_078", power);
    playReqs.emplace("DAL_078",
                     PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } });

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_081] Spellward Jeweler - COST:3 [ATK:3/HP:4]
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your hero can't be targeted by
    //       spells or Hero Powers until your next turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_085] Dalaran Crusader - COST:5 [ATK:5/HP:4]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_086] Sunreaver Spy - COST:2 [ATK:2/HP:3]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a <b>Secret</b>, gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_087] Hench-Clan Hag - COST:4 [ATK:3/HP:3]
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two 1/1 Amalgams
    //       with all minion types.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_088] Safeguard - COST:6 [ATK:4/HP:5]
    // - Race: Mechanical, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b> <b>Deathrattle:</b> Summon a 0/5
    //       Vault Safe with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_089] Spellbook Binder - COST:2 [ATK:3/HP:2]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you have <b>Spell Damage</b>,
    //       draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_090] Hench-Clan Sneak - COST:3 [ATK:3/HP:3]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_092] Arcane Servant - COST:2 [ATK:2/HP:3]
    // - Race: Elemental, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_095] Violet Spellsword - COST:4 [ATK:1/HP:6]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain +1 Attack
    //       for each spell in your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_096] Violet Warden - COST:6 [ATK:4/HP:7]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b> <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_400] EVIL Cable Rat - COST:2 [ATK:1/HP:1]
    // - Race: Beast, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a <b>Lackey</b> to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_434] Arcane Watcher - COST:3 [ATK:5/HP:6]
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Can't attack unless you have <b>Spell Damage</b>.
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_538] Unseen Saboteur - COST:6 [ATK:5/HP:6]
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your opponent casts a random spell
    //       from their hand <i>(targets chosen randomly)</i>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_539] Sunreaver Warmage - COST:5 [ATK:4/HP:4]
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a spell that
    //       costs (5) or more, deal 4 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_DRAG_TO_PLAY = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_544] Potion Vendor - COST:1 [ATK:1/HP:1]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 2 Health to all friendly characters.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_546] Barista Lynchen - COST:5 [ATK:4/HP:5]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a copy of each of your other
    //       <b>Battlecry</b> minions to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_548] Azerite Elemental - COST:5 [ATK:2/HP:7]
    // - Race: Elemental, Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: At the start of your turn, gain <b>Spell Damage +2</b>.
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_550] Underbelly Ooze - COST:7 [ATK:3/HP:5]
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: After this minion survives damage, summon a copy of it.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_551] Proud Defender - COST:4 [ATK:2/HP:6]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       Has +2 Attack while you have no other minions.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_553] Big Bad Archmage - COST:10 [ATK:6/HP:6]
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: At the end of your turn, summon a random
    //       6-Cost minion.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_554] Chef Nomi - COST:7 [ATK:6/HP:6]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck is empty,
    //       summon six 6/6 Greasefire Elementals.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_558] Archmage Vargoth - COST:4 [ATK:2/HP:6]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of your turn, cast a spell
    //       you've cast this turn <i>(targets are random)</i>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_560] Heroic Innkeeper - COST:8 [ATK:4/HP:4]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt.</b> <b>Battlecry:</b> Gain +2/+2
    //       for each other friendly minion.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_565] Portal Overfiend - COST:6 [ATK:5/HP:6]
    // - Race: Demon, Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Shuffle 3 Portals into your deck.
    //       When drawn, summon a 2/2 Demon with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_566] Eccentric Scribe - COST:6 [ATK:6/HP:4]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon four 1/1 Vengeful Scrolls.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_582] Portal Keeper - COST:4 [ATK:5/HP:2]
    // - Race: Demon, Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Shuffle 3 Portals into your deck.
    //       When drawn, summon a 2/2 Demon with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_592] Batterhead - COST:8 [ATK:3/HP:12]
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Rush</b>. After this attacks and kills a minion,
    //       it may attack again.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_735] Dalaran Librarian - COST:2 [ATK:2/HP:3]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Silence</b> adjacent minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SILENCE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_736] Archivist Elysiana - COST:8 [ATK:7/HP:7]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> 5 cards.
    //       Replace your deck with 2 copies of each.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_742] Whirlwind Tempest - COST:8 [ATK:6/HP:6]
    // - Race: Elemental, Faction: Neutral, Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: Your minions with <b>Windfury</b> have <b>Mega-Windfury</b>.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - WINDFURY = 1
    // - MEGA_WINDFURY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_743] Hench-Clan Hogsteed - COST:2 [ATK:2/HP:1]
    // - Race: Beast, Faction: Neutral, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b> <b>Deathrattle:</b> Summon a 1/1 Murloc.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_744] Faceless Rager - COST:3 [ATK:5/HP:1]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Copy a friendly minion's Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_747] Flight Master - COST:3 [ATK:3/HP:4]
    // - Faction: Alliance, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 2/2 Gryphon for each player.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_748] Mana Reservoir - COST:2 [ATK:0/HP:6]
    // - Race: Elemental, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_749] Recurring Villain - COST:5 [ATK:3/HP:6]
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> If this minion has 4 or more Attack,
    //       resummon it.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_751] Mad Summoner - COST:6 [ATK:4/HP:4]
    // - Race: Demon, Faction: Alliance, Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Fill each player's board with 1/1 Imps.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_752] Jepetto Joybuzz - COST:8 [ATK:6/HP:6]
    // - Set: Dalaran, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw 2 minions from your deck.
    //       Set their Attack, Health, and Cost to 1.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_760] Burly Shovelfist - COST:9 [ATK:9/HP:9]
    // - Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_771] Soldier of Fortune - COST:4 [ATK:5/HP:6]
    // - Race: Elemental, Set: Dalaran, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever this minion attacks, give your opponent a Coin.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_773] Magic Carpet - COST:3 [ATK:1/HP:6]
    // - Set: Dalaran, Rarity: Epic
    // --------------------------------------------------------
    // Text: After you play a 1-Cost minion,
    //       give it +1 Attack and <b>Rush</b>.
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_774] Exotic Mountseller - COST:7 [ATK:5/HP:8]
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you cast a spell, summon a random 3-Cost Beast.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_775] Tunnel Blaster - COST:7 [ATK:3/HP:7]
    // - Set: Dalaran, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b> <b>Deathrattle:</b> Deal 3 damage
    //       to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
}

void DalaranCardsGen::AddNeutralNonCollect(PowersType& powers,
                                           PlayReqsType& playReqs,
                                           EntouragesType& entourages)
{
    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_011e] Lazul's Curse (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: Reduced Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_052e] Muckmorphing (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: 4/4.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_077e] Toxic Fin (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_081e] Sparkly (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_086e] Stolen Secrets (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: +1/+1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_087t] Amalgam (*) - COST:1 [ATK:1/HP:1]
    // - Race: All, Set: Dalaran
    // --------------------------------------------------------
    // Text: <i>This is an Elemental, Mech, Demon, Murloc, Dragon,
    //       Beast, Pirate and Totem.</i>
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_088t2] Vault Safe (*) - COST:2 [ATK:0/HP:5]
    // - Race: Mechanical, Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_095e] Pizzazz (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_147e] Dragon Shout (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: +3/+3.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_351e] Ancient Blessings (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_548e] Arcane Expansion (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: Increased <b>Spell Damage</b>.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_554t] Greasefire Elemental (*) - COST:6 [ATK:6/HP:6]
    // - Race: Elemental, Faction: Neutral, Set: Dalaran
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_566t] Vengeful Scroll (*) - COST:1 [ATK:1/HP:1]
    // - Set: Dalaran
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_560e2] Protect the Brews! (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_561e] Imp-onomical (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_563e] Power of EVIL (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_570e] Never Surrender! (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: +2 Health.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_576e] Kirin Tor's Curse (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: Costs (1) more.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [DAL_582t] Felhound Portal (*) - COST:2
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Casts When Drawn</b>
    //       Summon a 2/2 Felhound with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TOPDECK = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // - CASTSWHENDRAWN = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_582t2] Felhound (*) - COST:2 [ATK:2/HP:2]
    // - Race: Demon, Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_589e] Hunting Party (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: +3/+3.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_607e] Fleeting Fel (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Rush</b>. Dies at end of turn.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_613] Faceless Lackey (*) - COST:1 [ATK:1/HP:1]
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a random 2-Cost minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_614] Kobold Lackey (*) - COST:1 [ATK:1/HP:1]
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 2 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_615] Witchy Lackey (*) - COST:1 [ATK:1/HP:1]
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Transform a friendly minion into one
    //       that costs (1) more.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_714e] Street Smarts (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_726e] Scargil's Blessing (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: Costs (1).
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_727e] Heroic (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_739] Goblin Lackey (*) - COST:1 [ATK:1/HP:1]
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion +1 Attack
    //       and <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_739e] Short Fuse (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: +1 Attack and <b>Rush</b>.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_741] Ethereal Lackey (*) - COST:1 [ATK:1/HP:1]
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a spell.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_743t] Hench-Clan Squire (*) - COST:1 [ATK:1/HP:1]
    // - Race: Murloc, Set: Dalaran
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_744e] Familiar Faces (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: Copied health.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_747t] Gryphon (*) - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Faction: Alliance, Set: Dalaran
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DAL_751t] Imp (*) - COST:1 [ATK:1/HP:1]
    // - Race: Demon, Faction: Neutral, Set: Dalaran
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_752e] Toy-sized (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: Jepetto Joybuzz made this 1/1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_752e2] On Sale (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: Costs (1).
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DAL_773e] Flying High (*) - COST:0
    // - Set: Dalaran
    // --------------------------------------------------------
    // Text: +1 Attack and <b>Rush</b>.
    // --------------------------------------------------------
}

void DalaranCardsGen::AddAll(PowersType& powers, PlayReqsType& playReqs,
                             EntouragesType& entourages)
{
    AddHeroes(powers, playReqs, entourages);
    AddHeroPowers(powers, playReqs, entourages);

    AddDruid(powers, playReqs, entourages);
    AddDruidNonCollect(powers, playReqs, entourages);

    AddHunter(powers, playReqs, entourages);
    AddHunterNonCollect(powers, playReqs, entourages);

    AddMage(powers, playReqs, entourages);
    AddMageNonCollect(powers, playReqs, entourages);

    AddPaladin(powers, playReqs, entourages);
    AddPaladinNonCollect(powers, playReqs, entourages);

    AddPriest(powers, playReqs, entourages);
    AddPriestNonCollect(powers, playReqs, entourages);

    AddRogue(powers, playReqs, entourages);
    AddRogueNonCollect(powers, playReqs, entourages);

    AddShaman(powers, playReqs, entourages);
    AddShamanNonCollect(powers, playReqs, entourages);

    AddWarlock(powers, playReqs, entourages);
    AddWarlockNonCollect(powers, playReqs, entourages);

    AddWarrior(powers, playReqs, entourages);
    AddWarriorNonCollect(powers, playReqs, entourages);

    AddNeutral(powers, playReqs, entourages);
    AddNeutralNonCollect(powers, playReqs, entourages);
}
}  // namespace RosettaStone
