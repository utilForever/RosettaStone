// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/CardSets/AlteracValleyCardsGen.hpp>
#include <Rosetta/PlayMode/Cards/CardPowers.hpp>

namespace RosettaStone::PlayMode
{
void AlteracValleyCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ HERO - HUNTER
    // [AV_113] Beaststalker Tavish - COST:6
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> and
    //       cast 2 Improved <b>Secrets</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // -------------------------------------------- HERO - MAGE
    // [AV_200] Magister Dawngrasp - COST:7
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Recast a spell from
    //       each spell school you've cast this game.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- HERO - WARRIOR
    // [AV_202] Rokara, the Valorous - COST:7
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Equip a 5/2 Unstoppable Force.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------- HERO - ROGUE
    // [AV_203] Shadowcrafter Scabbs - COST:8
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Return all minions to
    //       their owner's hands. Summon two 4/2 Shadows
    //       with <b>Stealth</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ------------------------------------- HERO - DEMONHUNTER
    // [AV_204] Kurtrus, Demon-Render - COST:6
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two 1/4 Demons with <b>Rush</b>.
    //       <i>(Improved by your hero attacks this game.)</i>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ------------------------------------------- HERO - DRUID
    // [AV_205] Wildheart Guff - COST:5
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Set your maximum Mana to 20.
    //       Gain an empty Mana Crystal. Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- HERO - PALADIN
    // [AV_206] Lightforged Cariel - COST:8
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 2 damage to all enemies.
    //       Equip a 2/5 Immovable Object.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ HERO - PRIEST
    // [AV_207] Xyrella, the Devout - COST:8
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Trigger the <b>Deathrattle</b>
    //       of every friendly minion that died this game.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------------------ HERO - SHAMAN
    // [AV_258] Bru'kan of the Elements - COST:8
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Call upon the power of two Elements!
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- HERO - WARLOCK
    // [AV_316] Dreadlich Tamsin - COST:6
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage to all minions.
    //       Shuffle 3 Rifts into your deck. Draw 3 cards.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------ HERO_POWER - HUNTER
    // [AV_113p] Summon Pet - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Summon an Animal Companion.
    // --------------------------------------------------------

    // -------------------------------------- HERO_POWER - MAGE
    // [AV_200p2] Arcane Burst - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Deal 2 damage.
    //       <b>Honorable Kill:</b> Gain +1 damage.
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // --------------------------------------------------------

    // ----------------------------------- HERO_POWER - WARRIOR
    // [AV_202p] Grand Slam - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Deal 2 damage.
    //       <b>Honorable Kill:</b> Gain 4 Armor.
    // --------------------------------------------------------
    // RefTag:
    // - HONORABLEKILL = 1
    // --------------------------------------------------------

    // ------------------------------------- HERO_POWER - ROGUE
    // [AV_203p] Sleight of Hand - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power.</b>
    //       The next card you play this turn costs (2) less.
    // --------------------------------------------------------

    // ------------------------------- HERO_POWER - DEMONHUNTER
    // [AV_204p] Ashfallen's Fury - COST:1
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       +2 Attack this turn.
    //       After a friendly minion attacks, refresh this.
    // --------------------------------------------------------

    // ------------------------------------- HERO_POWER - DRUID
    // [AV_205p] Nurture - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       <b>Choose One -</b> Draw a card;
    //       or Gain a Mana Crystal.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------

    // ----------------------------------- HERO_POWER - PALADIN
    // [AV_206p] Blessing of Queens - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Give a random minion in your hand +4/+4.
    // --------------------------------------------------------

    // ------------------------------------ HERO_POWER - PRIEST
    // [AV_207p] Holy Touch - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Restore 5 Health. Flip each turn.
    // --------------------------------------------------------

    // ------------------------------------ HERO_POWER - PRIEST
    // [AV_207p2] Void Spike - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Deal 5 damage. Flip each turn.
    // --------------------------------------------------------

    // ------------------------------------ HERO_POWER - SHAMAN
    // [AV_258p] Elemental Mastery - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Call upon a different Element every turn!
    // --------------------------------------------------------

    // ------------------------------------ HERO_POWER - SHAMAN
    // [AV_258p2] Water Invocation - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Restore 6 health to all friendly characters.
    //       Swaps each turn.
    // --------------------------------------------------------

    // ------------------------------------ HERO_POWER - SHAMAN
    // [AV_258pt] Earth Invocation - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Summon two 2/3 Elementals with <b>Taunt</b>.
    //       Swaps each turn.
    // --------------------------------------------------------

    // ------------------------------------ HERO_POWER - SHAMAN
    // [AV_258pt3] Fire Invocation - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Deal 6 damage to the enemy hero.
    //       Swaps each turn.
    // --------------------------------------------------------

    // ------------------------------------ HERO_POWER - SHAMAN
    // [AV_258pt4] Lightning Invocation - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Deal 2 damage to all enemy minions.
    //       Swaps each turn.
    // --------------------------------------------------------

    // ------------------------------------ HERO_POWER - SHAMAN
    // [AV_258pt7] Command the Elements - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Call upon a different Element every turn!
    // --------------------------------------------------------

    // ----------------------------------- HERO_POWER - WARLOCK
    // [AV_316hp] Chains of Dread - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Shuffle a Rift into your deck. Draw a card.
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - DRUID
    // [AV_210] Pathmaker - COST:3 [ATK:3/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Cast the other choice from
    //       the last <b>Choose One</b> spell you've cast.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [AV_211] Dire Frostwolf - COST:4 [ATK:4/HP:4]
    // - Race: Beast, Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //       <b>Deathrattle:</b> Summon a 2/2 Wolf with <b>Stealth</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("AV_211t", SummonSide::DEATHRATTLE));
    cards.emplace("AV_211", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [AV_291] Frostsaber Matriarch - COST:7 [ATK:4/HP:5]
    // - Race: Beast, Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Taunt</b>. Costs (1) less for each Beast
    //       you've summoned this game.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [AV_292] Heart of the Wild - COST:3
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion +2/+2, then give your Beasts +1/+1.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("AV_292e", EntityType::TARGET));
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::BEAST)) }));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("AV_292e2", EntityType::STACK));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("AV_292", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [AV_293] Wing Commander Mulverick - COST:4 [ATK:2/HP:5]
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Rush</b>.
    //       Your minions have "<b>Honorable Kill:</b>
    //       Summon a 2/2 Wyvern with <b>Rush</b>."
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AURA = 1
    // - RUSH = 1
    // --------------------------------------------------------
    // RefTag:
    // - HONORABLEKILL = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [AV_294] Clawfury Adept - COST:2 [ATK:2/HP:3]
    // - Race: Beast, Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give all other friendly characters
    //       +1 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [AV_295] Capture Coldtooth Mine - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Draw your lowest Cost card;
    //       or Draw your highest Cost card.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [AV_296] Pride Seeker - COST:3 [ATK:2/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your next <b>Choose One</b> card
    //       costs (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [AV_360] Frostwolf Kennels - COST:3
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn, summon a 2/2 Wolf
    //       with <b>Stealth</b>. Lasts 3 turns.
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "AV_211t", SummonSide::SPELL) };
    cardDef.power.GetTrigger()->lastTurn = 3;
    cards.emplace("AV_360", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [ONY_018] Boomkin - COST:5 [ATK:4/HP:5]
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Choose One - </b>Restore 8 Health to your hero;
    //       or Deal 4 damage.
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
    cardDef.property.chooseCardIDs = ChooseCardIDs{ "ONY_018t", "ONY_018t2" };
    cards.emplace("ONY_018", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [ONY_019] Raid Negotiator - COST:4 [ATK:3/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b>
    //       <b>Discover</b> a <b>Choose One</b> card.
    //       It has both effects combined.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [ONY_021] Scale of Onyxia - COST:7
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: Fill your board with 2/1 Whelps with <b>Rush</b>.
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("ONY_001t", 7, SummonSide::SPELL));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("ONY_021", cardDef);
}

void AlteracValleyCardsGen::AddDruidNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ SPELL - DRUID
    // [AV_205a] Ice Blossom - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Gain a Mana Crystal.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [AV_205pb] Valley Root - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Draw a card.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [AV_210e] Path Tracker - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Tracking Sub-Spell.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [AV_292e] Pack Alpha - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("AV_292e"));
    cards.emplace("AV_292e", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [AV_292e2] Pack Member - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("AV_292e2"));
    cards.emplace("AV_292e2", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [AV_293e] Air Strike - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Honorable Kill:</b> Summon a 2/2 Wyvern
    //       with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [AV_293t] Strike Wyvern - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [AV_294e] Snowcapped - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +1 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [AV_295a] More Resources - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Draw your lowest Cost card.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [AV_295b] More Supplies - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Draw your highest Cost card.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [AV_296e] Grown Up - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Your next Choose One card costs (2) less.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [AV_296e2] Proud - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [ONY_018t] Eyes of the Moon - COST:5
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Restore 8 Health to your hero.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<HealTask>(EntityType::HERO, 8));
    cards.emplace("ONY_018t", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [ONY_018t2] Heart of the Sun - COST:5
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Deal 4 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 4, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("ONY_018t2", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [ONY_019e] Decisive - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Your next <b>Choose One</b> card is combined.
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- SPELL - HUNTER
    // [AV_147] Dun Baldar Bunker - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn, draw a <b>Secret</b>
    //       and set its Cost to (1). Lasts 3 turns.
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = { ComplexTask::DrawCardFromDeck(
        1,
        SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsSecret()) },
        true) };
    cardDef.power.GetTrigger()->tasks.emplace_back(
        std::make_shared<AddEnchantmentTask>("AV_147e", EntityType::STACK));
    cardDef.power.GetTrigger()->lastTurn = 3;
    cards.emplace("AV_147", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [AV_224] Spring the Trap - COST:4
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 3 damage to a minion and cast a <b>Secret</b>
    //       from your deck. <b>Honorable Kill:</b> Cast 2.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - HONORABLEKILL = 1
    // - SECRET = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    cardDef.power.AddPowerTask(ComplexTask::CastSecretFromDeck());
    cardDef.power.AddHonorableKillTask(ComplexTask::CastSecretFromDeck());
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("AV_224", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [AV_226] Ice Trap - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your opponent casts a spell,
    //       return it to their hand instead. It costs (1) more.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - HUNTER
    // [AV_244] Bloodseeker - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Honorable Kill:</b> Gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddHonorableKillTask(
        std::make_shared<AddEnchantmentTask>("AV_244e", EntityType::WEAPON));
    cards.emplace("AV_244", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [AV_333] Revive Pet - COST:3
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: <b>Discover</b> a friendly Beast that died this game.
    //       Summon it.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [AV_334] Stormpike Battle Ram - COST:4 [ATK:4/HP:3]
    // - Race: Beast, Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Deathrattle:</b> Your next Beast costs (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddEnchantmentTask>("AV_334e2", EntityType::SOURCE));
    cards.emplace("AV_334", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [AV_335] Ram Tamer - COST:3 [ATK:4/HP:3]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a <b>Secret</b>,
    //       gain +1/+1 and <b>Stealth</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsControllingSecret()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                            "AV_335e", EntityType::SOURCE),
                        std::make_shared<SetGameTagTask>(
                            EntityType::SOURCE, GameTag::STEALTH, 1) }));
    cards.emplace("AV_335", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [AV_336] Wing Commander Ichman - COST:9 [ATK:5/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a Beast from your deck
    //       and give it <b>Rush</b>.
    //       If it kills a minion this turn, repeat.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [AV_337] Mountain Bear - COST:7 [ATK:5/HP:6]
    // - Race: Beast, Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Summon two 2/4 Cubs with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("AV_337t", 2, SummonSide::DEATHRATTLE));
    cards.emplace("AV_337", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [ONY_008] Furious Howl - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: Draw a card.
    //       Repeat until you have at least 3 cards.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [ONY_009] Pet Collector - COST:5 [ATK:4/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a Beast from your deck
    //       that costs (5) or less.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(ComplexTask::SummonRaceCostMinionFromDeck(
        Race::BEAST, 5, RelaSign::LEQ));
    cards.emplace("ONY_009", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [ONY_010] Dragonbane Shot - COST:3
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 2 damage.
    //       <b>Honorable Kill:</b> Add a Dragonbane Shot
    //       to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, true));
    cardDef.power.AddHonorableKillTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "ONY_010"));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("ONY_010", cardDef);
}

void AlteracValleyCardsGen::AddHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- SPELL - HUNTER
    // [AV_113t1] Improved Explosive Trap - COST:2
    // - Set: ALTERAC_VALLEY
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your hero is attacked,
    //       deal 3 damage to all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - SECRET = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [AV_113t2] Improved Freezing Trap - COST:2
    // - Set: ALTERAC_VALLEY
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When an enemy minion attacks,
    //       return it to its owner's hand. It costs (4) more.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - SECRET = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [AV_113t2e] Freezing - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (4) more.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [AV_113t3] Improved Snake Trap - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When one of your minions is attacked,
    //       summon three 2/2 Snakes.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - SECRET = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [AV_113t3t2] Snake - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Set: ALTERAC_VALLEY
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [AV_113t7] Improved Pack Tactics - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When a friendly minion is attacked,
    //       summon two 3/3 copies.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - SECRET = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [AV_113t8] Improved Open the Cages - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your turn starts, if you control
    //       two minions, summon two Animal Companions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - SECRET = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [AV_113t9] Improved Ice Trap - COST:2
    // - Set: ALTERAC_VALLEY
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your opponent casts a spell,
    //       return it to their hand instead. It costs (2) more.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - SECRET = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [AV_113t9e] Mega Frosty - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (2) more.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [AV_147e] Cloaked Secrets - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (1).
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::SetCost(1)));
    cards.emplace("AV_147e", cardDef);

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [AV_226e] Frosty - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (1) more.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [AV_244e] Bloodseeking - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(std::vector<std::shared_ptr<IEffect>>(
            { Effects::AttackN(1), Effects::DurabilityN(1) })));
    cards.emplace("AV_244e", cardDef);

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [AV_334e] Ready for Battle - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [AV_334e2] Battle Ready - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::HAND, EffectList{ Effects::ReduceCost(2) }));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition =
            std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::BEAST));
        aura->removeTrigger = { TriggerType::PLAY_MINION,
                                std::make_shared<SelfCondition>(
                                    SelfCondition::IsRace(Race::BEAST)) };
    }
    cards.emplace("AV_334e2", cardDef);

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [AV_335e] Sneaking Up - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("AV_335e"));
    cards.emplace("AV_335e", cardDef);

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [AV_336e] Frightful Pack - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: If this kills a minion this turn, summon a
    //       random Beast from your deck and give it <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [AV_337t] Mountain Cub - COST:3 [ATK:2/HP:4]
    // - Race: Beast, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("AV_337t", cardDef);

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [ONY_010e] Drakeshot - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ MINION - MAGE
    // [AV_114] Shivering Sorceress - COST:1 [ATK:2/HP:2]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Reduce the Cost of the highest
    //       Cost spell in your hand by (1).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [AV_115] Amplified Snowflurry - COST:2 [ATK:2/HP:3]
    // - Race: Elemental, Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your next Hero Power costs (0)
    //       and <b>Freezes</b> the target.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [AV_116] Arcane Brilliance - COST:4
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Add a copy of a 7, 8, 9, and 10-Cost spell
    //       in your deck to your hand.
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [AV_212] Siphon Mana - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Deal 2 damage. <b>Honorable Kill</b>: Reduce
    //       the Cost of spells in your hand by (1).
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [AV_218] Mass Polymorph - COST:7
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Transform all minions into 1/1 Sheep.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<TransformTask>(EntityType::ALL_MINIONS, "CS2_tk1"));
    cards.emplace("AV_218", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [AV_282] Build a Snowman - COST:3
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: Summon a 3/3 Snowman that <b>Freezes</b>.
    //       Add "Build a Snowbrute" to your hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("AV_282t"));
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "AV_282t2"));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("AV_282", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [AV_283] Rune of the Archmage - COST:9
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: Cast 20 Mana worth of Mage spells at enemies.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [AV_284] Balinda Stonehearth - COST:6 [ATK:5/HP:5]
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw 2 spells.
    //       Swap their Costs with this minion's stats.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [AV_290] Iceblood Tower - COST:10
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn, cast another spell
    //       from your deck. Lasts 3 turns.
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [ONY_006] Deep Breath - COST:5
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Deal 1 damage to a minion and its neighbors.
    //       (Improved by number of other spells in your hand.)
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [ONY_007] Haleh, Matron Protectorate - COST:8 [ATK:4/HP:12]
    // - Race: Dragon, Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you cast a spell,
    //       deal 4 damage randomly split among all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<EnqueueTask>(
        TaskList{
            std::make_shared<FilterStackTask>(SelfCondList{
                std::make_shared<SelfCondition>(SelfCondition::IsNotDead()) }),
            std::make_shared<RandomTask>(EntityType::ENEMIES, 1),
            std::make_shared<DamageTask>(EntityType::STACK, 1) },
        4, false) };
    cards.emplace("ONY_007", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [ONY_029] Drakefire Amulet - COST:10
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: <b>Tradeable</b>
    //       <b>Discover</b> 2 Dragons. Summon them.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // - TRADEABLE = 1
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddMageNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------- ENCHANTMENT - MAGE
    // [AV_114e] Shocking - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ------------------------------------- ENCHANTMENT - MAGE
    // [AV_115e5] Icy - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Your Hero Power costs (0) and
    //       <b>Freezes</b> the target.
    // --------------------------------------------------------

    // ------------------------------------- ENCHANTMENT - MAGE
    // [AV_212e] Kablow! - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [AV_282t] Snowman - COST:3 [ATK:3/HP:3]
    // - Race: Elemental, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Freeze</b> any character damaged by this minion.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("AV_282t", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [AV_282t2] Build a Snowbrute - COST:6
    // - Set: ALTERAC_VALLEY
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: Summon a 6/6 Snowbrute that <b>Freezes</b>.
    //       Add "Build a Snowgre" to your hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("AV_282t3"));
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "AV_282t4"));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("AV_282t2", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [AV_282t3] Snowbrute - COST:6 [ATK:6/HP:6]
    // - Race: Elemental, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Freeze</b> any character damaged by this minion.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("AV_282t3", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [AV_282t4] Build a Snowgre - COST:9
    // - Set: ALTERAC_VALLEY
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: Summon a 9/9 Snowgre that <b>Freezes</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("AV_282t5"));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("AV_282t4", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [AV_282t5] Snowgre - COST:9 [ATK:9/HP:9]
    // - Race: Elemental, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Freeze</b> any character damaged by this minion.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("AV_282t5", cardDef);

    // ------------------------------------- ENCHANTMENT - MAGE
    // [AV_284e] Arcane Swap - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Cost swapped.
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - PALADIN
    // [AV_213] Vitality Surge - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Draw a minion.
    //       Restore Health to your hero equal to its Cost.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [AV_338] Hold the Bridge - COST:3
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Give a minion +2/+1 and <b>Divine Shield</b>.
    //       It gains <b>Lifesteal</b> until end of turn.
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [AV_339] Templar Captain - COST:8 [ATK:8/HP:8]
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b>. After this attacks a minion,
    //       summon a 5/5 Defender with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [AV_340] Brasswing - COST:8 [ATK:9/HP:7]
    // - Race: Dragon, Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: At the end of your turn, deal 2 damage to all enemies.
    //       <b>Honorable Kill:</b> Restore 4 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - PALADIN
    // [AV_341] Cavalry Horn - COST:5
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon the lowest Cost minion
    //       in your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [AV_342] Protect the Innocent - COST:5
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon a 5/5 Defender with <b>Taunt</b>.
    //       If your hero was healed this turn, summon another.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [AV_343] Stonehearth Vindicator - COST:3 [ATK:3/HP:1]
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a spell that costs (3) or less.
    //       It costs (0) this turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [AV_344] Dun Baldar Bridge - COST:4
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you summon a minion, give it +2/+2.
    //       Lasts 3 turns.
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [AV_345] Saidan the Scarlet - COST:3 [ATK:2/HP:2]
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Rush.</b> Whenever this minion gains Attack or
    //       Health, double that amount <i>(wherever this is)</i>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - RUSH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [ONY_020] Stormwind Avenger - COST:3 [ATK:1/HP:5]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: After you cast a spell on this minion,
    //       it gains +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_CAST));
    cardDef.power.GetTrigger()->triggerSource =
        TriggerSource::SPELLS_CASTED_ON_THIS;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "ONY_020e", EntityType::SOURCE) };
    cards.emplace("ONY_020", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [ONY_022] Battle Vicar - COST:2 [ATK:1/HP:3]
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a Holy spell.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::HOLY_SPELL));
    cards.emplace("ONY_022", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [ONY_027] Ring of Courage - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Tradeable</b>
    //       Give a minion +1/+1. Repeat for each enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - TRADEABLE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("ONY_027e", EntityType::TARGET));
    cardDef.power.AddPowerTask(
        std::make_shared<CountTask>(EntityType::ENEMY_MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<EnqueueNumberTask>(
        TaskList{ std::make_shared<AddEnchantmentTask>("ONY_027e",
                                                       EntityType::TARGET) }));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("ONY_027", cardDef);
}

void AlteracValleyCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- WEAPON - PALADIN
    // [AV_146] The Immovable Object - COST:7
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: This doesn't lose Durability.
    //       Your hero takes half damage, rounded up.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [AV_146e] Tough - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Take half damage, rounded up.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [AV_146e2] Resilient Weapon - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: No durability loss.
    // --------------------------------------------------------
    // GameTag:
    // - ENCHANTMENT_INVISIBLE = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [AV_206pe] Blessing of Queens - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +4/+4.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [AV_338e] High Morale - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [AV_338e2] High Morale - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [AV_342t] Stormpike Defender - COST:5 [ATK:5/HP:5]
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [AV_343e] Stone Fortitude - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (3) less this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [AV_344e] Coldtooth Supplies - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [ONY_020e] En Garde! - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("ONY_020e"));
    cards.emplace("ONY_020e", cardDef);

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [ONY_027e] Heroic - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("ONY_027e"));
    cards.emplace("ONY_027e", cardDef);
}

void AlteracValleyCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- SPELL - PRIEST
    // [AV_315] Deliverance - COST:3
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Deal 3 damage to a minion.
    //       <b>Honorable Kill:</b> Summon a new 3/3 copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [AV_324] Shadow Word: Devour - COST:1
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Choose a minion.
    //       It steals 1 Health from ALL other minions.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [AV_325] Undying Disciple - COST:6 [ATK:3/HP:7]
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Deal damage equal to
    //       this minion's Attack to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [AV_326] Luminous Geode - COST:2 [ATK:1/HP:4]
    // - Race: Elemental, Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: After a friendly minion is healed, give it +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [AV_328] Spirit Guide - COST:5 [ATK:5/HP:5]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Draw a Holy spell and
    //       a Shadow spell.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [AV_329] Bless - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Give a minion +2 Health, then set its Attack
    //       to be equal to its Health.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [AV_330] Gift of the Naaru - COST:1
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Restore 3 Health to all characters.
    //       If any are still damaged, draw a card.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [AV_331] Najak Hexxen - COST:4 [ATK:1/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Take control of an enemy minion.
    //       <b>Deathrattle:</b> Give the minion back.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [AV_664] Stormpike Aid Station - COST:3
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       give your minions +2 Health. Lasts 3 turns.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [ONY_017] Horn of Wrathion - COST:3
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: Draw a minion. If it's a Dragon,
    //       summon two 2/1 Whelps with <b>Rush</b>.
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawMinionTask>(1, true));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::STACK, SelfCondList{ std::make_shared<SelfCondition>(
                               SelfCondition::IsRace(Race::DRAGON)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<SummonTask>("ONY_001t", 2,
                                                     SummonSide::SPELL) }));
    cards.emplace("ONY_017", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [ONY_026] Lightmaw Netherdrake - COST:4 [ATK:4/HP:4]
    // - Race: Dragon, Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Holy and
    //       a Shadow spell, deal 3 damage to all other minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE,
        SelfCondList{
            std::make_shared<SelfCondition>(
                SelfCondition::IsHoldingSpell(SpellSchool::HOLY)),
            std::make_shared<SelfCondition>(
                SelfCondition::IsHoldingSpell(SpellSchool::SHADOW)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<DamageTask>(
                  EntityType::ALL_MINIONS_NOSOURCE, 3) }));
    cards.emplace("ONY_026", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [ONY_028] Mi'da, Pure Light - COST:6 [ATK:4/HP:6]
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>, <b>Lifesteal</b>
    //       <b>Deathrattle:</b> Shuffle a Fragment into
    //       your deck that resummons Mi'da when drawn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - DIVINE_SHIELD = 1
    // - LIFESTEAL = 1
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddPriestNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- ENCHANTMENT - PRIEST
    // [AV_315e2] Salvation - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Attack and Health set to 3.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [AV_324e2] Superior - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Increased Health.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [AV_324e2b] Superior - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Increased Health.
    // --------------------------------------------------------
    // GameTag:
    // - ENCHANTMENT_INVISIBLE = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [AV_324e3] Inferior - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Reduced Health.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [AV_324eb] Inferior - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Reduced Health.
    // --------------------------------------------------------
    // GameTag:
    // - ENCHANTMENT_INVISIBLE = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [AV_326e] Illuminated - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [AV_329e] Blessed - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2 Health and this minion's Attack is equal to
    //       its Health.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [AV_329e2] Blessed - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2 Health.
    // --------------------------------------------------------
    // GameTag:
    // - ENCHANTMENT_INVISIBLE = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [AV_331e] Dark Concoction - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Give this back when Najak is destroyed.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [AV_331e2] Dark Concoction - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Took control of {0}.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [AV_664e2] Restored - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2 Health.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [ONY_028t] Fragment of Mi'da - COST:6
    // - Set: ALTERAC_VALLEY
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: <b>Casts When Drawn</b>
    //       Summon Mi'da, Pure Light.
    // --------------------------------------------------------
    // GameTag:
    // - TOPDECK = 1
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - ROGUE
    // [AV_201] Coldtooth Yeti - COST:3 [ATK:1/HP:5]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Gain +3 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddComboTask(
        std::make_shared<AddEnchantmentTask>("AV_201e", EntityType::SOURCE));
    cards.emplace("AV_201", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [AV_298] Wildpaw Gnoll - COST:5 [ATK:3/HP:5]
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       Costs (1) less for each card you've added to
    //       your hand from another class.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [AV_400] Snowfall Graveyard - COST:3
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Your <b>Deathrattles</b> trigger twice. Lasts 3 turns.
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- WEAPON - ROGUE
    // [AV_402] The Lobotomizer - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Honorable Kill:</b> Get a copy of the top card
    //       of your opponent's deck.
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [AV_403] Cera'thine Fleetrunner - COST:5 [ATK:5/HP:5]
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Replace your minions in hand and
    //       deck with ones from other classes.
    //       They cost (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [AV_405] Contraband Stash - COST:5
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Replay 5 cards from other classes
    //       you've played this game.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [AV_601] Forsaken Lieutenant - COST:2 [ATK:2/HP:2]
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b><b>Stealth</b>.</b>
    //       After you play a <b>Deathrattle</b> minion,
    //       become a 2/2 copy of it with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [AV_710] Reconnaissance - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Discover</b> a <b>Deathrattle</b> minion from
    //       another class. It costs (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [AV_711] Double Agent - COST:3 [ATK:3/HP:3]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a card from
    //       another class, summon a copy of this.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [ONY_030] SI:7 Smuggler - COST:3 [ATK:1/HP:3]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a random 1-cost minion
    //       (Upgraded for each SI:7 card you have played this game).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [ONY_031] Smokescreen - COST:8
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Draw 5 cards. Trigger any <b>Deathrattles</b> drawn.
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [ONY_032] Tooth of Nefarian - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 3 damage. <b>Honorable Kill:</b>
    //       <b>Discover</b> a spell from another class.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // - HONORABLEKILL = 1
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddRogueNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [AV_201e] Yeti Rage - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +3 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("AV_201e"));
    cards.emplace("AV_201e", cardDef);

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [AV_203pe] Sleight of Hand - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: The next card you play this turn costs (2) less.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [AV_203po] Sleight of Hand - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: The next card you play this turn costs (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [AV_203t] Shadow - COST:3 [ATK:4/HP:2]
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [AV_400e] Bunkered Up - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Deathrattles trigger twice.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [AV_403e2] Quickfooted - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [AV_601e] Forsaken - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: 2/2.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [AV_710e] Contracted - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- SPELL - SHAMAN
    // [AV_107] Glaciate - COST:6
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Discover</b> an 8-Cost minion.
    //       Summon and <b>Freeze</b> it.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [AV_250] Snowball Fight! - COST:3
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: Deal 1 damage to a minion and <b>Freeze</b> it.
    //       If it survives, repeat this on another minion!
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [AV_251] Cheaty Snobold - COST:3 [ATK:3/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: After an enemy is <b>Frozen</b>, deal 3 damage to it.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [AV_255] Snowfall Guardian - COST:6 [ATK:5/HP:5]
    // - Race: Elemental, Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Freeze</b> all other minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [AV_257] Bearon Gla'shear - COST:7 [ATK:6/HP:6]
    // - Race: Elemental, Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> For each Frost spell
    //       you've cast this game, summon a 3/4 Elemental
    //       that <b>Freezes</b>. <i>(@)</i>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [AV_259] Frostbite - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: Deal 3 damage. <b>Honorable Kill:</b>
    //       Your opponent's next spell costs (2) more.
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [AV_260] Sleetbreaker - COST:2 [ATK:3/HP:2]
    // - Race: Elemental, Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a Windchill to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "AV_266"));
    cards.emplace("AV_260", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [AV_266] Windchill - COST:1
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Freeze</b> a minion. Draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<FreezeTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("AV_266", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [AV_268] Wildpaw Cavern - COST:4
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn, summon a 3/4 Elemental
    //       that <b>Freezes</b>. Lasts 3 turns.
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "AV_257t", SummonSide::SPELL) };
    cardDef.power.GetTrigger()->lastTurn = 3;
    cards.emplace("AV_268", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [ONY_011] Don't Stand in the Fire! - COST:5
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Deal 10 damage randomly split among all enemy minions.
    //       <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [ONY_012] Spirit Mount - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion +1/+2 and <b>Spell Damage +1</b>.
    //       When it dies, summon a Spirit Raptor.
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [ONY_013] Bracing Cold - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: Restore 5 Health to your hero.
    //       Reduce the Cost of a random spell in your hand by (2).
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddShamanNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [AV_255e] Chilled - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [AV_257t] Frozen Stagguard - COST:3 [ATK:3/HP:4]
    // - Race: Elemental, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Freeze</b> any character damaged by this minion.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("AV_257t", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [AV_258t] Earth Invocation - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Summon two 2/3 Elementals with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [AV_258t2] Water Invocation - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Restore #6 Health to all friendly characters.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [AV_258t3] Fire Invocation - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Deal 6 damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [AV_258t4] Lightning Invocation - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Deal 2 damage to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [AV_258t6] Earthen Guardian - COST:2 [ATK:2/HP:3]
    // - Race: Elemental, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [ONY_012e] With Da Spirits - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +1/+2 and <b>Spell Damage +1</b>.
    //       <b>Deathrattle:</b> Summon a Spirit Raptor.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [ONY_012t] Bru'kan's Raptor - COST:2 [ATK:1/HP:2]
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [ONY_013e] Shivers - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - WARLOCK
    // [AV_277] Seeds of Destruction - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Shuffle four Rifts into your deck.
    //       They summon a 3/3 Dread Imp when drawn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::DECK, "AV_316t4", 4));
    cards.emplace("AV_277", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [AV_281] Felfire in the Hole! - COST:5
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Draw a spell and deal 2 damage to all enemies.
    //       If it's a Fel spell, deal 1 more.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawSpellTask>(1, true));
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ENEMIES, 2, true));
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::STACK, SelfCondList{ std::make_shared<SelfCondition>(
                               SelfCondition::IsFelSpell()) }));
    cardDef.power.AddPowerTask(
        std::make_shared<FlagTask>(true, TaskList{ std::make_shared<DamageTask>(
                                             EntityType::ENEMIES, 1, true) }));
    cards.emplace("AV_281", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [AV_285] Full-Blown Evil - COST:3
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Deal 5 damage randomly split among all enemy minions.
    //       Repeatable this turn.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<EnqueueTask>(
        TaskList{
            std::make_shared<FilterStackTask>(SelfCondList{
                std::make_shared<SelfCondition>(SelfCondition::IsNotDead()) }),
            std::make_shared<RandomTask>(EntityType::ENEMY_MINIONS, 1),
            std::make_shared<DamageTask>(EntityType::STACK, 1) },
        5, true));
    cardDef.power.AddPowerTask(ComplexTask::RepeatableThisTurn());
    cards.emplace("AV_285", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [AV_286] Felwalker - COST:6 [ATK:3/HP:7]
    // - Race: Demon, Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>.
    //       <b>Battlecry</b>: Cast the highest Cost Fel spell
    //       from your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [AV_308] Grave Defiler - COST:1 [ATK:2/HP:1]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Copy a Fel spell in your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(ComplexTask::CopyCardInHand(
        1, SelfCondList{
               std::make_shared<SelfCondition>(SelfCondition::IsFelSpell()) }));
    cards.emplace("AV_308", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [AV_312] Sacrificial Summoner - COST:3 [ATK:3/HP:3]
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a friendly minion.
    //       Summon a minion from your deck that costs (1) more.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [AV_313] Hollow Abomination - COST:5 [ATK:2/HP:8]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage to all enemy minions.
    //       <b>Honorable Kill:</b> Gain the minion's Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - HONORABLEKILL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [AV_317] Tamsin's Phylactery - COST:4
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: <b>Discover</b> a friendly <b>Deathrattle</b>
    //       minion that died this game.
    //       Give your minions its <b>Deathrattle</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DISCOVER = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [AV_657] Desecrated Graveyard - COST:3
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn, destroy your lowest
    //       Attack minion to summon a 4/4 Shade. Lasts 3 turns.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [ONY_033] Impfestation - COST:6
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Summon a 3/3 Dread Imp to attack each enemy minion.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [ONY_034] Curse of Agony - COST:1
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Shuffle three Agonies into the opponent's deck.
    //       They deal Fatigue damage when drawn.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [ONY_035] Spawn of Deathwing - COST:5 [ATK:6/HP:6]
    // - Race: Dragon, Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a random enemy minion.
    //       Discard a random card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [AV_286e2] Felgorged - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [AV_313e] Consumed - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Increased attack.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [AV_316t] Dread Imp - COST:3 [ATK:3/HP:3]
    // - Race: Demon, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("AV_316t", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [AV_316t4] Fel Rift - COST:3
    // - Set: ALTERAC_VALLEY
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: <b>Casts When Drawn</b>
    //       Summon a 3/3 Dread Imp.
    // --------------------------------------------------------
    // GameTag:
    // - TOPDECK = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTopdeckTask(std::make_shared<SummonTask>("AV_316t"));
    cardDef.power.AddPowerTask(std::make_shared<SummonTask>("AV_316t"));
    cards.emplace("AV_316t4", cardDef);

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [AV_317e] Lich Perfume - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Copied <b>Deathrattle</b> from {0}.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [AV_657e] Sacrificing - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Sacrifice this at end of turn.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [AV_657t] Desecrated Shade - COST:4 [ATK:4/HP:4]
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [ONY_034t] Agony - COST:1
    // - Set: ALTERAC_VALLEY
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: <b>Casts When Drawn</b>
    //       Take 1 Fatigue damage.
    // --------------------------------------------------------
    // GameTag:
    // - TOPDECK = 1
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - WARRIOR
    // [AV_108] Shield Shatter - COST:10
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: Deal 5 damage to all minions.
    //       Costs (1) less for each Armor you have.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ALL_MINIONS, 5, true));
    cardDef.power.AddAura(
        std::make_shared<AdaptiveCostEffect>([](const Playable* playable) {
            return playable->player->GetHero()->GetArmor();
        }));
    cards.emplace("AV_108", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [AV_109] Frozen Buckler - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: Gain 10 Armor.
    //       At the start of your next turn, lose 5 Armor.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ArmorTask>(10));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("AV_109e", EntityType::SOURCE));
    cards.emplace("AV_109", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [AV_119] To the Front! - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Your minions cost (2) less this turn
    //       <i>(but not less than 1)</i>.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [AV_145] Captain Galvangar - COST:6 [ATK:6/HP:6]
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you have gained 15 or
    //       more Armor this game, gain +3/+3 and <b>Charge</b>.
    //       <i>({0} left!)</i> <i>(Ready!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [AV_321] Glory Chaser - COST:3 [ATK:4/HP:3]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: After you play a <b>Taunt</b> minion, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_PLAY_MINION));
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::HasTaunt())
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DrawTask>(1) };
    cards.emplace("AV_321", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [AV_322] Snowed In - COST:3
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: Destroy a damaged minion.
    //       <b>Freeze</b> all other minions.
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_DAMAGED_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.power.AddPowerTask(
        std::make_shared<FreezeTask>(EntityType::ALL_MINIONS_NOTARGET));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 },
                                          { PlayReq::REQ_MINION_TARGET, 0 },
                                          { PlayReq::REQ_DAMAGED_TARGET, 0 } };
    cards.emplace("AV_322", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [AV_323] Scrapsmith - COST:3 [ATK:2/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Add two 2/4 Grunts
    //       with <b>Taunt</b> to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "AV_323t", 2));
    cards.emplace("AV_323", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [AV_565] Axe Berserker - COST:4 [ATK:3/HP:5]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>. <b>Honorable Kill:</b> Draw a weapon.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    // RefTag:
    // - HONORABLEKILL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddHonorableKillTask(std::make_shared<DrawWeaponTask>(1));
    cards.emplace("AV_565", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [AV_660] Iceblood Garrison - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       deal 1 damage to all minions. Lasts 3 turns.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DamageTask>(
        EntityType::ALL_MINIONS, 1, true) };
    cardDef.power.GetTrigger()->lastTurn = 3;
    cards.emplace("AV_660", cardDef);

    // ---------------------------------------- SPELL - WARRIOR
    // [ONY_023] Hit It Very Hard - COST:1
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: Gain +10 Attack and "Can't attack heroes" this turn.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [ONY_024] Onyxian Drake - COST:4 [ATK:4/HP:5]
    // - Race: Dragon, Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Deal damage equal to your Armor
    //       to an enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [ONY_025] Shoulder Check - COST:1
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Tradeable</b>
    //       Give a minion +2/+1 and <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TRADEABLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [AV_109e] Chilly - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Lose 5 Armor next turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::TURN_START));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<ArmorTask>(-5) };
    cardDef.power.GetTrigger()->removeAfterTriggered = true;
    cards.emplace("AV_109e", cardDef);

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [AV_119e] Frontlined - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Your minions cost (2) less this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [AV_145e] Fury of the Frostwolf - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +3/+3 and <b>Charge</b>.
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [AV_202t2] The Unstoppable Force - COST:7
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: After you attack a minion,
    //       smash it into the enemy hero!
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [AV_323t] Scrappy Grunt - COST:3 [ATK:2/HP:4]
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("AV_323t", cardDef);

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [ONY_023e] HIT IT HARD - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +10 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddDemonHunter(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- MINION - DEMONHUNTER
    // [AV_118] Battleworn Vanguard - COST:2 [ATK:2/HP:2]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: After your hero attacks, summon two 1/1 Felwings.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::AFTER_ATTACK));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SummonTask>(
        "BT_922t", 2) };
    cards.emplace("AV_118", cardDef);

    // ----------------------------------- WEAPON - DEMONHUNTER
    // [AV_209] Dreadprison Glaive - COST:1
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Honorable Kill:</b> Deal damage equal to
    //       your hero's Attack to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [AV_261] Flag Runner - COST:3 [ATK:1/HP:6]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever a friendly minion dies, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::DEATH));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::MINIONS;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "AV_261e", EntityType::SOURCE) };
    cards.emplace("AV_261", cardDef);

    // ----------------------------------- MINION - DEMONHUNTER
    // [AV_262] Warden of Chains - COST:4 [ATK:2/HP:6]
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> If you're holding a Demon that
    //       costs (5) or more, gain +1/+2.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::Has5MoreCostDemonInHand()) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "AV_262e2", EntityType::SOURCE) }));
    cards.emplace("AV_262", cardDef);

    // ------------------------------------ SPELL - DEMONHUNTER
    // [AV_264] Sigil of Reckoning - COST:5
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: At the start of your next turn,
    //       summon a random Demon from your hand.
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [AV_265] Ur'zul Giant - COST:13 [ATK:8/HP:8]
    // - Race: Demon, Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: Costs (1) less for each friendly minion
    //       that died this game.
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [AV_267] Caria Felsoul - COST:7 [ATK:7/HP:7]
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Transform into a 7/7 copy
    //       of a Demon in your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [AV_269] Flanking Maneuver - COST:4
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon a 4/2 Demon with <b>Rush</b>.
    //       If it dies this turn, summon another.
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [AV_661] Field of Strife - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Your minions have +1 Attack. Lasts 3 turns.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "AV_661e2", EntityType::MINIONS) };
    cardDef.power.GetTrigger()->lastTurn = 3;
    cards.emplace("AV_661", cardDef);

    // ------------------------------------ SPELL - DEMONHUNTER
    // [ONY_014] Keen Reflex - COST:2
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 1 damage to all minions.
    //       <b>Honorable Kill:</b> Gain +1 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [ONY_016] Wings of Hate (Rank 1) - COST:1
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon two 1/1 Felwings.
    //       <i>(Upgrades when you have 5 Mana.)</i>
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [ONY_036] Razorglaive Sentinel - COST:4 [ATK:5/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: After you play the left or right-most card
    //       in your hand, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddDemonHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [AV_204e] Ashfallen's Power - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [AV_204t2] Felbat Shrieker - COST:3 [ATK:1/HP:4]
    // - Race: Demon, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [AV_261e] Team Player - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +1 Attack
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("AV_261e"));
    cards.emplace("AV_261e", cardDef);

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [AV_262e2] Terrifying - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +1/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("AV_262e2"));
    cards.emplace("AV_262e2", cardDef);

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [AV_267e2] Demonic - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Attack and Health set to 7.
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [AV_269e] Woe Is Me - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: If this dies summon another.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_SILENCED = 1
    // - ENCHANTMENT_INVISIBLE = 1
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [AV_269t] Snowy Satyr - COST:3 [ATK:4/HP:2]
    // - Race: Demon, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [AV_661e2] Empowered - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +1 Attack from {0}.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("AV_661e2"));
    cards.emplace("AV_661e2", cardDef);

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [ONY_014e] Keen Reflex - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +1 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [ONY_016t] Wings of Hate (Rank 2) - COST:1
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon three 1/1 Felwings.
    //       <i>(Upgrades when you have 10 Mana.)</i>
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [ONY_016t2] Wings of Hate (Rank 3) - COST:1
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon four 1/1 Felwings.
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [AV_100] Drek'Thar - COST:4 [ATK:4/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry</b>: If this costs more than every
    //       minion in your deck, summon one of those minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_101] Herald of Lokholar - COST:4 [ATK:3/HP:5]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a Frost spell.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DrawSpellTask>(SpellSchool::FROST, 1));
    cards.emplace("AV_101", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [AV_102] Popsicooler - COST:3 [ATK:3/HP:3]
    // - Race: Mechanical, Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> <b>Freeze</b> two random
    //       enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<RandomTask>(EntityType::ENEMY_MINIONS, 2));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<FreezeTask>(EntityType::STACK));
    cards.emplace("AV_102", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [AV_112] Snowblind Harpy - COST:3 [ATK:3/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Frost spell,
    //       gain 5 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE,
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsHoldingSpell(SpellSchool::FROST)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<ArmorTask>(5) }));
    cards.emplace("AV_112", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [AV_121] Gnome Private - COST:1 [ATK:1/HP:3]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Honorable Kill:</b> Gain +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddHonorableKillTask(
        std::make_shared<AddEnchantmentTask>("AV_121e", EntityType::SOURCE));
    cards.emplace("AV_121", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [AV_122] Corporal - COST:2 [ATK:2/HP:3]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Honorable Kill:</b> Give your other minions
    //       <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddHonorableKillTask(std::make_shared<SetGameTagTask>(
        EntityType::MINIONS_NOSOURCE, GameTag::DIVINE_SHIELD, 1));
    cards.emplace("AV_122", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [AV_123] Sneaky Scout - COST:2 [ATK:3/HP:2]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //       <b>Honorable Kill:</b> Your next Hero Power costs (0).
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddHonorableKillTask(
        std::make_shared<AddEnchantmentTask>("AV_123e", EntityType::PLAYER));
    cards.emplace("AV_123", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [AV_124] Direwolf Commander - COST:3 [ATK:2/HP:5]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Honorable Kill:</b> Summon a 2/2 Wolf
    //       with <b>Stealth</b>.
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddHonorableKillTask(
        std::make_shared<SummonTask>("AV_211t", SummonSide::RIGHT));
    cards.emplace("AV_124", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [AV_125] Tower Sergeant - COST:4 [ATK:4/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control at least
    //       2 other minions, gain +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE,
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsFieldCount(3, RelaSign::GEQ)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "AV_125e", EntityType::SOURCE) }));
    cards.emplace("AV_125", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [AV_126] Bunker Sergeant - COST:3 [ATK:2/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your opponent has 2 or
    //       more minions, deal 1 damage to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE,
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsOpFieldCount(2, RelaSign::GEQ)) }));
    cardDef.power.AddPowerTask(
        std::make_shared<FlagTask>(true, TaskList{ std::make_shared<DamageTask>(
                                             EntityType::ENEMY_MINIONS, 1) }));
    cards.emplace("AV_126", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [AV_127] Ice Revenant - COST:4 [ATK:4/HP:5]
    // - Race: Elemental, Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever you cast a Frost spell, gain +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SPELLS;
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsFrostSpell())
    };
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "AV_127e", EntityType::SOURCE) };
    cards.emplace("AV_127", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [AV_128] Frozen Mammoth - COST:4 [ATK:6/HP:7]
    // - Race: Beast, Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: This is <b>Frozen</b> until you cast a Fire spell.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_129] Blood Guard - COST:5 [ATK:4/HP:7]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever this minion takes damage,
    //       give your minions +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_130] Legionnaire - COST:6 [ATK:9/HP:3]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give all minions in your hand +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<IncludeTask>(EntityType::HAND));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsMinion()) }));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<AddEnchantmentTask>("AV_130e", EntityType::STACK));
    cards.emplace("AV_130", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [AV_131] Knight-Captain - COST:5 [ATK:3/HP:3]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage.
    //       <b>Honorable Kill:</b> Gain +3/+3.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - HONORABLEKILL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3));
    cardDef.power.AddHonorableKillTask(
        std::make_shared<AddEnchantmentTask>("AV_131e", EntityType::SOURCE));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("AV_131", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [AV_132] Troll Centurion - COST:8 [ATK:8/HP:8]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>. <b>Honorable Kill:</b>
    //       Deal 8 damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddHonorableKillTask(
        std::make_shared<DamageTask>(EntityType::ENEMY_HERO, 8));
    cards.emplace("AV_132", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [AV_133] Icehoof Protector - COST:6 [ATK:2/HP:10]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Freeze</b> any character damaged by this minion.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("AV_133", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [AV_134] Frostwolf Warmaster - COST:4 [ATK:3/HP:3]
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: Costs (1) less for each card you've played this turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<AdaptiveCostEffect>([](const Playable* playable) {
            return playable->player->GetGameTag(
                GameTag::NUM_CARDS_PLAYED_THIS_TURN);
        }));
    cards.emplace("AV_134", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [AV_135] Stormpike Marshal - COST:4 [ATK:2/HP:6]
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       If you took 5 or more damage on your opponent's turn,
    //       this costs (1).
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_136] Kobold Taskmaster - COST:3 [ATK:2/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add 2 Armor Scraps to your hand
    //       that give +2 Health to a minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_137] Irondeep Trogg - COST:1 [ATK:1/HP:2]
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: After your opponent casts a spell,
    //       summon another Irondeep Trogg.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_138] Grimtotem Bounty Hunter - COST:3 [ATK:4/HP:2]
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy an enemy
    //       <b>Legendary</b> minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_LEGENDARY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DestroyTask>(EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_LEGENDARY_TARGET, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_ENEMY_TARGET, 0 } };
    cards.emplace("AV_138", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [AV_139] Abominable Lieutenant - COST:8 [ATK:3/HP:5]
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       eat a random enemy minion and gain its stats.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_141t] Lokholar the Ice Lord - COST:10 [ATK:8/HP:8]
    // - Race: Elemental, Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Rush</b>, <b>Windfury</b>
    //       Costs (5) less if you have 15 Health or less.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - RUSH = 1
    // - WINDFURY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_142t] Ivus, the Forest Lord - COST:1 [ATK:1/HP:1]
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Spend the rest of your Mana
    //       and gain +2/+2, <b>Rush</b>, <b>Divine Shield</b>,
    //       or <b>Taunt</b> at random for each.
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
    // [AV_143] Korrak the Bloodrager - COST:4 [ATK:3/HP:5]
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> If this
    //       wasn't <b>Honorably Killed</b>,
    //       resummon Korrak.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - HONORABLEKILL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_215] Frantic Hippogryph - COST:5 [ATK:3/HP:7]
    // - Race: Beast, Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>. <b>Honorable Kill</b>:
    //        Gain <b>Windfury</b>.
    // --------------------------------------------------------
    // GameTag:
    // - HONORABLEKILL = 1
    // - RUSH = 1
    // --------------------------------------------------------
    // RefTag:
    // - WINDFURY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddHonorableKillTask(std::make_shared<SetGameTagTask>(
        EntityType::SOURCE, GameTag::WINDFURY, 1));
    cards.emplace("AV_215", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [AV_219] Ram Commander - COST:2 [ATK:2/HP:2]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add two 1/1 Rams with <b>Rush</b>
    //       to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "AV_219t", 2));
    cards.emplace("AV_219", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [AV_222] Spammy Arcanist - COST:5 [ATK:3/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage to all other minions.
    //       If any die, repeat this.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_223] Vanndar Stormpike - COST:4 [ATK:4/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry</b>: If this costs less than
    //       every minion in your deck, reduce their Cost by (3).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_238] Gankster - COST:2 [ATK:4/HP:2]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //       After your opponent plays a minion, attack it.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_256] Reflecto Engineer - COST:3 [ATK:2/HP:4]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Swap the Attack and Health
    //       of all minions in both players' hands.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_309] Piggyback Imp - COST:3 [ATK:4/HP:1]
    // - Race: Demon, Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 4/1 Imp.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("AV_309t", SummonSide::DEATHRATTLE));
    cards.emplace("AV_309", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [AV_401] Stormpike Quartermaster - COST:2 [ATK:2/HP:2]
    // - Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: After you cast a spell,
    //       give a random minion in your hand +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = {
        ComplexTask::GiveBuffToRandomMinionInHand("AV_401e")
    };
    cards.emplace("AV_401", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [AV_704] Humongous Owl - COST:7 [ATK:8/HP:4]
    // - Race: Beast, Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 8 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<RandomTask>(EntityType::ENEMIES, 1));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<DamageTask>(EntityType::STACK, 8));
    cards.emplace("AV_704", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ONY_001] Onyxian Warder - COST:5 [ATK:3/HP:6]
    // - Race: Dragon, Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       summon two 2/1 Whelps with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ONY_002] Gear Grubber - COST:4 [ATK:4/HP:5]
    // - Set: ALTERAC_VALLEY, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>.
    //       If you end your turn with any unspent mana,
    //       reduce this card's Cost by (1).
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ONY_003] Whelp Bonker - COST:3 [ATK:1/HP:5]
    // - Set: ALTERAC_VALLEY, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Frenzy and Honorable Kill:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - FRENZY = 1
    // - HONORABLEKILL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ONY_004] Raid Boss Onyxia - COST:10 [ATK:8/HP:8]
    // - Race: Dragon, Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Rush</b>.
    //       <b>Immune</b> while you control a Whelp.
    //       <b>Battlecry:</b> Summon six 2/1 Whelps with <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - RUSH = 1
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ONY_005] Kazakusan - COST:8 [ATK:8/HP:8]
    // - Race: Dragon, Set: ALTERAC_VALLEY, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b>
    //       If you played 4 other Dragons this game,
    //       craft a custom deck of Treasures.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_121e] Gnome's Honor - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("AV_121e"));
    cards.emplace("AV_121e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_123e] Scouted - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Your Hero Power costs (0).
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::HERO_POWER, EffectList{ Effects::SetCost(0) }));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->removeTrigger = { TriggerType::INSPIRE, nullptr };
    }
    cards.emplace("AV_123e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_125e] Shielded - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("AV_125e"));
    cards.emplace("AV_125e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_127e] Frosty Spirit - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("AV_127e"));
    cards.emplace("AV_127e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_128e] Unthawed - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Frozen</b> until you cast a Fire spell.
    // --------------------------------------------------------
    // GameTag:
    // - ENCHANTMENT_INVISIBLE = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_129e] Incited - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_130e] Marching Orders - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("AV_130e"));
    cards.emplace("AV_130e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_131e] Armed to the Teeth - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +3/+3
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("AV_131e"));
    cards.emplace("AV_131e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_136e] Rusted Armor - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2 Health.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [AV_136t] Armor Scrap - COST:1
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Give a minion
    //       +2 Health.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_139e] Tummy Feel Funny - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Increased Stats
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_142e] Crystalskin - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_142e2] Uprooted - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Rush</b>.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_142e3] Forestguard - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_142e4] Imposing - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Taunt</b>.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_211t] Frostwolf Cub - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("AV_211t", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [AV_218t] Sheep - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: ALTERAC_VALLEY, Rarity: Common
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_219t] Battle Ram - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("AV_219t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_223e] Occupy the Keep - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (3) less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_256e] Reflected - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Attack and Health have been swapped.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_259e2] Frostbitten - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Costs (2) more.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_284e2] Magical Shift - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Swapped Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_284e3] Magical Shift - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Swapped Heatlh,
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AV_309t] Backpiggy Imp - COST:3 [ATK:4/HP:1]
    // - Race: Demon, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("AV_309t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AV_401e] Quartered - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("AV_401e"));
    cards.emplace("AV_401e", cardDef);

    // ---------------------------------------- SPELL - NEUTRAL
    // [AV_COIN1] The Coin - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Gain 1 Mana Crystal this turn only.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [AV_COIN2] The Coin - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Gain 1 Mana Crystal this turn only.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ONY_001t] Onyxian Whelp - COST:1 [ATK:2/HP:1]
    // - Race: Dragon, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("ONY_001t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ONY_002e] More Loot! - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Reduced Cost.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [ONY_005ta1] Necrotic Poison - COST:2
    // - Set: ALTERAC_VALLEY
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Destroy a minion.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [ONY_005ta10] Spyglass - COST:1
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Put a copy of a random card in your opponent's hand
    //       into yours. It costs (3) less.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ONY_005ta11] Clockwork Assistant - COST:3 [ATK:1/HP:1]
    // - Race: Mechanical, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Has +1/+1 for each spell you've cast this game.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ONY_005ta12] Grimmer Patron - COST:3 [ATK:3/HP:3]
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: At the end of your turn, summon a copy of this minion.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [ONY_005ta13] Puzzle Box - COST:3
    // - Set: ALTERAC_VALLEY
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Transform all minions into random ones
    //       that cost (3) more.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [ONY_005ta2] Mutating Injection - COST:2
    // - Set: ALTERAC_VALLEY
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Give a minion +4/+4 and <b>Taunt</b>.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ONY_005ta2e] Mutating Injection - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +4/+4 and <b>Taunt</b>.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - NEUTRAL
    // [ONY_005ta3] The Exorcisor - COST:1
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Silence</b> any minion attacked by this weapon.
    // --------------------------------------------------------
    // RefTag:
    // - SILENCE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [ONY_005ta4] Pure Cold - COST:5
    // - Set: ALTERAC_VALLEY
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: Deal 8 damage to the enemy hero, and <b>Freeze</b> it.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ONY_005ta5] Bubba - COST:5 [ATK:8/HP:8]
    // - Race: Beast, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Battlecry</b>: Summon six 1/1 Bloodhounds
    //       with <b>Rush</b> to attack an enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ONY_005ta5t] Bloodhound - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [ONY_005ta6] Holy Book - COST:8
    // - Set: ALTERAC_VALLEY
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: <b>Silence</b> and destroy a minion.
    //       Summon a 10/10 copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - SILENCE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ONY_005ta7] Crusty the Crustacean - COST:3 [ATK:3/HP:3]
    // - Race: Beast, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a minion.
    //       Gain its Attack and Health.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ONY_005ta7e] Om Nom Nom - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [ONY_005ta8] Looming Presence - COST:3
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Draw 2 cards. Gain 4 Armor.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ONY_005ta9] Beastly Beauty - COST:3 [ATK:2/HP:6]
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       After this attacks a minion and survives,
    //       transform this into an 8/8.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ONY_005ta9t] Beautiful Beast - COST:5 [ATK:8/HP:8]
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - NEUTRAL
    // [ONY_005tb1] Hyperblaster - COST:3
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>.
    //       Your hero is <b>Immune</b> while attacking.
    // --------------------------------------------------------
    // GameTag:
    // - POISONOUS = 1
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [ONY_005tb12] Dr. Boom's Boombox - COST:4
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Summon 7 'Boom Bots'.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ONY_005tb13] Wax Rager - COST:3 [ATK:5/HP:1]
    // - Race: Elemental, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Resummon this minion.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [ONY_005tb14] Vampiric Fangs - COST:3
    // - Set: ALTERAC_VALLEY
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Destroy a minion. Restore its Health to your hero.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ONY_005tb1e] Hyperblaster Enchantment - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Immune</b> while attacking.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [ONY_005tb2] Gnomish Army Knife - COST:5
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Give a minion <b>Rush</b>,
    //       <b>Windfury</b>, <b>Divine Shield</b>,
    //       <b>Lifesteal</b>, <b>Poisonous</b>,
    //       <b>Taunt</b>, and <b>Stealth</b>.
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // - LIFESTEAL = 1
    // - POISONOUS = 1
    // - RUSH = 1
    // - STEALTH = 1
    // - TAUNT = 1
    // - WINDFURY = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ONY_005tb2e] Tooled Up! - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Granted <b>Rush</b>,
    //       <b>Windfury</b>, <b>Divine Shield</b>,
    //       <b>Lifesteal</b>, <b>Poisonous</b>,
    //       <b>Taunt</b>, and <b>Stealth</b>.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [ONY_005tb3] LOCUUUUSTS!!! - COST:8
    // - Set: ALTERAC_VALLEY
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: <b>Twinspell</b>
    //       Choose an enemy.
    //       Fill your board with 2/2 Locusts that attack it.
    // --------------------------------------------------------
    // GameTag:
    // - TWINSPELL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [ONY_005tb3t] LOCUUUUSTS!!! - COST:8
    // - Set: ALTERAC_VALLEY
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Choose an enemy.
    //       Fill your board with 2/2 Locusts that attack it.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ONY_005tb3t2] Giant Locust - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Set: ALTERAC_VALLEY
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [ONY_005tb4] Wand of Disintegration - COST:5
    // - Set: ALTERAC_VALLEY
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: <b>Silence</b> and destroy all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - SILENCE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [ONY_005tb5] Staff of Scales - COST:5
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Summon three 1/1 Snakes with <b>Rush</b>,
    //       <b>Poisonous</b> and <b>Reborn</b>.
    // --------------------------------------------------------
    // RefTag:
    // - POISONOUS = 1
    // - REBORN = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ONY_005tb5t] Ancient Snake - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Poisonous</b>
    //       <b>Reborn</b>
    // --------------------------------------------------------
    // GameTag:
    // - POISONOUS = 1
    // - REBORN = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - NEUTRAL
    // [ONY_005tb6] Phaoris' Blade - COST:2
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Windfury</b>.
    //       After your hero attacks and kills a minion,
    //       this gains +2/+1.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - WINDFURY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [ONY_005tb610] Zephrys's Lamp - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Wish for the perfect card.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ONY_005tb6e] Phaoris' Fury - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [ONY_005tb7] Canopic Jars - COST:3
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Give your minions "<b>Deathrattle:</b>
    //       Summon a random <b>Legendary</b> minion."
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ONY_005tb7e] Canopic Jars - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a random
    //       <b>Legendary</b> minion.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [ONY_005tb8] Ancient Reflections - COST:4
    // - Set: ALTERAC_VALLEY
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Choose a minion.
    //       Fill your board with 1/1 copies of it.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ONY_005tb8e] Titan Hologram - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: 1/1.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [ONY_005tb9] Banana Split - COST:5
    // - Set: ALTERAC_VALLEY
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Give a friendly minion +2/+2.
    //       Summon two copies of it.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ONY_005tb9e] Glowing Green - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [ONY_005tc1] Embers of Ragnaros - COST:10
    // - Set: ALTERAC_VALLEY
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Shoot three fireballs at random enemies
    //       that deal 8 damage each.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [ONY_005tc2] Book of the Dead - COST:14
    // - Set: ALTERAC_VALLEY
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Deal 7 damage to all enemies.
    //       Costs (1) less for each minion that's died this game.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [ONY_005tc3] Annoy-o Horn - COST:8
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Fill your board with annoying minions.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [ONY_005tc4] Flex-plosion - COST:8
    // - Set: ALTERAC_VALLEY
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Blow up half your opponent's stuff.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - NEUTRAL
    // [ONY_005tc5] Blade of Quel'Delar - COST:1
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [ONY_005tc6] Hilt of Quel'Delar - COST:1
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: Give a minion +3/+3.
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - NEUTRAL
    // [ONY_005tc7] Quel'Delar - COST:6
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: After your hero attacks,
    //       deal 4 damage to all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [ONY_005tc7t] Forging Quel'Delar - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ONY_025e] Incensed - COST:0
    // - Set: ALTERAC_VALLEY
    // --------------------------------------------------------
    // Text: +2/+1 and <b>Rush</b>.
    // --------------------------------------------------------
}

void AlteracValleyCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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