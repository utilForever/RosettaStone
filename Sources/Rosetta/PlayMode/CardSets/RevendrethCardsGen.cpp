// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/RevendrethCardsGen.hpp>
#include <Rosetta/PlayMode/Cards/CardPowers.hpp>

namespace RosettaStone::PlayMode
{
void RevendrethCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void RevendrethCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void RevendrethCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ SPELL - DRUID
    // [REV_307] Natural Causes - COST:2
    // - Set: REVENDRETH, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Deal 2 damage. Summon a 2/2 Treant.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, true));
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("REV_336t2", SummonSide::SPELL));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("REV_307", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [REV_310] Death Blossom Whomper - COST:6 [ATK:7/HP:6]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a <b>Deathrattle</b> minion
    //       and gain its <b>Deathrattle.</b>
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [REV_311] Nightshade Bud - COST:8
    // - Set: REVENDRETH, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: <b>Choose One - </b>
    //       <b>Discover</b> a minion from your deck to summon;
    //       or a spell to cast.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [REV_313] Planted Evidence - COST:1
    // - Set: REVENDRETH, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: <b>Discover</b> a spell.
    //       It costs (2) less this turn.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::SPELL_AND_STACK));
    cardDef.power.AddAfterChooseTask(
        std::make_shared<AddEnchantmentTask>("REV_313e", EntityType::STACK));
    cards.emplace("REV_313", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [REV_314] Topior the Shrubbagazzor - COST:7 [ATK:5/HP:5]
    // - Race: Dragon, Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> For the rest of the game,
    //       after you cast a Nature spell,
    //       summon a 3/3 Whelp with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [REV_318] Widowbloom Seedsman - COST:4 [ATK:3/HP:2]
    // - Set: REVENDRETH, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a Nature spell.
    //       Gain an empty Mana Crystal.
    // --------------------------------------------------------
    // RefTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DrawSpellTask>(SpellSchool::NATURE, 1));
    cardDef.power.AddPowerTask(std::make_shared<ManaCrystalTask>(1, false));
    cards.emplace("REV_318", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [REV_319] Sesselie of the Fae Court - COST:8 [ATK:8/HP:8]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle</b>: Draw a minion.
    //       Reduce its Cost by (8).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(std::make_shared<DrawMinionTask>(1, true));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddEnchantmentTask>("REV_319e", EntityType::STACK));
    cards.emplace("REV_319", cardDef);

    // --------------------------------------- LOCATION - DRUID
    // [REV_333] Hedge Maze - COST:3
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: Trigger a friendly minion's <b>Deathrattle</b>.
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [REV_336] Plot of Sin - COST:3
    // - Set: REVENDRETH, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Summon two 2/2 Treants.
    //       <b>Infuse (5):</b> Two 5/5 Ancients instead.
    // --------------------------------------------------------
    // GameTag:
    // - INFUSE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("REV_336t2", 2, SummonSide::SPELL));
    cardDef.property.numMinionsToInfuse = 5;
    cardDef.property.infusedCardID = "REV_336t4";
    cards.emplace("REV_336", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [REV_365] Convoke the Spirits - COST:10
    // - Set: REVENDRETH, Rarity: Epic
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Cast 8 random Druid spells
    //       <i>(targets chosen randomly)</i>.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [MAW_024] Dew Process - COST:2
    // - Set: REVENDRETH, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: For the rest of the game,
    //       players draw an extra card at the start of their turn.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [MAW_025] Attorney-at-Maw - COST:2 [ATK:1/HP:3]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> <b>Silence</b> a minion;
    //       or Give a minion <b>Immune</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // - SILENCE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [MAW_026] Incarceration - COST:3
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: Choose a minion.
    //       It goes <b>Dormant</b> for 3 turns.
    // --------------------------------------------------------
}

void RevendrethCardsGen::AddDruidNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------ ENCHANTMENT - DRUID
    // [REV_310e] Whomping - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Copied <b>Deathrattle</b> from {0}.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [REV_311t] Sunlight Blossom - COST:8
    // - Set: REVENDRETH
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: <b>Discover</b> a spell from your deck to cast.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [REV_311t2] Moonlight Blossom - COST:8
    // - Set: REVENDRETH
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: <b>Discover</b> a minion from your deck to summon.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [REV_313e] Ripe Spell - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Costs (2) less this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Effects::ReduceCost(2), false, true));
    cards.emplace("REV_313e", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [REV_314e] Winter Queen's Blessing - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: For the rest of the game,
    //       after you play a Nature spell summon a 3/3 Dragon.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [REV_314t] Whelpagazzor - COST:3 [ATK:3/HP:3]
    // - Race: Dragon, Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [REV_318e] Cycle of Life - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Play the card to gain an empty Mana Crystal.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [REV_318e2] Play This Game Enchantment - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [REV_319e] Sesselie's Blessing - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Costs (8) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_unique<Enchant>(Effects::ReduceCost(8)));
    cards.emplace("REV_319e", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [REV_336t2] Treant - COST:2 [ATK:2/HP:2]
    // - Set: REVENDRETH
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("REV_336t2", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [REV_336t3] Ancient - COST:5 [ATK:5/HP:5]
    // - Set: REVENDRETH
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("REV_336t3", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [REV_336t4] Plot of Sin - COST:3
    // - Set: REVENDRETH, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: <b>Infused</b>
    //       Summon two 5/5 Ancients.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("REV_336t3", 2, SummonSide::SPELL));
    cards.emplace("REV_336t4", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [MAW_024e2] Maw Rules - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Player draws an extra card at the start of their turn.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [MAW_024e3] Maw Rules - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Draw an extra card at the start of your turn.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [MAW_025a] Guilty! - COST:2
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Silence</b> a minion.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [MAW_025b] Innocent! - COST:2
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Give a minion <b>Immune</b> this turn.
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [MAW_025e] Proven Innocent - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Immune</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [MAW_026e] Doing Time - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Dormant</b>. Awaken in 3 turns.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [MAW_026e2] Doing Time - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
}

void RevendrethCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- SPELL - HUNTER
    // [REV_350] Frenzied Fangs - COST:2
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: Summon two 2/1 Bats.
    //       <b>Infuse (3):</b> Give them +1/+2.
    // --------------------------------------------------------
    // GameTag:
    // - INFUSE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("REV_350t", 2, SummonSide::SPELL));
    cardDef.property.numMinionsToInfuse = 3;
    cardDef.property.infusedCardID = "REV_350t2";
    cards.emplace("REV_350", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [REV_352] Stonebound Gargon - COST:4 [ATK:3/HP:5]
    // - Race: Beast, Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Infuse (3):</b> Also damages the minions
    //       next to whomever this attacks.
    // --------------------------------------------------------
    // GameTag:
    // - INFUSE = 1
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.numMinionsToInfuse = 3;
    cardDef.property.infusedCardID = "REV_352t";
    cards.emplace("REV_352", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [REV_353] Huntsman Altimor - COST:7 [ATK:5/HP:4]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a Gargon Companion.
    //       <b>Infuse (4):</b> Summon another.
    //       <b>Infuse (4):</b> And another!
    // --------------------------------------------------------
    // Entourage: REV_353t3, REV_353t4, REV_353t5
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - INFUSE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<RandomEntourageTask>());
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>(SummonSide::RIGHT));
    cardDef.property.entourages =
        Entourages{ "REV_353t3", "REV_353t4", "REV_353t5" };
    cardDef.property.numMinionsToInfuse = 4;
    cardDef.property.infusedCardID = "REV_353t";
    cards.emplace("REV_353", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [REV_356] Batty Guest - COST:1 [ATK:1/HP:1]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 2/1 Bat.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(std::make_shared<SummonTask>("REV_350t"));
    cards.emplace("REV_356", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [REV_360] Spirit Poacher - COST:2 [ATK:2/HP:2]
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a random
    //       <b>Dormant</b> Wildseed.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [REV_361] Wild Spirits - COST:3
    // - Set: REVENDRETH, Rarity: Epic
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Summon two different <b>Dormant</b> Wildseeds.
    //       Make your Wildseeds awaken 1 turn sooner.
    // --------------------------------------------------------

    // -------------------------------------- LOCATION - HUNTER
    // [REV_362] Castle Kennels - COST:2
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give a friendly minion +2 Attack.
    //       If it's a Beast, give it <b>Rush</b>.
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [REV_363] Ara'lon - COST:5 [ATK:4/HP:5]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon one of
    //       each <b>Dormant</b> Wildseed.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [REV_364] Stag Charge - COST:3
    // - Set: REVENDRETH, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 3 damage.
    //       Summon a random <b>Dormant</b> Wildseed.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [REV_369] Collateral Damage - COST:8
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 6 damage to three random enemy minions.
    //       Excess damage hits the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [MAW_009] Shadehound - COST:5 [ATK:6/HP:5]
    // - Race: Beast, Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever this attacks,
    //       give your other Beasts +2/+2.
    //       <b>Infuse (3 Beasts):</b> Gain <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - INFUSE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [MAW_010] Motion Denied - COST:2
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After your opponent plays three cards
    //       in a turn, deal 6 damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [MAW_011] Defense Attorney Nathanos - COST:6 [ATK:5/HP:4]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a friendly
    //       <b>Deathrattle</b> minion that died this game.
    //       Trigger and gain its <b>Deathrattle</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
}

void RevendrethCardsGen::AddHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [REV_350e] Bloodthirsty - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: +1/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("REV_350e"));
    cards.emplace("REV_350e", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [REV_350t] Thirsty Bat - COST:1 [ATK:2/HP:1]
    // - Race: Beast, Set: REVENDRETH
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("REV_350t", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [REV_350t2] Frenzied Fangs - COST:2
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Infused</b>
    //       Summon two 2/1 Bats. Give them +1/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("REV_350t", 2, SummonSide::SPELL, true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("REV_350e", EntityType::STACK));
    cards.emplace("REV_350t2", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [REV_352t] Stonebound Gargon - COST:4 [ATK:3/HP:5]
    // - Race: Beast, Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Infused</b>
    //       <b>Rush</b>. Also damages the minions
    //       next to whomever this attacks.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SELF;
    cardDef.power.GetTrigger()->tasks = {
        ComplexTask::DamageMinionsNextToAttack()
    };
    cards.emplace("REV_352t", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [REV_353t] Huntsman Altimor - COST:7 [ATK:5/HP:4]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Infused</b>
    //       <b>Battlecry:</b> Summon 2 Gargon Companions.
    //       <b>Infuse (4):</b> Summon all 3!   
    // --------------------------------------------------------
    // Entourage: REV_353t3, REV_353t4, REV_353t5
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - INFUSE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<RandomEntourageTask>(2));
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>(
        SummonSide::RIGHT, std::nullopt, true, false, 2));
    cardDef.property.entourages =
        Entourages{ "REV_353t3", "REV_353t4", "REV_353t5" };
    cardDef.property.numMinionsToInfuse = 4;
    cardDef.property.infusedCardID = "REV_353t2";
    cards.emplace("REV_353t", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [REV_353t2] Huntsman Altimor - COST:7 [ATK:5/HP:4]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Infused</b>
    //       <b>Battlecry:</b> Summon all 3 Gargon Companions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("REV_353t5", SummonSide::RIGHT));
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("REV_353t4", SummonSide::RIGHT));
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("REV_353t3", SummonSide::RIGHT));
    cards.emplace("REV_353t2", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [REV_353t3] Hecutis - COST:3 [ATK:4/HP:4]
    // - Race: Beast, Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("REV_353t3", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [REV_353t4] Barghast - COST:3 [ATK:2/HP:4]
    // - Race: Beast, Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Your other minions have +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<Aura>(AuraType::FIELD_EXCEPT_SOURCE, "REV_353t4e"));
    cards.emplace("REV_353t4", cardDef);

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [REV_353t4e] Bone from the Stone - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Barghast is granting this minion +1 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("REV_353t4e"));
    cards.emplace("REV_353t4e", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [REV_353t5] Margore - COST:3 [ATK:4/HP:2]
    // - Race: Beast, Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("REV_353t5", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [REV_360t] Fox Spirit Wildseed - COST:1 [ATK:3/HP:1]
    // - Race: Beast, Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Dormant</b> for 1 turn.
    //       <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [REV_360t1] Bear Spirit Wildseed - COST:2 [ATK:2/HP:4]
    // - Race: Beast, Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Dormant</b> for 2 turns.
    //       <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [REV_360t1e] Mature Wildseed - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Dormant</b>. Awaken in 2 turns.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [REV_360t2] Stag Spirit Wildseed - COST:3 [ATK:4/HP:3]
    // - Race: Beast, Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Dormant</b> for 3 turns.
    //       When this awakens, equip a 3/2 Greatbow.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [REV_360t2e] Elder Wildseed - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Dormant</b>. Awaken in 3 turns.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - HUNTER
    // [REV_360t4] Stagpoint Wildbow - COST:4
    // - Set: REVENDRETH
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [REV_360te] Young Wildseed - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Dormant</b>. Awaken in 1 turn.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [REV_362e] Beast Mode - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [REV_362e2] Resistant - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Immune</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [MAW_009e] Maw Bound - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [MAW_009t] Shadehound - COST:5 [ATK:6/HP:5]
    // - Race: Beast, Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Infused</b>
    //       <b>Rush</b>. Whenever this attacks,
    //       give your other Beasts +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [MAW_010t] Improved Motion Denied - COST:2
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After your opponent plays three cards
    //       in a turn, deal 9 damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - SECRET = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [MAW_011e] Defending Death - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Copied <b>Deathrattle</b> from {0}.
    // --------------------------------------------------------
}

void RevendrethCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ MINION - MAGE
    // [REV_000] Suspicious Alchemist - COST:1 [ATK:1/HP:3]
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a spell.
    //       If your opponent guesses your choice,
    //       they get a copy.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [REV_504] Solid Alibi - COST:2
    // - Set: REVENDRETH, Rarity: Epic
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: Until your next turn,
    //       your hero can only take 1 damage at a time.
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [REV_505] Cold Case - COST:4
    // - Set: REVENDRETH, Rarity: Common
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: Summon two 2/2 Volatile Skeletons. Gain 4 Armor.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [REV_513] Chatty Bartender - COST:4 [ATK:4/HP:4]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       if you control a <b>Secret</b>,
    //       deal 2 damage to all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [REV_514] Kel'Thuzad, the Inevitable - COST:8 [ATK:6/HP:8]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Resurrect your Volatile Skeletons.
    //       Any that can't fit on the battlefield instantly explode!
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [REV_515] Orion, Mansion Manager - COST:4 [ATK:3/HP:5]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After a friendly <b>Secret</b> is revealed,
    //       cast a different Mage <b>Secret</b> and gain +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [REV_516] Vengeful Visage - COST:3
    // - Set: REVENDRETH, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After an enemy minion attacks your hero,
    //       summon a copy of it to attack the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [REV_601] Frozen Touch - COST:2
    // - Set: REVENDRETH, Rarity: Common
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: Deal 3 damage.
    //       <b>Infuse (3):</b> Add a Frozen Touch to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - INFUSE = 1
    // --------------------------------------------------------

    // ---------------------------------------- LOCATION - MAGE
    // [REV_602] Nightcloak Sanctum - COST:3
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Freeze</b> a minion.
    //       Summon a 2/2 Volatile Skeleton.
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [REV_840] Deathborne - COST:6
    // - Set: REVENDRETH, Rarity: Rare
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: Deal 2 damage to all minions.
    //       Summon a 2/2 Volatile Skeleton for each killed.
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [MAW_006] Objection! - COST:3
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your opponent plays a minion,
    //       <b>Counter</b> it.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    // RefTag:
    // - COUNTER = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [MAW_013] Life Sentence - COST:4
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: Remove a minion from the game.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [MAW_101] Contract Conjurer - COST:6 [ATK:6/HP:6]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: Costs (3) less for each <b>Secret</b> you control.
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
}

void RevendrethCardsGen::AddMageNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ------------------------------------- ENCHANTMENT - MAGE
    // [REV_000e] A Mystery! - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       guess what card your opponent chose
    //       to get a copy of it.
    // --------------------------------------------------------

    // ------------------------------------- ENCHANTMENT - MAGE
    // [REV_504e] Solid Alibi - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Your hero only takes 1 damage at a time
    //       until the start of your next turn.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [REV_601t] Frozen Touch - COST:2
    // - Set: REVENDRETH, Rarity: Common
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Infused</b>
    //       Deal 3 damage.
    //       Add a Frozen Touch to your hand.
    // --------------------------------------------------------

    // ------------------------------------- ENCHANTMENT - MAGE
    // [REV_841e2] Informed - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Your next Secret costs (0).
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
}

void RevendrethCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- SPELL - PALADIN
    // [REV_842] Promotion - COST:1
    // - Set: REVENDRETH, Rarity: Epic
    // --------------------------------------------------------
    // Text: Give a Silver Hand Recruit +3/+3 and <b>Taunt</b>.
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [REV_947] Muckborn Servant - COST:3 [ATK:2/HP:4]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> <b>Discover</b> a Paladin card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [REV_948] Service Bell - COST:3
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Discover</b> a Class card from your deck and
    //       draw all copies of it.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [REV_950] Divine Toll - COST:7
    // - Set: REVENDRETH, Rarity: Rare
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Shoot 5 rays at random minions.
    //       They give friendly minions +2/+2,
    //       and deal 2 damage to enemy minions.
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [REV_951] The Countess - COST:7 [ATK:7/HP:7]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck has no Neutral cards,
    //       add 3 <b>Legendary</b> Invitations to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [REV_952] Sinful Sous Chef - COST:1 [ATK:2/HP:1]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add 2 Silver Hand Recruits
    //       to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [REV_955] Stewart the Steward - COST:3 [ATK:3/HP:3]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give the next Silver Hand Recruit
    //       you summon +3/+3 and this <b>Deathrattle</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [REV_958] Buffet Biggun - COST:4 [ATK:2/HP:4]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two Silver Hand Recruits.
    //       <b>Infuse (3):</b> Give them +2 Attack and
    //       <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - INFUSE = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [REV_961] Elitist Snob - COST:5 [ATK:3/HP:4]
    // - Set: REVENDRETH, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> For each Paladin card in your hand,
    //       randomly gain <b>Divine Shield</b>, <b>Lifesteal</b>,
    //       <b>Rush</b>, or <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // - LIFESTEAL = 1
    // - RUSH = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ------------------------------------- LOCATION - PALADIN
    // [REV_983] Great Hall - COST:2
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: Set a minion's Attack and Health to 3.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [MAW_015] Jury Duty - COST:3
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: Summon two Silver Hand Recruits.
    //       Give your Silver Hand Recruits +1/+1.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [MAW_016] Order in the Court - COST:2
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: Reorder your deck from highest Cost to lowest Cost.
    //       Draw a card.
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [MAW_017] Class Action Lawyer - COST:2 [ATK:2/HP:3]
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck has no Neutral cards,
    //       set a minion's stats to 1/1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void RevendrethCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ---------------------------------- ENCHANTMENT - PALADIN
    // [REV_842e] Promoted - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: +3/+3.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [REV_842e2] Under New Leadership - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [REV_950e] Divine Toll - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [REV_951e] Guest of Honor - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Costs (0).
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [REV_951t] Legendary Invitation - COST:2
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Discover</b> a <b>Legendary</b> minion
    //       from another class. It costs (0).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [REV_955e] Open Position - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Your next Silver Hand Recruit carries on Stewart's legacy.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [REV_955e2] Stewart's Legacy - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: +3/+3.
    //       <b>Deathrattle:</b> Your next Silver Hand Recruit
    //       has this enchant.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [REV_958e] Served - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [REV_958t] Buffet Biggun - COST:4 [ATK:2/HP:4]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Infused.</b>
    //       <b>Battlecry:</b> Summon two Silver Hand Recruits.
    //       Give them +2 Attack and <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [REV_983e] Good Food - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Stats changed to 3/3.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [MAW_015e] Jury Summons - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [MAW_017e] Class Action - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: 1/1.
    // --------------------------------------------------------
}

void RevendrethCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- MINION - PRIEST
    // [REV_002] Suspicious Usher - COST:1 [ATK:1/HP:3]
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b>
    //       <b>Discover</b> a <b>Legendary</b> minion.
    //       If your opponent guesses your choice,
    //       they get a copy.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [REV_011] The Harvester of Envy - COST:3 [ATK:4/HP:3]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you play a card copied from the opponent,
    //       steal the original.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [REV_246] Mysterious Visitor - COST:2 [ATK:2/HP:3]
    // - Set: REVENDRETH, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Reduce the Cost of cards copied
    //       from your opponent by (2).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [REV_247] Partner in Crime - COST:4 [ATK:2/HP:5]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a copy of this minion
    //       at the end of your turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [REV_248] Boon of the Ascended - COST:4
    // - Set: REVENDRETH, Rarity: Epic
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Give a minion +2 Health.
    //       Summon a Kyrian with its stats and <b>Taunt</b>.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [REV_249] The Light! It Burns! - COST:1
    // - Set: REVENDRETH, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Deal damage to a minion equal to its Attack.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [REV_250] Pelagos - COST:3 [ATK:1/HP:6]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you cast a spell on a friendly minion,
    //       set its Attack and Health to the higher of the two.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [REV_252] Clean the Scene - COST:5
    // - Set: REVENDRETH, Rarity: Rare
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Destroy all minions with 3 or less Attack.
    //      <b>Infuse (3):</b> 6 or less.
    // --------------------------------------------------------
    // GameTag:
    // - INFUSE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [REV_253] Identity Theft - COST:3
    // - Set: REVENDRETH, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: <b>Discover</b> a copy of a card from
    //       your opponent's hand and deck.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // -------------------------------------- LOCATION - PRIEST
    // [REV_290] Cathedral of Atonement - COST:3
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give a minion +2/+1 and draw a card.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [MAW_021] Clear Conscience - COST:3
    // - Set: REVENDRETH, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Give a friendly minion +2/+3 and
    //       "Only you can target this with spells and Hero Powers."
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [MAW_022] Incriminating Psychic - COST:4 [ATK:2/HP:6]
    // - Race: Dragon, Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Copy a random card
    //       from your opponent's hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [MAW_023] Theft Accusation - COST:1
    // - Set: REVENDRETH, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Choose a minion.
    //       Destroy it after you play a card
    //       copied from the opponent.
    // --------------------------------------------------------
}

void RevendrethCardsGen::AddPriestNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- ENCHANTMENT - PRIEST
    // [REV_011e] Copied From Opponent - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [REV_246e2] Mind Read - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [REV_247e] Alibi - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: At the end of your turn, summon a copy of this.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [REV_248e] Boon of the Ascended - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: +2 Health.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [REV_248t] Ascended Kyrian - COST:1 [ATK:1/HP:1]
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [REV_250e1] Pelagos' Blessing - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Stats set to the higher value.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [REV_250e2] Pelagos' Blessing - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Stats set to the higher value.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [REV_252t] Clean the Scene - COST:5
    // - Set: REVENDRETH, Rarity: Rare
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: <b>Infused</b>
    //       Destroy all minions with 6 or less Attack.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [REV_290e] Atoned - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: +2/+1.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [MAW_021e] Cleared Conscience - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: +2/+3 and "Can't be targeted by spells or Hero Powers".
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [MAW_021e2] In the Clear - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [MAW_023e] Theft Trial - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: When you play a card copied from your opponent,
    //       destroy the accused.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [MAW_023e2] Accused of Theft - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: When the accuser plays a card copied from their enemy,
    //       this minion dies.
    // --------------------------------------------------------
}

void RevendrethCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- LOCATION - ROGUE
    // [REV_750] Sinstone Graveyard - COST:2
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon a 1/1 <b>Stealthed</b> Ghost.
    //       <i>(Has +1/+1 for each other card you played
    //       this turn!)</i>
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [REV_825] Double Cross - COST:2
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your opponent spends
    //       all their Mana, draw two cards.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [REV_826] Private Eye - COST:4 [ATK:3/HP:4]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Cast a <b>Secret</b> from your deck.
    //       <b>Combo:</b> Cast 2 instead.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - COMBO = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [REV_827] Sticky Situation - COST:2
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After your opponent casts a spell,
    //       summon a 3/4 Spider with <b>Stealth</b>.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [REV_828] Kidnap - COST:2
    // - Set: REVENDRETH, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After your opponent plays a minion,
    //       stuff it in a 0/4 Sack.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [REV_829] Halkias - COST:4 [ATK:5/HP:4]
    // - Race: Elemental, Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Stealth</b>.
    //       <b>Deathrattle:</b> Store Halkias's soul
    //       inside of a friendly <b>Secret</b>.
    //       It resummons Halkias when triggered.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [REV_938] Door of Shadows - COST:1
    // - Set: REVENDRETH, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Draw a spell.
    //       <b>Infuse (2):</b> Add a temporary copy of it
    //       to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - INFUSE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [REV_939] Serrated Bone Spike - COST:2
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 3 damage to a minion.
    //       If it dies, your next card this turn costs (2) less.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [REV_940] Necrolord Draka - COST:4 [ATK:3/HP:4]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Equip a 1/3 Dagger.
    //       <i>(+1 Attack for each other card
    //       you played this turn!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [REV_959] Ghastly Gravedigger - COST:3 [ATK:4/HP:3]
    // - Set: REVENDRETH, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a <b>Secret</b>,
    //       choose a card in your opponent's hand
    //       to shuffle into their deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [MAW_018] Perjury - COST:2
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your turn starts,
    //       <b>Discover</b> and cast a <b>Secret</b>
    //       from another class.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // - SECRET = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [MAW_019] Murder Accusation - COST:2
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: Choose a minion.
    //       Destroy it after another enemy minion dies.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [MAW_020] Scribbling Stenographer - COST:6 [ATK:4/HP:4]
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b>. Costs (1) less for each card
    //       you've played this turn.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
}

void RevendrethCardsGen::AddRogueNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- MINION - ROGUE
    // [REV_750t2] Haunted Conscience - COST:1 [ATK:1/HP:1]
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [REV_827t] Tomb Crawler - COST:3 [ATK:3/HP:4]
    // - Race: Beast, Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [REV_828e] Kidnapper's Sack - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: {0} is inside the sack!
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [REV_828t] Kidnapper's Sack - COST:1 [ATK:0/HP:4]
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Return your opponent's
    //       kidnapped minion to their hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [REV_829e] Shard of Halkias - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Contains Halkias' soul.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [REV_938t] Door of Shadows - COST:1
    // - Set: REVENDRETH, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: <b>Infused</b>
    //       Draw a spell.
    //       Add a temporary copy of it to your hand.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [REV_938te] Shadowstalking - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Discard this at the end of your turn.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [REV_939e] Serrated - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: The next card you play this turn costs (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_SILENCED = 1
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [REV_939e2] Serrated - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Your next card this turn costs (2) less.
    // --------------------------------------------------------

    // ----------------------------------------- WEAPON - ROGUE
    // [REV_940t] Maldraxxus Dagger - COST:1
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [MAW_019e] Murder Trial - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: When another enemy minion dies, destroy the accused.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [MAW_019e2] Accused of Murder - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: When an enemy minion of the accuser dies,
    //       this minion dies.
    // --------------------------------------------------------
}

void RevendrethCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- SPELL - SHAMAN
    // [REV_517] Criminal Lineup - COST:8
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: Choose a friendly minion.
    //       Summon 3 copies of it.
    //       <b>Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [REV_838] Gigantotem - COST:10 [ATK:8/HP:8]
    // - Race: Totem, Set: REVENDRETH, Rarity: Epic
    // --------------------------------------------------------
    // Text: Costs (1) less for each Totem you've summoned this game.
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - SHAMAN
    // [REV_917] Carving Chisel - COST:2
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: After your hero attacks, summon a random basic Totem.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [REV_920] Convincing Disguise - COST:1
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: Transform a friendly minion into one
    //       that costs (2) more.
    //       <b>Infuse (4):</b> Transform all friendly minions
    //       instead.
    // --------------------------------------------------------
    // GameTag:
    // - INFUSE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [REV_921] The Stonewright - COST:4 [ATK:5/HP:4]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> For the rest of the game,
    //       your Totems have +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // -------------------------------------- LOCATION - SHAMAN
    // [REV_923] Muck Pools - COST:1
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: Transform a friendly minion into one that costs (1) more.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [REV_924] Primordial Wave - COST:3
    // - Set: REVENDRETH, Rarity: Epic
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Transform enemy minions into ones that cost (1) less
    //       and friendly minions into ones that cost (1) more.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [REV_925] Baroness Vashj - COST:4 [ATK:3/HP:6]
    // - Race: Naga, Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: If this would transform into a minion,
    //       summon that minion instead.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [REV_935] Party Favor Totem - COST:3 [ATK:0/HP:3]
    // - Race: Totem, Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn, summon a random basic Totem.
    //       <b>Infuse (2):</b> Summon two instead.
    // --------------------------------------------------------
    // GameTag:
    // - INFUSE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [REV_936] Crud Caretaker - COST:4 [ATK:1/HP:1]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry</b>: Summon a 3/5 Elemental
    //       with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [MAW_003] Totemic Evidence - COST:1
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: Choose a basic Totem and summon it.
    //       <b>Infuse (3 Totems):</b> Summon all 4 instead.
    // --------------------------------------------------------
    // GameTag:
    // - INFUSE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [MAW_005] Framester - COST:3 [ATK:3/HP:3]
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Shuffle 3 'Framed' cards
    //       into the opponent's deck.
    //       When drawn, they <b>Overload</b> for (2).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [MAW_030] Torghast Custodian - COST:8 [ATK:6/HP:10]
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> For each enemy minion,
    //       randomly gain <b>Rush</b>, <b>Divine Shield</b>,
    //       or <b>Windfury</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // - RUSH = 1
    // - WINDFURY = 1
    // --------------------------------------------------------
}

void RevendrethCardsGen::AddShamanNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- SPELL - SHAMAN
    // [REV_920t] Convincing Disguise - COST:1
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Infused</b>
    //       Transform all friendly minions
    //       into random ones that cost (2) more.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [REV_921e] Living Stone - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Your Totems have +2 Attack.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [REV_935t] Party Favor Totem - COST:3 [ATK:0/HP:3]
    // - Race: Totem, Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Infused</b> At the end of your turn,
    //       summon two random basic Totems.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [REV_936t] Untreated Filth - COST:4 [ATK:3/HP:5]
    // - Race: Elemental, Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [REV_942e2] Relics of Old - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Your next spell this turn casts twice.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [MAW_003t] Totemic Evidence - COST:1
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Infused</b>
    //       Summon all 4 basic Totems.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [MAW_005t] Framed - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Casts When Drawn</b>
    //       <b>Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // - TOPDECK = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [MAW_030e2] Crawling - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Rush</b>.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [MAW_030e3] Sweeping - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [MAW_030e4] Formidable - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Windfury</b>.
    // --------------------------------------------------------
}

void RevendrethCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- SPELL - WARLOCK
    // [REV_239] Suffocating Shadows - COST:3
    // - Set: REVENDRETH, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: When you play or discard this,
    //       destroy a random enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - InvisibleDeathrattle = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [REV_240] Tome Tampering - COST:3
    // - Set: REVENDRETH, Rarity: Epic
    // --------------------------------------------------------
    // Text: Shuffle 1-Cost copies of cards in your hand
    //       into your deck, then discard your hand.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [REV_242] Flustered Librarian - COST:1 [ATK:1/HP:3]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: Has +1 Attack for each Imp you control.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [REV_244] Mischievous Imp - COST:4 [ATK:3/HP:3]
    // - Race: Demon, Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a copy of this.
    //       <b>Infuse (3):</b> Summon two copies instead.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - INFUSE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [REV_245] Impending Catastrophe - COST:2
    // - Set: REVENDRETH, Rarity: Epic
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Draw a card. Repeat for each Imp you control.
    // --------------------------------------------------------

    // ------------------------------------- LOCATION - WARLOCK
    // [REV_371] Vile Library - COST:2
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give a minion +1/+1 for each Imp you control.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [REV_372] Shadow Waltz - COST:5
    // - Set: REVENDRETH, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Summon a 3/5 Shadow with <b>Taunt</b>.
    //       If a minion died this turn, summon another.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [REV_373] Lady Darkvein - COST:5 [ATK:3/HP:6]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two 2/1 Shades.
    //       Each gains a <b>Deathrattle</b> to cast
    //       your last Shadow spell.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [REV_374] Shadowborn - COST:3 [ATK:3/HP:3]
    // - Race: Beast, Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Reduce the Cost of
    //       the highest Cost Shadow spell in your hand by (3).
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [REV_835] Imp King Rafaam - COST:6 [ATK:6/HP:6]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Resurrect four friendly Imps.
    //       <b>Infuse (5):</b> Give your Imps +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - INFUSE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [MAW_000] Imp-oster - COST:2 [ATK:1/HP:1]
    // - Race: Demon, Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a friendly Imp.
    //       Transform into a copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [MAW_001] Arson Accusation - COST:2
    // - Set: REVENDRETH, Rarity: Common
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Choose a minion.
    //       Destroy it after your hero takes damage.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [MAW_002] Habeas Corpses - COST:3
    // - Set: REVENDRETH, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: <b>Discover</b> a friendly minion to resurrect
    //       and give it <b>Rush</b>.
    //       It dies at the end of turn.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
}

void RevendrethCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [REV_239e] Suffocation - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Costs (3) less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [REV_240e] Cost Curse - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Costs (1).
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [REV_244t] Mischievous Imp - COST:4 [ATK:3/HP:3]
    // - Race: Demon, Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Infused Battlecry:</b> Summon two copies of this.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [REV_371e] Imp Power - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [REV_372t] Twirling Shadow - COST:5 [ATK:3/HP:5]
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [REV_373e] Dark Bidding - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Spell: {0} is inside!
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [REV_373t] Shadow Manifestation - COST:1 [ATK:2/HP:1]
    // - Set: REVENDRETH
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [REV_374e] In Shadow - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Costs (3) less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [REV_835e] Impfused Anima - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [REV_835t] Imp King Rafaam - COST:6 [ATK:6/HP:6]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Infused.</b>
    //       <b>Battlecry:</b> Summon four friendly Imps
    //       that died this game. Give your Imps +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [MAW_001e] Arson Trial - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: When your hero takes damage, destroy the accused.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [MAW_001e2] Accused of Arson - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: When the accuser takes damage, this minion dies.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [MAW_002e] Habeas Corpse - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Dies at the end of turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
}

void RevendrethCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - WARRIOR
    // [REV_006] Suspicious Pirate - COST:3 [ATK:3/HP:4]
    // - Race: Pirate, Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a weapon.
    //       If your opponent guesses your choice, they get a copy.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [REV_316] Remornia, Living Blade - COST:7 [ATK:4/HP:10]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       After this attacks, equip it.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - RUSH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [REV_332] Anima Extractor - COST:2 [ATK:1/HP:4]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever a friendly minion takes damage,
    //       give a random minion in your hand +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [REV_334] Burden of Pride - COST:4
    // - Set: REVENDRETH, Rarity: Epic
    // --------------------------------------------------------
    // Text: Summon three 1/3 Jailers with <b>Taunt</b>.
    //       If you have 20 or less Health, give them +1/+1.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [REV_337] Riot! - COST:2
    // - Set: REVENDRETH, Rarity: Epic
    // --------------------------------------------------------
    // Text: Your minions can't be reduced below 1 Health
    //       this turn. They each attack a random enemy minion.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [REV_930] Crazed Wretch - COST:2 [ATK:1/HP:4]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: Has +2 Attack and <b>Charge</b> while damaged.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [REV_931] Conqueror's Banner - COST:2
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: Reveal a card from each player's deck, three times.
    //       Draw any of yours that cost more.
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [REV_933] Imbued Axe - COST:3
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: After your hero attacks,
    //       give your damaged minions +1/+2.
    //       <b>Infuse (2):</b> +2/+2 instead.
    // --------------------------------------------------------
    // GameTag:
    // - INFUSE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [REV_934] Decimator Olgra - COST:6 [ATK:3/HP:7]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain +1/+1 for each damaged minion,
    //       then attack all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------- LOCATION - WARRIOR
    // [REV_990] Sanguine Depths - COST:1
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 1 damage to a minion and give it +2 Attack.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [MAW_027] Call to the Stand - COST:1
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: Your opponent summons a random minion from their hand.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [MAW_028] Mawsworn Bailiff - COST:5 [ATK:4/HP:4]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b><b>Taunt</b>.</b>
    //       <b>Battlecry:</b> If you have 4 or more Armor,
    //       gain +4/+4.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [MAW_029] Weapons Expert - COST:3 [ATK:3/HP:2]
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you have a weapon equipped,
    //       give it +1/+1. Otherwise, draw a weapon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void RevendrethCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [REV_316e] Remornia's Will - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Has the stats of Remornia.
    // --------------------------------------------------------
    // GameTag:
    // - ENCHANTMENT_INVISIBLE = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [REV_316t] Remornia, Living Blade - COST:7
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After your hero attacks,
    //       return this to the battlefield.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [REV_332e] Extracted - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [REV_334e] Empowered - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - ENCHANTMENT_INVISIBLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [REV_334t] Sanguine Jailer - COST:2 [ATK:1/HP:3]
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [REV_337e] Riot! - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Can't be reduced below 1 Health this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [REV_337e2] Riot! - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Your minions can't be reduced below
    //       1 Health this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [REV_930e] Angry - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Charge</b>.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [REV_933e] Thirst for Blood - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [REV_933e2] Thirst for Blood - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [REV_933t] Imbued Axe - COST:3
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Infused</b>
    //       After your hero attacks,
    //       give your damaged minions +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [REV_934e] Bloodthirsty - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [REV_990e] Sinfall Boon - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [MAW_028e2] This Man Is Charged! - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: +4/+4.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [MAW_029e2] Sharpened - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
}

void RevendrethCardsGen::AddDemonHunter(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------ SPELL - DEMONHUNTER
    // [REV_506] Sinful Brand - COST:1
    // - Set: REVENDRETH, Rarity: Epic
    // --------------------------------------------------------
    // Text: Brand an enemy minion.
    //       Whenever it takes damage,
    //       deal 2 damage to the enemy hero.
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [REV_507] Dispose of Evidence - COST:0
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give your hero +3 Attack this turn.
    //       Choose a card in your hand to shuffle into your deck.
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [REV_508] Relic of Dimensions - COST:5
    // - Set: REVENDRETH, Rarity: Epic
    // --------------------------------------------------------
    // Text: Draw two cards and reduce their Cost by (1).
    //       Improve your future Relics.
    // --------------------------------------------------------

    // ----------------------------------- WEAPON - DEMONHUNTER
    // [REV_509] Magnifying Glaive - COST:3
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: After your hero attacks,
    //       draw until you have 3 cards.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [REV_510] Kryxis the Voracious - COST:4 [ATK:7/HP:7]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry</b>: Discard your hand.
    //       <b>Deathrattle:</b> Draw 3 cards.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [REV_511] Bibliomite - COST:2 [ATK:5/HP:4]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry</b>: Choose a card in your hand
    //       to shuffle into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [REV_834] Relic of Extinction - COST:1
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 1 damage to a random enemy minion, twice.
    //       Improve your future Relics.
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [REV_937] Artificer Xy'mox - COST:8 [ATK:8/HP:8]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> and cast a Relic.
    //       <b>Infuse (5):</b> Cast all three instead.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - INFUSE = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------- LOCATION - DEMONHUNTER
    // [REV_942] Relic Vault - COST:2
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: The next Relic you play this turn casts twice.
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [REV_943] Relic of Phantasms - COST:3
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon two 1/1 Spirits.
    //       Improve your future Relics.
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [MAW_008] Sightless Magistrate - COST:4 [ATK:5/HP:4]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Both players draw
    //       until they have 5 cards.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [MAW_012] All Fel Breaks Loose - COST:5
    // - Set: REVENDRETH, Rarity: Common
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Summon a friendly Demon that died this game.
    //       <b>Infuse (3 Demons):</b> Summon three instead.
    // --------------------------------------------------------
    // RefTag:
    // - INFUSE = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [MAW_014] Prosecutor Mel'tranix - COST:4 [ATK:2/HP:6]
    // - Race: Demon, Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your opponent can only play
    //       their left- and right-most cards on their next turn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void RevendrethCardsGen::AddDemonHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [REV_506e] Branded - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Whenever this takes damage,
    //       deal 2 damage to your hero.
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [REV_506e2] Branded - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Costs (1) more.
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [REV_507e] Dispose of Evidence - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: +3 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [REV_508e] Dimensional - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Reduced Cost.
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [REV_937t] Artificer Xy'mox - COST:8 [ATK:8/HP:8]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Infused</b>
    //       <b>Battlecry:</b> Cast all three Relics.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [REV_942e] Relic Empowerment - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Your Relics cast twice.
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [REV_943t] Fleeting Spirit - COST:1 [ATK:1/HP:1]
    // - Set: REVENDRETH
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [MAW_012t] All Fel Breaks Loose - COST:5
    // - Set: REVENDRETH, Rarity: Common
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: <b>Infused</b>
    //       Summon three friendly Demons that died this game.
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [MAW_014e2] Literally Unplayable - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: You can only play the left and right-most cards
    //       in your hand.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
}

void RevendrethCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [REV_012] Bog Beast - COST:6 [ATK:3/HP:6]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Summon a 2/4 Muckmare
    //       with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("REV_012t", SummonSide::DEATHRATTLE));
    cards.emplace("REV_012", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [REV_013] Stoneborn Accuser - COST:5 [ATK:5/HP:5]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Infuse (5):</b>
    //       Gain "<b>Battlecry:</b> Deal 5 damage."
    // --------------------------------------------------------
    // GameTag:
    // - INFUSE = 1
    // --------------------------------------------------------
    // RefTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.numMinionsToInfuse = 5;
    cardDef.property.infusedCardID = "REV_013t";
    cards.emplace("REV_013", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [REV_014] Red Herring - COST:7 [ATK:3/HP:12]
    // - Race: Beast, Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       Your non-Red Herring minions have <b>Stealth</b>.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_015] Masked Reveler - COST:6 [ATK:4/HP:4]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Deathrattle:</b> Summon a 2/2 copy of
    //       another minion in your deck.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_016] Crooked Cook - COST:2 [ATK:1/HP:4]
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       if you dealt 3 or more damage to the enemy hero,
    //       draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_017] Insatiable Devourer - COST:9 [ATK:4/HP:4]
    // - Set: REVENDRETH, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Devour an enemy minion and
    //       gain its stats.
    //       <b>Infuse (5):</b> And its neighbors.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - INFUSE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_018] Prince Renathal - COST:3 [ATK:3/HP:4]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Your deck size and starting Health are 40.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    // RefTag:
    // - START_OF_GAME = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_019] Famished Fool - COST:5 [ATK:3/HP:5]
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a card.
    //       <b>Infuse (4):</b> Draw 3 instead.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - INFUSE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cardDef.property.numMinionsToInfuse = 4;
    cardDef.property.infusedCardID = "REV_019t";
    cards.emplace("REV_019", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [REV_020] Dinner Performer - COST:3 [ATK:2/HP:3]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a random minion
    //       from your deck that you can afford to play.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_021] Kael'thas Sinstrider - COST:8 [ATK:4/HP:7]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Every third minion you play each turn costs (0).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AURA = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_022] Murloc Holmes - COST:3 [ATK:3/HP:4]
    // - Race: Murloc, Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Solve 3 Clues about
    //       your opponent's cards to get copies of them.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_023] Demolition Renovator - COST:4 [ATK:4/HP:4]
    // - Set: REVENDRETH, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy an enemy location.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_238] Theotar, the Mad Duke - COST:5 [ATK:3/HP:3]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a card
    //       in each player's hand and swap them.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_251] Sinrunner - COST:5 [ATK:6/HP:5]
    // - Race: Beast, Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Destroy a random enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(ComplexTask::DestroyRandomEnemyMinion(1));
    cards.emplace("REV_251", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [REV_308] Maze Guide - COST:2 [ATK:1/HP:1]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry</b>: Summon a random 2-Cost minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<RandomMinionTask>(
        TagValues{ { GameTag::COST, 2, RelaSign::EQ } }));
    cardDef.power.AddPowerTask(std::make_shared<SummonStackTask>());
    cards.emplace("REV_308", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [REV_338] Dredger Staff - COST:1 [ATK:1/HP:2]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give minions in your hand +1 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "REV_338e", EntityType::MINIONS_HAND));
    cards.emplace("REV_338", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [REV_351] Roosting Gargoyle - COST:2 [ATK:2/HP:3]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly Beast +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_370] Party Crasher - COST:8 [ATK:7/HP:9]
    // - Set: REVENDRETH, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose an enemy minion.
    //       Throw a random minion from your hand at it.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_375] Stoneborn General - COST:10 [ATK:8/HP:8]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Deathrattle:</b> Summon an 8/8 Gravewing
    //       with <b>Rush</b>. 
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_377] Invitation Courier - COST:3 [ATK:3/HP:4]
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: After a card is added to your hand
    //       from another class, copy it.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_378] Forensic Duster - COST:3 [ATK:3/HP:4]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your opponent's minions cost
    //       (1) more next turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_837] Muck Plumber - COST:5 [ATK:5/HP:5]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: All minions cost (2) more.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_839] Sinstone Totem - COST:1 [ATK:0/HP:3]
    // - Race: Totem, Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: At the end of your turn, gain +1 Health.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_841] Anonymous Informant - COST:2 [ATK:2/HP:3]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> The next <b>Secret</b>
    //       you play costs (0).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_843] Sinfueled Golem - COST:7 [ATK:2/HP:2]
    // - Set: REVENDRETH, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Infuse (3):</b> Gain stats equal to
    //       the Attack of the minions that <b>Infused</b> this.
    // --------------------------------------------------------
    // GameTag:
    // - INFUSE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_845] Volatile Skeleton - COST:2 [ATK:2/HP:2]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 2 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_900] Scuttlebutt Ghoul - COST:4 [ATK:2/HP:5]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>.
    //       <b>Battlecry:</b> If you control a <b>Secret</b>,
    //       summon a copy of this.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_901] Dispossessed Soul - COST:4 [ATK:4/HP:5]
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a location,
    //       <b>Discover</b> a copy of a card in your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_906] Sire Denathrius - COST:10 [ATK:10/HP:10]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>.
    //       <b>Battlecry:</b> Deal 5 damage amongst enemies.
    //       <b>Endlessly Infuse (1):</b> Deal 1 more.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - INFUSE = 1
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_916] Creepy Painting - COST:3 [ATK:0/HP:6]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: After another minion dies, become a copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_945] Sketchy Stranger - COST:2 [ATK:2/HP:2]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a <b>Secret</b>
    //       from another class.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_946] Steamcleaner - COST:5 [ATK:5/HP:5]
    // - Race: Mechanical, Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy All cards in both players'
    //       decks that didn't start there.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_956] Priest of the Deceased - COST:2 [ATK:2/HP:3]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Infuse (3):</b> Gain +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - INFUSE = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.numMinionsToInfuse = 3;
    cardDef.property.infusedCardID = "REV_956t";
    cards.emplace("REV_956", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [REV_957] Murlocula - COST:4 [ATK:3/HP:4]
    // - Race: Murloc, Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    //       <b>Infuse (4):</b> This costs (0).
    // --------------------------------------------------------
    // GameTag:
    // - INFUSE = 1
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.numMinionsToInfuse = 4;
    cardDef.property.infusedCardID = "REV_957t";
    cards.emplace("REV_957", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [REV_960] Ashen Elemental - COST:3 [ATK:2/HP:4]
    // - Race: Elemental, Set: REVENDRETH, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Whenever your opponent draws
    //       a card next turn, they take 2 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [MAW_004] Soul Seeker - COST:5 [ATK:3/HP:3]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Swap this with a random minion
    //       from your opponent's deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [MAW_031] Afterlife Attendant - COST:3 [ATK:3/HP:4]
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: Your <b>Infuse</b> cards also <b>Infuse</b>
    //       while in your deck.
    // --------------------------------------------------------
    // GameTag:
    // - INFUSE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [MAW_032] Tight-Lipped Witness - COST:3 [ATK:2/HP:5]
    // - Set: REVENDRETH, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Secrets</b> can't be revealed.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [MAW_033] Sylvanas, the Accused - COST:6 [ATK:5/HP:5]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy an enemy minion.
    //       <b>Infuse (7):</b> Take control of it instead.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - INFUSE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [MAW_034] The Jailer - COST:10 [ATK:10/HP:10]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy your deck.
    //       For the rest of the game, your minions are <b>Immune</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------
}

void RevendrethCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [REV_012t] Muckmare - COST:3 [ATK:2/HP:4]
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("REV_012t", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [REV_013t] Stoneborn Accuser - COST:5 [ATK:5/HP:5]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Infused</b>
    //       <b>Battlecry:</b> Deal 5 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 5));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("REV_013t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [REV_015t] Masked - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: 2/2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [REV_016e] Suspicious Soup - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [REV_017e] Satiated - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Increased Stats
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_017t] Insatiable Devourer - COST:9 [ATK:4/HP:4]
    // - Set: REVENDRETH, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Infused</b>
    //       <b>Battlecry:</b> Devour an enemy minion and
    //       its neighbors to gain their stats.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_019t] Famished Fool - COST:5 [ATK:3/HP:5]
    // - Set: REVENDRETH, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Infused</b>
    //       <b>Battlecry:</b> Draw 3 cards.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(3));
    cards.emplace("REV_019t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [REV_021e] Sinstrider - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Costs (0).
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [REV_338e] Carving Time - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: +1 Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("REV_338e"));
    cards.emplace("REV_338e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [REV_351e] Invigorated - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_375t] Gravewing - COST:8 [ATK:8/HP:8]
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [REV_378e] Dusting - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Your minions cost (1) more this turn.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [REV_378e2] Discovered! - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Costs (1) more.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [REV_515e] Cosmic Power - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [REV_837e] Yuck! - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Costs (2) more.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [REV_839e] Sinful Stones - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Increased Health.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [REV_841e] Informed - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Your next Secret costs (0).
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [REV_843e] Animated - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_843t] Sinfueled Golem - COST:7 [ATK:2/HP:2]
    // - Set: REVENDRETH, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Infused</b>
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_906t] Sire Denathrius - COST:10 [ATK:10/HP:10]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>.
    //       <b>Battlecry:</b> Deal {1} damage amongst enemies.
    //       <b>Endlessly Infuse ({0}):</b> Deal 1 more.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - INFUSE = 1
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [REV_956t] Priest of the Deceased - COST:2 [ATK:4/HP:5]
    // - Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Infused</b>
    //       <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("REV_956t", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [REV_957t] Murlocula - COST:0 [ATK:3/HP:4]
    // - Race: Murloc, Set: REVENDRETH, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Infused Lifesteal</b>
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("REV_957t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [REV_960e] Ashy - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Whenever your opponent draws a card next turn,
    //       they take 2 damage.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [REV_COIN1] The Coin - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Gain 1 Mana Crystal this turn only.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [REV_COIN2] The Coin - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Gain 1 Mana Crystal this turn only.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [MAW_031e] Afterlife - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Your <b>Infuse</b> cards also <b>Infuse</b>
    //       in your deck.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [MAW_033t] Sylvanas, the Accused - COST:6 [ATK:5/HP:5]
    // - Set: REVENDRETH, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Infused</b>
    //       <b>Battlecry:</b> Take control of an enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [MAW_034e] Mawsworn - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Your minions are <b>Immune</b>
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [MAW_034e2] Mawsworn - COST:0
    // - Set: REVENDRETH
    // --------------------------------------------------------
    // Text: Can't die.
    // --------------------------------------------------------
}

void RevendrethCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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