// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/YoDCardsGen.hpp>

namespace RosettaStone::PlayMode
{
void YoDCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // -------------------------------------------- HERO - MAGE
    // [YOD_009] The Amazing Reno - COST:10 [ATK:0/HP:30]
    // - Faction: Neutral, Set: YoD, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Make all minions disappear.
    //       <i>*Poof!*</i>
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - HERO_POWER = 56075
    // --------------------------------------------------------
}

void YoDCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    // -------------------------------------- HERO_POWER - MAGE
    // [YOD_009h] What Does This Do? (*) - COST:0
    // - Faction: Neutral, Set: YoD
    // --------------------------------------------------------
    // Text: <b>Passive Hero Power</b> At the start of your turn,
    //       cast a random spell.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
}

void YoDCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ SPELL - DRUID
    // [YOD_001] Rising Winds - COST:2
    // - Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Twinspell</b> <b>Choose One -</b>
    //       Draw a card; or Summon a 3/2 Eagle.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // - TWINSPELL_COPY = 56141
    // - TWINSPELL = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [YOD_003] Winged Guardian - COST:7 [ATK:6/HP:8]
    // - Race: Beast, Set: YoD, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>, <b>Reborn</b>
    //       Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // - REBORN = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [YOD_040] Steel Beetle - COST:2 [ATK:2/HP:3]
    // - Race: Beast, Set: YoD, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a spell that
    //       costs (5) or more, gain 5 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void YoDCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ SPELL - DRUID
    // [YOD_001b] Take Flight (*) - COST:2
    // - Faction: Neutral, Set: YoD
    // --------------------------------------------------------
    // Text: Draw a card.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [YOD_001c] Swoop In (*) - COST:2
    // - Faction: Neutral, Set: YoD
    // --------------------------------------------------------
    // Text: Summon a 3/2 Eagle.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [YOD_001t] Eagle (*) - COST:2 [ATK:3/HP:2]
    // - Race: Beast, Set: YoD
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [YOD_001ts] Rising Winds (*) - COST:2
    // - Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Choose One -</b>
    //       Draw a card; or Summon a 3/2 Eagle.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
}

void YoDCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- MINION - HUNTER
    // [YOD_004] Chopshop Copter - COST:3 [ATK:2/HP:4]
    // - Race: Mechanical, Set: YoD, Rarity: Rare
    // --------------------------------------------------------
    // Text: After a friendly Mech dies,
    //       add a random Mech to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [YOD_005] Fresh Scent - COST:2
    // - Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Twinspell</b> Give a Beast +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - TWINSPELL_COPY = 56142
    // - TWINSPELL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_TARGET_WITH_RACE = 20
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [YOD_036] Rotnest Drake - COST:5 [ATK:6/HP:5]
    // - Race: Dragon, Set: YoD, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       destroy a random enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void YoDCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- ENCHANTMENT - HUNTER
    // [YOD_005e] Fresh Scent (*) - COST:0
    // - Set: YoD
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [YOD_005ts] Fresh Scent (*) - COST:2
    // - Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a Beast +2/+2.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_TARGET_WITH_RACE = 20
    // --------------------------------------------------------
}

void YoDCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ MINION - MAGE
    // [YOD_007] Animated Avalanche - COST:7 [ATK:7/HP:6]
    // - Race: Elemental, Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you played an Elemental
    //       last turn, summon a copy of this.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [YOD_008] Arcane Amplifier - COST:3 [ATK:2/HP:5]
    // - Race: Elemental, Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: Your Hero Power deals 2 extra damage.
    // --------------------------------------------------------
    // GameTag:
    // - HEROPOWER_DAMAGE = 1
    // --------------------------------------------------------
}

void YoDCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
}

void YoDCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - PALADIN
    // [YOD_010] Shotbot - COST:2 [ATK:2/HP:2]
    // - Race: Mechanical, Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Reborn</b>
    // --------------------------------------------------------
    // GameTag:
    // - REBORN = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [YOD_012] Air Raid - COST:2
    // - Set: YoD, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Twinspell</b>
    //       Summon two 1/1 Silver Hand Recruits with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TWINSPELL_COPY = 56144
    // - TWINSPELL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [YOD_043] Scalelord - COST:5 [ATK:5/HP:6]
    // - Race: Dragon, Set: YoD, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your Murlocs <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
}

void YoDCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- SPELL - PALADIN
    // [YOD_012ts] Air Raid (*) - COST:2
    // - Set: YoD, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon two 1/1 Silver Hand Recruits with <b>Taunt</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
}

void YoDCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- MINION - PRIEST
    // [YOD_013] Cleric of Scales - COST:1 [ATK:1/HP:1]
    // - Set: YoD, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       <b>Discover</b> a spell from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [YOD_014] Aeon Reaver - COST:6 [ATK:4/HP:4]
    // - Race: Dragon, Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal damage to a minion equal
    //       to its Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [YOD_015] Dark Prophecy - COST:3
    // - Set: YoD, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Discover</b> a 2 Cost minion.
    //       Summon it and give it +3 Health.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
}

void YoDCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- ENCHANTMENT - PRIEST
    // [YOD_015e] Prophecized (*) - COST:0
    // - Set: YoD
    // --------------------------------------------------------
    // Text: +3 Health.
    // --------------------------------------------------------
}

void YoDCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- MINION - ROGUE
    // [YOD_016] Skyvateer - COST:2 [ATK:1/HP:3]
    // - Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b> <b>Deathrattle:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [YOD_017] Shadow Sculptor - COST:5 [ATK:3/HP:2]
    // - Faction: Horde, Set: YoD, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Draw a card for each card
    //       you've played this turn.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [YOD_018] Waxmancy - COST:3
    // - Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Discover</b> a <b>Battlecry</b> minion.
    //       Reduce its Cost by (2).
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    // PlayReq:
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void YoDCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------ ENCHANTMENT - ROGUE
    // [YOD_018e] Forged in Wax (*) - COST:0
    // - Set: YoD
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------
}

void YoDCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- SPELL - SHAMAN
    // [YOD_020] Explosive Evolution - COST:2
    // - Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: Transform a minion into a random one that costs (3) more.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [YOD_041] Eye of the Storm - COST:10
    // - Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: Summon three 5/6 Elementals with <b>Taunt</b>.
    //       <b>Overload:</b> (3)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 3
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - SHAMAN
    // [YOD_042] The Fist of Ra-den - COST:4 [ATK:1/HP:0]
    // - Set: YoD, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you cast a spell, summon a <b>Legendary</b>
    //       minion of that Cost. Lose 1 Durability.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 4
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
}

void YoDCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- MINION - SHAMAN
    // [YOD_041t] Stormblocker (*) - COST:5 [ATK:5/HP:6]
    // - Race: Elemental, Set: YoD
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
}

void YoDCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- SPELL - WARLOCK
    // [YOD_025] Twisted Knowledge - COST:2
    // - Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Discover</b> 2 Warlock cards.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [YOD_026] Fiendish Servant - COST:1 [ATK:2/HP:1]
    // - Race: Demon, Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give this minion's Attack
    //       to a random friendly minion.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [YOD_027] Chaos Gazer - COST:3 [ATK:4/HP:3]
    // - Race: Demon, Set: YoD, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Corrupt a playable card in your
    //       opponent's hand. They have 1 turn to play it!
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void YoDCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [YOD_026e] Servant's Sacrifice (*) - COST:0
    // - Set: YoD
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [YOD_027e] Withering Away (*) - COST:0
    // - Set: YoD
    // --------------------------------------------------------
    // Text: Discard this at the end of your turn.
    // --------------------------------------------------------
}

void YoDCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - WARRIOR
    // [YOD_022] Risky Skipper - COST:1 [ATK:1/HP:3]
    // - Set: YoD, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you play a minion, deal 1 damage to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [YOD_023] Boom Squad - COST:1
    // - Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Discover</b> a <b>Lackey</b>, Mech, or Dragon.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // - GEARS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [YOD_024] Bomb Wrangler - COST:3 [ATK:2/HP:3]
    // - Set: YoD, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever this minion takes damage, summon a 1/1 Boom Bot.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
}

void YoDCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
}

void YoDCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - NEUTRAL
    // [YOD_006] Escaped Manasaber - COST:4 [ATK:3/HP:5]
    // - Race: Beast, Faction: Neutral, Set: YoD, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Stealth</b>Whenever this attacks,
    //       gain 1 Mana Crystal this turn only.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [YOD_028] Skydiving Instructor - COST:3 [ATK:2/HP:2]
    // - Faction: Neutral, Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 1 Cost minion from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [YOD_029] Hailbringer - COST:5 [ATK:3/HP:4]
    // - Race: Elemental, Faction: Neutral, Set: YoD, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two 1/1 Ice Shards
    //       that <b>Freeze</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 2
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [YOD_030] Licensed Adventurer - COST:2 [ATK:2/HP:2]
    // - Faction: Neutral, Set: YoD, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a <b>Quest</b>,
    //       add a Coin to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - QUEST = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [YOD_032] Skydiving Instructor - COST:4 [ATK:3/HP:3]
    // - Race: Demon, Faction: Neutral, Set: YoD, Rarity: Rare
    // --------------------------------------------------------
    // Text: Costs (1) less for each damage dealt to
    //       your opponent this turn.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [YOD_033] Boompistol Bully - COST:5 [ATK:5/HP:5]
    // - Faction: Neutral, Set: YoD, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Enemy <b>Battlecry</b> cards
    //       cost (5) more next turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [YOD_035] Grand Lackey Erkh - COST:4 [ATK:2/HP:3]
    // - Faction: Neutral, Set: YoD, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you play a <b>Lackey</b>,
    //       add a <b>Lackey</b> to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [YOD_038] Sky Gen'ral Kragg - COST:4 [ATK:2/HP:3]
    // - Race: Pirate, Faction: Neutral, Set: YoD, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Taunt</b> <b>Battlecry:</b>
    //       If you've played a <b>Quest</b> this game,
    //       summon a 4/2 Parrot with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - QUEST = 1
    // - RUSH = 1
    // --------------------------------------------------------
}

void YoDCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - NEUTRAL
    // [YOD_029t] Ice Shard - COST:1 [ATK:1/HP:1]
    // - Race: Elemental, Faction: Neutral, Set: YoD
    // --------------------------------------------------------
    // Text: <b>Freeze</b> any character damaged by this minion.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [YOD_032e] Frenzied (*) - COST:0
    // - Set: YoD
    // --------------------------------------------------------
    // Text: Cost reduced.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [YOD_033e] Smokescreen (*) - COST:0
    // - Set: YoD
    // --------------------------------------------------------
    // Text: Your <b>Battlecry</b> cards cost (5) more.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [YOD_038t] Sharkbait - COST:4 [ATK:4/HP:2]
    // - Race: Beast, Faction: Neutral, Set: YoD, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - RUSH = 1
    // --------------------------------------------------------
}

void YoDCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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
}  // namespace RosettaStone::PlayMode
