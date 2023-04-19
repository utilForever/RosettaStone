// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/CardSets/BoomsdayCardsGen.hpp>
#include <Rosetta/PlayMode/Cards/CardPowers.hpp>

namespace RosettaStone::PlayMode
{
void BoomsdayCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- HERO - WARRIOR
    // [BOT_238] Dr. Boom, Mad Genius - COST:7
    // - Set: BOOMSDAY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> For the rest of the game,game
    //       your Mechs have <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- HERO - WHIZBANG
    // [BOT_914h] Whizbang the Wonderful - COST:0
    // - Set: BOOMSDAY, Rarity: Free
    // --------------------------------------------------------
}

void BoomsdayCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- HERO_POWER - WARRIOR
    // [BOT_238p] Big Red Button - COST:2
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Activate this turn's Mech Suit power!
    // --------------------------------------------------------

    // ----------------------------------- HERO_POWER - WARRIOR
    // [BOT_238p1] Zap Cannon - COST:2
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Deal 3 damage. Swaps each turn.
    // --------------------------------------------------------

    // ----------------------------------- HERO_POWER - WARRIOR
    // [BOT_238p2] Blast Shield - COST:2
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Gain 7 Armor. Swaps each turn.
    // --------------------------------------------------------

    // ----------------------------------- HERO_POWER - WARRIOR
    // [BOT_238p3] KABOOM! - COST:2
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Deal 1 damage to all enemies. Swaps each turn.
    // --------------------------------------------------------

    // ----------------------------------- HERO_POWER - WARRIOR
    // [BOT_238p4] Delivery Drone - COST:2
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       <b>Discover</b> a Mech. Swaps each turn.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // - GEARS = 1
    // --------------------------------------------------------

    // ----------------------------------- HERO_POWER - WARRIOR
    // [BOT_238p6] Micro-Squad - COST:2
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Summon three 1/1 Microbots. Swaps each turn.
    // --------------------------------------------------------
}

void BoomsdayCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ SPELL - DRUID
    // [BOT_054] Biology Project - COST:1
    // - Set: BOOMSDAY, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Each player gains 2 Mana Crystals.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [BOT_404] Juicy Psychmelon - COST:4
    // - Set: BOOMSDAY, Rarity: Epic
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Draw a 7, 8, 9, and 10-Cost minion from your deck.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [BOT_419] Dendrologist - COST:2 [ATK:2/HP:3]
    // - Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a Treant,
    //       <b>Discover</b> a spell.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [BOT_420] Landscaping - COST:3
    // - Set: BOOMSDAY, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Summon two 2/2 Treants.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("EX1_tk9", 2));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("BOT_420", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [BOT_422] Tending Tauren - COST:6 [ATK:3/HP:4]
    // - Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Give your other minions +1/+1;
    //       or Summon two 2/2 Treants.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [BOT_423] Dreampetal Florist - COST:7 [ATK:4/HP:4]
    // - Set: BOOMSDAY, Rarity: Epic
    // --------------------------------------------------------
    // Text: At the end of your turn, reduce the Cost of
    //       a random minion in your hand by (7).
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [BOT_434] Flobbidinous Floop - COST:4 [ATK:3/HP:4]
    // - Set: BOOMSDAY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: While in your hand, this is a 3/4 copy
    //       of the last minion you played.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1

    // ------------------------------------------ SPELL - DRUID
    // [BOT_444] Floop's Glorious Gloop - COST:1
    // - Set: BOOMSDAY, Rarity: Legendary
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Whenever a minion dies this turn,
    //       gain 1 Mana Crystal this turn only.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [BOT_507] Gloop Sprayer - COST:7 [ATK:4/HP:4]
    // - Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a copy of each adjacent minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [BOT_523] Mulchmuncher - COST:9 [ATK:8/HP:8]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b>. Costs (1) less for each friendly Treant
    //       that died this game.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
}

void BoomsdayCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ SPELL - DRUID
    // [BOT_422a] Old Growth - COST:6
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: Give your other minions +1/+1.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [BOT_422b] New Growth - COST:6
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: Summon two 2/2 Treants.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [BOT_423e] Floral Arrangement - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: Costs (7) less.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [BOT_434e] Floopy - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: Transforming into recent minions.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [BOT_434e2] Floopy - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: 3/4.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [BOT_444e] Gloopy - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: Whenever a minion dies this turn,
    //       gain 1 Mana Crystal this turn only.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
}

void BoomsdayCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- SPELL - HUNTER
    // [BOT_033] Bomb Toss - COST:2
    // - Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 2 damage. Summon a 0/2 Goblin Bomb.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [BOT_034] Boommaster Flark - COST:7 [ATK:5/HP:5]
    // - Set: BOOMSDAY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon four 0/2 Goblin Bombs.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [BOT_035] Venomizer - COST:2 [ATK:2/HP:2]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Magnetic</b>
    //       <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - MODULAR = 1
    // - POISONOUS = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [BOT_038] Fireworks Tech - COST:2 [ATK:2/HP:1]
    // - Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly Mech +1/+1.
    //       If it has <b>Deathrattle</b>, trigger it.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [BOT_039] Necromechanic - COST:4 [ATK:3/HP:6]
    // - Set: BOOMSDAY, Rarity: Epic
    // --------------------------------------------------------
    // Text: Your <b>Deathrattles</b> trigger twice.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [BOT_251] Spider Bomb - COST:3 [ATK:2/HP:2]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Magnetic</b>
    //       <b>Deathrattle:</b> Destroy a random enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - MODULAR = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [BOT_402] Secret Plan - COST:1
    // - Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Discover</b> a <b>Secret</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [BOT_429] Flark's Boom-Zooka - COST:7
    // - Set: BOOMSDAY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Summon 3 minions from your deck.
    //       They attack enemy minions, then die.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1

    // ----------------------------------------- SPELL - HUNTER
    // [BOT_437] Goblin Prank - COST:2
    // - Set: BOOMSDAY, Rarity: Epic
    // --------------------------------------------------------
    // Text: Give a friendly minion +3/+3 and <b>Rush</b>.
    //       It dies at end of turn.
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [BOT_438] Cybertech Chip - COST:2
    // - Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give your minions "<b>Deathrattle:</b>
    //       Add a random Mech to your hand."
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
}

void BoomsdayCardsGen::AddHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- ENCHANTMENT - HUNTER
    // [BOT_038e] Primed - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [BOT_251e] Spider Bomb - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Destroy a random enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - MODULAR = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [BOT_438e] Chipped - COST:0
    // - Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a random Mech to your hand.
    // --------------------------------------------------------
}

void BoomsdayCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------- SPELL - MAGE
    // [BOT_101] Astral Rift - COST:2
    // - Set: BOOMSDAY, Rarity: Rare
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Add 2 random minions to your hand.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [BOT_103] Stargazer Luna - COST:3 [ATK:2/HP:4]
    // - Set: BOOMSDAY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you play the right-most card in your hand,
    //       draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [BOT_254] Unexpected Results - COST:3
    // - Set: BOOMSDAY, Rarity: Epic
    // --------------------------------------------------------
    // Text: Summon two random 2-Cost minions
    //       <i>(improved by <b>Spell Damage</b>)</i>.
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [BOT_256] Astromancer - COST:7 [ATK:5/HP:5]
    // - Set: BOOMSDAY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a random minion with
    //       Cost equal to your hand size.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [BOT_257] Luna's Pocket Galaxy - COST:7
    // - Set: BOOMSDAY, Rarity: Legendary
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Change the Cost of minions in your deck to (1).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1

    // ------------------------------------------- SPELL - MAGE
    // [BOT_453] Shooting Star - COST:1
    // - Set: BOOMSDAY, Rarity: Common
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Deal 1 damage to a minion and the minions next to it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeAdjacentTask>(EntityType::TARGET, true));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::STACK, 1, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("BOT_453", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [BOT_531] Celestial Emissary - COST:2 [ATK:2/HP:1]
    // - Race: Elemental, Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your next spell this turn
    //       has <b>Spell Damage +2</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [BOT_600] Research Project - COST:2
    // - Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: Each player draws 2 cards.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [BOT_601] Meteorologist - COST:6 [ATK:3/HP:3]
    // - Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> For each card in your hand,
    //       deal 1 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [BOT_604] Cosmic Anomaly - COST:4 [ATK:4/HP:3]
    // - Race: Elemental, Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Spell Damage +2</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
}

void BoomsdayCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------- ENCHANTMENT - MAGE
    // [BOT_257e] Starstruck - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: Costs (1).
    // --------------------------------------------------------

    // ------------------------------------- ENCHANTMENT - MAGE
    // [BOT_531e] Celestial Power - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: You have <b>Spell Damage +2</b>
    //       for your next spell this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ------------------------------------- ENCHANTMENT - MAGE
    // [BOT_531e2] Celestial Power - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: You have <b>Spell Damage +2</b>
    //       for your next spell this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
}

void BoomsdayCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- SPELL - PALADIN
    // [BOT_234] Shrink Ray - COST:5
    // - Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Set the Attack and Health of all minions to 1.
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [BOT_236] Crystalsmith Kangor - COST:2 [ATK:1/HP:2]
    // - Set: BOOMSDAY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>, <b>Lifesteal</b>
    //       Your healing is doubled.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DIVINE_SHIELD = 1
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [BOT_436] Prismatic Lens - COST:4
    // - Set: BOOMSDAY, Rarity: Epic
    // --------------------------------------------------------
    // Text: Draw a minion and a spell from your deck.
    //       Swap their Costs.
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [BOT_537] Mechano-Egg - COST:5 [ATK:0/HP:5]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon an 8/8 Robosaur.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [BOT_906] Glow-Tron - COST:1 [ATK:1/HP:3]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Magnetic</b>
    // --------------------------------------------------------
    // GameTag:
    // - MODULAR = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [BOT_908] Autodefense Matrix - COST:1
    // - Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When one of your minions is attacked,
    //       give it <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [BOT_909] Crystology - COST:1
    // - Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Draw two 1-Attack minions from your deck.
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [BOT_910] Glowstone Technician - COST:5 [ATK:3/HP:4]
    // - Set: BOOMSDAY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give all minions in your hand +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [BOT_911] Annoy-o-Module - COST:4 [ATK:2/HP:4]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Magnetic</b>
    //       <b>Divine Shield</b>
    //       <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // - MODULAR = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [BOT_912] Kangor's Endless Army - COST:7
    // - Set: BOOMSDAY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Resurrect 3 friendly Mechs.
    //       They keep any <b>Magnetic</b> upgrades.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // RefTag:
    // - MODULAR = 1
    // --------------------------------------------------------
}

void BoomsdayCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ---------------------------------- ENCHANTMENT - PALADIN
    // [BOT_436e] Swapped Cost - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: Cost swapped.
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [BOT_537t] Robosaur - COST:8 [ATK:8/HP:8]
    // - Race: Mechanical, Set: BOOMSDAY
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [BOT_910e] Light Infused - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [BOT_911e] Annoy-o-Module - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: <b>Taunt</b>, <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - MODULAR = 1
    // --------------------------------------------------------
}

void BoomsdayCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- MINION - PRIEST
    // [BOT_216] Omega Medic - COST:3 [ATK:3/HP:4]
    // - Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you have 10 Mana Crystals,
    //       restore 10 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [BOT_219] Extra Arms - COST:3
    // - Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give a minion +2/+2.
    //       Add 'More Arms!' to your hand that gives +2/+2.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [BOT_258] Zerek, Master Cloner - COST:6 [ATK:5/HP:5]
    // - Set: BOOMSDAY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> If you've cast any spells
    //       on this minion, resummon it.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [BOT_435] Cloning Device - COST:1
    // - Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Discover</b> a copy of a minion in your opponent's deck.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // - GEARS = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [BOT_509] Dead Ringer - COST:2 [ATK:2/HP:1]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Draw a <b>Deathrattle</b> minion
    //       from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [BOT_517] Topsy Turvy - COST:0
    // - Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: Swap a minion's Attack and Health.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [BOT_529] Power Word: Replicate - COST:5
    // - Set: BOOMSDAY, Rarity: Epic
    // --------------------------------------------------------
    // Text: Choose a friendly minion. Summon a 5/5 copy of it.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [BOT_558] Test Subject - COST:1 [ATK:0/HP:2]
    // - Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Return any spells you cast
    //       on this minion to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [BOT_566] Reckless Experimenter - COST:5 [ATK:4/HP:6]
    // - Set: BOOMSDAY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle</b> minions you play cost (3) less,
    //       but die at the end of the turn.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [BOT_567] Zerek's Cloning Gallery - COST:9
    // - Set: BOOMSDAY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Summon a 1/1 copy of each minion in your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
}

void BoomsdayCardsGen::AddPriestNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- ENCHANTMENT - PRIEST
    // [BOT_219e] Armed - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [BOT_219t] More Arms! - COST:3
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: Give a minion +2/+2.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [BOT_219te] More Armed - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [BOT_258e] Cloning Vector - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: Prepared to summon Zerek, Master Cloner
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [BOT_529e] Replicated - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: 5/5.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [BOT_558e] Stored Data - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: Storing spell.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [BOT_566e] Reckless Experiment - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: This minion will die a reckless death
    //       at the end of the turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [BOT_566e2] Reckless Experiment - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: Costs (3) less.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [BOT_567e] Cloned - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: 1/1.
    // --------------------------------------------------------
}

void BoomsdayCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ SPELL - ROGUE
    // [BOT_084] Violet Haze - COST:2
    // - Set: BOOMSDAY, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Add 2 random <b>Deathrattle</b> cards to your hand.
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [BOT_087] Academic Espionage - COST:4
    // - Set: BOOMSDAY, Rarity: Epic
    // --------------------------------------------------------
    // Text: Shuffle 10 cards from your opponent's class
    //       into your deck. They cost (1).
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [BOT_242] Myra's Unstable Element - COST:5
    // - Set: BOOMSDAY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Draw the rest of your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1

    // ----------------------------------------- MINION - ROGUE
    // [BOT_243] Myra Rotspring - COST:5 [ATK:4/HP:2]
    // - Set: BOOMSDAY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a <b>Deathrattle</b>
    //       minion. Also gain its <b>Deathrattle</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [BOT_283] Pogo-Hopper - COST:1 [ATK:1/HP:1]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain +2/+2 for each other
    //       Pogo-Hopper you played this game.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- WEAPON - ROGUE
    // [BOT_286] Necrium Blade - COST:3
    // - Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Trigger the <b>Deathrattle</b>
    //       of a random friendly minion.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [BOT_288] Lab Recruiter - COST:2 [ATK:3/HP:2]
    // - Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Shuffle 3 copies of a friendly
    //       minion into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [BOT_508] Necrium Vial - COST:5
    // - Set: BOOMSDAY, Rarity: Epic
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Trigger a friendly minion's <b>Deathrattle</b> twice.
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [BOT_565] Blightnozzle Crawler - COST:4 [ATK:2/HP:4]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 1/1 Ooze with
    //       <b>Poisonous</b> and <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - POISONOUS = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [BOT_576] Crazed Chemist - COST:5 [ATK:4/HP:4]
    // - Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Give a friendly minion +4 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
}

void BoomsdayCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------ ENCHANTMENT - ROGUE
    // [BOT_087e] Academic Espionage - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: Costs (1).
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [BOT_243e] Necroalchemy - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: Copied <b>Deathrattle</b> from {0}.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [BOT_283e] Kinetic Energy - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [BOT_565t] Radioactive Ooze - COST:1 [ATK:1/HP:1]
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    //       <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - POISONOUS = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [BOT_576e] Overcharged - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: +4 Attack.
    // --------------------------------------------------------
}

void BoomsdayCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- SPELL - SHAMAN
    // [BOT_093] Elementary Reaction - COST:2
    // - Set: BOOMSDAY, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Draw a card.
    //       Copy it if you played an Elemental last turn.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [BOT_099] Eureka! - COST:6
    // - Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon a copy of a random minion from your hand.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [BOT_245] The Storm Bringer - COST:6
    // - Set: BOOMSDAY, Rarity: Legendary
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Transform your minions into random
    //       <b>Legendary</b> minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1

    // ----------------------------------------- SPELL - SHAMAN
    // [BOT_246] Beakered Lightning - COST:0
    // - Set: BOOMSDAY, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Deal 1 damage to all minions. <b>Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [BOT_291] Storm Chaser - COST:4 [ATK:3/HP:4]
    // - Race: Elemental, Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a spell from your deck that
    //       costs (5) or more.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [BOT_407] Thunderhead - COST:4 [ATK:3/HP:6]
    // - Race: Elemental, Set: BOOMSDAY, Rarity: Epic
    // --------------------------------------------------------
    // Text: After you play a card with <b>Overload</b>,
    //       summon two 1/1 Sparks with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - OVERLOAD = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [BOT_411] Electra Stormsurge - COST:3 [ATK:3/HP:3]
    // - Race: Elemental, Set: BOOMSDAY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your next spell this turn casts twice.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [BOT_451] Voltaic Burst - COST:1
    // - Set: BOOMSDAY, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Summon two 1/1 Sparks with <b>Rush</b>.
    //       <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [BOT_533] Menacing Nimbus - COST:2 [ATK:2/HP:2]
    // - Race: Elemental, Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a random Elemental to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<RandomCardTask>(
        CardType::MINION, CardClass::INVALID, Race::ELEMENTAL));
    cardDef.power.AddPowerTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cards.emplace("BOT_533", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [BOT_543] Omega Mind - COST:2 [ATK:2/HP:3]
    // - Set: BOOMSDAY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you have 10 Mana Crystals,
    //       your spells have <b>Lifesteal</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
}

void BoomsdayCardsGen::AddShamanNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [BOT_411e] Electric - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: Your next spell this turn casts twice.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [BOT_411e2] Electricking - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: Your next spell this turn casts twice.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
}

void BoomsdayCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- SPELL - WARLOCK
    // [BOT_222] Spirit Bomb - COST:1
    // - Set: BOOMSDAY, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Deal 4 damage to a minion and your hero.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [BOT_224] Doubling Imp - COST:3 [ATK:2/HP:2]
    // - Race: Demon, Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a copy of this minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [BOT_226] Nethersoul Buster - COST:3 [ATK:1/HP:5]
    // - Race: Demon, Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain +1 Attack for each damage
    //       your hero has taken this turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [BOT_263] Soul Infusion - COST:1
    // - Set: BOOMSDAY, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Give the left-most minion in your hand +2/+2.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [BOT_433] Dr. Morrigan - COST:6 [ATK:5/HP:5]
    // - Set: BOOMSDAY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Swap this with a minion
    //       from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [BOT_443] Void Analyst - COST:2 [ATK:2/HP:2]
    // - Race: Demon, Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give all Demons in your hand +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [BOT_521] Ectomancy - COST:6
    // - Set: BOOMSDAY, Rarity: Epic
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Summon copies of all Demons you control.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [BOT_536] Omega Agent - COST:5 [ATK:4/HP:5]
    // - Set: BOOMSDAY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you have 10 Mana Crystals,
    //       summon 2 copies of this minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [BOT_568] The Soularium - COST:1
    // - Set: BOOMSDAY, Rarity: Legendary
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Draw 3 cards. At the end of your turn, discard them.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1

    // ---------------------------------------- SPELL - WARLOCK
    // [BOT_913] Demonic Project - COST:2
    // - Set: BOOMSDAY, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Each player transforms a random minion
    //       in their hand into a Demon.
    // --------------------------------------------------------
}

void BoomsdayCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [BOT_226e] Nethercharged - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: Attack increased.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [BOT_263e] Infused - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [BOT_443e] Well-Studied - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: +1/+1 from Void Analyst.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [BOT_568e] Fleeting Soul - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: Discards at the end of your turn.
    // --------------------------------------------------------
}

void BoomsdayCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- SPELL - WARRIOR
    // [BOT_042] Weapons Project - COST:2
    // - Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: Each player equips a 2/3 weapon and gains 6 Armor.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [BOT_059] Eternium Rover - COST:1 [ATK:1/HP:3]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever this minion takes damage, gain 2 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [BOT_067] Rocket Boots - COST:2
    // - Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion <b>Rush</b>. Draw a card.
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [BOT_069] The Boomship - COST:9
    // - Set: BOOMSDAY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Summon 3 random minions from your hand.
    //       Give them <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [BOT_104] Dyn-o-matic - COST:5 [ATK:3/HP:4]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 5 damage randomly split
    //       among all minions except Mechs.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [BOT_218] Security Rover - COST:6 [ATK:2/HP:6]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever this minion takes damage,
    //       summon a 2/3 Mech with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [BOT_237] Beryllium Nullifier - COST:7 [ATK:4/HP:8]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Magnetic</b>
    //       Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // - MODULAR = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [BOT_299] Omega Assembly - COST:1
    // - Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Discover</b> a Mech.
    //       If you have 10 Mana Crystals, keep all 3 cards.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // - GEARS = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [BOT_406] Supercollider - COST:5
    // - Set: BOOMSDAY, Rarity: Epic
    // --------------------------------------------------------
    // Text: After you attack a minion,
    //       force it to attack one of its neighbors.
    // --------------------------------------------------------
    // GameTag:
    // - FINISH_ATTACK_SPELL_ON_DAMAGE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
}

void BoomsdayCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- WEAPON - WARRIOR
    // [BOT_042t] Gearblade - COST:2
    // - Set: BOOMSDAY
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [BOT_067e] Rocket Boots - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: <b>Rush</b>.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [BOT_069e] Rocketeer - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: <b>Rush</b>.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [BOT_218t] Guard Bot - COST:2 [ATK:2/HP:3]
    // - Race: Mechanical, Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
}

void BoomsdayCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_020] Skaterbot - COST:1 [ATK:1/HP:1]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Magnetic</b>
    //       <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - MODULAR = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_021] Bronze Gatekeeper - COST:3 [ATK:1/HP:5]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Magnetic</b>
    //       <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - MODULAR = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_031] Goblin Bomb - COST:1 [ATK:0/HP:2]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 2 damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_050] Rusty Recycler - COST:5 [ATK:2/HP:6]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Lifesteal</b>
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_066] Mechanical Whelp - COST:6 [ATK:2/HP:2]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 7/7 Mechanical Dragon.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_079] Faithful Lumi - COST:1 [ATK:1/HP:1]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly Mech +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_083] Toxicologist - COST:2 [ATK:2/HP:2]
    // - Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your weapon +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("BOT_083e", EntityType::WEAPON));
    cards.emplace("BOT_083", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_098] Unpowered Mauler - COST:2 [ATK:2/HP:4]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Can only attack if you cast a spell this turn.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_102] Spark Drill - COST:6 [ATK:5/HP:1]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Deathrattle:</b> Add two 1/1 Sparks with
    //       <b>Rush</b> to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_107] Missile Launcher - COST:6 [ATK:4/HP:4]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Magnetic</b> At the end of your turn,
    //       deal 1 damage to all other characters.
    // --------------------------------------------------------
    // GameTag:
    // - MODULAR = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_267] Piloted Reaper - COST:4 [ATK:4/HP:3]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a random minion from
    //       your hand that costs (2) or less.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_270] Giggling Inventor - COST:6 [ATK:2/HP:1]
    // - Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two 1/2 Mechs with
    //       <b>Taunt</b> and <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_280] Holomancer - COST:5 [ATK:3/HP:3]
    // - Set: BOOMSDAY, Rarity: Epic
    // --------------------------------------------------------
    // Text: After your opponent plays a minion,
    //       summon a 1/1 copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_296] Omega Defender - COST:4 [ATK:2/HP:6]
    // - Set: BOOMSDAY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> If you have 10 Mana Crystals,
    //       gain +10 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_308] Spring Rocket - COST:3 [ATK:2/HP:1]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 2 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_309] Upgradeable Framebot - COST:2 [ATK:1/HP:5]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_312] Replicating Menace - COST:4 [ATK:3/HP:1]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Magnetic</b>
    //       <b>Deathrattle:</b> Summon three 1/1 Microbots.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - MODULAR = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_401] Weaponized Piñata - COST:4 [ATK:4/HP:3]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a random <b>Legendary</b>
    //       minion to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_413] Brainstormer - COST:3 [ATK:3/HP:1]
    // - Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain +1 Health for each spell
    //       in your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_414] Cloakscale Chemist - COST:2 [ATK:1/HP:2]
    // - Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //       <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // - STEALTH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_424] Mecha'thun - COST:10 [ATK:10/HP:10]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> If you have no cards in your
    //       deck, hand, and battlefield, destroy the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_431] Whirliglider - COST:2 [ATK:2/HP:1]
    // - Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 0/2 Goblin Bomb.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_445] Mecharoo - COST:1 [ATK:1/HP:1]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 1/1 Jo-E Bot.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_447] Crystallizer - COST:1 [ATK:1/HP:3]
    // - Set: BOOMSDAY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 5 damage to your hero.
    //       Gain 5 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_448] Damaged Stegotron - COST:6 [ATK:5/HP:12]
    // - Race: Mechanical, Faction: Horde, Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Deal 6 damage to this minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_511] Seaforium Bomber - COST:5 [ATK:5/HP:5]
    // - Set: BOOMSDAY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Shuffle a Bomb into your opponent's
    //       deck. When drawn, it explodes for 5 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_532] Explodinator - COST:4 [ATK:3/HP:2]
    // - Race: Mechanical, Faction: Horde, Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two 0/2 Goblin Bombs.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_534] Bull Dozer - COST:9 [ATK:9/HP:7]
    // - Race: Mechanical, Faction: Alliance, Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_535] Microtech Controller - COST:3 [ATK:2/HP:1]
    // - Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two 1/1 Microbots.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_538] Spark Engine - COST:2 [ATK:2/HP:1]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a 1/1 Spark with <b>Rush</b>
    //       to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_539] Arcane Dynamo - COST:6 [ATK:3/HP:4]
    // - Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a spell that
    //       costs (5) or more.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_540] E.M.P. Operative - COST:5 [ATK:3/HP:3]
    // - Set: BOOMSDAY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a Mech.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_544] Loose Specimen - COST:5 [ATK:6/HP:6]
    // - Race: Beast, Set: BOOMSDAY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 6 damage randomly split
    //       among other friendly minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_548] Zilliax - COST:5 [ATK:3/HP:2]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Magnetic</b> <b><b>Divine Shield</b>,
    //       <b>Taunt</b>, Lifesteal, Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DIVINE_SHIELD = 1
    // - LIFESTEAL = 1
    // - MODULAR = 1
    // - RUSH = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_550] Electrowright - COST:3 [ATK:3/HP:3]
    // - Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a spell that
    //       costs (5) or more, gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_552] Star Aligner - COST:7 [ATK:7/HP:7]
    // - Set: BOOMSDAY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control 3 minions with
    //       7 Health, deal 7 damage to all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_555] Harbinger Celestia - COST:4 [ATK:5/HP:6]
    // - Set: BOOMSDAY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Stealth</b> After your opponent plays a minion,
    //       become a copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - STEALTH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_559] Augmented Elekk - COST:3 [ATK:3/HP:4]
    // - Race: Beast, Set: BOOMSDAY, Rarity: Epic
    // --------------------------------------------------------
    // Text: Whenever you shuffle a card into a deck,
    //       shuffle in an extra copy.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_562] Coppertail Imposter - COST:4 [ATK:4/HP:4]
    // - Race: Mechanical, Faction: Horde, Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain <b>Stealth</b> until
    //       your next turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_563] Wargear - COST:5 [ATK:5/HP:5]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Magnetic</b>
    // --------------------------------------------------------
    // GameTag:
    // - MODULAR = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_573] Subject 9 - COST:5 [ATK:4/HP:4]
    // - Race: Beast, Set: BOOMSDAY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw 5 different <b>Secrets</b>
    //       from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_603] Steel Rager - COST:4 [ATK:5/HP:1]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_606] Kaboom Bot - COST:3 [ATK:2/HP:2]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 4 damage to a random
    //       enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_700] SN1P-SN4P - COST:3 [ATK:2/HP:3]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Magnetic</b>, <b>Echo</b>
    //       <b>Deathrattle:</b> Summon two 1/1 Microbots.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - ECHO = 1
    // - MODULAR = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_907] Galvanizer - COST:2 [ATK:1/HP:2]
    // - Race: Mechanical, Set: BOOMSDAY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Reduce the Cost of Mechs
    //       in your hand by (1).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_914] Whizbang the Wonderful - COST:4 [ATK:4/HP:5]
    // - Set: BOOMSDAY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: You start the game with one of
    //       Whizbang's Wonderful Decks!
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
}

void BoomsdayCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BOT_020e] Skaterbot - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - MODULAR = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BOT_021e] Bronze Gatekeeper - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - MODULAR = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BOT_035e] Venomizer - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>.
    // --------------------------------------------------------
    // GameTag:
    // - MODULAR = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BOT_039e] Necromechanical - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: Your <b>Deathrattles</b> trigger twice.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_066t] Mechanical Dragon - COST:7 [ATK:7/HP:7]
    // - Race: Mechanical, Set: BOOMSDAY
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BOT_079e] Illuminated - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BOT_083e] Toxic - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("BOT_083e"));
    cards.emplace("BOT_083e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BOT_101e2] Warcried - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_102t] Spark - COST:1 [ATK:1/HP:1]
    // - Race: Elemental, Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BOT_107e] Missile Launcher - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: When your turn ends,
    //       deal 1 damage to other characters.
    // --------------------------------------------------------
    // GameTag:
    // - MODULAR = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BOT_234e] Shrink Ray - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: 1/1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BOT_237e] Beryllium Nullifier - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // - MODULAR = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BOT_238e] Boomtastic - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: Your Mechs have <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BOT_238e2] Boomtastic - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: Dr. Boom is granting your Mechs <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_270t] Annoy-o-Tron - COST:2 [ATK:1/HP:2]
    // - Race: Mechanical, Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BOT_280e] Hologram - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: 1/1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BOT_296e] Omega Surge - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: +10 Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BOT_312e] Replicating Menace - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon three 1/1 Microbots.
    // --------------------------------------------------------
    // GameTag:
    // - MODULAR = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_312t] Microbot - COST:1 [ATK:1/HP:1]
    // - Race: Mechanical, Set: BOOMSDAY
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BOT_413e] Brain Power - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: Increased Health.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BOT_422ae] Old Growth - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BOT_437e] Slimed - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: +3/+3 and <b>Rush</b>.
    //       Dies a slimy death at the end of the turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [BOT_445t] Jo-E Bot - COST:1 [ATK:1/HP:1]
    // - Race: Mechanical, Set: BOOMSDAY
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [BOT_511t] Bomb - COST:5
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: <b>Casts When Drawn</b> You take 5 damage.
    // --------------------------------------------------------
    // GameTag:
    // - TOPDECK = 1
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTopdeckTask(
        std::make_shared<DamageTask>(EntityType::HERO, 5));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::HERO, 5));
    cards.emplace("BOT_511t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BOT_517e] Downside Up - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: Attack and Health have been swapped by Topsy Turvy.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BOT_543e] Mind Meld - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: Your spells have <b>Lifesteal</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BOT_548e] Zilliax - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: <b><b>Divine Shield</b>, <b>Taunt</b>,
    //       Lifesteal, Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - MODULAR = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BOT_550e] Electrified - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BOT_559e] Dealing - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // GameTag:
    // - ENCHANTMENT_INVISIBLE = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BOT_562e] Disguised - COST:0
    // - Faction: Horde, Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: <b>Stealthed</b> until your next turn.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BOT_563e] Wargear - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------
    // GameTag:
    // - MODULAR = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BOT_700e] SN1P-SN4P - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon two 1/1 Microbots.
    // --------------------------------------------------------
    // GameTag:
    // - MODULAR = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BOT_906e] Glow-Tron - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------
    // GameTag:
    // - MODULAR = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [BOT_907e] Galvanized - COST:0
    // - Set: BOOMSDAY
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------
}

void BoomsdayCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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
