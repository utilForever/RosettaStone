// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/CardSets/UngoroCardsGen.hpp>
#include <Rosetta/PlayMode/Cards/CardPowers.hpp>

namespace RosettaStone::PlayMode
{
void UngoroCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void UngoroCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------ HERO_POWER - HUNTER
    // [UNG_917t1] Dinomancy (*) - COST:2
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Give a Beast +2/+2.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_TARGET_WITH_RACE = 20
    // --------------------------------------------------------

    // ----------------------------------- HERO_POWER - NEUTRAL
    // [UNG_934t2] DIE, INSECT! (*) - COST:2
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Deal 8 damage to a random enemy.
    // --------------------------------------------------------
}

void UngoroCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - DRUID
    // [UNG_078] Tortollan Forager - COST:2 [ATK:2/HP:2]
    // - Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a random minion with 5 or
    //       more Attack to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [UNG_086] Giant Anaconda - COST:7 [ATK:5/HP:3]
    // - Race: Beast, Set: Ungoro, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a minion from your hand
    //       with 5 or more Attack.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [UNG_100] Verdant Longneck - COST:5 [ATK:5/HP:4]
    // - Race: Beast, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Adapt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - ADAPT = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [UNG_101] Shellshifter - COST:4 [ATK:3/HP:3]
    // - Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Choose One - </b>Transform into a 5/3
    //       with <b>Stealth</b>; or a 3/5 with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // - STEALTH = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [UNG_103] Evolving Spores - COST:4
    // - Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Adapt</b> your minions.
    // --------------------------------------------------------
    // RefTag:
    // - ADAPT = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [UNG_108] Earthen Scales - COST:2
    // - Faction: Neutral, Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give a friendly minion +1/+1,
    //       then gain Armor equal to its Attack.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("UNG_108e", EntityType::TARGET));
    cardDef.power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::TARGET, GameTag::ATK));
    cardDef.power.AddPowerTask(std::make_shared<ArmorTask>(0, false, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_FRIENDLY_TARGET, 0 } };
    cards.emplace("UNG_108", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [UNG_109] Elder Longneck - COST:3 [ATK:5/HP:1]
    // - Race: Beast, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a minion
    //       with 5 or more Attack, <b>Adapt</b>.
    // --------------------------------------------------------
    // Entourage: UNG_999t10, UNG_999t2, UNG_999t3, UNG_999t4,
    //            UNG_999t5, UNG_999t6, UNG_999t7, UNG_999t8,
    //            UNG_999t13, UNG_999t14
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - ADAPT = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [UNG_111] Living Mana - COST:5
    // - Set: Ungoro, Rarity: Epic
    // --------------------------------------------------------
    // Text: Transform your Mana Crystals into 2/2 minions.
    //       Recover the mana when they die.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [UNG_116] Jungle Giants - COST:1
    // - Set: Ungoro, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Quest:</b> Summon 5 minions with 5 or more Attack.
    //       <b>Reward:</b> Barnabus.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - QUEST = 1
    // - QUEST_PROGRESS_TOTAL = 5
    // - 676 = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [UNG_852] Tyrantus - COST:10 [ATK:12/HP:12]
    // - Race: Beast, Set: Ungoro, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("UNG_852", cardDef);
}

void UngoroCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ SPELL - DRUID
    // [UNG_101a] Raptor Form (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: +2 Attack and <b>Stealth</b>
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [UNG_101b] Direhorn Form (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: +2 Health and <b>Taunt</b>.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [UNG_101t] Shellshifter (*) - COST:4 [ATK:5/HP:3]
    // - Race: Beast, Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [UNG_101t2] Shellshifter (*) - COST:4 [ATK:3/HP:5]
    // - Race: Beast, Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [UNG_101t3] Shellshifter (*) - COST:4 [ATK:5/HP:5]
    // - Race: Beast, Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //       <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - STEALTH = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [UNG_108e] It's All Scaley... (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("UNG_108e"));
    cards.emplace("UNG_108e", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [UNG_111t1] Mana Treant (*) - COST:2 [ATK:2/HP:2]
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Gain an empty Mana Crystal.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [UNG_116t] Barnabus the Stomper (*) - COST:5 [ATK:8/HP:8]
    // - Race: Beast, Set: Ungoro
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Reduce the Cost of minions
    //       in your deck to (0).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [UNG_116te] Romper Stompers (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: Costs (0).
    // --------------------------------------------------------
}

void UngoroCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - HUNTER
    // [UNG_800] Terrorscale Stalker - COST:3 [ATK:3/HP:3]
    // - Faction: Neutral, Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Trigger a friendly minion's
    //       <b>Deathrattle</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_WITH_DEATHRATTLE = 0
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [UNG_910] Grievous Bite - COST:2
    // - Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 2 damage to a minion and 1 damage to adjacent ones.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [UNG_912] Jeweled Macaw - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a random Beast to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomCardTask>(CardType::MINION, CardClass::INVALID, Race::BEAST));
    cardDef.power.AddPowerTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cards.emplace("UNG_912", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [UNG_913] Tol'vir Warden - COST:5 [ATK:3/HP:5]
    // - Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw two 1-Cost minions
    //       from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [UNG_914] Raptor Hatchling - COST:1 [ATK:2/HP:1]
    // - Race: Beast, Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Shuffle a 4/3 Raptor
    //       into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddCardTask>(EntityType::DECK, "UNG_914t1", 1));
    cards.emplace("UNG_914", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [UNG_915] Crackling Razormaw - COST:2 [ATK:3/HP:2]
    // - Race: Beast, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Adapt</b> a friendly Beast.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_WITH_RACE = 20
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - ADAPT = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [UNG_916] Stampede - COST:1
    // - Set: Ungoro, Rarity: Epic
    // --------------------------------------------------------
    // Text: Each time you play a Beast this turn,
    //       add a random Beast to_your hand.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [UNG_917] Dinomancy - COST:2
    // - Set: Ungoro, Rarity: Epic
    // --------------------------------------------------------
    // Text: Your Hero Power becomes 'Give a Beast +2/+2.'
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [UNG_919] Swamp King Dred - COST:7 [ATK:9/HP:9]
    // - Race: Beast, Set: Ungoro, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After your opponent plays a minion, attack it.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [UNG_920] The Marsh Queen - COST:1
    // - Set: Ungoro, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Quest:</b> Play seven 1-Cost minions.
    //       <b>Reward:</b> Queen Carnassa.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - QUEST = 1
    // - QUEST_PROGRESS_TOTAL = 7
    // - 676 = 1
    // --------------------------------------------------------
}

void UngoroCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - HUNTER
    // [UNG_914t1] Raptor Patriarch (*) - COST:1 [ATK:4/HP:3]
    // - Race: Beast, Set: Ungoro
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("UNG_914t1", cardDef);

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [UNG_916e] Stampeding (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [UNG_917e] Well Fed (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [UNG_920t1] Queen Carnassa (*) - COST:5 [ATK:8/HP:8]
    // - Race: Beast, Set: Ungoro
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Shuffle 15 Raptors into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [UNG_920t2] Carnassa's Brood (*) - COST:1 [ATK:3/HP:2]
    // - Race: Beast, Set: Ungoro
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void UngoroCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------- SPELL - MAGE
    // [UNG_018] Flame Geyser - COST:2
    // - Faction: Neutral, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 2 damage.
    //       Add a 1/2 Elemental to your hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [UNG_020] Arcanologist - COST:2 [ATK:2/HP:3]
    // - Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a <b>Secret</b> from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(ComplexTask::DrawCardFromDeck(
        1, SelfCondList{
               std::make_shared<SelfCondition>(SelfCondition::IsSecret()) }));
    cards.emplace("UNG_020", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [UNG_021] Steam Surger - COST:4 [ATK:5/HP:4]
    // - Race: Elemental, Faction: Neutral, Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you played an Elemental last turn,
    //       add a 'Flame Geyser' to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [UNG_024] Mana Bind - COST:3
    // - Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your opponent casts a spell,
    //       add a copy to your hand that costs (0).
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [UNG_027] Pyros - COST:2 [ATK:2/HP:2]
    // - Race: Elemental, Set: Ungoro, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Return this to your hand
    //       as a 6/6 that costs (6).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [UNG_028] Open the Waygate - COST:1
    // - Set: Ungoro, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Quest:</b> Cast 6 spells that didn't start
    //       in your deck.
    //       <b>Reward:</b> Time Warp.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - QUEST = 1
    // - QUEST_PROGRESS_TOTAL = 6
    // - 676 = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [UNG_846] Shimmering Tempest - COST:2 [ATK:2/HP:1]
    // - Race: Elemental, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a random Mage spell
    //       to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [UNG_941] Primordial Glyph - COST:2
    // - Set: Ungoro, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Discover</b> a spell. Reduce its Cost by (2).
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [UNG_948] Molten Reflection - COST:4
    // - Faction: Neutral, Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: Choose a friendly minion. Summon a copy of it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [UNG_955] Meteor - COST:6
    // - Set: Ungoro, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 15 damage to a minion and 3 damage
    //       to adjacent ones.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
}

void UngoroCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ MINION - MAGE
    // [UNG_027t2] Pyros (*) - COST:6 [ATK:6/HP:6]
    // - Race: Elemental, Set: Ungoro, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Return this to your hand
    //       as a 10/10 that costs (10).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [UNG_027t4] Pyros (*) - COST:10 [ATK:10/HP:10]
    // - Race: Elemental, Set: Ungoro, Rarity: Legendary
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ------------------------------------- ENCHANTMENT - MAGE
    // [UNG_028e] Insightful (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: Take an extra turn.
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [UNG_028t] Time Warp (*) - COST:5
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: Take an extra turn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ------------------------------------- ENCHANTMENT - MAGE
    // [UNG_941e] Primal Magic (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: Cost reduced.
    // --------------------------------------------------------
}

void UngoroCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- SPELL - PALADIN
    // [UNG_004] Dinosize - COST:8
    // - Faction: Neutral, Set: Ungoro, Rarity: Epic
    // --------------------------------------------------------
    // Text: Set a minion's Attack and Health to 10.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [UNG_011] Hydrologist - COST:2 [ATK:2/HP:2]
    // - Race: Murloc, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a <b>Secret</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [UNG_015] Sunkeeper Tarim - COST:6 [ATK:3/HP:7]
    // - Set: Ungoro, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Set all other minions' Attack
    //       and Health to 3.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - PALADIN
    // [UNG_950] Vinecleaver - COST:7 [ATK:4/HP:0]
    // - Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: After your hero attacks,
    //       summon two 1/1 Silver Hand Recruits.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 3
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [UNG_952] Spikeridged Steed - COST:6
    // - Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give a minion +2/+6 and <b>Taunt</b>.
    //       When it dies, summon a Stegodon.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [UNG_953] Primalfin Champion - COST:2 [ATK:1/HP:2]
    // - Race: Murloc, Set: Ungoro, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Return any spells you cast
    //       on this minion to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - 537 = 1
    // - 542 = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [UNG_954] The Last Kaleidosaur - COST:1
    // - Set: Ungoro, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Quest:</b> Cast 6 spells on your minions.
    //       <b>Reward:</b> Galvadon.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - QUEST = 1
    // - QUEST_PROGRESS_TOTAL = 6
    // - 676 = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [UNG_960] Lost in the Jungle - COST:1
    // - Faction: Alliance, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: Summon two 1/1 Silver Hand Recruits.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [UNG_961] Adaptation - COST:1
    // - Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Adapt</b> a friendly minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    // RefTag:
    // - ADAPT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [UNG_962] Lightfused Stegodon - COST:4 [ATK:3/HP:4]
    // - Race: Beast, Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Adapt</b> your Silver Hand Recruits.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - ADAPT = 1
    // --------------------------------------------------------
}

void UngoroCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------- ENCHANTMENT - PALADIN
    // [UNG_004e] RAAAAR! (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: Stats changed to 10/10.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [UNG_015e] Watched (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: Stats changed to 3/3.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [UNG_952e] On a Stegodon (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: +2/+6 and <b>Taunt</b>.
    //       <b>Deathrattle:</b> Summon a Stegodon.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [UNG_953e] Inspired (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: Storing spell.
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [UNG_954t1] Galvadon (*) - COST:5 [ATK:5/HP:5]
    // - Race: Beast, Set: Ungoro
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Adapt</b> 5 times.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - ADAPT = 1
    // --------------------------------------------------------
}

void UngoroCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - PRIEST
    // [UNG_022] Mirage Caller - COST:3 [ATK:2/HP:3]
    // - Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a friendly minion.
    //       Summon a 1/1 copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [UNG_029] Shadow Visions - COST:2
    // - Set: Ungoro, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Discover</b> a copy of a spell in your deck.
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [UNG_030] Binding Heal - COST:1
    // - Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: Restore 5 Health to a minion and your hero.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [UNG_032] Crystalline Oracle - COST:1 [ATK:1/HP:1]
    // - Race: Elemental, Faction: Horde, Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Copy a card from your
    //       opponent's deck and add it to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [UNG_034] Radiant Elemental - COST:2 [ATK:2/HP:3]
    // - Race: Elemental, Faction: Neutral, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: Your spells cost (1) less.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::HAND, EffectList{ Effects::ReduceCost(1) }));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsSpell());
    }
    cards.emplace("UNG_034", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [UNG_035] Curious Glimmerroot - COST:3 [ATK:3/HP:3]
    // - Set: Ungoro, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Look at 3 cards.
    //       Guess which one started in your opponent's deck
    //       to get a copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [UNG_037] Tortollan Shellraiser - COST:4 [ATK:2/HP:6]
    // - Faction: Neutral, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Give a random friendly minion +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [UNG_854] Free From Amber - COST:8
    // - Faction: Neutral, Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Discover</b> a minion that costs (8) or more.
    //       Summon it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_TARGET_WITH_DEATHRATTLE = 0
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [UNG_940] Awaken the Makers - COST:1
    // - Set: Ungoro, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Quest:</b> Summon 7 <b>Deathrattle</b> minions.<b>
    //       Reward:</b> Amara, Warden of Hope.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - QUEST = 1
    // - QUEST_PROGRESS_TOTAL = 7
    // - 676 = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [UNG_963] Lyra the Sunshard - COST:5 [ATK:3/HP:5]
    // - Race: Elemental, Set: Ungoro, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever you cast a spell,
    //       add a random Priest spell to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomCardTask>(CardType::SPELL, CardClass::PRIEST),
        std::make_shared<AddStackToTask>(EntityType::HAND)
    };
    cards.emplace("UNG_963", cardDef);
}

void UngoroCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- ENCHANTMENT - PRIEST
    // [UNG_022e] Mirage (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: 1/1.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [UNG_037e] Shellshield (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [UNG_940t8] Amara, Warden of Hope (*) - COST:5 [ATK:8/HP:8]
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Set your hero's Health to 40.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void UngoroCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - ROGUE
    // [UNG_058] Razorpetal Lasher - COST:2 [ATK:2/HP:2]
    // - Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a Razorpetal to your hand
    //       that deals 1 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "UNG_057t1", 1));
    cards.emplace("UNG_058", cardDef);

    // ----------------------------------------- WEAPON - ROGUE
    // [UNG_061] Obsidian Shard - COST:4 [ATK:3/HP:0]
    // - Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: Costs (1) less for each card you've played from
    //       another class.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 3a
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [UNG_063] Biteweed - COST:2 [ATK:1/HP:1]
    // - Faction: Neutral, Set: Ungoro, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Gain +1/+1 for each other card
    //       you've played this turn.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [UNG_064] Vilespine Slayer - COST:5 [ATK:3/HP:4]
    // - Faction: Neutral, Set: Ungoro, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Destroy a minion.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_FOR_COMBO = 0
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [UNG_065] Sherazin, Corpse Flower - COST:4 [ATK:5/HP:3]
    // - Set: Ungoro, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Go dormant.
    //       Play 4 cards in a turn to revive this minion.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 10
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [UNG_057] Razorpetal Volley - COST:2
    // - Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: Add two Razorpetals to_your hand that deal 1 damage.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "UNG_057t1", 2));
    cards.emplace("UNG_057", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [UNG_060] Mimic Pod - COST:3
    // - Faction: Neutral, Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: Draw a card, then add a copy of it to your hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [UNG_067] The Caverns Below - COST:1
    // - Set: Ungoro, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Quest:</b> Play five minions with the same name.
    //       <b>Reward:</b> Crystal Core.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - QUEST = 1
    // - QUEST_PROGRESS_TOTAL = 5
    // - 676 = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [UNG_823] Envenom Weapon - COST:3
    // - Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give your weapon <b>Poisonous</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_WEAPON_EQUIPPED = 0
    // --------------------------------------------------------
    // RefTag:
    // - POISONOUS = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [UNG_856] Hallucination - COST:1
    // - Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Discover</b> a card from your opponent's class.
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
}

void UngoroCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ SPELL - ROGUE
    // [UNG_057t1] Razorpetal (*) - COST:1
    // - Faction: Neutral, Set: Ungoro
    // --------------------------------------------------------
    // Text: Deal 1 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("UNG_057t1", cardDef);

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [UNG_063e] Sprout (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [UNG_065t] Sherazin, Seed (*) - COST:11 [ATK:0/HP:1]
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: When you play 4 cards in a turn, revive this minion.
    // --------------------------------------------------------
    // GameTag:
    // - HIDE_STATS = 1
    // - UNTOUCHABLE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [UNG_067t1] Crystal Core (*) - COST:5
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: For the rest of the game, your minions are 4/4.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - RITUAL = 1
    // --------------------------------------------------------
}

void UngoroCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - SHAMAN
    // [UNG_019] Air Elemental - COST:1 [ATK:2/HP:1]
    // - Race: Elemental, Faction: Horde, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [UNG_025] Volcano - COST:5
    // - Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 15 damage randomly split among all minions.
    //       <b>Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 2
    // - OVERLOAD_OWED = 2
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [UNG_201] Primalfin Totem - COST:2 [ATK:0/HP:3]
    // - Race: Totem, Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn, summon a 1/1 Murloc.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [UNG_202] Fire Plume Harbinger - COST:2 [ATK:1/HP:1]
    // - Race: Elemental, Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Reduce the Cost of Elementals
    //       in your hand by (1).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [UNG_208] Stone Sentinel - COST:7 [ATK:4/HP:4]
    // - Race: Elemental, Set: Ungoro, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you played an Elemental last turn,
    //       summon two 2/3 Elementals with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_TARGET_WITH_DEATHRATTLE = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [UNG_211] Kalimos, Primal Lord - COST:8 [ATK:7/HP:7]
    // - Race: Elemental, Set: Ungoro, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you played an Elemental last turn,
    //       cast an Elemental Invocation.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [UNG_817] Tidal Surge - COST:3
    // - Faction: Neutral, Set: Ungoro, Rarity: Common
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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 4, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("UNG_817", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [UNG_938] Hot Spring Guardian - COST:3 [ATK:2/HP:4]
    // - Race: Elemental, Set: Ungoro, Rarity: common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Restore 3_Health.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [UNG_942] Unite the Murlocs - COST:1
    // - Set: Ungoro, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Quest:</b> Summon 10 Murlocs.
    //       <b>Reward:</b> Megafin.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - QUEST = 1
    // - QUEST_PROGRESS_TOTAL = 10
    // - 676 = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [UNG_956] Spirit Echo - COST:3
    // - Set: Ungoro, Rarity: Epic
    // --------------------------------------------------------
    // Text: Give your minions "<b>Deathrattle:</b>
    //       Return this to your hand."
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
}

void UngoroCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- MINION - SHAMAN
    // [UNG_208t] Rock Elemental (*) - COST:2 [ATK:2/HP:3]
    // - Race: Elemental, Set: Ungoro
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [UNG_211a] Invocation of Earth (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: Fill your board with 1/1 Elementals.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [UNG_211aa] Stone Elemental (*) - COST:1 [ATK:1/HP:1]
    // - Race: Elemental, Faction: Neutral, Set: Ungoro
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [UNG_211b] Invocation of Water (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: Restore 12 Health to your hero.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [UNG_211c] Invocation of Fire (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: Deal 6 damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [UNG_211d] Invocation of Air (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: Deal 3 damage to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [UNG_942t] Megafin (*) - COST:5 [ATK:8/HP:8]
    // - Race: Murloc, Set: Ungoro
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Fill your hand with random Murlocs.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [UNG_956e] Echoed Spirit (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Return to your hand.
    // --------------------------------------------------------
}

void UngoroCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - WARLOCK
    // [UNG_047] Ravenous Pterrordax - COST:4 [ATK:4/HP:4]
    // - Race: Beast, Faction: Neutral, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a friendly minion
    //       to <b>Adapt</b> twice.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    // RefTag:
    // - ADAPT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [UNG_049] Tar Lurker - COST:5 [ATK:1/HP:7]
    // - Race: Elemental, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       Has +3 Attack during your opponent's turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [UNG_829] Lakkari Sacrifice - COST:1
    // - Set: Ungoro, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Quest:</b> Discard 6 cards.
    //       <b>Reward:</b> Nether Portal.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - QUEST = 1
    // - QUEST_PROGRESS_TOTAL = 6
    // - 676 = 1
    // - 839 = 1
    // - QUEST_REWARD_DATABASE_ID = 41942
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [UNG_830] Cruel Dinomancer - COST:6 [ATK:5/HP:5]
    // - Faction: Neutral, Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a random minion
    //       you discarded this game.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [UNG_831] Corrupting Mist - COST:2
    // - Faction: Neutral, Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: Corrupt every minion.
    //       Destroy them at the start of your next turn.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [UNG_832] Bloodbloom - COST:2
    // - Set: Ungoro, Rarity: Epic
    // --------------------------------------------------------
    // Text: The next spell you cast this turn costs Health
    //       instead of Mana.
    // --------------------------------------------------------
    // Entourage: UNG_999t10, UNG_999t2, UNG_999t3, UNG_999t4,
    //            UNG_999t5, UNG_999t6, UNG_999t7, UNG_999t8,
    //            UNG_999t13, UNG_999t14
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [UNG_833] Lakkari Felhound - COST:4 [ATK:3/HP:8]
    // - Race: Demon, Faction: Neutral, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Discard your two lowest-Cost cards.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscardTask>(2, DiscardType::LOWEST_COST));
    cards.emplace("UNG_833", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [UNG_834] Feeding Time - COST:5
    // - Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 3 damage to a minion. Summon three 1/1 Pterrordaxes.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [UNG_835] Chittering Tunneler - COST:3 [ATK:3/HP:3]
    // - Race: Beast, Set: Ungoro, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a spell.
    //       Deal damage to your hero equal to its Cost.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [UNG_836] Clutchmother Zavas - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Set: Ungoro, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever you discard this,
    //       give it +2/+2 and return it to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - InvisibleDeathrattle = 1
    // --------------------------------------------------------
}

void UngoroCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- SPELL - WARLOCK
    // [UNG_829t1] Nether Portal (*) - COST:5
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: Open a permanent portal that summons 3/2 Imps.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [UNG_829t2] Nether Portal (*) - COST:11 [ATK:0/HP:1]
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: At the end of your turn, summon two 3/2 Imps.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - HIDE_STATS = 1
    // - UNTOUCHABLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [UNG_829t3] Nether Imp (*) - COST:2 [ATK:3/HP:2]
    // - Race: Demon, Set: Ungoro
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [UNG_834t1] Pterrordax (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Ungoro
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [UNG_831e] Corrupting Mist (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: At the start of the corrupting player's turn,
    //       destroy this minion.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [UNG_836e] Remembrance (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: +2/+2 each time this is discarded.
    // --------------------------------------------------------
}

void UngoroCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - WARRIOR
    // [UNG_838] Tar Lord - COST:7 [ATK:1/HP:11]
    // - Race: Elemental, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       Has +4 Attack during your opponent's turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [UNG_922] Explore Un'Goro - COST:2
    // - Set: Ungoro, Rarity: Epic
    // --------------------------------------------------------
    // Text: Replace your deck with copies of "<b>Discover</b> a card."
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [UNG_923] Iron Hide - COST:1
    // - Faction: Neutral, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: Gain 5 Armor.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [UNG_925] Ornery Direhorn - COST:6 [ATK:5/HP:5]
    // - Race: Beast, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> <b>Adapt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - ADAPT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [UNG_926] Cornered Sentry - COST:2 [ATK:2/HP:6]
    // - Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>.
    //       <b>Battlecry:</b> Summon three 1/1 Raptors for
    //       your opponent.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [UNG_927] Sudden Genesis - COST:5
    // - Set: Ungoro, Rarity: Epic
    // --------------------------------------------------------
    // Text: Summon copies of your damaged minions.
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [UNG_929] Molten Blade - COST:1 [ATK:1/HP:0]
    // - Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: Each turn this is in your hand,
    //       transform it into a new weapon.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [UNG_933] King Mosh - COST:9 [ATK:9/HP:7]
    // - Race: Beast, Faction: Neutral, Set: Ungoro, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy all damaged minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [UNG_934] Fire Plume's Heart - COST:1
    // - Set: Ungoro, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Quest:</b> Play 7 <b>Taunt</b> minions.
    //       <b>Reward:</b> Sulfuras.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - QUEST = 1
    // - QUEST_PROGRESS_TOTAL = 7
    // - 676 = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [UNG_957] Direhorn Hatchling - COST:5 [ATK:3/HP:6]
    // - Race: Beast, Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Shuffle a 6/9 Direhorn with
    //       <b>Taunt</b> into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
}

void UngoroCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- SPELL - WARRIOR
    // [UNG_922t1] Choose Your Path (*) - COST:1
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: <b>Discover</b> a card.
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [UNG_929e] Magmic (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: Transforming into random weapons.
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [UNG_934t1] Sulfuras (*) - COST:3 [ATK:4/HP:0]
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your Hero Power becomes
    //       'Deal 8 damage to a random enemy.'
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DURABILITY = 2
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [UNG_957t1] Direhorn Matriarch (*) - COST:5 [ATK:6/HP:9]
    // - Race: Beast, Set: Ungoro
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
}

void UngoroCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_001] Pterrordax Hatchling - COST:3 [ATK:2/HP:2]
    // - Race: Beast, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b><b>Battlecry:</b> Adapt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - ADAPT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_002] Volcanosaur - COST:7 [ATK:5/HP:6]
    // - Race: Beast, Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Adapt</b>, then <b>Adapt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - ADAPT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_009] Ravasaur Runt - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control at least
    //       2 other minions, <b>Adapt.</b>
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - ADAPT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_010] Sated Threshadon - COST:7 [ATK:5/HP:7]
    // - Race: Beast, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon three 1/1 Murlocs.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_070] Tol'vir Stoneshaper - COST:4 [ATK:3/HP:5]
    // - Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you played an Elemental last turn,
    //       gain <b>Taunt</b> and <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_071] Giant Mastodon - COST:9 [ATK:6/HP:10]
    // - Race: Beast, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_072] Stonehill Defender - COST:3 [ATK:1/HP:4]
    // - Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> <b>Discover</b> a <b>Taunt</b> minion.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_073] Rockpool Hunter - COST:2 [ATK:2/HP:3]
    // - Race: Murloc, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly Murloc +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_WITH_RACE = 14
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_075] Vicious Fledgling - COST:3 [ATK:3/HP:3]
    // - Race: Beast, Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: After this minion attacks a hero, <b>Adapt</b>.
    // --------------------------------------------------------
    // RefTag:
    // - ADAPT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_076] Eggnapper - COST:3 [ATK:3/HP:1]
    // - Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon two 1/1 Raptors.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_079] Frozen Crusher - COST:6 [ATK:8/HP:8]
    // - Race: Elemental, Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: After this minion attacks, <b>Freeze</b> it.
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_082] Thunder Lizard - COST:3 [ATK:3/HP:3]
    // - Race: Beast, Faction: Neutral, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry</b>: If you played an Elemental last turn,
    //       <b>Adapt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - ADAPT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_083] Devilsaur Egg - COST:3 [ATK:0/HP:3]
    // - Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 5/5 Devilsaur.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("UNG_083t1", SummonSide::DEATHRATTLE));
    cards.emplace("UNG_083", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_084] Fire Plume Phoenix - COST:4 [ATK:3/HP:3]
    // - Race: Elemental, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 2 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_NONSELF_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_085] Emerald Hive Queen - COST:1 [ATK:2/HP:3]
    // - Race: Beast, Faction: Horde, Set: Ungoro, Rarity: Epic
    // --------------------------------------------------------
    // Text: Your minions cost (2) more.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_087] Bittertide Hydra - COST:5 [ATK:8/HP:8]
    // - Race: Beast, Set: Ungoro, Rarity: Epic
    // --------------------------------------------------------
    // Text: Whenever this minion takes damage,
    //       deal 3 damage to your hero.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_088] Tortollan Primalist - COST:8 [ATK:5/HP:4]
    // - Set: Ungoro, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a spell and
    //       cast it with random targets.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_089] Gentle Megasaur - COST:4 [ATK:5/HP:4]
    // - Race: Beast, Set: Ungoro, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Adapt</b> your Murlocs.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - ADAPT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_099] Charged Devilsaur - COST:8 [ATK:7/HP:7]
    // - Race: Beast, Set: Ungoro, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    //       <b>Battlecry:</b> Can't attack heroes this turn.
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_113] Bright-Eyed Scout - COST:4 [ATK:3/HP:4]
    // - Set: Ungoro, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a card. Change its Cost to (5).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_205] Glacial Shard - COST:1 [ATK:2/HP:1]
    // - Race: Elemental, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Freeze</b> an enemy.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_801] Nesting Roc - COST:5 [ATK:4/HP:7]
    // - Race: Beast, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control at least
    //       2 other minions, gain <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_803] Emerald Reaver - COST:1 [ATK:2/HP:1]
    // - Race: Beast, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage to each hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_806] Ultrasaur - COST:10 [ATK:7/HP:14]
    // - Race: Beast, Faction: Neutral, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("UNG_806", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_807] Golakka Crawler - COST:2 [ATK:2/HP:3]
    // - Race: Beast, Faction: Neutral, Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a Pirate and gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_TARGET_WITH_RACE = 23
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_808] Stubborn Gastropod - COST:2 [ATK:1/HP:2]
    // - Race: Beast, Faction: Neutral, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - POISONOUS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_809] Fire Fly - COST:1 [ATK:1/HP:2]
    // - Race: Elemental, Faction: Alliance, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry</b>: Add a 1/2 Elemental to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "UNG_809t1", 1));
    cards.emplace("UNG_809", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_810] Stegodon - COST:4 [ATK:2/HP:6]
    // - Race: Beast, Faction: Neutral, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_812] Sabretooth Stalker - COST:6 [ATK:8/HP:2]
    // - Race: Beast, Faction: Neutral, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_813] Stormwatcher - COST:7 [ATK:4/HP:8]
    // - Race: Elemental, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - WINDFURY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("UNG_813", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_814] Giant Wasp - COST:3 [ATK:2/HP:2]
    // - Race: Beast, Faction: Neutral, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //       <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // - POISONOUS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_816] Servant of Kalimos - COST:5 [ATK:4/HP:5]
    // - Race: Elemental, Faction: Neutral, Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you played an Elemental last turn,
    //       <b>Discover</b> an Elemental.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_TARGET_WITH_DEATHRATTLE = 0
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_818] Volatile Elemental - COST:2 [ATK:1/HP:1]
    // - Race: Elemental, Faction: Neutral, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 3 damage to a random enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_840] Hemet, Jungle Hunter - COST:6 [ATK:6/HP:6]
    // - Set: Ungoro, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy all cards in your deck
    //       that cost (3) or less.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_843] The Voraxx - COST:4 [ATK:3/HP:3]
    // - Set: Ungoro, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you cast a spell on this minion,
    //       summon a 1/1 Plant and cast another copy on it.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_844] Humongous Razorleaf - COST:3 [ATK:4/HP:8]
    // - Faction: Alliance, Set: Ungoro, Rarity: Rare
    // --------------------------------------------------------
    // Text: Can't attack.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_ATTACK = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("UNG_844", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_845] Igneous Elemental - COST:3 [ATK:2/HP:3]
    // - Race: Elemental, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add two 1/2 Elementals to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_847] Blazecaller - COST:7 [ATK:6/HP:6]
    // - Race: Elemental, Set: Ungoro, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you played an Elemental last turn,
    //       deal 5 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NONSELF_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE_AND_ELEMENTAL_PLAYED_LAST_TURN = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_848] Primordial Drake - COST:8 [ATK:4/HP:8]
    // - Race: Dragon, Set: Ungoro, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Deal 2 damage to all other minions.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ALL_MINIONS_NOSOURCE, 2));
    cards.emplace("UNG_848", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_851] Elise the Trailblazer - COST:5 [ATK:5/HP:5]
    // - Set: Ungoro, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Shuffle a sealed <b>Un'Goro</b>
    //       pack into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_900] Spiritsinger Umbra - COST:4 [ATK:3/HP:4]
    // - Set: Ungoro, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you summon a minion,
    //       trigger its <b>Deathrattle</b> effect.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_907] Ozruk - COST:9 [ATK:5/HP:5]
    // - Race: Elemental, Set: Ungoro, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Gain +5 Health for each Elemental
    //       you played last turn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_928] Tar Creeper - COST:3 [ATK:1/HP:5]
    // - Race: Elemental, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       Has +2 Attack during your opponent's turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<AdaptiveEffect>(
        GameTag::ATK, EffectOperator::ADD, [=](const Playable* playable) {
            return playable->player == playable->game->GetOpponentPlayer() ? 2
                                                                           : 0;
        }));
    cards.emplace("UNG_928", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_937] Primalfin Lookout - COST:3 [ATK:3/HP:2]
    // - Race: Murloc, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control another Murloc,
    //       <b>Discover</b> a Murloc.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_946] Gluttonous Ooze - COST:3 [ATK:3/HP:3]
    // - Set: Ungoro, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy your opponent's weapon
    //       and gain Armor equal to its Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_WITH_DEATHRATTLE = 0
    // --------------------------------------------------------
}

void UngoroCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;
    // --------------------------------------- MINION - NEUTRAL
    // [ICC_828t2] Stubborn Gastropod (*) - COST:2 [ATK:1/HP:2]
    // - Race: Beast, Faction: Neutral, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - POISONOUS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_828t3] Giant Wasp (*) - COST:3 [ATK:2/HP:2]
    // - Race: Beast, Fac: Neutral, Set: Ungoro, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //       <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // - POISONOUS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_076t1] Raptor (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Ungoro
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [UNG_067t1e] Crystallized (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: Your minions are 4/4.
    // --------------------------------------------------------
    // GameTag:
    // - 758 = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [UNG_067t1e2] Crystallized (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: 4/4.
    // --------------------------------------------------------
    // GameTag:
    // - 758 = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [UNG_070e] Stonewall (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b> and <b>Taunt</b>.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [UNG_073e] Trained (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: +1/+1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_083t1] Devilsaur (*) - COST:5 [ATK:5/HP:5]
    // - Race: Beast, Set: Ungoro
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("UNG_083t1", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [UNG_113e] Scouted (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: Costs (5).
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_201t] Primalfin (*) - COST:1 [ATK:1/HP:1]
    // - Race: Murloc, Set: Ungoro
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [UNG_202e] Fiery (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [UNG_807e] Overfull Belly (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_809t1] Flame Elemental (*) - COST:1 [ATK:1/HP:2]
    // - Race: Elemental, Faction: Alliance, Set: Ungoro
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("UNG_809t1", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [UNG_823e] Envenomed (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - POISONOUS = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [UNG_823ed] Envenomed (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [UNG_832e] Dark Power (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: Your next spell costs Health instead of Mana.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [UNG_851t1] Un'Goro Pack (*) - COST:2
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: Add 5 <b>Journey to Un'Goro</b> cards to your hand.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [UNG_907e] Just Blaze (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: +5 Health
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [UNG_999t2] Living Spores (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon two 1/1 Plants.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [UNG_999t2e] Living Spores (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon two 1/1 Plants.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [UNG_999t2t1] Plant (*) - COST:1 [ATK:1/HP:1]
    // - Set: Ungoro
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [UNG_999t3] Flaming Claws (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: +3 Attack
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [UNG_999t3e] Flaming Claws (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: +3 Attack.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [UNG_999t4] Rocky Carapace (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: +3 Health
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [UNG_999t4e] Rocky Carapace (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: +3 Health.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [UNG_999t5] Liquid Membrane (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [UNG_999t5e] Liquid Membrane (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [UNG_999t6] Massive (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [UNG_999t6e] Massive (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [UNG_999t7] Lightning Speed (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: <b>Windfury</b>
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [UNG_999t7e] Lightning Speed (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: <b>Windfury</b>
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [UNG_999t8] Crackling Shield (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [UNG_999t8e] Crackling Shield (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [UNG_999t10] Shrouding Mist (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: <b>Stealth</b> until your next turn.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [UNG_999t10e] Shrouding Mist (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: Stealthed until your next turn.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [UNG_999t13] Poison Spit (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [UNG_999t13e] Poison Spit (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [UNG_999t14] Volcanic Might (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: +1/+1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [UNG_999t14e] Volcanic Might (*) - COST:0
    // - Set: Ungoro
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
}

void UngoroCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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