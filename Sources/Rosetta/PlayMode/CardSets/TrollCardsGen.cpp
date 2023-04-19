// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/CardSets/TrollCardsGen.hpp>
#include <Rosetta/PlayMode/Cards/CardPowers.hpp>

namespace RosettaStone::PlayMode
{
void TrollCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ HERO - HUNTER
    // [TRL_065] Zul'jin - COST:10 [ATK:0/HP:30]
    // - Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Cast all spells you've played
    //       this game <i>(targets chosen randomly)</i>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 50579
    // --------------------------------------------------------
}

void TrollCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------ HERO_POWER - HUNTER
    // [TRL_065h] Berserker Throw (*) - COST:2
    // - Set: Troll
    // --------------------------------------------------------
    // Text: <b>Hero Power</b> Deal 2 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
}

void TrollCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - DRUID
    // [TRL_223] Spirit of the Raptor - COST:1 [ATK:0/HP:3]
    // - Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Stealth</b> for 1 turn.
    //       After your hero attacks and kills a minion,
    //       draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [TRL_232] Ironhide Direhorn - COST:7 [ATK:7/HP:7]
    // - Race: Beast, Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Overkill:</b> Summon a 5/5 Ironhide Runt.
    // --------------------------------------------------------
    // GameTag:
    // - OVERKILL = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [TRL_240] Savage Striker - COST:2 [ATK:2/HP:3]
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal damage to an enemy minion
    //       equal to your hero's Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE_AND_HERO_HAS_ATTACK = 0
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [TRL_241] Gonk, the Raptor - COST:7 [ATK:4/HP:9]
    // - Race: Beast, Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After your hero attacks and kills a minion,
    //       it may attack again.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [TRL_243] Pounce - COST:0
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: Give your hero +2 Attack this turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("TRL_243e", EntityType::HERO));
    cards.emplace("TRL_243", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [TRL_244] Predatory Instincts - COST:4
    // - Faction: Neutral, Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: Draw a Beast from your deck. Double its Health.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [TRL_254] Mark of the Loa - COST:4
    // - Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Choose One</b> - Give a minion +2/+4 and
    //       <b>Taunt</b>; or Summon two 3/2 Raptors.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [TRL_255] Stampeding Roar - COST:6
    // - Faction: Neutral, Set: Troll, Rarity: Epic
    // --------------------------------------------------------
    // Text: Summon a random Beast from your hand and
    //       give it <b>Rush</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_NUM_MINION_SLOTS = 1
    // - REQ_FRIENDLY_MINION_OF_RACE_IN_HAND = 20
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [TRL_341] Treespeaker - COST:5 [ATK:4/HP:4]
    // - Faction: Neutral, Set: Troll, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Transform your Treants
    //       into 5/5 Ancients.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [TRL_343] Wardruid Loti - COST:3 [ATK:1/HP:2]
    // - Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Choose One - </b>Transform into one of
    //       Loti's four dinosaur forms.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
}

void TrollCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- MINION - DRUID
    // [TRL_232t] Ironhide Runt (*) - COST:5 [ATK:5/HP:5]
    // - Race: Beast, Set: Troll
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [TRL_254a] Gonk's Resilience (*) - COST:0
    // - Faction: Neutral, Set: Troll
    // --------------------------------------------------------
    // Text: Give a minion +2/+4 and <b>Taunt</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [TRL_254ae] Mark of the Loa (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: +2/+4 and <b>Taunt</b>.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [TRL_254b] Raptor Pack (*) - COST:0
    // - Faction: Neutral, Set: Troll
    // --------------------------------------------------------
    // Text: Summon two 3/2 Raptors.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [TRL_254t] Raptor (*) - COST:2 [ATK:3/HP:2]
    // - Race: Beast, Set: Troll
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [TRL_255e] Stampede! (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: Has <b>Rush</b>.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [TRL_341t] Ancient (*) - COST:5 [ATK:5/HP:5]
    // - Set: Troll
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [TRL_343at1] Ankylodon (*) - COST:3 [ATK:1/HP:6]
    // - Race: Beast, Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [TRL_343at2] Wardruid Loti (*) - COST:3 [ATK:1/HP:6]
    // - Race: Beast, Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [TRL_343bt1] Sabertusk (*) - COST:3 [ATK:4/HP:2]
    // - Race: Beast, Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [TRL_343bt2] Wardruid Loti (*) - COST:3 [ATK:4/HP:2]
    // - Race: Beast, Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [TRL_343ct1] Pterrordax (*) - COST:3 [ATK:1/HP:4]
    // - Race: Beast, Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [TRL_343ct2] Wardruid Loti (*) - COST:3 [ATK:1/HP:4]
    // - Race: Beast, Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [TRL_343dt1] Ravasaur (*) - COST:3 [ATK:1/HP:2]
    // - Race: Beast, Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>, <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - STEALTH = 1
    // - POISONOUS = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [TRL_343dt2] Wardruid Loti (*) - COST:3 [ATK:1/HP:2]
    // - Race: Beast, Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>, <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // - POISONOUS = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [TRL_343et1] Wardruid Loti (*) - COST:3 [ATK:4/HP:6]
    // - Race: Beast, Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Taunt</b>, <b>Rush</b>, <b>Poisonous</b>,
    //       <b>Stealth</b>, <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // - STEALTH = 1
    // - SPELLPOWER = 1
    // - POISONOUS = 1
    // - RUSH = 1
    // --------------------------------------------------------
}

void TrollCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- WEAPON - HUNTER
    // [TRL_111] Headhunter's Hatchet - COST:2 [ATK:2/HP:0]
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a Beast,
    //       gain +1 Durability.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE,
        SelfCondList{ std::make_shared<SelfCondition>(
            SelfCondition::IsControllingRace(Race::BEAST)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "TRL_111e1", EntityType::SOURCE) }));
    cards.emplace("TRL_111", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [TRL_119] The Beast Within - COST:1
    // - Set: Troll, Rarity: Epic
    // --------------------------------------------------------
    // Text: Give a friendly Beast +1/+1,
    //       then it attacks a random enemy minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_TARGET_WITH_RACE = 20
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [TRL_339] Master's Call - COST:3
    // - Faction: Neutral, Set: Troll, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Discover</b> a minion in your deck.
    //       If all 3 are Beasts, draw them all.
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [TRL_347] Baited Arrow - COST:5
    // - Faction: Neutral, Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 3 damage.
    //       <b>Overkill:</b> Summon a 5/5 Devilsaur.
    // --------------------------------------------------------
    // GameTag:
    // - OVERKILL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [TRL_348] Springpaw - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b> <b>Battlecry:</b> Add a 1/1 Lynx
    //       with <b>Rush</b> to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddCardTask>(EntityType::HAND, "TRL_348t", 1));
    cards.emplace("TRL_348", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [TRL_349] Bloodscalp Strategist - COST:3 [ATK:2/HP:4]
    // - Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you have a weapon equipped,
    //       <b>Discover</b> a spell.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [TRL_566] Revenge of the Wild - COST:2
    // - Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon your Beasts that died this turn.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_FRIENDLY_MINION_OF_RACE_DIED_THIS_TURN = 20
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [TRL_900] Halazzi, the Lynx - COST:5 [ATK:3/HP:2]
    // - Race: Beast, Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Fill your hand with 1/1 Lynxes
    //       that have <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [TRL_901] Spirit of the Lynx - COST:3 [ATK:0/HP:3]
    // - Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Stealth</b> for 1 turn.
    //       Whenever you summon a Beast, give it +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
}

void TrollCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - HUNTER
    // [TRL_347t] Devilsaur (*) - COST:5 [ATK:5/HP:5]
    // - Race: Beast, Set: Troll
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [TRL_348t] Lynx (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Faction: Neutral, Set: Troll
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("TRL_348t", cardDef);
}

void TrollCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------- SPELL - MAGE
    // [TRL_310] Elemental Evocation - COST:0
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: The next Elemental you play this turn costs (2) less.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [TRL_311] Arcanosaur - COST:6 [ATK:3/HP:3]
    // - Race: Elemental, Faction: Neutral, Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you played an Elemental last turn,
    //       deal 3 damage to all other minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [TRL_313] Scorch - COST:4
    // - Faction: Neutral, Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 4 damage to a minion.
    //       Costs (1) if you played an Elemental last turn.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [TRL_315] Pyromaniac - COST:3 [ATK:3/HP:4]
    // - Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever your Hero Power kills a minion, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::INSPIRE));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<DrawTask>(1) };
    cardDef.power.GetTrigger()->conditions = SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsDefenderDead())
    };
    cards.emplace("TRL_315", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [TRL_316] Jan'alai, the Dragonhawk - COST:7 [ATK:4/HP:4]
    // - Race: Beast, Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your Hero Power dealt 8 damage
    //       this game, summon Ragnaros the Firelord.
    //       @<i>({0} left!)</i>@ <i>(Ready!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - PLAYER_TAG_THRESHOLD_TAG_ID = 1025
    // - PLAYER_TAG_THRESHOLD_VALUE = 8
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [TRL_317] Blast Wave - COST:5
    // - Faction: Neutral, Set: Troll, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 2 damage to_all minions.
    //       <b>Overkill</b>: Add a random Mage spell to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - OVERKILL = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [TRL_318] Hex Lord Malacrass - COST:8 [ATK:5/HP:5]
    // - Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry</b>: Add a copy of your opening hand
    //       to your hand <i>(except this card)</i>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [TRL_319] Spirit of the Dragonhawk - COST:2 [ATK:0/HP:3]
    // - Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Stealth</b> for 1 turn.
    //       Your Hero Power also targets adjacent minions.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // - AURA = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [TRL_390] Daring Fire-Eater - COST:1 [ATK:1/HP:1]
    // - Faction: Neutral, Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your next Hero Power this turn
    //       deals 2 more damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [TRL_400] Splitting Image - COST:3
    // - Set: Troll, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When one of your minions is attacked,
    //       summon a copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
}

void TrollCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------- ENCHANTMENT - MAGE
    // [TRL_310e] Elemental Evocation (*) - COST:0
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: The next Elemental you play this turn costs (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
}

void TrollCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - PALADIN
    // [TRL_300] Shirvallah, the Tiger - COST:25 [ATK:7/HP:5]
    // - Race: Beast, Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>, <b>Rush</b>, <b>Lifesteal</b>
    //       Costs (1) less for each Mana you've spent on spells.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DIVINE_SHIELD = 1
    // - LIFESTEAL = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [TRL_302] Time Out! - COST:3
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: Your hero is <b>Immune</b> until your next turn.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - PALADIN
    // [TRL_304] Farraki Battleaxe - COST:5 [ATK:3/HP:0]
    // - Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Overkill:</b> Give a minion in your hand +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 3
    // - OVERKILL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [TRL_305] A New Challenger... - COST:7
    // - Set: Troll, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Discover</b> a 6-Cost minion.
    //       Summon it with <b>Taunt</b> and <b>Divine Shield</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // - DIVINE_SHIELD = 1
    // - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [TRL_306] Immortal Prelate - COST:2 [ATK:1/HP:3]
    // - Set: Troll, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Shuffle this into your deck.
    //       It keeps any enchantments.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - 542 = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [TRL_307] Flash of Light - COST:2
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: Restore 4 Health. Draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<HealTask>(EntityType::TARGET, 4));
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("TRL_307", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [TRL_308] High Priest Thekal - COST:3 [ATK:3/HP:4]
    // - Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Convert all but 1 of your
    //       Hero's Health into Armor.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [TRL_309] Spirit of the Tiger - COST:4 [ATK:0/HP:3]
    // - Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Stealth</b> for 1 turn.
    //       After you cast a spell,
    //       summon a Tiger with stats equal to its Cost.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - PALADIN
    // [TRL_543] Bloodclaw - COST:1 [ATK:2/HP:0]
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 5 damage to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [TRL_545] Zandalari Templar - COST:4 [ATK:4/HP:4]
    // - Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you've restored 10 Health
    //       this game, gain +4/+4 and <b>Taunt</b>.
    //       @ <i>({0} left!)</i>@ <i>(Ready!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - PLAYER_TAG_THRESHOLD_TAG_ID = 958
    // - PLAYER_TAG_THRESHOLD_VALUE = 10
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
}

void TrollCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------- ENCHANTMENT - PALADIN
    // [TRL_302e] Time Out! (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: <b>Immune</b> until your next turn.
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [TRL_309t] Tiger (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Troll
    // --------------------------------------------------------
}

void TrollCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- SPELL - PRIEST
    // [TRL_097] Seance - COST:2
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: Choose a minion. Add a copy of it to your hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [TRL_128] Regenerate - COST:0
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: Restore 3 Health.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [TRL_131] Sand Drudge - COST:3 [ATK:3/HP:3]
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever you cast a spell,
    //       summon a 1/1 Zombie with <b>Taunt</b>.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [TRL_258] Mass Hysteria - COST:5
    // - Faction: Neutral, Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: Force each minion to attack another random minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [TRL_259] Princess Talanji - COST:8 [ATK:7/HP:5]
    // - Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon all minions from your hand
    //       that didn't start in your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [TRL_260] Bwonsamdi, the Dead - COST:7 [ATK:7/HP:7]
    // - Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw 1-Cost minions from your deck
    //       until your hand is full.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [TRL_408] Grave Horror - COST:12 [ATK:7/HP:8]
    // - Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       Costs (1) less for each spell you've cast this game.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [TRL_500] Surrender to Madness - COST:3
    // - Set: Troll, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy 3 of your Mana Crystals.
    //       Give all minions in your deck +2/+2.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [TRL_501] Auchenai Phantasm - COST:2 [ATK:3/HP:2]
    // - Set: Troll, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> This turn,
    //       your healing effects deal damage instead.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [TRL_502] Spirit of the Dead - COST:1 [ATK:0/HP:3]
    // - Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Stealth</b> for 1 turn.
    //       After a friendly minion dies,
    //       shuffle a 1-Cost copy of it into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------
}

void TrollCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- MINION - PRIEST
    // [TRL_131t] Zombie (*) - COST:1 [ATK:1/HP:1]
    // - Set: Troll
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [TRL_500e] Absolutely Mad! (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [TRL_502e] Prayer to Bwonsamdi (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: Bwonsamdi made this cost (1).
    // --------------------------------------------------------
}

void TrollCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- MINION - ROGUE
    // [TRL_071] Bloodsail Howler - COST:2 [ATK:1/HP:1]
    // - Race: Pirate, Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Battlecry:</b> Gain +1/+1 for each other Pirate
    //       you control.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ----------------------------------------- WEAPON - ROGUE
    // [TRL_074] Serrated Tooth - COST:1 [ATK:1/HP:0]
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give your minions <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 3
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [TRL_077] Gurubashi Hypemon - COST:7 [ATK:5/HP:7]
    // - Set: Troll, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a 1/1 copy of
    //       a <b>Battlecry</b> minion. It costs (1).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [TRL_092] Spirit of the Shark - COST:4 [ATK:0/HP:3]
    // - Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Stealth</b> for 1 turn.
    //       Your minions' <b>Battlecries</b> and <b>Combos</b>
    //       trigger twice.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // - AURA = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [TRL_124] Raiding Party - COST:3
    // - Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: Draw 2 Pirates from your deck.
    //       <b>Combo:</b> And a weapon.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [TRL_126] Captain Hooktusk - COST:8 [ATK:6/HP:3]
    // - Race: Pirate, Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon 3 Pirates from your deck.
    //       Give them <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [TRL_127] Cannon Barrage - COST:6
    // - Faction: Neutral, Set: Troll, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 3 damage to a random enemy.
    //       Repeat for each of your Pirates.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [TRL_156] Stolen Steel - COST:2
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Discover</b> a weapon <i>(from another class)</i>.
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [TRL_157] Walk the Plank - COST:4
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: Destroy an undamaged minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_UNDAMAGED_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [TRL_409] Gral, the Shark - COST:5 [ATK:2/HP:2]
    // - Race: Beast, Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Eat a minion in your deck and
    //       gain its stats.
    //       <b>Deathrattle:</b> Add it to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void TrollCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------ ENCHANTMENT - ROGUE
    // [TRL_409e] Blood in the Water (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: Destroyed {0} and gained its stats.
    // --------------------------------------------------------
}

void TrollCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- SPELL - SHAMAN
    // [TRL_012] Totemic Smash - COST:1
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 2 damage.
    //       <b>Overkill</b>: Summon a basic Totem.
    // --------------------------------------------------------
    // Entourage: CS2_052, CS2_050, NEW1_009, CS2_051
    // --------------------------------------------------------
    // GameTag:
    // - OVERKILL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [TRL_058] Haunting Visions - COST:3
    // - Set: Troll, Rarity: Epic
    // --------------------------------------------------------
    // Text: The next spell you cast this turn costs (3) less.
    //       <b>Discover</b> a spell.
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [TRL_059] Bog Slosher - COST:3 [ATK:3/HP:3]
    // - Race: Elemental, Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Return a friendly minion
    //       to your hand and give it +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [TRL_060] Spirit of the Frog - COST:3 [ATK:0/HP:3]
    // - Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Stealth</b> for 1 turn.
    //       Whenever you cast a spell,
    //       draw a spell from your deck that costs (1) more.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [TRL_082] Big Bad Voodoo - COST:2
    // - Set: Troll, Rarity: Epic
    // --------------------------------------------------------
    // Text: Give a friendly minion "<b>Deathrattle:</b>
    //       Summon a random minion that costs (1) more."
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [TRL_085] Zentimo - COST:3 [ATK:1/HP:3]
    // - Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever you target a minion with a spell, it also
    //       targets adjacent ones.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [TRL_345] Krag'wa, the Frog - COST:6 [ATK:4/HP:6]
    // - Race: Beast, Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Return all spells you played
    //       last turn to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<FuncNumberTask>([](const Playable* playable) {
            Player* player = playable->player;
            const int turn = playable->game->GetTurn();

            std::vector<Card*> playedSpells;
            playedSpells.reserve(10);

            for (auto& history : player->playHistory)
            {
                if (history.sourceCard->GetCardType() == CardType::SPELL &&
                    history.turn == turn - 2)
                {
                    playedSpells.emplace_back(history.sourceCard);
                }
            }

            for (const auto& playedSpell : playedSpells)
            {
                Playable* spell = Entity::GetFromCard(player, playedSpell);
                player->GetHandZone()->Add(spell);

                if (player->GetHandZone()->IsFull())
                {
                    break;
                }
            }

            return 0;
        }));
    cards.emplace("TRL_345", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [TRL_351] Rain of Toads - COST:6
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: Summon three 2/4 Toads with <b>Taunt</b>.
    //       <b>Overload:</b> (3)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 3
    // - OVERLOAD_OWED = 3
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - SHAMAN
    // [TRL_352] Likkim - COST:2 [ATK:1/HP:0]
    // - Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: Has +2 Attack while you have <b>Overloaded</b>
    //       Mana Crystals.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 3
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [TRL_522] Wartbringer - COST:1 [ATK:2/HP:1]
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you played 2 spells this turn,
    //       deal 2 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_SPELLS_PLAYED_THIS_TURN = 2
    // --------------------------------------------------------
}

void TrollCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [TRL_059e] Sloshed (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [TRL_082e] Voodoo (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a minion that costs (1) more.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [TRL_351t] Toad (*) - COST:3 [ATK:2/HP:4]
    // - Race: Beast, Set: Troll
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
}

void TrollCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - WARLOCK
    // [TRL_245] Shriek - COST:1
    // - Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: Discard your lowest Cost card.
    //       Deal 2 damage to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - DISCARD_CARDS = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [TRL_246] Void Contract - COST:8
    // - Set: Troll, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy half of each player's deck.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [TRL_247] Soulwarden - COST:6 [ATK:6/HP:6]
    // - Set: Troll, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add 3 random cards you discarded
    //       this game to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [TRL_249] Grim Rally - COST:1
    // - Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: Destroy a friendly minion. Give your minions +1/+1.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [TRL_251] Spirit of the Bat - COST:2 [ATK:0/HP:3]
    // - Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Stealth</b> for 1 turn.
    //       After a friendly minion dies,
    //       give a minion in your hand +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [TRL_252] High Priestess Jeklik - COST:4 [ATK:3/HP:5]
    // - Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Taunt</b>, <b>Lifesteal</b>
    //       When you discard this,
    //       add 2 copies of it to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // - InvisibleDeathrattle = 1
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::DISCARD));
    cardDef.power.GetTrigger()->triggerActivation = TriggerActivation::HAND;
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::SELF;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<CopyTask>(
        EntityType::SOURCE, ZoneType::HAND, 2) };
    cards.emplace("TRL_252", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [TRL_253] Hir'eek, the Bat - COST:8 [ATK:1/HP:1]
    // - Race: Beast, Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Fill your board with copies
    //       of this minion.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [TRL_257] Blood Troll Sapper - COST:7 [ATK:5/HP:8]
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: After a friendly minion dies,
    //       deal 2 damage to the enemy hero.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [TRL_551] Reckless Diretroll - COST:3 [ATK:2/HP:6]
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Discard your lowest Cost card.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // - DISCARD_CARDS = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [TRL_555] Demonbolt - COST:8
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: Destroy a minion.
    //       Costs (1) less for each minion you control.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
}

void TrollCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TrollCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- SPELL - WARRIOR
    // [TRL_321] Devastate - COST:1
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 4 damage to a damaged minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_DAMAGED_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [TRL_323] Emberscale Drake - COST:5 [ATK:5/HP:5]
    // - Race: Dragon, Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       gain 5 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [TRL_324] Heavy Metal! - COST:6
    // - Faction: Neutral, Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon a random minion with Cost equal to
    //       your Armor <i>(up to 10).</i>
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [TRL_325] Sul'thraze - COST:6 [ATK:4/HP:0]
    // - Set: Troll, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Overkill</b>: You may attack again.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 4
    // - OVERKILL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [TRL_326] Smolderthorn Lancer - COST:3 [ATK:3/HP:2]
    // - Set: Troll, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       destroy a damaged enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_ENEMY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE_AND_DRAGON_IN_HAND = 0
    // - REQ_DAMAGED_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [TRL_327] Spirit of the Rhino - COST:1 [ATK:0/HP:3]
    // - Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Stealth</b> for 1 turn.
    //       Your <b>Rush</b> minions are <b>Immune</b> the turn
    //       they're summoned.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [TRL_328] War Master Voone - COST:4 [ATK:4/HP:3]
    // - Faction: Neutral, Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Copy all Dragons in your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [TRL_329] Akali, the Rhino - COST:8 [ATK:5/HP:5]
    // - Race: Beast, Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Overkill:</b> Draw a <b>Rush</b> minion
    //       from your deck. Give it +5/+5.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - RUSH = 1
    // - OVERKILL = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [TRL_360] Overlord's Whip - COST:3 [ATK:2/HP:0]
    // - Faction: Neutral, Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: After you play a minion, deal 1 damage to it.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 4
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [TRL_362] Dragon Roar - COST:2
    // - Faction: Neutral, Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: Add 2 random Dragons to your hand.
    // --------------------------------------------------------
}

void TrollCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [TRL_329e] Rhino Skin (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: +5/+5.
    // --------------------------------------------------------
}

void TrollCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - NEUTRAL
    // [TRL_010] Half-Time Scavenger - COST:4 [ATK:3/HP:5]
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //       <b>Overkill</b>: Gain 3 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // - OVERKILL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_015] Ticket Scalper - COST:4 [ATK:5/HP:3]
    // - Race: Pirate, Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Overkill</b>: Draw 2 cards.
    // --------------------------------------------------------
    // GameTag:
    // - OVERKILL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_020] Sightless Ranger - COST:5 [ATK:3/HP:4]
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Overkill</b>: Summon two 1/1 Bats.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // - OVERKILL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_057] Serpent Ward - COST:2 [ATK:0/HP:2]
    // - Race: Totem, Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       deal 2 damage to the enemy hero.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_096] Griftah - COST:4 [ATK:4/HP:5]
    // - Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> two cards.
    //       Give one to your opponent at random.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_151] Former Champ - COST:5 [ATK:1/HP:1]
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 5/5 Hotshot.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_312] Spellzerker - COST:2 [ATK:2/HP:3]
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: Has <b>Spell Damage +2</b> while damaged.
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_363] Saronite Taskmaster - COST:1 [ATK:2/HP:3]
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 0/3 Free Agent
    //       with <b>Taunt</b> for your opponent.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_405] Untamed Beastmaster - COST:3 [ATK:3/HP:4]
    // - Set: Troll, Rarity: Epic
    // --------------------------------------------------------
    // Text: Whenever you draw a Beast, give it +2/+2.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_406] Dozing Marksman - COST:2 [ATK:0/HP:4]
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: Has +4 Attack while damaged.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_407] Waterboy - COST:2 [ATK:2/HP:1]
    // - Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your next Hero Power this turn
    //       costs (0).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_503] Scarab Egg - COST:2 [ATK:0/HP:2]
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon three 1/1 Scarabs.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_504] Booty Bay Bookie - COST:2 [ATK:3/HP:3]
    // - Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your opponent a Coin.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_505] Helpless Hatchling - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Reduce the Cost of a Beast
    //       in your hand by (1).
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_506] Gurubashi Chicken - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Overkill:</b> Gain +5 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - OVERKILL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_507] Sharkfin Fan - COST:2 [ATK:2/HP:2]
    // - Race: Pirate, Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: After your hero attacks, summon a 1/1 Pirate.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_508] Regeneratin' Thug - COST:4 [ATK:3/HP:5]
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       restore 2 Health to this minion.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_509] Banana Buffoon - COST:3 [ATK:2/HP:2]
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add 2 Bananas to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_512] Cheaty Anklebiter - COST:2 [ATK:2/HP:1]
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    //       <b>Battlecry:</b> Deal 1 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_513] Mosh'ogg Enforcer - COST:8 [ATK:2/HP:14]
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_514] Belligerent Gnome - COST:2 [ATK:1/HP:4]
    // - Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> If your opponent has 2 or
    //       more minions, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_515] Rabble Bouncer - COST:7 [ATK:2/HP:7]
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       Costs (1) less for each enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_516] Gurubashi Offering - COST:1 [ATK:0/HP:2]
    // - Set: Troll, Rarity: Epic
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       destroy this and gain 8 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - 886 = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_517] Arena Fanatic - COST:4 [ATK:2/HP:3]
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give all minions in your hand +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_520] Murloc Tastyfin - COST:4 [ATK:3/HP:2]
    // - Race: Murloc, Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Draw 2 Murlocs from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_521] Arena Patron - COST:5 [ATK:3/HP:3]
    // - Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Overkill:</b> Summon another Arena Patron.
    // --------------------------------------------------------
    // GameTag:
    // - OVERKILL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_523] Firetree Witchdoctor - COST:2 [ATK:2/HP:2]
    // - Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       <b>Discover</b> a spell.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_524] Shieldbreaker - COST:2 [ATK:2/HP:1]
    // - Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Silence</b> an enemy minion
    //       with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_ENEMY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_MUST_TARGET_TAUNTER = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // - SILENCE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_525] Arena Treasure Chest - COST:4 [ATK:0/HP:4]
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Draw 2 cards.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_526] Dragonmaw Scorcher - COST:5 [ATK:3/HP:6]
    // - Race: Dragon, Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage to all other minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_527] Drakkari Trickster - COST:3 [ATK:3/HP:4]
    // - Set: Troll, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give each player a copy of
    //       a random card from their opponent's deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_528] Linecracker - COST:7 [ATK:5/HP:10]
    // - Set: Troll, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Overkill:</b> Double this minion's Attack.
    // --------------------------------------------------------
    // GameTag:
    // - OVERKILL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_530] Masked Contender - COST:3 [ATK:2/HP:4]
    // - Set: Troll, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a <b>Secret</b>,
    //       play a <b>Secret</b> from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_531] Rumbletusk Shaker - COST:4 [ATK:3/HP:2]
    // - Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 3/2 Rumbletusk Breaker.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_532] Mosh'Ogg Announcer - COST:5 [ATK:6/HP:5]
    // - Set: Troll, Rarity: Epic
    // --------------------------------------------------------
    // Text: Enemies attacking this have a 50% chance to
    //       attack someone else.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_533] Ice Cream Peddler - COST:4 [ATK:3/HP:5]
    // - Set: Troll, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a <b>Frozen</b>
    //       minion, gain 8 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_535] Snapjaw Shellfighter - COST:5 [ATK:3/HP:8]
    // - Set: Troll, Rarity: Epic
    // --------------------------------------------------------
    // Text: Whenever an adjacent minion takes damage,
    //       this minion takes it instead.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_537] Da Undatakah - COST:8 [ATK:8/HP:5]
    // - Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain the <b>Deathrattle</b>
    //       effects of 3 friendly minions that died this game.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_541] Hakkar, the Soulflayer - COST:10 [ATK:9/HP:6]
    // - Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Shuffle a Corrupted Blood into
    //       each player's deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_542] Oondasta - COST:9 [ATK:7/HP:7]
    // - Race: Beast, Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Overkill:</b> Summon a Beast from your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - RUSH = 1
    // - OVERKILL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_546] Ornery Tortoise - COST:3 [ATK:3/HP:5]
    // - Race: Beast, Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 5 damage to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // ------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_550] Amani War Bear - COST:7 [ATK:5/HP:7]
    // - Race: Beast, Set: Troll, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_564] Mojomaster Zihi - COST:6 [ATK:5/HP:5]
    // - Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Set each player to 5 Mana Crystals.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_569] Crowd Roaster - COST:7 [ATK:7/HP:4]
    // - Race: Dragon, Set: Troll, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       deal 7 damage to an enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE_AND_DRAGON_IN_HAND = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_570] Soup Vendor - COST:2 [ATK:1/HP:4]
    // - Set: Troll, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you restore 3 or more Health to your hero,
    //       draw a card.
    // --------------------------------------------------------
}

void TrollCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_020t] Bat (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Troll
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_058e] Visions (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: The next spell you cast this turn costs (3) less.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_071e] Bloody Sails (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_074e] Carnassial (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: <b>Rush</b>.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_077e] Hype! (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: Gurubashi Hypemon made this 1/1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_092e] Power of the Shark (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: Your minions' <b>Battlecries</b> and
    //       <b>Combos</b> trigger twice.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_096e] Guess the Card! (*) - COST:4 [ATK:4/HP:5]
    // - Set: Troll
    // --------------------------------------------------------
    // Text: Guess the card your opponent chose to get a copy.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_111e1] Headhunter's Hatchet (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: Increased Durability.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<Enchant>(Effects::DurabilityN(1)));
    cards.emplace("TRL_111e1", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_119e] The Beast Within (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_151t] Hotshot (*) - COST:5 [ATK:5/HP:5]
    // - Set: Troll
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_243e] Pounce (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("TRL_243e"));
    cards.emplace("TRL_243e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_244e] Predatory Instincts (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: Doubled Health.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_249e] Grim Rally (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_251e] Hir'eek's Offering (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: Increased stats from Spirit of the Bat.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_304e] Battle Ready (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: +2/+2 from Farraki Battleaxe.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_312e] Power of Gurubashi (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: <b>Spell Damage +2</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_316t] Ragnaros the Firelord (*) - COST:8 [ATK:8/HP:8]
    // - Race: Elemental, Faction: Neutral, Set: Troll, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Can't attack. At the end of your turn,
    //       deal 8 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CANT_ATTACK = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_319e] Power of the Dragonhawk (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: Your Hero Power also hits adjacent minions.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_327e] Protected by Spirit of the Rhino (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: <b>Immune</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_363t] Free Agent (*) - COST:1 [ATK:0/HP:3]
    // - Set: Troll
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_390e2] Flameweaving (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: Your next Hero Power deals 2 more damage.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_405e] Warpaint (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_406e] Wrong Side of Da Bed (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: +4 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_407e] High Quality H2O (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: Your Hero Power costs (0).
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_501e] Dark Soul (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: Your healing effects are dealing damage.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_503t] Scarab (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Troll
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_505e] Avenger (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_506e] Ready to Strike (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: +5 Attack.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_507t] Swabbie (*) - COST:1 [ATK:1/HP:1]
    // - Race: Pirate, Set: Troll
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [TRL_509t] Bananas (*) - COST:1
    // - Set: Troll
    // --------------------------------------------------------
    // Text: Give a minion +1/+1.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_509te] Bananas (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: Has +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_514e] Belligerent (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_517e2] WHOOOOO! (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_528e] Crazed (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: Doubled Attack.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [TRL_531t] Rumbletusk Breaker (*) - COST:2 [ATK:3/HP:2]
    // - Set: Troll
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_537e] Undatakah Deathrattles (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [TRL_541t] Corrupted Blood (*) - COST:1
    // - Set: Troll
    // --------------------------------------------------------
    // Text: <b>Casts When Drawn</b>
    //       Take 3 damage. After you draw,
    //       shuffle two copies of this into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // - TOPDECK = 1
    // --------------------------------------------------------
    // RefTag:
    // - CASTSWHENDRAWN = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_545e] Rejuvenated (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: +4/+4 and <b>Taunt</b>.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [TRL_901e] Blessing of Halazzi (*) - COST:0
    // - Set: Troll
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
}

void TrollCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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