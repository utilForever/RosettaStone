// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/CardSets/UldumCardsGen.hpp>
#include <Rosetta/Enchants/Effects.hpp>
#include <Rosetta/Enchants/Enchants.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddEnchantmentTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DamageTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/RandomTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/SummonTask.hpp>

using namespace RosettaStone::SimpleTasks;

namespace RosettaStone
{
void UldumCardsGen::AddHeroes(PowersType& powers, PlayReqsType& playReqs,
                              EntouragesType& entourages)
{
    (void)powers;
}

void UldumCardsGen::AddHeroPowers(PowersType& powers, PlayReqsType& playReqs,
                                  EntouragesType& entourages)
{
    // ------------------------------------- HERO_POWER - DRUID
    // [ULD_131p] Ossirian Tear (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Passive Hero Power</b>
    //       Your <b>Choose One</b> cards have both effects combined.
    // --------------------------------------------------------
    // GameTag:
    // - HIDE_STATS = 1
    // --------------------------------------------------------

    // ----------------------------------- HERO_POWER - WARLOCK
    // [ULD_140p] Tome of Origination (*) - COST:2
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Draw a card. It costs (0).
    // --------------------------------------------------------

    // ------------------------------------ HERO_POWER - HUNTER
    // [ULD_155p] Ramkahen Roar (*) - COST:2
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Give your minions +2 Attack.
    // --------------------------------------------------------

    // ------------------------------------ HERO_POWER - SHAMAN
    // [ULD_291p] Heart of Vir'naal (*) - COST:2
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Your <b>Battlecries</b> trigger twice this turn.
    // --------------------------------------------------------
    // RefTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------- HERO_POWER - ROGUE
    // [ULD_326p] Ancient Blades (*) - COST:2
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Equip a 3/2 Blade with
    //       <b>Immune</b> while attacking.
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------

    // ----------------------------------- HERO_POWER - PALADIN
    // [ULD_431p] Emperor Wraps (*) - COST:2
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Summon a 2/2 copy of a friendly minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------

    // -------------------------------------- HERO_POWER - MAGE
    // [ULD_433p] Ascendant Scroll (*) - COST:2
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Add a random Mage spell to your hand.
    //       It costs (2) less.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_HAND_NOT_FULL = 0
    // --------------------------------------------------------

    // ----------------------------------- HERO_POWER - WARRIOR
    // [ULD_711p3] Anraphet's Core (*) - COST:2
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Summon a 4/3 Golem.
    //       After your hero attacks, refresh this.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------

    // ------------------------------------ HERO_POWER - PRIEST
    // [ULD_724p] Obelisk's Eye (*) - COST:2
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Restore 3 Health.
    //       If you target a minion, also give it +3/+3.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
}

void UldumCardsGen::AddDruid(PowersType& powers, PlayReqsType& playReqs,
                             EntouragesType& entourages)
{
    // ------------------------------------------ SPELL - DRUID
    // [ULD_131] Untapped Potential - COST:1
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Quest:</b> End 4 turns with any unspent Mana.
    //       <b>Reward:</b> Ossirian Tear.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - QUEST = 1
    // - QUEST_PROGRESS_TOTAL = 4
    // - 676 = 1
    // - 839 = 1
    // - QUEST_REWARD_DATABASE_ID = 53499
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [ULD_133] Crystal Merchant - COST:2 [ATK:1/HP:4]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: If you have any unspent Mana at the end of your turn,
    //       draw a card.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [ULD_134] BEEEES!!! - COST:3 [ATK:1/HP:4]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: Choose a minion. Summon four 1/1 Bees that attack it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [ULD_135] Hidden Oasis - COST:6
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Choose One</b> - Summon a 6/6 Ancient with <b>Taunt</b>;
    //       or Restore 12 Health.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [ULD_136] Worthy Expedition - COST:1
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Discover</b> a <b>Choose One</b> card.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [ULD_137] Garden Gnome - COST:4 [ATK:2/HP:3]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a spell that
    //       costs (5) or more, summon two 2/2 Treants.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [ULD_138] Anubisath Defender - COST:5 [ATK:3/HP:5]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Taunt</b>. Costs (0) if you've cast a spell that
    //       costs (5) or more this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [ULD_139] Elise the Enlightened - COST:5 [ATK:5/HP:5]
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck has no duplicates,
    //       duplicate your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [ULD_273] Overflow - COST:7
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: Restore 5 Health to all characters. Draw 5 cards.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [ULD_292] Oasis Surger - COST:5 [ATK:3/HP:3]
    // - Race: Elemental, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b> <b>Choose One -</b> Gain +2/+2;
    //       or Summon a copy of this minion.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // - RUSH = 1
    // --------------------------------------------------------
}

void UldumCardsGen::AddDruidNonCollect(PowersType& powers,
                                       PlayReqsType& playReqs,
                                       EntouragesType& entourages)
{
    // ----------------------------------------- MINION - DRUID
    // [ULD_134t] Bee (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Uldum
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [ULD_135a] Befriend the Ancient (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Summon a 6/6 Ancient with <b>Taunt</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [ULD_135at] Vir'naal Ancient (*) - COST:6 [ATK:6/HP:6]
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [ULD_135b] Drink the Water (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Restore 12 Health.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [ULD_137t] Treant (*) - COST:2 [ATK:2/HP:2]
    // - Set: Uldum
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [ULD_288e] Buried (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Anka, the Buried made this 1/1.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [ULD_292a] Focused Burst (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Gain +2/+2.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [ULD_292ae] Focused (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [ULD_292b] Divide and Conquer (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Summon a copy of this minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 2
    // --------------------------------------------------------
}

void UldumCardsGen::AddHunter(PowersType& powers, PlayReqsType& playReqs,
                              EntouragesType& entourages)
{
    // ---------------------------------------- MINION - HUNTER
    // [ULD_151] Ramkahen Wildtamer - COST:3 [ATK:4/HP:3]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Copy a random Beast in your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [ULD_152] Pressure Plate - COST:2
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After your opponent casts a spell,
    //       destroy a random enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [ULD_154] Hyena Alpha - COST:4 [ATK:3/HP:3]
    // - Race: Beast, Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a <b>Secret</b>,
    //       summon two 2/2 Hyenas.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [ULD_155] Unseal the Vault - COST:1
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Quest:</b> Summon 20 minions.
    //       <b>Reward:</b> Ramkahen Roar.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - QUEST = 1
    // - QUEST_PROGRESS_TOTAL = 20
    // - 676 = 1
    // - 839 = 1
    // - QUEST_REWARD_DATABASE_ID = 53925
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [ULD_156] Dinotamer Brann - COST:7 [ATK:2/HP:4]
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck has no duplicates,
    //       summon King Krush.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [ULD_212] Wild Bloodstinger - COST:6 [ATK:6/HP:9]
    // - Race: Beast, Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a minion from
    //       your opponent's hand. Attack it.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [ULD_410] Scarlet Webweaver - COST:6 [ATK:5/HP:5]
    // - Race: Beast, Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Reduce the Cost of a random Beast
    //       in your hand by (5).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [ULD_429] Hunter's Pack - COST:3
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: Add a random Hunter Beast, <b>Secret</b>,
    //       and weapon to your hand.
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - HUNTER
    // [ULD_430] Desert Spear - COST:3 [ATK:1/HP:0]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: After your hero attacks,
    //       summon a 1/1 Locust with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 3
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [ULD_713] Swarm of Locusts - COST:6
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon seven 1/1 Locusts with <b>Rush</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
}

void UldumCardsGen::AddHunterNonCollect(PowersType& powers,
                                        PlayReqsType& playReqs,
                                        EntouragesType& entourages)
{
    // ---------------------------------------- MINION - HUNTER
    // [ULD_154t] Hyena (*) - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Set: Uldum
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [ULD_155e] Roar! (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [ULD_156t] Duke (*) - COST:5 [ATK:5/HP:5]
    // - Race: Beast, Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [ULD_156t2] Duchess (*) - COST:5 [ATK:5/HP:5]
    // - Race: Beast, Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [ULD_156t3] King Krush (*) - COST:9 [ATK:8/HP:8]
    // - Race: Beast, Faction: Neutral, Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CHARGE = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [ULD_410e] Weaved (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Costs (5) less.
    // --------------------------------------------------------
}

void UldumCardsGen::AddMage(PowersType& powers, PlayReqsType& playReqs,
                            EntouragesType& entourages)
{
    // ------------------------------------------- SPELL - MAGE
    // [ULD_216] Puzzle Box of Yogg-Saron - COST:10
    // - Faction: Neutral, Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: Cast 10 random spells <i>(targets chosen randomly).</i>
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [ULD_236] Tortollan Pilgrim - COST:8 [ATK:5/HP:5]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry</b>: <b>Discover</b> a copy of
    //       a spell in your deck and cast it with random targets.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [ULD_238] Reno the Relicologist - COST:6 [ATK:4/HP:6]
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck has no duplicates,
    //       deal 10 damage randomly split among all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [ULD_239] Flame Ward - COST:3
    // - Faction: Neutral, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After a minion attacks your hero,
    //       deal 3 damage to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [ULD_240] Arcane Flakmage - COST:2 [ATK:3/HP:2]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you play a <b>Secret</b>,
    //       deal 2 damage to all enemy minions.
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [ULD_293] Cloud Prince - COST:5 [ATK:4/HP:4]
    // - Race: Elemental, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a <b>Secret</b>,
    //       deal 6 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_FRIENDLY_SECRETS = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [ULD_329] Dune Sculptor - COST:3 [ATK:3/HP:3]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you cast a spell, add a random Mage
    //       minion to your hand.
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [ULD_433] Raid the Sky Temple - COST:1
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Quest:</b> Cast 10 spells.
    //       <b>Reward: </b>Ascendant Scroll.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - QUEST = 1
    // - QUEST_PROGRESS_TOTAL = 10
    // - 676 = 1
    // - 839 = 1
    // - QUEST_REWARD_DATABASE_ID = 53946
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [ULD_435] Naga Sand Witch - COST:5 [ATK:5/HP:5]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Change the Cost of spells
    //       in your hand to (5).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [ULD_726] Ancient Mysteries - COST:2
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: Draw a <b>Secret</b> from your deck. It costs (0).
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
}

void UldumCardsGen::AddMageNonCollect(PowersType& powers,
                                      PlayReqsType& playReqs,
                                      EntouragesType& entourages)
{
    // ------------------------------------- ENCHANTMENT - MAGE
    // [ULD_435e] Sandwitched (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Costs (5).
    // --------------------------------------------------------

    // ------------------------------------- ENCHANTMENT - MAGE
    // [ULD_726e] Translated (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Costs (0).
    // --------------------------------------------------------
}

void UldumCardsGen::AddPaladin(PowersType& powers, PlayReqsType& playReqs,
                               EntouragesType& entourages)
{
    // ---------------------------------------- SPELL - PALADIN
    // [ULD_143] Pharaoh's Blessing - COST:6
    // - Faction: Neutral, Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give a minion +4/+4, <b>Divine Shield</b>,
    //       and <b>Taunt</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [ULD_145] Brazen Zealot - COST:1 [ATK:2/HP:1]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you summon a minion, gain +1 Attack.
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [ULD_207] Ancestral Guardian - COST:4 [ATK:4/HP:2]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b> <b>Reborn</b>
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // - REBORN = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [ULD_217] Micro Mummy - COST:2 [ATK:1/HP:2]
    // - Race: Mechanical, Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Reborn</b> At the end of your turn, give
    //       another random friendly minion +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - REBORN = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [ULD_431] Making Mummies - COST:1
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Quest:</b> Play 5 <b>Reborn</b> minions.
    //       <b>Reward:</b> Emperor Wraps.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - QUEST = 1
    // - QUEST_PROGRESS_TOTAL = 5
    // - 676 = 1
    // - 839 = 1
    // - QUEST_REWARD_DATABASE_ID = 53908
    // --------------------------------------------------------
    // RefTag:
    // - REBORN = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [ULD_438] Salhet's Pride - COST:3 [ATK:3/HP:1]
    // - Race: Beast, Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Draw two 1-Health minions
    //       from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [ULD_439] Sandwasp Queen - COST:2 [ATK:3/HP:1]
    // - Race: Beast, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add two 2/1 Sandwasps to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [ULD_500] Sir Finley of the Sands - COST:2 [ATK:2/HP:3]
    // - Race: Murloc, Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck has no duplicates,
    //       <b>Discover</b> an upgraded Hero Power.
    // --------------------------------------------------------
    // Entourage: AT_132_DRUID, AT_132_HUNTER, AT_132_MAGE, AT_132_PALADIN,
    //            AT_132_PRIEST, AT_132_SHAMAN, AT_132_ROGUE, AT_132_WARLOCK,
    //            AT_132_WARRIOR
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [ULD_716] Tip the Scales - COST:8
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: Summon 7 Murlocs from your deck.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [ULD_728] Subdue - COST:2
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: Set a minion's Attack and Health to 1.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
}

void UldumCardsGen::AddPaladinNonCollect(PowersType& powers,
                                         PlayReqsType& playReqs,
                                         EntouragesType& entourages)
{
    // ---------------------------------- ENCHANTMENT - PALADIN
    // [ULD_143e] Pharaoh's Blessing (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: +4/+4, <b>Divine Shield</b>, and <b>Taunt</b>.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [ULD_145e] Zeal (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [ULD_431e] Emperor Wrapped (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: 2/2.
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [ULD_439t] Sandwasp (*) - COST:1 [ATK:2/HP:1]
    // - Race: Beast, Set: Uldum
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [ULD_716e2] Watched (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Stats changed to 3/3.
    // --------------------------------------------------------
}

void UldumCardsGen::AddPriest(PowersType& powers, PlayReqsType& playReqs,
                              EntouragesType& entourages)
{
    // ---------------------------------------- MINION - PRIEST
    // [ULD_262] High Priest Amet - COST:4 [ATK:2/HP:7]
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever you summon a minion,
    //       set its Health equal to this minion's.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [ULD_265] Embalming Ritual - COST:1
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion <b>Reborn</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - REBORN = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [ULD_266] Grandmummy - COST:2 [ATK:1/HP:2]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Reborn</b> <b>Deathrattle:</b> Give a random
    //       friendly minion +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - REBORN = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [ULD_268] Psychopomp - COST:4 [ATK:3/HP:1]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a random friendly minion
    //       that died this game. Give it <b>Reborn</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - REBORN = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [ULD_269] Wretched Reclaimer - COST:3 [ATK:3/HP:3]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a friendly minion,
    //       then return it to life with full Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [ULD_270] Sandhoof Waterbearer - COST:5 [ATK:5/HP:5]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: At the end of your turn, restore 5 Health
    //       to a damaged friendly character.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [ULD_272] Holy Ripple - COST:2
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal $1 damage to all enemies. Restore 1 Health
    //       to all friendly characters.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [ULD_714] Penance - COST:2
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b> Deal 3 damage to a_minion.
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [ULD_718] Plague of Death - COST:9
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Silence</b> and destroy all minions.
    // --------------------------------------------------------
    // GameTag:
    // - SILENCE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [ULD_724] Activate the Obelisk - COST:1
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Quest:</b> Restore 15 Health.
    //       <b>Reward:</b> Obelisk's Eye.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - QUEST = 1
    // - QUEST_PROGRESS_TOTAL = 15
    // - 676 = 1
    // - 839 = 1
    // - QUEST_REWARD_DATABASE_ID = 54750
    // --------------------------------------------------------
}

void UldumCardsGen::AddPriestNonCollect(PowersType& powers,
                                        PlayReqsType& playReqs,
                                        EntouragesType& entourages)
{
    // ----------------------------------- ENCHANTMENT - PRIEST
    // [ULD_262e] Amet's Blessing (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Health changed.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [ULD_266e] Grandmummy's Blessing (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - REBORN = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [ULD_724e] Obelisk's Gaze (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------
}

void UldumCardsGen::AddRogue(PowersType& powers, PlayReqsType& playReqs,
                             EntouragesType& entourages)
{
    // ----------------------------------------- MINION - ROGUE
    // [ULD_186] Pharaoh Cat - COST:1 [ATK:1/HP:2]
    // - Race: Beast, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a random <b>Reborn</b> minion
    //       to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - REBORN = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [ULD_231] Whirlkick Master - COST:2 [ATK:1/HP:2]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: Whenever you play a <b>Combo</b> card,
    //       add a random <b>Combo</b> card to your hand.
    // --------------------------------------------------------
    // RefTag:
    // - COMBO = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [ULD_280] Sahket Sapper - COST:4 [ATK:4/HP:4]
    // - Race: Pirate, Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Return a random enemy minion
    //       to your opponent's hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- WEAPON - ROGUE
    // [ULD_285] Hooked Scimitar - COST:3 [ATK:2/HP:0]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Gain +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - COMBO = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [ULD_286] Shadow of Death - COST:4
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: Choose a minion. Shuffle 3 'Shadows' into your deck
    //       that summon a copy when drawn.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [ULD_288] Anka, the Buried - COST:5 [ATK:5/HP:5]
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Change each <b>Deathrattle</b>
    //       minion in your hand into a 1/1 that costs (1).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [ULD_326] Bazaar Burglary - COST:1
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Quest:</b> Add 4 cards from other classes to your hand.
    //       <b>Reward: </b>Ancient Blades.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - QUEST = 1
    // - QUEST_PROGRESS_TOTAL = 4
    // - 676 = 1
    // - 839 = 1
    // - QUEST_REWARD_DATABASE_ID = 54312
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [ULD_327] Bazaar Mugger - COST:5 [ATK:3/HP:5]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b> <b>Battlecry:</b> Add a random minion
    //       from another class to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [ULD_328] Clever Disguise - COST:2
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: Add 2 random spells from another class to your hand.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [ULD_715] Plague of Madness - COST:1
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: Each player equips a 2/2 Knife with <b>Poisonous</b>.
    // --------------------------------------------------------
    // GameTag:
    // - 858 = 2451
    // --------------------------------------------------------
    // RefTag:
    // - POISONOUS = 1
    // --------------------------------------------------------
}

void UldumCardsGen::AddRogueNonCollect(PowersType& powers,
                                       PlayReqsType& playReqs,
                                       EntouragesType& entourages)
{
    // ------------------------------------ ENCHANTMENT - ROGUE
    // [ULD_285e] Polished (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [ULD_286t] Shadow (*) - COST:4
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Casts When Drawn</b> Summon a {0}.
    // --------------------------------------------------------
    // GameTag:
    // - TOPDECK = 1
    // --------------------------------------------------------
    // RefTag:
    // - CASTSWHENDRAWN = 1
    // --------------------------------------------------------

    // ----------------------------------------- WEAPON - ROGUE
    // [ULD_326t] Mirage Blade (*) - COST:2 [ATK:3/HP:0]
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Your hero is <b>Immune</b> while attacking.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------

    // ----------------------------------------- WEAPON - ROGUE
    // [ULD_715t] Plagued Knife (*) - COST:1 [ATK:2/HP:0]
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - POISONOUS = 1
    // --------------------------------------------------------
}

void UldumCardsGen::AddShaman(PowersType& powers, PlayReqsType& playReqs,
                              EntouragesType& entourages)
{
    // ---------------------------------------- MINION - SHAMAN
    // [ULD_158] Sandstorm Elemental - COST:2 [ATK:2/HP:2]
    // - Race: Elemental, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage to all enemy minions.
    // <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [ULD_169] Mogu Fleshshaper - COST:7 [ATK:3/HP:4]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b>. Costs (1) less for each minion
    //       on the battlefield.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [ULD_170] Weaponized Wasp - COST:3 [ATK:3/HP:3]
    // - Race: Beast, Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a <b>Lackey</b>,
    //       deal 3 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ88 = 0
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [ULD_171] Totemic Surge - COST:0
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: Give your Totems +2 Attack.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [ULD_172] Plague of Murlocs - COST:3
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: Transform all minions into random Murlocs.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [ULD_173] Vessina - COST:4 [ATK:2/HP:6]
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: While you're <b>Overloaded</b>,
    //       your other minions have +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [ULD_181] Earthquake - COST:7
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 5 damage to all minions,
    //       then deal 2 damage to all minions.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [ULD_276] EVIL Totem - COST:2 [ATK:0/HP:2]
    // - Race: Totem, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       add a <b>Lackey</b> to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - 1359 = 1
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [ULD_291] Corrupt the Waters - COST:1
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Quest:</b> Play 6 <b>Battlecry</b> cards.
    //       <b>Reward:</b> Heart of Vir'naal.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - QUEST = 1
    // - QUEST_PROGRESS_TOTAL = 6
    // - 676 = 1
    // - 839 = 1
    // - QUEST_REWARD_DATABASE_ID = 54370
    // --------------------------------------------------------
    // RefTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - SHAMAN
    // [ULD_413] Splitting Axe - COST:4 [ATK:3/HP:0]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon copies of your Totems.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void UldumCardsGen::AddShamanNonCollect(PowersType& powers,
                                        PlayReqsType& playReqs,
                                        EntouragesType& entourages)
{
    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [ULD_171e] Big Surge (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [ULD_173e] Vessina's Devotion (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Vessina is granting this minion +2_Attack.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [ULD_433e] Cheat Sheet (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------
}

void UldumCardsGen::AddWarlock(PowersType& powers, PlayReqsType& playReqs,
                               EntouragesType& entourages)
{
    // ---------------------------------------- SPELL - WARLOCK
    // [ULD_140] Supreme Archaeology - COST:1
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Quest:</b> Draw 20 cards.
    //       <b>Reward:</b> Tome of Origination.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - QUEST = 1
    // - QUEST_PROGRESS_TOTAL = 20
    // - 676 = 1
    // - 839 = 1
    // - QUEST_REWARD_DATABASE_ID = 53740
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [ULD_160] Sinister Deal - COST:1
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Discover</b> a <b>Lackey</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // - 1359 = 1
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [ULD_161] Neferset Thrasher - COST:3 [ATK:4/HP:5]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever this attacks, deal 3 damage to your hero.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [ULD_162] EVIL Recruiter - COST:3 [ATK:3/HP:3]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a friendly <b>Lackey</b>
    //       to summon a 5/5 Demon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - 1359 = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ87 = 0
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [ULD_163] Expired Merchant - COST:2 [ATK:2/HP:1]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Discard your highest Cost card.
    //       <b>Deathrattle:</b> Add 2 copies of it to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [ULD_165] Riftcleaver - COST:6 [ATK:7/HP:5]
    // - Race: Demon, Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a minion.
    //       Your hero takes damage equal to its Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [ULD_167] Diseased Vulture - COST:4 [ATK:3/HP:5]
    // - Race: Beast, Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: After your hero takes damage on your turn,
    //       summon a random 3-Cost minion.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [ULD_168] Dark Pharaoh Tekahn - COST:5 [ATK:4/HP:4]
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> For the rest of the game,
    //       your <b>Lackeys</b> are 4/4.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [ULD_324] Impbalming - COST:4
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: Destroy a minion. Shuffle 3 Worthless Imps into your deck.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [ULD_717] Plague of Flames - COST:1
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: Destroy all your minions.
    //       For each one, destroy a random enemy minion.
    // --------------------------------------------------------
}

void UldumCardsGen::AddWarlockNonCollect(PowersType& powers,
                                         PlayReqsType& playReqs,
                                         EntouragesType& entourages)
{
    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [ULD_140e] Origination (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Costs (0).
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [ULD_162t] EVIL Demon (*) - COST:5 [ATK:5/HP:5]
    // - Race: Demon, Set: Uldum
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [ULD_163e] Expired Goods (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Discarded {0}.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [ULD_168e] Lackey Empowerment (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Your <b>Lackeys</b> are 4/4.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [ULD_168e2] Lackey Empowerment (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Your <b>Lackeys</b> are 4/4.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [ULD_168e3] Lackey Empowerment (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: 4/4.
    // --------------------------------------------------------
    // GameTag:
    // - ENCHANTMENT_INVISIBLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [ULD_324t] Worthless Imp (*) - COST:1 [ATK:1/HP:1]
    // - Race: Demon, Set: Uldum
    // --------------------------------------------------------
}

void UldumCardsGen::AddWarrior(PowersType& powers, PlayReqsType& playReqs,
                               EntouragesType& entourages)
{
    // --------------------------------------- MINION - WARRIOR
    // [ULD_195] Frightened Flunky - COST:2 [ATK:2/HP:2]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> <b>Discover</b> a <b>Taunt</b> minion.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [ULD_206] Restless Mummy - COST:4 [ATK:3/HP:2]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b> <b>Reborn</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // - REBORN = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [ULD_253] Tomb Warden - COST:8 [ATK:3/HP:6]
    // - Race: Mechanical, Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Summon a copy of this minion.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [ULD_256] Into the Fray - COST:1
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give all <b>Taunt</b> minions in your hand +2/+2.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [ULD_258] Armagedillo - COST:6 [ATK:4/HP:7]
    // - Race: Beast, Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Taunt</b> At the end of your turn,
    //       give all <b>Taunt</b> minions in your hand +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [ULD_707] Plague of Wrath - COST:5
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: Destroy all damaged minions.
    // --------------------------------------------------------
    // GameTag:
    // - 858 = 41425
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [ULD_708] Livewire Lance - COST:3 [ATK:2/HP:0]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: After your Hero attacks,
    //       add a <b>Lackey</b> to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - 1359 = 1
    // --------------------------------------------------------
    // RefTag:
    // - MARK_OF_EVIL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [ULD_709] Armored Goon - COST:6 [ATK:6/HP:7]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever your hero attacks, gain 5 Armor.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [ULD_711] Hack the System - COST:1
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Quest:</b> Attack 5 times with your hero.
    //       <b>Reward:</b> Anraphet's Core.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - QUEST = 1
    // - QUEST_PROGRESS_TOTAL = 5
    // - 676 = 1
    // - 839 = 1
    // - QUEST_REWARD_DATABASE_ID = 54416
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [ULD_720] Bloodsworn Mercenary - COST:3 [ATK:3/HP:3]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry</b>: Choose a damaged friendly minion.
    //       Summon a copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_DAMAGED_TARGET = 0
    // --------------------------------------------------------
}

void UldumCardsGen::AddWarriorNonCollect(PowersType& powers,
                                         PlayReqsType& playReqs,
                                         EntouragesType& entourages)
{
    // --------------------------------------- MINION - WARRIOR
    // [ULD_711t] Stone Golem (*) - COST:3 [ATK:4/HP:3]
    // - Set: Uldum
    // --------------------------------------------------------
}

void UldumCardsGen::AddNeutral(PowersType& powers, PlayReqsType& playReqs,
                               EntouragesType& entourages)
{
    Power power;

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_003] Zephrys the Great - COST:2 [ATK:3/HP:2]
    // - Race: Elemental, Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck has no duplicates,
    //       wish for the perfect card.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_157] Questing Explorer - COST:2 [ATK:2/HP:3]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a <b>Quest</b>,
    //       draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - QUEST = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_174] Serpent Egg - COST:2 [ATK:0/HP:3]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 3/4 Sea Serpent.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(
        std::make_shared<SummonTask>("ULD_174t", SummonSide::DEATHRATTLE));
    powers.emplace("ULD_174", power);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_177] Octosari - COST:8 [ATK:8/HP:8]
    // - Race: Beast, Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Draw 8 cards.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_178] Siamat - COST:7 [ATK:6/HP:6]
    // - Race: Elemental, Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain 2 of <b>Rush</b>,
    //       <b>Taunt</b>, <b>Divine Shield</b>, or
    //       <b>Windfury</b> <i>(your choice).</i>
    // --------------------------------------------------------
    // Entourage: ULD_178a2, ULD_178a, ULD_178a3, ULD_178a4
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - WINDFURY = 1
    // - TAUNT = 1
    // - DIVINE_SHIELD = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_179] Phalanx Commander - COST:5 [ATK:4/HP:5]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: Your <b>Taunt</b> minions have +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // - 1429 = 58385
    // - TECH_LEVEL = 3
    // - 1456 = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_180] Sunstruck Henchman - COST:4 [ATK:6/HP:5]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       this has a 50% chance to fall asleep.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_182] Spitting Camel - COST:2 [ATK:2/HP:4]
    // - Race: Beast, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: At the end of your turn, deal 1 damage
    //       to another random friendly minion.
    // --------------------------------------------------------
    power.ClearData();
    power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    power.GetTrigger()->tasks = {
        std::make_shared<RandomTask>(EntityType::MINIONS_NOSOURCE, 1),
        std::make_shared<DamageTask>(EntityType::STACK, 1)
    };
    powers.emplace("ULD_182", power);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_183] Anubisath Warbringer - COST:9 [ATK:9/HP:6]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give all minions in your hand +3/+3.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_184] Kobold Sandtrooper - COST:2 [ATK:2/HP:1]
    // - Faction: Alliance, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 3 damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 3));
    powers.emplace("ULD_184", power);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_185] Temple Berserker - COST:2 [ATK:1/HP:2]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Reborn</b> Has +2 Attack while damaged.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // - REBORN = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_188] Golden Scarab - COST:3 [ATK:2/HP:2]
    // - Race: Beast, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b><b>Battlecry:</b> Discover</b> a 4-Cost card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_189] Faceless Lurker - COST:5 [ATK:3/HP:3]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Double this minion's Health.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_190] Pit Crocolisk - COST:8 [ATK:5/HP:6]
    // - Race: Beast, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 5 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_191] Beaming Sidekick - COST:1 [ATK:1/HP:2]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion +2 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("ULD_191e", EntityType::TARGET));
    powers.emplace("ULD_191", power);
    playReqs.emplace("ULD_191",
                     PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                               { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                               { PlayReq::REQ_MINION_TARGET, 0 } });

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_193] Living Monument - COST:10 [ATK:10/HP:10]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_194] Wasteland Scorpid - COST:7 [ATK:3/HP:9]
    // - Race: Beast, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - POISONOUS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_196] Neferset Ritualist - COST:2 [ATK:2/HP:3]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore adjacent minions
    //       to full Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_197] Quicksand Elemental - COST:2 [ATK:3/HP:2]
    // - Race: Elemental, Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give all enemy minions -2 Attack
    //       this turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_198] Conjured Mirage - COST:4 [ATK:3/HP:10]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b> At the start of your turn,
    //       shuffle this minion into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_205] Candletaker - COST:3 [ATK:3/HP:2]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Reborn</b>
    // --------------------------------------------------------
    // GameTag:
    // - REBORN = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_208] Khartut Defender - COST:6 [ATK:3/HP:4]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>, <b>Reborn</b> <b>Deathrattle:</b>
    //       Restore 3 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // - REBORN = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_209] Vulpera Scoundrel - COST:3 [ATK:2/HP:3]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry</b>: <b>Discover</b> a spell or
    //       pick a mystery choice.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_214] Generous Mummy - COST:3 [ATK:5/HP:4]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Reborn</b> Your opponent's cards cost (1) less.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // - REBORN = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_215] Wrapped Golem - COST:7 [ATK:7/HP:5]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Reborn</b> At the end of your turn,
    //       summon a 1/1 Scarab with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - REBORN = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_229] Mischief Maker - COST:3 [ATK:3/HP:3]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Swap the top card of your deck
    //       with your opponent's.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_250] Infested Goblin - COST:3 [ATK:2/HP:3]
    // - Set: Uldum, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b> <b>Deathrattle:</b> Add two 1/1 Scarabs
    //       with <b>Taunt</b> to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_271] Injured Tol'vir - COST:2 [ATK:2/HP:6]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Deal 3 damage to this minion.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<DamageTask>(EntityType::SOURCE, 3));
    powers.emplace("ULD_271", power);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_274] Wasteland Assassin - COST:5 [ATK:4/HP:2]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b> <b>Reborn</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // - REBORN = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_275] Bone Wraith - COST:4 [ATK:2/HP:5]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b> <b>Reborn</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - REBORN = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_282] Jar Dealer - COST:1 [ATK:1/HP:1]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a random 1-Cost minion
    //       to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_289] Fishflinger - COST:2 [ATK:3/HP:2]
    // - Race: Murloc, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a random Murloc
    //       to each player's hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_290] History Buff - COST:3 [ATK:3/HP:4]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: Whenever you play a minion,
    //       give a random minion in your hand +1/+1.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_304] King Phaoris - COST:10 [ATK:5/HP:5]
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> For each spell in your hand,
    //       summon a random minion of the same Cost.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_309] Dwarven Archaeologist - COST:2 [ATK:2/HP:3]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: After you <b>Discover</b> a card,
    //       reduce its cost by (1).
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_450] Vilefiend - COST:2 [ATK:2/HP:2]
    // - Race: Demon, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    powers.emplace("ULD_450", power);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_702] Mortuary Machine - COST:5 [ATK:8/HP:8]
    // - Race: Mechanical, Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: After your opponent plays a minion,
    //       give it <b>Reborn</b>.
    // --------------------------------------------------------
    // RefTag:
    // - REBORN = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_703] Desert Obelisk - COST:5 [ATK:0/HP:5]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: If you control 3 of these at the end of your turn,
    //       deal 5 damage to a random enemy.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_705] Mogu Cultist - COST:1 [ATK:1/HP:1]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your board is full of Mogu Cultists,
    //       sacrifice them all and summon Highkeeper Ra.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_706] Blatant Decoy - COST:6 [ATK:5/HP:5]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Each player summons
    //       the lowest Cost minion from their hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_712] Bug Collector - COST:2 [ATK:2/HP:1]
    // - Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 1/1 Locust with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(std::make_shared<SummonTask>("ULD_430t"));
    powers.emplace("ULD_712", power);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_719] Desert Hare - COST:3 [ATK:1/HP:1]
    // - Race: Beast, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two 1/1 Desert Hares.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_721] Colossus of the Moon - COST:10 [ATK:10/HP:10]
    // - Set: Uldum, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b> <b>Reborn</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DIVINE_SHIELD = 1
    // - REBORN = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_723] Murmy - COST:1 [ATK:1/HP:1]
    // - Race: Murloc, Set: Uldum, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Reborn</b>
    // --------------------------------------------------------
    // GameTag:
    // - REBORN = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_727] Body Wrapper - COST:4 [ATK:4/HP:4]
    // - Set: Uldum, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a friendly minion
    //       that died this game. Shuffle it into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - USE_DISCOVER_VISUALS = 1
    // --------------------------------------------------------
}

void UldumCardsGen::AddNeutralNonCollect(PowersType& powers,
                                         PlayReqsType& playReqs,
                                         EntouragesType& entourages)
{
    Power power;

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_174t] Sea Serpent (*) - COST:3 [ATK:3/HP:4]
    // - Race: Beast, Set: Uldum
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    powers.emplace("ULD174t", power);

    // ---------------------------------------- SPELL - NEUTRAL
    // [ULD_178a] Siamat's Wind (*) - COST:0
    // - Faction: Neutral, Set: Uldum
    // --------------------------------------------------------
    // Text: Give Siamat <b>Windfury</b>.
    // --------------------------------------------------------
    // GameTag:
    // - HIDE_STATS = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - WINDFURY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [ULD_178a2] Siamat's Shield (*) - COST:0
    // - Faction: Neutral, Set: Uldum
    // --------------------------------------------------------
    // Text: Give Siamat <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - HIDE_STATS = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [ULD_178a3] Siamat's Heart (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Give Siamat <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - HIDE_STATS = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [ULD_178a4] Siamat's Speed (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Give Siamat <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - HIDE_STATS = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_179e] Commanded (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Phalanx Commander is granting this +2 Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_183e] Anubisath Power (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: +3/+3.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_185e] Enraged (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_189e] Bravery (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Doubled Health.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_191e] Assisting! (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: +2 Health.
    // --------------------------------------------------------
    power.ClearData();
    power.AddEnchant(Enchants::GetEnchantFromText("ULD_191e"));
    powers.emplace("ULD_191e", power);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_197e] Stuck! (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: -2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [ULD_209t] Mystery Choice! (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Add a random spell to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - HIDE_STATS = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_214e] Charity (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_215t] Scarab (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_217e] Microwrapped (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Attack increased.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_256e] Frayed (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: +2/+2 from Into the Fray.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_258e] Tough (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Increased stats from Armagedillo.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_290e] Erudite (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Increased stats from History Buff.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_291pe] Heart of Vir'naal (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Your <b>Battlecries</b> trigger twice this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_309e] Archaelogical Study (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_430t] Locust (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(nullptr);
    powers.emplace("ULD_430t", power);

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_616] Titanic Lackey (*) - COST:1 [ATK:1/HP:1]
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion +2 Health
    //       and <b>Taunt</b>.
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
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_616e] Hardened (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: +2 Health and <b>Taunt</b>.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ULD_705t] Highkeeper Ra (*) - COST:10 [ATK:20/HP:20]
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       deal 20 damage to all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ULD_728e] Subdued (*) - COST:0
    // - Set: Uldum
    // --------------------------------------------------------
    // Text: 1/1.
    // --------------------------------------------------------
}

void UldumCardsGen::AddAll(PowersType& powers, PlayReqsType& playReqs,
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
