// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/CardSets/IcecrownCardsGen.hpp>
#include <Rosetta/PlayMode/Cards/CardPowers.hpp>

namespace RosettaStone::PlayMode
{
void IcecrownCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ HERO - SHAMAN
    // [ICC_481] Thrall, Deathseer - COST:5 [ATK:0/HP:30]
    // - Set: Icecrown, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Transform your minions into
    //       random ones that cost (2) more.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 42982
    // --------------------------------------------------------

    // ------------------------------------------- HERO - ROGUE
    // [ICC_827] Valeera the Hollow - COST:9 [ATK:0/HP:30]
    // - Set: Icecrown, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain <b>Stealth</b> until
    //       your next turn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 43188
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ------------------------------------------ HERO - HUNTER
    // [ICC_828] Deathstalker Rexxar - COST:6 [ATK:0/HP:30]
    // - Set: Icecrown, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 2 damage to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 43183
    // --------------------------------------------------------

    // ----------------------------------------- HERO - PALADIN
    // [ICC_829] Uther of the Ebon Blade - COST:9 [ATK:0/HP:30]
    // - Set: Icecrown, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Equip a 5/3 <b>Lifesteal</b> weapon.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 43013
    // --------------------------------------------------------
    // RefTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // ------------------------------------------ HERO - PRIEST
    // [ICC_830] Shadowreaper Anduin - COST:8 [ATK:0/HP:30]
    // - Set: Icecrown, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy all minions with 5 or
    //       more Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 45397
    // --------------------------------------------------------

    // ----------------------------------------- HERO - WARLOCK
    // [ICC_831] Bloodreaver Gul'dan - COST:10 [ATK:0/HP:30]
    // - Set: Icecrown, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon all friendly Demons
    //       that died this game.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 43181
    // --------------------------------------------------------

    // ------------------------------------------- HERO - DRUID
    // [ICC_832] Malfurion the Pestilent - COST:7 [ATK:0/HP:30]
    // - Set: Icecrown, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Choose One -</b>
    //       Summon 2 <b>Poisonous</b> Spiders;
    //       or 2 Scarabs with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - ARMOR = 5
    // - HERO_POWER = 43182
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // - POISONOUS = 1
    // --------------------------------------------------------

    // -------------------------------------------- HERO - MAGE
    // [ICC_833] Frost Lich Jaina - COST:9 [ATK:0/HP:30]
    // - Set: Icecrown, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 3/6 Water Elemental.
    //       Your Elementals have <b>Lifesteal</b> this game.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 42944
    // --------------------------------------------------------
    // RefTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- HERO - WARRIOR
    // [ICC_834] Scourgelord Garrosh - COST:8 [ATK:0/HP:30]
    // - Set: Icecrown, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry</b>: Equip a 4/3_Shadowmourne that
    //       also damages adjacent minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - ARMOR = 5
    // - HERO_POWER = 45585
    // --------------------------------------------------------
}

void IcecrownCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- HERO_POWER - NEUTRAL
    // [ICC_481p] Transmute Spirit (*) - COST:2
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: <b>Hero Power:</b> Transform a friendly minion
    //       into a random one that costs (1) more.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ------------------------------------- HERO_POWER - ROGUE
    // [ICC_827p] Death's Shadow (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: <b>Passive Hero Power</b>
    //       During your turn,
    //       add a 'Shadow Reflection' to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - HIDE_STATS = 1
    // --------------------------------------------------------

    // ----------------------------------- HERO_POWER - NEUTRAL
    // [ICC_828p] Build-A-Beast (*) - COST:2
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Craft a custom Zombeast.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_HAND_NOT_FULL = 0
    // --------------------------------------------------------

    // ----------------------------------- HERO_POWER - NEUTRAL
    // [ICC_829p] The Four Horsemen (*) - COST:2
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Summon a 2/2 Horseman.
    //       If you have all 4, destroy the enemy hero.
    // --------------------------------------------------------
    // Entourage: ICC_829t2, ICC_829t3, ICC_829t4, ICC_829t5
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------

    // ------------------------------------ HERO_POWER - PRIEST
    // [ICC_830p] Voidform (*) - COST:2
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Deal 2 damage.
    //       After you play a card, refresh this.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ----------------------------------- HERO_POWER - NEUTRAL
    // [ICC_831p] Siphon Life (*) - COST:2
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       <b>Lifesteal</b> Deal 3 damage.
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ----------------------------------- HERO_POWER - NEUTRAL
    // [ICC_832p] Plague Lord (*) - COST:2
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       <b>Choose One -</b> +3 Attack this turn;
    //       or Gain 3 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------- HERO_POWER - NEUTRAL
    // [ICC_833h] Icy Touch (*) - COST:2
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Deal 1 damage.
    //       If this kills a minion, summon a Water Elemental.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ----------------------------------- HERO_POWER - WARRIOR
    // [ICC_834h] Bladestorm (*) - COST:2
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //        Deal 1 damage to all minions.
    // --------------------------------------------------------
}

void IcecrownCardsGen::AddDeathknightNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- WEAPON - DEATHKNIGHT
    // [ICC_314t1] Frostmourne (*) - COST:7 [ATK:5/HP:0]
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon every minion killed
    //       by this weapon.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DURABILITY = 3
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEATHKNIGHT
    // [ICC_314t2] Army of the Dead (*) - COST:6
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: Remove the top 5 cards of your deck.
    //       Summon any minions removed.
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEATHKNIGHT
    // [ICC_314t3] Doom Pact (*) - COST:5
    // - Faction: Neutral, Set: Icecrown
    // --------------------------------------------------------
    // Text: Destroy all minions. Remove the top card
    //       from your deck for each minion destroyed.
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEATHKNIGHT
    // [ICC_314t4] Death Grip (*) - COST:2
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: Steal a minion from your opponent's deck
    //       and add it to your hand.
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEATHKNIGHT
    // [ICC_314t5] Death Coil (*) - COST:2
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: Deal 5 damage to an enemy, or restore 5 Health
    //       to a friendly character.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEATHKNIGHT
    // [ICC_314t6] Obliterate (*) - COST:2
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: Destroy a minion.
    //       Your hero takes damage equal to its Health.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEATHKNIGHT
    // [ICC_314t7] Anti-Magic Shell (*) - COST:4
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: Give your minions +2/+2 and
    //       "Can't be targeted by spells or Hero Powers."
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEATHKNIGHT
    // [ICC_314t8] Death and Decay (*) - COST:3
    // - Faction: Neutral, Set: Icecrown
    // --------------------------------------------------------
    // Text: Deal 3 damage to all enemies.
    // --------------------------------------------------------
}

void IcecrownCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- MINION - DRUID
    // [ICC_047] Fatespinner - COST:5 [ATK:5/HP:3]
    // - Set: Icecrown, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Choose a Deathrattle (Secretly)
    //       -</b> Deal 3 damage to all minions;
    //       or Give them +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // - 818 = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [ICC_050] Webweave - COST:5
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: Summon two 1/2 <b>Poisonous</b> Spiders.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - POISONOUS = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [ICC_051] Druid of the Swarm - COST:2 [ATK:1/HP:2]
    // - Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Transform into a 1/2
    //       with <b>Poisonous</b>; or a 1/5 with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // - POISONOUS = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [ICC_054] Spreading Plague - COST:6
    // - Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon a 1/5 Scarab with <b>Taunt</b>.
    //       If your opponent has more minions, cast this again.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [ICC_079] Gnash - COST:3
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: Give your hero +3 Attack this turn. Gain 3 Armor.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [ICC_085] Ultimate Infestation - COST:10
    // - Set: Icecrown, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 5 damage. Draw 5 cards. Gain 5 Armor.
    //       Summon a 5/5 Ghoul.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [ICC_807] Strongshell Scavenger - COST:4 [ATK:2/HP:3]
    // - Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your <b>Taunt</b> minions +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [ICC_808] Crypt Lord - COST:3 [ATK:1/HP:6]
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       After you summon a minion, gain +1 Health.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [ICC_835] Hadronox - COST:9 [ATK:3/HP:7]
    // - Race: Beast, Set: Icecrown, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon your <b>Taunt</b> minions
    //       that died this game.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
}

void IcecrownCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ SPELL - DRUID
    // [ICC_047a] Growth (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give all minions +2/+2.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [ICC_047b] Decay (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 3 damage to all minions.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [ICC_047e] Growth (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [ICC_047t] Fatespinner (*) - COST:5 [ATK:5/HP:3]
    // - Set: Icecrown, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Secret Deathrattle:</b>
    //       Deal 3 damage to all minions; or Give them +2/+2.
    //       <b>Secret Deathrattle:</b> Give +2/+2 to all minions.
    //       <b>Secret Deathrattle:</b> Deal 3 damage to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [ICC_047t2] Fatespinner (*) - COST:5 [ATK:5/HP:3]
    // - Set: Icecrown, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 3 damage to all minions
    //       and give them +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [ICC_051a] Spider Form (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [ICC_051b] Scarab Form (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: +3 Health and <b>Taunt</b>.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [ICC_051t] Druid of the Swarm (*) - COST:2 [ATK:1/HP:2]
    // - Race: Beast, Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - POISONOUS = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [ICC_051t2] Druid of the Swarm (*) - COST:2 [ATK:1/HP:5]
    // - Race: Beast, Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [ICC_051t3] Druid of the Swarm (*) - COST:2 [ATK:1/HP:5]
    // - Race: Beast, Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - POISONOUS = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [ICC_079e] Gnash (*) - COST:0
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: +3 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [ICC_085t] Ghoul Infestor (*) - COST:5 [ATK:5/HP:5]
    // - Set: Icecrown
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [ICC_808e] Might of Ner'ub (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: Increased Health.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [ICC_832a] Scarab Plague (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: Summon two 1/5 Scarabs with <b>Taunt</b>.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [ICC_832b] Spider Plague (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: Summon two 1/2 Spiders with <b>Poisonous</b>.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [ICC_832pa] Scarab Shell (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: +3 Armor.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [ICC_832pb] Spider Fangs (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: +3 Attack.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [ICC_832t3] Frost Widow (*) - COST:1 [ATK:1/HP:2]
    // - Race: Beast, Set: Icecrown
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - POISONOUS = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [ICC_832t4] Scarab Beetle (*) - COST:2 [ATK:1/HP:5]
    // - Race: Beast, Set: Icecrown
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
}

void IcecrownCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - HUNTER
    // [ICC_021] Exploding Bloatbat - COST:4 [ATK:2/HP:1]
    // - Race: Beast, Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b>
    //       Deal 2 damage to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [ICC_049] Toxic Arrow - COST:2
    // - Set: Icecrown, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 2 damage to a minion. If it survives,
    //       give it <b>Poisonous</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    // RefTag:
    // - POISONOUS = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [ICC_052] Play Dead - COST:1
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: Trigger a friendly minion's <b>Deathrattle</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_WITH_DEATHRATTLE = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [ICC_200] Venomstrike Trap - COST:2
    // - Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When one of your minions is attacked,
    //       summon a 2/3 <b>Poisonous</b> Cobra.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    // RefTag:
    // - POISONOUS = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [ICC_204] Professor Putricide - COST:4 [ATK:5/HP:4]
    // - Set: Icecrown, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you play a <b>Secret</b>,
    //       put a random Hunter <b>Secret</b> into the battlefield.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [ICC_243] Corpse Widow - COST:5 [ATK:4/HP:6]
    // - Race: Beast, Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: Your <b>Deathrattle</b> cards cost (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [ICC_415] Stitched Tracker - COST:3 [ATK:2/HP:2]
    // - Faction: Neutral, Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a copy of
    //       a minion in your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [ICC_419] Bearshark - COST:3 [ATK:4/HP:3]
    // - Race: Beast, Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("ICC_419", cardDef);

    // ---------------------------------------- MINION - HUNTER
    // [ICC_825] Abominable Bowman - COST:7 [ATK:6/HP:7]
    // - Set: Icecrown, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a random friendly Beast
    //       that died this game.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
}

void IcecrownCardsGen::AddHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- ENCHANTMENT - HUNTER
    // [ICC_828e] Stitched (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: {0} and {1}.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_SILENCED = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [ICC_828t] Zombeast (*) - COST:0 [ATK:1/HP:1]
    // - Race: Beast, Set: Icecrown
    // --------------------------------------------------------
    // Text: {0}
    //       {1}
    // --------------------------------------------------------
}

void IcecrownCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ MINION - MAGE
    // [ICC_068] Ice Walker - COST:2 [ATK:1/HP:3]
    // - Race: Elemental, Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: Your Hero Power also <b><b>Freeze</b>s</b> the target.
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [ICC_069] Ghastly Conjurer - COST:4 [ATK:2/HP:6]
    // - Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a 'Mirror Image' spell
    //       to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [ICC_082] Frozen Clone - COST:3
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After your opponent plays a minion,
    //       add two copies of it to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [ICC_083] Doomed Apprentice - COST:3 [ATK:3/HP:2]
    // - Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: Your opponent's spells cost (1) more.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [ICC_086] Glacial Mysteries - COST:8
    // - Set: Icecrown, Rarity: Epic
    // --------------------------------------------------------
    // Text: Put one of each <b>Secret</b> from your deck
    //       into the battlefield.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_SECRET_ZONE_CAP_FOR_NON_SECRET = 0
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [ICC_252] Coldwraith - COST:3 [ATK:3/HP:4]
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If an enemy is <b>Frozen</b>,
    //       draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_FROZEN_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [ICC_823] Simulacrum - COST:3
    // - Set: Icecrown, Rarity: Epic
    // --------------------------------------------------------
    // Text: Copy the lowest Cost minion in your hand.
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [ICC_836] Breath of Sindragosa - COST:1
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 2 damage to a random enemy minion
    //       and <b>Freeze</b> it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_ENEMY_MINIONS = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [ICC_838] Sindragosa - COST:8 [ATK:8/HP:8]
    // - Race: Dragon, Set: Icecrown, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two 0/1 Frozen Champions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void IcecrownCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ MINION - MAGE
    // [ICC_833t] Water Elemental (*) - COST:4 [ATK:3/HP:6]
    // - Race: Elemental, Faction: Neutral, Set: Icecrown
    // --------------------------------------------------------
    // Text: <b>Freeze</b> any character damaged by this minion.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [ICC_838t] Frozen Champion (*) - COST:1 [ATK:0/HP:1]
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a random
    //       <b>Legendary</b> minion to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
}

void IcecrownCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - PALADIN
    // [ICC_034] Arrogant Crusader - COST:4 [ATK:5/HP:2]
    // - Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> If it's your opponent's turn,
    //       summon a 2/2 Ghoul.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [ICC_038] Righteous Protector - COST:1 [ATK:1/HP:1]
    // - Set: Icecrown, Rarity: Common
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
    cards.emplace("ICC_038", cardDef);

    // ---------------------------------------- SPELL - PALADIN
    // [ICC_039] Dark Conviction - COST:2
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: Set a minion's Attack and Health to 3.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - PALADIN
    // [ICC_071] Light's Sorrow - COST:4 [ATK:1/HP:0]
    // - Set: Icecrown, Rarity: Epic
    // --------------------------------------------------------
    // Text: After a friendly minion loses <b>Divine Shield</b>,
    //       gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 4
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [ICC_244] Desperate Stand - COST:2
    // - Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give a minion "<b>Deathrattle:</b> Return this
    //       to life with 1 Health."
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [ICC_245] Blackguard - COST:6 [ATK:3/HP:9]
    // - Set: Icecrown, Rarity: Epic
    // --------------------------------------------------------
    // Text: Whenever your hero is healed,
    //       deal that much damage to a random enemy minion.
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [ICC_801] Howling Commander - COST:3 [ATK:2/HP:2]
    // - Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw a <b>Divine Shield</b>
    //       minion from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [ICC_820] Chillblade Champion - COST:4 [ATK:3/HP:2]
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    //       <b>Lifesteal</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [ICC_858] Bolvar, Fireblood - COST:5 [ATK:1/HP:7]
    // - Set: Icecrown, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    //       After a friendly minion loses <b>Divine Shield</b>,
    //       gain +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
}

void IcecrownCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ---------------------------------- ENCHANTMENT - PALADIN
    // [ICC_071e] Dying Light (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [ICC_244e] Redeemed (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Return this to life with 1 Health.
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - PALADIN
    // [ICC_829t] Grave Vengeance (*) - COST:8 [ATK:5/HP:0]
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DURABILITY = 3
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [ICC_829t2] Deathlord Nazgrim (*) - COST:2 [ATK:2/HP:2]
    // - Set: Icecrown
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [ICC_829t3] Thoras Trollbane (*) - COST:2 [ATK:2/HP:2]
    // - Set: Icecrown
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [ICC_829t4] Inquisitor Whitemane (*) - COST:2 [ATK:2/HP:2]
    // - Set: Icecrown
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [ICC_829t5] Darion Mograine (*) - COST:2 [ATK:2/HP:2]
    // - Set: Icecrown
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [ICC_858e] Fading Light (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
}

void IcecrownCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- SPELL - PRIEST
    // [ICC_207] Devour Mind - COST:5
    // - Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: Copy 3 cards in your opponent's deck
    //       and add them to your hand.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [ICC_210] Shadow Ascendant - COST:2 [ATK:2/HP:2]
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       give another random friendly minion +1/+1.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [ICC_212] Acolyte of Agony - COST:3 [ATK:3/HP:3]
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [ICC_213] Eternal Servitude - COST:4
    // - Set: icecrown, Rarity: rare
    // --------------------------------------------------------
    // Text: <b>Discover</b> a friendly minion that died
    //       this game. Summon it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_FRIENDLY_MINION_DIED_THIS_GAME = 0
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [ICC_214] Obsidian Statue - COST:9 [ATK:4/HP:8]
    // - Set: Icecrown, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Taunt, Lifesteal</b>
    //       <b>Deathrattle:</b> Destroy a random enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [ICC_215] Archbishop Benedictus - COST:7 [ATK:4/HP:6]
    // - Set: Icecrown, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Shuffle a copy of your
    //       opponent's deck into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [ICC_235] Shadow Essence - COST:6
    // - Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon a 5/5 copy of a random minion in your deck.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [ICC_802] Spirit Lash - COST:2
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    //       Deal 1 damage to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [ICC_849] Embrace Darkness - COST:6
    // - Set: Icecrown, Rarity: Epic
    // --------------------------------------------------------
    // Text: Choose an enemy minion.
    //       At the start of your turn, gain control of it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------
}

void IcecrownCardsGen::AddPriestNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- ENCHANTMENT - PRIEST
    // [ICC_210e] Ascended (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: Stats increased.
    // --------------------------------------------------------
}

void IcecrownCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - ROGUE
    // [ICC_065] Bone Baron - COST:5 [ATK:5/HP:5]
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add two 1/1 Skeletons to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [ICC_201] Roll the Bones - COST:2
    // - Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: Draw a card.
    //       If it has <b>Deathrattle</b>, cast this again.
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [ICC_221] Leeching Poison - COST:1
    // - Faction: Neutral, Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: Give your weapon <b>Lifesteal</b> this turn.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_WEAPON_EQUIPPED = 0
    // --------------------------------------------------------
    // RefTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [ICC_233] Doomerang - COST:1
    // - Set: Icecrown, Rarity: Epic
    // --------------------------------------------------------
    // Text: Throw your weapon at a minion.
    //       It deals its damage, then returns to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_WEAPON_EQUIPPED = 0
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [ICC_240] Runeforge Haunter - COST:4 [ATK:5/HP:3]
    // - Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: During your turn, your weapon doesn't lose Durability.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [ICC_809] Plague Scientist - COST:3 [ATK:2/HP:3]
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Give a friendly minion <b>Poisonous</b>.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_TARGET_FOR_COMBO = 0
    // --------------------------------------------------------
    // RefTag:
    // - POISONOUS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddComboTask(
        std::make_shared<AddEnchantmentTask>("ICC_809e", EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                  { PlayReq::REQ_TARGET_FOR_COMBO, 0 } };
    cards.emplace("ICC_809", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [ICC_811] Lilian Voss - COST:4 [ATK:4/HP:5]
    // - Set: Icecrown, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Replace spells in your hand
    //       with random spells
    //       <i>(from your opponent's class).</i>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- WEAPON - ROGUE
    // [ICC_850] Shadowblade - COST:3 [ATK:3/HP:0]
    // - Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your hero is <b>Immune</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [ICC_910] Spectral Pillager - COST:6 [ATK:5/HP:5]
    // - Faction: Neutral, Set: Icecrown, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Deal damage equal to the number of
    //       other cards you've played this turn.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_FOR_COMBO = 0
    // --------------------------------------------------------
}

void IcecrownCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [ICC_018e] Witty Weaponplay (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [ICC_221e] Leeching Poison (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: Has <b>Lifesteal</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [ICC_240e] Resilient Weapon (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: No durability loss.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [ICC_809e] Test Subject (*) - COST:0
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------
    // RefTag:
    // - POISONOUS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("ICC_809e"));
    cards.emplace("ICC_809e", cardDef);

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [ICC_827e] Shadow Reflection (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: Always copy your last played card.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [ICC_827e3] Veil of Shadows (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: <b>Stealth</b> until your next turn.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [ICC_850e] Shaded (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: <b>Immune</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [ICC_827t] Shadow Reflection (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: Each time you play a card,
    //       transform this into a copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - HIDE_STATS = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MUST_PLAY_OTHER_CARD_FIRST = 0
    // --------------------------------------------------------
}

void IcecrownCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- SPELL - SHAMAN
    // [ICC_056] Cryostasis - COST:2
    // - Set: Icecrown, Rarity: Epic
    // --------------------------------------------------------
    // Text: Give a minion +3/+3 and <b>Freeze</b> it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [ICC_058] Brrrloc - COST:2 [ATK:2/HP:2]
    // - Race: Murloc, Set: Icecrown, Rarity: Common
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

    // ----------------------------------------- SPELL - SHAMAN
    // [ICC_078] Avalanche - COST:4
    // - Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Freeze</b> a minion and deal 3 damage
    //       to adjacent ones.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [ICC_081] Drakkari Defender - COST:3 [ATK:2/HP:8]
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Overload:</b> (3)
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - OVERLOAD = 3
    // - OVERLOAD_OWED = 3
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [ICC_088] Voodoo Hexxer - COST:5 [ATK:2/HP:7]
    // - Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Freeze</b> any character damaged by this minion.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - FREEZE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [ICC_089] Ice Fishing - COST:2
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: Draw 2 Murlocs from your deck.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [ICC_090] Snowfury Giant - COST:11 [ATK:8/HP:8]
    // - Race: Elemental, Set: Icecrown, Rarity: Epic
    // --------------------------------------------------------
    // Text: Costs (1) less for each Mana Crystal you've
    //       <b><b>Overload</b>ed</b> this game.
    // --------------------------------------------------------
    // RefTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - SHAMAN
    // [ICC_236] Ice Breaker - COST:3 [ATK:1/HP:0]
    // - Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: Destroy any <b>Frozen</b> minion damaged by this.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 3
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [ICC_289] Moorabi - COST:6 [ATK:4/HP:4]
    // - Set: Icecrown, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever another minion is <b>Frozen</b>,
    //       add a copy of it to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------
}

void IcecrownCardsGen::AddShamanNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void IcecrownCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - WARLOCK
    // [ICC_041] Defile - COST:2
    // - Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 1 damage to all minions.
    //       If any die, cast this again.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [ICC_055] Drain Soul - COST:2
    // - Set: Icecrown, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    //       Deal 3 damage to a minion.
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
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
    cards.emplace("ICC_055", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [ICC_075] Despicable Dreadlord - COST:5 [ATK:4/HP:5]
    // - Race: Demon, Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       deal 1 damage to all enemy minions.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [ICC_206] Treachery - COST:3
    // - Set: Icecrown, Rarity: Epic
    // --------------------------------------------------------
    // Text: Choose a friendly minion and give it to your opponent.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [ICC_218] Howlfiend - COST:3 [ATK:3/HP:6]
    // - Race: Demon, Faction: Neutral, Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever this minion takes damage,
    //       discard a random card.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [ICC_407] Gnomeferatu - COST:2 [ATK:2/HP:3]
    // - Set: Icecrown, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Remove the top card of
    //       your opponent's deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [ICC_469] Unwilling Sacrifice - COST:3
    // - Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: Choose a friendly minion.
    //       Destroy it and a random enemy minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [ICC_841] Blood-Queen Lana'thel - COST:5 [ATK:1/HP:6]
    // - Set: Icecrown, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    //       Has +1 Attack for each card you've discarded
    //       this game.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [ICC_903] Sanguine Reveler - COST:1 [ATK:1/HP:1]
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a friendly minion
    //       and gain +2/+2.
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

void IcecrownCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void IcecrownCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - WARRIOR
    // [ICC_062] Mountainfire Armor - COST:3 [ATK:4/HP:3]
    // - Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> If it's your opponent's turn,
    //       gain 6 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [ICC_064] Blood Razor - COST:4 [ATK:2/HP:0]
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry and Deathrattle:</b>
    //       Deal 1 damage to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - DEATHRATTLE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [ICC_091] Dead Man's Hand - COST:2
    // - Set: Icecrown, Rarity: Epic
    // --------------------------------------------------------
    // Text: Shuffle a copy of your hand into your deck.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [ICC_238] Animated Berserker - COST:1 [ATK:1/HP:3]
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: After you play a minion, deal 1 damage to it.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [ICC_281] Forge of Souls - COST:2
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: Draw 2 weapons from your deck.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [ICC_405] Rotface - COST:8 [ATK:4/HP:6]
    // - Set: Icecrown, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever this minion survives damage,
    //       summon a random <b>Legendary</b> minion.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [ICC_408] Val'kyr Soulclaimer - COST:3 [ATK:1/HP:4]
    // - Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever this minion survives damage,
    //       summon a 2/2 Ghoul.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [ICC_450] Death Revenant - COST:5 [ATK:3/HP:3]
    // - Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain +1/+1 for each damaged minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [ICC_837] Bring It On! - COST:2
    // - Set: Icecrown, Rarity: Epic
    // --------------------------------------------------------
    // Text: Gain 10 Armor. Reduce the Cost of minions
    //       in your opponent's hand by (2).
    // --------------------------------------------------------
}

void IcecrownCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- WEAPON - WARRIOR
    // [ICC_834w] Shadowmourne (*) - COST:8 [ATK:4/HP:0]
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: Also damages the minions next to whomever
    //       your hero attacks.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DURABILITY = 3
    // --------------------------------------------------------
}

void IcecrownCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_018] Phantom Freebooter - COST:4 [ATK:3/HP:3]
    // - Race: Pirate, Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain stats equal to your weapon's.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_019] Skelemancer - COST:5 [ATK:2/HP:2]
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> If it's your opponent's turn,
    //       summon an 8/8 Skeleton.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_023] Snowflipper Penguin - COST:0 [ATK:1/HP:1]
    // - Race: Beast, Set: Icecrown, Rarity: Common
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_025] Rattling Rascal - COST:4 [ATK:2/HP:2]
    // - Set: Icecrown, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 5/5 Skeleton.
    //       <b>Deathrattle:</b> Summon one for your opponent.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_026] Grim Necromancer - COST:4 [ATK:2/HP:4]
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon two 1/1 Skeletons.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("ICC_026t", SummonSide::LEFT));
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("ICC_026t", SummonSide::RIGHT));
    cards.emplace("ICC_026", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_027] Bone Drake - COST:6 [ATK:6/HP:5]
    // - Race: Dragon, Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a random Dragon to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_028] Sunborne Val'kyr - COST:5 [ATK:5/HP:4]
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give adjacent minions +2 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_029] Cobalt Scalebane - COST:5 [ATK:5/HP:5]
    // - Race: Dragon, Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       give another random friendly minion +3 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        ComplexTask::GiveBuffToAnotherRandomMinionInField("ICC_029e")
    };
    cards.emplace("ICC_029", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_031] Night Howler - COST:4 [ATK:3/HP:4]
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever this minion takes damage, gain +2 Attack.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_032] Venomancer - COST:5 [ATK:2/HP:5]
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - POISONOUS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_067] Vryghoul - COST:3 [ATK:3/HP:1]
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> If it's your opponent's turn,
    //       summon a 2/2 Ghoul.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_092] Acherus Veteran - COST:1 [ATK:2/HP:1]
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion +1 Attack.
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
    // [ICC_093] Tuskarr Fisherman - COST:2 [ATK:2/HP:3]
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion
    //       <b>Spell Damage +1</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_094] Fallen Sun Cleric - COST:2 [ATK:2/HP:1]
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion +1/+1.
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
    // [ICC_096] Furnacefire Colossus - COST:6 [ATK:6/HP:6]
    // - Set: Icecrown, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Discard all weapons
    //       from your hand and gain their stats.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_097] Grave Shambler - COST:4 [ATK:4/HP:4]
    // - Race: Elemental, Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever your weapon is destroyed, gain +1/+1.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_098] Tomb Lurker - COST:5 [ATK:5/HP:3]
    // - Set: Icecrown, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a random <b>Deathrattle</b>
    //       minion that died this game to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_099] Ticking Abomination - COST:4 [ATK:5/HP:6]
    // - Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 5 damage to your minions.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_220] Deadscale Knight - COST:1 [ATK:1/HP:1]
    // - Race: Murloc, Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_257] Corpse Raiser - COST:5 [ATK:3/HP:3]
    // - Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion
    //       "<b>Deathrattle:</b> Resummon this minion."
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DEATH_KNIGHT = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_314] The Lich King - COST:8 [ATK:8/HP:8]
    // - Set: Icecrown, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       At the end of your turn,
    //       add a random <b>Death Knight</b> card to your hand.
    // --------------------------------------------------------
    // Entourage: ICC_314t3, ICC_314t2, ICC_314t7, ICC_314t4,
    //            ICC_314t5, ICC_314t6, ICC_314t8, ICC_314t1
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_466] Saronite Chain Gang - COST:4 [ATK:2/HP:3]
    // - Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Summon a copy of this minion.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_467] Deathspeaker - COST:3 [ATK:2/HP:4]
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion
    //       <b>Immune</b> this turn.
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
    // - IMMUNE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_468] Wretched Tiller - COST:1 [ATK:1/HP:1]
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever this minion attacks,
    //       deal 2 damage to the enemy hero.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_700] Happy Ghoul - COST:3 [ATK:3/HP:3]
    // - Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: Costs (0) if your hero was healed this turn.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_701] Skulking Geist - COST:6 [ATK:4/HP:6]
    // - Set: Icecrown, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy all 1-Cost spells
    //       in both hands and decks.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_702] Shallow Gravedigger - COST:3 [ATK:3/HP:1]
    // - Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a random <b>Deathrattle</b>
    //       minion to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_705] Bonemare - COST:7 [ATK:5/HP:5]
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion +4/+4
    //       and <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_706] Nerubian Unraveler - COST:6 [ATK:5/HP:5]
    // - Set: Icecrown, Rarity: Epic
    // --------------------------------------------------------
    // Text: Spells cost (2) more.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_810] Deathaxe Punisher - COST:4 [ATK:3/HP:3]
    // - Set: Icecrown, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a random <b>Lifesteal</b>
    //       minion in your hand +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_812] Meat Wagon - COST:4 [ATK:1/HP:4]
    // - Race: Mechanical, Set: Icecrown, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a minion from your deck
    //       with less Attack than this minion.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_851] Prince Keleseth - COST:2 [ATK:2/HP:2]
    // - Set: Icecrown, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck has no 2-Cost cards,
    //       give_all minions in your deck +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_852] Prince Taldaram - COST:3 [ATK:3/HP:3]
    // - Set: Icecrown, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck has_no 3-Cost cards,
    //       transform into a 3/3 copy of a minion.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_DRAG_TO_PLAY = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_853] Prince Valanar - COST:4 [ATK:4/HP:4]
    // - Set: Icecrown, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck has no 4-Cost cards,
    //       gain <b>Lifesteal</b> and <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_854] Arfus - COST:4 [ATK:2/HP:2]
    // - Race: Beast, Set: Icecrown, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a random <b>Death Knight</b>
    //       card to your hand.
    // --------------------------------------------------------
    // Entourage: ICC_314t2, ICC_314t3, ICC_314t4, ICC_314t5,
    //            ICC_314t7, ICC_314t8, ICC_314t6, ICC_314t1
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_855] Hyldnir Frostrider - COST:3 [ATK:4/HP:4]
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Freeze</b> your other minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_856] Spellweaver - COST:6 [ATK:4/HP:4]
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Spell Damage +2</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 2
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_900] Necrotic Geist - COST:6 [ATK:5/HP:3]
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever one of your other minions dies,
    //       summon a 2/2 Ghoul.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_901] Drakkari Enchanter - COST:3 [ATK:1/HP:5]
    // - Set: Icecrown, Rarity: Epic
    // --------------------------------------------------------
    // Text: Your end of turn effects trigger twice.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_902] Mindbreaker - COST:3 [ATK:2/HP:5]
    // - Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: Hero Powers are disabled.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_904] Wicked Skeleton - COST:4 [ATK:1/HP:1]
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain +1/+1 for each minion
    //       that died this turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_905] Bloodworm - COST:5 [ATK:4/HP:4]
    // - Race: Beast, Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_911] Keening Banshee - COST:4 [ATK:5/HP:5]
    // - Set: Icecrown, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you play a card,
    //       remove the top 3 cards of your deck.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_912] Corpsetaker - COST:4 [ATK:3/HP:3]
    // - Set: Icecrown, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain <b>Taunt</b>
    //       if your deck has a <b>Taunt</b> minion.
    //       Repeat for <b>Divine Shield</b>,
    //       <b>Lifesteal</b>, <b>Windfury</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - WINDFURY = 1
    // - TAUNT = 1
    // - DIVINE_SHIELD = 1
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_913] Tainted Zealot - COST:2 [ATK:1/HP:1]
    // - Set: Icecrown, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    //       <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
}

void IcecrownCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_019t] Skeletal Flayer (*) - COST:8 [ATK:8/HP:8]
    // - Set: Icecrown
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_025t] Skeletal Enforcer (*) - COST:5 [ATK:5/HP:5]
    // - Set: Icecrown
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_026t] Skeleton (*) - COST:1 [ATK:1/HP:1]
    // - Set: Icecrown
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("ICC_026t", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_028e] Blessing of the Val'kyr (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: +2 Health.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_029e] Dragonscales (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: Attack increased.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<Enchant>(Effects::AttackN(3)));
    cards.emplace("ICC_029e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_031e] Awooooo! (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: This minion has increased Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_039e] Convinced (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: Stats changed to 3/3.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_049e] Toxic Arrow (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: Poisonous.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_056e] Frozen Blood (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: +3/+3.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_092e] Veteran's Favor (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_093e] Fresh Fish! (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_094e] Cleric's Blessing (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_096e] Me Bigger (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_097e] Armed and Dangerous (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_235e] Shadow Essence (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: Attack and Health set to 5.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_257e] Ready to Return (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Resummon this minion.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_314t1e] Trapped Soul (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: {0}
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_314t7e] Anti-Magic Shell (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: +2/+2 and "Can't be targeted by spells or Hero Powers."
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_450e] Bloodthirsty (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_467e] Deathward (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: <b>Immune</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_483e] Frostmourne Enchantment (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_705e] Bonemare's Boon (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: +4/+4 and <b>Taunt</b>.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_800h3t] Zombeast (*) - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Icecrown
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_807e] Strongshell (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_810e] Bloodthirsty (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: +2/+2 from Deathaxe Punisher.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_832e] Fangs (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: +3 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_833e] Frost Lich (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: Your Elementals have <b>Lifesteal</b>.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_833e2] Icy Veins (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: Frost Lich Jaina is granting your Elementals
    //       <b>Lifesteal</b>.
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_837e] Challenged (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: Minion cost reduced by (2).
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_841e] Vampiric Bite (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_849e] Embraced (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: At the start of the next turn,
    //       lose control of this minion.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_851e] Keleseth's Blessing (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_852e] Taldaram's Visage (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: 3/3.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [ICC_900t] Ghoul (*) - COST:2 [ATK:2/HP:2]
    // - Set: Icecrown
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_903t] Bloodthirst (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [ICC_904e] Extra Calcium (*) - COST:0
    // - Set: Icecrown
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------
}

void IcecrownCardsGen::AddAll(std::map<std::string, CardDef>& cards)
{
    AddHeroes(cards);
    AddHeroPowers(cards);
    AddDeathknightNonCollect(cards);

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