// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/TheSunkenCityCardsGen.hpp>
#include <Rosetta/PlayMode/Cards/CardPowers.hpp>

namespace RosettaStone::PlayMode
{
void TheSunkenCityCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TheSunkenCityCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TheSunkenCityCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - DRUID
    // [TSC_026] Colaque - COST:7 [ATK:6/HP:5]
    // - Race: Beast, Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Colossal +1</b>
    //       <b>Immune</b> while you control Colaque's Shell.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - COLOSSAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<AdaptiveEffect>(
        std::make_shared<SelfCondition>(
            SelfCondition::IsControllingColaqueShell()),
        GameTag::IMMUNE));
    cardDef.property.appendages = { { "TSC_026t", SummonSide::RIGHT } };
    cards.emplace("TSC_026", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [TSC_650] Flipper Friends - COST:5
    // - Set: THE_SUNKEN_CITY, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: <b>Choose One</b> -
    //       Summon a 6/6 Orca with <b>Taunt</b>;
    //       or six 1/1 Otters with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.chooseCardIDs = ChooseCardIDs{ "TSC_650a", "TSC_650d" };
    cards.emplace("TSC_650", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [TSC_651] Seaweed Strike - COST:3
    // - Set: THE_SUNKEN_CITY, Rarity: Epic
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Deal 4 damage to a minion.
    //       If you played a Naga while holding this,
    //       also give your hero +4 Attack this turn.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [TSC_652] Green-Thumb Gardener - COST:6 [ATK:5/HP:5]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Refresh empty Mana Crystals
    //       equal to the Cost of the most expensive spell
    //       in your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [TSC_653] Bottomfeeder - COST:1 [ATK:1/HP:3]
    // - Race: Beast, Set: THE_SUNKEN_CITY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a Bottomfeeder to
    //       the bottom of your deck with permanent +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [TSC_654] Aquatic Form - COST:0
    // - Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Dredge</b>.
    //       If you have the Mana to play the card this turn,
    //       draw it.
    // --------------------------------------------------------
    // GameTag:
    // - DREDGE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [TSC_656] Miracle Growth - COST:8
    // - Set: THE_SUNKEN_CITY, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Draw 3 cards.
    //       Summon a Plant with <b>Taunt</b> and
    //       stats equal to your hand size.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [TSC_657] Dozing Kelpkeeper - COST:1 [ATK:4/HP:4]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b>. Starts <b>Dormant</b>.
    //       After you've cast 5 Mana worth of spells, awaken.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [TSC_658] Hedra the Heretic - COST:7 [ATK:4/HP:5]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b>
    //       For each spell you've cast while holding this,
    //       summon a minion of that spell's Cost.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [TSC_927] Azsharan Gardens - COST:1
    // - Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: Give all minions in your hand +1/+1.
    //       Put a 'Sunken Gardens' on the bottom of your deck.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [TID_000] Spirit of the Tides - COST:2 [ATK:2/HP:2]
    // - Race: Elemental, Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: If you have any unspent Mana at the end
    //       of your turn, gain +1/+2.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [TID_001] Moonbeam - COST:1
    // - Set: THE_SUNKEN_CITY, Rarity: Common
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Deal 1 damage to an enemy, twice.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [TID_002] Herald of Nature - COST:3 [ATK:3/HP:3]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b>
    //       If you've cast a Nature spell while holding this,
    //       give your other minions +1/+2.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void TheSunkenCityCardsGen::AddDruidNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - DRUID
    // [TSC_026t] Colaque's Shell - COST:5 [ATK:0/HP:8]
    // - Race: Beast, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Gain 8 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(std::make_shared<ArmorTask>(8));
    cards.emplace("TSC_026t", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [TSC_650a] Order the Orca - COST:5
    // - Set: THE_SUNKEN_CITY
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Summon a 6/6 Orca with <b>Taunt</b>.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("TSC_650t", SummonSide::SPELL));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("TSC_650a", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [TSC_650d] Romp of Otters - COST:5
    // - Set: THE_SUNKEN_CITY
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Summon six 1/1 Otters with <b>Rush</b>.
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("TSC_650t4", 6, SummonSide::SPELL));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("TSC_650d", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [TSC_650t] Orca - COST:6 [ATK:6/HP:6]
    // - Race: Beast, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("TSC_650t", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [TSC_650t4] Otter - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("TSC_650t4", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [TSC_651e] Explosive - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: +4 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [TSC_656t] Kelp Creeper - COST:1 [ATK:1/HP:1]
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [TSC_657e] Aquatic Slumber - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Dormant</b>.
    //       Awaken after you cast 5 Mana worth of spells.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [TSC_927e] Watered - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [TSC_927t] Sunken Gardens - COST:1
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Give +1/+1 to all minions in your hand, deck,
    //       and battlefield.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [TID_000e] Endless Sea - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: +1/+2.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [TID_002e] Nature's Bounty - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: +1/+2.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [TID_078e] In Shambles - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Your next <b>Deathrattle</b> card costs (1) less.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [TID_078e2] Shambled - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------
}

void TheSunkenCityCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- SPELL - HUNTER
    // [TSC_023] Barbed Nets - COST:1
    // - Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 2 damage to an enemy.
    //       If you played a Naga while holding this,
    //       choose a second target.
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - HUNTER
    // [TSC_070] Harpoon Gun - COST:3
    // - Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: After your hero attacks, <b>Dredge</b>.
    //       If it's a Beast, reduce its Cost by (2).
    // --------------------------------------------------------
    // GameTag:
    // - DREDGE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [TSC_071] Twinbow Terrorcoil - COST:4 [ATK:4/HP:4]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b>
    //       If you've cast a spell while holding this,
    //       your next spell casts twice.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [TSC_072] Conch's Call - COST:3
    // - Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: Draw a Naga and a spell.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(ComplexTask::DrawCardFromDeck(
        1, SelfCondList{ std::make_shared<SelfCondition>(
               SelfCondition::IsRace(Race::NAGA)) }));
    cardDef.power.AddPowerTask(std::make_shared<DrawSpellTask>(1));
    cards.emplace("TSC_072", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [TSC_073] Raj Naz'jan - COST:2 [ATK:2/HP:3]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you cast a spell,
    //       deal damage equal to its Cost to the enemy Hero.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [TSC_929] Emergency Maneuvers - COST:2
    // - Set: THE_SUNKEN_CITY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Secret:</b>
    //       When a friendly minion dies, summon a copy of it.
    //       It's <b>Dormant</b> for 1 turn.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [TSC_945] Azsharan Saber - COST:4 [ATK:4/HP:3]
    // - Race: Beast, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b><b>Rush</b>.</b> <b>Deathrattle:</b>
    //       Put a 'Sunken Saber' on the bottom of your deck.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [TSC_946] Urchin Spines - COST:1
    // - Set: THE_SUNKEN_CITY, Rarity: Epic
    // --------------------------------------------------------
    // Text: Your spells this turn are <b>Poisonous</b>.
    // --------------------------------------------------------
    // RefTag:
    // - POISONOUS = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [TSC_947] Naga's Pride - COST:3
    // - Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon two 2/2 Lionfish.
    //       If you played a Naga while holding this,
    //       give them +1/+1.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("TSC_947t", 2, SummonSide::SPELL, true));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE,
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsTagValue(GameTag::TAG_SCRIPT_DATA_NUM_1, 1)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "TSC_947e", EntityType::STACK) }));
    ComplexTrigger::PlayedNagaWhileHoldingThis(cardDef.power);
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("TSC_947", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [TSC_950] Hydralodon - COST:7 [ATK:5/HP:5]
    // - Race: Beast, Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Colossal +2</b>
    //       <b>Battlecry:</b> Give your Hydralodon Heads <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - COLOSSAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [TID_074] Ancient Krakenbane - COST:3 [ATK:3/HP:3]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b>
    //       If you've cast three spells while holding this,
    //       deal 5 damage.
    //       <i>({0} left!)</i> <i>(Ready!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [TID_075] Shellshot - COST:3
    // - Set: THE_SUNKEN_CITY, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Deal 3 damage to a random enemy minion.
    //       Repeat this with 1 less damage.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [TID_099] K9-0tron - COST:2 [ATK:2/HP:3]
    // - Race: Mechanical, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Dredge</b>.
    //       If it's a 1-Cost minion, summon it.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DREDGE = 1
    // --------------------------------------------------------
}

void TheSunkenCityCardsGen::AddHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [TSC_071e] Twinned - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Your next spell casts twice.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [TSC_071e2] Twinning - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Your next spell casts twice.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [TSC_929t] Improved Emergency Maneuvers - COST:2
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Secret:</b>
    //       When a friendly minion dies, summon two copies of it.
    //       They're <b>Dormant</b> for 1 turn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - SECRET = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [TSC_945t] Sunken Saber - COST:4 [ATK:4/HP:3]
    // - Race: Beast, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b><b>Rush</b>.</b> <b>Deathrattle:</b>
    //       Summon a Beast from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [TSC_946e] Poisonous Urchin - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Your spells are <b>Poisonous</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - POISONOUS = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [TSC_946e2] Poisonous - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [TSC_947e] Well-fed Fish - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("TSC_947e"));
    cards.emplace("TSC_947e", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [TSC_947t] Lionfish - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("TSC_947t", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [TSC_950t] Hydralodon Head - COST:2 [ATK:3/HP:1]
    // - Race: Beast, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> If you control Hydralodon,
    //       summon 2 Hydralodon Heads.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [TSC_950t2] Hydralodon Head - COST:2 [ATK:3/HP:1]
    // - Race: Beast, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> If you control Hydralodon,
    //       summon 2 Hydralodon Heads.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
}

void TheSunkenCityCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ MINION - MAGE
    // [TSC_029] Gaia, the Techtonic - COST:8 [ATK:5/HP:7]
    // - Race: Mechanical, Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Colossal +2</b>
    //       After a friendly Mech attacks,
    //       deal 1 damage to all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - COLOSSAL = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::MINIONS;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::MECHANICAL))
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DamageTask>(
        EntityType::ENEMIES, 1) };
    cardDef.property.appendages = { { "TSC_029t", SummonSide::LEFT },
                                    { "TSC_029t2", SummonSide::RIGHT } };
    cards.emplace("TSC_029", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [TSC_054] Mecha-Shark - COST:3 [ATK:4/HP:3]
    // - Race: Mechanical, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: After you summon a Mech,
    //       deal 3 damage randomly split among all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_SUMMON));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::MECHANICAL))
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<EnqueueTask>(
        TaskList{
            std::make_shared<FilterStackTask>(SelfCondList{
                std::make_shared<SelfCondition>(SelfCondition::IsNotDead()) }),
            std::make_shared<RandomTask>(EntityType::ENEMIES, 1),
            std::make_shared<DamageTask>(EntityType::STACK, 1) },
        3) };
    cards.emplace("TSC_054", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [TSC_055] Seafloor Gateway - COST:3
    // - Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Draw a Mech.
    //       Reduce the Cost of Mechs in your hand by (1).
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DrawRaceMinionTask>(Race::MECHANICAL, 1, false));
    cardDef.power.AddPowerTask(std::make_shared<IncludeTask>(EntityType::HAND));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsRace(Race::MECHANICAL)) }));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("TSC_055e", EntityType::STACK));
    cards.emplace("TSC_055", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [TSC_056] Volcanomancy - COST:2
    // - Set: THE_SUNKEN_CITY, Rarity: Epic
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Choose a minion.
    //       When it dies, deal 3 damage to all other minions.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [TSC_087] Commander Sivara - COST:4 [ATK:3/HP:5]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b>
    //       If you've cast three spells while holding this,
    //       add those spells back to your hand.
    //       <i>({0} left!)</i> <i>(Ready!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [TSC_620] Spitelash Siren - COST:5 [ATK:2/HP:6]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Epic
    // --------------------------------------------------------
    // Text: After you play a Naga,
    //       refresh two Mana Crystals.
    //       <i>(Then switch to spell!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [TSC_642] Trench Surveyor - COST:2 [ATK:3/HP:2]
    // - Race: Mechanical, Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Dredge</b>.
    //       If it's a Mech, draw it.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DREDGE = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [TSC_643] Spellcoiler - COST:2 [ATK:2/HP:3]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b>
    //       If you've cast a spell while holding this,
    //       <b>Discover</b> a spell.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [TSC_776] Azsharan Sweeper - COST:3 [ATK:3/HP:4]
    // - Race: Mechanical, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b>
    //       Put a 'Sunken Sweeper' on the bottom of your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<PutCardDeckTask>("TSC_776t", DeckPosition::BOTTOM));
    cards.emplace("TSC_776", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [TSC_948] Gifts of Azshara - COST:2
    // - Set: THE_SUNKEN_CITY, Rarity: Rare
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Draw a card.
    //       If you played a Naga while holding this, do it again.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [TID_707] Submerged Spacerock - COST:2 [ATK:2/HP:2]
    // - Race: Elemental, Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b>
    //       Add two Arcane Mage spells to your hand.
    //       At the end of your turn, discard them.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [TID_708] Polymorph: Jellyfish - COST:3
    // - Set: THE_SUNKEN_CITY, Rarity: Common
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Transform a minion into a 4/1 Jellyfish
    //       with <b>Spell Damage +2</b>.
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [TID_709] Lady Naz'jar - COST:5 [ATK:5/HP:5]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: While in your hand, this transforms after you cast
    //       a Fire, Frost, or Arcane spell.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
}

void TheSunkenCityCardsGen::AddMageNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ MINION - MAGE
    // [TSC_029t] Gaia's Drill - COST:3 [ATK:2/HP:3]
    // - Race: Mechanical, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("TSC_029t", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [TSC_029t2] Gaia's Drill - COST:3 [ATK:2/HP:3]
    // - Race: Mechanical, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("TSC_029t2", cardDef);

    // ------------------------------------- ENCHANTMENT - MAGE
    // [TSC_055e] Mechanical Marvel - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::ReduceCost(1)));
    cards.emplace("TSC_055e", cardDef);

    // ------------------------------------- ENCHANTMENT - MAGE
    // [TSC_056e] Explosive - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: When this dies, deal 3 damage to all other minions.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [TSC_776t] Sunken Sweeper - COST:3 [ATK:3/HP:4]
    // - Race: Mechanical, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add 3 random Mechs to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{ std::make_shared<RandomCardTask>(
                      CardType::MINION, CardClass::INVALID, Race::MECHANICAL),
                  std::make_shared<AddStackToTask>(EntityType::HAND) },
        3));
    cards.emplace("TSC_776t", cardDef);

    // ------------------------------------- ENCHANTMENT - MAGE
    // [TID_707e] Submerged - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Discards at the end of your turn.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [TID_708t] Jellyfish - COST:3 [ATK:4/HP:1]
    // - Race: Beast, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Spell Damage +2</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // ------------------------------------- ENCHANTMENT - MAGE
    // [TID_709e] Naz'jar's Gift - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [TID_709t] Lady Naz'jar - COST:5 [ATK:5/HP:5]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Reduce the Cost of spells
    //       in your hand by (1).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [TID_709t2] Lady Naz'jar - COST:5 [ATK:5/HP:5]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 5 damage to an enemy minion
    //       and 2 to adjacent minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [TID_709t3] Lady Naz'jar - COST:5 [ATK:5/HP:5]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain 8 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void TheSunkenCityCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - PALADIN
    // [TSC_030] The Leviathan - COST:7 [ATK:4/HP:5]
    // - Race: Mechanical, Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Colossal +1</b>
    //       <b>Rush</b>, <b>Divine Shield</b>
    //       After this attacks, <b>Dredge</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - COLOSSAL = 1
    // - DIVINE_SHIELD = 1
    // - DREDGE = 1
    // - RUSH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SELF;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DredgeTask>() };
    cardDef.property.appendages = { { "TSC_030t2", SummonSide::RIGHT } };
    cards.emplace("TSC_030", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [TSC_059] Bubblebot - COST:4 [ATK:4/HP:4]
    // - Race: Mechanical, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your other Mechs
    //       <b>Divine Shield</b> and <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [TSC_060] Shimmering Sunfish - COST:3 [ATK:2/HP:5]
    // - Race: Beast, Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Holy Spell,
    //       gain <b>Taunt</b> and <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [TSC_061] The Garden's Grace - COST:10
    // - Set: THE_SUNKEN_CITY, Rarity: Epic
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Give a minion +5/+5 and <b>Divine Shield</b>.
    //       Costs (1) less for each Mana you've spent
    //       on Holy spells this game.
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [TSC_074] Kotori Lightblade - COST:2 [ATK:2/HP:3]
    // - Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you cast a Holy spell on this,
    //       cast it again on another friendly minion.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [TSC_076] Immortalized in Stone - COST:7
    // - Set: THE_SUNKEN_CITY, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Summon a 1/2, 2/4 and 4/8 Elemental with <b>Taunt</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("TSC_076t", SummonSide::SPELL));
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("TSC_076t2", SummonSide::SPELL));
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("TSC_076t3", SummonSide::SPELL));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("TSC_076", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [TSC_079] Radar Detector - COST:2
    // - Set: THE_SUNKEN_CITY, Rarity: Epic
    // --------------------------------------------------------
    // Text: Scan the bottom 5 cards of your deck.
    //       Draw any Mechs found this way, then shuffle your deck.
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [TSC_083] Seafloor Savior - COST:2 [ATK:2/HP:2]
    // - Race: Mechanical, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Dredge</b>.
    //       If it's a minion,
    //       give it this minion's Attack and Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DREDGE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [TSC_644] Azsharan Mooncatcher - COST:3 [ATK:4/HP:2]
    // - Race: Mechanical, Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>. <b>Battlecry:</b>
    //       Put a 'Sunken Mooncatcher' on the bottom of your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [TSC_952] Holy Maki Roll - COST:1
    // - Set: THE_SUNKEN_CITY, Rarity: Rare
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Restore 2 Health. Repeatable this turn.
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [TID_077] Lightray - COST:9 [ATK:5/HP:5]
    // - Race: Elemental, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       Costs (1) less for each Paladin card
    //       you've played this game.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [TID_098] Myrmidon - COST:3 [ATK:3/HP:4]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: After you cast a spell on this minion, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [TID_949] Front Lines - COST:9
    // - Set: THE_SUNKEN_CITY, Rarity: Epic
    // --------------------------------------------------------
    // Text: Summon a minion from each player's deck.
    //       Repeat until either side of the battlefield is full.
    // --------------------------------------------------------
}

void TheSunkenCityCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - PALADIN
    // [TSC_030t2] The Leviathan's Claw - COST:3 [ATK:4/HP:2]
    // - Race: Mechanical, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Rush</b>, <b>Divine Shield</b>
    //       After this attacks, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DIVINE_SHIELD = 1
    // - RUSH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SELF;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DrawTask>(1) };
    cards.emplace("TSC_030t2", cardDef);

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [TSC_032e3] Blade Counter - COST:0
    // - Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: This <b>Counters</b> the next <b>Secretly</b>
    //       chosen minion or spell your opponent plays.
    // --------------------------------------------------------
    // GameTag:
    // - COUNTER = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [TSC_061e] Graced - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: +5/+5 and <b>Divine Shield</b>.
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [TSC_076t] Worn Statue - COST:1 [ATK:1/HP:2]
    // - Race: Elemental, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("TSC_076t", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [TSC_076t2] Living Statue - COST:3 [ATK:2/HP:4]
    // - Race: Elemental, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("TSC_076t2", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [TSC_076t3] Pristine Statue - COST:5 [ATK:4/HP:8]
    // - Race: Elemental, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("TSC_076t3", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [TSC_644t] Sunken Mooncatcher - COST:3 [ATK:4/HP:2]
    // - Race: Mechanical, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>.
    //       <b>Battlecry:</b> Summon a copy of this.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [TSC_928e] Overclocked - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
}

void TheSunkenCityCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- SPELL - PRIEST
    // [TSC_209] Whirlpool - COST:8
    // - Set: THE_SUNKEN_CITY, Rarity: Epic
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Destroy all minions and all copies of them
    //       <i>(wherever they are)</i>.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [TSC_210] Illuminate - COST:0
    // - Set: THE_SUNKEN_CITY, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: <b>Dredge</b>.
    //       If it's a spell, reduce its Cost by (3).
    // --------------------------------------------------------
    // GameTag:
    // - DREDGE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [TSC_211] Whispers of the Deep - COST:1
    // - Set: THE_SUNKEN_CITY, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: <b>Silence</b> a friendly minion,
    //       then deal damage equal to its Attack randomly split
    //       among all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------
    // RefTag:
    // - SILENCE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [TSC_212] Handmaiden - COST:3 [ATK:3/HP:2]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b>
    //       If you've cast three spells while holding this,
    //       draw 3 cards. <i>({0} left!)</i> <i>(Ready!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [TSC_213] Queensguard - COST:2 [ATK:2/HP:3]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b>
    //       Gain +1/+1 for each spell you've cast this turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [TSC_215] Serpent Wig - COST:1
    // - Set: THE_SUNKEN_CITY, Rarity: Epic
    // --------------------------------------------------------
    // Text: Give a minion +1/+2.
    //       If you played a Naga while holding this,
    //       add a Serpent Wig to your hand.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [TSC_216] Blackwater Behemoth - COST:7 [ATK:8/HP:10]
    // - Race: Beast, Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Colossal +1</b>
    //       <b>Lifesteal</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - COLOSSAL = 1
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [TSC_702] Switcheroo - COST:3
    // - Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: Draw 2 minions. Swap their Health.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [TSC_775] Azsharan Ritual - COST:4
    // - Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Silence</b> a minion and summon a copy of it.
    //       Put a 'Sunken Ritual' on the bottom of your deck.
    // --------------------------------------------------------
    // GameTag:
    // - SILENCE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [TSC_828] Priestess Valishj - COST:0 [ATK:1/HP:1]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Refresh an empty Mana Crystal
    //       for each spell you've cast this turn. <i>(@)</i>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [TID_085] Herald of Light - COST:3 [ATK:3/HP:4]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b>
    //       If you've cast a Holy spell while holding this,
    //       restore 6 Health to all friendly characters.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [TID_700] Disarming Elemental - COST:4 [ATK:4/HP:4]
    // - Race: Elemental, Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Dredge</b> for your opponent.
    //       Set its Cost to (6).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DREDGE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [TID_920] Drown - COST:4
    // - Set: THE_SUNKEN_CITY, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Put an enemy minion on the bottom of your deck.
    // --------------------------------------------------------
}

void TheSunkenCityCardsGen::AddPriestNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- ENCHANTMENT - PRIEST
    // [TSC_213e] Tides Call - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [TSC_215e] Snakes for Hair - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [TSC_216t] Behemoth's Lure - COST:2 [ATK:1/HP:4]
    // - Race: Beast, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       force a random enemy minion
    //       to attack the Blackwater Behemoth.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [TSC_702e] Switcheroo'd - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Swapped stats.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [TSC_775t] Sunken Ritual - COST:4
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Silence</b> a minion and summon 2 copies of it.
    // --------------------------------------------------------
    // GameTag:
    // - SILENCE = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [TID_700e] Disarmed - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Costs (6).
    // --------------------------------------------------------
}

void TheSunkenCityCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - ROGUE
    // [TSC_085] Cutlass Courier - COST:3 [ATK:2/HP:5]
    // - Race: Pirate, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: After your hero attacks, draw a Pirate.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- WEAPON - ROGUE
    // [TSC_086] Swordfish - COST:3
    // - Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Dredge</b>.
    //       If it's a Pirate,
    //       give this weapon and the Pirate +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DREDGE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [TSC_912] Azsharan Vessel - COST:5
    // - Set: THE_SUNKEN_CITY, Rarity: Epic
    // --------------------------------------------------------
    // Text: Summon two 3/3 Pirates with <b>Stealth</b>.
    //       Put a 'Sunken Vessel' on the bottom of your deck.
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [TSC_916] Gone Fishin' - COST:1
    // - Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Dredge</b>.
    //       <b>Combo:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // - DREDGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DredgeTask>());
    cardDef.power.AddComboTask(std::make_shared<DredgeTask>());
    cardDef.power.AddAfterChooseForComboTask(std::make_shared<DrawTask>(1));
    cards.emplace("TSC_916", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [TSC_932] Blood in the Water - COST:6
    // - Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 3 damage to an enemy.
    //       Summon a 5/5 Shark with <b>Rush</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_ENEMY_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("TSC_932t", SummonSide::SPELL));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_ENEMY_TARGET, 0 },
                                          { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("TSC_932", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [TSC_933] Bootstrap Sunkeneer - COST:5 [ATK:4/HP:4]
    // - Race: Pirate, Set: THE_SUNKEN_CITY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Put an enemy minion
    //       on the bottom of your opponent's deck.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [TSC_934] Pirate Admiral Hooktusk - COST:8 [ATK:8/HP:8]
    // - Race: Pirate, Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b>
    //       If you've summoned 8 other Pirates this game,
    //       plunder the enemy!
    //       <i>({0} left!)</i> <i>(Ready!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [TSC_936] Swiftscale Trickster - COST:4 [ATK:2/HP:2]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your next spell this turn costs (0).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [TSC_937] Crabatoa - COST:6 [ATK:6/HP:5]
    // - Race: Beast, Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Colossal +2</b>
    //       Your Crabatoa Claws have +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AURA = 1
    // - COLOSSAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [TSC_963] Filletfighter - COST:1 [ATK:3/HP:1]
    // - Race: Pirate, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_NONSELF_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 1));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_NONSELF_TARGET, 0 } };
    cards.emplace("TSC_963", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [TID_078] Shattershambler - COST:1 [ATK:1/HP:3]
    // - Race: Elemental, Faction: Horde, Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b>
    //       Your next <b>Deathrattle</b> minion costs (1) less,
    //       but immediately dies when played.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [TID_080] Inkveil Ambusher - COST:2 [ATK:1/HP:2]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //       Has +3 Attack and <b>Immune</b> while attacking.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [TID_931] Jackpot! - COST:2
    // - Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: Add two random spells from other classes
    //       that cost (5) or more to your hand.
    // --------------------------------------------------------
}

void TheSunkenCityCardsGen::AddRogueNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [TSC_086e] Sharp Point - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [TSC_912t] Sunken Vessel - COST:5
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Casts When Drawn</b>
    //       Summon two 3/3 Pirates with <b>Stealth</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TOPDECK = 1
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [TSC_912t2] Sunken Pirate - COST:3 [ATK:3/HP:3]
    // - Race: Pirate, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [TSC_912t3] Azsharan Pirate - COST:3 [ATK:3/HP:3]
    // - Race: Pirate, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [TSC_932t] Tiger Shark - COST:5 [ATK:5/HP:5]
    // - Race: Beast, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("TSC_932t", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [TSC_934t] Take their Supplies! - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Take 5 cards from your opponent's deck.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [TSC_934t2] Take their Gold! - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Take 2 cards from your opponent's hand.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [TSC_934t3] Take their Ship! - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Take control of your opponent's highest Attack minion.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [TSC_936e] Fooled the Audience - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Your next spell this turn costs (0).
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [TSC_937e] Crusty Treasure - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [TSC_937t] Crabatoa's Claw - COST:2 [ATK:2/HP:1]
    // - Race: Beast, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Deathrattle:</b> Equip a 2/1 Claw.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ----------------------------------------- WEAPON - ROGUE
    // [TSC_937t2] Crabatoa Claw - COST:1
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [TSC_937t3] Crabatoa's Claw - COST:2 [ATK:2/HP:1]
    // - Race: Beast, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Deathrattle:</b> Equip a 2/1 Claw.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [TID_080e2] Inked - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Immune</b> and +3 Attack while attacking.
    // --------------------------------------------------------
}

void TheSunkenCityCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- MINION - SHAMAN
    // [TSC_630] Wrathspine Enchanter - COST:7 [ATK:5/HP:4]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Cast a copy of a Fire, Frost,
    //       and Nature spell in your hand
    //       <i>(targets chosen randomly).</i>
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [TSC_631] Schooling - COST:1
    // - Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: Add three 1/1 Piranha Swarmers to your hand.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [TSC_633] Piranha Poacher - COST:3 [ATK:2/HP:5]
    // - Race: Murloc, Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       add a 1/1 Piranha Swarmer to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [TSC_635] Radiance of Azshara - COST:3 [ATK:3/HP:4]
    // - Race: Elemental, Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Fire Spell Damage +2</b>
    //       Your Nature spells cost (1) less.
    //       After you cast a Frost spell, gain 3 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AURA = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [TSC_637] Scalding Geyser - COST:1
    // - Set: THE_SUNKEN_CITY, Rarity: Common
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Deal 2 damage.
    //       <b>Dredge</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DREDGE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [TSC_639] Glugg the Gulper - COST:7 [ATK:3/HP:5]
    // - Race: Beast, Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Colossal +3</b>
    //       After a friendly minion dies, gain its original stats.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - COLOSSAL = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [TSC_648] Coral Keeper - COST:5 [ATK:3/HP:4]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 3/3 Elemental for
    //       each spell school you've cast this game.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [TSC_772] Azsharan Scroll - COST:1
    // - Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Discover</b> a Fire, Frost or Nature spell.
    //       Put a 'Sunken Scroll' on the bottom of your deck.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [TSC_922] Anchored Totem - COST:2 [ATK:0/HP:3]
    // - Race: Totem, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: After you summon a 1-Cost minion, give it +2/+1.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [TSC_923] Bioluminescence - COST:3
    // - Set: THE_SUNKEN_CITY, Rarity: Epic
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Give your minions <b>Spell Damage +1</b>.
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [TID_003] Tidelost Burrower - COST:4 [ATK:4/HP:4]
    // - Race: Murloc, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Dredge</b>.
    //       If it's a Murloc, summon a 2/2 copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DREDGE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [TID_004] Clownfish - COST:3 [ATK:3/HP:2]
    // - Race: Murloc, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your next two Murlocs cost (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [TID_005] Command of Neptulon - COST:5
    // - Set: THE_SUNKEN_CITY, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Summon two 5/4 Elementals with <b>Rush</b>.
    //       <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
}

void TheSunkenCityCardsGen::AddShamanNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [TSC_635e] Kaldorei Strength - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [TSC_639e] Gulped - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [TSC_639t] Glugg's Tail - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [TSC_639t2] Glugg's Tail - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [TSC_639t3] Glugg's Tail - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [TSC_648t] Coral Elemental - COST:3 [ATK:3/HP:3]
    // - Race: Elemental, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [TSC_772t] Sunken Scroll - COST:1
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Add a Fire, Frost, and Nature spell
    //       from your class to your hand.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [TSC_922e] Sink or Swim - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: +2/+1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [TSC_923e] Bioluminescent - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [TID_003e2] Revealed - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: 2/2.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [TID_004e] Clownfish Car - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Your next two Murlocs cost (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [TID_004e2] Clownin' Around - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [TID_005t] Water Revenant - COST:4 [ATK:5/HP:4]
    // - Race: Elemental, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
}

void TheSunkenCityCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - WARLOCK
    // [TSC_039] Azsharan Scavenger - COST:2 [ATK:2/HP:3]
    // - Race: Murloc, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b>
    //       Put a 'Sunken Scavenger' on the bottom of your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [TSC_614] Voidgill - COST:2 [ATK:3/HP:2]
    // - Race: Murloc, Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give all Murlocs in your hand +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [TSC_753] Bloodscent Vilefin - COST:3 [ATK:3/HP:4]
    // - Race: Murloc, Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Dredge</b>.
    //       If it's a Murloc,
    //       change its Cost to Health instead of Mana.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DREDGE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [TSC_924] Abyssal Wave - COST:6
    // - Set: THE_SUNKEN_CITY, Rarity: Epic
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Deal 4 damage to all minions.
    //       Give your opponent an Abyssal Curse.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [TSC_925] Rock Bottom - COST:1
    // - Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon a 1/1 Murloc, then <b>Dredge</b>.
    //       If it's also a Murloc, summon one more.
    // --------------------------------------------------------
    // GameTag:
    // - DREDGE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [TSC_955] Sira'kess Cultist - COST:3 [ATK:3/HP:4]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your opponent an Abyssal Curse.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [TSC_956] Dragged Below - COST:3
    // - Set: THE_SUNKEN_CITY, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Deal 4 damage to a minion.
    //       Give your opponent an Abyssal Curse.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [TSC_957] Chum Bucket - COST:2
    // - Set: THE_SUNKEN_CITY, Rarity: Epic
    // --------------------------------------------------------
    // Text: Give all Murlocs in your hand +1/+1.
    //       Repeat for each Murloc you control.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [TSC_959] Za'qul - COST:5 [ATK:6/HP:5]
    // - Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Your Abyssal Curses heal you for the damage they deal.
    //       <b>Battlecry:</b> Give your opponent an Abyssal Curse.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AURA = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [TSC_962] Gigafin - COST:8 [ATK:7/HP:4]
    // - Race: Murloc, Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Colossal +1</b>.
    //       <b>Battlecry:</b> Devour all enemy minions.
    //       <b>Deathrattle:</b> Spit them back out.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - COLOSSAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [TID_717] Herald of Shadows - COST:3 [ATK:4/HP:2]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b>
    //       If you've cast a Shadow spell while holding this,
    //       steal 2 Health from a minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [TID_718] Immolate - COST:4
    // - Set: THE_SUNKEN_CITY, Rarity: Rare
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Light every card in the opponent's hand on fire.
    //       In 3 turns, any still in hand are destroyed!
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [TID_719] Commander Ulthok - COST:5 [ATK:7/HP:7]
    // - Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your opponent's cards cost Health
    //       instead of Mana next turn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void TheSunkenCityCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - WARLOCK
    // [TSC_039t] Sunken Scavenger - COST:2 [ATK:2/HP:3]
    // - Race: Murloc, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your other Murlocs +1/+1
    //       <i>(wherever they are)</i>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [TSC_039te] Mllgggrrrr - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [TSC_614e] Void Powered - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [TSC_753e] Fresh Scent - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Costs Health instead of Mana.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [TSC_925t] Coldlight Lurker - COST:1 [ATK:1/HP:1]
    // - Race: Murloc, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [TSC_955t] Abyssal Curse - COST:2
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: At the start of your turn, take {0} damage.
    //       Each Curse is worse than the last.
    //       <i>({1} turns remaining).</i>
    // --------------------------------------------------------
    // GameTag:
    // - EVIL_GLOW = 1
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [TSC_957e] Empty Bucket - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [TSC_959e] Cursed - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Your Abyssal Curses heal you for the damage they deal.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [TSC_959e2] Cursed - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Your Curses cost (2) more this game.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [TSC_962e] Swallowed Whole - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Storing a Minion.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [TSC_962e2] Bloated - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Gigafin has eaten all enemy minions!
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [TSC_962t] Gigafin's Maw - COST:6 [ATK:4/HP:7]
    // - Race: Murloc, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Taunt</b> <b>Deathrattle:</b>
    //       Permanently destroy all minions inside Gigafin.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [TID_717e] Siphoned - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Reduced Health.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [TID_717e2] Shadow Siphon - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Increased Health.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [TID_717e2b] Siphoned - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Increased Health.
    // --------------------------------------------------------
    // GameTag:
    // - ENCHANTMENT_INVISIBLE = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [TID_717eb] Siphoned - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Reduced Health.
    // --------------------------------------------------------
    // GameTag:
    // - ENCHANTMENT_INVISIBLE = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [TID_718e] Engulfed in Flame - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: In 3 turns, destroy the opponent's cards that are on fire.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [TID_718e2] Engulfed in Flame - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: This card is on fire!
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [TID_719e] Blood Squeeze - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Your cards cost Health instead of Mana this turn.
    // --------------------------------------------------------
}

void TheSunkenCityCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - WARRIOR
    // [TSC_659] Trenchstalker - COST:9 [ATK:8/HP:9]
    // - Race: Beast, Set: THE_SUNKEN_CITY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Attack three different random enemies.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [TSC_660] Nellie, the Great Thresher - COST:7 [ATK:5/HP:5]
    // - Race: Beast, Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Colossal +1</b> <b>Battlecry:</b>
    //       <b>Discover</b> 3 Pirates to crew Nellie's Ship!
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - COLOSSAL = 1
    // - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [TSC_913] Azsharan Trident - COST:3
    // - Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b>
    //       Put a 'Sunken Trident' on the bottom of your deck.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [TSC_917] Blackscale Brute - COST:7 [ATK:5/HP:6]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>. <b>Battlecry:</b>
    //       If you have a weapon equipped,
    //       summon a 5/6 Naga with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [TSC_939] Forged in Flame - COST:2
    // - Set: THE_SUNKEN_CITY, Rarity: Common
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Destroy your weapon,
    //       then draw cards equal to its Attack.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [TSC_940] From the Depths - COST:4
    // - Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Reduce the Cost of the bottom five cards
    //       in your deck by (3), then <b>Dredge</b>.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [TSC_941] Guard the City - COST:2
    // - Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: Gain 3 Armor.
    //       Summon a 2/3 Naga with <b>Taunt</b>.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ArmorTask>(3));
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("TSC_941t", SummonSide::SPELL));
    cards.emplace("TSC_941", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [TSC_942] Obsidiansmith - COST:2 [ATK:3/HP:2]
    // - Race: Pirate, Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Dredge</b>.
    //       If it's a minion or a weapon, give it +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DREDGE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [TSC_943] Lady Ashvane - COST:5 [ATK:5/HP:5]
    // - Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give all weapons in your hand,
    //       deck, and battlefield +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [TSC_944] The Fires of Zin-Azshari - COST:2
    // - Set: THE_SUNKEN_CITY, Rarity: Epic
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Replace your deck with minions that cost (5) or more.
    //       They cost (5).
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [TID_714] Igneous Lavagorger - COST:4 [ATK:3/HP:5]
    // - Race: Elemental, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> <b>Dredge</b>.
    //       Gain Armor equal to its Cost.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DREDGE = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [TID_715] Clash of the Colossals - COST:3
    // - Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Add a random <b>Colossal</b> minion
    //       to both players' hands.
    //       Yours costs (2) less.
    // --------------------------------------------------------
    // RefTag:
    // - COLOSSAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [TID_716] Tidal Revenant - COST:8 [ATK:5/HP:8]
    // - Race: Elemental, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 5 damage. Gain 8 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void TheSunkenCityCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [TSC_660e] Mercenary's Fee - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Costs (1).
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [TSC_660e2] Pirate Crew - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Holding Nellie's Pirate Crew.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [TSC_660t] Nellie's Pirate Ship - COST:5 [ATK:2/HP:6]
    // - Race: Beast, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b><b>Taunt</b>.</b> <b>Deathrattle:</b>
    //       Add Nellie's Pirate crew to your hand.
    //       They Cost (1) less.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [TSC_913t] Sunken Trident - COST:3
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: After your hero attacks,
    //       deal 2 damage to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [TSC_917t] Firescale Berserker - COST:7 [ATK:5/HP:6]
    // - Race: Naga, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [TSC_940e2] Current Events - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Costs (3) less.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [TSC_941t] Naga Centaur - COST:2 [ATK:2/HP:3]
    // - Race: Naga, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("TSC_941t", cardDef);

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [TSC_942e] Flameforged - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [TSC_943e] Rigid Carapace - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [TSC_944e] The Fiery Deep - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Costs (5).
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [TID_714e] Gorged - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Increased attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [TID_715e] Colossal Advantage - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------
}

void TheSunkenCityCardsGen::AddDemonHunter(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------ SPELL - DEMONHUNTER
    // [TSC_006] Multi-Strike - COST:2
    // - Set: THE_SUNKEN_CITY, Rarity: Rare
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Give your hero +2 Attack this turn.
    //       They may attack an additional enemy minion.
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [TSC_057] Azsharan Defector - COST:4 [ATK:5/HP:3]
    // - Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b>. <b>Deathrattle:</b>
    //       Put a 'Sunken Defector' on the bottom of your deck.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [TSC_058] Predation - COST:3
    // - Set: THE_SUNKEN_CITY, Rarity: Rare
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Deal 3 damage.
    //       Costs (0) if you played a Naga while holding this.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    cardDef.power.AddAura(
        std::make_shared<AdaptiveCostEffect>([](const Playable* playable) {
            if (playable->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1) == 1)
            {
                return playable->GetGameTag(GameTag::COST);
            }

            return 0;
        }));
    ComplexTrigger::PlayedNagaWhileHoldingThis(cardDef.power);
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("TSC_058", cardDef);

    // ----------------------------------- MINION - DEMONHUNTER
    // [TSC_217] Wayward Sage - COST:2 [ATK:2/HP:2]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Outcast:</b> Reduce the Cost of the left and
    //       right-most cards in your hand by (1).
    // --------------------------------------------------------
    // GameTag:
    // - OUTCAST = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [TSC_218] Lady S'theno - COST:3 [ATK:2/HP:4]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Immune</b> while attacking.
    //       After you cast a spell,
    //       attack the lowest Health enemy.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [TSC_219] Xhilag of the Abyss - COST:7 [ATK:3/HP:6]
    // - Race: Demon, Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Colossal +4</b>
    //       At the start of your turn,
    //       increase the damage of Xhilag's Stalks by 1.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - COLOSSAL = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [TSC_608] Abyssal Depths - COST:3
    // - Set: THE_SUNKEN_CITY, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Draw your two lowest Cost minions.
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [TSC_609] Coilskar Commander - COST:6 [ATK:2/HP:6]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Taunt</b>. <b>Battlecry:</b>
    //       If you've cast three spells while holding this,
    //       summon two copies of this.
    //       <i>({0} left!)</i> <i>(Ready!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [TSC_610] Glaiveshark - COST:4 [ATK:4/HP:3]
    // - Race: Beast, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your hero attacked this turn,
    //       deal 2 damage to all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------- WEAPON - DEMONHUNTER
    // [TSC_915] Bone Glaive - COST:5
    // - Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Dredge</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DREDGE = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [TID_703] Topple the Idol - COST:5
    // - Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Dredge</b>. Reveal it and deal damage equal to
    //       its Cost to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // - DREDGE = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [TID_704] Fossil Fanatic - COST:2 [ATK:2/HP:2]
    // - Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: After your hero attacks, draw a Fel spell.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [TID_706] Herald of Chaos - COST:3 [ATK:3/HP:4]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    //       <b>Battlecry:</b>
    //       If you've cast a Fel spell while holding this,
    //       gain <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
}

void TheSunkenCityCardsGen::AddDemonHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [TSC_006e] Soulbound - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [TSC_006e2] Multi-Strike enchant - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Attack +2.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [TSC_057t] Sunken Defector - COST:4 [ATK:5/HP:3]
    // - Race: Naga, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Charge</b>. After this attacks,
    //       deal 5 damage to a random enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [TSC_058e] Looting - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Costs (0).
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [TSC_217e] Found the Wrong Way - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [TSC_219e] Eye-Laser Surgery - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Improved damage.
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [TSC_219t] Xhilag's Stalk - COST:2 [ATK:1/HP:2]
    // - Race: Demon, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       deal 2 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [TSC_219t2] Xhilag's Stalk - COST:2 [ATK:1/HP:2]
    // - Race: Demon, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       deal 2 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [TSC_219t3] Xhilag's Stalk - COST:2 [ATK:1/HP:2]
    // - Race: Demon, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       deal 2 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [TSC_219t4] Xhilag's Stalk - COST:2 [ATK:1/HP:2]
    // - Race: Demon, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       deal 2 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [TID_706e] Felfused - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Has <b>Rush</b>.
    // --------------------------------------------------------
}

void TheSunkenCityCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_001] Naval Mine - COST:2 [ATK:0/HP:2]
    // - Race: Mechanical, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 4 damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 4));
    cards.emplace("TSC_001", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_002] Pufferfist - COST:3 [ATK:3/HP:3]
    // - Race: Pirate, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: After your hero attacks, deal 1 damage to all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DamageTask>(
        EntityType::ENEMIES, 1) };
    cards.emplace("TSC_002", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_007] Gangplank Diver - COST:5 [ATK:6/HP:4]
    // - Race: Pirate, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Dormant</b> for 1 turn.
    //       <b>Rush</b>. <b>Immune</b> while attacking.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_013] Slimescale Diver - COST:3 [ATK:2/HP:4]
    // - Race: Murloc, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Dormant</b> for 1 turn.
    //       <b>Rush</b>, <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - POISONOUS = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_017] Baba Naga - COST:4 [ATK:4/HP:4]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you've cast
    //       a spell while holding this, deal 3 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE,
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsTagValue(GameTag::TAG_SCRIPT_DATA_NUM_1, 1)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DamageTask>(EntityType::TARGET, 3) }));
    ComplexTrigger::CastSpellWhileHoldingThis(cardDef.power);
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 } };
    cards.emplace("TSC_017", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_020] Barbaric Sorceress - COST:6 [ATK:3/HP:7]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>.
    //       <b>Battlecry:</b> Swap the Cost of a random spell
    //       in each player's hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_032] Blademaster Okani - COST:4 [ATK:2/HP:6]
    // - Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b>
    //       <b>Secretly</b> choose to <b>Counter</b> the next minion
    //       or spell your opponent plays while this is alive.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - COUNTER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_034] Gorloc Ravager - COST:5 [ATK:4/HP:3]
    // - Race: Murloc, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw 3 Murlocs.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_052] School Teacher - COST:4 [ATK:4/HP:4]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a 1/1 Nagaling to your hand.
    //       <b>Discover</b> a spell that costs (3) or less
    //       to teach it.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_053] Rainbow Glowscale - COST:2 [ATK:2/HP:3]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("TSC_053", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_064] Slithering Deathscale - COST:7 [ATK:5/HP:9]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b>
    //       If you've cast three spells while holding this,
    //       deal 3 damage to all enemies.
    //       <i>({0} left!)</i> <i>(Ready!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_065] Helmet Hermit - COST:1 [ATK:4/HP:3]
    // - Race: Beast, Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Can't attack.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_ATTACK = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("TSC_065", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_067] Ambassador Faelin - COST:4 [ATK:4/HP:5]
    // - Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Put 3 <b>Colossal</b> minions
    //       on the bottom of your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - COLOSSAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_069] Amalgam of the Deep - COST:2 [ATK:2/HP:3]
    // - Race: All, Set: THE_SUNKEN_CITY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a friendly minion.
    //       <b>Discover</b> a minion of the same minion type.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_632] Click-Clocker - COST:1 [ATK:1/HP:1]
    // - Race: Mechanical, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>. <b>Battlecry:</b>
    //       Give a random Mech in your hand +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_638] Piranha Swarmer - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       After you summon a Piranha Swarmer, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_640] Reefwalker - COST:3 [ATK:3/HP:2]
    // - Race: Elemental, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry and Deathrattle:</b>
    //       Summon a 1/1 Piranha Swarmer.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_641] Queen Azshara - COST:5 [ATK:5/HP:5]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b>
    //       If you've cast three spells while holding this,
    //       choose an Ancient Relic.
    //       <i>({0} left!)</i> <i>(Ready!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_645] Mothership - COST:6 [ATK:5/HP:4]
    // - Race: Mechanical, Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Deathrattle:</b> Summon two random Mechs
    //       that cost (3) or less.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_646] Seascout Operator - COST:3 [ATK:2/HP:4]
    // - Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a Mech,
    //       summon two 2/1 Mechafish.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_647] Pelican Diver - COST:1 [ATK:4/HP:1]
    // - Race: Beast, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Dormant</b> for 1 turn.
    //       <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_649] Ini Stormcoil - COST:5 [ATK:4/HP:4]
    // - Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a friendly Mech.
    //       Summon a copy of it with <b>Rush</b>,
    //       <b>Windfury</b>, and <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // - RUSH = 1
    // - WINDFURY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_823] Murkwater Scribe - COST:2 [ATK:3/HP:2]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> The next spell you play costs (1) less.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_826] Crushclaw Enforcer - COST:3 [ATK:3/HP:4]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b>
    //       If you've cast a spell while holding this,
    //       draw a Naga.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_827] Vicious Slitherspear - COST:1 [ATK:1/HP:3]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you cast a spell,
    //       gain +1 Attack until your next turn.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_829] Naga Giant - COST:20 [ATK:8/HP:8]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Epic
    // --------------------------------------------------------
    // Text: Costs (1) less for each Mana you've spent
    //       on spells this game.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_908] Sir Finley, Sea Guide - COST:1 [ATK:1/HP:3]
    // - Race: Murloc, Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Swap your hand with the bottom
    //       of your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_909] Tuskarrrr Trawler - COST:2 [ATK:2/HP:3]
    // - Race: Pirate, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Dredge</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DREDGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DredgeTask>());
    cards.emplace("TSC_909", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_911] Excavation Specialist - COST:4 [ATK:3/HP:6]
    // - Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Dredge</b>.
    //       Reduce its Cost by (1).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DREDGE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_919] Azsharan Sentinel - COST:5 [ATK:5/HP:6]
    // - Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>. <b>Deathrattle:</b>
    //       Put a 'Sunken Sentinel' on the bottom of your deck.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_926] Smothering Starfish - COST:4 [ATK:2/HP:4]
    // - Race: Beast, Set: THE_SUNKEN_CITY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Silence</b> ALL other minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SILENCE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_928] Security Automaton - COST:2 [ATK:1/HP:3]
    // - Race: Mechanical, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: After you summon a Mech, gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_935] Selfish Shellfish - COST:4 [ATK:7/HP:7]
    // - Race: Beast, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Your opponent draws 2 cards.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_938] Treasure Guard - COST:3 [ATK:1/HP:5]
    // - Race: Naga, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(std::make_shared<DrawTask>(1));
    cards.emplace("TSC_938", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_960] Twin-fin Fin Twin - COST:3 [ATK:2/HP:1]
    // - Race: Murloc, Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b>. <b>Battlecry:</b> Summon a copy of this.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TID_710] Snapdragon - COST:3 [ATK:3/HP:3]
    // - Race: Beast, Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give all <b>Battlecry</b> minions
    //       in your deck +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TID_711] Ozumat - COST:8 [ATK:6/HP:5]
    // - Race: Beast, Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Colossal +6</b>
    //       <b>Deathrattle:</b> For each of Ozumat's Tentacles,
    //       destroy a random enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - COLOSSAL = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TID_712] Neptulon the Tidehunter - COST:10 [ATK:7/HP:7]
    // - Race: Elemental, Set: THE_SUNKEN_CITY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Colossal +2</b>, <b>Rush</b>, <b>Windfury</b>
    //       Whenever Neptulon attacks, if you control any Hands,
    //       they attack instead.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - COLOSSAL = 1
    // - RUSH = 1
    // - TRIGGER_VISUAL = 1
    // - WINDFURY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TID_713] Bubbler - COST:1 [ATK:2/HP:4]
    // - Race: Elemental, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: After this minion takes exactly one damage,
    //       destroy it. <i>(Pop!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TID_744] Coilfang Constrictor - COST:4 [ATK:5/HP:4]
    // - Race: Beast, Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b>
    //       Look at 3 cards in your opponent's hand
    //       and choose one. It can't be played next turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void TheSunkenCityCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - NEUTRAL
    // [TSC_003] Coilfang Constrictor - COST:4 [ATK:5/HP:4]
    // - Race: Beast, Set: THE_SUNKEN_CITY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Look at 3 cards
    //       in your opponent's hand and choose one.
    //       It can't be played next turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TSC_003e] Constricted - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Can't be played next turn.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TSC_020e] Barbarous - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Attack was swapped.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TSC_020e2] Barbarous - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Cost was swapped.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [TSC_032t] Minion Counter - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Counter</b> the next minion your opponent plays.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [TSC_032t2] Spell Counter - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Counter</b> the next spell your opponent plays.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_052t] Nagaling - COST:1 [ATK:1/HP:1]
    // - Race: Naga, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Cast {0}.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TSC_083e] Lamplight - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TSC_632e] Robo-claws - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TSC_638e] Swarming - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_638t] Piranha Swarmer - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       After you summon a Piranha Swarmer, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_638t2] Piranha Swarmer - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       After you summon a Piranha Swarmer, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_638t3] Piranha Swarmer - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       After you summon a Piranha Swarmer, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_638t4] Piranha Swarmer - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: THE_SUNKEN_CITY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       After you summon a Piranha Swarmer, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [TSC_641ta] Ring of Tides - COST:1
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: After you cast a spell,
    //       this becomes a copy of it that costs (1).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TSC_641tae] Shifting - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Transforming into your spells.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [TSC_641tb] Horn of Ancients - COST:3
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Add a random <b>Colossal</b> minion to your hand.
    //       It costs (1).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // RefTag:
    // - COLOSSAL = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - NEUTRAL
    // [TSC_641tc] Xal'atath - COST:2
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: After you cast a spell,
    //       deal 2 damage to the enemy hero and lose 1 Durability.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [TSC_641td] Tidestone of Golganneth - COST:1
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Shuffle 5 random spells into your deck.
    //       Set their Cost to (1). Draw two cards.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TSC_641tde] Reduced - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Costs (1).
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_646t] Mechafish - COST:1 [ATK:2/HP:1]
    // - Race: Mechanical, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TSC_647e] Diving - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Dormant</b>. Awaken in 1 turn.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TSC_649e2] Enhanced! - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Granted <b>Rush</b>, <b>Divine Shield</b>
    //       and <b>Windfury</b>.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TSC_823e] Murky - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Your next spell costs (1) less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TSC_827e] Vicious - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: +1 Attack until your next turn.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TSC_919t] Sunken Sentinel - COST:5 [ATK:5/HP:6]
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b><b>Divine Shield</b>,</b> <b><b>Taunt</b>,</b>
    //       <b>Lifesteal</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // - LIFESTEAL = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [TSC_COIN1] The Coin - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Gain 1 Mana Crystal this turn only.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [TSC_COIN2] The Coin - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Gain 1 Mana Crystal this turn only.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TID_710e] Razor Sharp - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TID_711t] Ozumat's Tentacle - COST:1 [ATK:1/HP:3]
    // - Race: Beast, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TID_711t2] Ozumat's Tentacle - COST:1 [ATK:1/HP:3]
    // - Race: Beast, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TID_711t3] Ozumat's Tentacle - COST:1 [ATK:1/HP:3]
    // - Race: Beast, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TID_711t4] Ozumat's Tentacle - COST:1 [ATK:1/HP:3]
    // - Race: Beast, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TID_711t5] Ozumat's Tentacle - COST:1 [ATK:1/HP:3]
    // - Race: Beast, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TID_711t6] Ozumat's Tentacle - COST:1 [ATK:1/HP:3]
    // - Race: Beast, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TID_712t] Neptulon's Hand - COST:4 [ATK:4/HP:2]
    // - Race: Elemental, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Immune</b> while attacking.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TID_712t2] Neptulon's Hand - COST:4 [ATK:4/HP:2]
    // - Race: Elemental, Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: <b>Immune</b> while attacking.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TID_744e] Constricted - COST:0
    // - Set: THE_SUNKEN_CITY
    // --------------------------------------------------------
    // Text: Can't be played next turn.
    // --------------------------------------------------------
}

void TheSunkenCityCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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