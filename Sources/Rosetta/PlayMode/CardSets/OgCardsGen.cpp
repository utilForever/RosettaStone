// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/CardSets/OgCardsGen.hpp>
#include <Rosetta/PlayMode/Cards/CardPowers.hpp>

namespace RosettaStone::PlayMode
{
void OgCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void OgCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- HERO_POWER - PALADIN
    // [OG_006b] The Tidal Hand (*) - COST:2
    // - Set: Og
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>b
    //       Summon a 1/1 Silver Hand Murloc.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
}

void OgCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - DRUID
    // [OG_044] Fandral Staghelm - COST:4 [ATK:3/HP:5]
    // - Set: Og, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Your <b>Choose One</b> cards and powers
    //       have both effects combined.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::PLAYER, EffectList{ std::make_shared<Effect>(
                              GameTag::CHOOSE_BOTH, EffectOperator::SET, 1) }));
    cards.emplace("OG_044", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [OG_047] Feral Rage - COST:3
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Give your hero +4 Attack this turn;
    //       or Gain 8 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cardDef.property.chooseCardIDs = ChooseCardIDs{ "OG_047a", "OG_047b" };
    cards.emplace("OG_047", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [OG_048] Mark of Y'Shaarj - COST:2
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion +2/+2.
    //       If it's a Beast, draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [OG_051] Forbidden Ancient - COST:1 [ATK:1/HP:1]
    // - Set: Og, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Spend all your Mana.
    //       Gain +1/+1 for each mana spent.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [OG_188] Klaxxi Amber-Weaver - COST:4 [ATK:4/HP:5]
    // - Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your C'Thun has at least 10 Attack,
    //       gain +5 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - RITUAL = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [OG_195] Wisps of the Old Gods - COST:7
    // - Set: Og, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Summon seven 1/1 Wisps;
    //       or Give your minions +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [OG_202] Mire Keeper - COST:4 [ATK:3/HP:3]
    // - Set: Og, Rarity: rare
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Summon a 2/2 Slime;
    //       or Gain an empty Mana Crystal.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [OG_293] Dark Arakkoa - COST:6 [ATK:5/HP:7]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Give your C'Thun +3/+3
    //       <i>(wherever it is).</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // - RITUAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [OG_313] Addled Grizzly - COST:3 [ATK:2/HP:2]
    // - Race: Beast, Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you summon a minion, give it +1/+1.
    // --------------------------------------------------------
}

void OgCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------ ENCHANTMENT - DRUID
    // [OG_045a] Nerubian Spores (*) - COST:0
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: Get a Beast when this dies.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [OG_047a] Evolve Spines (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Give your hero +4 Attack this turn.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("OG_047e", EntityType::HERO));
    cards.emplace("OG_047a", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [OG_047b] Evolve Scales (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Gain 8 Armor.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ArmorTask>(8));
    cards.emplace("OG_047b", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [OG_047e] Spines (*) - COST:0
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: +4 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("OG_047e"));
    cards.emplace("OG_047e", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [OG_048e] Mark of Y'Shaarj (*) - COST:0
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [OG_051e] Forbidden Power (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [OG_195a] Many Wisps (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Summon seven 1/1 Wisps.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [OG_195b] Big Wisps (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Give your minions +2/+2.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [OG_195c] Wisp (*) - COST:0 [ATK:1/HP:1]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [OG_202a] Y'Shaarj's Strength (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Summon a 2/2 Slime.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [OG_202ae] Y'Shaarj's Strength (*) - COST:0
    // - Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: +3/+3.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [OG_202b] Yogg-Saron's Magic (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Gain an empty Mana Crystal.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [OG_202c] Slime (*) - COST:2 [ATK:2/HP:2]
    // - Set: Og
    // --------------------------------------------------------
}

void OgCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- SPELL - HUNTER
    // [OG_045] Infest - COST:3
    // - Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give your minions "<b>Deathrattle:</b>
    //       Add a random Beast to your hand."
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [OG_061] On the Hunt - COST:1
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 1 damage. Summon a 1/1 Mastiff.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [OG_179] Fiery Bat - COST:1 [ATK:2/HP:1]
    // - Race: Beast, Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 1 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [OG_211] Call of the Wild - COST:9
    // - Set: Og, Rarity: Epic
    // --------------------------------------------------------
    // Text: Summon all three Animal Companions.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [OG_216] Infested Wolf - COST:4 [ATK:3/HP:3]
    // - Race: Beast, Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon two 1/1 Spiders.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [OG_292] Forlorn Stalker - COST:3 [ATK:4/HP:2]
    // - Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give all <b>Deathrattle</b>
    //       minions in your hand +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [OG_308] Giant Sand Worm - COST:8 [ATK:8/HP:8]
    // - Race: Beast, Set: Og, Rarity: Epic
    // --------------------------------------------------------
    // Text: Whenever this attacks and kills a minion,
    //       it may attack again.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [OG_309] Princess Huhuran - COST:5 [ATK:6/HP:5]
    // - Race: Beast, Set: Og, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Trigger a friendly minion's
    //       <b>Deathrattle</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
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

    // ---------------------------------------- MINION - HUNTER
    // [OG_325] Carrion Grub - COST:3 [ATK:2/HP:5]
    // - Race: Beast, Set: Og, Rarity: Common
    // --------------------------------------------------------
}

void OgCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- MINION - HUNTER
    // [OG_061t] Mastiff (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Og
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [OG_216a] Spider (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Og
    // --------------------------------------------------------
}

void OgCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------- SPELL - MAGE
    // [OG_081] Shatter - COST:2
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: Destroy a <b>Frozen</b> minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_FROZEN_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [OG_083] Twilight Flamecaller - COST:3 [ATK:2/HP:2]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [OG_085] Demented Frostcaller - COST:4 [ATK:2/HP:4]
    // - Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: After you cast a spell, <b>Freeze</b> a random enemy.
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [OG_086] Forbidden Flame - COST:0
    // - Set: Og, Rarity: Epic
    // --------------------------------------------------------
    // Text: Spend all your Mana.
    //       Deal that much damage to a minion.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [OG_087] Servant of Yogg-Saron - COST:5 [ATK:5/HP:4]
    // - Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Cast a random spell that costs
    //       (5) or less <i>(targets chosen randomly)</i>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [OG_090] Cabalist's Tome - COST:5
    // - Set: Og, Rarity: Epic
    // --------------------------------------------------------
    // Text: Add 3 random Mage spells to your hand.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [OG_120] Anomalus - COST:8 [ATK:8/HP:6]
    // - Race: Elemental, Set: Og, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 8 damage to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [OG_207] Faceless Summoner - COST:6 [ATK:5/HP:5]
    // - Set: Og, Rarity: Common
    // -------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a random 3-Cost minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [OG_303] Cult Sorcerer - COST:2 [ATK:3/HP:2]
    // - Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b><b>Spell Damage</b> +1</b>
    //       After you cast a spell, give your C'Thun +1/+1
    //       <i>(wherever it is).</i>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // - RITUAL = 1
    // --------------------------------------------------------
}

void OgCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void OgCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - PALADIN
    // [OG_006] Vilefin Inquisitor - COST:1 [ATK:1/HP:3]
    // - Race: Murloc, Set: Og, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your Hero Power becomes
    //       'Summon a 1/1 Murloc.'
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [OG_198] Forbidden Healing - COST:0
    // - Set: Og, Rarity: Epic
    // --------------------------------------------------------
    // Text: Spend all your Mana. Restore twice that much Health.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [OG_221] Selfless Hero - COST:1 [ATK:2/HP:1]
    // - Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give a random friendly minion
    //       <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - PALADIN
    // [OG_222] Rallying Blade - COST:3 [ATK:3/HP:0]
    // - Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give +1/+1 to your minions
    //       with <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [OG_223] Divine Strength - COST:1
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion +1/+2.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [OG_229] Ragnaros, Lightlord - COST:8 [ATK:8/HP:8]
    // - Race: Elemental, Set: Og, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       restore 8 Health to a damaged friendly character.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<IncludeTask>(EntityType::FRIENDS),
        std::make_shared<FilterStackTask>(SelfCondList{
            std::make_shared<SelfCondition>(SelfCondition::IsDamaged()) }),
        std::make_shared<RandomTask>(EntityType::STACK, 1),
        std::make_shared<HealTask>(EntityType::STACK, 8)
    };
    cards.emplace("OG_229", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [OG_273] Stand Against Darkness - COST:4
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: Summon five 1/1 Silver Hand Recruits.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("CS2_101t", 5, SummonSide::SPELL));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("OG_273", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [OG_310] Steward of Darkshire - COST:3 [ATK:3/HP:3]
    // - Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you summon a 1-Health minion,
    //       give it <b>Divine Shield</b>.
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [OG_311] A Light in the Darkness - COST:2
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Discover</b> a minion. Give it +1/+1.
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
}

void OgCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - PALADIN
    // [OG_006a] Silver Hand Murloc (*) - COST:1 [ATK:1/HP:1]
    // - Race: Murloc, Set: Og
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [OG_222e] Rally (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
}

void OgCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- SPELL - PRIEST
    // [OG_094] Power Word: Tentacles - COST:5
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion +2/+6.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [OG_096] Twilight Darkmender - COST:5 [ATK:6/HP:5]
    // - Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your C'Thun has at least 10 Attack,
    //       restore 10 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - RITUAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [OG_100] Shadow Word: Horror - COST:4
    // - Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: Destroy all minions with 2 or less Attack.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [OG_101] Forbidden Shaping - COST:0
    // - Set: Og, Rarity: Epic
    // --------------------------------------------------------
    // Text: Spend all your Mana.
    //       Summon a random minion that costs that much.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [OG_104] Embrace the Shadow - COST:2
    // - Set: Og, Rarity: Epic
    // --------------------------------------------------------
    // Text: This turn, your healing effects deal damage instead.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [OG_234] Darkshire Alchemist - COST:5 [ATK:4/HP:5]
    // - Set: Og, Rarity: common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 5 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_NONSELF_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [OG_316] Herald Volazj - COST:6 [ATK:5/HP:5]
    // - Set: Og, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 1/1 copy of each of
    //       your other minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [OG_334] Hooded Acolyte - COST:4 [ATK:3/HP:6]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever a character is healed, give your
    //       C'Thun +1/+1 <i>(wherever it is).</i>
    // --------------------------------------------------------
    // GameTag:
    // - RITUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [OG_335] Shifting Shade - COST:4 [ATK:4/HP:3]
    // - Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Copy a card from your
    //       opponent's deck and add it to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
}

void OgCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- ENCHANTMENT - PRIEST
    // [OG_094e] Tentacles (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: +2/+6
    // --------------------------------------------------------
}

void OgCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - ROGUE
    // [OG_070] Bladed Cultist - COST:1 [ATK:1/HP:2]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddComboTask(
        std::make_shared<AddEnchantmentTask>("OG_070e", EntityType::SOURCE));
    cards.emplace("OG_070", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [OG_072] Journey Below - COST:1
    // - Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Discover</b> a <b>Deathrattle</b> card.
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [OG_073] Thistle Tea - COST:6
    // - Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: Draw a card. Add 2 extra copies of it to your hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [OG_080] Xaril, Poisoned Mind - COST:4 [ATK:3/HP:2]
    // - Set: Og, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry and Deathrattle:</b> Add a random
    //       Toxin card to your hand.
    // --------------------------------------------------------
    // Entourage: OG_080d, OG_080e, OG_080f, OG_080c, OG_080b
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [OG_176] Shadow Strike - COST:3
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 5 damage to an undamaged character.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_UNDAMAGED_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [OG_267] Southsea Squidface - COST:4 [ATK:4/HP:4]
    // - Race: Pirate, Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give your weapon +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [OG_282] Blade of C'Thun - COST:9 [ATK:4/HP:4]
    // - Set: Og, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a minion.
    //       Add its Attack and Health to your C'Thun's
    //       <i>(wherever it is).</i>
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - RITUAL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [OG_291] Shadowcaster - COST:5 [ATK:4/HP:4]
    // - Set: Og, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a friendly minion.
    //       Add a 1/1 copy to your hand that costs (1).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [OG_330] Undercity Huckster - COST:2 [ATK:2/HP:2]
    // - Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a random class card
    //       to your hand <i>(from your opponent's class)</i>.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
}

void OgCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [OG_070e] Thirsty Blades (*) - COST:0
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("OG_070e"));
    cards.emplace("OG_070e", cardDef);

    // ------------------------------------------ SPELL - ROGUE
    // [OG_080b] Kingsblood Toxin (*) - COST:1
    // - Set: Og
    // --------------------------------------------------------
    // Text: Draw a card.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [OG_080c] Bloodthistle Toxin (*) - COST:1
    // - Set: Og
    // --------------------------------------------------------
    // Text: Return a friendly minion to your hand.
    //       It costs (2) less.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [OG_080d] Briarthorn Toxin (*) - COST:1
    // - Set: Og
    // --------------------------------------------------------
    // Text: Give a minion +3 Attack.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [OG_080e] Fadeleaf Toxin (*) - COST:1
    // - Set: Og
    // --------------------------------------------------------
    // Text: Give a friendly minion <b>Stealth</b>
    //       until your next turn.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [OG_080f] Firebloom Toxin (*) - COST:1
    // - Set: Og
    // --------------------------------------------------------
    // Text: Deal 2 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [OG_267e] Squid Oil Sheen (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: +2 Attack
    // --------------------------------------------------------
}

void OgCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- SPELL - SHAMAN
    // [OG_023] Primal Fusion - COST:1
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion +1/+1 for each of your Totems.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [OG_024] Flamewreathed Faceless - COST:4 [ATK:7/HP:7]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 2
    // - OVERLOAD_OWED = 2
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [OG_026] Eternal Sentinel - COST:2 [ATK:3/HP:2]
    // - Set: Og, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Unlock your <b>Overloaded</b>
    //       Mana Crystals.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [OG_027] Evolve - COST:1
    // - Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: Transform your minions into random minions that
    //       cost (1) more.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [OG_028] Thing from Below - COST:6 [ATK:5/HP:5]
    // - Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       Costs (1) less for each Totem you've summoned
    //       this game.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - SHAMAN
    // [OG_031] Hammer of Twilight - COST:5 [ATK:4/HP:0]
    // - Set: Og, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 4/2 Elemental.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [OG_206] Stormcrack - COST:2
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 4 damage to a minion. <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // - OVERLOAD_OWED = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [OG_209] Hallazeal the Ascended - COST:5 [ATK:4/HP:6]
    // - Race: Elemental, Set: Og, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever your spells deal damage,
    //       restore that much Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [OG_328] Master of Evolution - COST:4 [ATK:4/HP:5]
    // - Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Transform a friendly minion
    //       into a random one that costs (1) more.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
}

void OgCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- MINION - SHAMAN
    // [OG_031a] Twilight Elemental (*) - COST:3 [ATK:4/HP:2]
    // - Race: Elemental, Set: Og, Rarity: Epic
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [TB_OG_027] Evolve (*) - COST:1
    // - Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: Transform your minions into random minions that
    //       cost (1) more.
    // --------------------------------------------------------
}

void OgCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - WARLOCK
    // [OG_109] Darkshire Librarian - COST:2 [ATK:3/HP:2]
    // - Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Discard a random card.
    //       <b>Deathrattle:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DiscardTask>(1));
    cardDef.power.AddDeathrattleTask(std::make_shared<DrawTask>(1));
    cards.emplace("OG_109", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [OG_113] Darkshire Councilman - COST:3 [ATK:1/HP:5]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: After you summon a minion, gain +1 Attack.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [OG_114] Forbidden Ritual - COST:0
    // - Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: Spend all your Mana. Summon that many 1/1 Tentacles.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [OG_116] Spreading Madness - COST:3
    // - Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 9 damage randomly split among ALL characters.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [OG_118] Renounce Darkness - COST:2
    // - Set: Og, Rarity: Epic
    // --------------------------------------------------------
    // Text: Replace your Hero Power and Warlock cards with
    //       another class's. The cards cost (1) less.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [OG_121] Cho'gall - COST:7 [ATK:7/HP:7]
    // - Set: Og, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> The next spell you cast this turn
    //       costs Health instead of Mana.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [OG_239] DOOM! - COST:10
    // - Set: Og, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy all minions. Draw a card for each.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [OG_241] Possessed Villager - COST:1 [ATK:1/HP:1]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 1/1 Shadowbeast.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<SummonTask>("OG_241a", SummonSide::DEATHRATTLE));
    cards.emplace("OG_241", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [OG_302] Usher of Souls - COST:5 [ATK:5/HP:6]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever a friendly minion dies,
    //       give your C'Thun +1/+1 <i>(wherever it is).</i>
    // --------------------------------------------------------
    // GameTag:
    // - RITUAL = 1
    // --------------------------------------------------------
}

void OgCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [OG_113e] Power of the People (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [OG_114a] Icky Tentacle (*) - COST:1 [ATK:1/HP:1]
    // - Set: Og
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [OG_241a] Shadowbeast (*) - COST:1 [ATK:1/HP:1]
    // - Set: Og
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("OG_241a", cardDef);
}

void OgCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- WEAPON - WARRIOR
    // [OG_033] Tentacles for Arms - COST:5 [ATK:2/HP:0]
    // - Set: Og, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Return this to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [OG_149] Ravaging Ghoul - COST:3 [ATK:3/HP:3]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage to all other minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [OG_218] Bloodhoof Brave - COST:4 [ATK:2/HP:6]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       Has +3 Attack while damaged.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - ENRAGED = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(Triggers::EnrageTrigger("OG_218e")));
    cards.emplace("OG_218", cardDef);

    // --------------------------------------- MINION - WARRIOR
    // [OG_220] Malkorok - COST:7 [ATK:6/HP:5]
    // - Set: Og, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Equip a random weapon.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [OG_276] Blood Warriors - COST:3
    // - Set: Og, Rarity: Epic
    // --------------------------------------------------------
    // Text: Add a copy of each damaged friendly minion to your hand.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [OG_301] Ancient Shieldbearer - COST:7 [ATK:6/HP:6]
    // - Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your C'Thun has at least
    //       10 Attack, gain 10 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - RITUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [OG_312] N'Zoth's First Mate - COST:1 [ATK:1/HP:1]
    // - Race: Pirate, Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Equip a 1/3 Rusty Hook.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [OG_314] Blood To Ichor - COST:1
    // - Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 1 damage to a minion.
    //       If it survives, summon a 2/2 Slime.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [OG_315] Bloodsail Cultist - COST:3 [ATK:3/HP:4]
    // - Race: Pirate, Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control another Pirate,
    //       give your weapon +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void OgCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- WEAPON - WARRIOR
    // [OG_058] Rusty Hook (*) - COST:1 [ATK:1/HP:0]
    // - Set: Og
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 3
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [OG_312e] Upgraded (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Increased Durability.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [OG_314b] Slime (*) - COST:2 [ATK:2/HP:2]
    // - Set: Og
    // --------------------------------------------------------
}

void OgCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - NEUTRAL
    // [OG_034] Silithid Swarmer - COST:3 [ATK:3/HP:5]
    // - Race: Beast, Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: Can only attack if your hero attacked this turn.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_042] Y'Shaarj, Rage Unbound - COST:10 [ATK:10/HP:10]
    // - Set: Og, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       put a minion from your deck into the battlefield.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_082] Evolved Kobold - COST:4 [ATK:2/HP:2]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Spell Damage +2</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 2
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_102] Darkspeaker - COST:5 [ATK:3/HP:6]
    // - Set: Og, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Swap stats with a friendly minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_122] Mukla, Tyrant of the Vale - COST:6 [ATK:5/HP:5]
    // - Race: Beast, Set: Og, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add 2 Bananas to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_123] Shifter Zerus - COST:1 [ATK:1/HP:1]
    // - Set: Og, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Each turn this is in your hand,
    //       transform it into a random minion.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_131] Twin Emperor Vek'lor - COST:7 [ATK:4/HP:6]
    // - Set: Og, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b><b>Taunt</b>
    //       Battlecry:</b> If your C'Thun has at least 10 Attack,
    //       summon another Emperor.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // - BATTLECRY = 1
    // - RITUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_133] N'Zoth, the Corruptor - COST:10 [ATK:5/HP:7]
    // - Set: Og, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon your <b>Deathrattle</b>
    //       minions that died this game.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_134] Yogg-Saron, Hope's End - COST:10 [ATK:7/HP:5]
    // - Set: Og, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Cast a random spell for each spell
    //       you've cast this game <i>(targets chosen randomly)</i>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_138] Nerubian Prophet - COST:6 [ATK:4/HP:4]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       reduce this card's Cost by (1).
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_141] Faceless Behemoth - COST:10 [ATK:10/HP:10]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_142] Eldritch Horror - COST:8 [ATK:6/HP:10]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_145] Psych-o-Tron - COST:5 [ATK:3/HP:4]
    // - Race: Mechanical, Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_147] Corrupted Healbot - COST:5 [ATK:6/HP:6]
    // - Race: Mechanical, Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Restore 8 Health to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_150] Aberrant Berserker - COST:4 [ATK:3/HP:5]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Enrage:</b> +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_151] Tentacle of N'Zoth - COST:1 [ATK:1/HP:1]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 1 damage to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_152] Grotesque Dragonhawk - COST:7 [ATK:5/HP:5]
    // - Race: Beast, Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - WINDFURY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_153] Bog Creeper - COST:7 [ATK:6/HP:8]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_156] Bilefin Tidehunter - COST:2 [ATK:2/HP:1]
    // - Race: Murloc, Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 1/1 Ooze with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_158] Zealous Initiate - COST:1 [ATK:1/HP:1]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give a random friendly minion +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_161] Corrupted Seer - COST:6 [ATK:2/HP:3]
    // - Race: Murloc, Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 2 damage to all non-Murloc minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_162] Disciple of C'Thun - COST:3 [ATK:2/HP:1]
    // - Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 2 damage.
    //       Give your C'Thun +2/+2 <i>(wherever it is)</i>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - RITUAL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_NONSELF_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_173] Blood of The Ancient One - COST:9 [ATK:9/HP:9]
    // - Set: Og, Rarity: Epic
    // --------------------------------------------------------
    // Text: If you control two of these at the end of your turn,
    //       merge them into 'The Ancient One'.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_174] Faceless Shambler - COST:4 [ATK:1/HP:1]
    // - Set: Og, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Copy a friendly minion's Attack
    //       and Health.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_200] Validated Doomsayer - COST:5 [ATK:0/HP:7]
    // - Set: Og, Rarity: Epic
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       set this minion's Attack to 7.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_247] Twisted Worgen - COST:2 [ATK:3/HP:1]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_248] Am'gam Rager - COST:3 [ATK:1/HP:5]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_249] Infested Tauren - COST:4 [ATK:2/HP:3]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Summon a 2/2 Slime.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_254] Eater of Secrets - COST:4 [ATK:2/HP:4]
    // - Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy all enemy <b>Secrets</b>.
    //       Gain +1/+1 for each.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_255] Doomcaller - COST:8 [ATK:7/HP:9]
    // - Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your C'Thun +2/+2
    //       <i>(wherever it is).</i>
    //       If it's dead, shuffle it into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - RITUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_256] Spawn of N'Zoth - COST:3 [ATK:2/HP:2]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give your minions +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_271] Scaled Nightmare - COST:6 [ATK:2/HP:8]
    // - Race: Dragon, Set: Og, Rarity: Epic
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       double this minion's Attack.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_272] Twilight Summoner - COST:4 [ATK:1/HP:1]
    // - Set: Og, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 5/5 Faceless Destroyer.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_280] C'Thun - COST:10 [ATK:6/HP:6]
    // - Set: Og, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal damage equal to this
    //       minion's Attack randomly split among all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_281] Beckoner of Evil - COST:2 [ATK:2/HP:3]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your C'Thun +2/+2
    //       <i>(wherever it is).</i>
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - RITUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_283] C'Thun's Chosen - COST:4 [ATK:4/HP:2]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    //       <b>Battlecry:</b> Give your C'Thun +2/+2
    //       <i>(wherever it is).</i>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // - BATTLECRY = 1
    // - RITUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_284] Twilight Geomancer - COST:2 [ATK:1/HP:4]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Give your C'Thun <b>Taunt</b>
    //       <i>(wherever it is).</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1a
    // - RITUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_286] Twilight Elder - COST:3 [ATK:3/HP:4]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: At the end of your turn, give your C'Thun +1/+1
    //       <i>(wherever it is).</i>
    // --------------------------------------------------------
    // GameTag:
    // - RITUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_290] Ancient Harbinger - COST:6 [ATK:4/HP:6]
    // - Set: Og, Rarity: Epic
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       put a 10-Cost minion from your deck into your hand.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_295] Cult Apothecary - COST:5 [ATK:4/HP:4]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> For each enemy minion,
    //       restore 2 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_300] The Boogeymonster - COST:8 [ATK:6/HP:7]
    // - Set: Og, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever this attacks and kills a minion, gain +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_317] Deathwing, Dragonlord - COST:10 [ATK:12/HP:12]
    // - Race: Dragon, Set: Og, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Put all Dragons from your hand
    //       into the battlefield.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_318] Hogger, Doom of Elwynn - COST:7 [ATK:6/HP:6]
    // - Set: Og, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever this minion takes damage,
    //       summon a 2/2 Gnoll with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_320] Midnight Drake - COST:4 [ATK:1/HP:4]
    // - Race: Dragon, Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain +1 Attack for each other card
    //       in your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_321] Crazed Worshipper - COST:5 [ATK:3/HP:6]
    // - Set: Og, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Taunt.</b>
    //       Whenever this minion takes damage,
    //       give your C'Thun +1/+1 <i>(wherever it is).</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - RITUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_322] Blackwater Pirate - COST:4 [ATK:2/HP:5]
    // - Race: Pirate, Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: Your weapons cost (2) less.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_323] Polluted Hoarder - COST:4 [ATK:4/HP:2]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_326] Duskboar - COST:2 [ATK:4/HP:1]
    // - Race: Beast, Set: Og, Rarity: Common
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_327] Squirming Tentacle - COST:3 [ATK:2/HP:4]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_337] Cyclopian Horror - COST:4 [ATK:3/HP:3]
    // - Set: Og, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Taunt</b>.
    //       <b>Battlecry:</b> Gain +1 Health for each enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_338] Nat, the Darkfisher - COST:2 [ATK:2/HP:4]
    // - Set: Og, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the start of your opponent's turn,
    //       they have a 50% chance to draw an extra card.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_339] Skeram Cultist - COST:6 [ATK:7/HP:6]
    // - Set: Og, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your C'Thun +2/+2
    //       <i>(wherever it is).</i>
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - RITUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_340] Soggoth the Slitherer - COST:9 [ATK:5/HP:9]
    // - Set: Og, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // --------------------------------------------------------
}

void OgCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_010e] Shadowy (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: 1/1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_023t] Primally Infused (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_080ae] Bloodthistle (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_080de] Fadeleaf (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Stealthed until your next turn.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_080ee] BriarthorTn (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: +3 Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_102e] Power Transfer (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Swapped stats.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_104e] Embracing the Shadow (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Your healing effects are dealing damage.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_118e] Renounce Darkness Deck Ench (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_118f] New Calling (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Cost reduced.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_121e] Dark Power (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Your next spell costs Health instead of Mana.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_123e] Shifting (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Transforming into random minions.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_138e] Will of the Vizier (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Reduced Cost.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_150e] Enraged (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_156a] Ooze (*) - COST:1 [ATK:1/HP:1]
    // - Set: Og, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_158e] Secrets of the Cult (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_173a] The Ancient One (*) - COST:9 [ATK:30/HP:30]
    // - Set: Og, Rarity: Epic
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_174e] Faceless (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Copying stats.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_188e] Amber Carapace (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: +5 Health.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_195e] Enormous (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_200e] Doom Free (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Attack set to 7.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_218e] Enraged (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: +3 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ENRAGED = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("OG_218e"));
    cards.emplace("OG_218e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_223e] Optimism (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: +1/+2.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_249a] Slime (*) - COST:2 [ATK:2/HP:2]
    // - Set: Og
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_254e] Secretly Sated (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_256e] Slimed (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_270a] Nerubian Soldier (*) - COST:8 [ATK:7/HP:7]
    // - Set: Og
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_271e] Terrifying Visage (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Attack increased.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_272t] Faceless Destroyer (*) - COST:4 [ATK:5/HP:5]
    // - Set: Og
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_279] C'Thun (*) - COST:10 [ATK:6/HP:6]
    // - Set: Og, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal damage equal to this
    //       minion's Attack randomly split among all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_281e] Fanatic Devotion (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Increased Stats.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_282e] Devotion of the Blade (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_284e] Geomancy (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Has <b>Taunt</b>.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_290e] Caller Devotion (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_291e] Flickering Darkness (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Shadowcaster made this 1/1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_292e] Night's Devotion (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_293e] Arrakoa Devotion (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: +5/+5.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_293f] Dark Guardian (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Increased Stats.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_300e] Tasty! (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_302e] Soul Power (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_303e] Sorcerous Devotion (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_311e] Beacon of Hope (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_313e] Addled (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_315e] Reforged (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_316k] Shadowy (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: 1/1.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_318t] Gnoll (*) - COST:2 [ATK:2/HP:2]
    // - Set: Og
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [OG_319] Twin Emperor Vek'nilash (*) - COST:7 [ATK:4/HP:6]
    // - Set: Og
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_320e] Hour of Corruption (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_321e] Power of Faith (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_337e] Eve of Destruction (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: Stats increased.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [OG_339e] Vassal's Subservience (*) - COST:0
    // - Set: Og
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
}

void OgCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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