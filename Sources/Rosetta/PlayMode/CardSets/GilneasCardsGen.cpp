// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/CardSets/GilneasCardsGen.hpp>
#include <Rosetta/PlayMode/Cards/CardPowers.hpp>

namespace RosettaStone::PlayMode
{
void GilneasCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ HERO - SHAMAN
    // [GIL_504] Hagatha the Witch - COST:8 [ATK:0/HP:30]
    // - Set: Gilneas, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 47631
    // --------------------------------------------------------
}

void GilneasCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- HERO_POWER - NEUTRAL
    // [GIL_504h] Bewitch (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: <b>Passive Hero Power</b>
    //       After you play a minion,
    //       add a random Shaman spell to your hand.
    // --------------------------------------------------------
}

void GilneasCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- MINION - DRUID
    // [GIL_188] Druid of the Scythe - COST:3 [ATK:2/HP:2]
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Transform into a 4/2
    //       with <b>Rush</b>; or a 2/4 with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [GIL_507] Bewitched Guardian - COST:5 [ATK:4/HP:1]
    // - Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Gain +1 Health for each card
    //       in your hand.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [GIL_553] Wispering Woods - COST:4
    // - Set: Gilneas, Rarity: Epic
    // --------------------------------------------------------
    // Text: Summon a 1/1 Wisp for each card in your hand.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [GIL_571] Witching Hour - COST:3
    // - Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon a random friendly Beast that died this game.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // - REQ_FRIENDLY_MINIONS_OF_RACE_DIED_THIS_GAME = 20
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [GIL_637] Ferocious Howl - COST:3
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: Draw a card. Gain 1 Armor for each card in your hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [GIL_658] Splintergraft - COST:8 [ATK:8/HP:8]
    // - Set: Gilneas, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a friendly minion.
    //       Add a 10/10 copy to your hand that costs (10).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [GIL_663] Witchwood Apple - COST:2
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: Add three 2/2 Treants to your hand.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [GIL_800] Duskfallen Aviana - COST:5 [ATK:3/HP:7]
    // - Set: Gilneas, Rarity: Legendary
    // --------------------------------------------------------
    // Text: On each player's turn, the first card played costs (0).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AURA = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [GIL_833] Forest Guide - COST:4 [ATK:1/HP:6]
    // - Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn, both players draw a card.
    // --------------------------------------------------------
}

void GilneasCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ SPELL - DRUID
    // [GIL_188a] Dire Panther Form (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: +2 Attack and <b>Rush</b>
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [GIL_188b] Dire Wolf Form (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: +2 Health and <b>Taunt</b>
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [GIL_188t] Druid of the Scythe (*) - COST:3 [ATK:4/HP:2]
    // - Race: Beast, Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [GIL_188t2] Druid of the Scythe (*) - COST:3 [ATK:2/HP:4]
    // - Race: Beast, Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [GIL_188t3] Druid of the Scythe (*) - COST:3 [ATK:4/HP:4]
    // - Race: Beast, Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [GIL_553t] Wisp (*) - COST:0 [ATK:1/HP:1]
    // - Set: Gilneas
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [GIL_663t] Treant (*) - COST:2 [ATK:2/HP:2]
    // - Set: Gilneas
    // --------------------------------------------------------
}

void GilneasCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - HUNTER
    // [GIL_128] Emeriss - COST:10 [ATK:8/HP:8]
    // - Race: Dragon, Set: Gilneas, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Double the Attack and Health
    //       of all minions in your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [GIL_200] Duskhaven Hunter - COST:3 [ATK:2/HP:5]
    // - Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //       Each turn this is in your hand,
    //       swap its Attack and Health.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [GIL_518] Wing Blast - COST:4
    // - Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 4 damage to a minion.
    //       If a minion died this turn, this costs (1).
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [GIL_562] Vilebrood Skitterer - COST:5 [ATK:1/HP:3]
    // - Race: Beast, Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    //       <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - POISONOUS = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [GIL_577] Rat Trap - COST:2
    // - Set: Gilneas, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After your opponent plays
    //       three cards in a turn, summon a 6/6 Rat.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [GIL_607] Toxmonger - COST:4 [ATK:2/HP:4]
    // - Set: Gilneas, Rarity: Epic
    // --------------------------------------------------------
    // Text: Whenever you play a 1-Cost minion,
    //       give it <b>Poisonous</b>.
    // --------------------------------------------------------
    // RefTag:
    // - POISONOUS = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [GIL_607t] Hunting Mastiff - COST:2 [ATK:2/HP:1]
    // - Race: Beast, Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Echo</b>
    //       <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // - ECHO = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [GIL_650] Houndmaster Shaw - COST:4 [ATK:3/HP:6]
    // - Set: Gilneas, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Your other minions have <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<Aura>(AuraType::FIELD_EXCEPT_SOURCE, "GIL_650e"));
    cards.emplace("GIL_650", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [GIL_828] Dire Frenzy - COST:4
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a Beast +3/+3.
    //       Shuffle 3 copies into your deck with +3/+3.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_WITH_RACE = 20
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("GIL_828e", EntityType::TARGET));
    cardDef.power.AddPowerTask(std::make_shared<CopyTask>(
        EntityType::TARGET, ZoneType::DECK, 3, true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("GIL_828e", EntityType::STACK));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_TARGET_WITH_RACE, 20 } };
    cards.emplace("GIL_828", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [GIL_905] Carrion Drake - COST:5 [ATK:3/HP:7]
    // - Race: Dragon, Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If a minion died this turn,
    //       gain <b>Poisonous</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - POISONOUS = 1
    // --------------------------------------------------------
}

void GilneasCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- MINION - HUNTER
    // [GIL_200t] Duskhaven Hunter (*) - COST:3 [ATK:5/HP:2]
    // - Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //       Each turn this is in your hand,
    //       swap its Attack and Health.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [GIL_577t] Doom Rat (*) - COST:6 [ATK:6/HP:6]
    // - Race: Beast, Set: Gilneas
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [ICC_828t5] Hunting Mastiff (*) - COST:2 [ATK:2/HP:1]
    // - Race: Beast, Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Echo</b>
    //       <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // - ECHO = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [ICC_828t6] Vilebrood Skitterer (*) - COST:5 [ATK:1/HP:3]
    // - Race: Beast, Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    //       <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - POISONOUS = 1
    // - RUSH = 1
    // --------------------------------------------------------
}

void GilneasCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ MINION - MAGE
    // [GIL_116] Arcane Keysmith - COST:4 [ATK:2/HP:2]
    // - Set: Gilneas, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a <b>Secret</b>.
    //       Put it into the battlefield.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [GIL_147] Cinderstorm - COST:3
    // - Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 5 damage randomly split among all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [GIL_548] Book of Specters - COST:2
    // - Set: Gilneas, Rarity: Epic
    // --------------------------------------------------------
    // Text: Draw 3 cards. Discard any spells drawn.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [GIL_549] Toki, Time-Tinker - COST:6 [ATK:5/HP:5]
    // - Set: Gilneas, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a random <b>Legendary</b>
    //       minion from the past to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [GIL_640] Curio Collector - COST:5 [ATK:4/HP:4]
    // - Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you draw a card, gain +1/+1.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [GIL_645] Bonfire Elemental - COST:5 [ATK:5/HP:5]
    // - Race: Elemental, Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you played an Elemental
    //       last turn, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [GIL_664] Vex Crow - COST:4 [ATK:3/HP:3]
    // - Race: Beast, Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever you cast a spell,
    //       summon a random 2-Cost minion.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [GIL_691] Archmage Arugal - COST:2 [ATK:2/HP:2]
    // - Set: Gilneas, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever you draw a minion,
    //       add a copy of it to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [GIL_801] Snap Freeze - COST:2
    // - Set: Gilneas, Rarity: Common
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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::TARGET, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsFrozen()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DestroyTask>(EntityType::TARGET) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        false, TaskList{ std::make_shared<FreezeTask>(EntityType::TARGET) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("GIL_801", cardDef);
}

void GilneasCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void GilneasCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- SPELL - PALADIN
    // [GIL_145] Sound the Bells! - COST:2
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Echo</b>
    //       Give a minion +1/+2.
    // --------------------------------------------------------
    // GameTag:
    // - ECHO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [GIL_203] Rebuke - COST:2
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: Enemy spells cost (5) more next turn.
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [GIL_545] Ghostly Charger - COST:5 [ATK:3/HP:4]
    // - Race: Beast, Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    //       <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - PALADIN
    // [GIL_596] Silver Sword - COST:8 [ATK:3/HP:0]
    // - Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: After your hero attacks, give your minions +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 4
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [GIL_634] Bellringer Sentry - COST:4 [ATK:3/HP:4]
    // - Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry and Deathrattle:</b> Put a
    //       <b>Secret</b> from your deck into the battlefield.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [GIL_635] Cathedral Gargoyle - COST:2 [ATK:2/HP:2]
    // - Set: Gilneas, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       gain <b>Taunt</b> and <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [GIL_685] Paragon of Light - COST:3 [ATK:2/HP:5]
    // - Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: While this minion has 3 or more Attack,
    //       it has <b>Taunt</b> and <b>Lifesteal</b>.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [GIL_694] Prince Liam - COST:5 [ATK:5/HP:5]
    // - Set: Gilneas, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Transform all 1-Cost cards
    //       in your deck into <b>Legendary</b> minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [GIL_817] The Glass Knight - COST:4 [ATK:4/HP:3]
    // - Set: Gilneas, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    //       Whenever you restore Health, gain <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [GIL_903] Hidden Wisdom - COST:1
    // - Set: Gilneas, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After your opponent plays
    //       three cards in a turn, draw 2 cards.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
}

void GilneasCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ---------------------------------- ENCHANTMENT - PALADIN
    // [GIL_145e] DING DONG! (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: +1/+2.
    // --------------------------------------------------------
}

void GilneasCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- SPELL - PRIEST
    // [GIL_134] Holy Water - COST:5
    // - Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 4 damage to a minion. If that kills it,
    //       add a copy of it to your hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [GIL_142] Chameleos - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Gilneas, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Each turn this is in your hand,
    //       transform it into a card your opponent is holding.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [GIL_156] Quartz Elemental - COST:5 [ATK:5/HP:8]
    // - Race: Elemental, Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: Can't attack while damaged.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [GIL_190] Nightscale Matriarch - COST:7 [ATK:4/HP:9]
    // - Race: Dragon, Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever a friendly minion is healed,
    //       summon a 3/3_Whelp.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [GIL_661] Divine Hymn - COST:2
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: Restore 6 Health to all friendly characters.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [GIL_805] Coffin Crasher - COST:6 [ATK:6/HP:5]
    // - Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a <b>Deathrattle</b>
    //       minion from your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [GIL_813] Vivid Nightmare - COST:3
    // - Set: Gilneas, Rarity: Epic
    // --------------------------------------------------------
    // Text: Choose a friendly minion.
    //       Summon a copy of it with 1 Health remaining.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_NUM_MINION_SLOTS = 1
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [GIL_835] Squashling - COST:2 [ATK:2/HP:1]
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Echo</b>
    //       <b>Battlecry:</b> Restore 2 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - ECHO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [GIL_840] Lady in White - COST:6 [ATK:5/HP:5]
    // - Set: Gilneas, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Cast 'Inner Fire' on every minion
    //       in your deck <i>(set Attack equal to Health).</i>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void GilneasCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- MINION - PRIEST
    // [GIL_190t] Nightscale Whelp (*) - COST:3 [ATK:3/HP:3]
    // - Race: Dragon, Set: Gilneas
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [GIL_840e] Angelic Fortitude (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: Has Attack equal to its Health.
    // --------------------------------------------------------
}

void GilneasCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ SPELL - ROGUE
    // [GIL_506] Cheap Shot - COST:2
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Echo</b>
    //        Deal 2 damage to a minion.
    // --------------------------------------------------------
    // GameTag:
    // - ECHO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [GIL_510] Mistwraith - COST:4 [ATK:3/HP:5]
    // - Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you play an <b>Echo</b> card, gain +1/+1.
    // --------------------------------------------------------
    // RefTag:
    // - ECHO = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [GIL_557] Cursed Castaway - COST:6 [ATK:5/HP:3]
    // - Race: Pirate, Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Deathrattle:</b> Draw a <b>Combo</b> card
    //       from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - RUSH = 1
    // --------------------------------------------------------
    // RefTag:
    // - COMBO = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [GIL_598] Tess Greymane - COST:7 [ATK:6/HP:6]
    // - Set: Gilneas, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Replay every card
    //       from another class you've played this game
    //       <i>(targets chosen randomly)</i>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<FuncNumberTask>([](const Playable* playable) {
            Player* player = playable->player;

            std::vector<Card*> playedCards;
            playedCards.reserve(30);

            for (auto& history : player->playHistory)
            {
                if (!history.sourceCard->IsCardClass(CardClass::NEUTRAL) &&
                    !history.sourceCard->IsCardClass(
                        player->GetHero()->card->GetCardClass()))
                {
                    playedCards.emplace_back(history.sourceCard);
                }
            }

            Random::shuffle(playedCards);

            for (const auto& card : playedCards)
            {
                auto validTargets = card->GetValidPlayTargets(player);
                if (card->mustHaveToTargetToPlay && validTargets.empty())
                {
                    continue;
                }

                const auto targetIdx =
                    Random::get<std::size_t>(0, validTargets.size() - 1);
                const auto randTarget =
                    validTargets.empty() ? nullptr : validTargets[targetIdx];
                const auto chooseOneIdx = Random::get<int>(1, 2);

                Entity* entity = Entity::GetFromCard(player, card);

                switch (card->GetCardType())
                {
                    case CardType::HERO:
                    {
                        Generic::PlayHero(player, dynamic_cast<Hero*>(entity),
                                          randTarget, chooseOneIdx);
                        break;
                    }
                    case CardType::MINION:
                    case CardType::LOCATION:
                    {
                        if (player->GetFieldZone()->IsFull())
                        {
                            break;
                        }

                        Generic::Summon(dynamic_cast<Minion*>(entity), -1,
                                        player);

                        player->game->ProcessDestroyAndUpdateAura();
                        break;
                    }
                    case CardType::SPELL:
                    {
                        Generic::CastSpell(player, dynamic_cast<Spell*>(entity),
                                           randTarget, chooseOneIdx);

                        while (player->choice)
                        {
                            const auto choiceIdx = Random::get<std::size_t>(
                                0, player->choice->choices.size());
                            Generic::ChoicePick(player,
                                                static_cast<int>(choiceIdx));
                        }

                        player->game->ProcessDestroyAndUpdateAura();
                        break;
                    }
                    case CardType::WEAPON:
                    {
                        const auto weapon = dynamic_cast<Weapon*>(entity);

                        if (const auto aura = weapon->card->power.GetAura();
                            aura)
                        {
                            aura->Activate(weapon);
                        }

                        if (const auto trigger =
                                weapon->card->power.GetTrigger();
                            trigger)
                        {
                            trigger->Activate(weapon);
                        }

                        player->GetHero()->AddWeapon(*weapon);
                        break;
                    }
                    case CardType::INVALID:
                    case CardType::GAME:
                    case CardType::PLAYER:
                    case CardType::ENCHANTMENT:
                    case CardType::ITEM:
                    case CardType::TOKEN:
                    case CardType::HERO_POWER:
                    case CardType::BLANK:
                    case CardType::GAME_MODE_BUTTON:
                    case CardType::MOVE_MINION_HOVER_TARGET:
                    case CardType::LETTUCE_ABILITY:
                    case CardType::BATTLEGROUND_HERO_BUDDY:
                    case CardType::BATTLEGROUND_QUEST_REWARD:
                        throw std::invalid_argument(
                            "Tess Greymane (GIL_598) - Invalid card "
                            "type!");
                }
            }

            return 0;
        }));
    cards.emplace("GIL_598", cardDef);

    // ----------------------------------------- WEAPON - ROGUE
    // [GIL_672] Spectral Cutlass - COST:4 [ATK:2/HP:0]
    // - Set: Gilneas, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    //       Whenever you play a card from another class,
    //       gain +1 Durability.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [GIL_677] Face Collector - COST:3 [ATK:2/HP:2]
    // - Set: Gilneas, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Echo</b>
    //       <b>Battlecry:</b> Add a random <b>Legendary</b>
    //       minion to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ECHO = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [GIL_687] WANTED! - COST:4
    // - Set: Gilneas, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 3 damage to a minion.
    //       If that kills it, add a Coin to your hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [GIL_696] Pick Pocket - COST:2
    // - Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Echo</b>
    //       Add a random card to your hand
    //       <i>(from your opponent's class).</i>
    // --------------------------------------------------------
    // GameTag:
    // - ECHO = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [GIL_827] Blink Fox - COST:3 [ATK:3/HP:3]
    // - Race: Beast, Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a random card to your hand
    //       <i>(from your opponent's class).</i>
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [GIL_902] Cutthroat Buccaneer - COST:3 [ATK:2/HP:4]
    // - Race: Pirate, Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Give your weapon +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
}

void GilneasCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void GilneasCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- MINION - SHAMAN
    // [GIL_531] Witch's Apprentice - COST:1 [ATK:0/HP:1]
    // - Race: Beast, Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Add a random Shaman spell
    //       to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [GIL_583] Totem Cruncher - COST:4 [ATK:2/HP:3]
    // - Race: Beast, Set: Gilneas, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Destroy your Totems.
    //       Gain +2/+2 for each destroyed.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [GIL_586] Earthen Might - COST:2
    // - Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give a minion +2/+2. If it's an Elemental,
    //       add a random Elemental to your hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [GIL_600] Zap! - COST:0
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 2 damage to a minion. <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // - OVERLOAD_OWED = 1
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [GIL_678] Ghost Light Angler - COST:2 [ATK:2/HP:2]
    // - Race: Murloc, Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Echo</b>
    // --------------------------------------------------------
    // GameTag:
    // - ECHO = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [GIL_807] Bogshaper - COST:7 [ATK:4/HP:8]
    // - Race: Elemental, Set: Gilneas, Rarity: Epic
    // --------------------------------------------------------
    // Text: Whenever you cast a spell,
    //       draw a minion from your deck.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [GIL_820] Shudderwock - COST:9 [ATK:6/HP:6]
    // - Set: Gilneas, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Repeat all other <b>Battlecries</b>
    //       from cards you played this game
    //       <i>(targets chosen randomly)</i>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - 960 = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [GIL_836] Blazing Invocation - COST:1
    // - Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Discover</b> a <b>Battlecry</b> minion.
    // --------------------------------------------------------
    // RefTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------
}

void GilneasCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void GilneasCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - WARLOCK
    // [GIL_191] Fiendish Circle - COST:3
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: Summon four 1/1 Imps.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("GIL_191t", 4));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("GIL_191", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [GIL_508] Duskbat - COST:3 [ATK:2/HP:4]
    // - Race: Beast, Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your hero took damage this turn,
    //       summon two 1/1 Bats.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [GIL_515] Ratcatcher - COST:3 [ATK:2/HP:2]
    // - Set: Gilneas, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Battlecry:</b> Destroy a friendly minion and
    //       gain its Attack and Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - RUSH = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [GIL_543] Dark Possession - COST:1
    // - Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 2 damage to a friendly character.
    //       <b>Discover</b> a Demon.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    // - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [GIL_565] Deathweb Spider - COST:5 [ATK:4/HP:6]
    // - Race: Beast, Set: Gilneas, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your hero took damage
    //       this turn, gain <b>Lifesteal</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [GIL_608] Witchwood Imp - COST:1 [ATK:1/HP:1]
    // - Race: Demon, Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //       <b>Deathrattle:</b> Give a random friendly minion
    //       +2 Health.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [GIL_618] Glinda Crowskin - COST:6 [ATK:3/HP:7]
    // - Set: Gilneas, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Minions in your hand have <b>Echo</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - ECHO = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [GIL_665] Curse of Weakness - COST:2
    // - Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Echo</b>
    //       Give all enemy minions -2 Attack until your next turn.
    // --------------------------------------------------------
    // GameTag:
    // - ECHO = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [GIL_693] Blood Witch - COST:4 [ATK:3/HP:6]
    // - Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       deal 1 damage to your hero.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [GIL_825] Lord Godfrey - COST:7 [ATK:4/HP:4]
    // - Set: Gilneas, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 2 damage to all other minions.
    //       If any die, repeat this <b>Battlecry</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void GilneasCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - WARLOCK
    // [GIL_191t] Imp (*) - COST:1 [ATK:1/HP:1]
    // - Race: Demon, Set: Gilneas
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("GIL_191t", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [GIL_508t] Bat (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Gilneas
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [GIL_608e] Infusion (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: +2 Health.
    // --------------------------------------------------------
}

void GilneasCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - WARRIOR
    // [GIL_113] Rabid Worgen - COST:3 [ATK:3/HP:3]
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [GIL_152] Blackhowl Gunspire - COST:7 [ATK:3/HP:8]
    // - Set: Gilneas, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Can't attack. Whenever this minion takes damage,
    //       deal 3 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CANT_ATTACK = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [GIL_155] Redband Wasp - COST:2 [ATK:1/HP:3]
    // - Race: Beast, Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       Has +3 Attack while damaged.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [GIL_537] Deadly Arsenal - COST:6
    // - Set: Gilneas, Rarity: Epic
    // --------------------------------------------------------
    // Text: Reveal a weapon from your deck.
    //       Deal its Attack to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [GIL_547] Darius Crowley - COST:5 [ATK:4/HP:5]
    // - Set: Gilneas, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       After this attacks and kills a minion, gain +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SELF;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsDefenderDead())
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "GIL_547e", EntityType::SOURCE) };
    cards.emplace("GIL_547", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [GIL_580] Town Crier - COST:1 [ATK:1/HP:2]
    // - Set: Gilneas, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a <b>Rush</b> minion
    //       from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [GIL_653] Woodcutter's Axe - COST:2 [ATK:2/HP:0]
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give +2/+1 to a random
    //       friendly <b>Rush</b> minion.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [GIL_654] Warpath - COST:2
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Echo</b>
    //       Deal 1 damage to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - ECHO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [GIL_655] Festeroot Hulk - COST:5 [ATK:2/HP:7]
    // - Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: After a friendly minion attacks, gain +1 Attack.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [GIL_803] Militia Commander - COST:4 [ATK:2/HP:5]
    // - Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Battlecry:</b> Gain +3 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - RUSH = 1
    // --------------------------------------------------------
}

void GilneasCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [GIL_803e] Reckless (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: +3 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
}

void GilneasCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_117] Worgen Abomination - COST:7 [ATK:6/HP:6]
    // - Set: Gilneas, Rarity: Epic
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       deal 2 damage to all other damaged minions.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_118] Deranged Doctor - COST:8 [ATK:8/HP:8]
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Restore 8 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_119] Cauldron Elemental - COST:8 [ATK:7/HP:7]
    // - Race: Elemental, Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: Your other Elementals have +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_120] Furious Ettin - COST:7 [ATK:5/HP:9]
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_121] Darkmire Moonkin - COST:7 [ATK:2/HP:8]
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Spell Damage +2</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 2
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_124] Mossy Horror - COST:6 [ATK:2/HP:7]
    // - Set: Gilneas, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy all other minions
    //       with 2 or less Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::ALL_MINIONS_NOSOURCE));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsTagValue(GameTag::ATK, 2, RelaSign::LEQ)) }));
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::STACK));
    cards.emplace("GIL_124", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_125] Mad Hatter - COST:4 [ATK:3/HP:2]
    // - Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Randomly toss 3 hats
    //       to other minions. Each hat gives +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_WITH_RACE = 11
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_143] Vicious Scalehide - COST:2 [ATK:1/HP:3]
    // - Race: Beast, Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    //       <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_198] Azalina Soulthief - COST:7 [ATK:3/HP:3]
    // - Set: Gilneas, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Replace your hand
    //       with a copy of your opponent's.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_201] Pumpkin Peasant - COST:3 [ATK:2/HP:4]
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    //       Each turn this is in your hand,
    //       swap its Attack and Health.
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_202] Gilnean Royal Guard - COST:8 [ATK:3/HP:8]
    // - Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: [x]<b>Divine Shield</b>, <b>Rush</b>
    //       Each turn this is in your hand,
    //       swap its Attack and Health.
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_207] Phantom Militia - COST:3 [ATK:2/HP:4]
    // - Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Echo</b>
    //       <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - ECHO = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_212] Ravencaller - COST:3 [ATK:2/HP:1]
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add two random 1-Cost minions
    //       to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_213] Tanglefur Mystic - COST:3 [ATK:3/HP:4]
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a random 2-Cost minion
    //       to each player's hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_513] Lost Spirit - COST:2 [ATK:1/HP:1]
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give your minions +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_526] Wyrmguard - COST:7 [ATK:3/HP:11]
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       gain +1 Attack and <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_527] Felsoul Inquisitor - COST:4 [ATK:1/HP:6]
    // - Race: Demon, Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    //       <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_528] Swift Messenger - COST:4 [ATK:2/HP:6]
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       Each turn this is in your hand,
    //       swap its Attack and Health.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_529] Spellshifter - COST:2 [ATK:1/HP:4]
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    //       Each turn this is in your hand,
    //       swap its Attack and Health.
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_534] Hench-Clan Thug - COST:3 [ATK:3/HP:3]
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: After your hero attacks, give this minion +1/+1.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_558] Swamp Leech - COST:1 [ATK:2/HP:1]
    // - Race: Beast, Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_561] Blackwald Pixie - COST:3 [ATK:3/HP:4]
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Refresh your Hero Power.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_578] Countess Ashmore - COST:7 [ATK:6/HP:6]
    // - Set: Gilneas, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a <b>Rush</b>,
    //       <b>Lifesteal</b>, and <b>Deathrattle</b>
    //       card from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // - LIFESTEAL = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_581] Sandbinder - COST:4 [ATK:2/HP:4]
    // - Set: Gilneas, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw an Elemental from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_584] Witchwood Piper - COST:4 [ATK:3/HP:3]
    // - Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw the lowest Cost minion
    //       from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_601] Scaleworm - COST:4 [ATK:4/HP:4]
    // - Race: Beast, Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       gain +1 Attack and <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_614] Voodoo Doll - COST:3 [ATK:1/HP:1]
    // - Set: Gilneas, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a minion.
    //       <b>Deathrattle:</b> Destroy the chosen minion.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_616] Splitting Festeroot - COST:8 [ATK:4/HP:4]
    // - Set: Gilneas, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon two 2/2 Splitting Saplings.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_620] Dollmaster Dorian - COST:5 [ATK:2/HP:6]
    // - Set: Gilneas, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever you draw a minion, summon a 1/1 copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_622] Lifedrinker - COST:4 [ATK:3/HP:3]
    // - Race: Beast, Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage to the enemy hero.
    //       Restore 3 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 3));
    cardDef.power.AddPowerTask(std::make_shared<HealTask>(EntityType::HERO, 3));
    cards.emplace("GIL_622", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_623] Witchwood Grizzly - COST:5 [ATK:3/HP:12]
    // - Race: Beast, Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Lose 1 Health for each card
    //       in your opponent's hand.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_624] Night Prowler - COST:4 [ATK:3/HP:3]
    // - Race: Beast, Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If this is the only minion
    //       in the battlefield, gain +3/+3.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_646] Clockwork Automaton - COST:5 [ATK:4/HP:4]
    // - Race: Mechanical, Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: Double the damage and healing of your Hero Power.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_648] Chief Inspector - COST:5 [ATK:4/HP:6]
    // - Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy all enemy <b>Secrets</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_667] Rotten Applebaum - COST:5 [ATK:4/HP:5]
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Restore 4 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_680] Walnut Sprite - COST:3 [ATK:3/HP:3]
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Echo</b>
    // --------------------------------------------------------
    // GameTag:
    // - ECHO = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_681] Nightmare Amalgam - COST:3 [ATK:3/HP:4]
    // - Race: All, Set: Gilneas, Rarity: Epic
    // --------------------------------------------------------
    // Text: <i>This is an Elemental, Mech, Demon, Murloc,
    //       Dragon, Beast, Pirate and Totem.</i>
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_682] Muck Hunter - COST:5 [ATK:5/HP:8]
    // - Set: Gilneas, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Battlecry:</b> Summon two 2/1_Mucklings
    //       for your opponent.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_683] Marsh Drake - COST:3 [ATK:5/HP:4]
    // - Race: Dragon, Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 2/1 <b>Poisonous</b>
    //       Drakeslayer for your opponent.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - POISONOUS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_809] Unpowered Steambot - COST:4 [ATK:0/HP:9]
    // - Race: Mechanical, Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_815] Baleful Banker - COST:2 [ATK:2/HP:2]
    // - Set: Gilneas, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a friendly minion.
    //       Shuffle a copy of it into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_816] Swamp Dragon Egg - COST:1 [ATK:0/HP:3]
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a random Dragon to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_819] Witch's Cauldron - COST:3 [ATK:0/HP:4]
    // - Set: Gilneas, Rarity: Epic
    // --------------------------------------------------------
    // Text: After a friendly minion dies,
    //       add a random Shaman spell to your hand.
    // --------------------------------------------------------
}

void GilneasCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_000] Echo Enchant (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: Destroy card if in hand at the end of turn.
    // --------------------------------------------------------
    // GameTag:
    // - GHOSTLY = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_119e] Toil and Trouble (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: Cauldron Elemental is granting this +2 Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_125e] Hat (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_128e] Mark of Emeriss (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: Doubled Attack and Health.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_130e] Fable (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_142e] Shifting (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: Transforming into random card from your opponent's hand.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_155e] Enraged (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: +3 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_200e] Swapped Stats (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // GameTag:
    // - ENCHANTMENT_INVISIBLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_201t] Pumpkin Peasant (*) - COST:3 [ATK:4/HP:2]
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    //       Each turn this is in your hand,
    //       swap its Attack and Health.
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_202t] Gilnean Royal Guard (*) - COST:8 [ATK:8/HP:3]
    // - Set: Gilneas, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>, <b>Rush</b>
    //       Each turn this is in your hand,
    //       swap its Attack and Health.
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_203e] Rebuked (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: Your spells cost (5) more this turn.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_507e] Bewitched (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: Increased Health.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_510e] Misty (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_513e] Spooky Sacrifice (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_515e] Engorged (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_526e] For the Dragonhoard! (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: +1 Attack and <b>Taunt</b>.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_528t] Swift Messenger (*) - COST:4 [ATK:6/HP:2]
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       Each turn this is in your hand,
    //       swap its Attack and Health.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_529t] Spellshifter (*) - COST:2 [ATK:4/HP:1]
    // - Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    //       Each turn this is in your hand,
    //       swap its Attack and Health.
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_534t] Reinforced (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_547e] Bloodfang (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Effects::AttackHealthN(2)));
    cards.emplace("GIL_547e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_583e] Crunched (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_586e] Storm Hardened (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_596e] Sterling (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_601e] Bold Worm (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: +1 Attack and <b>Rush</b>.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_607e] Viletoxin (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_614e1] Voodoo Doll Cursed (*) - COST:0
    // - Set: Gilneas, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroyed when Voodoo Doll is destroyed.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_614e2] Voodoo Doll Cursing (*) - COST:0
    // - Set: Gilneas, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Destroy {0}.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_616t] Splitting Sapling (*) - COST:3 [ATK:2/HP:2]
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon two 1/1 Woodchips.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_616t2] Woodchip (*) - COST:1 [ATK:1/HP:1]
    // - Set: Gilneas
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_620e] Creepy Doll (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: Dollmaster Dorian made a 1/1 copy.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_623e] Grizzled (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: Decreased Health.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_624e] Stalking (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: +3/+3.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_640e] Rare Find! (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_650e] Hounded! (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: Houndmaster Shaw grants <b>Rush</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("GIL_650e"));
    cards.emplace("GIL_650e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_653e] Woodcutter (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: +2/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_655e] Grown (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_658e] Splintergrafted (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: Splintergraft made this 10/10.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_665e] Curse of Weakness (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: -2 Attack until next turn.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_672e] Spooky (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: Increased Durability.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_682t] Muckling (*) - COST:1 [ATK:2/HP:1]
    // - Set: Gilneas
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [GIL_683t] Drakeslayer (*) - COST:1 [ATK:2/HP:1]
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - POISONOUS = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_692e] Curse of Ur (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: Your <b>Hero Power</b> costs (1).
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_800e2] Badsong (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: Costs (0).
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_828e] Dire Frenzy (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: +3/+3.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("GIL_828e"));
    cards.emplace("GIL_828e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_837e] Moth Dust (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: Doubled Health.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_902e] Sharpened (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [GIL_905e] Corrosive Breath (*) - COST:0
    // - Set: Gilneas
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_828t7] Vicious Scalehide (*) - COST:2 [ATK:1/HP:3]
    // - Race: Beast, Set: Gilneas, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    //       <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // - RUSH = 1
    // --------------------------------------------------------
}

void GilneasCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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