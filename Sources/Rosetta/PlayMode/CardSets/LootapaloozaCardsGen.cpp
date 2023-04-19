// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/CardSets/LootapaloozaCardsGen.hpp>
#include <Rosetta/PlayMode/Cards/CardPowers.hpp>

namespace RosettaStone::PlayMode
{
void LootapaloozaCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void LootapaloozaCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void LootapaloozaCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ SPELL - DRUID
    // [LOOT_047] Barkskin - COST:1
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion +3 Health. Gain 3 Armor.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [LOOT_048] Ironwood Golem - COST:4 [ATK:3/HP:6]
    // - Faction: Neutral, Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       Can only attack if you have 3 or more Armor.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [LOOT_051] Lesser Jasper Spellstone - COST:1
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 2 damage to a minion.
    //       <i>(Gain 3 Armor to upgrade.)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 3
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    // RefTag:
    // - ARMOR = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [LOOT_054] Branching Paths - COST:4
    // - Set: Lootapalooza, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Choose Twice -</b> Draw a card;
    //       Give your minions +1 Attack; Gain 6 Armor.
    // --------------------------------------------------------
    // Entourage: LOOT_054d, LOOT_054b, LOOT_054c
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [LOOT_056] Astral Tiger - COST:4 [ATK:3/HP:5]
    // - Set: Lootapalooza, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Shuffle a copy of this minion
    //       into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [LOOT_309] Oaken Summons - COST:4
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: Gain 6 Armor.
    //       <b>Recruit</b> a minion that costs (4) or less.
    // --------------------------------------------------------
    // RefTag:
    // - RECRUIT = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [LOOT_314] Grizzled Guardian - COST:8 [ATK:3/HP:5]
    // - Race: Beast, Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> <b>Recruit</b> 2 minions
    //       that cost (4) or less.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - RECRUIT = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [LOOT_329] Ixlid, Fungal Lord - COST:5 [ATK:2/HP:4]
    // - Race: Elemental, Set: Lootapalooza, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you play a minion, summon a copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [LOOT_351] Greedy Sprite - COST:3 [ATK:3/HP:1]
    // - Set: lootapalooza, Rarity: rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Gain an empty Mana Crystal.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- WEAPON - DRUID
    // [LOOT_392] Twig of the World Tree - COST:4 [ATK:1/HP:0]
    // - Set: Lootapalooza, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Gain 10 Mana Crystals.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DURABILITY = 5
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
}

void LootapaloozaCardsGen::AddDruidNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ SPELL - DRUID
    // [LOOT_051t1] Jasper Spellstone (*) - COST:1
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 4 damage to a minion.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 3
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    // RefTag:
    // - ARMOR = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [LOOT_051t2] Greater Jasper Spellstone (*) - COST:1
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 6 damage to a minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [LOOT_054b] Explore the Darkness (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Give your minions +1 Attack.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [LOOT_054c] Loot the Chest (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Gain 6 Armor.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [LOOT_054d] Eat the Mushroom (*) - COST:0
    // - Faction: Neutral, Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Draw a card.
    // --------------------------------------------------------
}

void LootapaloozaCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- SPELL - HUNTER
    // [LOOT_077] Flanking Strike - COST:4
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 3 damage to a minion. Summon a 3/3 Wolf.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [LOOT_078] Cave Hydra - COST:3 [ATK:2/HP:4]
    // - Race: Beast, Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: Also damages the minions next to whomever
    //       this attacks.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [LOOT_079] Wandering Monster - COST:2
    // - Faction: Neutral, Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When an enemy attacks your hero,
    //       summon a 3-Cost minion as the new target.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [LOOT_080] Lesser Emerald Spellstone - COST:5
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon two 3/3 Wolves.
    //       <i>(Play a <b>Secret</b> to upgrade.)</i>
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - HUNTER
    // [LOOT_085] Rhok'delar - COST:7 [ATK:4/HP:0]
    // - Set: Lootapalooza, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck has no minions,
    //       fill your hand with Hunter spells.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DURABILITY = 2
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [LOOT_217] To My Side! - COST:6
    // - Set: Lootapalooza, Rarity: Epic
    // --------------------------------------------------------
    // Text: Summon an Animal Companion,
    //       or 2 if your deck has no minions.
    // --------------------------------------------------------
    // Entourage: NEW1_032, NEW1_033, NEW1_034
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - HUNTER
    // [LOOT_222] Candleshot - COST:1 [ATK:1/HP:0]
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Immune</b> while attacking.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 3
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TARGET));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::HERO;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "DS1_188e", EntityType::HERO) };
    cards.emplace("LOOT_222", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [LOOT_511] Kathrena Winterwisp - COST:8 [ATK:6/HP:6]
    // - Set: Lootapalooza, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry and Deathrattle:</b> <b>Recruit</b> a Beast.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RECRUIT = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [LOOT_520] Seeping Oozeling - COST:6 [ATK:5/HP:4]
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain the <b>Deathrattle</b>
    //       of a random minion in your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [LOOT_522] Crushing Walls - COST:7
    // - Set: Lootapalooza, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy your opponent's left and right-most minions.
    // --------------------------------------------------------
}

void LootapaloozaCardsGen::AddHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- MINION - HUNTER
    // [LOOT_077t] Wolf (*) - COST:3 [ATK:3/HP:3]
    // - Race: Beast, Set: Lootapalooza
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [LOOT_080t2] Emerald Spellstone (*) - COST:5
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon three 3/3 Wolves.
    //       <i>(Play a <b>Secret</b> to upgrade.)</i>
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [LOOT_080t3] Greater Emerald Spellstone (*) - COST:5
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon four 3/3 Wolves.
    // --------------------------------------------------------
}

void LootapaloozaCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------- SPELL - MAGE
    // [LOOT_101] Explosive Runes - COST:3
    // - Faction: Neutral, Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After your opponent plays a minion,
    //       deal 6 damage to it and any excess to their hero.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // - ImmuneToSpellpower = 1
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
            ComplexTask::ActivateSecret(TaskList{ std::make_shared<CustomTask>(
                [](const Player* player, Entity* source, Playable* target) {
                    if (!target)
                    {
                        return;
                    }

                    const auto realSource = dynamic_cast<Playable*>(source);
                    const auto realTarget = dynamic_cast<Character*>(target);

                    const int targetHealth = realTarget->GetHealth();
                    Generic::TakeDamageToCharacter(realSource, realTarget, 6,
                                                   true);

                    if (realTarget->isDestroyed)
                    {
                        const int remainDamage = 6 - targetHealth;
                        if (remainDamage > 0)
                        {
                            Generic::TakeDamageToCharacter(
                                realSource, player->opponent->GetHero(),
                                remainDamage, true);
                        }
                    }
                }) }))
    };
    cards.emplace("LOOT_101", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [LOOT_103] Lesser Ruby Spellstone - COST:2
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: Add 1 random Mage spell to your hand.
    //       <i>(Play 2 Elementals to upgrade.)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 2
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [LOOT_104] Shifting Scroll - COST:0
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: Each turn this is in your hand,
    //       transform it into a random Mage spell.
    // --------------------------------------------------------
    // GameTag:
    // - HIDE_STATS = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [LOOT_106] Deck of Wonders - COST:5
    // - Set: Lootapalooza, Rarity: Epic
    // --------------------------------------------------------
    // Text: Shuffle 5 Scrolls into your deck.
    //       When drawn, cast a random spell.
    // --------------------------------------------------------

    // ------------------------------------------ WEAPON - MAGE
    // [LOOT_108] Aluneth - COST:6
    // - Set: Lootapalooza, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of your turn, draw 3 cards.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DURABILITY = 3
    // - InvisibleDeathrattle = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [LOOT_170] Raven Familiar - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Reveal a spell in each deck.
    //       If yours costs more, draw it.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [LOOT_172] Dragon's Fury - COST:5
    // - Faction: Neutral, Set: Lootapalooza, Rarity: Epic
    // --------------------------------------------------------
    // Text: Reveal a spell from your deck.
    //       Deal damage equal to its Cost to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [LOOT_231] Arcane Artificer - COST:1 [ATK:1/HP:2]
    // - Race: Elemental, Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever you cast a spell,
    //       gain Armor equal to its Cost.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [LOOT_535] Dragoncaller Alanna - COST:9 [ATK:3/HP:3]
    // - Set: Lootapalooza, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 5/5 Dragon for each spell
    //       you cast this game that costs (5) or more.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [LOOT_537] Leyline Manipulator - COST:4 [ATK:4/HP:5]
    // - Race: Elemental, Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding any cards that
    //       didn't start in your deck, reduce their Cost by (2).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void LootapaloozaCardsGen::AddMageNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------- SPELL - MAGE
    // [LOOT_103t1] Ruby Spellstone (*) - COST:2
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: Add 2 random Mage spells to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 2
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [LOOT_103t2] Greater Ruby Spellstone (*) - COST:2
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: Add 3 random Mage spells to your hand.
    // --------------------------------------------------------

    // ------------------------------------- ENCHANTMENT - MAGE
    // [LOOT_104e] Shifting (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Transforming into random Mage spells.
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [LOOT_106t] Scroll of Wonder (*) - COST:5
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Cast a random spell. Draw a card.
    //       Cast this when drawn.
    // --------------------------------------------------------
    // GameTag:
    // - TOPDECK = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [LOOT_535t] Fire Dragon (*) - COST:5 [ATK:5/HP:5]
    // - Race: Dragon, Set: Lootapalooza
    // --------------------------------------------------------
}

void LootapaloozaCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- SPELL - PALADIN
    // [LOOT_088] Potion of Heroism - COST:2
    // - Fac: neutral, Set: lootapalooza, Rarity: common
    // --------------------------------------------------------
    // Text: Give a minion <b>Divine_Shield</b>.
    //       Draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [LOOT_091] Lesser Pearl Spellstone - COST:2
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon a 2/2 Spirit with <b>Taunt</b>.
    //       <i>(Restore 3 Health to upgrade.)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 3
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - HEALTH = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [LOOT_093] Call to Arms - COST:5
    // - Set: Lootapalooza, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Recruit</b> 3 minions that cost (2) or less.
    // --------------------------------------------------------
    // RefTag:
    // - RECRUIT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [LOOT_216] Lynessa Sunsorrow - COST:7 [ATK:1/HP:1]
    // - Set: Lootapalooza, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Cast each spell you cast
    //       on your minions this game on this one.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - PALADIN
    // [LOOT_286] Unidentified Maul - COST:3 [ATK:2/HP:0]
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: Gains a bonus effect in your hand.
    // --------------------------------------------------------
    // Entourage: LOOT_286t2, LOOT_286t3, LOOT_286t1, LOOT_286t4
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [LOOT_313] Crystal Lion - COST:6 [ATK:5/HP:5]
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    //       Costs (1) less for each Silver Hand Recruit you control.
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [LOOT_333] Level Up! - COST:5
    // - Set: Lootapalooza, Rarity: Epic
    // --------------------------------------------------------
    // Text: Give your Silver Hand Recruits +2/+2 and <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - 717 = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [LOOT_363] Drygulch Jailor - COST:2 [ATK:1/HP:1]
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add 3 Silver Hand Recruits
    //       to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [LOOT_398] Benevolent Djinn - COST:3 [ATK:2/HP:4]
    // - Race: Elemental, Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       restore 3 Health to your hero.
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - PALADIN
    // [LOOT_500] Val'anyr - COST:6 [ATK:4/HP:0]
    // - Set: Lootapalooza, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give a minion in your hand +4/+2.
    //       When it dies, reequip this.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DURABILITY = 2
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
}

void LootapaloozaCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - PALADIN
    // [LOOT_091t] Guardian Spirit (*) - COST:2 [ATK:2/HP:2]
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [LOOT_091t1] Pearl Spellstone (*) - COST:2
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon a 4/4 Spirit with <b>Taunt</b>. @
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 3
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - HEALTH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [LOOT_091t1t] Guardian Spirit (*) - COST:4 [ATK:4/HP:4]
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [LOOT_091t2] Greater Pearl Spellstone (*) - COST:2
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon a 6/6 Spirit with <b>Taunt</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [LOOT_091t2t] Guardian Spirit (*) - COST:6 [ATK:6/HP:6]
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - PALADIN
    // [LOOT_286t1] Champion's Maul (*) - COST:3 [ATK:2/HP:0]
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two 1/1 Silver Hand Recruits.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - PALADIN
    // [LOOT_286t2] Sacred Maul (*) - COST:3 [ATK:2/HP:0]
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your minions <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - PALADIN
    // [LOOT_286t3] Blessed Maul (*) - COST:3 [ATK:2/HP:0]
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your minions +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - PALADIN
    // [LOOT_286t4] Purifier's Maul (*) - COST:3 [ATK:2/HP:0]
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your minions <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - PALADIN
    // [LOOT_500d] Val'anyr Reequip Effect Dummy (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: It is a dummy card for holding a effect to play
    //       when reequipping Val'anyr (LOOT_500)
    // --------------------------------------------------------
}

void LootapaloozaCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- SPELL - PRIEST
    // [LOOT_008] Psychic Scream - COST:7
    // - Set: lootapalooza, Rarity: epic
    // --------------------------------------------------------
    // Text: Shuffle all minions into your opponent's deck.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [LOOT_187] Twilight's Call - COST:3
    // - Faction: Neutral, Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon 1/1 copies of 2 friendly <b>Deathrattle</b>
    //       minions that died this game.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_FRIENDLY_MINION_DIED_THIS_GAME = 0
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - PRIEST
    // [LOOT_209] Dragon Soul - COST:3
    // - Set: Lootapalooza, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you cast 3 spells in a turn,
    //       summon a 5/5 Dragon.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DURABILITY = 3
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [LOOT_278] Unidentified Elixir - COST:3
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion +2/+2.
    //       Gains a bonus effect in your hand.
    // --------------------------------------------------------
    // Entourage: LOOT_278t1, LOOT_278t2, LOOT_278t3, LOOT_278t4
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [LOOT_353] Psionic Probe - COST:1
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: Copy a spell in your opponent's deck and
    //       add it to your hand.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [LOOT_410] Duskbreaker - COST:4 [ATK:3/HP:3]
    // - Race: Dragon, Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       deal 3 damage to all other minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [LOOT_507] Lesser Diamond Spellstone - COST:7
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: Resurrect 2 different friendly minions.
    //       <i>(Cast 4 spells to upgrade.)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 4
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [LOOT_528] Twilight Acolyte - COST:3 [ATK:2/HP:4]
    // - Set: Lootapalooza, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       swap this minion's Attack with another minion's.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE_AND_DRAGON_IN_HAND = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [LOOT_534] Gilded Gargoyle - COST:3 [ATK:2/HP:2]
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a Coin to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [LOOT_538] Temporus - COST:7 [ATK:6/HP:6]
    // - Race: Dragon, Set: Lootapalooza, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your opponent takes two turns.
    //       Then you take two turns.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void LootapaloozaCardsGen::AddPriestNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- MINION - PRIEST
    // [LOOT_209t] Dragon Spirit (*) - COST:5 [ATK:5/HP:5]
    // - Race: Dragon, Set: Lootapalooza
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [LOOT_278t1] Elixir of Life (*) - COST:3
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion +2/+2 and <b>Lifesteal</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [LOOT_278t2] Elixir of Purity (*) - COST:3
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion +2/+2 and <b>Divine Shield</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [LOOT_278t3] Elixir of Shadows (*) - COST:3
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion +2/+2. Summon a 1/1 copy of_it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [LOOT_278t4] Elixir of Hope (*) - COST:3
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion +2/+2 and "<b>Deathrattle:</b>
    //       Return this minion to your hand."
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [LOOT_507t] Diamond Spellstone (*) - COST:7
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: Resurrect 3 different friendly minions.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 4
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [LOOT_507t2] Greater Diamond Spellstone (*) - COST:7
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: Resurrect 4 different friendly minions.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [LOOT_538e] Time Spiraling (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Take an extra turn.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [LOOT_538e2] Revenge (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Take an extra turn.
    // --------------------------------------------------------
}

void LootapaloozaCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- MINION - ROGUE
    // [LOOT_026] Fal'dorei Strider - COST:4 [ATK:4/HP:4]
    // - Set: Lootapalooza, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Shuffle 3 Ambushes into your deck.
    //       When drawn, summon a 4/4 Spider.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [LOOT_033] Cavern Shinyfinder - COST:2 [ATK:3/HP:1]
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a weapon from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [LOOT_165] Sonya Shadowdancer - COST:3 [ATK:2/HP:2]
    // - Set: Lootapalooza, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After a friendly minion dies,
    //       add a 1/1 copy of it to your hand. It costs (1).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [LOOT_204] Cheat Death - COST:2
    // - Set: lootapalooza, Rarity: common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When a friendly minion dies,
    //       return it to your hand. It costs (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [LOOT_210] Sudden Betrayal - COST:2
    // - Set: lootapalooza, Rarity: common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When a minion attacks your hero,
    //       instead it attacks one of its neighbors.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [LOOT_211] Elven Minstrel - COST:4 [ATK:3/HP:2]
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Draw 2 minions from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [LOOT_214] Evasion - COST:2
    // - Set: Lootapalooza, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After your hero takes damage,
    //       become <b>Immune</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [LOOT_412] Kobold Illusionist - COST:5 [ATK:3/HP:3]
    // - Faction: Alliance, Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 1/1 copy of a minion
    //       from your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [LOOT_503] Lesser Onyx Spellstone - COST:5
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: Destroy 1 random enemy minion.
    //       <i>(Play 3 <b>Deathrattle</b> cards to upgrade.)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 3
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_ENEMY_MINIONS = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- WEAPON - ROGUE
    // [LOOT_542] Kingsbane - COST:1 [ATK:1/HP:3]
    // - Set: Lootapalooza, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Shuffle this into your deck.
    //       It keeps any enchantments.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DURABILITY = 3
    // - DEATHRATTLE = 1
    // - 851 = 1
    // --------------------------------------------------------
}

void LootapaloozaCardsGen::AddRogueNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ SPELL - ROGUE
    // [LOOT_026e] Spider Ambush! (*) - COST:4
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Summon a 4/4 Spider. Draw a card.
    //       Cast this when drawn.
    // --------------------------------------------------------
    // GameTag:
    // - TOPDECK = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [LOOT_026t] Leyline Spider (*) - COST:4 [ATK:4/HP:4]
    // - Race: Beast, Set: Lootapalooza
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [LOOT_503t] Onyx Spellstone (*) - COST:5
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: Destroy up to 2 random enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 3
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_ENEMY_MINIONS = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [LOOT_503t2] Greater Onyx Spellstone (*) - COST:5
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: Destroy up to 3 random enemy minions.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_ENEMY_MINIONS = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [LOOT_542e] Kingsbane Shuffle (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Getting ready to shuffle in.
    // --------------------------------------------------------
}

void LootapaloozaCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- SPELL - SHAMAN
    // [LOOT_060] Crushing Hand - COST:2
    // - Faction: Neutral, Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 8 damage to a minion.
    //       <b><b>Overload</b>:</b> (3)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 3
    // - OVERLOAD_OWED = 3
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [LOOT_062] Kobold Hermit - COST:2 [ATK:1/HP:1]
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a basic Totem. Summon it.
    // --------------------------------------------------------
    // Entourage: CS2_052, CS2_050, NEW1_009, CS2_051
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [LOOT_064] Lesser Sapphire Spellstone - COST:7
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon 1 copy of a friendly minion.
    //       <i>(<b>Overload</b> 3 Mana Crystals to upgrade.)</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 3
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [LOOT_344] Primal Talismans - COST:3
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give your minions "<b>Deathrattle:</b>
    //       Summon a random basic Totem."
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [LOOT_358] Grumble, Worldshaker - COST:6 [ATK:7/HP:7]
    // - Race: Elemental, Set: Lootapalooza, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Return your other minions
    //       to your hand. They cost (1).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [LOOT_373] Healing Rain - COST:3
    // - Set: Lootapalooza, Rarity: common
    // --------------------------------------------------------
    // Text: Restore 12 Health randomly split among
    //       all friendly characters.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [LOOT_504] Unstable Evolution - COST:1
    // - Set: Lootapalooza, Rarity: Epic
    // --------------------------------------------------------
    // Text: Transform a friendly minion into one
    //       that costs (1) more. Repeatable this turn.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - SHAMAN
    // [LOOT_506] The Runespear - COST:8 [ATK:3/HP:0]
    // - Set: Lootapalooza, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After your hero attacks, <b>Discover</b> a spell
    //       and cast it with random targets.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DURABILITY = 3
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [LOOT_517] Murmuring Elemental - COST:2 [ATK:1/HP:1]
    // - Race: Elemental, Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your next <b>Battlecry</b>
    //       this turn triggers twice.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [LOOT_518] Windshear Stormcaller - COST:5 [ATK:5/HP:5]
    // - Set: Lootapalooza, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control all 4 basic Totems,
    //       summon Al'Akir the Windlord.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void LootapaloozaCardsGen::AddShamanNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- SPELL - SHAMAN
    // [LOOT_064t1] Sapphire Spellstone (*) - COST:7
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon 2 copies of a friendly minion.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 3
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [LOOT_064t2] Greater Sapphire Spellstone (*) - COST:7
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon 3 copies of a friendly minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [LOOT_344e] Primal Talisman (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a random basic Totem.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [LOOT_504t] Unstable Evolution (*) - COST:1
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Transform a friendly minion into one
    //       that costs (1) more. Repeatable this turn.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
}

void LootapaloozaCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - WARLOCK
    // [LOOT_013] Vulgar Homunculus - COST:2 [ATK:2/HP:4]
    // - Race: Demon, Facion: Neutral, Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Deal 2 damage to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [LOOT_014] Kobold Librarian - COST:1 [ATK:2/HP:1]
    // - Faction: Neutral, Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a card.
    //       Deal 2 damage to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [LOOT_017] Dark Pact - COST:1
    // - Faction: Alliance, Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: Destroy a friendly minion.
    //       Restore 4 Health to your hero.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [LOOT_018] Hooked Reaver - COST:4 [ATK:4/HP:4]
    // - Race: Demon, Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you have 15 or less Health,
    //       gain +3/+3 and <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [LOOT_043] Lesser Amethyst Spellstone - COST:4
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Lifesteal.</b> Deal 3 damage to a minion.
    //       <i>(Take damage from your cards to upgrade.)</i>
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [LOOT_306] Possessed Lackey - COST:6 [ATK:2/HP:2]
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> <b>Recruit</b> a Demon.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - RECRUIT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [LOOT_368] Voidlord - COST:9 [ATK:3/HP:9]
    // - Race: demon, Set: lootapalooza, Rarity: epic
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Summon three 1/3 Demons
    //       with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [LOOT_415] Rin, the First Disciple - COST:6 [ATK:3/HP:6]
    // - Set: Lootapalooza, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Add 'The First Seal' to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [LOOT_417] Cataclysm - COST:4
    // - Set: Lootapalooza, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy all minions. Discard your hand.
    // --------------------------------------------------------
    // GameTag:
    // - 890 = 10
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARLOCK
    // [LOOT_420] Skull of the Man'ari - COST:5
    // - Set: Lootapalooza, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       summon a Demon from your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DURABILITY = 3
    // - InvisibleDeathrattle = 1
    // --------------------------------------------------------
}

void LootapaloozaCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- SPELL - WARLOCK
    // [LOOT_043t2] Amethyst Spellstone (*) - COST:4
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Lifesteal.</b> Deal 5 damage to a minion.
    //       <i>(Take damage from your cards to upgrade.)</i>
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [LOOT_043t3] Greater Amethyst Spellstone (*) - COST:4
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Lifesteal.</b> Deal 7 damage to a minion.
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [LOOT_415t1] The First Seal (*) - COST:5
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Summon a 2/2 Demon. Add 'The Second Seal' to your hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [LOOT_415t1t] Felhunter (*) - COST:2 [ATK:2/HP:2]
    // - Race: Demon, Set: Lootapalooza
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [LOOT_415t2] The Second Seal (*) - COST:5
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Summon a 3/3 Demon. Add 'The Third Seal' to your hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [LOOT_415t2t] Felhunter (*) - COST:3 [ATK:3/HP:3]
    // - Race: Demon, Set: Lootapalooza
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [LOOT_415t3] The Third Seal (*) - COST:5
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Summon a 4/4 Demon. Add 'The Fourth Seal' to your hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [LOOT_415t3t] Felhunter (*) - COST:4 [ATK:4/HP:4]
    // - Race: Demon, Set: Lootapalooza
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [LOOT_415t4] The Fourth Seal (*) - COST:5
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Summon a 5/5 Demon. Add 'The Final Seal' to your hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [LOOT_415t4t] Felhunter (*) - COST:5 [ATK:5/HP:5]
    // - Race: Demon, Set: Lootapalooza
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [LOOT_415t5t] Felhunter (*) - COST:6 [ATK:6/HP:6]
    // - Race: Demon, Set: Lootapalooza
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [LOOT_415t5] The Final Seal (*) - COST:5
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Summon a 6/6 Demon.
    //       Add 'Azari, the Devourer' to your hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [LOOT_415t6] Azari, the Devourer (*) - COST:10 [ATK:10/HP:10]
    // - Race: Demon, Set: Lootapalooza
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy your opponent's deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void LootapaloozaCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - WARRIOR
    // [LOOT_041] Kobold Barbarian - COST:3 [ATK:4/HP:4]
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the start of your turn, attack a random enemy.
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [LOOT_044] Bladed Gauntlet - COST:2
    // - Set: Lootapalooza, Rarity: Epic
    // --------------------------------------------------------
    // Text: Has Attack equal to your Armor. Can't attack heroes.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [LOOT_203] Lesser Mithril Spellstone - COST:7
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon one 5/5 Mithril Golem.
    //       <i>(Equip a weapon to upgrade.)</i>
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [LOOT_285] Unidentified Shield - COST:6
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: Gain 5 Armor.
    //       Gains a bonus effect in your hand.
    // --------------------------------------------------------
    // Entourage: LOOT_285t, LOOT_285t2, LOOT_285t3, LOOT_285t4
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [LOOT_364] Reckless Flurry - COST:3
    // - Set: lootapalooza, Rarity: epic
    // --------------------------------------------------------
    // Text: Spend all your Armor.
    //       Deal that much damage to all minions.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [LOOT_365] Gemstudded Golem - COST:6 [ATK:5/HP:9]
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       Can only attack if you have 5 or more Armor.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [LOOT_367] Drywhisker Armorer - COST:2 [ATK:2/HP:2]
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> For each enemy minion, gain 2 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [LOOT_370] Gather Your Party - COST:6
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Recruit</b> a minion.
    // --------------------------------------------------------
    // RefTag:
    // - RECRUIT = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [LOOT_380] Woecleaver - COST:8 [ATK:3/HP:0]
    // - Set: Lootapalooza, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After your hero attacks, <b>Recruit</b> a minion.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DURABILITY = 3
    // --------------------------------------------------------
    // RefTag:
    // - RECRUIT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [LOOT_519] Geosculptor Yip - COST:8 [ATK:4/HP:8]
    // - Set: Lootapalooza, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of your turn, summon a random minion
    //       with Cost equal to your Armor <i>(up to 10)</i>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
}

void LootapaloozaCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- SPELL - WARRIOR
    // [LOOT_203t2] Mithril Spellstone (*) - COST:7
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon two 5/5 Mithril Golems.
    //       <i>(Equip a weapon to upgrade.)</i>
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [LOOT_203t3] Greater Mithril Spellstone (*) - COST:7
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon three 5/5 Mithril Golems.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [LOOT_203t4] Mithril Golem (*) - COST:5 [ATK:5/HP:5]
    // - Set: Lootapalooza
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [LOOT_285t] Tower Shield +10 (*) - COST:6
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: Gain 5 Armor.
    //       Gain 10 more Armor.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [LOOT_285t2] Serrated Shield (*) - COST:6
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: Gain 5 Armor.
    //       Deal 5 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [LOOT_285t3] Runed Shield (*) - COST:6
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: Gain 5 Armor.
    //       Summon a 5/5 Golem.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [LOOT_285t3t] Iron Golem (*) - COST:5 [ATK:5/HP:5]
    // - Set: Lootapalooza
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [LOOT_285t4] Spiked Shield (*) - COST:6
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: Gain 5 Armor.
    //       Equip a 5/2 weapon.
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [LOOT_285t4t] Spiked Shield (*) - COST:5 [ATK:5/HP:0]
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [LOOT_528e] Twilight Curse (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Attack was swapped.
    // --------------------------------------------------------
}

void LootapaloozaCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_069] Sewer Crawler - COST:3 [ATK:1/HP:1]
    // - Faction: Neutral, Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 2/3_Giant Rat.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_111] Scorp-o-matic - COST:2 [ATK:1/HP:2]
    // - Race: Mechanical, Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a minion with 1 or less Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_MAX_ATTACK = 1
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_117] Wax Elemental - COST:1 [ATK:0/HP:2]
    // - Race: Elemental, Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_118] Ebon Dragonsmith - COST:4 [ATK:3/HP:4]
    // - Race: Dragon, Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Reduce the Cost of a random weapon
    //       in your hand by (2).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_122] Corrosive Sludge - COST:5 [ATK:5/HP:5]
    // - Faction: Alliance, Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy your opponent's weapon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_124] Lone Champion - COST:3 [ATK:2/HP:4]
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control no other minions,
    //       gain <b>Taunt</b> and <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsFieldCount(1)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true, TaskList{ std::make_shared<AddEnchantmentTask>(
                  "LOOT_124e", EntityType::SOURCE) }));
    cards.emplace("LOOT_124", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_125] Stoneskin Basilisk - COST:3 [ATK:1/HP:1]
    // - Race: Beast, Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    //       <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // - POISONOUS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("LOOT_125", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_130] Arcane Tyrant - COST:5 [ATK:4/HP:4]
    // - Race: Elemental, Set: Lootapalooza, Rarity: Epic
    // --------------------------------------------------------
    // Text: Costs (0) if you've cast a spell that costs (5)
    //       or more this turn.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_131] Green Jelly - COST:5 [ATK:3/HP:3]
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       summon a 1/2 Ooze with <b>Taunt</b>.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_132] Dragonslayer - COST:3 [ATK:4/HP:3]
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 6 damage to a Dragon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_TARGET_WITH_RACE = 24
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_134] Toothy Chest - COST:3 [ATK:0/HP:4]
    // - Faction: Neutral, Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       set this minion's Attack to 4.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_136] Sneaky Devil - COST:4 [ATK:2/HP:2]
    // - Race: Demon, Faction: Alliance, Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //       Your other minions have +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_137] Sleepy Dragon - COST:9 [ATK:4/HP:12]
    // - Race: Dragon, Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("LOOT_137", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_144] Hoarding Dragon - COST:4 [ATK:5/HP:6]
    // - Race: Dragon, Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give your opponent two Coins.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_149] Corridor Creeper - COST:7 [ATK:5/HP:5]
    // - Race: Beast, Faction: Neutral, Set: Lootapalooza, Rarity: Epic
    // --------------------------------------------------------
    // Text: Costs (1) less whenever a minion dies
    //       while this is in your hand.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_150] Furbolg Mossbinder - COST:5 [ATK:1/HP:1]
    // - Faction: Alliance, Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Transform a friendly minion
    //       into a 6/6 Elemental.
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
    // [LOOT_152] Boisterous Bard - COST:3 [ATK:3/HP:2]
    // - Faction: Alliance, Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your other minions +1 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_153] Violet Wurm - COST:8 [ATK:7/HP:7]
    // - Race: Beast, Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon seven 1/1 Grubs.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_154] Gravelsnout Knight - COST:1 [ATK:2/HP:3]
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a random 1-Cost minion
    //       for your opponent.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_161] Carnivorous Cube - COST:5 [ATK:4/HP:6]
    // - Set: Lootapalooza, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a friendly minion.
    //       <b>Deathrattle:</b> Summon 2 copies of it.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_167] Fungalmancer - COST:5 [ATK:2/HP:2]
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give adjacent minions +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_184] Silver Vanguard - COST:7 [ATK:3/HP:3]
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> <b>Recruit</b> an 8-Cost minion.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - RECRUIT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_193] Shimmering Courser - COST:4 [ATK:3/HP:3]
    // - Race: Beast, Set: Lootapalooza, Rarity: Epic
    // --------------------------------------------------------
    // Text: Only you can target this with spells and Hero Powers.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_218] Feral Gibberer - COST:1 [ATK:1/HP:1]
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: After this minion attacks a hero,
    //       add a copy of it to your hand.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_233] Cursed Disciple - COST:4 [ATK:5/HP:1]
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 5/1 Revenant.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_258] Dire Mole - COST:1 [ATK:1/HP:3]
    // - Race: Beast, Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_291] Shroom Brewer - COST:4 [ATK:4/HP:4]
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 4 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_315] Trogg Gloomeater - COST:5 [ATK:1/HP:5]
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - POISONOUS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_347] Kobold Apprentice - COST:3 [ATK:2/HP:1]
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage randomly split
    //       among all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_357] Marin the Fox - COST:8 [ATK:6/HP:6]
    // - Set: Lootapalooza, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 0/8 Treasure Chest
    //       for your opponent. <i>(Break it for awesome loot!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_375] Guild Recruiter - COST:5 [ATK:2/HP:4]
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Recruit</b> a minion that
    //       costs (4) or less.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RECRUIT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_382] Kobold Monk - COST:4 [ATK:3/HP:6]
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: Your hero can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_383] Hungry Ettin - COST:6 [ATK:4/HP:10]
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Summon a random 2-Cost minion
    //       for your opponent.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_388] Fungal Enchanter - COST:3 [ATK:3/HP:3]
    // - Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 2 Health to all
    //       friendly characters.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_389] Rummaging Kobold - COST:3 [ATK:1/HP:3]
    // - Set: Lootapalooza, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Return one of your destroyed
    //       weapons to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_394] Shrieking Shroom - COST:3 [ATK:1/HP:2]
    // - Set: Lootapalooza, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       summon a random 1-Cost minion.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_413] Plated Beetle - COST:2 [ATK:2/HP:3]
    // - Race: Beast, Set: Lootapalooza, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Gain 3 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(std::make_shared<ArmorTask>(3));
    cards.emplace("LOOT_413", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_414] Grand Archivist - COST:8 [ATK:4/HP:7]
    // - Set: Lootapalooza, Rarity: Epic
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       cast a spell from your deck
    //       <i>(targets chosen randomly)</i>.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_516] Zola the Gorgon - COST:3 [ATK:2/HP:2]
    // - Set: Lootapalooza, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a friendly minion.
    //       Add a Golden copy of it to your hand.
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
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<CopyTask>(
        EntityType::TARGET, ZoneType::HAND, 1, true));
    cardDef.power.AddPowerTask(std::make_shared<SetGameTagTask>(
        EntityType::STACK, GameTag::PREMIUM, 1));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 } };
    cards.emplace("LOOT_516", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_521] Master Oakheart - COST:9 [ATK:5/HP:5]
    // - Set: Lootapalooza, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Recruit</b> a 1, 2,
    //       and 3-Attack minion.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - RECRUIT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_526] The Darkness - COST:4 [ATK:20/HP:20]
    // - Set: Lootapalooza, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Starts dormant.
    //       <b>Battlecry:</b> Shuffle 3 Candles into the enemy deck.
    //       When drawn, this awakens.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_529] Void Ripper - COST:3 [ATK:3/HP:3]
    // - Race: Demon, Set: Lootapalooza, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Swap the
    //       Attack and Health of all other minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_539] Spiteful Summoner - COST:7 [ATK:4/HP:4]
    // - Faction: Neutral, Set: Lootapalooza, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Reveal a spell from your deck.
    //       Summon a random minion with the same Cost.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_540] Dragonhatcher - COST:9 [ATK:2/HP:4]
    // - Set: Lootapalooza, Rarity: Epic
    // --------------------------------------------------------
    // Text: At the end of your turn, <b>Recruit</b> a Dragon.
    // --------------------------------------------------------
    // RefTag:
    // - RECRUIT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_541] King Togwaggle - COST:8 [ATK:5/HP:5]
    // - Set: Lootapalooza, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Swap decks with your opponent.
    //       Give them a Ransom spell to swap back.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void LootapaloozaCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_018e] Hooked Horror (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: +3/+3.
    //       <b>Taunt</b>
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_047e] Barkskin (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: +3 Health.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_054be] Fearless (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_069t] Giant Rat (*) - COST:3 [ATK:2/HP:3]
    // - Race: Beast, Set: Lootapalooza
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_118e] Smithing (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Cost reduced.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_124e] Lonely (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: <b>Taunt</b> and <b>Divine Shield</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("LOOT_124e"));
    cards.emplace("LOOT_124e", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_131t1] Green Ooze (*) - COST:2 [ATK:1/HP:2]
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_134e] Toothy (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Attack set to 4.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_136e] Devilish Power (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Sneaky Devil is granting this minion +1 Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_149e] Creepier (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_150t1] Moss Elemental (*) - COST:6 [ATK:6/HP:6]
    // - Race: Elemental, Set: Lootapalooza
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_152e] Inspired (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: +1 Health.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_153t1] Grub (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Lootapalooza
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_161e] Carnivorous Cube (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Destroyed {0}.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_165e] Sonya's Shadow (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Sonya Shadowdancer made this 1/1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_167e] Magic Mushroom (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_187e] Shadowy (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: 1/1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_204e] Close Call (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_214e] Evasive (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: <b>Immune</b> until end of turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_216e] Light of the Exarch (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Spell cast on minion.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_233t] Cursed Revenant (*) - COST:4 [ATK:5/HP:1]
    // - Set: Lootapalooza
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_278e] Tastes Like ???? (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_278t1e] Sanguine (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: +2/+2 and <b>Lifesteal</b>.
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // -------------------------z--------- ENCHANTMENT - NEUTRAL
    // [LOOT_278t2e] Pure (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: +2/+2 and <b>Divine Shield</b>.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_278t3e] Shadowtouched (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_278t3e2] Shadowy (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: 1/1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_278t4e] Hopeful (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: +2/+2.
    //       <b>Deathrattle:</b> Return this minion to your hand.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_286t3e] Holy Blessings (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_333e] +1 Level! (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: +2/+2 and <b>Taunt</b>.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_357l] Master Chest (*) - COST:3 [ATK:0/HP:8]
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give your opponent
    //       a fantastic treasure!
    // --------------------------------------------------------
    // Entourage: LOOT_998h, LOOT_998j, LOOT_998l, LOOT_998k
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - MULTIPLY_BUFF_VALUE = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_358e] Grumbly Tumbly (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Costs (1).
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_412e] Shadowy (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: 1/1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_500e] Wielding Val'anyr (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: +4/+2.
    //       <b>Deathrattle:</b> Equip a 4/2 Val'anyr.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_517e] Murmurs (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Your next <b>Battlecry</b> this turn triggers twice.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_517e2] Murmuring (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Your next <b>Battlecry</b> this turn triggers twice.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_520e] Albino Chameleon (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Copied Deathrattle from {0}.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_526d] The Darkness (*) - COST:4 [ATK:20/HP:20]
    // - Set: Lootapalooza, Rarity: Legendary
    // --------------------------------------------------------
    // Text:
    // --------------------------------------------------------
    // GameTag:
    // - TAG_SCRIPT_DATA_NUM_2 = 3
    // - ELITE = 1
    // - HIDE_STATS = 1
    // - UNTOUCHABLE = 1
    // - SCORE_VALUE_1 = 3
    // - IGNORE_HIDE_STATS_FOR_BIG_CARD = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_526et] Darkness Candle Detect (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [LOOT_526t] Darkness Candle (*) - COST:4
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Snuff out a candle. Draw a card.
    //       Cast this when drawn.
    // --------------------------------------------------------
    // GameTag:
    // - TOPDECK = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_529e] Void Shift (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Attack and Health have been swapped.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [LOOT_541t] King's Ransom (*) - COST:5
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Swap decks with your opponent.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [LOOT_998h] Tolin's Goblet (*) - COST:3
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Draw a card. Fill your hand with copies of it.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(1, true));
    cardDef.power.AddPowerTask(std::make_shared<FuncPlayableTask>(
        [=](const std::vector<Playable*>& playables) {
            if (playables.empty())
            {
                return std::vector<Playable*>{};
            }

            const Playable* drawnCard = playables[0];
            if (!drawnCard)
            {
                return std::vector<Playable*>{};
            }

            const int space = drawnCard->player->GetHandZone()->GetFreeSpace();
            for (int i = 0; i < space; ++i)
            {
                Playable* copiedCard =
                    Entity::GetFromCard(drawnCard->player, drawnCard->card);
                drawnCard->player->GetHandZone()->Add(copiedCard);
            }

            return std::vector<Playable*>{};
        }));
    cards.emplace("LOOT_998h", cardDef);

    // ---------------------------------------- SPELL - NEUTRAL
    // [LOOT_998j] Zarog's Crown (*) - COST:3
    // - Faction: Neutral, Set: Lootapalooza
    // --------------------------------------------------------
    // Text: <b>Discover</b> a <b>Legendary</b> minion.
    //       Summon two copies of it.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DiscoverTask>(DiscoverType::LEGENDARY_MINION_SUMMON));
    cardDef.power.AddAfterChooseTask(
        std::make_shared<CopyTask>(EntityType::TARGET, ZoneType::PLAY));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("LOOT_998j", cardDef);

    // ---------------------------------------- SPELL - NEUTRAL
    // [LOOT_998l] Wondrous Wand (*) - COST:3
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Draw 3 cards. Reduce their Costs to (0).
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<DrawTask>(3, true));
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("LOOT_998le", EntityType::STACK));
    cards.emplace("LOOT_998l", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [LOOT_998le] Wand's Wonder (*) - COST:0
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: Costs (0).
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::SetCost(0)));
    cards.emplace("LOOT_998le", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [LOOT_998k] Golden Kobold (*) - COST:3 [ATK:6/HP:6]
    // - Set: Lootapalooza
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Replace your hand with <b>Legendary</b> minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ChangeEntityTask>(
        EntityType::HAND, CardType::MINION, CardClass::INVALID, Race::INVALID,
        Rarity::LEGENDARY, false));
    cards.emplace("LOOT_998k", cardDef);
}

void LootapaloozaCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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
