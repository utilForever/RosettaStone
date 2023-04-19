// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/CardSets/Expert1CardsGen.hpp>
#include <Rosetta/PlayMode/Cards/CardPowers.hpp>

namespace RosettaStone::PlayMode
{
void Expert1CardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- HERO - WARLOCK
    // [EX1_323] Lord Jaraxxus - COST:9 [ATK:0/HP:30]
    // - Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Equip a 3/8 Blood Fury.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<WeaponTask>("EX1_323w"));
    cardDef.property.heroPowerDbfID = 1178;
    cards.emplace("EX1_323", cardDef);
}

void Expert1CardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------ HERO_POWER - PRIEST
    // [EX1_625t] Mind Spike (*) - COST:2
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Deal 2 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("EX1_625t", cardDef);

    // ------------------------------------ HERO_POWER - PRIEST
    // [EX1_625t2] Mind Shatter (*) - COST:2
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Deal 3 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("EX1_625t2", cardDef);

    // ----------------------------------- HERO_POWER - WARLOCK
    // [EX1_tk33] INFERNO! (*) - COST:2
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Summon a 6/6 Infernal.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("EX1_tk34"));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("EX1_tk33", cardDef);
}

void Expert1CardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ SPELL - DRUID
    // [EX1_154] Wrath - COST:2
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Deal 3 damage to a minion;
    //       or 1 damage and draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cardDef.property.chooseCardIDs = ChooseCardIDs{ "EX1_154a", "EX1_154b" };
    cards.emplace("EX1_154", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_155] Mark of Nature - COST:3
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Give a minion +4 Attack;
    //       or +4 Health and <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cardDef.property.chooseCardIDs = ChooseCardIDs{ "EX1_155a", "EX1_155b" };
    cards.emplace("EX1_155", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_158] Soul of the Forest - COST:4
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Give your minions
    //       "<b>Deathrattle:</b> Summon a 2/2 Treant."
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_158e", EntityType::MINIONS));
    cards.emplace("EX1_158", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_160] Power of the Wild - COST:2
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Give your minions +1/+1;
    //       or Summon a 3/2 Panther.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.chooseCardIDs = ChooseCardIDs{ "EX1_160a", "EX1_160b" };
    cards.emplace("EX1_160", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_161] Naturalize - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Destroy a minion. Your opponent draws 2 cards.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(std::make_shared<DrawOpTask>(2));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("EX1_161", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_164] Nourish - COST:5
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Gain 2 Mana Crystals;
    //       or Draw 3 cards.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.chooseCardIDs = ChooseCardIDs{ "EX1_164a", "EX1_164b" };
    cards.emplace("EX1_164", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [EX1_165] Druid of the Claw - COST:5 [ATK:5/HP:4]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Transform into a 5/4 with <b>Charge</b>;
    //       or a 5/6 with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<TransformTask>(EntityType::SOURCE, "OG_044a"));
    cardDef.property.chooseCardIDs = ChooseCardIDs{ "EX1_165a", "EX1_165b" };
    cards.emplace("EX1_165", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [EX1_166] Keeper of the Grove - COST:4 [ATK:2/HP:4]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Deal 2 damage;
    //       or <b>Silence</b> a minion.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    // RefTag:
    // - SILENCE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cardDef.property.chooseCardIDs = ChooseCardIDs{ "EX1_166a", "EX1_166b" };
    cards.emplace("EX1_166", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [EX1_178] Ancient of War - COST:7 [ATK:5/HP:5]
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Choose One -</b>+5 Attack;
    //       or +5 Health and <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.chooseCardIDs = ChooseCardIDs{ "EX1_178a", "EX1_178b" };
    cards.emplace("EX1_178", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_183] Gift of the Wild - COST:8
    // - Set: Expert1, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Give your minions +2/+2 and <b>Taunt</b>.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_183e", EntityType::MINIONS));
    cards.emplace("EX1_183", cardDef);

    // ------------------------------------------- SPELL - DRUID
    // [EX1_570] Bite - COST:4
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give your hero +4 Attack this turn. Gain 4 Armor.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_570e", EntityType::HERO));
    cardDef.power.AddPowerTask(std::make_shared<ArmorTask>(4));
    cards.emplace("EX1_570", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_571] Force of Nature - COST:5
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Summon three 2/2 Treants.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("EX1_tk9", 3));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("EX1_571", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [EX1_573] Cenarius - COST:8 [ATK:5/HP:8]
    // - Faction: Neutral, Set: Expert1, Rarity: Legendary
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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.chooseCardIDs = ChooseCardIDs{ "EX1_573a", "EX1_573b" };
    cards.emplace("EX1_573", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_578] Savagery - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal damage equal to your hero's Attack to a minion.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::HERO, GameTag::ATK));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageNumberTask>(EntityType::TARGET, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("EX1_578", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [NEW1_007] Starfall - COST:5
    // - Set: Expert1, Rarity: Rare
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Deal 5 damage to a minion;
    //       or 2 damage to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 } };
    cardDef.property.chooseCardIDs = ChooseCardIDs{ "NEW1_007a", "NEW1_007b" };
    cards.emplace("NEW1_007", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [NEW1_008] Ancient of Lore - COST:7 [ATK:5/HP:5]
    // - Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Draw 2 cards;
    //       or Restore 5 Health.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cardDef.property.chooseCardIDs = ChooseCardIDs{ "NEW1_008a", "NEW1_008b" };
    cards.emplace("NEW1_008", cardDef);
}

void Expert1CardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ SPELL - DRUID
    // [EX1_154a] Solar Wrath (*) - COST:0
    // - Faction: Neutral, Set: Expert1
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Deal 3 damage to a minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("EX1_154a", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_154b] Nature's Wrath (*) - COST:0
    // - Faction: Neutral, Set: Expert1
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Deal 1 damage to a minion. Draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1, true));
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("EX1_154b", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_155a] Tiger's Fury (*) - COST:0
    // - Faction: Neutral, Set: Expert1
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: +4 Attack.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_155ae", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("EX1_155a", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_155ae] Mark of Nature (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: This minion has +4 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_155ae"));
    cards.emplace("EX1_155ae", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_155b] Thick Hide (*) - COST:0
    // - Faction: Neutral, Set: Expert1
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: +4 Health and <b>Taunt</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_155be", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("EX1_155b", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_155be] Mark of Nature (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: This minion has +4 Health and <b>Taunt</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_155be"));
    cards.emplace("EX1_155be", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_166a] Moonfire (*) - COST:0
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: Deal 2 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("EX1_166a", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_166b] Dispel (*) - COST:0
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: <b>Silence</b> a minion.
    // --------------------------------------------------------
    // GameTag:
    // - SILENCE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SilenceTask>(EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("EX1_166b", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [EX1_158e] Soul of the Forest (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Deathrattle: Summon a 2/2 Treant.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("EX1_158t", SummonSide::DEFAULT));
    cards.emplace("EX1_158e", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [EX1_158t] Treant (*) - COST:2 [ATK:2/HP:2]
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_158t", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_160a] Summon a Panther (*) - COST:2
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: Summon a 3/2 Panther.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("EX1_160t", SummonSide::SPELL));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("EX1_160a", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_160b] Leader of the Pack (*) - COST:2
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: Give your minions +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_160be", EntityType::MINIONS));
    cards.emplace("EX1_160b", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [EX1_160be] Leader of the Pack (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_160be"));
    cards.emplace("EX1_160be", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [EX1_160t] Panther (*) - COST:2 [ATK:3/HP:2]
    // - Race: Beast, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_160t", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_164a] Rampant Growth (*) - COST:5
    // - Faction: Neutral, Set: Expert1
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Gain 2 Mana Crystals.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ManaCrystalTask>(2, true));
    cards.emplace("EX1_164a", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_164b] Enrich (*) - COST:5
    // - Faction: Neutral, Set: Expert1
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Draw 3 cards.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(3));
    cards.emplace("EX1_164b", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [EX1_165a] Cat Form (*) - COST:5 [ATK:5/HP:4]
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<TransformTask>(EntityType::SOURCE, "EX1_165t1"));
    cards.emplace("EX1_165a", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [EX1_165b] Bear Form (*) - COST:5 [ATK:5/HP:6]
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<TransformTask>(EntityType::SOURCE, "EX1_165t2"));
    cards.emplace("EX1_165b", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [EX1_165t1] Druid of the Claw (*) - COST:5 [ATK:5/HP:4]
    // - Race: Beast, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_165t1", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [EX1_165t2] Druid of the Claw (*) - COST:5 [ATK:5/HP:6]
    // - Race: Beast, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_165t2", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_178a] Rooted (*) - COST:7
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: +5 Health and <b>Taunt</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_178ae", EntityType::SOURCE));
    cards.emplace("EX1_178a", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [EX1_178ae] Rooted (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +5 Health and <b>Taunt</b>
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_178ae"));
    cards.emplace("EX1_178ae", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_178b] Uproot (*) - COST:7
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: +5 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_178be", EntityType::SOURCE));
    cards.emplace("EX1_178b", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [EX1_178be] Uprooted (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +5 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_178be"));
    cards.emplace("EX1_178be", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [EX1_183e] Gift of the Wild (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +2/+2 and <b>Taunt</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_183e"));
    cards.emplace("EX1_183e", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [EX1_570e] Bite - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +4 Attack this turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_570e"));
    cards.emplace("EX1_570e", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_573a] Demigod's Favor (*) - COST:0
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: Give your other minions +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "EX1_573ae", EntityType::MINIONS_NOSOURCE));
    cards.emplace("EX1_573a", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [EX1_573ae] Demigod's Favor (*) - COST:0
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_573ae"));
    cards.emplace("EX1_573ae", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [EX1_573b] Shan'do's Lesson (*) - COST:0
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: Summon two 2/2 Treants with <b>Taunt</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{ std::make_shared<SummonTask>("EX1_573t", SummonSide::RIGHT),
                  std::make_shared<SummonTask>("EX1_573t", SummonSide::LEFT) },
        1));
    cards.emplace("EX1_573b", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [EX1_573t] Treant (*) - COST:2 [ATK:2/HP:2]
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_573t", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [EX1_tk9] Treant (*) - COST:2 [ATK:2/HP:2]
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_tk9", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [NEW1_007a] Stellar Drift (*) - COST:0
    // - Set: Expert1
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Deal 2 damage to all enemy minions.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 2, true));
    cards.emplace("NEW1_007a", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [NEW1_007b] Starlord (*) - COST:0
    // - Set: Expert1
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Deal 5 damage to a minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 5, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("NEW1_007b", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [NEW1_008a] Ancient Teachings (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Draw 2 cards.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(2));
    cards.emplace("NEW1_008a", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [NEW1_008b] Ancient Secrets (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Restore 5 Health.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<HealTask>(EntityType::TARGET, 5));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("NEW1_008b", cardDef);
}

void Expert1CardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- WEAPON - HUNTER
    // [DS1_188] Gladiator's Longbow - COST:7 [ATK:5/HP:0]
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: Your hero is <b>Immune</b> while attacking.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TARGET));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "DS1_188e", EntityType::HERO) };
    cards.emplace("DS1_188", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [EX1_531] Scavenging Hyena - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever a friendly Beast dies, gain +2/+1.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::DEATH));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::BEAST))
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_531e", EntityType::SOURCE) };
    cards.emplace("EX1_531", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [EX1_533] Misdirection - COST:2
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When an enemy attacks your hero,
    //       instead it attacks another random character.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    cardDef.power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsProposedDefender(CardType::HERO)) };
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<IncludeTask>(
            EntityType::ALL,
            EntityTypeList{ EntityType::TARGET, EntityType::HERO }),
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsNotDead()),
            std::make_shared<SelfCondition>(SelfCondition::IsNotImmune()) }),
        std::make_shared<ConditionTask>(
            EntityType::STACK, SelfCondList{ std::make_shared<SelfCondition>(
                                   SelfCondition::IsInZone(ZoneType::PLAY)) }),
        std::make_shared<FlagTask>(
            true,
            TaskList{ std::make_shared<ConditionTask>(
                EntityType::TARGET,
                SelfCondList{ std::make_shared<SelfCondition>(
                                  SelfCondition::IsInZone(ZoneType::PLAY)),
                              std::make_shared<SelfCondition>(
                                  SelfCondition::IsNotDead()) }) }),
        std::make_shared<FlagTask>(
            true, ComplexTask::ActivateSecret(TaskList{
                      std::make_shared<RandomTask>(EntityType::STACK, 1),
                      std::make_shared<ChangeAttackingTargetTask>(
                          EntityType::TARGET, EntityType::STACK) }))
    };
    cards.emplace("EX1_533", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [EX1_534] Savannah Highmane - COST:6 [ATK:6/HP:5]
    // - Race: Beast, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon two 2/2 Hyenas.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("EX1_534t", 2, SummonSide::DEATHRATTLE));
    cards.emplace("EX1_534", cardDef);

    // ---------------------------------------- WEAPON - HUNTER
    // [EX1_536] Eaglehorn Bow - COST:3 [ATK:3/HP:0]
    // - Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever a friendly <b>Secret</b> is revealed,
    //       gain +1 Durability.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::SECRET_REVEALED));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_536e", EntityType::WEAPON) };
    cards.emplace("EX1_536", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [EX1_537] Explosive Shot - COST:5
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Deal 5 damage to a minion and 2 damage
    //       to adjacent ones.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 5, true));
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeAdjacentTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::STACK, 2, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("EX1_537", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [EX1_538] Unleash the Hounds - COST:3
    // - Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: For each enemy minion,
    //       summon a 1/1 Hound with <b>Charge</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_ENEMY_MINIONS = 1
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<CountTask>(EntityType::ENEMY_MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<EnqueueNumberTask>(TaskList{
        std::make_shared<SummonTask>("EX1_538t", SummonSide::SPELL) }));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_MINIMUM_ENEMY_MINIONS, 1 },
                  { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("EX1_538", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_543", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [EX1_544] Flare - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: All minions lose <b>Stealth</b>.
    //       Destroy all enemy <b>Secrets</b>. Draw a card.
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RevealStealthTask>(EntityType::ALL_MINIONS));
    cardDef.power.AddPowerTask(
        std::make_shared<MoveToGraveyardTask>(EntityType::ENEMY_SECRETS));
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace("EX1_544", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [EX1_549] Bestial Wrath - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: Give a friendly Beast +2 Attack and <b>Immune</b> this turn.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_TARGET_WITH_RACE = 20
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_549o", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_TARGET_WITH_RACE, 20 },
                                          { PlayReq::REQ_FRIENDLY_TARGET, 0 } };
    cards.emplace("EX1_549", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [EX1_554] Snake Trap - COST:2
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When one of your minions is attacked,
    //       summon three 1/1 Snakes.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY;
    cardDef.power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(
                          SelfCondition::IsProposedDefender(CardType::MINION)),
                      std::make_shared<SelfCondition>(
                          SelfCondition::IsEventTargetFieldNotFull()) };
    cardDef.power.GetTrigger()->tasks = ComplexTask::ActivateSecret(
        TaskList{ std::make_shared<SummonTask>("EX1_554t", 3) });
    cards.emplace("EX1_554", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [EX1_609] Snipe - COST:2
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After your opponent plays a minion,
    //       deal 4 damage to it.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_PLAY_MINION));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY_MINIONS;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<ConditionTask>(
            EntityType::TARGET, SelfCondList{ std::make_shared<SelfCondition>(
                                    SelfCondition::IsNotDead()) }),
        std::make_shared<FlagTask>(
            true,
            ComplexTask::ActivateSecret(TaskList{
                std::make_shared<DamageTask>(EntityType::TARGET, 4, true) }))
    };
    cards.emplace("EX1_609", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [EX1_610] Explosive Trap - COST:2
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your hero is attacked,
    //       deal 2 damage to all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY;
    cardDef.power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsProposedDefender(CardType::HERO)) };
    cardDef.power.GetTrigger()->tasks = ComplexTask::ActivateSecret(
        TaskList{ std::make_shared<DamageTask>(EntityType::ENEMIES, 2, true) });
    cards.emplace("EX1_610", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [EX1_611] Freezing Trap - COST:2
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When an enemy minion attacks,
    //       return it to its owner's hand. It costs (2) more.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY_MINIONS;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<ConditionTask>(
            EntityType::TARGET, SelfCondList{ std::make_shared<SelfCondition>(
                                    SelfCondition::IsNotDead()) }),
        std::make_shared<FlagTask>(
            true, ComplexTask::ActivateSecret(TaskList{
                      std::make_shared<ReturnHandTask>(EntityType::TARGET),
                      std::make_shared<AddAuraEffectTask>(
                          Effects::AddCost(2), EntityType::TARGET) }))
    };
    cards.emplace("EX1_611", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [EX1_617] Deadly Shot - COST:3
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Destroy a random enemy minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_ENEMY_MINIONS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(ComplexTask::DestroyRandomEnemyMinion(1));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_MINIMUM_ENEMY_MINIONS, 1 } };
    cards.emplace("EX1_617", cardDef);
}

void Expert1CardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [DS1_188e] Gladiator's Longbow enchantment (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::Immune));
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RemoveEnchantmentTask>()
    };
    cards.emplace("DS1_188e", cardDef);

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [EX1_531e] Well Fed (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased Attack and Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<OngoingEnchant>(std::vector<std::shared_ptr<IEffect>>{
            Effects::AttackN(2), Effects::HealthN(1) }));
    cards.emplace("EX1_531e", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [EX1_534t] Hyena (*) - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_534t", cardDef);

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [EX1_536e] Upgraded (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased Durability.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<OngoingEnchant>(
        std::vector<std::shared_ptr<IEffect>>{ Effects::DurabilityN(1) }));
    cards.emplace("EX1_536e", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [EX1_538t] Hound (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Expert1
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_538t", cardDef);

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [EX1_549o] Bestial Wrath (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +2 Attack and <b>Immune</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_549o"));
    cards.emplace("EX1_549o", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [EX1_554t] Snake (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_554t", cardDef);
}

void Expert1CardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------- SPELL - MAGE
    // [CS2_028] Blizzard - COST:6
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: Deal 2 damage to all enemy minions
    //       and <b>Freeze</b> them.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 2, true));
    cardDef.power.AddPowerTask(
        std::make_shared<FreezeTask>(EntityType::ENEMY_MINIONS));
    cards.emplace("CS2_028", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [CS2_031] Ice Lance - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Freeze</b> a character.
    //       If it was already <b>Frozen</b>, deal 4 damage instead.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::TARGET, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsFrozen()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 4, true) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        false, TaskList{ std::make_shared<FreezeTask>(EntityType::TARGET) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("CS2_031", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [EX1_179] Icicle - COST:2
    // - Set: Expert1, Rarity: Epic
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: Deal 2 damage to a minion.
    //       If it's <b>Frozen</b>, draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, true));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::TARGET, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsFrozen()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DrawTask>(1) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("EX1_179", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [EX1_180] Tome of Intellect - COST:1
    // - Set: Expert1, Rarity: Common
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Add a random Mage spell to your hand.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomCardTask>(CardType::SPELL, CardClass::MAGE));
    cardDef.power.AddPowerTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cards.emplace("EX1_180", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [EX1_274] Ethereal Arcanist - COST:4 [ATK:3/HP:3]
    // - Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: If you control a <b>Secret</b> at the end of your turn,
    //       gain +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsControllingSecret())
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_274e", EntityType::SOURCE) };
    cards.emplace("EX1_274", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [EX1_275] Cone of Cold - COST:3
    // - Faction: Neutral, Set: Expert1, Rarity: Common
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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeAdjacentTask>(EntityType::TARGET, true));
    cardDef.power.AddPowerTask(std::make_shared<FreezeTask>(EntityType::STACK));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::STACK, 1, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("EX1_275", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [EX1_279] Pyroblast - COST:10
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Deal 10 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 10, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("EX1_279", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [EX1_287] Counterspell - COST:3
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
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
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY_SPELLS;
    cardDef.power.GetTrigger()->tasks =
        ComplexTask::ActivateSecret(TaskList{ std::make_shared<SetGameTagTask>(
            EntityType::TARGET, GameTag::CANT_PLAY, 1) });
    cardDef.power.GetTrigger()->fastExecution = true;
    cards.emplace("EX1_287", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [EX1_289] Ice Barrier - COST:3
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your hero is attacked,
    //       gain 8 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    cardDef.power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsProposedDefender(CardType::HERO)) };
    cardDef.power.GetTrigger()->tasks =
        ComplexTask::ActivateSecret(TaskList{ std::make_shared<ArmorTask>(8) });
    cards.emplace("EX1_289", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [EX1_294] Mirror Entity - COST:3
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After your opponent plays a minion,
    //       summon a copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_PLAY_MINION));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY_MINIONS;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<ConditionTask>(
            EntityType::EVENT_SOURCE,
            SelfCondList{
                std::make_shared<SelfCondition>(SelfCondition::IsNotDead()),
                std::make_shared<SelfCondition>(
                    SelfCondition::IsNotUntouchable()),
                std::make_shared<SelfCondition>(
                    SelfCondition::IsOpFieldNotFull()) }),
        std::make_shared<FlagTask>(
            true,
            ComplexTask::ActivateSecret(TaskList{
                std::make_shared<SummonCopyTask>(EntityType::EVENT_SOURCE) }))
    };
    cards.emplace("EX1_294", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [EX1_295] Ice Block - COST:3
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your hero takes fatal damage,
    //       prevent it and become <b>Immune</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::PREDAMAGE));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsHeroFatalPreDamaged())
    };
    cardDef.power.GetTrigger()->fastExecution = true;
    cardDef.power.GetTrigger()->tasks = ComplexTask::ActivateSecret(TaskList{
        std::make_shared<AddEnchantmentTask>("EX1_295o", EntityType::HERO) });
    cards.emplace("EX1_295", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [EX1_559] Archmage Antonidas - COST:7 [ATK:5/HP:7]
    // - Faction: Neutral, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever you cast a spell,
    //       add a 'Fireball' spell to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddCardTask>(
        EntityType::HAND, "CS2_029") };
    cards.emplace("EX1_559", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [EX1_594] Vaporize - COST:3
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When a minion attacks your hero,
    //       destroy it.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY_MINIONS;
    cardDef.power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsProposedDefender(CardType::HERO)) };
    cardDef.power.GetTrigger()->fastExecution = true;
    cardDef.power.GetTrigger()->tasks = ComplexTask::ActivateSecret(
        TaskList{ std::make_shared<DestroyTask>(EntityType::TARGET) });
    cards.emplace("EX1_594", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [EX1_608] Sorcerer's Apprentice - COST:4 [ATK:3/HP:2]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
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
    cards.emplace("EX1_608", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [EX1_612] Kirin Tor Mage - COST:3 [ATK:4/HP:3]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> The next <b>Secret</b>
    //       you play this turn costs (0).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_612o", EntityType::PLAYER));
    cards.emplace("EX1_612", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [NEW1_012] Mana Wyrm - COST:1 [ATK:1/HP:2]
    // - Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever you cast a spell, gain +1 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SPELLS;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "NEW1_012o", EntityType::SOURCE) };
    cards.emplace("NEW1_012", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [tt_010] Spellbender - COST:3
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When an enemy casts a spell on a minion,
    //       summon a 1/3 as the new target.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TARGET));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsSpellTargetingMinion())
    };
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<ConditionTask>(
            EntityType::SOURCE,
            SelfCondList{
                std::make_shared<SelfCondition>(
                    SelfCondition::IsFieldNotFull()),
                std::make_shared<SelfCondition>(
                    SelfCondition::IsTagValue(GameTag::CANT_PLAY, 0)) }),
        std::make_shared<FlagTask>(
            true, ComplexTask::ActivateSecret(TaskList{
                      std::make_shared<SummonTask>("tt_010a", SummonSide::SPELL,
                                                   true),
                      std::make_shared<IncludeTask>(
                          EntityType::SOURCE, std::vector<EntityType>(), true),
                      std::make_shared<IncludeTask>(
                          EntityType::TARGET, std::vector<EntityType>(), true),
                      std::make_shared<FuncPlayableTask>(
                          [=](const std::vector<Playable*>& playables) {
                              playables[2]->SetCardTarget(
                                  playables[0]->GetGameTag(GameTag::ENTITY_ID));
                              return playables;
                          }) }))
    };
    cards.emplace("tt_010", cardDef);
}

void Expert1CardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------- ENCHANTMENT - MAGE
    // [EX1_274e] Raw Power! (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Effects::AttackHealthN(2)));
    cards.emplace("EX1_274e", cardDef);

    // ------------------------------------- ENCHANTMENT - MAGE
    // [EX1_295o] Ice Block (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Your hero is <b>Immune</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_295o"));
    cards.emplace("EX1_295o", cardDef);

    // ------------------------------------- ENCHANTMENT - MAGE
    // [EX1_612o] Power of the Kirin Tor (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Your next Secret costs (0).
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::HAND, EffectList{ Effects::SetCost(0) }));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsSecret());
        aura->removeTrigger = { TriggerType::CAST_SPELL,
                                std::make_shared<SelfCondition>(
                                    SelfCondition::IsSecret()) };
    }
    cards.emplace("EX1_612o", cardDef);

    // ------------------------------------- ENCHANTMENT - MAGE
    // [NEW1_012o] Mana Gorged (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::AttackN(1)));
    cards.emplace("NEW1_012o", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [tt_010a] Spellbender - COST:0 [ATK:1/HP:3]
    // - Set: Expert1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("tt_010a", cardDef);
}

void Expert1CardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - PALADIN
    // [EX1_130] Noble Sacrifice - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When an enemy attacks,
    //       summon a 2/1 Defender as the new target.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ENEMY;
    cardDef.power.GetTrigger()->tasks = ComplexTask::ActivateSecret(TaskList{
        std::make_shared<SummonTask>("EX1_130a", SummonSide::SPELL, true),
        std::make_shared<ChangeAttackingTargetTask>(EntityType::TARGET,
                                                    EntityType::STACK) });
    cards.emplace("EX1_130", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [EX1_132] Eye for an Eye - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your hero takes damage,
    //       deal that much damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TAKE_DAMAGE));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = ComplexTask::ActivateSecret(TaskList{
        std::make_shared<GetEventNumberTask>(),
        std::make_shared<DamageNumberTask>(EntityType::ENEMY_HERO, true) });
    cards.emplace("EX1_132", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [EX1_136] Redemption - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When a friendly minion dies,
    //       return it to life with 1 Health.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::DEATH));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::MINIONS;
    cardDef.power.GetTrigger()->tasks = ComplexTask::ActivateSecret(TaskList{
        std::make_shared<CopyTask>(EntityType::TARGET, ZoneType::PLAY, 1, true),
        std::make_shared<FuncPlayableTask>(
            [=](const std::vector<Playable*>& playables) {
                const auto target = dynamic_cast<Minion*>(playables[0]);

                if (!target)
                {
                    return std::vector<Playable*>{};
                }

                target->SetDamage(target->GetHealth() - 1);

                return std::vector<Playable*>{ target };
            }) });
    cardDef.power.GetTrigger()->removeAfterTriggered = true;
    cards.emplace("EX1_136", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [EX1_184] Righteousness - COST:5
    // - Set: Expert1, Rarity: Rare
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Give your minions <b>Divine Shield</b>.
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SetGameTagTask>(
        EntityType::MINIONS, GameTag::DIVINE_SHIELD, 1));
    cards.emplace("EX1_184", cardDef);

    // ----------------------------------------- SPELL - PALADIN
    // [EX1_349] Divine Favor - COST:3
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Draw cards until you have as many in hand
    //       as your opponent.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<FuncNumberTask>([](const Playable* playable) {
            const int diffHands =
                playable->player->opponent->GetHandZone()->GetCount() -
                playable->player->GetHandZone()->GetCount();

            return diffHands > 0 ? diffHands : 0;
        }));
    cardDef.power.AddPowerTask(std::make_shared<DrawNumberTask>());
    cards.emplace("EX1_349", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [EX1_354] Lay on Hands - COST:8
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Restore 8 Health. Draw 3 cards.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<HealTask>(EntityType::TARGET, 8));
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(3));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("EX1_354", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [EX1_355] Blessed Champion - COST:5
    // - Set: Expert1, Rarity: Rare
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Double a minion's Attack.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_355e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("EX1_355", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [EX1_362] Argent Protector - COST:2 [ATK:3/HP:2]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SetGameTagTask>(
        EntityType::TARGET, GameTag::DIVINE_SHIELD, 1));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                  { PlayReq::REQ_NONSELF_TARGET, 0 } };
    cards.emplace("EX1_362", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [EX1_363] Blessing of Wisdom - COST:1
    // - Set: Expert1, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Choose a minion. Whenever it attacks, draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_363e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("EX1_363", cardDef);

    // ------------------------------------------ SPELL - PALADIN
    // [EX1_365] Holy Wrath - COST:5
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Draw a card and deal damage equal to its Cost.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1, true));
    cardDef.power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::STACK, GameTag::COST));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageNumberTask>(EntityType::TARGET, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("EX1_365", cardDef);

    // --------------------------------------- WEAPON - PALADIN
    // [EX1_366] Sword of Justice - COST:3 [ATK:1/HP:0]
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: After you summon a minion,
    //       give it +1/+1 and this loses 1 Durability.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 5
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_SUMMON));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<AddEnchantmentTask>("EX1_366e", EntityType::TARGET),
        std::make_shared<DamageWeaponTask>(false)
    };
    cards.emplace("EX1_366", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [EX1_379] Repentance - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After your opponent plays a minion,
    //       reduce its Health to 1.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_PLAY_MINION));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<ConditionTask>(
            EntityType::EVENT_SOURCE,
            SelfCondList{
                std::make_shared<SelfCondition>(SelfCondition::IsNotDead()),
                std::make_shared<SelfCondition>(
                    SelfCondition::IsNotUntouchable()) }),
        std::make_shared<FlagTask>(
            true, ComplexTask::ActivateSecret(
                      TaskList{ std::make_shared<AddEnchantmentTask>(
                          "EX1_379e", EntityType::EVENT_SOURCE) }))
    };
    cards.emplace("EX1_379", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [EX1_382] Aldor Peacekeeper - COST:3 [ATK:3/HP:3]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_382e", EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_ENEMY_TARGET, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cards.emplace("EX1_382", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [EX1_383] Tirion Fordring - COST:8 [ATK:6/HP:6]
    // - Faction: Neutral, Set: Expert1, Rarity: Legendary
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
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(std::make_shared<WeaponTask>("EX1_383t"));
    cards.emplace("EX1_383", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [EX1_384] Avenging Wrath - COST:6
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Deal 8 damage randomly split among all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{ std::make_shared<RandomTask>(EntityType::ENEMIES, 1),
                  std::make_shared<DamageTask>(EntityType::STACK, 1) },
        8, true));
    cards.emplace("EX1_384", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [EX1_619] Equality - COST:2
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Change the Health of all minions to 1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "EX1_619e", EntityType::ALL_MINIONS));
    cards.emplace("EX1_619", cardDef);
}

void Expert1CardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - PALADIN
    // [EX1_130a] Defender (*) - COST:1 [ATK:2/HP:1]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_130a", cardDef);

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [EX1_355e] Blessed Champion (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: This minion's Attack has been doubled.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(GameTag::ATK, EffectOperator::MUL, 2));
    cards.emplace("EX1_355e", cardDef);

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [EX1_363e] Blessing of Wisdom (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: When this minion attacks, the player who blessed
    //       it draws a card.
    // --------------------------------------------------------
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    cardDef.power.GetTrigger()->triggerSource =
        TriggerSource::ENCHANTMENT_TARGET;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DrawTask>(1) };
    cards.emplace("EX1_363e", cardDef);

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [EX1_366e] Justice Served (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Has +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_366e"));
    cards.emplace("EX1_366e", cardDef);

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [EX1_379e] Repentance (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Health reduced to 1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Effects::SetBaseHealth(1)));
    cards.emplace("EX1_379e", cardDef);

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [EX1_382e] Stand Down! (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Attack changed to 1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::SetAttack(1)));
    cards.emplace("EX1_382e", cardDef);

    // --------------------------------------- WEAPON - PALADIN
    // [EX1_383t] Ashbringer (*) - COST:5 [ATK:5/HP:0]
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DURABILITY = 3
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_383t", cardDef);

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [EX1_619e] Equality (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Health changed to 1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Effects::SetBaseHealth(1)));
    cards.emplace("EX1_619e", cardDef);
}

void Expert1CardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::TARGET, GameTag::HEALTH));
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::TARGET, GameTag::DAMAGE, 0, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<MathNumberIndexTask>(0, 1, MathOperation::SUB));
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "CS1_129e", EntityType::TARGET, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("CS1_129", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [EX1_091] Cabal Shadow Priest - COST:6 [ATK:4/HP:5]
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Take control of an enemy minion
    //       that has 2 or less Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_TARGET_MAX_ATTACK = 2
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<ControlTask>(EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_TARGET_MAX_ATTACK, 2 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_ENEMY_TARGET, 0 } };
    cards.emplace("EX1_091", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [EX1_195] Kul Tiran Chaplain - COST:2 [ATK:2/HP:3]
    // - Set: Expert1, Rarity: Rare
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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_195e", EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cards.emplace("EX1_195", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [EX1_196] Scarlet Subjugator - COST:1 [ATK:2/HP:1]
    // - Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give an enemy minion -2 Attack
    //       until your next turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_ENEMY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_196e", EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_ENEMY_TARGET, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cards.emplace("EX1_196", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [EX1_197] Shadow Word: Ruin - COST:4
    // - Set: Expert1, Rarity: Epic
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Destroy all minions with 5 or more Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::ALL_MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsTagValue(GameTag::ATK, 5, RelaSign::GEQ)) }));
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::STACK));
    cards.emplace("EX1_197", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [EX1_198] Natalie Seline - COST:8 [ATK:8/HP:1]
    // - Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a minion and gain its Health.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::TARGET, GameTag::HEALTH));
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::TARGET, GameTag::DAMAGE, 0, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<MathNumberIndexTask>(0, 1, MathOperation::SUB));
    cardDef.power.AddPowerTask(std::make_shared<SetGameTagNumberTask>(
        EntityType::SOURCE, GameTag::HEALTH));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cards.emplace("EX1_198", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [EX1_332] Silence - COST:0
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: <b>Silence</b> a minion.
    // --------------------------------------------------------
    // GameTag:
    // - SILENCE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SilenceTask>(EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("EX1_332", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [EX1_334] Shadow Madness - COST:3
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Gain control of an enemy minion with 3 or
    //       less Attack until end of turn.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // - REQ_NUM_MINION_SLOTS = 1
    // - REQ_TARGET_MAX_ATTACK = 3
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<ControlTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_334e", EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_ENEMY_TARGET, 0 },
                  { PlayReq::REQ_NUM_MINION_SLOTS, 1 },
                  { PlayReq::REQ_TARGET_MAX_ATTACK, 3 } };
    cards.emplace("EX1_334", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [EX1_335] Lightspawn - COST:3 [ATK:0/HP:4]
    // - Race: Elemental, Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: This minion's Attack is always equal to its Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<AdaptiveEffect>(
        GameTag::ATK, EffectOperator::SET, [=](Playable* playable) {
            return dynamic_cast<Minion*>(playable)->GetHealth();
        }));
    cards.emplace("EX1_335", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [EX1_339] Thoughtsteal - COST:2
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Copy 2 cards in your opponent's deck and
    //       add them to your hand.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::ENEMY_DECK, 2));
    cardDef.power.AddPowerTask(
        std::make_shared<CopyTask>(EntityType::STACK, ZoneType::HAND));
    cards.emplace("EX1_339", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [EX1_341] Lightwell - COST:2 [ATK:0/HP:5]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the start of your turn, restore 3 Health
    //       to a damaged friendly character.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<IncludeTask>(EntityType::FRIENDS),
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsDamaged()) }),
        std::make_shared<RandomTask>(EntityType::STACK, 1),
        std::make_shared<HealTask>(EntityType::STACK, 3)
    };
    cards.emplace("EX1_341", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [EX1_345] Mindgames - COST:4
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Put a copy of a random minion from
    //       your opponent's deck into the battlefield.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::ENEMY_DECK));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsMinion()) }));
    cardDef.power.AddPowerTask(std::make_shared<CountTask>(EntityType::STACK));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::HERO, SelfCondList{ std::make_shared<SelfCondition>(
                              SelfCondition::IsStackNum(1, RelaSign::GEQ)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<RandomTask>(EntityType::STACK, 1),
                        std::make_shared<CopyTask>(EntityType::STACK,
                                                   ZoneType::PLAY) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        false, TaskList{ std::make_shared<SummonTask>("EX1_345t",
                                                      SummonSide::SPELL) }));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("EX1_345", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [EX1_350] Prophet Velen - COST:7 [ATK:7/HP:7]
    // - Faction: Neutral, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Double the damage and healing of
    //       your spells and Hero Power.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::PLAYER,
        EffectList{ std::make_shared<Effect>(GameTag::SPELLPOWER_DOUBLE,
                                             EffectOperator::ADD, 1) }));
    cards.emplace("EX1_350", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [EX1_591] Auchenai Soulpriest - COST:4 [ATK:3/HP:5]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Your cards and powers that restore Health
    //       now deal damage instead.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::PLAYER,
        EffectList{ std::make_shared<Effect>(GameTag::HEALING_DOES_DAMAGE,
                                             EffectOperator::SET, 1) }));
    cards.emplace("EX1_591", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [EX1_621] Circle of Healing - COST:0
    // - Set: Expert1, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Restore 4 Health to all minions.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<HealTask>(EntityType::ALL_MINIONS, 4));
    cards.emplace("EX1_621", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [EX1_623] Temple Enforcer - COST:5 [ATK:5/HP:6]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion +3 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_623e", EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cards.emplace("EX1_623", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [EX1_624] Holy Fire - COST:6
    // - Faction: Priest, Set: Expert1, Rarity: Rare
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Deal 5 damage. Restore 5 Health to your hero.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 5, true));
    cardDef.power.AddPowerTask(std::make_shared<HealTask>(EntityType::HERO, 5));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("EX1_624", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [EX1_625] Shadowform - COST:2
    // - Faction: Priest, Set: Expert1, Rarity: Epic
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Your Hero Power becomes 'Deal 2 damage'.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<ChangeHeroPowerTask>("EX1_625t"));
    cards.emplace("EX1_625", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [EX1_626] Mass Dispel - COST:4
    // - Set: Expert1, Rarity: Rare
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: <b>Silence</b> all enemy minions. Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - SILENCE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SilenceTask>(EntityType::ENEMY_MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace("EX1_626", cardDef);
}

void Expert1CardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- ENCHANTMENT - PRIEST
    // [CS1_129e] Inner Fire - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Change a minion's Attack to be equal to its Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Enchants::SetAttackScriptTag));
    cards.emplace("CS1_129e", cardDef);

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [EX1_195e] Aided (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +2 Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_195e"));
    cards.emplace("EX1_195e", cardDef);

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [EX1_196e] Subjugated (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: -2 Attack until your next turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Atk::Effect(EffectOperator::SUB, 2)));
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->removeAfterTriggered = true;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RemoveEnchantmentTask>()
    };
    cards.emplace("EX1_196e", cardDef);

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [EX1_334e] Shadow Madness (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: This minion has switched controllers this turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(std::vector<std::shared_ptr<IEffect>>{
            Effects::Charge,
            std::make_shared<Effect>(GameTag::CONTROLLER_CHANGED_THIS_TURN,
                                     EffectOperator::SET, 1) }));
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->eitherTurn = true;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RemoveEnchantmentTask>(),
        std::make_shared<ControlTask>(EntityType::TARGET, true)
    };
    cards.emplace("EX1_334e", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [EX1_345t] Shadow of Nothing - COST:0 [ATK:0/HP:1]
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: Mindgames whiffed! Your opponent had no minions!
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_345t", cardDef);

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [EX1_623e] Infusion (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +3 Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_623e"));
    cards.emplace("EX1_623e", cardDef);
}

void Expert1CardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ SPELL - ROGUE
    // [CS2_073] Cold Blood - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Common
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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_073e", EntityType::TARGET));
    cardDef.power.AddComboTask(
        std::make_shared<AddEnchantmentTask>("CS2_073e2", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("CS2_073", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [CS2_233] Blade Flurry - COST:2
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Destroy your weapon and deal its damage
    //       to all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_WEAPON_EQUIPPED = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::WEAPON, GameTag::ATK));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageNumberTask>(EntityType::ENEMY_MINIONS, true));
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::WEAPON));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_WEAPON_EQUIPPED, 0 } };
    cards.emplace("CS2_233", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [EX1_124] Eviscerate - COST:2
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 2 damage. <b>Combo:</b> Deal 4 damage instead.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, true));
    cardDef.power.AddComboTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 4, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("EX1_124", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [EX1_126] Betrayal - COST:2
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Force an enemy minion to deal its damage
    //       to the minions next to it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::TARGET, GameTag::ATK));
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeAdjacentTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageNumberTask>(EntityType::STACK));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_ENEMY_TARGET, 0 } };
    cards.emplace("EX1_126", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [EX1_128] Conceal - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Give your minions <b>Stealth</b> until your next turn.
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "EX1_128e", EntityType::MINIONS, false, false,
        SelfCondition::HasNotStealth()));
    cards.emplace("EX1_128", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [EX1_131] Defias Ringleader - COST:2 [ATK:2/HP:2]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Summon a 2/1 Defias Bandit.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddComboTask(
        std::make_shared<SummonTask>("EX1_131t", SummonSide::RIGHT));
    cards.emplace("EX1_131", cardDef);

    // ----------------------------------------- WEAPON - ROGUE
    // [EX1_133] Perdition's Blade - COST:3 [ATK:2/HP:0]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage.
    //       <b>Combo:</b> Deal 2 instead.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - BATTLECRY = 1
    // - COMBO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1));
    cardDef.power.AddComboTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cards.emplace("EX1_133", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddComboTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_FOR_COMBO, 0 } };
    cards.emplace("EX1_134", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [EX1_137] Headcrack - COST:3
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 2 damage to the enemy hero.
    //       <b>Combo:</b> Return this to your hand next turn.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 2, true));
    cardDef.power.AddComboTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 2, true));
    cardDef.power.AddComboTask(std::make_shared<SetGameTagTask>(
        EntityType::SOURCE, GameTag::HEADCRACK_COMBO, 1));
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<ConditionTask>(
            EntityType::SOURCE,
            SelfCondList{ std::make_shared<SelfCondition>(
                SelfCondition::IsTagValue(GameTag::HEADCRACK_COMBO, 1)) }),
        std::make_shared<FlagTask>(
            true,
            TaskList{ std::make_shared<IncludeTask>(EntityType::SOURCE),
                      std::make_shared<FuncPlayableTask>(
                          [=](const std::vector<Playable*>& playables) {
                              const auto source = playables[0];

                              source->zone->Remove(source);
                              source->SetGameTag(GameTag::HEADCRACK_COMBO, 0);

                              return std::vector<Playable*>{ source };
                          }),
                      std::make_shared<AddStackToTask>(EntityType::HAND) })
    };
    cardDef.power.GetTrigger()->removeAfterTriggered = true;
    cards.emplace("EX1_137", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [EX1_144] Shadowstep - COST:0
    // - Faction: Neutral, Set: Expert1, Rarity: Common
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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<ReturnHandTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(std::make_shared<AddAuraEffectTask>(
        Effects::ReduceCost(2), EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_FRIENDLY_TARGET, 0 } };
    cards.emplace("EX1_144", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [EX1_145] Preparation - COST:0
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: The next spell you cast this turn costs (2) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_145o", EntityType::PLAYER));
    cards.emplace("EX1_145", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [EX1_182] Pilfer - COST:1
    // - Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Add a random card from another class to your hand
    //       <i>(from your opponent's class)</i>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomCardTask>(EntityType::ENEMY_HERO));
    cardDef.power.AddPowerTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cards.emplace("EX1_182", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [EX1_522] Patient Assassin - COST:2 [ATK:1/HP:2]
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //       <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // - POISONOUS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_522", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [EX1_613] Edwin VanCleef - COST:3 [ATK:2/HP:2]
    // - Faction: Neutral, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Gain +2/+2 for each other card
    //       you've played this turn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - COMBO = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddComboTask(std::make_shared<GetPlayerGameTagTask>(
        GameTag::NUM_CARDS_PLAYED_THIS_TURN));
    cardDef.power.AddComboTask(std::make_shared<MathSubtractTask>(1));
    cardDef.power.AddComboTask(std::make_shared<MathMultiplyTask>(2));
    cardDef.power.AddComboTask(std::make_shared<AddEnchantmentTask>(
        "EX1_613e", EntityType::SOURCE, true));
    cards.emplace("EX1_613", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [NEW1_005] Kidnapper - COST:6 [ATK:5/HP:3]
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Return a minion to its owner's hand.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_FOR_COMBO = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddComboTask(
        std::make_shared<ReturnHandTask>(EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_TARGET_FOR_COMBO, 0 } };
    cards.emplace("NEW1_005", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [NEW1_014] Master of Disguise - COST:4 [ATK:4/HP:4]
    // - Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion <b>Stealth</b>
    //       until your next turn.
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
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("NEW1_014e", EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_NONSELF_TARGET, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 } };
    cards.emplace("NEW1_014", cardDef);
}

void Expert1CardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [CS2_073e] Cold Blood (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("CS2_073e"));
    cards.emplace("CS2_073e", cardDef);

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [CS2_073e2] Cold Blood (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +4 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("CS2_073e2"));
    cards.emplace("CS2_073e2", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [EX1_128e] Conceal - COST:1
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Stealthed until your next turn.
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::Stealth));
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RemoveEnchantmentTask>()
    };
    cardDef.power.GetTrigger()->removeAfterTriggered = true;
    cards.emplace("EX1_128e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_131t] Defias Bandit (*) - COST:1 [ATK:2/HP:1]
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_131t", cardDef);

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [EX1_145o] Preparation (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: The next spell you cast this turn costs (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_SILENCED = 1
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::HAND, EffectList{ Effects::ReduceCost(2) }));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsSpell());
        aura->removeTrigger = { TriggerType::CAST_SPELL, nullptr };
    }
    cards.emplace("EX1_145o", cardDef);

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [EX1_613e] VanCleef's Vengeance (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Enchants::AddAttackHealthScriptTag));
    cards.emplace("EX1_613e", cardDef);

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [NEW1_014e] Disguised (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Stealthed until your next turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::Stealth));
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->removeAfterTriggered = true;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RemoveEnchantmentTask>()
    };
    cards.emplace("NEW1_014e", cardDef);
}

void Expert1CardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_038e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("CS2_038", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [CS2_053] Far Sight - COST:3
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: Draw a card. That card costs (3) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1, true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_053e", EntityType::STACK));
    cards.emplace("CS2_053", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [EX1_238] Lightning Bolt - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Common
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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("EX1_238", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [EX1_241] Lava Burst - COST:3
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Deal 5 damage. <b>Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 2
    // - OVERLOAD_OWED = 2
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 5, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("EX1_241", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [EX1_243] Dust Devil - COST:1 [ATK:3/HP:1]
    // - Race: Elemental, Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Windfury</b>. <b>Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 2
    // - OVERLOAD_OWED = 2
    // - WINDFURY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_243", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [EX1_245] Earth Shock - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: <b>Silence</b> a minion, then deal 1 damage to it.
    // --------------------------------------------------------
    // GameTag:
    // - SILENCE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SilenceTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("EX1_245", cardDef);

    // ---------------------------------------- WEAPON - SHAMAN
    // [EX1_247] Stormforged Axe - COST:2 [ATK:2/HP:0]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 3
    // - OVERLOAD = 1
    // - OVERLOAD_OWED = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_247", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [EX1_248] Feral Spirit - COST:3
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("EX1_tk11", 2));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("EX1_248", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [EX1_250] Earth Elemental - COST:5 [ATK:7/HP:8]
    // - Race: Elemental, Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b><b>Overload</b>:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 2
    // - OVERLOAD_OWED = 2
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_250", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [EX1_251] Forked Lightning - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Deal 2 damage to 2 random enemy minions.
    //       <b>Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 2
    // - OVERLOAD_OWED = 2
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_ENEMY_MINIONS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::ENEMY_MINIONS, 2));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::STACK, 2, true));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_MINIMUM_ENEMY_MINIONS, 1 } };
    cards.emplace("EX1_251", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [EX1_258] Unbound Elemental - COST:3 [ATK:3/HP:4]
    // - Race: Elemental, Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: After you play a card with <b>Overload</b>,
    //       gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::PLAY_CARD));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsOverloadCard())
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_258e", EntityType::SOURCE) };
    cards.emplace("EX1_258", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [EX1_259] Lightning Storm - COST:3
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Deal 3 damage to all enemy minions.
    //       <b>Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 2
    // - OVERLOAD_OWED = 2
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_MINIONS, 3, true));
    cards.emplace("EX1_259", cardDef);

    // ---------------------------------------- WEAPON - SHAMAN
    // [EX1_567] Doomhammer - COST:5 [ATK:2/HP:0]
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Windfury, Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 8
    // - WINDFURY = 1
    // - OVERLOAD = 2
    // - OVERLOAD_OWED = 2
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_567", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [EX1_575] Mana Tide Totem - COST:3 [ATK:0/HP:3]
    // - Race: Totem, Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DrawTask>(1) };
    cards.emplace("EX1_575", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [NEW1_010] Al'Akir the Windlord - COST:8 [ATK:3/HP:6]
    // - Race: Elemental, Set: Expert1, Rarity: Legendary
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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("NEW1_010", cardDef);
}

void Expert1CardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [CS2_038e] Ancestral Spirit (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Resummon this minion.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<CopyTask>(EntityType::SOURCE, ZoneType::PLAY));
    cards.emplace("CS2_038e", cardDef);

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [CS2_053e] Far Sight (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: One of your cards costs (3) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::ReduceCost(3)));
    cards.emplace("CS2_053e", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [EX1_tk11] Spirit Wolf (*) - COST:2 [ATK:2/HP:3]
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_tk11", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_258e] Overloading (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Effects::AttackHealthN(1)));
    cards.emplace("EX1_258e", cardDef);
}

void Expert1CardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - WARLOCK
    // [CS2_059] Blood Imp - COST:1 [ATK:0/HP:1]
    // - Race: Demon, Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>. At the end of your turn,
    //       give another random friendly minion +1 Health.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomTask>(EntityType::MINIONS_NOSOURCE, 1),
        std::make_shared<AddEnchantmentTask>("CS2_059o", EntityType::STACK)
    };
    cards.emplace("CS2_059", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [EX1_181] Call of the Void - COST:1
    // - Set: Expert1, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Add a random Demon to your hand.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<RandomCardTask>(
        CardType::MINION, CardClass::INVALID, Race::DEMON));
    cardDef.power.AddPowerTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cards.emplace("EX1_181", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [EX1_185] Siegebreaker - COST:7 [ATK:5/HP:8]
    // - Race: Demon, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       Your other Demons have +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<Aura>(AuraType::FIELD_EXCEPT_SOURCE, "EX1_185e"));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::DEMON));
    }
    cards.emplace("EX1_185", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [EX1_301] Felguard - COST:3 [ATK:3/HP:5]
    // - Race: Demon, Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Destroy one of your Mana Crystals.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ManaCrystalTask>(-1, false));
    cards.emplace("EX1_301", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [EX1_303] Shadowflame - COST:4
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Destroy a friendly minion and deal its Attack damage
    //       to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::TARGET, GameTag::ATK));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageNumberTask>(EntityType::ENEMY_MINIONS, true));
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("EX1_303", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [EX1_304] Void Terror - COST:3 [ATK:3/HP:4]
    // - Race: Demon, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy both adjacent minions
    //       and gain their Attack and Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeAdjacentTask>(EntityType::SOURCE));
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::STACK, GameTag::ATK, 0, 1));
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::STACK, GameTag::ATK, 1, 2));
    cardDef.power.AddPowerTask(
        std::make_shared<MathNumberIndexTask>(1, 2, MathOperation::ADD));
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::STACK, GameTag::HEALTH, 0, 3));
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::STACK, GameTag::HEALTH, 1, 4));
    cardDef.power.AddPowerTask(
        std::make_shared<MathNumberIndexTask>(3, 4, MathOperation::ADD, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::STACK));
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "EX1_304e", EntityType::SOURCE, true));
    cards.emplace("EX1_304", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [EX1_309] Siphon Soul - COST:5
    // - Set: Expert1, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Destroy a minion. Restore 3 Health to your hero.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(std::make_shared<HealTask>(EntityType::HERO, 3));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("EX1_309", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [EX1_310] Doomguard - COST:5 [ATK:5/HP:7]
    // - Race: Demon, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Charge</b>.
    //       <b>Battlecry:</b> Discard two random cards.
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DiscardTask>(2));
    cards.emplace("EX1_310", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [EX1_312] Twisting Nether - COST:8
    // - Set: Expert1, Rarity: Epic
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Destroy all minions.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::ALL_MINIONS));
    cards.emplace("EX1_312", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [EX1_313] Pit Lord - COST:4 [ATK:5/HP:6]
    // - Race: Demon, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 5 damage to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::HERO, 5));
    cards.emplace("EX1_313", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [EX1_315] Summoning Portal - COST:4 [ATK:0/HP:4]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Your minions cost (2) less, but not less than (1).
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<SummoningPortalAura>());
    cards.emplace("EX1_315", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [EX1_316] Power Overwhelming - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Give a friendly minion +4/+4 until end of turn.
    //       Then, it dies. Horribly.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_316e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_FRIENDLY_TARGET, 0 } };
    cards.emplace("EX1_316", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [EX1_317] Sense Demons - COST:3
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Draw 2 Demons from your deck.
    // --------------------------------------------------------
    cardDef.ClearData();
    for (size_t i = 0; i < 2; ++i)
    {
        cardDef.power.AddPowerTask(
            std::make_shared<IncludeTask>(EntityType::DECK));
        cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(
            SelfCondList{ std::make_shared<SelfCondition>(
                SelfCondition::IsRace(Race::DEMON)) }));
        cardDef.power.AddPowerTask(
            std::make_shared<CountTask>(EntityType::STACK));
        cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
            EntityType::HERO,
            SelfCondList{ std::make_shared<SelfCondition>(
                SelfCondition::IsStackNum(1, RelaSign::GEQ)) }));
        cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
            true, TaskList{ std::make_shared<RandomTask>(EntityType::STACK, 1),
                            std::make_shared<DrawStackTask>() }));
        cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
            false, TaskList{ std::make_shared<AddCardTask>(EntityType::HAND,
                                                           "EX1_317t") }));
    }
    cards.emplace("EX1_317", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [EX1_319] Flame Imp - COST:1
    // - Race: Demon, Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::HERO, 3));
    cards.emplace("EX1_319", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [EX1_320] Bane of Doom - COST:5
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Deal 2 damage to a character.
    //       If that kills it, summon a random Demon.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, true));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::TARGET, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsDead()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<RandomCardTask>(
                            CardType::MINION, CardClass::INVALID, Race::DEMON),
                        std::make_shared<SummonTask>(SummonSide::SPELL) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("EX1_320", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [EX1_596] Demonfire - COST:2
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Deal 2 damage to a minion.
    //       If it's a friendly Demon, give it +2/+2 instead.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::TARGET,
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsRace(Race::DEMON)) },
        RelaCondList{
            std::make_shared<RelaCondition>(RelaCondition::IsFriendly()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "EX1_596e", EntityType::TARGET) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        false,
        TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 2, true) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("EX1_596", cardDef);
}

void Expert1CardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [CS2_059o] Blood Pact (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::HealthN(1)));
    cards.emplace("CS2_059o", cardDef);

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [EX1_185e] Siegebreaking (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Siegebreaker is granting this minion +1 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_185e"));
    cards.emplace("EX1_185e", cardDef);

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [EX1_304e] Consume (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Enchants::AddAttackHealthScriptTag));
    cards.emplace("EX1_304e", cardDef);

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [EX1_316e] Power Overwhelming (*) - COST:0
    // - Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: This minion has +4/+4, but will die a horrible death
    //       at the end of the turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_316e"));
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DestroyTask>(
        EntityType::TARGET) };
    cards.emplace("EX1_316e", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [EX1_317t] Worthless Imp - COST:1 [ATK:1/HP:1]
    // - Race: Demon, Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    // Text: <i>You are out of demons!
    //       At least there are always imps...</i>
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_317t", cardDef);

    // --------------------------------------- WEAPON - WARLOCK
    // [EX1_323w] Blood Fury (*) - COST:3 [ATK:3/HP:0]
    // - Set: Expert1
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DURABILITY = 8
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_323w", cardDef);

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [EX1_596e] Demonfire (*) - COST:0
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: This Demon has +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_596e"));
    cards.emplace("EX1_596e", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [EX1_tk34] Infernal (*) - COST:6 [ATK:6/HP:6]
    // - Race: Demon, Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_tk34", cardDef);
}

void Expert1CardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_104e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_DAMAGED_TARGET, 0 } };
    cards.emplace("CS2_104", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [EX1_391] Slam - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 2 damage to a minion.
    //       If it survives, draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, true));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::TARGET, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsNotDead()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DrawTask>(1) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("EX1_391", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [EX1_392] Battle Rage - COST:2
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Draw a card for each damaged friendly character.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<CountTask>(
        EntityType::FRIENDS, 0,
        std::vector<SelfCondition>{ SelfCondition::IsDamaged() }));
    cardDef.power.AddPowerTask(std::make_shared<DrawNumberTask>());
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("EX1_392", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [EX1_393] Amani Berserker - COST:2 [ATK:2/HP:3]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Has +3 Attack while damaged.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(Triggers::EnrageTrigger("EX1_393e")));
    cards.emplace("EX1_393", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [EX1_398] Arathi Weaponsmith - COST:4 [ATK:3/HP:3]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Equip a 2/2 weapon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<WeaponTask>("EX1_398t"));
    cards.emplace("EX1_398", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [EX1_402] Armorsmith - COST:2 [ATK:1/HP:4]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever a friendly minion takes damage,
    //       gain 1 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TAKE_DAMAGE));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::MINIONS;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<ArmorTask>(1) };
    cards.emplace("EX1_402", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [EX1_407] Brawl - COST:5
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy all minions except one.
    //       <i>(chosen randomly)</i>
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_TOTAL_MINIONS = 2
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::ALL_MINIONS, 1));
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(
        EntityType::ALL_MINIONS, std::vector<EntityType>{ EntityType::STACK }));
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::STACK));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_MINIMUM_TOTAL_MINIONS, 2 } };
    cards.emplace("EX1_407", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [EX1_408] Mortal Strike - COST:4
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 4 damage.
    //       If you have 12 or less Health, deal 6 instead.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::HERO, SelfCondList{ std::make_shared<SelfCondition>(
                              SelfCondition::IsHealth(12, RelaSign::LEQ)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 6, true) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        false,
        TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 4, true) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("EX1_408", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [EX1_409] Upgrade! - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: If you have a weapon, give it +1/+1.
    //       Otherwise equip a 1/3 weapon.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::HERO, SelfCondList{ std::make_shared<SelfCondition>(
                              SelfCondition::IsWeaponEquipped()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "EX1_409e", EntityType::WEAPON) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        false, TaskList{ std::make_shared<WeaponTask>("EX1_409t") }));
    cards.emplace("EX1_409", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [EX1_410] Shield Slam - COST:1
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::HERO, GameTag::ARMOR));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageNumberTask>(EntityType::TARGET, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("EX1_410", cardDef);

    // --------------------------------------- WEAPON - WARRIOR
    // [EX1_411] Gorehowl - COST:7 [ATK:7/HP:0]
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: Attacking a minion costs 1 Attack instead of 1 Durability.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TARGET));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsProposedDefender(CardType::MINION)) };
    cardDef.power.GetTrigger()->fastExecution = true;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_411e", EntityType::SOURCE) };
    cards.emplace("EX1_411", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [EX1_414] Grommash Hellscream - COST:8 [ATK:4/HP:9]
    // - Faction: Neutral, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    //       Has +6 Attack while damaged.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CHARGE = 1
    // - ENRAGED = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<EnrageEffect>(AuraType::SELF, "EX1_414e"));
    cards.emplace("EX1_414", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [EX1_603] Cruel Taskmaster - COST:2 [ATK:2/HP:3]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_603e", EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_NONSELF_TARGET, 0 } };
    cards.emplace("EX1_603", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [EX1_604] Frothing Berserker - COST:3 [ATK:2/HP:4]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever a minion takes damage, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TAKE_DAMAGE));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ALL_MINIONS;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_604o", EntityType::SOURCE) };
    cards.emplace("EX1_604", cardDef);

    // ----------------------------------------- SPELL - WARRIOR
    // [EX1_607] Inner Rage - COST:0
    // - Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 1 damage to a minion and give it +2 Attack.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1, true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_607e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("EX1_607", cardDef);

    // ----------------------------------------- SPELL - WARRIOR
    // [NEW1_036] Commanding Shout - COST:2
    // - Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Your minions can't be reduced below 1 Health this turn.
    //       Draw a card.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("NEW1_036e2", EntityType::PLAYER));
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace("NEW1_036", cardDef);
}

void Expert1CardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [CS2_104e] Rampage (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +3/+3.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("CS2_104e"));
    cards.emplace("CS2_104e", cardDef);

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [EX1_393e] Enraged (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +3 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_393e"));
    cards.emplace("EX1_393e", cardDef);

    // --------------------------------------- WEAPON - WARRIOR
    // [EX1_398t] Battle Axe (*) - COST:1 [ATK:2/HP:0]
    // - Set: Expert1
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_398t", cardDef);

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [EX1_409e] Upgraded (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +1 Attack and +1 Durability.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(std::vector<std::shared_ptr<IEffect>>{
            Effects::AttackN(1), Effects::DurabilityN(1) }));
    cards.emplace("EX1_409e", cardDef);

    // --------------------------------------- WEAPON - WARRIOR
    // [EX1_409t] Heavy Axe (*) - COST:1 [ATK:1/HP:0]
    // - Set: Expert1
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 3
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_409t", cardDef);

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [EX1_411e] Bloodrage (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: No durability loss.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::Immune));
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->fastExecution = true;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RemoveEnchantmentTask>(),
        std::make_shared<AddEnchantmentTask>("EX1_411e2", EntityType::WEAPON)
    };
    cards.emplace("EX1_411e", cardDef);

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [EX1_411e2] Needs Sharpening (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Decreased Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<OngoingEnchant>(std::vector<std::shared_ptr<IEffect>>{
            std::make_shared<Effect>(GameTag::ATK, EffectOperator::SUB, 1) }));
    cards.emplace("EX1_411e2", cardDef);

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [EX1_414e] Enraged (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +6 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_414e"));
    cards.emplace("EX1_414e", cardDef);

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [EX1_603e] Whipped Into Shape (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_603e"));
    cards.emplace("EX1_603e", cardDef);

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [EX1_604o] Berserk (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<OngoingEnchant>(
        std::vector<std::shared_ptr<IEffect>>{ Effects::AttackN(1) }));
    cards.emplace("EX1_604o", cardDef);

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [EX1_607e] Inner Rage (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_607e"));
    cards.emplace("EX1_607e", cardDef);

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [NEW1_036e] Commanding Shout (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Can't be reduced below 1 Health this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(std::make_shared<Effect>(
        GameTag::HEALTH_MINIMUM, EffectOperator::SET, 1)));
    {
        const auto enchant = dynamic_cast<Enchant*>(cardDef.power.GetEnchant());
        enchant->isOneTurnEffect = true;
    }
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::PREDAMAGE));
    {
        const auto trigger = dynamic_cast<Trigger*>(cardDef.power.GetTrigger());
        trigger->triggerSource = TriggerSource::ENCHANTMENT_TARGET;
        trigger->fastExecution = true;
        trigger->tasks = {
            std::make_shared<IncludeTask>(EntityType::TARGET),
            std::make_shared<FuncPlayableTask>(
                [=](const std::vector<Playable*>& playables) {
                    const auto minion = dynamic_cast<Minion*>(playables[0]);
                    int& eventNumber =
                        minion->game->currentEventData->eventNumber;

                    if (eventNumber >= minion->GetHealth())
                    {
                        eventNumber = minion->GetHealth() - 1;
                    }

                    return std::vector<Playable*>{ minion };
                })
        };
    }
    cards.emplace("NEW1_036e", cardDef);

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [NEW1_036e2] Commanding Shout (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Your minions can't be reduced below 1 Health this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(AuraType::FIELD, "NEW1_036e"));
    cards.emplace("NEW1_036e2", cardDef);
}

void Expert1CardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [CS1_069] Fen Creeper - COST:5 [ATK:3/HP:6]
    // - Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS1_069", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<HealTask>(EntityType::TARGET, 3));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cards.emplace("CS2_117", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_146] Southsea Deckhand - COST:1 [ATK:2/HP:1]
    // - Race: Pirate, Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Has <b>Charge</b> while you have a weapon equipped.
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<AdaptiveEffect>(
        std::make_shared<SelfCondition>(SelfCondition::IsWeaponEquipped()),
        GameTag::CHARGE));
    cards.emplace("CS2_146", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_151] Silver Hand Knight - COST:5 [ATK:4/HP:4]
    // - Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 2/2 Squire.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("CS2_152", SummonSide::RIGHT));
    cards.emplace("CS2_151", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_161] Ravenholdt Assassin - COST:7 [ATK:7/HP:5]
    // - Faction: Alliance, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_161", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_169] Young Dragonhawk - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Faction: Horde, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - WINDFURY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_169", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_181] Injured Blademaster - COST:3 [ATK:4/HP:7]
    // - Faction: Horde, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 4 damage to himself.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::SOURCE, 4, false));
    cards.emplace("CS2_181", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_188] Abusive Sergeant - COST:1 [ATK:1/HP:1]
    // - Faction: Alliance, Set: Expert1, Rarity: Common
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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("CS2_188o", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("CS2_188", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_203] Ironbeak Owl - COST:3 [ATK:2/HP:1]
    // - Race: Beast, Faction: Horde, Set: Expert1, Rarity: Common
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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SilenceTask>(EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("CS2_203", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_221] Spiteful Smith - COST:5 [ATK:4/HP:6]
    // - Faction: Horde, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Enrage:</b> Your weapon has +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<EnrageEffect>(AuraType::WEAPON, "CS2_221e"));
    cards.emplace("CS2_221", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_227] Venture Co. Mercenary - COST:5 [ATK:7/HP:6]
    // - Faction: Horde, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Your minions cost (3) more.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::HAND, EffectList{ Effects::AddCost(3) }));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsMinion());
    }
    cards.emplace("CS2_227", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_231] Wisp - COST:0 [ATK:1/HP:1]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_231", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_001] Lightwarden - COST:1 [ATK:1/HP:2]
    // - Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever a character is healed, gain +2 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TAKE_HEAL));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_001e", EntityType::SOURCE) };
    cards.emplace("EX1_001", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_002] The Black Knight - COST:6 [ATK:4/HP:5]
    // - Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy an enemy minion
    //       with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_MUST_TARGET_TAUNTER = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_MUST_TARGET_TAUNTER, 0 },
                  { PlayReq::REQ_ENEMY_TARGET, 0 } };
    cards.emplace("EX1_002", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_004] Young Priestess - COST:1 [ATK:2/HP:1]
    // - Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       give another random friendly minion +1 Health.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomTask>(EntityType::MINIONS_NOSOURCE, 1),
        std::make_shared<AddEnchantmentTask>("EX1_004e", EntityType::STACK)
    };
    cards.emplace("EX1_004", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_005] Big Game Hunter - COST:4 [ATK:4/HP:2]
    // - Set: Expert1, Rarity: Epic
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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_TARGET_MIN_ATTACK, 7 } };
    cards.emplace("EX1_005", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_006] Alarm-o-Bot - COST:3 [ATK:0/HP:3]
    // - Race: Mechanical, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       swap this minion with a random one in your hand.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::HasMinionInHand())
    };
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<GetGameTagTask>(EntityType::SOURCE,
                                         GameTag::ZONE_POSITION),
        std::make_shared<MoveToSetasideTask>(EntityType::SOURCE),
        std::make_shared<IncludeTask>(EntityType::HAND),
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsMinion()) }),
        std::make_shared<RandomTask>(EntityType::STACK, 1),
        std::make_shared<RemoveHandTask>(EntityType::STACK),
        std::make_shared<SummonTask>(SummonSide::NUMBER),
        std::make_shared<ReturnHandTask>(EntityType::SOURCE)
    };
    cards.emplace("EX1_006", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_007] Acolyte of Pain - COST:3 [ATK:1/HP:3]
    // - Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever this minion takes damage, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TAKE_DAMAGE));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SELF;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DrawTask>(1) };
    cards.emplace("EX1_007", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_008] Argent Squire - COST:1 [ATK:1/HP:1]
    // - Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_008", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_009] Angry Chicken - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Enrage:</b> +5 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(Triggers::EnrageTrigger("EX1_009e")));
    cards.emplace("EX1_009", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_010] Worgen Infiltrator - COST:1 [ATK:2/HP:1]
    // - Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_010", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_012] Bloodmage Thalnos - COST:2 [ATK:1/HP:1]
    // - Faction: neutral, Set: expert1, Rarity: legendary
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    //       <b>Deathrattle:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - SPELLPOWER = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(std::make_shared<DrawTask>(1));
    cards.emplace("EX1_012", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_014] King Mukla - COST:3 [ATK:5/HP:5]
    // - Race: Beast, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your opponent 2 Bananas.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::ENEMY_HAND, "EX1_014t", 2));
    cards.emplace("EX1_014", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_016] Sylvanas Windrunner - COST:6 [ATK:5/HP:5]
    // - Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b>
    //       Take control of a random enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<RandomTask>(EntityType::ENEMY_MINIONS, 1));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<ControlTask>(EntityType::STACK));
    cards.emplace("EX1_016", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_017] Jungle Panther - COST:3 [ATK:4/HP:2]
    // - Race: Beast, Faction: Horde, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_017", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_020] Scarlet Crusader - COST:3 [ATK:3/HP:1]
    // - Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_020", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_021] Thrallmar Farseer - COST:3 [ATK:2/HP:3]
    // - Faction: Horde, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - WINDFURY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_021", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_023] Silvermoon Guardian - COST:4 [ATK:3/HP:3]
    // - Faction: Horde, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_023", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_028] Stranglethorn Tiger - COST:5 [ATK:5/HP:5]
    // - Race: Beast, Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_028", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_029] Leper Gnome - COST:1 [ATK:2/HP:1]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 2 damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 2, false));
    cards.emplace("EX1_029", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_032", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_033] Windfury Harpy - COST:6 [ATK:4/HP:5]
    // - Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - WINDFURY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_033", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_043] Twilight Drake - COST:4 [ATK:4/HP:1]
    // - Faction: Alliance, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain +1 Health
    //       for each card in your hand.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<CountTask>(EntityType::HAND));
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "EX1_043e", EntityType::SOURCE, true));
    cards.emplace("EX1_043", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_044] Questing Adventurer - COST:3 [ATK:2/HP:2]
    // - Faction: Alliance, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you play a card, gain +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::PLAY_CARD));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_044e", EntityType::SOURCE) };
    cards.emplace("EX1_044", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_045] Ancient Watcher - COST:2 [ATK:4/HP:5]
    // - Faction: Alliance, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Can't attack.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_ATTACK = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_045", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_046] Dark Iron Dwarf - COST:4 [ATK:4/HP:4]
    // - Faction: Alliance, Set: Expert1, Rarity: Common
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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_046e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("EX1_046", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_048] Spellbreaker - COST:4 [ATK:4/HP:3]
    // - Faction: Horde, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Silence</b> a minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_NONSELF_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - SILENCE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SilenceTask>(EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_NONSELF_TARGET, 0 } };
    cards.emplace("EX1_048", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_049] Youthful Brewmaster - COST:2 [ATK:3/HP:2]
    // - Faction: Alliance, Set: Expert1, Rarity: Common
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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<ReturnHandTask>(EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_NONSELF_TARGET, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 } };
    cards.emplace("EX1_049", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_050] Coldlight Oracle - COST:3 [ATK:2/HP:2]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Each player draws 2 cards.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(2));
    cardDef.power.AddPowerTask(std::make_shared<DrawOpTask>(2));
    cards.emplace("EX1_050", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_055] Mana Addict - COST:2 [ATK:1/HP:3]
    // - Faction: Alliance, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you cast a spell, gain +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_055o", EntityType::SOURCE) };
    cards.emplace("EX1_055", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_057] Ancient Brewmaster - COST:4 [ATK:5/HP:4]
    // - Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Return a friendly minion
    //       from the battlefield to your hand.
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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<ReturnHandTask>(EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                  { PlayReq::REQ_NONSELF_TARGET, 0 } };
    cards.emplace("EX1_057", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_058] Sunfury Protector - COST:2 [ATK:2/HP:3]
    // - Faction: Alliance, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give adjacent minions <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(
        EntityType::SOURCE, RelaCondList{ std::make_shared<RelaCondition>(
                                RelaCondition::IsSideBySide()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<SetGameTagTask>(EntityType::STACK, GameTag::TAUNT, 1));
    cards.emplace("EX1_058", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_059] Crazed Alchemist - COST:2 [ATK:2/HP:2]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SwapAttackHealthTask>(EntityType::TARGET, "EX1_059e"));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cards.emplace("EX1_059", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_067", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_076] Pint-Sized Summoner - COST:2 [ATK:2/HP:2]
    // - Faction: Alliance, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: The first minion you play each turn costs (1) less.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<SwitchingAura>(
        AuraType::HAND, SelfCondition::MinionsPlayedThisTurn(0),
        TriggerType::PLAY_MINION, EffectList{ Effects::ReduceCost(1) }));
    {
        const auto aura = dynamic_cast<SwitchingAura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsMinion());
    }
    cards.emplace("EX1_076", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_080] Secretkeeper - COST:1 [ATK:1/HP:2]
    // - Faction: Alliance, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever a <b>Secret</b> is played, gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsSecret())
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_080o", EntityType::SOURCE) };
    cards.emplace("EX1_080", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_082] Mad Bomber - COST:2 [ATK:3/HP:2]
    // - Faction: Alliance, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage randomly split
    //       between all other characters.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{ std::make_shared<RandomTask>(EntityType::ALL_NOSOURCE, 1),
                  std::make_shared<DamageTask>(EntityType::STACK, 1) },
        3, false));
    cards.emplace("EX1_082", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_083] Tinkmaster Overspark - COST:3 [ATK:3/HP:3]
    // - Faction: Alliance, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Transform another random minion
    //       into a 5/5 Devilsaur or a 1/1 Squirrel.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::ALL_MINIONS_NOSOURCE, 1));
    cardDef.power.AddPowerTask(std::make_shared<ChanceTask>(true));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<TransformTask>(EntityType::STACK,
                                                        "EX1_tk28") }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        false, TaskList{ std::make_shared<TransformTask>(EntityType::STACK,
                                                         "EX1_tk29") }));
    cards.emplace("EX1_083", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_085] Mind Control Tech - COST:3 [ATK:3/HP:3]
    // - Faction: Alliance, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your opponent has 4 or
    //       more minions, take control of one at random.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::ENEMY_MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<FuncPlayableTask>(
        [=](const std::vector<Playable*>& playables) {
            return playables.size() > 3 ? playables : std::vector<Playable*>{};
        }));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsFieldFull()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DestroyTask>(EntityType::STACK) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        false, TaskList{ std::make_shared<ControlTask>(EntityType::STACK) }));
    cards.emplace("EX1_085", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_089] Arcane Golem - COST:3 [ATK:4/HP:2]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Charge</b>.
    //       <b>Battlecry:</b> Give your opponent a Mana Crystal.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - CHARGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<ManaCrystalTask>(1, false, true));
    cards.emplace("EX1_089", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_093] Defender of Argus - COST:4 [ATK:3/HP:3]
    // - Faction: Alliance, Set: Expert1, Rarity: Rare
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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(
        EntityType::SOURCE, RelaCondList{ std::make_shared<RelaCondition>(
                                RelaCondition::IsSideBySide()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_093e", EntityType::STACK));
    cards.emplace("EX1_093", cardDef);

    // ---------------------------------------- MINION - NEUTRAL
    // [EX1_095] Gadgetzan Auctioneer - COST:5 [ATK:4/HP:4]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you cast a spell, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DrawTask>(1) };
    cards.emplace("EX1_095", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_096] Loot Hoarder - COST:2 [ATK:2/HP:1]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(std::make_shared<DrawTask>(1));
    cards.emplace("EX1_096", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_097] Abomination - COST:5 [ATK:4/HP:4]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>.
    //       <b>Deathrattle:</b> Deal 2 damage to all characters.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<DamageTask>(EntityType::ALL, 2));
    cards.emplace("EX1_097", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_100] Lorewalker Cho - COST:2 [ATK:0/HP:4]
    // - Faction: Neutral, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever a player casts a spell,
    //       put a copy into the other player's hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<ConditionTask>(
            EntityType::TARGET, RelaCondList{ std::make_shared<RelaCondition>(
                                    RelaCondition::IsFriendly()) }),
        std::make_shared<FlagTask>(
            true, TaskList{ std::make_shared<CopyTask>(
                      EntityType::TARGET, ZoneType::HAND, 1, false, true) }),
        std::make_shared<FlagTask>(
            false, TaskList{ std::make_shared<CopyTask>(EntityType::TARGET,
                                                        ZoneType::HAND) })
    };
    cards.emplace("EX1_100", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_102] Demolisher - COST:3 [ATK:1/HP:4]
    // - Race: Mechanical, Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       deal 2 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomTask>(EntityType::ENEMIES, 1),
        std::make_shared<DamageTask>(EntityType::STACK, 2)
    };
    cards.emplace("EX1_102", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_103] Coldlight Seer - COST:3 [ATK:2/HP:3]
    // - Race: Murloc, Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your other Murlocs +2 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::MINIONS_NOSOURCE));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsRace(Race::MURLOC)) }));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_103e", EntityType::STACK));
    cards.emplace("EX1_103", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_105] Mountain Giant - COST:12 [ATK:8/HP:8]
    // - Race: Elemental, Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: Costs (1) less for each other card in your hand.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<AdaptiveCostEffect>([](const Playable* playable) {
            return playable->player->GetHandZone()->GetCount() - 1;
        }));
    cards.emplace("EX1_105", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_110] Cairne Bloodhoof - COST:6 [ATK:5/HP:5]
    // - Faction: Alliance, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 5/5 Baine Bloodhoof.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("EX1_110t", SummonSide::DEATHRATTLE));
    cards.emplace("EX1_110", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_116] Leeroy Jenkins - COST:5 [ATK:6/HP:2]
    // - Faction: Alliance, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Charge</b>.
    //       <b>Battlecry:</b> Summon two 1/1 Whelps for your opponent.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CHARGE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{ std::make_shared<SummonOpTask>("EX1_116t") }, 2));
    cards.emplace("EX1_116", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_162] Dire Wolf Alpha - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Adjacent minions have +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ADJACENT_BUFF = 1
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<AdjacentAura>("EX1_162o"));
    cards.emplace("EX1_162", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_170] Emperor Cobra - COST:3 [ATK:2/HP:3]
    // - Race: Beast, Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - POISONOUS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_170", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_186] SI:7 Infiltrator - COST:4 [ATK:5/HP:4]
    // - Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a random enemy <b>Secret</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::ENEMY_SECRETS, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<MoveToGraveyardTask>(EntityType::STACK));
    cards.emplace("EX1_186", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_187] Arcane Devourer - COST:8 [ATK:4/HP:8]
    // - Race: Elemental, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you cast a spell, gain +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_187e", EntityType::SOURCE) };
    cards.emplace("EX1_187", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_188] Barrens Stablehand - COST:7 [ATK:5/HP:5]
    // - Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a random Beast.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<RandomMinionTask>(TagValues{
        { GameTag::CARDRACE, static_cast<int>(Race::BEAST), RelaSign::EQ } }));
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>());
    cards.emplace("EX1_188", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_189] Brightwing - COST:3 [ATK:3/HP:2]
    // - Race: Dragon, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a random <b>Legendary</b>
    //       minion to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomCardTask>(CardType::MINION, CardClass::INVALID,
                                         Race::INVALID, Rarity::LEGENDARY));
    cardDef.power.AddPowerTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cards.emplace("EX1_189", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_190] High Inquisitor Whitemane - COST:6 [ATK:5/HP:7]
    // - Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon all friendly minions
    //       that died this turn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<CustomTask>(
        [](Player* player, [[maybe_unused]] Entity* source,
           [[maybe_unused]] Playable* target) {
            const auto field = player->GetFieldZone();
            if (field->IsFull())
            {
                return;
            }

            const int num = player->GetNumFriendlyMinionsDiedThisTurn();
            auto& graveyard = *(player->GetGraveyardZone());

            std::vector<int> buffer;
            buffer.reserve(num);
            int k = 0;

            for (int i = graveyard.GetCount() - 1, j = 0; j < num; --i)
            {
                if (!graveyard[i]->isDestroyed)
                {
                    continue;
                }

                if (graveyard[i]->card->GetCardType() != CardType::MINION)
                {
                    continue;
                }

                buffer.emplace_back(i);

                ++j;
                ++k;
            }

            for (--k; k >= 0; --k)
            {
                const auto playable = Entity::GetFromCard(
                    player, graveyard[buffer[k]]->card, std::nullopt, field);
                field->Add(playable);

                if (field->IsFull())
                {
                    return;
                }
            }
        }));
    cards.emplace("EX1_190", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_249] Baron Geddon - COST:7 [ATK:7/HP:7]
    // - Race: Elemental, Faction: Neutral, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       deal 2 damage to all other characters.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DamageTask>(
        EntityType::ALL_NOSOURCE, 2) };
    cards.emplace("EX1_249", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_283] Frost Elemental - COST:6 [ATK:5/HP:5]
    // - Race: Elemental, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Freeze</b> a character.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<FreezeTask>(EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cards.emplace("EX1_283", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_284] Azure Drake - COST:5 [ATK:4/HP:5]
    // - Race: Dragon, Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    //       <b>Battlecry:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cards.emplace("EX1_284", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_298] Ragnaros the Firelord - COST:8 [ATK:8/HP:8]
    // - Race: Elemental, Faction: Neutral, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Can't attack. At the end of your turn,
    //       deal 8 damage to a random enemy.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<IncludeTask>(EntityType::ENEMIES),
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsNotDead()) }),
        std::make_shared<RandomTask>(EntityType::STACK, 1),
        std::make_shared<DamageTask>(EntityType::STACK, 8)
    };
    cards.emplace("EX1_298", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_390] Tauren Warrior - COST:3 [ATK:2/HP:3]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b> Has +3 Attack while damaged.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(Triggers::EnrageTrigger("EX1_390e")));
    cards.emplace("EX1_390", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_396] Mogu'shan Warden - COST:4 [ATK:1/HP:7]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_396", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_405] Shieldbearer - COST:1 [ATK:0/HP:4]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_405", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_412] Raging Worgen - COST:3 [ATK:3/HP:3]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Has +1 Attack and <b>Windfury</b> while damaged.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // --------------------------------------------------------
    // RefTag:
    // - WINDFURY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<EnrageEffect>(AuraType::SELF, "EX1_412e"));
    cards.emplace("EX1_412", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_507] Murloc Warleader - COST:3 [ATK:3/HP:3]
    // - Race: Murloc, Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: Your other Murlocs have +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<Aura>(AuraType::FIELD_EXCEPT_SOURCE, "EX1_507e"));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition = std::make_shared<SelfCondition>(
            SelfCondition::IsRace(Race::MURLOC));
    }
    cards.emplace("EX1_507", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_509] Murloc Tidecaller - COST:1 [ATK:1/HP:2]
    // - Race: Murloc, Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you summon a Murloc, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::SUMMON));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::MURLOC))
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "EX1_509e", EntityType::SOURCE) };
    cards.emplace("EX1_509", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_556] Harvest Golem - COST:3 [ATK:2/HP:3]
    // - Race: Mechanical, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 2/1 Damaged Golem.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("skele21", SummonSide::DEATHRATTLE));
    cards.emplace("EX1_556", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_557] Nat Pagle - COST:2 [ATK:0/HP:4]
    // - Faction: Neutral, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       you have a 50% chance to draw an extra card.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->percentage = 0.5f;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DrawTask>(1) };
    cards.emplace("EX1_557", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_558] Harrison Jones - COST:5 [ATK:5/HP:4]
    // - Faction: Neutral, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy your opponent's weapon
    //       and draw cards equal to its Durability.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::ENEMY_WEAPON, GameTag::DURABILITY));
    cardDef.power.AddPowerTask(std::make_shared<GetGameTagTask>(
        EntityType::ENEMY_WEAPON, GameTag::DAMAGE, 0, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<MathNumberIndexTask>(0, 1, MathOperation::SUB));
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::ENEMY_WEAPON));
    cardDef.power.AddPowerTask(std::make_shared<DrawNumberTask>());
    cards.emplace("EX1_558", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_560] Nozdormu - COST:9 [ATK:8/HP:8]
    // - Race: Dragon, Faction: Neutral, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Players only have 15 seconds to take their turns.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::PLAYERS, EffectList{ std::make_shared<Effect>(
                               GameTag::TIMEOUT, EffectOperator::SET, -60) }));
    cards.emplace("EX1_560", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_561] Alexstrasza - COST:9 [ATK:8/HP:8]
    // - Race: Dragon, Faction: Neutral, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Set a hero's remaining Health to 15.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_HERO_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<CustomTask>(
        []([[maybe_unused]] Player* player, [[maybe_unused]] Entity* source,
           [[maybe_unused]] Playable* target) {
            Hero* hero = dynamic_cast<Hero*>(target);
            hero->SetDamage(hero->GetBaseHealth() - 15);
        }));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_HERO_TARGET, 0 } };
    cards.emplace("EX1_561", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_562] Onyxia - COST:9 [ATK:8/HP:8]
    // - Race: Dragon, Faction: Neutral, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon 1/1 Whelps until your side
    //       of the battlefield is full.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{ std::make_shared<SummonTask>("EX1_116t", SummonSide::RIGHT),
                  std::make_shared<SummonTask>("EX1_116t", SummonSide::LEFT) },
        3));
    cards.emplace("EX1_562", cardDef);

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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_563", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_564] Faceless Manipulator - COST:5 [ATK:3/HP:3]
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a minion and become a copy of it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_NONSELF_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<TransformCopyTask>());
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_NONSELF_TARGET, 0 } };
    cards.emplace("EX1_564", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_572] Ysera - COST:9 [ATK:4/HP:12]
    // - Race: Dragon, Faction: Neutral, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of your turn, add a Dream Card to your hand.
    // --------------------------------------------------------
    // Entourage: DREAM_01, DREAM_02, DREAM_03, DREAM_04, DREAM_05
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomEntourageTask>(1),
        std::make_shared<AddStackToTask>(EntityType::HAND)
    };
    cardDef.property.entourages =
        Entourages{ "DREAM_01", "DREAM_02", "DREAM_03", "DREAM_04",
                    "DREAM_05" };
    cards.emplace("EX1_572", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_577] The Beast - COST:6 [ATK:9/HP:7]
    // - Race: Beast, Faction: Neutral, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 3/3 Finkle Einhorn
    //       for your opponent.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonOpTask>("EX1_finkle"));
    cards.emplace("EX1_577", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_583] Priestess of Elune - COST:6 [ATK:5/HP:4]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 4 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<HealTask>(EntityType::HERO, 4));
    cards.emplace("EX1_583", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_584] Ancient Mage - COST:4 [ATK:2/HP:5]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give adjacent minions
    //       <b>Spell Damage +1</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(
        EntityType::SOURCE, RelaCondList{ std::make_shared<RelaCondition>(
                                RelaCondition::IsSideBySide()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_584e", EntityType::STACK));
    cards.emplace("EX1_584", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_586] Sea Giant - COST:10 [ATK:8/HP:8]
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: Costs (1) less for each other minion
    //       on the battlefield.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<AdaptiveCostEffect>([=](const Playable* playable) {
            return playable->player->GetFieldZone()->GetCount() +
                   playable->player->opponent->GetFieldZone()->GetCount();
        }));
    cards.emplace("EX1_586", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_590] Blood Knight - COST:3 [ATK:3/HP:3]
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> All minions lose <b>Divine Shield</b>.
    //       Gain +3/+3 for each Shield lost.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::ALL_MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsTagValue(GameTag::DIVINE_SHIELD, 1)) }));
    cardDef.power.AddPowerTask(std::make_shared<SetGameTagTask>(
        EntityType::STACK, GameTag::DIVINE_SHIELD, 0));
    cardDef.power.AddPowerTask(std::make_shared<CountTask>(EntityType::STACK));
    cardDef.power.AddPowerTask(std::make_shared<MathMultiplyTask>(3));
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "EX1_590e", EntityType::SOURCE, true));
    cards.emplace("EX1_590", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_595] Cult Master - COST:4 [ATK:4/HP:2]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever one of your other minions dies, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::DEATH));
    cardDef.power.GetTrigger()->triggerSource =
        TriggerSource::MINIONS_EXCEPT_SELF;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DrawTask>(1) };
    cards.emplace("EX1_595", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_597] Imp Master - COST:3 [ATK:1/HP:5]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       deal 1 damage to this minion and summon a 1/1 Imp.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<DamageTask>(EntityType::SOURCE, 1),
        std::make_shared<SummonTask>("EX1_598", SummonSide::RIGHT)
    };
    cards.emplace("EX1_597", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_614] Xavius - COST:6 [ATK:7/HP:5]
    // - Race: Demon, Faction: Neutral, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you play a card, summon a 2/1 Satyr.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::PLAY_CARD));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "EX1_614t", SummonSide::RIGHT) };
    cards.emplace("EX1_614", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_616] Mana Wraith - COST:2 [ATK:2/HP:2]
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: ALL minions cost (1) more.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::HANDS, EffectList{ Effects::AddCost(1) }));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsMinion());
    }
    cards.emplace("EX1_616", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_620] Molten Giant - COST:20 [ATK:8/HP:8]
    // - Race: Elemental, Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: Costs (1) less for each damage your hero has taken.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<AdaptiveCostEffect>([](const Playable* playable) {
            return playable->player->GetHero()->GetDamage();
        }));
    cards.emplace("EX1_620", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_017] Hungry Crab - COST:1 [ATK:1/HP:2]
    // - Race: Beast, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a Murloc and gain +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_TARGET_WITH_RACE = 14
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::TARGET, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsRace(Race::MURLOC)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DestroyTask>(EntityType::TARGET),
                        std::make_shared<AddEnchantmentTask>(
                            "NEW1_017e", EntityType::SOURCE) }));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_TARGET_WITH_RACE, 14 } };
    cards.emplace("NEW1_017", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_018] Bloodsail Raider - COST:2 [ATK:2/HP:3]
    // - Race: Pirate, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain Attack equal to the Attack
    //       of your weapon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<GetGameTagTask>(EntityType::WEAPON, GameTag::ATK));
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "NEW1_018e", EntityType::SOURCE, true));
    cards.emplace("NEW1_018", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_019] Knife Juggler - COST:2 [ATK:3/HP:2]
    // - Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you summon a minion,
    //       deal 1 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_SUMMON));
    cardDef.power.GetTrigger()->triggerSource =
        TriggerSource::MINIONS_EXCEPT_SELF;
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<IncludeTask>(EntityType::ENEMIES),
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsNotDead()) }),
        std::make_shared<RandomTask>(EntityType::STACK, 1),
        std::make_shared<DamageTask>(EntityType::STACK, 1)
    };
    cards.emplace("NEW1_019", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_020] Wild Pyromancer - COST:2 [ATK:3/HP:2]
    // - Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you cast a spell, deal 1 damage to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_CAST));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DamageTask>(
        EntityType::ALL_MINIONS, 1) };
    cards.emplace("NEW1_020", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_021] Doomsayer - COST:2 [ATK:0/HP:7]
    // - Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: At the start of your turn, destroy all minions.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DestroyTask>(
        EntityType::ALL_MINIONS) };
    cards.emplace("NEW1_021", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_022] Dread Corsair - COST:4 [ATK:3/HP:3]
    // - Race: Pirate, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       Costs (1) less per Attack of your weapon.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<AdaptiveCostEffect>([](const Playable* playable) {
            if (!playable->player->GetHero()->HasWeapon())
            {
                return 0;
            }

            return playable->player->GetHero()->weapon->GetAttack();
        }));
    cards.emplace("NEW1_022", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_023] Faerie Dragon - COST:2 [ATK:3/HP:2]
    // - Race: Dragon, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("NEW1_023", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_024] Captain Greenskin - COST:5 [ATK:5/HP:4]
    // - Race: Pirate, Set: Expert1, Rarity: legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your weapon +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("NEW1_024o", EntityType::WEAPON));
    cards.emplace("NEW1_024", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_025] Bloodsail Corsair - COST:2 [ATK:1/HP:2]
    // - Race: Pirate, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Remove 1 Durability from
    //       your opponent's weapon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<RemoveDurabilityTask>(1, true));
    cards.emplace("NEW1_025", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_026] Violet Teacher - COST:4 [ATK:3/HP:5]
    // - Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you cast a spell,
    //       summon a 1/1 Violet Apprentice.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "NEW1_026t", SummonSide::RIGHT) };
    cards.emplace("NEW1_026", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_027] Southsea Captain - COST:3 [ATK:3/HP:3]
    // - Race: Pirate, Faction: Neutral, Set: Expert1, Rarity: Epic
    // --------------------------------------------------------
    // Text: Your other Pirates have +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<Aura>(AuraType::FIELD_EXCEPT_SOURCE, "NEW1_027e"));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition = std::make_shared<SelfCondition>(
            SelfCondition::IsRace(Race::PIRATE));
    }
    cards.emplace("NEW1_027", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_029] Millhouse Manastorm - COST:2 [ATK:4/HP:4]
    // - Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Enemy spells cost (0) next turn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("NEW1_029t", EntityType::PLAYER));
    cards.emplace("NEW1_029", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_030] Deathwing - COST:10 [ATK:12/HP:12]
    // - Race: Dragon, Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy all other minions
    //       and discard your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::ALL_MINIONS_NOSOURCE));
    cardDef.power.AddPowerTask(
        std::make_shared<RemoveHandTask>(EntityType::HAND));
    cards.emplace("NEW1_030", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_037] Master Swordsmith - COST:2 [ATK:1/HP:3]
    // - Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       give another random friendly minion +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomTask>(EntityType::MINIONS_NOSOURCE, 1),
        std::make_shared<AddEnchantmentTask>("NEW1_037e", EntityType::STACK)
    };
    cards.emplace("NEW1_037", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_038] Gruul - COST:8 [ATK:7/HP:7]
    // - Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of each turn, gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->eitherTurn = true;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "NEW1_038o", EntityType::SOURCE) };
    cards.emplace("NEW1_038", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_040] Hogger - COST:6 [ATK:4/HP:4]
    // - Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       summon a 2/2 Gnoll with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "NEW1_040t", SummonSide::RIGHT) };
    cards.emplace("NEW1_040", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_041] Stampeding Kodo - COST:5 [ATK:3/HP:5]
    // - Race: Beast, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a random enemy minion
    //       with 2 or less Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::ENEMY_MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsTagValue(GameTag::ATK, 2, RelaSign::LEQ)) }));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::STACK));
    cards.emplace("NEW1_041", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [tt_004] Flesheating Ghoul - COST:3 [ATK:3/HP:3]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever a minion dies, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::DEATH));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::ALL_MINIONS;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "tt_004o", EntityType::SOURCE) };
    cards.emplace("tt_004", cardDef);
}

void Expert1CardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [CS2_152] Squire (*) - COST:1 [ATK:2/HP:2]
    // - Faction: Alliance, Set: Expert1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("CS2_152", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CS2_188o] Inspired (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: This minion has +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("CS2_188o"));
    cards.emplace("CS2_188o", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CS2_221e] Sharp! (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +2 Attack from Spiteful Smith.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(
        std::make_shared<Effect>(GameTag::ATK, EffectOperator::ADD, 2)));
    cards.emplace("CS2_221e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DREAM_05e] Nightmare (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: This minion has +4/+4, but will be destroyed soon.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("DREAM_05e"));
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DestroyTask>(
        EntityType::TARGET) };
    cards.emplace("DREAM_05e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_001e] Warded (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::AttackN(2)));
    cards.emplace("EX1_001e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_004e] Elune's Grace (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::HealthN(1)));
    cards.emplace("EX1_004e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_009e] Enraged (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +5 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_009e"));
    cards.emplace("EX1_009e", cardDef);

    // ---------------------------------------- SPELL - NEUTRAL
    // [EX1_014t] Bananas (*) - COST:1
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Give a minion +1/+1.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("EX1_014te", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("EX1_014t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_014te] Bananas (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Has +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_014te"));
    cards.emplace("EX1_014te", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_043e] Hour of Twilight (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Enchants::AddHealthScriptTag));
    cards.emplace("EX1_043e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_044e] Level Up! (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased Attack and Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Effects::AttackHealthN(1)));
    cards.emplace("EX1_044e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_046e] Tempered (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_046e"));
    cards.emplace("EX1_046e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_055o] Empowered (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Mana Addict has increased Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Effects::AttackN(2), false, true));
    cards.emplace("EX1_055o", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_059e] Experiments! (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Attack and Health have been swapped by Crazed Alchemist.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Enchants::SetAttackHealthScriptTag));
    cards.emplace("EX1_059e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_080o] Keeping Secrets (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(
        std::vector<std::shared_ptr<IEffect>>{ Effects::AttackHealthN(1) }));
    cards.emplace("EX1_080o", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_093e] Hand of Argus (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +1/+1 and <b>Taunt</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_093e"));
    cards.emplace("EX1_093e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_103e] Mrghlglhal (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +2 Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_103e"));
    cards.emplace("EX1_103e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_187e] Arcane Gorged (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<OngoingEnchant>(Effects::AttackHealthN(2)));
    cards.emplace("EX1_187e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_110t] Baine Bloodhoof (*) - COST:4 [ATK:5/HP:5]
    // - Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_110t", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_116t] Whelp (*) - COST:1 [ATK:1/HP:1]
    // - Race: Dragon, Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_116t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_162o] Strength of the Pack (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +1 Attack from Dire Wolf Alpha.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_162o"));
    cards.emplace("EX1_162o", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_390e] Enraged (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +3 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_390e"));
    cards.emplace("EX1_390e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_412e] Enraged (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +1 Attack and <b>Windfury</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_412e"));
    cards.emplace("EX1_412e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_507e] Mrgglaargl! (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +2 Attack from Murloc Warleader.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("EX1_507e"));
    cards.emplace("EX1_507e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_509e] Blarghghl (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::AttackN(1)));
    cards.emplace("EX1_509e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_584e] Teachings of the Kirin Tor (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Effects::SpellPowerN(1)));
    cards.emplace("EX1_584e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [EX1_590e] Shadows of M'uru (*) - COST:0
    // - Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // Text: This minion has consumed Divine Shields and
    //       has increased Attack and Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Enchants::AddAttackHealthScriptTag));
    cards.emplace("EX1_590e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_614t] Xavian Satyr (*) - COST:1 [ATK:2/HP:1]
    // - Race: Demon, Set: Expert1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_614t", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_598] Imp (*) - COST:1 [ATK:1/HP:1]
    // - Race: Demon, Faction: Neutral, Set: Expert1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_598", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_finkle] Finkle Einhorn (*) - COST:3 [ATK:3/HP:3]
    // - Race: Beast, Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_finkle", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_tk28] Squirrel (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_tk28", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_tk29] Devilsaur (*) - COST:5 [ATK:5/HP:5]
    // - Race: Beast, Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("EX1_tk29", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [NEW1_017e] Full Belly (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +2/+2. Full of Murloc.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("NEW1_017e"));
    cards.emplace("NEW1_017e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [NEW1_018e] Treasure Crazed (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Enchants::AddAttackScriptTag));
    cards.emplace("NEW1_018e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [NEW1_024o] Greenskin's Command (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(std::vector<std::shared_ptr<IEffect>>(
            { Effects::AttackN(1), Effects::DurabilityN(1) })));
    cards.emplace("NEW1_024o", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_026t] Violet Apprentice (*) - COST:1 [ATK:1/HP:1]
    // - Set: Expert1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("NEW1_026t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [NEW1_027e] Yarrr! (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Southsea Captain is granting +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("NEW1_027e"));
    cards.emplace("NEW1_027e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [NEW1_029t] Kill Millhouse! (*) - COST:0
    // - Set: Expert1, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Spells cost (0) this turn!
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::ENEMY_HAND, EffectList{ Effects::SetCost(0) }));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsSpell());
        aura->removeTrigger = { TriggerType::TURN_END,
                                std::make_shared<SelfCondition>(
                                    SelfCondition::IsEnemyTurn()) };
    }
    cards.emplace("NEW1_029t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [NEW1_037e] Equipped (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::AttackN(1)));
    cards.emplace("NEW1_037e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [NEW1_038o] Growth (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Gruul is growing...
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<OngoingEnchant>(Effects::AttackHealthN(1)));
    cards.emplace("NEW1_038o", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [NEW1_040t] Gnoll (*) - COST:2 [ATK:2/HP:2]
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("NEW1_040t", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [skele21] Damaged Golem (*) - COST:1 [ATK:2/HP:1]
    // - Race: Mechanical, Faction: Neutral, Set: Expert1, Rarity: Common
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("skele21", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [tt_004o] Cannibalize (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<OngoingEnchant>(
        std::vector<std::shared_ptr<IEffect>>{ Effects::AttackN(1) }));
    cards.emplace("tt_004o", cardDef);
}

void Expert1CardsGen::AddDreamNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - DREAM
    // [DREAM_01] Laughing Sister (*) - COST:2 [ATK:3/HP:5]
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DREAM_01", cardDef);

    // ------------------------------------------ SPELL - DREAM
    // [DREAM_02] Ysera Awakens (*) - COST:3
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Deal 5 damage to all minions except Ysera.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::ALL_MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsName("Ysera", false)) }));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::STACK, 5, true));
    cards.emplace("DREAM_02", cardDef);

    // ----------------------------------------- MINION - DREAM
    // [DREAM_03] Emerald Drake (*) - COST:4 [ATK:7/HP:6]
    // - Race: Dragon, Set: Expert1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DREAM_03", cardDef);

    // ------------------------------------------ SPELL - DREAM
    // [DREAM_04] Dream (*) - COST:1
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Return an enemy minion to your opponent's hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<ReturnHandTask>(EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_ENEMY_TARGET, 0 } };
    cards.emplace("DREAM_04", cardDef);

    // ------------------------------------------ SPELL - DREAM
    // [DREAM_05] Nightmare (*) - COST:0
    // - Set: Expert1
    // --------------------------------------------------------
    // Text: Give a minion +4/+4. At the start of your next turn, destroy it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("DREAM_05e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DREAM_05", cardDef);
}

void Expert1CardsGen::AddAll(std::map<std::string, CardDef>& cards)
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

    AddDreamNonCollect(cards);
}
}  // namespace RosettaStone::PlayMode
