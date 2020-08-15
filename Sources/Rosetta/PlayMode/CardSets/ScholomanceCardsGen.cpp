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
    Power power;

    // ----------------------------------------- MINION - DRUID
    // [SCH_242] Gibberling - COST: 1 [ATK: 1/HP: 1]
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Spellburst:</b> Summon a Gibberling.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [SCH_333] Nature Studies - COST: 1
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Discover</b> a spell. Your next one costs (1) less.
    // --------------------------------------------------------
    // GameTag:
    //  - DISCOVER = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [SCH_427] Lightning Bloom - COST: 0
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: Gain 2 Mana Crystals this turn only.
    //       <b>Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    //  - OVERLOAD = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [SCH_606] Partner Assignment - COST: 1
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Add a random 2-Cost and 3-Cost Beast to your hand.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [SCH_609] Survival of the Fittest - COST: 10
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: Give +4/+4 to all minions in your hand, deck, and battlefield.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [SCH_612] Runic Carvings - COST: 6
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Summon four 2/2 Treant Totems; or
    // <b>Overload:</b> (2) to summon them with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    //  - CHOOSE_ONE = 1
    //  - OVERLOAD = 1
    // --------------------------------------------------------
    // RefTag:
    //  - RUSH = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [SCH_613] Groundskeeper - COST: 4 [ATK: 4/HP: 5]
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> If you're holding a
    //       spell that costs (5) or more,
    //       restore 5 Health.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    //  - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [SCH_614] Forest Warden Omu - COST: 6 [ATK: 5/HP: 4]
    //  - Set: SCHOLOMANCE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Spellburst:</b> Refresh your Mana Crystals.
    // --------------------------------------------------------
    // GameTag:
    //  - ELITE = 1

    // ----------------------------------------- MINION - DRUID
    // [SCH_616] Twilight Runner - COST: 5 [ATK: 5/HP: 4]
    //  - Race: BEAST, Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //       Whenever this attacks, draw 2 cards.
    // --------------------------------------------------------
    // GameTag:
    //  - STEALTH = 1
    //  - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
}

void ScholomanceCardsGen::AddDruidNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------------ ENCHANTMENT - DRUID
    // [SCH_182e] Outspoken - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [SCH_333e] Nature Studies - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Your next spell costs (1) less.
    // --------------------------------------------------------
    // GameTag:
    //  - AURA = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [SCH_333e2] Studying Nature - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [SCH_609e] Survival of the Fittest - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: +4/+4.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [SCH_612a] Call to Aid - COST: 6
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Summon four 2/2 Treant Totems.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [SCH_612b] Alarm the Forest - COST: 6
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Summon four 2/2 Treant Totems with <b>Rush</b>.
    //       <b>Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    //  - OVERLOAD = 1
    // --------------------------------------------------------
    // RefTag:
    //  - RUSH = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [SCH_612t] Treant Totem - COST: 2 [ATK: 2/HP: 2]
    //  - Race: TOTEM, Set: SCHOLOMANCE
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [SCH_617e] Adorable - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
}

void ScholomanceCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------------- MINION - HUNTER
    // [SCH_133] Wolpertinger - COST: 1 [ATK: 1/HP: 1]
    //  - Race: BEAST, Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a copy of this.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [SCH_239] Krolusk Barkstripper - COST: 4 [ATK: 3/HP: 5]
    //  - Race: BEAST, Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Spellburst:</b> Destroy a random enemy minion.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [SCH_244] Teacher's Pet - COST: 5 [ATK: 4/HP: 5]
    //  - Race: BEAST, Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Summon a
    //       random 3-Cost Beast.
    // --------------------------------------------------------
    // GameTag:
    //  - DEATHRATTLE = 1
    //  - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [SCH_300] Carrion Studies - COST: 1
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Discover</b> a <b>Deathrattle</b> minion. Your next one costs
    // (1) less.
    // --------------------------------------------------------
    // GameTag:
    //  - DISCOVER = 1
    // --------------------------------------------------------
    // RefTag:
    //  - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [SCH_340] Bloated Python - COST: 3 [ATK: 1/HP: 2]
    //  - Race: BEAST, Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 4/4 Hapless Handler.
    // --------------------------------------------------------
    // GameTag:
    //  - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [SCH_539] Professor Slate - COST: 3 [ATK: 3/HP: 4]
    //  - Set: SCHOLOMANCE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Your spells are <b>Poisonous</b>.
    // --------------------------------------------------------
    // GameTag:
    //  - ELITE = 1
    //  - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    //  - POISONOUS = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [SCH_604] Overwhelm - COST: 1
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 2 damage to a minion. Deal one more damage for each Beast you
    // control.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [SCH_607] Shan'do Wildclaw - COST: 3 [ATK: 3/HP: 3]
    //  - Set: SCHOLOMANCE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Give Beasts
    //       in your deck +1/+1; or
    //       Transform into a copy
    //       of a friendly Beast.
    // --------------------------------------------------------
    // GameTag:
    //  - ELITE = 1
    //  - CHOOSE_ONE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [SCH_610] Guardian Animals - COST: 7
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: Summon two Beasts that cost (5) or less from your deck. Give them
    // <b>Rush</b>.
    // --------------------------------------------------------
    // RefTag:
    //  - RUSH = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [SCH_617] Adorable Infestation - COST: 1
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion +1/+1. Summon a 1/1 Cub. Add a Cub to your hand.
    // --------------------------------------------------------
}

void ScholomanceCardsGen::AddHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------------- MINION - HUNTER
    // [SCH_340t] Hapless Handler - COST: 4 [ATK: 4/HP: 4]
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [SCH_538e] Ace Hunter's Lesson - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: <b>Immune</b> while attacking.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [SCH_600t3e] Kolek's Call - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Kolek is granting this minion +1 Attack.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [SCH_607a] Transfiguration - COST: 3
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Transform into a copy of a friendly Beast.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [SCH_607b] Rile the Herd - COST: 3
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Give Beasts in your deck +1/+1.
    // --------------------------------------------------------
    // RefTag:
    //  - IMMUNE = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [SCH_607e] Riled Up - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [SCH_617t] Marsuul Cub - COST: 1 [ATK: 1/HP: 1]
    //  - Race: BEAST, Set: SCHOLOMANCE
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [SCH_618e] Blood of Innocents - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
}

void ScholomanceCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------------------ MINION - MAGE
    // [SCH_241] Firebrand - COST: 3 [ATK: 3/HP: 4]
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b><b>Spellburst</b>:</b> Deal 4 damage randomly split among
    // all enemy minions.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [SCH_243] Wyrm Weaver - COST: 5 [ATK: 3/HP: 6]
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Spellburst:</b> Summon two 1/3 Mana Wyrms.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [SCH_310] Lab Partner - COST: 1 [ATK: 1/HP: 3]
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    //  - SPELLPOWER = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [SCH_348] Combustion - COST: 3
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 4 damage to
    //       a minion. Any excess
    //       damages both neighbors.
    // --------------------------------------------------------
    // GameTag:
    //  - ImmuneToSpellpower = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [SCH_353] Cram Session - COST: 2
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Draw 1 cards <i>(improved by <b>Spell Damage</b>)</i>.
    // --------------------------------------------------------
    // RefTag:
    //  - SPELLPOWER = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [SCH_400] Mozaki, Master Duelist - COST: 5 [ATK: 3/HP: 8]
    //  - Set: SCHOLOMANCE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you cast a spell, gain <b>Spell Damage +1</b>.
    // --------------------------------------------------------
    // GameTag:
    //  - ELITE = 1
    //  - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    //  - SPELLPOWER = 1
    // --------------------------------------------------------
}

void ScholomanceCardsGen::AddMageNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------------- ENCHANTMENT - MAGE
    // [SCH_400e2] Magic Master - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
}

void ScholomanceCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    Power power;

    // --------------------------------------- MINION - PALADIN
    // [SCH_135] Turalyon, the Tenured - COST: 8 [ATK: 3/HP: 12]
    //  - Set: SCHOLOMANCE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Rush</b>. Whenever this attacks
    //       a minion, set the defender's
    //       Attack and Health to 3.
    // --------------------------------------------------------
    // GameTag:
    //  - ELITE = 1
    //  - RUSH = 1
    //  - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [SCH_138] Blessing of Authority - COST: 5
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give a minion +8/+8. It can't attack heroes this turn.
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [SCH_139] Devout Pupil - COST: 6 [ATK: 4/HP: 5]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Divine Shield, Taunt</b>
    //       Costs (1) less for each spell
    //       you've cast on friendly
    //       characters this game.
    // --------------------------------------------------------
    // GameTag:
    //  - DIVINE_SHIELD = 1
    //  - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [SCH_141] High Abbess Alura - COST: 4 [ATK: 3/HP: 6]
    //  - Set: SCHOLOMANCE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Spellburst:</b> Cast a spell from your deck <i>(targets this if
    // possible)</i>.
    // --------------------------------------------------------
    // GameTag:
    //  - ELITE = 1

    // --------------------------------------- MINION - PALADIN
    // [SCH_149] Argent Braggart - COST: 2 [ATK: 1/HP: 1]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain Attack and Health to match the highest in
    // the battlefield.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [SCH_247] First Day of School - COST: 0
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: Add 2 random 1-Cost minions to your hand.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [SCH_250] Wave of Apathy - COST: 1
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: Set the Attack of all enemy minions to 1 until your next turn.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [SCH_302] Gift of Luminance - COST: 3
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give a minion <b>Divine Shield</b>, then summon a 1/1 copy of it.
    // --------------------------------------------------------
    // RefTag:
    //  - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - PALADIN
    // [SCH_523] Ceremonial Maul - COST: 3
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Spellburst</b>: Summon a Student with <b>Taunt</b> and stats
    // equal to the spell's Cost.
    // --------------------------------------------------------
    // RefTag:
    //  - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [SCH_524] Shield of Honor - COST: 1
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a damaged minion +3 Attack and <b>Divine Shield</b>.
    // --------------------------------------------------------
    // RefTag:
    //  - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [SCH_526] Lord Barov - COST: 3 [ATK: 3/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Set the Health
    //       of all other minions to 1.
    //       <b>Deathrattle:</b> Deal 1 damage
    //       to all minions.
    // --------------------------------------------------------
    // GameTag:
    //  - ELITE = 1
    //  - BATTLECRY = 1
    //  - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [SCH_532] Goody Two-Shields - COST: 3 [ATK: 4/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    //       <b>Spellburst:</b> Gain <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    //  - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [SCH_533] Commencement - COST: 7
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon a minion from your deck. Give it <b>Taunt</b> and <b>Divine
    // Shield</b>.
    // --------------------------------------------------------
    // RefTag:
    //  - DIVINE_SHIELD = 1
    //  - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [SCH_712] Judicious Junior - COST: 6 [ATK: 4/HP: 9]
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    // --------------------------------------------------------
    // GameTag:
    //  - LIFESTEAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    cards.emplace("SCH_712", CardDef(power));
}

void ScholomanceCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [SCH_135e] Schooled - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: 3/3.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [SCH_138e] Blessing of Authority - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: +8/+8.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [SCH_138e2] Honorable Intentions - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Can't attack heroes this turn.
    // --------------------------------------------------------
    // GameTag:
    //  - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [SCH_149e] Best of the Best - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [SCH_523t] Honor Student - COST: 1 [ATK: 1/HP: 1]
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // RefTag:
    //  - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [SCH_533e] Graduated - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: <b>Taunt</b>, <b>Divine Shield</b>.
    // --------------------------------------------------------
}

void ScholomanceCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------------- MINION - PRIEST
    // [SCH_120] Cabal Acolyte - COST: 4 [ATK: 2/HP: 6]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Spellburst:</b> Gain control
    //       of a random enemy minion
    //       with 2 or less Attack.
    // --------------------------------------------------------
    // GameTag:
    //  - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [SCH_126] Disciplinarian Gandling - COST: 4 [ATK: 3/HP: 6]
    //  - Set: SCHOLOMANCE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you play a minion,
    //       destroy it and summon a
    //       4/4 Failed Student.
    // --------------------------------------------------------
    // GameTag:
    //  - ELITE = 1
    //  - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [SCH_136] Power Word: Feast - COST: 2
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give a minion +2/+2. Restore it to full Health at the end of this
    // turn.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [SCH_137] Frazzled Freshman - COST: 1 [ATK: 1/HP: 4]
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [SCH_140] Flesh Giant - COST: 8 [ATK: 8/HP: 8]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: Costs (1) less for each time your hero's Health changed during your
    // turns.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [SCH_159] Mindrender Illucia - COST: 2 [ATK: 1/HP: 3]
    //  - Set: SCHOLOMANCE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Swap hands and decks with your opponent until
    // your next turn.
    // --------------------------------------------------------
    // GameTag:
    //  - ELITE = 1
    //  - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [SCH_233] Draconic Studies - COST: 1
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Discover</b> a Dragon. Your
    //       next one costs (1) less.
    // --------------------------------------------------------
    // GameTag:
    //  - DISCOVER = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [SCH_512] Initiation - COST: 6
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 4 damage to a minion. If that kills it, summon a new copy.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [SCH_513] Brittlebone Destroyer - COST: 4 [ATK: 3/HP: 3]
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your hero's
    //       Health changed this turn,
    //       destroy a minion.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [SCH_514] Raise Dead - COST: 0
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 3 damage to your hero. Return two friendly minions that died
    // this game to your hand.
    // --------------------------------------------------------
}

void ScholomanceCardsGen::AddPriestNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------------- MINION - PRIEST
    // [SCH_126t] Failed Student - COST: 4 [ATK: 4/HP: 4]
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [SCH_136e] Power Word: Feast - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [SCH_136e2] Famished - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Restores full health at end of turn.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [SCH_159e] Mind Swap - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: At the start of your turn, swap both players hands and decks.
    // --------------------------------------------------------
    // GameTag:
    //  - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [SCH_233e] Draconic Studies - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Your next Dragon costs (1) less.
    // --------------------------------------------------------
    // GameTag:
    //  - AURA = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [SCH_233e2] Studying Dragons - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [SCH_250e] Apathetic - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Attack reduced to 1 until next turn.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [SCH_302e] Student of the Light - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: 1/1.
    // --------------------------------------------------------
}

void ScholomanceCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------------- MINION - ROGUE
    // [SCH_234] Shifty Sophomore - COST: 4 [ATK: 4/HP: 4]
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //       <b>Spellburst:</b> Add a <b>Combo</b> card to your hand.
    // --------------------------------------------------------
    // GameTag:
    //  - STEALTH = 1
    // --------------------------------------------------------
    // RefTag:
    //  - COMBO = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [SCH_305] Secret Passage - COST: 1
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: Replace your hand with 5 cards from your deck. Swap back next turn.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [SCH_426] Infiltrator Lilian - COST: 4 [ATK: 4/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //       <b>Deathrattle:</b> Summon a 4/2
    //       Forsaken Lilian that attacks
    //       a random enemy.
    // --------------------------------------------------------
    // GameTag:
    //  - ELITE = 1
    //  - DEATHRATTLE = 1
    //  - STEALTH = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [SCH_519] Vulpera Toxinblade - COST: 3 [ATK: 3/HP: 3]
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: Your weapon has +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    //  - AURA = 1
    // --------------------------------------------------------

    // ----------------------------------------- WEAPON - ROGUE
    // [SCH_622] Self-Sharpening Sword - COST: 3
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: After your hero attacks, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    //  - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [SCH_706] Plagiarize - COST: 2
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> At the end of your opponent's turn, add copies of
    // the cards they played to your hand.
    // --------------------------------------------------------
    // GameTag:
    //  - SECRET = 1
    // --------------------------------------------------------
}

void ScholomanceCardsGen::AddRogueNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [SCH_305e] Secret Exit - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [SCH_305e2] Secret Entrance - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [SCH_305e3] Secret Passage Player Enchantment - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [SCH_351e] Illusion - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: This might be an illusion that dies when it takes damage.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [SCH_351e2] Illusion - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: This might be an illusion that dies when it takes damage.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [SCH_352e] Potion of Illusion - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: 1/1.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [SCH_426t] Forsaken Lilian - COST: 4 [ATK: 4/HP: 2]
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // GameTag:
    //  - ELITE = 1
}

void ScholomanceCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------------- MINION - SHAMAN
    // [SCH_236] Diligent Notetaker - COST: 2 [ATK: 2/HP: 3]
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Spellburst:</b> Return the spell to your hand.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [SCH_271] Molten Blast - COST: 3
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 2 damage. Summon that many 1/1 Elementals.
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - SHAMAN
    // [SCH_301] Rune Dagger - COST: 2
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: After your hero attacks, gain <b>Spell Damage +1</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    //  - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    //  - SPELLPOWER = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [SCH_507] Instructor Fireheart - COST: 3 [ATK: 3/HP: 3]
    //  - Set: SCHOLOMANCE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a spell
    //       that costs (1) or more.
    //       If you play it this turn,
    //       repeat this effect.
    // --------------------------------------------------------
    // GameTag:
    //  - ELITE = 1
    //  - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    //  - DISCOVER = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [SCH_535] Tidal Wave - COST: 8
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    //       Deal 3 damage to
    //       all minions.
    // --------------------------------------------------------
    // GameTag:
    //  - LIFESTEAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [SCH_615] Totem Goliath - COST: 5 [ATK: 4/HP: 5]
    //  - Race: TOTEM, Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon all four basic Totems.
    //       <b>Overload: (2)</b>
    // --------------------------------------------------------
    // GameTag:
    //  - DEATHRATTLE = 1
    // --------------------------------------------------------
    // RefTag:
    //  - OVERLOAD = 1
    // --------------------------------------------------------
}

void ScholomanceCardsGen::AddShamanNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------------- MINION - SHAMAN
    // [SCH_271t] Molten Elemental - COST: 1 [ATK: 1/HP: 1]
    //  - Race: ELEMENTAL, Set: SCHOLOMANCE
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [SCH_507e] Hot Streak! - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: If played this turn, <b>Discover</b> another spell.
    // --------------------------------------------------------
    // GameTag:
    //  - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
}

void ScholomanceCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    Power power;

    // --------------------------------------- MINION - WARLOCK
    // [SCH_147] Boneweb Egg - COST: 2 [ATK: 0/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon
    //       two 2/1 Spiders. If you
    //       discard this, trigger its
    //       <b>Deathrattle</b>.
    // --------------------------------------------------------
    // GameTag:
    //  - DEATHRATTLE = 1
    //  - InvisibleDeathrattle = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [SCH_158] Demonic Studies - COST: 1
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Discover</b> a Demon. Your next one costs (1) less.
    // --------------------------------------------------------
    // GameTag:
    //  - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [SCH_181] Archwitch Willow - COST: 9 [ATK: 7/HP: 7]
    //  - Set: SCHOLOMANCE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a random Demon from your hand and deck.
    // --------------------------------------------------------
    // GameTag:
    //  - ELITE = 1
    //  - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [SCH_307] School Spirits - COST: 3
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 2 damage to all
    //       minions. Shuffle 2 Soul
    //       Fragments into your deck.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [SCH_343] Void Drinker - COST: 5 [ATK: 4/HP: 5]
    //  - Race: DEMON, Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Taunt</b>. <b>Battlecry:</b> Destroy
    //       a Soul Fragment in your
    //       deck to gain +3/+3.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    //  - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [SCH_517] Shadowlight Scholar - COST: 3 [ATK: 3/HP: 4]
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a Soul Fragment in your deck to deal 3
    // damage.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [SCH_700] Spirit Jailer - COST: 1 [ATK: 1/HP: 3]
    //  - Race: DEMON, Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Shuffle 2 Soul Fragments into your deck.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [SCH_701] Soul Shear - COST: 2
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 3 damage to a
    //       minion. Shuffle 2 Soul
    //       Fragments into your deck.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [SCH_702] Felosophy - COST: 1
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: Copy the lowest Cost
    //       Demon in your hand.
    //       <b>Outcast:</b> Give both +1/+1.
    // --------------------------------------------------------
    // GameTag:
    //  - OUTCAST = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [SCH_703] Soulciologist Malicia - COST: 7 [ATK: 5/HP: 5]
    //  - Set: SCHOLOMANCE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> For each Soul Fragment in your deck, summon a 3/3
    // Soul with <b>Rush</b>.@ <i>(@)</i>
    // --------------------------------------------------------
    // GameTag:
    //  - ELITE = 1
    //  - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    //  - RUSH = 1
    // --------------------------------------------------------
}

void ScholomanceCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // --------------------------------------- MINION - WARLOCK
    // [SCH_147t] Boneweb Spider - COST: 1 [ATK: 2/HP: 1]
    //  - Race: BEAST, Set: SCHOLOMANCE
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [SCH_158e] Demonic Studies - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Your next Demon costs (1) less.
    // --------------------------------------------------------
    // GameTag:
    //  - AURA = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [SCH_307t] Soul Fragment - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: <b>Casts When Drawn</b>
    //       Restore #2 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    //  - TOPDECK = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [SCH_343e] Soul Powered - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: +3/+3.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [SCH_703t] Released Soul - COST: 3 [ATK: 3/HP: 3]
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    //  - RUSH = 1
    // --------------------------------------------------------
}

void ScholomanceCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------------- SPELL - WARRIOR
    // [SCH_237] Athletic Studies - COST: 1
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Discover</b> a <b>Rush</b> minion. Your next one costs (1) less.
    // --------------------------------------------------------
    // GameTag:
    //  - DISCOVER = 1
    // --------------------------------------------------------
    // RefTag:
    //  - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [SCH_238] Reaper's Scythe - COST: 4
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Spellburst</b>: Also
    //       damages adjacent
    //       minions this turn.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [SCH_317] Playmaker - COST: 3 [ATK: 4/HP: 3]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: After you play a <b>Rush</b>
    //       minion, summon a copy
    //        with 1 Health remaining.
    // --------------------------------------------------------
    // GameTag:
    //  - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    //  - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [SCH_337] Troublemaker - COST: 8 [ATK: 6/HP: 8]
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn, summon two 3/3 Ruffians that attack random
    // enemies.
    // --------------------------------------------------------
    // GameTag:
    //  - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [SCH_525] In Formation! - COST: 2
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: Add 2 random <b>Taunt</b> minions to your hand.
    // --------------------------------------------------------
    // RefTag:
    //  - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [SCH_621] Rattlegore - COST: 9 [ATK: 9/HP: 9]
    //  - Set: SCHOLOMANCE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Resummon this with -1/-1.
    // --------------------------------------------------------
    // GameTag:
    //  - ELITE = 1
    //  - DEATHRATTLE = 1
    // --------------------------------------------------------
}

void ScholomanceCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [SCH_237e] Athletic Studies - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Your next <b>Rush</b> minion costs (1) less.
    // --------------------------------------------------------
    // GameTag:
    //  - AURA = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [SCH_237e2] Studying Athletics - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [SCH_238e] Reaping - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Damages minions next to whomever your hero attacks.
    // --------------------------------------------------------
    // GameTag:
    //  - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [SCH_337t] Ruffian - COST: 3 [ATK: 3/HP: 3]
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [SCH_425e] Sharpened - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [SCH_526e] A Common Peasant - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Health changed to 1.
    // --------------------------------------------------------
}

void ScholomanceCardsGen::AddDemonHunter(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------- WEAPON - DEMONHUNTER
    // [SCH_252] Marrowslicer - COST: 4
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Shuffle 2 Soul Fragments into your deck.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [SCH_253] Cycle of Hatred - COST: 7
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 3 damage to all minions. Summon a 3/3 Spirit for every minion
    // killed.
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [SCH_276] Magehunter - COST: 3 [ATK: 2/HP: 3]
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       Whenever this attacks a minion, <b>Silence</b> it.
    // --------------------------------------------------------
    // GameTag:
    //  - RUSH = 1
    //  - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    //  - SILENCE = 1
    // --------------------------------------------------------

    // ----------------------------------- WEAPON - DEMONHUNTER
    // [SCH_279] Trueaim Crescent - COST: 1
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: After your Hero attacks a minion, your minions attack it too.
    // --------------------------------------------------------
    // GameTag:
    //  - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [SCH_354] Ancient Void Hound - COST: 9 [ATK: 10/HP: 10]
    //  - Race: DEMON, Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       steal 1 Attack and Health
    //       from all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    //  - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [SCH_355] Shardshatter Mystic - COST: 3 [ATK: 3/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a Soul Fragment in your deck to deal 3
    // damage to all other minions.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [SCH_356] Glide - COST: 4
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Shuffle your hand into
    //       your deck. Draw 4 cards.
    //       <b>Outcast:</b> Your opponent
    //       does the same.
    // --------------------------------------------------------
    // GameTag:
    //  - OUTCAST = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [SCH_357] Fel Guardians - COST: 7
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: Summon three 1/2 Demons with <b>Taunt</b>. Costs (1) less whenever
    // a friendly minion dies.
    // --------------------------------------------------------
    // RefTag:
    //  - TAUNT = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [SCH_422] Double Jump - COST: 1
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: Draw an <b>Outcast</b> card from your deck.
    // --------------------------------------------------------
    // RefTag:
    //  - OUTCAST = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [SCH_538] Ace Hunter Kreen - COST: 3 [ATK: 2/HP: 4]
    //  - Set: SCHOLOMANCE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Your other characters are <b>Immune</b> while attacking.
    // --------------------------------------------------------
    // GameTag:
    //  - ELITE = 1
    //  - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    //  - IMMUNE = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [SCH_600] Demon Companion - COST: 1
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon a random Demon Companion.
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [SCH_603] Star Student Stelina - COST: 4 [ATK: 4/HP: 3]
    //  - Set: SCHOLOMANCE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Outcast:</b> Look at 3 cards
    //       in your opponent's hand.
    //       Shuffle one of them
    //       into their deck.
    // --------------------------------------------------------
    // GameTag:
    //  - ELITE = 1
    //  - OUTCAST = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [SCH_618] Blood Herald - COST: 5 [ATK: 1/HP: 1]
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever a friendly minion dies while this is in your hand, gain
    // +1/+1.
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [SCH_704] Soulshard Lapidary - COST: 5 [ATK: 5/HP: 5]
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a Soul
    //       Fragment in your deck to
    //       give your hero +5 Attack
    //       this turn.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [SCH_705] Vilefiend Trainer - COST: 4 [ATK: 5/HP: 4]
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Outcast:</b> Summon two 1/1 Demons.
    // --------------------------------------------------------
    // GameTag:
    //  - OUTCAST = 1
    // --------------------------------------------------------
}

void ScholomanceCardsGen::AddDemonHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ----------------------------------- MINION - DEMONHUNTER
    // [SCH_253t] Spirit of Vengeance - COST: 3 [ATK: 3/HP: 3]
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [SCH_354e] Siphoned - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Reduced Attack and Health.
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [SCH_354e2] Void Siphon - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Increased Attack and Health.
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [SCH_354e2a] Void Siphon - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
    // GameTag:
    //  - ENCHANTMENT_INVISIBLE = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [SCH_354e2b] Void Siphon - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Increased Health.
    // --------------------------------------------------------
    // GameTag:
    //  - ENCHANTMENT_INVISIBLE = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [SCH_354ea] Siphoned - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Reduced Attack.
    // --------------------------------------------------------
    // GameTag:
    //  - ENCHANTMENT_INVISIBLE = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [SCH_354eb] Siphoned - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Reduced Health.
    // --------------------------------------------------------
    // GameTag:
    //  - ENCHANTMENT_INVISIBLE = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [SCH_357e] Soul Infused - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Costs less.
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [SCH_357t] Soulfed Felhound - COST: 1 [ATK: 1/HP: 2]
    //  - Race: DEMON, Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    //  - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [SCH_600t1] Reffuh - COST: 1 [ATK: 2/HP: 1]
    //  - Race: DEMON, Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    //  - CHARGE = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [SCH_600t2] Shima - COST: 1 [ATK: 2/HP: 2]
    //  - Race: DEMON, Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    //  - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [SCH_600t3] Kolek - COST: 1 [ATK: 1/HP: 2]
    //  - Race: DEMON, Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Your other minions have +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    //  - AURA = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [SCH_702e] Felosophically Inclined - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: +1/+1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [SCH_704e] Soul Rage - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: +5 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    //  - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [SCH_705t] Snarling Vilefiend - COST: 1 [ATK: 1/HP: 1]
    //  - Race: DEMON, Set: SCHOLOMANCE
    // --------------------------------------------------------
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
    // [SCH_142] Voracious Reader - COST: 2 [ATK: 1/HP: 3]
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn, draw until you have 3 cards.
    // --------------------------------------------------------
    // GameTag:
    //  - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_143] Divine Rager - COST: 4 [ATK: 5/HP: 1]
    //  - Race: ELEMENTAL, Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    //  - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_145] Desk Imp - COST: 0 [ATK: 1/HP: 1]
    //  - Race: DEMON, Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_146] Robes of Protection - COST: 3 [ATK: 2/HP: 4]
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Your minions have "Can't be targeted by spells or Hero Powers."
    // --------------------------------------------------------
    // GameTag:
    //  - AURA = 1
    //  - CANT_BE_TARGETED_BY_SPELLS = 1
    //  - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_157] Enchanted Cauldron - COST: 3 [ATK: 1/HP: 6]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b><b>Spellburst</b>:</b> Cast a random spell of the same Cost.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_160] Wandmaker - COST: 2 [ATK: 2/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a 1-Cost spell from your class to your hand.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_162] Vectus - COST: 5 [ATK: 4/HP: 4]
    //  - Set: SCHOLOMANCE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two
    //       1/1 Whelps. Each gains a
    //       <b>Deathrattle</b> from your minions
    //       that died this game.
    // --------------------------------------------------------
    // GameTag:
    //  - ELITE = 1
    //  - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    //  - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_182] Speaker Gidra - COST: 3 [ATK: 1/HP: 4]
    //  - Set: SCHOLOMANCE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b><b>Rush</b>, Windfury</b>
    //       <b><b>Spellburst</b>:</b> Gain Attack
    //       and Health equal to
    //       the spell's Cost.
    // --------------------------------------------------------
    // GameTag:
    //  - ELITE = 1
    //  - RUSH = 1
    //  - WINDFURY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_199] Transfer Student - COST: 2 [ATK: 2/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: This has different effects based on which game board you're on.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_224] Headmaster Kel'Thuzad - COST: 5 [ATK: 4/HP: 6]
    //  - Set: SCHOLOMANCE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Spellburst:</b> If the spell destroys any minions, summon them.
    // --------------------------------------------------------
    // GameTag:
    //  - ELITE = 1

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_230] Onyx Magescribe - COST: 6 [ATK: 4/HP: 9]
    //  - Race: DRAGON, Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Spellburst:</b> Add 2 random spells from your class to your
    // hand.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_231] Intrepid Initiate - COST:1 [ATK:1/HP:2]
    // - Set: Scholomance, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Spellburst:</b> Gain +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddSpellburstTask(
        std::make_shared<AddEnchantmentTask>("SCH_231e", EntityType::SOURCE));
    cards.emplace("SCH_231", CardDef(power));

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_232] Crimson Hothead - COST: 4 [ATK: 3/HP: 6]
    //  - Race: DRAGON, Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Spellburst:</b> Gain +1 Attack and <b>Taunt</b>.
    // --------------------------------------------------------
    // RefTag:
    //  - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [SCH_235] Devolving Missiles - COST: 1
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: Shoot three missiles
    //       at random enemy minions
    //       that transform them into
    //       ones that cost (1) less.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_245] Steward of Scrolls - COST: 5 [ATK: 4/HP: 4]
    //  - Race: ELEMENTAL, Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    //       <b>Battlecry:</b> <b>Discover</b> a spell.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    //  - DISCOVER = 1
    //  - SPELLPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_248] Pen Flinger - COST: 1 [ATK: 1/HP: 1]
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage. <b>Spellburst:</b> Return this
    // to your hand.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - NEUTRAL
    // [SCH_259] Sphere of Sapience - COST: 1
    //  - Set: SCHOLOMANCE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       look at your top card. You
    //       can put it on the bottom
    //        and lose 1 Durability.
    // --------------------------------------------------------
    // GameTag:
    //  - ELITE = 1
    //  - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [SCH_270] Primordial Studies - COST: 1
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Discover</b> a <b>Spell Damage</b> minion. Your next one costs
    // (1) less.
    // --------------------------------------------------------
    // GameTag:
    //  - DISCOVER = 1
    // --------------------------------------------------------
    // RefTag:
    //  - SPELLPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_273] Ras Frostwhisper - COST: 5 [ATK: 3/HP: 6]
    //  - Set: SCHOLOMANCE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       deal 1 damage to all enemies <i>(improved by <b>Spell
    //       Damage</b>)</i>.
    // --------------------------------------------------------
    // GameTag:
    //  - ELITE = 1
    //  - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    //  - SPELLPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_283] Manafeeder Panthara - COST: 2 [ATK: 2/HP: 3]
    //  - Race: BEAST, Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you've used your Hero Power this turn, draw a
    // card.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_311] Animated Broomstick - COST: 1 [ATK: 1/HP: 1]
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Battlecry:</b> Give your other minions <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    //  - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_312] Tour Guide - COST: 1 [ATK: 1/HP: 1]
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your next Hero Power costs (0).
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_313] Wretched Tutor - COST: 4 [ATK: 2/HP: 5]
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Spellburst:</b> Deal 2 damage to all other minions.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_350] Wand Thief - COST: 1 [ATK: 1/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Combo:</b> <b>Discover</b> a Mage spell.
    // --------------------------------------------------------
    // GameTag:
    //  - COMBO = 1
    //  - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_351] Jandice Barov - COST: 5 [ATK: 2/HP: 1]
    //  - Set: SCHOLOMANCE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two
    //       random 5-Cost minions.
    //       Secretly pick one that dies
    //        when it takes damage.
    // --------------------------------------------------------
    // GameTag:
    //  - ELITE = 1
    //  - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [SCH_352] Potion of Illusion - COST: 4
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: Add 1/1 copies of your minions to your hand. They cost (1).
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_425] Doctor Krastinov - COST: 5 [ATK: 4/HP: 4]
    //  - Set: SCHOLOMANCE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       Whenever this attacks, give your weapon +1/+1.
    // --------------------------------------------------------
    // GameTag:
    //  - ELITE = 1
    //  - RUSH = 1
    //  - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_428] Lorekeeper Polkelt - COST: 4 [ATK: 4/HP: 5]
    //  - Set: SCHOLOMANCE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Reorder your deck
    //       from the highest Cost card
    //       to the lowest Cost card.
    // --------------------------------------------------------
    // GameTag:
    //  - ELITE = 1
    //  - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [SCH_509] Brain Freeze - COST: 1
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Freeze</b> a minion. <b>Combo:</b> Also deal 3 damage to it.
    // --------------------------------------------------------
    // GameTag:
    //  - COMBO = 1
    // --------------------------------------------------------
    // RefTag:
    //  - FREEZE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [SCH_521] Coerce - COST: 3
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: Destroy a damaged minion. <b>Combo:</b> Destroy any minion.
    // --------------------------------------------------------
    // GameTag:
    //  - COMBO = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_522] Steeldancer - COST: 4 [ATK: 4/HP: 4]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a random
    //       minion with Cost equal to
    //       your weapon's Attack.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_530] Sorcerous Substitute - COST: 6 [ATK: 6/HP: 6]
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you have <b>Spell Damage</b>, summon a copy of
    // this.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    //  - SPELLPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_537] Trick Totem - COST: 2 [ATK: 0/HP: 3]
    //  - Race: TOTEM, Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn, cast a random spell that costs (3) or
    // less.
    // --------------------------------------------------------
    // GameTag:
    //  - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_605] Lake Thresher - COST: 5 [ATK: 4/HP: 6]
    //  - Race: BEAST, Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: Also damages the minions next to whomever
    //       this attacks.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [SCH_623] Cutting Class - COST: 5
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: Draw 2 cards.
    //       Costs (1) less per Attack
    //       of your weapon.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_707] Fishy Flyer - COST: 4 [ATK: 4/HP: 3]
    //  - Race: MURLOC, Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>. <b>Deathrattle:</b> Add a 4/3 Ghost with <b>Rush</b>
    // to your hand.
    // --------------------------------------------------------
    // GameTag:
    //  - DEATHRATTLE = 1
    //  - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_708] Sneaky Delinquent - COST: 2 [ATK: 3/HP: 1]
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>. <b>Deathrattle:</b> Add a 3/1 Ghost with
    // <b>Stealth</b> to your hand.
    // --------------------------------------------------------
    // GameTag:
    //  - DEATHRATTLE = 1
    //  - STEALTH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_709] Smug Senior - COST: 6 [ATK: 5/HP: 7]
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>. <b>Deathrattle:</b> Add a 5/7 Ghost with <b>Taunt</b>
    // to your hand.
    // --------------------------------------------------------
    // GameTag:
    //  - DEATHRATTLE = 1
    //  - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_710] Ogremancer - COST: 5 [ATK: 3/HP: 7]
    //  - Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever your opponent
    //       casts a spell, summon a 2/2
    //       Skeleton with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    //  - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    //  - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_711] Plagued Protodrake - COST: 8 [ATK: 8/HP: 8]
    //  - Race: DRAGON, Set: SCHOLOMANCE, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a random 7-Cost minion.
    // --------------------------------------------------------
    // GameTag:
    //  - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_713] Cult Neophyte - COST: 2 [ATK: 3/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your opponent's spells cost (1) more next turn.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_714] Educated Elekk - COST: 3 [ATK: 3/HP: 4]
    //  - Race: BEAST, Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: Whenever a spell is played,
    //       this minion remembers it.
    //       <b>Deathrattle:</b> Shuffle the
    //       spells into your deck.
    // --------------------------------------------------------
    // GameTag:
    //  - DEATHRATTLE = 1
    //  - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_717] Keymaster Alabaster - COST: 7 [ATK: 6/HP: 8]
    //  - Set: SCHOLOMANCE, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever your opponent
    //        draws a card, add a copy to 
    //        your hand that costs (1).
    // --------------------------------------------------------
    // GameTag:
    //  - ELITE = 1
    //  - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
}

void ScholomanceCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SCH_146e] Protected - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    //  - CANT_BE_TARGETED_BY_SPELLS = 1
    //  - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SCH_158e2] Studying Demons - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SCH_162e] Experimental Plague - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Copied <b>Deathrattle</b> from {0}.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_162t] Plagued Hatchling - COST: 1 [ATK: 1/HP: 1]
    //  - Race: DRAGON, Set: SCHOLOMANCE
    // --------------------------------------------------------
    // RefTag:
    //  - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_199t] Transfer Student - COST: 2 [ATK: 2/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    //  - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_199t10] Transfer Student - COST: 2 [ATK: 2/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Spend all your Mana. Summon a random minion of
    // that Cost.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_199t11] Transfer Student - COST: 2 [ATK: 2/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a <b>Karazhan</b> Portal spell to your hand.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_199t12] Transfer Student - COST: 2 [ATK: 2/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a random minion in your hand +2/+2.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SCH_199t12e] Supplies from Gadgetzan - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_199t13] Transfer Student - COST: 2 [ATK: 2/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Adapt</b>.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    //  - ADAPT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_199t14] Transfer Student - COST: 2 [ATK: 2/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a random
    //       <b>Death Knight</b> card to
    //       your hand.
    // --------------------------------------------------------
    // GameTag:
    //  - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_199t15] Transfer Student - COST: 2 [ATK: 2/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Recruit</b> a minion that costs (2) or less.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    //  - RECRUIT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_199t16] Transfer Student - COST: 2 [ATK: 2/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Echo</b>
    //       <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    //  - ECHO = 1
    //  - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_199t17] Transfer Student - COST: 2 [ATK: 2/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Taunt</b>. <b>Battlecry:</b> If you
    //       have 10 Mana Crystals,
    //       gain +5/+5.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    //  - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SCH_199t17e] Omega Transfer - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: +5/+5.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_199t18] Transfer Student - COST: 2 [ATK: 2/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Overkill:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    //  - OVERKILL = 1
    //  - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_199t19] Transfer Student - COST: 2 [ATK: 2/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a <b>Lackey</b> to your hand.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_199t2] Transfer Student - COST: 2 [ATK: 2/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 2 damage.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_199t20] Transfer Student - COST: 2 [ATK: 2/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Reborn</b>
    // --------------------------------------------------------
    // GameTag:
    //  - REBORN = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_199t21] Transfer Student - COST: 2 [ATK: 2/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a Dragon.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    //  - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_199t22] Transfer Student - COST: 2 [ATK: 2/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Dormant</b> for 2 turns.
    //       When this awakens, deal
    //       3 damage to two random
    //       enemy minions.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_199t23] Transfer Student - COST: 2 [ATK: 2/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a Dual Class card to your hand.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_199t24] Transfer Student - COST: 2 [ATK: 2/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a random weapon to your hand.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_199t25] Transfer Student - COST: 2 [ATK: 2/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add an <b>Uldum</b> Plague spell to your hand.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_199t3] Transfer Student - COST: 2 [ATK: 2/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion +1/+2.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SCH_199t3e] Mark of the Pandaren - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: +1/+2.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_199t4] Transfer Student - COST: 2 [ATK: 2/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //        <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    //  - POISONOUS = 1
    //  - STEALTH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_199t5] Transfer Student - COST: 2 [ATK: 2/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a random <b>Deathrattle</b> minion to
    // your hand.
    // --------------------------------------------------------
    // GameTag:
    //  - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_199t6] Transfer Student - COST: 2 [ATK: 2/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry and Deathrattle:</b> Add a <b>Spare Part</b> card to
    // your hand.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    //  - DEATHRATTLE = 1
    // --------------------------------------------------------
    // RefTag:
    //  - SPARE_PART = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_199t7] Transfer Student - COST: 2 [ATK: 2/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: At the end of your turn, reduce the Cost of a random card in your
    // hand by (2).
    // --------------------------------------------------------
    // GameTag:
    //  - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SCH_199t7e] Transfer of Power - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_199t8] Transfer Student - COST: 2 [ATK: 2/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Inspire:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    //  - INSPIRE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_199t9] Transfer Student - COST: 2 [ATK: 2/HP: 2]
    //  - Set: SCHOLOMANCE, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a new basic Hero Power.
    // --------------------------------------------------------
    // GameTag:
    //  - BATTLECRY = 1
    //  - DISCOVER = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SCH_224e3] Kel'thuzad's Call - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_224t] Mr. Bigglesworth - COST: 0 [ATK: 1/HP: 1]
    //  - Race: BEAST, Set: SCHOLOMANCE
    // --------------------------------------------------------
    // GameTag:
    //  - ELITE = 1
    // --------------------------------------------------------


    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SCH_231e] Ready for School (*) - COST:0
    // - Set: Scholomance
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("SCH_231e"));
    cards.emplace("SCH_231e", CardDef(power));

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SCH_232e] Fired Up - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: +1 Attack and <b>Taunt</b>.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [SCH_259t] A New Fate - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Draw a different card.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SCH_270e] Runic Studies - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Your next <b>Spell Damage</b> minion costs (1) less.
    // --------------------------------------------------------
    // GameTag:
    //  - AURA = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SCH_270e2] Studying Runes - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SCH_300e] Carrion Studies - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Your next <b>Deathrattle</b> minion costs (1) less.
    // --------------------------------------------------------
    // GameTag:
    //  - AURA = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SCH_300e2] Studying Carrion - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SCH_301e] Runic Power - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: You have <b>Spell Damage +1</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    //  - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [SCH_305d] Secret Passage Dummy - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Dummy Hook Up SCH 305e3
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SCH_312e] School Tour - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Your Hero Power costs (0).
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SCH_351a] This is an Illusion. - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SCH_351b] This is not an Illusion. - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SCH_519e] Akunda's Bite - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SCH_524e] Shield of Honor - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: +3 Attack and <b>Divine Shield</b>.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SCH_539e] Professor's Poison - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SCH_622e] Honed Edge - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_707t] Spectral Flyer - COST: 4 [ATK: 4/HP: 3]
    //  - Race: MURLOC, Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    //  - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_708t] Spectral Delinquent - COST: 2 [ATK: 3/HP: 1]
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    //  - STEALTH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_709t] Spectral Senior - COST: 6 [ATK: 5/HP: 7]
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    //  - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SCH_710t] Risen Skeleton - COST: 2 [ATK: 2/HP: 2]
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    //  - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SCH_713e] Spoiled! - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Your spells cost (1) more this turn.
    // --------------------------------------------------------
    // GameTag:
    //  - AURA = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SCH_713e2] Spoiling - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Costs (1) more.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SCH_714e] Educated - COST: 0
    //  - Set: SCHOLOMANCE
    // --------------------------------------------------------
    // Text: Remembering spell.
    // --------------------------------------------------------
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