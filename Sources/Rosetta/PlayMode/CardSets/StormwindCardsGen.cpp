// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/CardSets/StormwindCardsGen.hpp>
#include <Rosetta/PlayMode/Cards/CardPowers.hpp>

namespace RosettaStone::PlayMode
{
void StormwindCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void StormwindCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void StormwindCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - DRUID
    // [SW_419] Oracle of Elune - COST:3 [ATK:2/HP:4]
    // - Set: STORMWIND, Rarity: Epic
    // --------------------------------------------------------
    // Text: After you play a minion that costs (2) or less,
    //       summon a copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_PLAY_MINION));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsCost(2, RelaSign::LEQ))
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SummonCopyTask>(
        EntityType::TARGET) };
    cards.emplace("SW_419", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [SW_422] Sow the Soil - COST:1
    // - Set: STORMWIND, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: <b>Choose One</b> - Give your minions +1 Attack;
    //       or Summon a 2/2 Treant.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.chooseCardIDs = ChooseCardIDs{ "SW_422a", "SW_422b" };
    cards.emplace("SW_422", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [SW_428] Lost in the Park - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline:</b> Gain 4 Attack with your hero.
    //       <b>Reward:</b> Gain 5 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::GAIN_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<QuestProgressTask>(
        TaskList{ std::make_shared<ArmorTask>(5) }, ProgressType::GAIN_ATTACK,
        "SW_428t") };
    cardDef.property.questProgressTotal = 4;
    cards.emplace("SW_428", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [SW_429] Best in Shell - COST:6
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Tradeable</b>
    //       Summon two 2/7 Turtles with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TRADEABLE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("SW_429t", 2, SummonSide::SPELL));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("SW_429", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [SW_431] Park Panther - COST:4 [ATK:4/HP:4]
    // - Race: Beast, Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b>. Whenever this attacks,
    //       give your hero +3 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SELF;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "SW_431e", EntityType::HERO) };
    cards.emplace("SW_431", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [SW_432] Kodo Mount - COST:4
    // - Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give a minion +4/+2 and <b>Rush</b>.
    //       When it dies, summon a Kodo.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("SW_432e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("SW_432", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [SW_436] Wickerclaw - COST:2 [ATK:1/HP:4]
    // - Race: Beast, Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: After your hero gains Attack,
    //       this minion gains +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::GAIN_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "SW_436e", EntityType::SOURCE) };
    cardDef.property.questProgressTotal = 4;
    cards.emplace("SW_436", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [SW_437] Composting - COST:2
    // - Set: STORMWIND, Rarity: Epic
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Give your minions "<b>Deathrattle:</b> Draw a card."
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("SW_437e", EntityType::MINIONS));
    cards.emplace("SW_437", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [SW_439] Vibrant Squirrel - COST:1 [ATK:2/HP:1]
    // - Race: Beast, Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Shuffle 4 Acorns into your deck.
    //       When drawn, summon a 2/1 Squirrel.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddCardTask>(EntityType::DECK, "SW_439t", 4));
    cards.emplace("SW_439", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [SW_447] Sheldras Moontree - COST:8 [ATK:5/HP:5]
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> The next 3 spells you draw are
    //       <b>Cast When Drawn</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [DED_001] Druid of the Reef - COST:1 [ATK:1/HP:1]
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Choose One - </b>Transform into
    //       a 3/1 Shark with <b>Rush</b>; or
    //       a 1/3 Turtle with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<TransformTask>(EntityType::SOURCE, "DED_001c"));
    cardDef.property.chooseCardIDs = ChooseCardIDs{ "DED_001a", "DED_001b" };
    cards.emplace("DED_001", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [DED_002] Moonlit Guidance - COST:2
    // - Set: STORMWIND, Rarity: Rare
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: <b>Discover</b> a copy of a card in your deck.
    //       If you play it this turn, draw the original.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [DED_003] Jerry Rig Carpenter - COST:2 [ATK:2/HP:1]
    // - Race: Pirate, Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a <b>Choose One</b> spell
    //       and split it.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void StormwindCardsGen::AddDruidNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ SPELL - DRUID
    // [SW_422a] New Growth - COST:1
    // - Set: STORMWIND
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Summon a 2/2 Treant.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("EX1_158t", SummonSide::DEFAULT));
    cards.emplace("SW_422a", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [SW_422b] Fertilizer - COST:1
    // - Set: STORMWIND
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Give your minions +1 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("SW_422e", EntityType::MINIONS));
    cards.emplace("SW_422b", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [SW_422e] Replanted - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("SW_422e"));
    cards.emplace("SW_422e", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [SW_422t] Treant - COST:2 [ATK:2/HP:2]
    // - Set: STORMWIND
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [SW_428t] Defend the Squirrels - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline:</b> Gain 5 Attack with your hero.
    //       <b>Reward:</b> Gain 5 Armor and draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::GAIN_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<QuestProgressTask>(
        TaskList{ std::make_shared<ArmorTask>(5),
                  std::make_shared<DrawTask>(1) },
        ProgressType::GAIN_ATTACK, "SW_428t2") };
    cardDef.property.questProgressTotal = 5;
    cards.emplace("SW_428t", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [SW_428t2] Feral Friendsy - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline:</b> Gain 6 Attack with your hero.
    //       <b>Reward:</b> Guff the Tough.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::GAIN_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<QuestProgressTask>(
        "SW_428t4", ProgressType::GAIN_ATTACK) };
    cardDef.property.questProgressTotal = 6;
    cards.emplace("SW_428t2", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [SW_428t4] Guff the Tough - COST:5 [ATK:8/HP:8]
    // - Race: Beast, Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Taunt</b>.
    //       <b>Battlecry:</b> Give your hero +8 Attack this turn.
    //       Gain 8 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("SW_428t4e", EntityType::HERO));
    cardDef.power.AddPowerTask(std::make_shared<ArmorTask>(8));
    cards.emplace("SW_428t4", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [SW_428t4e] Guff's Buff - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Your hero has Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_unique<Enchant>(Effects::AttackN(8), false, true));
    cards.emplace("SW_428t4e", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [SW_429t] Goldshell Turtle - COST:4 [ATK:2/HP:7]
    // - Race: Beast, Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("SW_429t", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [SW_431e] Rawr! - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: +3 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("SW_431e"));
    cards.emplace("SW_431e", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [SW_432e] On a Kodo - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: +4/+2 and <b>Rush</b>.
    //       <b>Deathrattle:</b> Summon a Kodo.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("SW_432e"));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("SW_432t", SummonSide::DEATHRATTLE));
    cards.emplace("SW_432e", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [SW_432t] Guff's Kodo - COST:3 [ATK:4/HP:2]
    // - Race: Beast, Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("SW_432t", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [SW_436e] Wicked Claws - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("SW_436e"));
    cards.emplace("SW_436e", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [SW_439t] Acorn - COST:1
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Casts When Drawn</b>
    //       Summon a 2/1 Squirrel.
    // --------------------------------------------------------
    // GameTag:
    // - TOPDECK = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTopdeckTask(std::make_shared<SummonTask>("SW_439t2"));
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("SW_439t2"));
    cards.emplace("SW_439t", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [SW_439t2] Satisfied Squirrel - COST:1 [ATK:2/HP:1]
    // - Race: Beast, Set: STORMWIND
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("SW_439t2", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [SW_447e] Elune's Guidance - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Your next 3 spells are <b>Cast When Drawn</b>.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [SW_447e2] Elune's Guidance 2 - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Your next 3 spells are <b>Cast When Drawn</b>.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [DED_001a] Shark Form - COST:1 [ATK:3/HP:1]
    // - Race: Beast, Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<TransformTask>(EntityType::SOURCE, "DED_001at"));
    cards.emplace("DED_001a", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [DED_001at] Druid of the Reef - COST:1 [ATK:3/HP:1]
    // - Race: Beast, Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DED_001at", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [DED_001b] Sea Turtle Form - COST:1 [ATK:1/HP:3]
    // - Race: Beast, Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<TransformTask>(EntityType::SOURCE, "DED_001bt"));
    cards.emplace("DED_001b", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [DED_001bt] Druid of the Reef - COST:1 [ATK:1/HP:3]
    // - Race: Beast, Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DED_001bt", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [DED_001c] Druid of the Reef - COST:1 [ATK:3/HP:3]
    // - Race: Beast, Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DED_001c", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [DED_002e] Path of the Moon - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: If played this turn, draw the original copy.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
}

void StormwindCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- SPELL - HUNTER
    // [SW_320] Rats of Extraordinary Size - COST:6
    // - Set: STORMWIND, Rarity: Epic
    // --------------------------------------------------------
    // Text: Summon seven 1/1 Rats.
    //       Any that can't fit on the battlefield go
    //       to your hand with +4/+4.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [SW_321] Aimed Shot - COST:3
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 3 damage.
    //       Your next Hero Power deals 2 more damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("SW_321e", EntityType::HERO));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("SW_321", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [SW_322] Defend the Dwarven District - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline:</b> Deal damage with 3 spells.
    //       <b>Reward:</b> Your Hero Power can target minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [SW_323] The Rat King - COST:5 [ATK:5/HP:5]
    // - Race: Beast, Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Rush</b>. <b>Deathrattle:</b> Go <b>Dormant</b>.
    //       Revive after 5 friendly minions die.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [SW_455] Rodent Nest - COST:4 [ATK:2/HP:2]
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon five 1/1 Rats.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("SW_455t", 5, SummonSide::DEATHRATTLE));
    cards.emplace("SW_455", cardDef);

    // ---------------------------------------- WEAPON - HUNTER
    // [SW_457] Leatherworking Kit - COST:1
    // - Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: After three friendly Beasts die,
    //       draw a Beast and give it +1/+1.
    //       Lose 1 Durability.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [SW_458] Ramming Mount - COST:3
    // - Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give a minion +2/+2 and <b>Immune</b>
    //       while attacking. When it dies, summon a Ram.
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [SW_459] Stormwind Piper - COST:3 [ATK:1/HP:6]
    // - Race: Demon, Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: After this minion attacks, give your Beasts +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [SW_460] Devouring Swarm - COST:0
    // - Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: Choose an enemy minion. Your minions attack it,
    //       then return any that die to your hand.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [SW_463] Imported Tarantula - COST:5 [ATK:4/HP:5]
    // - Race: Beast, Set: STORMWIND, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Tradeable</b>
    //       <b>Deathrattle:</b> Summon two 1/1 Spiders with
    //       <b>Poisonous</b> and <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - TRADEABLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - POISONOUS = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [DED_007] Defias Blastfisher - COST:5 [ATK:3/HP:2]
    // - Race: Pirate, Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 2 damage to a random enemy.
    //       Repeat for each of your Beasts.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [DED_008] Monstrous Parrot - COST:4 [ATK:3/HP:4]
    // - Race: Beast, Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Repeat the last friendly
    //       <b>Deathrattle</b> that triggered.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [DED_009] Doggie Biscuit - COST:2
    // - Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Tradeable</b>
    //       Give a minion +2/+3. After you <b>Trade</b> this,
    //       give a friendly minion <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TRADEABLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
}

void StormwindCardsGen::AddHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [SW_320e] Extraordinarily Sized - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: +4/+4
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [SW_321e] Aiming - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Your next Hero Power deals 2 more damage.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_unique<Enchant>(
        GameTag::HEROPOWER_DAMAGE, EffectOperator::ADD, 2));
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::INSPIRE));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RemoveEnchantmentTask>()
    };
    cardDef.power.GetTrigger()->removeAfterTriggered = true;
    cards.emplace("SW_321e", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [SW_322t] Take the High Ground - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline:</b> Deal damage with 2 spells.
    //       <b>Reward:</b> Set the Cost of your Hero Power to (0).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [SW_322t2] Knock 'Em Down - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline:</b> Deal damage with 2 spells.
    //       <b>Reward:</b> Tavish, Master Marksman.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [SW_322t4] Tavish, Master Marksman - COST:5 [ATK:7/HP:7]
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> For the rest of the game,
    //       spells you cast refresh your Hero Power.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [SW_323e] Rat King's Slumber - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Dormant</b>. Awaken after 5 friendly minions die.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [SW_455t] Rat - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: STORMWIND
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("SW_455t", cardDef);

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [SW_458e] On a Ram - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: +2/+2 and <b>Immune</b> while attacking.
    //       <b>Deathrattle:</b> Summon a Ram.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [SW_458t] Tavish's Ram - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Immune</b> while attacking.
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [SW_459e] Entranced - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [SW_463t] Invasive Spiderling - COST:2 [ATK:1/HP:1]
    // - Race: Beast, Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    //       <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - POISONOUS = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [DED_009e] Good Doggie! - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: +2/+3.
    // --------------------------------------------------------
}

void StormwindCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ WEAPON - MAGE
    // [SW_001] Celestial Ink Set - COST:2
    // - Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you spend 5 Mana on spells,
    //       reduce the cost of a spell in your hand by (5).
    //       Lose 1 Durability.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [SW_107] Fire Sale - COST:4
    // - Set: STORMWIND, Rarity: Common
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: <b>Tradeable</b>
    //       Deal 3 damage to all minions.
    // --------------------------------------------------------
    // RefTag:
    // - TRADEABLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ALL_MINIONS, 3, true));
    cards.emplace("SW_107", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [SW_108] First Flame - COST:1
    // - Set: STORMWIND, Rarity: Rare
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Deal 2 damage to a minion.
    //       Add a Second Flame to your hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "SW_108t"));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("SW_108", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [SW_109] Clumsy Courier - COST:7 [ATK:4/HP:5]
    // - Set: STORMWIND, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Cast the highest Cost spell
    //       from your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [SW_110] Ignite - COST:2
    // - Set: STORMWIND, Rarity: Epic
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Deal 2 damage. Shuffle an Ignite into
    //       your deck that deals one more damage.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [SW_111] Sanctum Chandler - COST:5 [ATK:4/HP:5]
    // - Race: Elemental, Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you cast a Fire spell, draw a spell.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [SW_112] Prestor's Pyromancer - COST:2 [ATK:2/HP:3]
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your next Fire spell has
    //       <b>Spell Damage +2</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [SW_113] Grand Magus Antonidas - COST:8 [ATK:6/HP:6]
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you've cast
    //       a Fire spell on each of your last three turns,
    //       cast 3 Fireballs at random enemies. <i>(@/3)</i>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [SW_450] Sorcerer's Gambit - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline:</b> Cast a Fire, Frost, and Arcane spell.
    //       <b>Reward: </b>Draw a spell.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [SW_462] Hot Streak - COST:0
    // - Set: STORMWIND, Rarity: Common
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Your next Fire spell this turn costs (2) less.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [DED_515] Grey Sage Parrot - COST:6 [ATK:4/HP:5]
    // - Race: Beast, Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Repeat the last spell
    //       you've cast that costs (5) or more.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [DED_516] Deepwater Evoker - COST:4 [ATK:3/HP:4]
    // - Race: Pirate, Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a spell.
    //       Gain Armor equal to its Cost.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [DED_517] Arcane Overflow - COST:5
    // - Set: STORMWIND, Rarity: Rare
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Deal 8 damage to an enemy minion.
    //       Summon a Remnant with stats equal to the excess damage.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------
}

void StormwindCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------- ENCHANTMENT - MAGE
    // [SW_059e] Engineered - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Cost reduced.
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [SW_108t] Second Flame - COST:1
    // - Set: STORMWIND
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Deal 2 damage to a minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("SW_108t", cardDef);

    // ------------------------------------- ENCHANTMENT - MAGE
    // [SW_112e] Burning Hot! - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Your next Fire spell has <b>Spell Damage +2</b>.
    // --------------------------------------------------------

    // ------------------------------------- ENCHANTMENT - MAGE
    // [SW_112e2] Burning Hot! - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Your next Fire spell has <b>Spell Damage +2</b>.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_SILENCED = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [SW_450t] Stall for Time - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline:</b> Cast a Fire, Frost, and Arcane spell.
    //       <b>Reward:</b> <b>Discover</b> one.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [SW_450t2] Reach the Portal Room - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline:</b> Cast a Fire, Frost, and Arcane spell.
    //       <b>Reward:</b> Arcanist Dawngrasp.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [SW_450t4] Arcanist Dawngrasp - COST:5 [ATK:7/HP:7]
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> For the rest of the game,
    //       you have <b>Spell Damage +2</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // ------------------------------------- ENCHANTMENT - MAGE
    // [SW_450t4e] Power of Dawngrasp - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Spell Damage +3</b>
    // --------------------------------------------------------

    // ------------------------------------- ENCHANTMENT - MAGE
    // [SW_462e] Hot Streak - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: The next Fire spell you play costs (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [DED_517t] Arcane Remnant - COST:1 [ATK:1/HP:1]
    // - Race: Elemental, Set: STORMWIND
    // --------------------------------------------------------
}

void StormwindCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - PALADIN
    // [SW_046] City Tax - COST:2
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Tradeable</b>
    //       <b>Lifesteal</b>. Deal 1 damage to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // - TRADEABLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ALL_MINIONS, 1, true));
    cards.emplace("SW_046", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [SW_047] Highlord Fordragon - COST:6 [ATK:5/HP:5]
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    //       After a friendly minion loses <b>Divine Shield</b>,
    //       give a minion in your hand +5/+5.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DIVINE_SHIELD = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - PALADIN
    // [SW_048] Prismatic Jewel Kit - COST:1
    // - Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: After a friendly minion loses <b>Divine Shield</b>,
    //       give minions in your hand +1/+1.
    //       Lose 1 Durability.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [SW_049] Blessed Goods - COST:1
    // - Set: STORMWIND, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: <b>Discover</b> a <b>Secret</b>, weapon,
    //       or <b>Divine Shield</b> minion.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // - SECRET = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [SW_305] First Blade of Wrynn - COST:4 [ATK:3/HP:5]
    // - Set: STORMWIND, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    //       <b>Battlecry:</b> Gain <b>Rush</b>
    //       if this has at least 4 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsAttack(4, RelaSign::GEQ)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<SetGameTagTask>(EntityType::SOURCE,
                                                         GameTag::RUSH, 1) }));
    cards.emplace("SW_305", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [SW_313] Rise to the Occasion - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline:</b> Play 3 different 1-Cost cards.
    //       <b>Reward:</b> Equip a 1/4 Light's Justice.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - PALADIN
    // [SW_314] Lightbringer's Hammer - COST:3
    // - Set: STORMWIND, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    //       Can't attack heroes.
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [SW_315] Alliance Bannerman - COST:3 [ATK:2/HP:2]
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a minion.
    //       Give minions in your hand +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawMinionTask>(1, false));
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "SW_315e", EntityType::MINIONS_HAND));
    cards.emplace("SW_315", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [SW_316] Noble Mount - COST:2
    // - Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give a minion +1/+1 and <b>Divine Shield</b>.
    //       When it dies, summon a Warhorse.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("SW_316e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("SW_316", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [SW_317] Catacomb Guard - COST:3 [ATK:1/HP:4]
    // - Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    //       <b>Battlecry:</b> Deal damage equal to
    //       this minion's Attack to an enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [DED_500] Wealth Redistributor - COST:5 [ATK:2/HP:8]
    // - Race: Pirate, Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>. <b>Battlecry:</b> Swap the Attack
    //       of the highest and lowest Attack minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [DED_501] Sunwing Squawker - COST:4 [ATK:3/HP:4]
    // - Race: Beast, Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Repeat the last spell
    //       you've cast on a friendly minion on this.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [DED_502] Righteous Defense - COST:3
    // - Set: STORMWIND, Rarity: Rare
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Set a minion's Attack and Health to 1.
    //       Give the stats it lost to a minion in your hand.
    // --------------------------------------------------------
}

void StormwindCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - PALADIN
    // [SW_313t] Pave the Way - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline: </b> Play 3 different 1-Cost cards.
    //       <b>Reward:</b> Upgrade your Hero Power.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [SW_313t2] Avenge the Fallen - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline:</b> Play 3 different 1-Cost cards.
    //       <b>Reward:</b> Lightborn Cariel.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [SW_313t4] Lightborn Cariel - COST:5 [ATK:7/HP:7]
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> For the rest of the game,
    //       your Silver Hand Recruits have +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [SW_313t4e] Light's Strength - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: For the rest of the game,
    //       your Silver Hand Recruits have +2/+2.
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [SW_316t] Cariel's Warhorse - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("SW_316t", cardDef);

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [DED_500e] Redistributed - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Attack was swapped.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [DED_502e] Justified - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: 1/1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [DED_502e2] Light's Favored - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------
}

void StormwindCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- WEAPON - PRIEST
    // [SW_012] Shadowcloth Needle - COST:1
    // - Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you cast a Shadow spell,
    //       deal 1 damage to all enemies.
    //       Lose 1 Durability.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [SW_433] Seek Guidance - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline:</b> Play a 2, 3, and 4-Cost card.
    //       <b>Reward:</b> <b>Discover</b> a card from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [SW_440] Call of the Grave - COST:1
    // - Set: STORMWIND, Rarity: Epic
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: <b>Discover</b> a <b>Deathrattle</b> minion.
    //       If you have enough Mana to play it,
    //       trigger its <b>Deathrattle</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [SW_441] Shard of the Naaru - COST:1
    // - Set: STORMWIND, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: <b>Tradeable</b>
    //       <b>Silence</b> all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - TRADEABLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - SILENCE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SilenceTask>(EntityType::ENEMY_MINIONS));
    cards.emplace("SW_441", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [SW_442] Void Shard - COST:4
    // - Set: STORMWIND, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    //       Deal 4 damage.
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 4, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("SW_442", cardDef);

    // ----------------------------------------- SPELL - PRIEST
    // [SW_443] Elekk Mount - COST:7
    // - Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give a minion +4/+7 and <b>Taunt</b>.
    //       When it dies, summon an Elekk.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("SW_443e", EntityType::TARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("SW_443", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [SW_444] Twilight Deceptor - COST:2 [ATK:2/HP:3]
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If any hero took damage this turn,
    //       draw a Shadow spell.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [SW_445] Psyfiend - COST:3 [ATK:3/HP:4]
    // - Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you cast a Shadow spell,
    //       deal 2 damage to each Hero.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_CAST));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsShadowSpell())
    };
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<DamageTask>(EntityType::HERO, 2),
        std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 2)
    };
    cards.emplace("SW_445", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [SW_446] Voidtouched Attendant - COST:1 [ATK:1/HP:3]
    // - Set: STORMWIND, Rarity: Epic
    // --------------------------------------------------------
    // Text: Both heroes take one extra damage from all sources.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [SW_448] Darkbishop Benedictus - COST:5 [ATK:5/HP:6]
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Start of Game:</b> If the spells in your deck
    //       are all Shadow, enter Shadowform.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    // RefTag:
    // - START_OF_GAME = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [DED_512] Amulet of Undying - COST:3
    // - Set: STORMWIND, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: <b>Tradeable</b>
    //       Resurrect 1 friendly <b>Deathrattle</b> minion.
    //       <i>(Upgrades when <b>Traded</b>!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TRADEABLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [DED_513] Defias Leper - COST:2 [ATK:3/HP:2]
    // - Race: Pirate, Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Shadow spell,
    //       deal 2 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_DRAG_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE,
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsHoldingSpell(SpellSchool::SHADOW)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 2) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_DRAG_TO_PLAY, 0 } };
    cards.emplace("DED_513", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [DED_514] Copycat - COST:3 [ATK:3/HP:4]
    // - Race: Beast, Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a copy of the next card
    //       your opponent plays to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void StormwindCardsGen::AddPriestNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- SPELL - PRIEST
    // [SW_433t] Discover the Void Shard - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline:</b> Play a 5 and 6-Cost card.
    //       <b>Reward:</b> <b>Discover</b> a card from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [SW_433t2] Illuminate the Void - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline:</b> Play a 7 and 8-Cost card.
    //       <b>Reward:</b> Xyrella, the Sanctified.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [SW_433t3] Xyrella, the Sanctified - COST:5 [ATK:7/HP:7]
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Shuffle the Purified Shard
    //       into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [SW_433t3a] Purified Shard - COST:10
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Destroy the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TOPDECK = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [SW_443e] On an Elekk - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: +4/+7 and <b>Taunt</b>.
    //       <b>Deathrattle:</b> Summon an Elekk.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("SW_443e"));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("SW_443t", SummonSide::DEATHRATTLE));
    cards.emplace("SW_443e", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [SW_443t] Xyrella's Elekk - COST:6 [ATK:4/HP:7]
    // - Race: Beast, Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("SW_443t", cardDef);

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [SW_446e] Voidtouched - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Both heroes take one extra damage from all sources.
    // --------------------------------------------------------
}

void StormwindCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - ROGUE
    // [SW_050] Maestra of the Masquerade - COST:2 [ATK:3/HP:2]
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: You start the game as a different class
    //       until you play a Rogue card.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [SW_052] Find the Imposter - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline:</b> Play 2 SI:7 cards.
    //       <b>Reward:</b> Add a Spy Gizmo to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ----------------------------------------- WEAPON - ROGUE
    // [SW_310] Counterfeit Blade - COST:4
    // - Set: STORMWIND, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain a random friendly
    //       <b>Deathrattle</b> that triggered this game.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [SW_311] Garrote - COST:2
    // - Set: STORMWIND, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 2 damage to the enemy hero.
    //       Shuffle 2 Bleeds into your deck that
    //       deal 2 more when drawn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 2, true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::DECK, "SW_311t", 2));
    cards.emplace("SW_311", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [SW_405] Sketchy Information - COST:3
    // - Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: Draw a <b>Deathrattle</b> card that costs (4) or less.
    //       Trigger its <b>Deathrattle.</b>
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [SW_411] SI:7 Informant - COST:4 [ATK:3/HP:3]
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain +1/+1 for each other
    //       SI:7 card you've played this game.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [SW_412] SI:7 Extortion - COST:1
    // - Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Tradeable</b>
    //       Deal 3 damage to an undamaged character.
    // --------------------------------------------------------
    // GameTag:
    // - TRADEABLE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_UNDAMAGED_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                  { PlayReq::REQ_UNDAMAGED_TARGET, 0 } };
    cards.emplace("SW_412", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [SW_413] SI:7 Operative - COST:3 [ATK:2/HP:4]
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       After this attacks a minion, gain <b>Stealth</b>.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SELF;
    cardDef.power.GetTrigger()->conditions =
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsEventTargetIs(CardType::MINION)) };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SetGameTagTask>(
        EntityType::SOURCE, GameTag::STEALTH, 1) };
    cards.emplace("SW_413", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [SW_417] SI:7 Assassin - COST:7 [ATK:4/HP:4]
    // - Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: Costs (1) less for each SI:7 card you've played this game.
    //       <b>Combo:</b> Destroy an enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [SW_434] Loan Shark - COST:3 [ATK:3/HP:4]
    // - Race: Beast, Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your opponent a Coin.
    //       <b>Deathrattle:</b> You get two.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::ENEMY_HAND, "GAME_005", 1));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "GAME_005", 2));
    cards.emplace("SW_434", cardDef);

    // ----------------------------------------- WEAPON - ROGUE
    // [DED_004] Blackwater Cutlass - COST:1
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Tradeable</b>
    //       After you <b>Trade</b> this,
    //       reduce the cost of a spell in your hand by (1).
    // --------------------------------------------------------
    // GameTag:
    // - TRADEABLE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [DED_005] Parrrley - COST:1
    // - Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: Swap this for a card in your opponent's deck.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [DED_510] Edwin, Defias Kingpin - COST:4 [ATK:4/HP:4]
    // - Race: Pirate, Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a card.
    //       If you play it this turn,
    //       gain +2/+2 and repeat this effect.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void StormwindCardsGen::AddRogueNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ SPELL - ROGUE
    // [SW_052t] Learn the Truth - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline:</b> Play 2 SI:7 cards.
    //       <b>Reward:</b> Add a Spy Gizmo to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [SW_052t2] Marked a Traitor - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline:</b> Play 2 SI:7 cards.
    //       <b>Reward:</b> Spymaster Scabbs.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [SW_052t3] Spymaster Scabbs - COST:5 [ATK:7/HP:7]
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add one of each Spy Gizmo
    //       to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [SW_052t4] Fizzflash Distractor - COST:1
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Return an enemy minion to its owner's hand.
    //       They can't play it next turn.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [SW_052t4e] Distracted - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Can't be played.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [SW_052t5] Spy-o-matic - COST:1 [ATK:3/HP:2]
    // - Race: Mechanical, Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Look at 3 cards in
    //       your opponent's deck. Pick one to put on top.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [SW_052t6] Noggen-Fog Generator - COST:1
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Give a minion +2 Attack and <b>Stealth</b>.
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [SW_052t6e] Noggen-Fog - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: +2 Attack and <b>Stealth</b>.
    // --------------------------------------------------------

    // ----------------------------------------- WEAPON - ROGUE
    // [SW_052t7] Hidden Gyroblade - COST:1
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Throw this at a random enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [SW_052t8_t] Undercover Mole - COST:1 [ATK:2/HP:3]
    // - Race: Beast, Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Stealth</b>. After this attacks,
    //       add a random card to your hand
    //       <i>(from your opponent's class).</i>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [SW_310e] Counterfeit Blade - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Copied <b>Deathrattle</b> from {0}.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [SW_311t] Bleed - COST:1
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Casts When Drawn</b>
    //       Deal 2 damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - TOPDECK = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTopdeckTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 2, true));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 2, true));
    cards.emplace("SW_311t", cardDef);

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [SW_411e] Well Informed - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: +1/+1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [DED_004e] Blackwater Treasure - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [DED_510e] Defias Supplies - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: If played this turn, draw a card and give Edwin +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [DED_510e2] King of the Brotherhood - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------
}

void StormwindCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- WEAPON - SHAMAN
    // [SW_025] Auctionhouse Gavel - COST:2
    // - Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: After your hero attacks, reduce the Cost of
    //       a <b>Battlecry</b> minion in your hand by (1).
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [SW_026] Spirit Alpha - COST:4 [ATK:2/HP:5]
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: After you play a card with <b>Overload</b>,
    //       summon a 2/3 Spirit Wolf with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - OVERLOAD = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [SW_031] Command the Elements - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline:</b> Play 3 cards with <b>Overload</b>.
    //       <b>Reward:</b> Unlock your <b>Overloaded</b> Mana Crystals.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    // RefTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [SW_032] Granite Forgeborn - COST:4 [ATK:4/HP:4]
    // - Race: Elemental, Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Reduce the cost of Elementals
    //       in your hand and deck by (1).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [SW_033] Canal Slogger - COST:4 [ATK:6/HP:4]
    // - Race: Elemental, Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>, <b>Lifesteal</b>
    //       <b>Overload:</b> (1)
    // --------------------------------------------------------
    // RefTag:
    // - LIFESTEAL = 1
    // - OVERLOAD = 1
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("SW_033", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [SW_034] Tiny Toys - COST:6
    // - Set: STORMWIND, Rarity: Epic
    // --------------------------------------------------------
    // Text: Summon four random 5-Cost minions.
    //       Make them 2/2.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [SW_035] Charged Call - COST:3
    // - Set: STORMWIND, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: <b>Discover</b> a 1-Cost minion and summon it.
    //       <i>(Upgraded for each <b>Overload</b> card
    //       you played this game!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    // RefTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [SW_095] Investment Opportunity - COST:1
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: Draw an <b>Overload</b> card.
    // --------------------------------------------------------
    // RefTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(ComplexTask::DrawCardFromDeck(
        1, SelfCondList{ std::make_shared<SelfCondition>(
               SelfCondition::IsOverloadCard()) }));
    cards.emplace("SW_095", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [SW_114] Overdraft - COST:1
    // - Set: STORMWIND, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Tradeable</b>
    //       Unlock your <b>Overloaded</b> Mana Crystals
    //       to deal that much damage.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // - TRADEABLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [SW_115] Bolner Hammerbeak - COST:2 [ATK:1/HP:4]
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you play a <b>Battlecry</b> minion,
    //       repeat the first <b>Battlecry</b> played this turn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [DED_509] Brilliant Macaw - COST:3 [ATK:3/HP:3]
    // - Race: Beast, Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Repeat the last <b>Battlecry</b>
    //       you played.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [DED_511] Suckerhook - COST:4 [ATK:3/HP:6]
    // - Race: Pirate, Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       transform your weapon into one that costs (1) more.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [DED_522] Cookie the Cook - COST:3 [ATK:2/HP:3]
    // - Race: Murloc, Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    //       <b>Deathrattle:</b> Equip a 2/3 Stirring Rod
    //       with <b>Lifesteal</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(std::make_shared<WeaponTask>("DED_522t"));
    cards.emplace("DED_522", cardDef);
}

void StormwindCardsGen::AddShamanNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [SW_025e] Sold! - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [SW_031t] Stir the Stones - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline:</b> Play 3 cards with <b>Overload</b>.
    //       <b>Reward:</b> Summon a 3/3 Elemental with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    // RefTag:
    // - OVERLOAD = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [SW_031t2] Tame the Flames - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline:</b> Play 3 cards with <b>Overload</b>.
    //       <b>Reward:</b> Stormcaller Bru'kan.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    // RefTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [SW_031t7] Stormcaller Bru'kan - COST:5 [ATK:7/HP:7]
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> For the rest of the game,
    //       your spells cast twice.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [SW_031t7e] Stormcaller - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Spells cast twice.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [SW_031t8] Living Earth - COST:3 [ATK:3/HP:3]
    // - Race: Elemental, Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [SW_032e] Forged - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - SHAMAN
    // [DED_522t] Cookie's Stirring Rod - COST:3
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("DED_522t", cardDef);
}

void StormwindCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- WEAPON - WARLOCK
    // [SW_003] Runed Mithril Rod - COST:5
    // - Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you draw 4 cards,
    //       reduce the Cost of cards in your hand by (1).
    //       Lose 1 Durability.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [SW_084] Bloodbound Imp - COST:2 [ATK:2/HP:5]
    // - Race: Demon, Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever this attacks, deal 2 damage to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SELF;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DamageTask>(
        EntityType::HERO, 2) };
    cards.emplace("SW_084", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [SW_085] Dark Alley Pact - COST:4
    // - Set: STORMWIND, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Summon a Fiend with stats equal to your hand size.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [SW_086] Shady Bartender - COST:5 [ATK:4/HP:4]
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Tradeable</b>
    //       <b>Battlecry:</b> Give your Demons +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TRADEABLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::DEMON)) }));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("SW_086e", EntityType::STACK));
    cards.emplace("SW_086", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [SW_087] Dreaded Mount - COST:3
    // - Set: STORMWIND, Rarity: Epic
    // --------------------------------------------------------
    // Text: Give a minion +1/+1.
    //       When it dies, summon an endless Dreadsteed.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [SW_088] Demonic Assault - COST:4
    // - Set: STORMWIND, Rarity: Common
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Deal 3 damage.
    //       Summon two 1/3 Voidwalkers with <b>Taunt</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("CS2_065", 2, SummonSide::SPELL));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("SW_088", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [SW_089] Entitled Customer - COST:6 [ATK:3/HP:2]
    // - Set: STORMWIND, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal damage equal to your
    //       hand size to all other minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [SW_090] Touch of the Nathrezim - COST:1
    // - Set: STORMWIND, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Deal 2 damage to a minion.
    //       If it dies, restore 3 Health to your hero.
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
                                SelfCondition::IsDead()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<HealTask>(EntityType::HERO, 3) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("SW_090", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [SW_091] The Demon Seed - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline:</b> Take 8 damage on your turns.
    //       <b>Reward:</b> <b>Lifesteal</b>.
    //       Deal 3 damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [SW_092] Anetheron - COST:6 [ATK:8/HP:6]
    // - Race: Demon, Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Costs (1) if your hand is full.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<AdaptiveCostEffect>(
        [](Playable* playable) { return 1; }, EffectOperator::SET,
        SelfCondition::IsHandFull()));
    cards.emplace("SW_092", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [DED_503] Shadowblade Slinger - COST:1 [ATK:2/HP:1]
    // - Race: Pirate, Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you've taken damage this turn,
    //       deal that much to an enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [DED_504] Wicked Shipment - COST:1
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Tradeable</b>
    //       Summon 2 1/1 Imps.
    //       <i>(Upgrades by 2 when <b>Traded</b>!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TRADEABLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [DED_505] Hullbreaker - COST:4 [ATK:4/HP:3]
    // - Race: Demon, Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry and Deathrattle:</b>
    //       Draw a spell.
    //       Your hero takes damage equal to its Cost.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
}

void StormwindCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - WARLOCK
    // [SW_085t] Fiend - COST:1 [ATK:1/HP:1]
    // - Race: Demon, Set: STORMWIND
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [SW_087t] Tamsin's Dreadsteed - COST:4 [ATK:1/HP:1]
    // - Race: Demon, Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> At the end of the turn,
    //       summon Tamsin's Dreadsteed.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [SW_091t] Establish the Link - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline:</b> Take 8 damage on your turns.
    //       <b>Reward:</b> <b>Lifesteal</b>.
    //       Deal 3 damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [SW_091t3] Complete the Ritual - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline:</b> Take 8 damage on your turns.
    //       <b>Reward:</b> Blightborn Tamsin.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [SW_091t4] Blightborn Tamsin - COST:5 [ATK:7/HP:7]
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> For the rest of the game,
    //       damage you take on your turn damages
    //       your opponent instead.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [DED_504t] Ship Imp - COST:1 [ATK:1/HP:1]
    // - Race: Demon, Set: STORMWIND
    // --------------------------------------------------------
}

void StormwindCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - WARRIOR
    // [SW_021] Cowardly Grunt - COST:6 [ATK:6/HP:2]
    // - Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a minion from your deck.
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(ComplexTask::SummonMinionFromDeck());
    cards.emplace("SW_021", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [SW_023] Provoke - COST:0
    // - Set: STORMWIND, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Tradeable</b>
    //       Choose a friendly minion.
    //       Enemy minions attack it.
    // --------------------------------------------------------
    // GameTag:
    // - TRADEABLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [SW_024] Lothar - COST:7 [ATK:7/HP:7]
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of your turn, attack a random enemy minion.
    //       If it dies, gain +3/+3.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [SW_027] Shiver Their Timbers! - COST:1
    // - Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 2 damage to a minion.
    //       If you control a Pirate, deal 5 instead.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsHoldingRace(Race::PIRATE)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 5, true) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        false,
        TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 2, true) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("SW_027", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [SW_028] Raid the Docks - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline:</b> Play 3 Pirates.
    //       <b>Reward:</b> Draw a weapon.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [SW_029] Harbor Scamp - COST:2 [ATK:2/HP:2]
    // - Race: Pirate, Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a Pirate.
    // --------------------------------------------------------
    // RefTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(ComplexTask::DrawCardFromDeck(
        1, SelfCondList{ std::make_shared<SelfCondition>(
               SelfCondition::IsRace(Race::PIRATE)) }));
    cards.emplace("SW_029", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [SW_030] Cargo Guard - COST:3 [ATK:2/HP:4]
    // - Race: Pirate, Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn, gain 3 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<ArmorTask>(3) };
    cards.emplace("SW_030", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [SW_093] Stormwind Freebooter - COST:3 [ATK:3/HP:4]
    // - Race: Pirate, Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your hero +2 Attack this turn.
    // --------------------------------------------------------
    // RefTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("SW_093e", EntityType::HERO));
    cards.emplace("SW_093", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [SW_094] Heavy Plate - COST:3
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Tradeable</b>
    //       Gain 8 Armor.
    // --------------------------------------------------------
    // RefTag:
    // - TRADEABLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ArmorTask>(8));
    cards.emplace("SW_094", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [SW_097] Remote-Controlled Golem - COST:4 [ATK:3/HP:6]
    // - Race: Mechanical, Set: STORMWIND, Rarity: Epic
    // --------------------------------------------------------
    // Text: After this takes damage,
    //       shuffle two Golem Parts into your deck.
    //       When drawn, summon a 2/1 Mech.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [DED_518] Man the Cannons - COST:2
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 3 damage to a minion and 1 damage to all other minions.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    cardDef.power.AddPowerTask(std::make_shared<DamageTask>(
        EntityType::ALL_MINIONS_NOTARGET, 1, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("DED_518", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [DED_519] Defias Cannoneer - COST:3 [ATK:3/HP:3]
    // - Race: Pirate, Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: After your hero attacks,
    //       deal 2 damage to a random enemy twice.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<EnqueueTask>(
        TaskList{ std::make_shared<RandomTask>(EntityType::ENEMIES, 1),
                  std::make_shared<DamageTask>(EntityType::STACK, 2) },
        2, false) };
    cards.emplace("DED_519", cardDef);

    // --------------------------------------- WEAPON - WARRIOR
    // [DED_527] Blacksmithing Hammer - COST:4
    // - Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Tradeable</b>
    //       After you <b>Trade</b> this, gain +2 Durability.
    // --------------------------------------------------------
    // GameTag:
    // - TRADEABLE = 1
    // --------------------------------------------------------
}

void StormwindCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- SPELL - WARRIOR
    // [SW_028t] Create a Distraction - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline:</b> Play 3 Pirates.
    //       <b>Reward:</b> Deal 2 damage
    //       to a random enemy twice.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [SW_028t2] Secure the Supplies - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline:</b> Play 3 Pirates.
    //       <b>Reward:</b> Cap'n Rokara.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [SW_028t5] Cap'n Rokara - COST:5 [ATK:7/HP:7]
    // - Race: Pirate, Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon The Juggernaut!
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [SW_028t6] The Juggernaut - COST:5 [ATK:0/HP:1]
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Start of Your Turn:</b> Summon a Pirate,
    //       equip a Warrior weapon, and fire two cannons
    //       that deal 2 damage!
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // - UNTOUCHABLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [SW_097t] Golem Parts - COST:1
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Casts When Drawn</b>
    //       Summon a 2/1 Damaged Golem.
    // --------------------------------------------------------
    // GameTag:
    // - TOPDECK = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [DED_527e] Blacksmithing - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: +2 Durability.
    // --------------------------------------------------------
}

void StormwindCardsGen::AddDemonHunter(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- MINION - DEMONHUNTER
    // [SW_037] Irebound Brute - COST:7 [ATK:6/HP:7]
    // - Race: Demon, Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       Costs (1) less for each card drawn this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<AdaptiveCostEffect>([](const Playable* playable) {
            return playable->player->GetNumCardsDrawnThisTurn();
        }));
    cards.emplace("SW_037", cardDef);

    // ------------------------------------ SPELL - DEMONHUNTER
    // [SW_039] Final Showdown - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline:</b> Draw 4 cards in one turn.
    //       <b>Reward:</b> Reduce the Cost of the cards drawn by (1).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [SW_040] Fel Barrage - COST:2
    // - Set: STORMWIND, Rarity: Common
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Deal 2 damage to the lowest Health enemy, twice.
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [SW_041] Sigil of Alacrity - COST:1
    // - Set: STORMWIND, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: At the start of your next turn,
    //       draw a card and reduce its Cost by (1).
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [SW_042] Persistent Peddler - COST:4 [ATK:4/HP:3]
    // - Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Tradeable</b>
    //       <b>Deathrattle:</b> Summon a Persistent Peddler
    //       from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - TRADEABLE = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [SW_043] Felgorger - COST:4 [ATK:4/HP:3]
    // - Race: Demon, Set: STORMWIND, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a Fel spell.
    //       Reduce its Cost by (2).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::DECK));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsFelSpell()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<RandomTask>(EntityType::STACK, 1));
    cardDef.power.AddPowerTask(std::make_shared<DrawStackTask>(true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("SW_043e", EntityType::STACK));
    cards.emplace("SW_043", cardDef);

    // ----------------------------------- MINION - DEMONHUNTER
    // [SW_044] Jace Darkweaver - COST:8 [ATK:7/HP:5]
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Cast all Fel spells you've played
    //       this game <i>(targets enemies if possible)</i>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [SW_451] Metamorfin - COST:1 [ATK:1/HP:2]
    // - Race: Murloc, Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> If you've cast a Fel spell
    //       this turn, gain +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::CastFelSpellInThisTurn()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "SW_451e", EntityType::SOURCE) }));
    cards.emplace("SW_451", cardDef);

    // ------------------------------------ SPELL - DEMONHUNTER
    // [SW_452] Chaos Leech - COST:3
    // - Set: STORMWIND, Rarity: Rare
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>. Deal 3 damage to a minion.
    //       <b>Outcast:</b> Deal 5 instead.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // - OUTCAST = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE,
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsLeftOrRightMostCardInHand()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 5, true) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        false,
        TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 3, true) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("SW_452", cardDef);

    // ----------------------------------- WEAPON - DEMONHUNTER
    // [SW_454] Lion's Frenzy - COST:3
    // - Set: STORMWIND, Rarity: Epic
    // --------------------------------------------------------
    // Text: Has Attack equal to the number of cards
    //       you've drawn this turn.
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [DED_506] Need for Greed - COST:5
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Tradeable</b>
    //       Draw 3 cards. If drawn this turn, this costs (3).
    // --------------------------------------------------------
    // GameTag:
    // - TRADEABLE = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [DED_507] Crow's Nest Lookout - COST:3 [ATK:2/HP:2]
    // - Race: Demon, Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 2 damage
    //       to the left and right-most enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [DED_508] Proving Grounds - COST:6
    // - Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon two minions from your deck.
    //       They fight!
    // --------------------------------------------------------
}

void StormwindCardsGen::AddDemonHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [SW_037e] Prepped to Strike - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [SW_039t] Gain Momentum - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline:</b> Draw 5 cards in one turn.
    //       <b>Reward:</b> Reduce the Cost of the cards drawn by (1).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [SW_039t2e] Faster Moves - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - ENCHANTMENT_INVISIBLE = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [SW_039t3] Close the Portal - COST:1
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Questline:</b> Draw 5 cards in one turn.
    //       <b>Reward:</b> Demonslayer Kurtrus.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [SW_039t3_t] Demonslayer Kurtrus - COST:5 [ATK:7/HP:7]
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> For the rest of the game,
    //       cards you draw cost (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    // RefTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [SW_041e2] Light as a Feather - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [SW_451e] Mighty Morphing - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("SW_451e"));
    cards.emplace("SW_451e", cardDef);
}

void StormwindCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [SW_006] Stubborn Suspect - COST:4 [ATK:3/HP:3]
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a random 3-Cost minion.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(std::make_shared<RandomMinionTask>(
        TagValues{ { GameTag::COST, 3, RelaSign::EQ } }));
    cardDef.power.AddDeathrattleTask(std::make_shared<SummonStackTask>());
    cards.emplace("SW_006", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [SW_036] Two-Faced Investor - COST:3 [ATK:2/HP:4]
    // - Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       reduce the Cost of a card in your hand by (1).
    //       <i>(50% chance to increase.)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SW_045] Auctioneer Jaxon - COST:2 [ATK:2/HP:3]
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever you <b>Trade</b>,
    //       <b>Discover</b> a card from your deck to draw instead.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // - TRADEABLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SW_054] Stormwind Guard - COST:5 [ATK:4/HP:5]
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Give adjacent minions +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeAdjacentTask>(EntityType::SOURCE));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("SW_054e", EntityType::STACK));
    cards.emplace("SW_054", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [SW_055] Impatient Shopkeep - COST:3 [ATK:3/HP:3]
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Tradeable</b>
    //       <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    // RefTag:
    // - TRADEABLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("SW_055", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [SW_056] Spice Bread Baker - COST:4 [ATK:3/HP:2]
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore Health to your hero
    //       equal to your hand size.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SW_057] Package Runner - COST:3 [ATK:5/HP:6]
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: Can only attack if you have at least 8 cards in hand.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SW_059] Deeprun Engineer - COST:2 [ATK:1/HP:2]
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a Mech.
    //       It costs (1) less.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SW_060] Florist - COST:2 [ATK:2/HP:3]
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: At then end of your turn,
    //       reduce the cost of a Nature spell in your hand by (1).
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SW_061] Guild Trader - COST:4 [ATK:3/HP:4]
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Tradeable</b>
    //       <b>Spell Damage +2</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // - TRADEABLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("SW_061", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [SW_062] Goldshire Gnoll - COST:10 [ATK:5/HP:4]
    // - Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       Costs (1) less for each other card in your hand.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SW_063] Battleground Battlemaster - COST:6 [ATK:5/HP:5]
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: Adjacent minions have <b>Windfury</b>.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - WINDFURY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<AdjacentAura>("SW_063e"));
    cards.emplace("SW_063", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [SW_064] Northshire Farmer - COST:3 [ATK:3/HP:3]
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a friendly Beast.
    //       Shuffle three 3/3 copies into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SW_065] Pandaren Importer - COST:2 [ATK:1/HP:3]
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a spell
    //       that didn't start in your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SW_066] Royal Librarian - COST:4 [ATK:3/HP:4]
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Tradeable</b>
    //       <b>Battlecry:</b> <b>Silence</b> a minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TRADEABLE = 1
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
    cards.emplace("SW_066", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [SW_067] Stockades Guard - COST:1 [ATK:1/HP:3]
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SetGameTagTask>(
        EntityType::TARGET, GameTag::TAUNT, 1));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cards.emplace("SW_067", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [SW_068] Mo'arg Forgefiend - COST:8 [ATK:8/HP:8]
    // - Race: Demon, Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Gain 8 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(std::make_shared<ArmorTask>(8));
    cards.emplace("SW_068", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [SW_069] Enthusiastic Banker - COST:3 [ATK:2/HP:3]
    // - Set: STORMWIND, Rarity: Epic
    // --------------------------------------------------------
    // Text: At the end of your turn, store a card from your deck.
    //       <b>Deathrattle:</b> Add the stored cards to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SW_070] Mailbox Dancer - COST:2 [ATK:3/HP:2]
    // - Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a Coin to your hand.
    //       <b>Deathrattle:</b> Give your opponent one.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "GAME_005", 1));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddCardTask>(EntityType::ENEMY_HAND, "GAME_005", 1));
    cards.emplace("SW_070", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [SW_071] Lion's Guard - COST:5 [ATK:4/HP:6]
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you have 15 or less Health,
    //       gain +2/+4 and <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::HERO, SelfCondList{ std::make_shared<SelfCondition>(
                              SelfCondition::IsHealth(15, RelaSign::LEQ)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "SW_071e", EntityType::SOURCE) }));
    cards.emplace("SW_071", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [SW_072] Rustrot Viper - COST:3 [ATK:3/HP:4]
    // - Race: Beast, Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Tradeable</b>
    //       <b>Battlecry:</b> Destroy your opponent's weapon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TRADEABLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::ENEMY_WEAPON));
    cards.emplace("SW_072", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [SW_073] Cheesemonger - COST:4 [ATK:3/HP:6]
    // - Set: STORMWIND, Rarity: Epic
    // --------------------------------------------------------
    // Text: Whenever your opponent casts a spell,
    //       add a random spell with the same Cost to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SW_074] Nobleman - COST:3 [ATK:2/HP:3]
    // - Set: STORMWIND, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Create a Golden copy of
    //       a random card in your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SW_075] Elwynn Boar - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: STORMWIND, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> If you had 7 Elwynn Boars
    //       die this game, equip a 15/3 Sword of
    //       a Thousand Truths.@ <i>(@/7)</i>
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SW_076] City Architect - COST:6 [ATK:4/HP:4]
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two 0/5 Castle Walls
    //       with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("SW_076t", SummonSide::LEFT));
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("SW_076t", SummonSide::RIGHT));
    cards.emplace("SW_076", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [SW_077] Stockades Prisoner - COST:2 [ATK:5/HP:4]
    // - Set: STORMWIND, Rarity: Epic
    // --------------------------------------------------------
    // Text: Starts <b>Dormant</b>.
    //       After you play 3 cards, this awakens.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SW_078] Lady Prestor - COST:6 [ATK:6/HP:7]
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Transform minions
    //       in your deck into random Dragons.
    //       <i>(They keep their original stats and Cost.)</I>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SW_079] Flightmaster Dungar - COST:3 [ATK:3/HP:3]
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a flightpath and go <b>Dormant.</b>
    //       Awaken with a bonus when you complete it!
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SW_080] Cornelius Roame - COST:6 [ATK:4/HP:5]
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the start and end of each player's turn,
    //       draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    const auto trigger1 = std::make_shared<Trigger>(TriggerType::TURN_START);
    trigger1->eitherTurn = true;
    trigger1->tasks = { std::make_shared<DrawTask>(1) };
    const auto trigger2 = std::make_shared<Trigger>(TriggerType::TURN_END);
    trigger2->eitherTurn = true;
    trigger2->tasks = { std::make_shared<DrawTask>(1) };
    cardDef.power.AddTrigger(std::make_shared<MultiTrigger>(
        std::vector<std::shared_ptr<Trigger>>{ trigger1, trigger2 }));
    cards.emplace("SW_080", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [SW_081] Varian, King of Stormwind - COST:8 [ATK:7/HP:7]
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a <b>Rush</b> minion
    //       to gain <b>Rush</b>.
    //       Repeat for <b>Taunt</b> and <b>Divine Shield</b>.
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
    // [SW_306] Encumbered Pack Mule - COST:2 [ATK:2/HP:3]
    // - Race: Beast, Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       When you draw this, add a copy of it to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - TOPDECK = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SW_307] Traveling Merchant - COST:3 [ATK:2/HP:3]
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Tradeable</b>
    //       <b>Battlecry:</b> Gain +1/+1 for each other
    //       friendly minion you control.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TRADEABLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SW_319] Peasant - COST:1 [ATK:2/HP:1]
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: At the start of your turn, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SW_400] Entrapped Sorceress - COST:3 [ATK:3/HP:4]
    // - Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a <b>Quest</b>,
    //       <b>Discover</b> a spell.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------
    // RefTag:
    // - QUEST = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SW_418] SI:7 Skulker - COST:2 [ATK:2/HP:2]
    // - Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //       <b>Battlecry:</b> The next card you draw costs (1) less.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - STEALTH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DED_006] Mr. Smite - COST:7 [ATK:6/HP:5]
    // - Race: Pirate, Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Your Pirates have <b>Charge</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DED_521] Maddest Bomber - COST:8 [ATK:9/HP:8]
    // - Set: STORMWIND, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 12 damage randomly split
    //       among all other characters.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DED_523] Golakka Glutton - COST:3 [ATK:2/HP:3]
    // - Race: Pirate, Set: STORMWIND, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a Beast and gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DED_524] Multicaster - COST:4 [ATK:3/HP:4]
    // - Race: Pirate, Set: STORMWIND, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a card for
    //       each different spell school you've cast this game.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [DED_525] Goliath, Sneed's Masterpiece - COST:8 [ATK:8/HP:8]
    // - Race: Mechanical, Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Fire five rockets
    //       at enemy minions that deal
    //       2 damage each. <i>(You pick
    //       the targets!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void StormwindCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_001e] Inscription Enchant - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Your next spell costs (5) less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_001e2] Inscription Discount - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Costs (5) less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_003e] Enchanting Dust - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_024e] FOR STORMWIND! - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: +3/+3.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_034e] Tiny Toy - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: 2/2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_036e] Good Investment - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Costs (1)  less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_036e2] Bad Investment - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Costs (1)  more.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_039t3_te] Ludicrous Speed - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_039te] Fast Moves - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_043e] Gorging - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_unique<Enchant>(Effects::ReduceCost(2)));
    cards.emplace("SW_043e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_047e] Highlord's Blessing - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: +5/+5.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_048e] Faceted Dawnstone - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_050e] Disguise - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Appearing as someone else.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_054e] For the Alliance! - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("SW_054e"));
    cards.emplace("SW_054e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_060t] Pretty Flowers - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_063e] Ready for Battle! - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Windfury</b>
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("SW_063e"));
    cards.emplace("SW_063e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_064e] Raised in a Barn - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: 3/3.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_069e] Safety Deposit - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Storing {0}.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_071e] Defend the King! - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: +2/+4 and <b>Taunt</b>
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("SW_071e"));
    cards.emplace("SW_071e", cardDef);

    // --------------------------------------- WEAPON - NEUTRAL
    // [SW_075t] Sword of a Thousand Truths - COST:10
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: After your hero attacks,
    //       destroy your opponent's Mana Crystals.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [SW_076t] Castle Wall - COST:2 [ATK:0/HP:5]
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("SW_076t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_077e] Locked Up - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Dormant</b>. Play 3 cards to awaken.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_078e] Dragon Form - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Adjusted stats.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_078e2] Dragon Cost - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Adjusted Cost.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_079e4] Westfall Flight - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Dormant</b>. Summon a 2/2 Adventurer in 1 turn.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_079e5] Ironforge Flight - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Dormant</b>.
    //       Restore 10 health to your hero in 3 turns.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_079e6] Plaguelands Flight - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Dormant</b>. Deal 12 damage randomly split
    //       to enemies in 5 turns.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [SW_079t] Westfall - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: In 1 turn, summon a 2/2 Adventurer with
    //       a random bonus effect.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [SW_079t2] Ironforge - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: In 3 turns, restore 10 Health to your hero.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_079t2e] Ironforge Flight - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: In 3 turns, restore 10 Health to your hero.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [SW_079t3] Eastern Plaguelands - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: In 5 turns, deal 12 damage randomly split among enemies.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_079t3e] Plaguelands Flight - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: In 5 turns, deal 12 damage randomly split among enemies.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_079te] Westfall Flight - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Next turn, summon a 2/2 Adventurer.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_086e] Souls on Tap - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("SW_086e"));
    cards.emplace("SW_086e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_087e] On a Dreadsteed - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: +1/+1.
    //       <b>Deathrattle:</b> Summon a never-ending Dreadsteed.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_087e2] Tamsin's Dreadsteed - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Summon a Dreadsteed at the end of the turn.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_091t5] Blightborn - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: For the rest of the game, damage you take
    //       on your turn instead damages your opponent.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_093e] Paid to Loot - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("SW_093e"));
    cards.emplace("SW_093e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_307e] Booming Business - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_313t4ee] Light's Power - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_315e] Stormwind Pride - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("SW_315e"));
    cards.emplace("SW_315e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_316e] On a Horse - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: +1/+1 and <b>Divine Shield</b>.
    //       <b>Deathrattle:</b> Summon a Warhorse.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("SW_316e"));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("SW_316t", SummonSide::DEATHRATTLE));
    cards.emplace("SW_316e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_322e] Practiced - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_322e2] Tavish Stormpike Enchant - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> For the rest of the game,
    //       your spells refresh your Hero Power.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_322e3] Crackshot - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Your Hero Power Can Target Minions
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_418e] Secret Intel - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_418e2] Spy Stuff - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: The next card you draw costs (1) less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_437e] Fertilizer - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Draw a card.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(std::make_shared<DrawTask>(1));
    cards.emplace("SW_437e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_457e] Reinforced Hide - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [SW_COIN1] The Coin - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Gain 1 Mana Crystal this turn only.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [SW_COIN2] The Coin - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Gain 1 Mana Crystal this turn only.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DED_006e2] Charge - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: {0} grants <b>Charge</b>.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DED_514e] Copycat - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Add a copy of the next card your opponent plays
    //       to your hand.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [DED_523e] Stuffed Belly - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
}

void StormwindCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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