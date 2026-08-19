// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/ReturnOfTheLichKingCardsGen.hpp>

namespace RosettaStone::PlayMode
{
void ReturnOfTheLichKingCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- HERO - PALADIN
    // [RLK_Prologue_Arthas_001hp] Arthas - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------

    // ----------------------------------------- HERO - PALADIN
    // [RLK_Prologue_Arthas_001hp2] Arthas - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------

    // ------------------------------------- HERO - DEATHKNIGHT
    // [RLK_Prologue_Arthas_002hp] Arthas - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------

    // ------------------------------------- HERO - DEATHKNIGHT
    // [RLK_Prologue_Arthas_003hp] Arthas - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------

    // ------------------------------------- HERO - DEATHKNIGHT
    // [RLK_Prologue_Arthas_004hp] Arthas - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------

    // ------------------------------------- HERO - DEMONHUNTER
    // [RLK_Prologue_FroznThrn_004hb3] The Frozen Throne - COST:0
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Free
    // --------------------------------------------------------
    // GameTag:
    // - IMMUNE = 1
    // --------------------------------------------------------

    // ------------------------------------- HERO - DEMONHUNTER
    // [RLK_Prologue_Illidan_004hb] Illidan Stormrage - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------

    // ------------------------------------- HERO - DEMONHUNTER
    // [RLK_Prologue_IllidanD_004hb2] Demonic Illidan - COST:0
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Free
    // --------------------------------------------------------

    // ------------------------------------- HERO - DEATHKNIGHT
    // [RLK_Prologue_LichKing_004hp2] The Lich King - COST:0
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Free
    // --------------------------------------------------------

    // ------------------------------------- HERO - DEATHKNIGHT
    // [RLK_Prologue_MalGanis_001hb] Mal'Ganis - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------

    // ------------------------------------------ HERO - HUNTER
    // [RLK_Prologue_Sylvanas_003hb] Sylvanas Windrunner - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------

    // ------------------------------------------ HERO - HUNTER
    // [RLK_Prologue_SylvanasB_003hb2] Sylvanas Windrunner - COST:0
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Free
    // --------------------------------------------------------

    // ----------------------------------------- HERO - PALADIN
    // [RLK_Prologue_Uther_002hb] Uther Lightbringer - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
}

void ReturnOfTheLichKingCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- HERO_POWER - PALADIN
    // [RLK_Prologue_Arthas_001p] Reinforce - COST:2
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Summon a 1/1 Silver Hand Recruit.
    // --------------------------------------------------------

    // ------------------------------- HERO_POWER - DEATHKNIGHT
    // [RLK_Prologue_Arthas_002p] Ghoul Charge - COST:2
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Summon a 1/1 Ghoul with <b>Charge</b>.
    //       It dies at end of turn.
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------

    // ------------------------------- HERO_POWER - DEATHKNIGHT
    // [RLK_Prologue_Arthas_003p] Ghoul Charge - COST:2
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Summon a 1/1 Ghoul with <b>Charge</b>.
    //       It dies at end of turn.
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------

    // ------------------------------- HERO_POWER - DEATHKNIGHT
    // [RLK_Prologue_Arthas_004p] Ghoul Charge - COST:2
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Summon a 1/1 Ghoul with <b>Charge</b>.
    //       It dies at end of turn.
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------

    // ------------------------------- HERO_POWER - DEMONHUNTER
    // [RLK_Prologue_Illidan_004p] Demon Claws - COST:2
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       +2 Attack this turn.
    // --------------------------------------------------------

    // ------------------------------- HERO_POWER - DEMONHUNTER
    // [RLK_Prologue_Illidan_004p2] Demonic Blast - COST:4
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Deal 3 damage.
    // --------------------------------------------------------

    // ------------------------------- HERO_POWER - DEATHKNIGHT
    // [RLK_Prologue_MalGanis_001p] Ghoul Charge - COST:2
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Summon a 1/1 Ghoul with <b>Charge</b>.
    //       It dies at end of turn.
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------

    // ------------------------------------ HERO_POWER - HUNTER
    // [RLK_Prologue_Sylvanas_003p] Quick Fire - COST:1
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Deal 1 damage to two random enemy minions.
    // --------------------------------------------------------

    // ----------------------------------- HERO_POWER - PALADIN
    // [RLK_Prologue_Uther_002p] Equip Lightbringer - COST:4
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Equip a 3/4 Lightbringer.
    // --------------------------------------------------------
}

void ReturnOfTheLichKingCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- MINION - DRUID
    // [RLK_650] Lingering Zombie - COST:1 [ATK:1/HP:1]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 1/1 Disarmed Zombie with
    //       "<b>Deathrattle:</b> Summon a 1/1 Zombie."
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [RLK_651] Crypt Keeper - COST:8 [ATK:4/HP:6]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>. Costs (1) less for each Armor you have.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [RLK_652] Unending Swarm - COST:6
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: Resurrect all friendly minions that cost (2) or less.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [RLK_654] Beetlemancy - COST:5
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Choose One</b> - Gain 12 Armor;
    //       or Summon two 3/3 Beetles with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [RLK_655] Wither - COST:2
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Choose a minion. Each friendly Undead steals
    //       1 Attack and Health from it.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [RLK_656] Chitinous Plating - COST:2
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: Gain 4 Armor.
    //       At the start of your next turn, gain 4 more.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [RLK_657] Underking - COST:7 [ATK:6/HP:6]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Battlecry and Deathrattle:</b> Gain 6 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DEATHRATTLE = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [RLK_658] Elder Nadox - COST:5 [ATK:5/HP:4]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a friendly Undead.
    //       Your minions gain its Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [RLK_659] Anub'Rekhan - COST:8 [ATK:7/HP:7]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain 8 Armor.
    //       This turn, your minions cost Armor instead of Mana.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [RLK_956] Nerubian Flyer - COST:2 [ATK:2/HP:3]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If a friendly Undead died after
    //       your last turn, summon a 2/2 Nerubian.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void ReturnOfTheLichKingCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- MINION - DRUID
    // [RLK_650t] Disarmed Zombie - COST:1 [ATK:1/HP:1]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 1/1 Zombie.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [RLK_650t2] Unarmed Zombie - COST:1 [ATK:1/HP:1]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [RLK_654a] Beetle Juice - COST:5
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Gain 12 Armor.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [RLK_654b] Bug Snacks - COST:5
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Summon two 3/3 Beetles with <b>Taunt</b>.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [RLK_654t] Beetle - COST:3 [ATK:3/HP:3]
    // - Race: Beast, Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [RLK_655e] Withered - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Reduced stats.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [RLK_655e2] Life Siphon - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [RLK_655e2a] Life Siphon - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ENCHANTMENT_INVISIBLE = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [RLK_655e2b] Life Siphon - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Increased Health.
    // --------------------------------------------------------
    // GameTag:
    // - ENCHANTMENT_INVISIBLE = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [RLK_655ea] Withered - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Reduced Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ENCHANTMENT_INVISIBLE = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [RLK_655eb] Withered - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Reduced Health.
    // --------------------------------------------------------
    // GameTag:
    // - ENCHANTMENT_INVISIBLE = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [RLK_656e] Molting - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Gain 4 Armor next turn.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [RLK_658e] Might of Nadox - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [RLK_659e] Hardened Carapace - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Your minions cost Armor instead of Mana this turn.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [RLK_956t] Nerubian Skitterer - COST:2 [ATK:2/HP:2]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
}

void ReturnOfTheLichKingCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- SPELL - HUNTER
    // [RLK_804] Conjured Arrow - COST:2
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Deal 2 damage to a minion.
    //       <b>Manathirst (6):</b> Draw that many cards.
    // --------------------------------------------------------
    // GameTag:
    // - MANATHIRST = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [RLK_817] Arcane Quiver - COST:2
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: <b>Discover</b> a spell from your deck.
    //       If it's Arcane, give it <b>Spell Damage +1</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [RLK_818] Ricochet Shot - COST:1
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Deal 1 damage to three random enemies.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [RLK_819] Eversong Portal - COST:4
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Summon 1 4/4 Lynxes with <b>Rush</b>
    //       <i>(improved by <b>Spell Damage</b>)</i>.
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [RLK_820] Halduron Brightwing - COST:3 [ATK:3/HP:4]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give all Arcane spells
    //       in your deck <b>Spell Damage +1</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [RLK_821] Scourge Tamer - COST:2 [ATK:2/HP:2]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Craft a custom Zombeast.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [RLK_825] Shockspitter - COST:2 [ATK:2/HP:2]
    // - Race: Beast, Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage.
    //       <i>(Improved by your hero attacks this game!)</i>
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [RLK_826] Silvermoon Farstrider - COST:2 [ATK:2/HP:3]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give all Arcane spells
    //       in your hand <b>Spell Damage +1</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [RLK_827] Keeneye Spotter - COST:3 [ATK:3/HP:4]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever your hero attacks a minion,
    //       set its Health to 1.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - HUNTER
    // [RLK_828] Hope of Quel'Thalas - COST:6
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After your hero attacks,
    //       give your minions +1/+1 <i>(wherever they are).</i>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
}

void ReturnOfTheLichKingCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- MINION - HUNTER
    // [RLK_819t] Eversong Lynx - COST:4 [ATK:4/HP:4]
    // - Race: Beast, Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [RLK_827e] Hunter's Mark - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: This minion has 1 Health.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [RLK_828e] Light of the Sunwell - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: +1/+1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [RLK_Prologue_804] Conjured Arrow - COST:4
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Deal 2 damage to a minion and draw 2 cards.
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - HUNTER
    // [RLK_Prologue_Bow_003w] Windrunner's Bow - COST:5
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: After your hero attacks,
    //       summon two Silvermoon Sentinels.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [RLK_Prologue_RLK_817] Arcane Quiver - COST:2
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: <b>Discover</b> a spell from your deck.
    //       If it's Arcane, give it <b>Spell Damage +1</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [RLK_Prologue_RLK_826] Silvermoon Farstrider - COST:2 [ATK:2/HP:3]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give all Arcane spells
    //       in your hand <b>Spell Damage +1</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------
}

void ReturnOfTheLichKingCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ MINION - MAGE
    // [RLK_541] Vexallus - COST:5 [ATK:3/HP:5]
    // - Race: Elemental, Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Your Arcane spells
    //       cast twice.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AURA = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [RLK_542] Arcsplitter - COST:3 [ATK:3/HP:2]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add 2 Arcane Bolts to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [RLK_543] Magister's Apprentice - COST:2 [ATK:3/HP:2]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: Your Arcane spells cost (1) less.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [RLK_544] Arcane Defenders - COST:8
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Summon two 5/6 Golems with <b>Taunt</b> and
    //       "Can't be targeted by spells or Hero Powers."
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [RLK_545] Energy Shaper - COST:4 [ATK:3/HP:5]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Transform all spells
    //       in your hand into ones that cost (2) more.
    //       <i>(They keep their original Cost.)</i>
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [RLK_546] Vast Wisdom - COST:3
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Discover</b> two spells that cost (3) or less.
    //       Swap their Costs.
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [RLK_547] Prismatic Elemental - COST:2 [ATK:1/HP:3]
    // - Race: Elemental, Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a spell from any class.
    //       It costs (1) less.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [RLK_548] Arcane Wyrm - COST:1 [ATK:1/HP:2]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add an Arcane Bolt to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [RLK_803] Grand Magister Rommath - COST:9 [ATK:5/HP:7]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Recast each spell
    //       you've cast this game that didn't start in your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [RLK_843] Arcane Bolt - COST:1
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Deal 2 damage.
    //       <b>Manathirst (8):</b> Deal 3 damage instead.
    // --------------------------------------------------------
    // GameTag:
    // - MANATHIRST = 1
    // --------------------------------------------------------
}

void ReturnOfTheLichKingCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ MINION - MAGE
    // [RLK_544t] Golem Guardian - COST:5 [ATK:5/HP:6]
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ------------------------------------- ENCHANTMENT - MAGE
    // [RLK_546e] Infinite Wisdom - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: This card's cost is swapped.
    // --------------------------------------------------------

    // ------------------------------------- ENCHANTMENT - MAGE
    // [RLK_547e] Strange Energy - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ------------------------------------- ENCHANTMENT - MAGE
    // [RLK_803e] Mana Sated - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Your Arcane spells cast twice.
    // --------------------------------------------------------
}

void ReturnOfTheLichKingCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - PALADIN
    // [RLK_527] Timewarden - COST:4 [ATK:3/HP:5]
    // - Race: Dragon, Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Until the end of your next turn,
    //       Dragons you summon gain <b>Taunt</b>
    //       and <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [RLK_916] Daring Drake - COST:4 [ATK:4/HP:4]
    // - Race: Dragon, Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Battlecry:</b> If you're holding a Dragon,
    //       gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [RLK_917] Flight of the Bronze - COST:1
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Discover</b> a Dragon.
    //       <b>Manathirst (7):</b> Summon a 5/5 Drake
    //       with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // - MANATHIRST = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [RLK_918] For Quel'Thalas! - COST:2
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Give a friendly minion +3 Attack.
    //       Give your hero +2 Attack this turn.
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [RLK_919] Anachronos - COST:7 [ATK:8/HP:8]
    // - Race: Dragon, Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Send all other minions 2 turns
    //       into the future.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [RLK_921] Sanguine Soldier - COST:1 [ATK:2/HP:1]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>
    //        <b>Battlecry:</b> Deal 2 damage to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [RLK_922] Seal of Blood - COST:3
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Give a minion +3/+3 and <b>Divine Shield</b>.
    //       Deal 3 damage to your hero.
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [RLK_923] Feast and Famine - COST:1
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: Give your hero +3 Attack this turn.
    //       <b>Manathirst (4):</b> And <b>Lifesteal</b>.
    // --------------------------------------------------------
    // GameTag:
    // - MANATHIRST = 1
    // --------------------------------------------------------
    // RefTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [RLK_924] Blood Matriarch Liadrin - COST:2 [ATK:3/HP:2]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you summon a minion with less Attack than this,
    //       give it <b>Divine Shield</b> and <b>Rush</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [RLK_927] Blood Crusader - COST:6 [ATK:5/HP:5]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your next Paladin minion
    //       this turn costs Health instead of Mana.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void ReturnOfTheLichKingCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------- ENCHANTMENT - PALADIN
    // [RLK_527e2] From the Future - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Has <b>Divine Shield</b> and <b>Taunt</b>.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [RLK_916e] Bravery - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: +1/+1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [RLK_917t] Bronze Defender - COST:5 [ATK:5/HP:5]
    // - Race: Dragon, Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [RLK_918e] For Quel'Thalas! - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: +3 Attack
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [RLK_918e2] For Quel'Thalas! - COST:2
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [RLK_919e] Time Travel - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Sending a minion 2 turns into the future.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [RLK_922e] Blood Seal - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: +3/+3.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [RLK_923e1] Feast - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: +3 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [RLK_923e3] Famine - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [RLK_924e] Annointed in Blood - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Gains <b>Rush</b> and <b>Divine Shield</b>.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [RLK_927e] Crusade - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Costs Health instead of Mana.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_SILENCED = 1
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [RLK_Prologue_Anasterian_003t] Anasterian Sunstrider - COST:5 [ATK:5/HP:12]
    // - Race: Bloodelf, Faction: Horde, Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Rush</b>.
    //       Also damages the minions next to whomever he attacks.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [RLK_Prologue_Gavinrad_002t] Gavinrad the Dire - COST:3 [ATK:2/HP:6]
    // - Faction: Horde, Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Your Silver Hand Recruits have +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AI_MUST_PLAY = 1
    // - AURA = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [RLK_Prologue_Gavinrad_002te1] Inspiring Presence - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [RLK_Prologue_Lightbringer_003e] Blessed by Lightbringer - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Divine Shield</b>.
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - PALADIN
    // [RLK_Prologue_Lightbringer_003w] Hammer of the Lightbringer - COST:4
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------
}

void ReturnOfTheLichKingCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- SPELL - PRIEST
    // [RLK_812] Animate Dead - COST:1
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Resurrect a friendly minion that costs (3)
    //       or less.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [RLK_813] Bonecaller - COST:4 [ATK:2/HP:4]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle</b>: Resurrect a friendly Undead
    //       that died this game.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [RLK_814] Crystalsmith Cultist - COST:1 [ATK:1/HP:2]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Shadow spell,
    //       gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [RLK_815] Shadow Word: Undeath - COST:5
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Deal 2 damage to all enemies.
    //       If a friendly Undead died after your last turn,
    //       deal 2 more.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [RLK_816] Sister Svalna - COST:6 [ATK:6/HP:6]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <i>Permanently</i>
    //       add a Vision of Darkness to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [RLK_822] Haunting Nightmare - COST:3 [ATK:3/HP:3]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Haunt a card in your hand.
    //       When you play it, summon a 3/3 Soldier.
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [RLK_823] Undying Allies - COST:0
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: After you play an Undead this turn,
    //       give it <b>Reborn</b>.
    // --------------------------------------------------------
    // RefTag:
    // - REBORN = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [RLK_829] Grave Digging - COST:4
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Draw 2 cards.
    //       Costs (1) if a friendly Undead died after your last turn.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [RLK_832] High Cultist Basaleph - COST:5 [ATK:3/HP:5]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Resurrect all friendly Undead
    //       that died after your last turn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [RLK_845] Mind Eater - COST:2 [ATK:3/HP:2]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a copy of a card
    //       in your opponent's deck to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
}

void ReturnOfTheLichKingCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- ENCHANTMENT - PRIEST
    // [RLK_814e] Shadow Flow - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: +1/+1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [RLK_816t3] Vision of Darkness - COST:3
    // - Set: RETURN_OF_THE_LICH_KING
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: <b>Discover</b> a Shadow spell.
    //       <i>(This stays in your hand.)</i>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [RLK_822e] Cold Sweat - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [RLK_822e2] Night Terror - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Summons a 3/3 Soldier
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [RLK_822t] Haunted Soldier - COST:3 [ATK:3/HP:3]
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [RLK_823e] Grave Calling - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: After you play an Undead this turn,
    //       give it <b>Reborn</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
}

void ReturnOfTheLichKingCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- MINION - ROGUE
    // [RLK_216] Rotten Rodent - COST:2 [ATK:2/HP:1]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Reduce the Cost of
    //       all <b>Deathrattle</b> cards in your deck by (1).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [RLK_217] Scourge Illusionist - COST:4 [ATK:4/HP:4]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a 4/4 copy of another
    //       <b>Deathrattle</b> minion in your deck to your hand.
    //       It costs (4) less.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [RLK_529] Noxious Infiltrator - COST:4 [ATK:2/HP:5]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    //       <b>Battlecry:</b> If a friendly Undead died
    //       after your last turn, deal 1 damage to a minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - POISONOUS = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [RLK_567] Shadow of Demise - COST:0
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Each time you cast a spell,
    //       transform this into a copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [RLK_568] Concoctor - COST:1 [ATK:1/HP:2]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a random Concoction to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [RLK_569] Potion Belt - COST:2
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Discover</b> 2 Concoctions.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [RLK_570] Ghoulish Alchemist - COST:2 [ATK:3/HP:2]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry</b>: Your next Concoction costs (0).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [RLK_571] Vile Apothecary - COST:3 [ATK:2/HP:4]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       add a random Concoction to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [RLK_572] Potionmaster Putricide - COST:2 [ATK:1/HP:4]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After a minion dies, add a Concoction to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [RLK_573] Ghostly Strike - COST:1
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 1 damage. <b>Combo:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
}

void ReturnOfTheLichKingCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------ ENCHANTMENT - ROGUE
    // [RLK_216e] Rotten - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [RLK_217e] Illusion - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: 4/4.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [RLK_217e2] Illusory - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Costs (4) less.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [RLK_567e] Death's Reflection - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Always copy your last played card.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [RLK_567e2] Shadow of Death - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Transforming into recent spells.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [RLK_570e] Yellow Potion - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [RLK_570e3] Blue Spirit - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Costs (3) less.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [RLK_570e4] Doctored - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Your next Concoction costs (0).
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [RLK_570t] Mixed Potion - COST:3
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [RLK_570t1] Slimy Concoction - COST:3
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Summon a random 3-Cost minion.
    //       <i>Add another Concoction to your hand to mix together!</i>
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [RLK_570t1t] Orange Slime - COST:3 [ATK:3/HP:4]
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [RLK_570t1t1] Mixed Concoction - COST:3
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Summon a random 3-Cost minion.
    //       Add a card to your hand from another class.
    //       It costs (3) less.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [RLK_570t1t2] Mixed Concoction - COST:3
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Summon a random 3-Cost minion.
    //       Destroy a random enemy minion.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [RLK_570t1t3] Mixed Concoction - COST:3
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Deal 3 damage. Summon a random 3-Cost minion.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [RLK_570t1t4] Mixed Concoction - COST:3
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Summon two random 3-Cost minions.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [RLK_570t2] Dreadful Concoction - COST:3
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Destroy a random enemy minion.
    //       <i>Add another Concoction to your hand to mix together!</i>
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [RLK_570t2e] Green Potion - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Poisonous</b> and <b>Reborn</b>.
    // --------------------------------------------------------
    // GameTag:
    // - POISONOUS = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [RLK_570t2t1] Mixed Concoction - COST:3
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Deal 3 damage.
    //       Destroy a random enemy minion.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [RLK_570t2t2] Mixed Concoction - COST:3
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Destroy two random enemy minions.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [RLK_570t3] Bubbling Concoction - COST:3
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Deal 3 damage.
    //       <i>Add another Concoction to your hand to mix together!</i>
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [RLK_570t3t] Mixed Concoction - COST:3
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Deal 3 damage, twice.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [RLK_570t4] Hazy Concoction - COST:3
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Add a card to your hand from another class. It costs (3) less.
    //       <i>Add another Concoction to your hand to mix together!</i>
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [RLK_570t4t1] Mixed Concoction - COST:3
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Add a card to your hand from another class. It costs (3) less.
    //       Destroy a random enemy minion.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [RLK_570t4t2] Mixed Concoction - COST:3
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Deal 3 damage. Add a card to your hand from another class.
    //       It costs (3) less.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [RLK_570t4t3] Mixed Concoction - COST:3
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Add two cards to your hand from another class.
    //       They cost (3) less.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [RLK_570t5] Gleaming Concoction - COST:3
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Draw 2 cards.
    //       <i>Add another Concoction to your hand to mix together!</i>
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [RLK_570tt1] Mixed Concoction - COST:3
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Draw 2 cards. Summon a random 3-Cost minion.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [RLK_570tt2] Mixed Concoction - COST:3
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Deal 3 damage. Draw 2 cards.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [RLK_570tt3] Mixed Concoction - COST:3
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Draw 2 cards. Add a card to your hand from another class.
    //       It costs (3) less.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [RLK_570tt4] Mixed Concoction - COST:3
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Draw 2 cards. Destroy a random enemy minion.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [RLK_570tt5] Mixed Concoction - COST:3
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Draw 4 cards.
    // --------------------------------------------------------
}

void ReturnOfTheLichKingCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- MINION - SHAMAN
    // [RLK_550] Rotgill - COST:5 [ATK:3/HP:6]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your other
    //       minions "<b>Deathrattle:</b> Give
    //         your minions +1/+1."
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [RLK_551] Blightblood Berserker - COST:8 [ATK:3/HP:8]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Taunt</b>, <b>Lifesteal</b>, <b>Reborn</b>
    //       <b>Deathrattle:</b> Deal 3 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - LIFESTEAL = 1
    // - REBORN = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [RLK_552] Unliving Champion - COST:3 [ATK:3/HP:2]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If a friendly
    //       Undead died after your
    //       last turn, summon two
    //       3/2 Zombies.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [RLK_553] Prescience - COST:4
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Draw 2 minions. For each that costs (5)
    //       or more, summon a 
    //       2/3 Spirit with <b>Taunt</b>.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [RLK_554] Harkener of Dread - COST:5 [ATK:2/HP:2]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Summon a 6/6
    //       Undead with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [RLK_909] Deathweaver Aura - COST:2
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Give a minion "<b>Deathrattle:</b> Summon two 3/2 Zombies."
    // <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [RLK_910] Shadow Suffusion - COST:3
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Give your minions
    //       "<b>Deathrattle:</b> Deal 3
    //       damage to a random
    //       enemy."
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [RLK_911] From De Other Side - COST:10
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Summon a copy of each minion in your hand.
    //       They attack random enemy minions, then die.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [RLK_912] Scourge Troll - COST:1 [ATK:1/HP:3]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattles</b> given to this minion trigger twice.
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [RLK_913] Overlord Drakuru - COST:9 [ATK:6/HP:8]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Rush</b>, <b>Windfury</b>
    //       After this attacks and kills
    //       a minion, resurrect it
    //       on your side.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - RUSH = 1
    // - TRIGGER_VISUAL = 1
    // - WINDFURY = 1
    // --------------------------------------------------------
}

void ReturnOfTheLichKingCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [RLK_550e] Deathwatch - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give your minions +1/+1.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [RLK_550e2] Deathsight - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [RLK_553t] Ghastly Apparition - COST:2 [ATK:2/HP:3]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [RLK_554t] Drakkari Specter - COST:6 [ATK:6/HP:6]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [RLK_909e] Voodoo Be With You - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon two 3/2 Zombies.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [RLK_909t] Drakkari Zombie - COST:2 [ATK:3/HP:2]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [RLK_910e] Mojo Missile - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 3 damage to a random enemy.
    // --------------------------------------------------------
}

void ReturnOfTheLichKingCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - WARLOCK
    // [RLK_531] Infantry Reanimator - COST:6 [ATK:4/HP:4]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Resurrect
    //       a friendly Undead.
    //       Give it <b>Reborn</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - REBORN = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [RLK_532] Walking Dead - COST:3 [ATK:2/HP:5]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       If you discard this minion, summon it.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - InvisibleDeathrattle = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [RLK_533] Scourge Supplies - COST:3
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: Draw 3 cards.
    //       Choose one to discard.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [RLK_534] Soul Barrage - COST:5
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: When you play
    //       or discard this, deal 6 damage randomly split among all enemies.
    // --------------------------------------------------------
    // GameTag:
    // - ImmuneToSpellpower = 1
    // - InvisibleDeathrattle = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [RLK_535] Savage Ymirjar - COST:5 [ATK:7/HP:7]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Battlecry:</b> Discard 2 cards.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [RLK_536] Shallow Grave - COST:2
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // --------------------------------------------------------
    // Text: Trigger a friendly minion's <b>Deathrattle</b>, then destroy it.
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [RLK_537] Twisted Tether - COST:4
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Destroy a minion.
    //       Give its stats to a random Undead in your hand.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [RLK_538] Devourer of Souls - COST:1 [ATK:1/HP:3]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After a friendly minion dies, gain its <b>Deathrattle</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [RLK_539] Dar'Khan Drathir - COST:8 [ATK:6/HP:6]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    //       At the end of your turn,
    //       deal 6 damage to the
    //       enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - LIFESTEAL = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [RLK_540] Amorphous Slime - COST:5 [ATK:5/HP:3]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Discard a
    //       random Undead.
    //       <b>Deathrattle:</b> Summon a copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
}

void ReturnOfTheLichKingCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [RLK_537e] Twisted Tether - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [RLK_538e] Devoured Soul - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Copied <b>Deathrattle</b> from {0}.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [RLK_540e] Morphing - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Discarded {0}.
    // --------------------------------------------------------
}

void ReturnOfTheLichKingCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- SPELL - WARRIOR
    // [RLK_600] Sunfire Smithing - COST:4
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Equip a 4/2 Sword.
    //       Give a random minion
    //       in your hand +4/+2.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [RLK_601] Last Stand - COST:4
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: Draw a <b>Taunt</b> minion. Double its stats.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [RLK_602] Silverfury Stalwart - COST:6 [ATK:4/HP:8]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b><b>Taunt</b>, Rush</b>
    //       Can't be targeted by
    //       spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [RLK_603] Light of the Phoenix - COST:4
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Draw 2 cards. Costs (1) less for each damaged friendly character.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [RLK_604] Thori'belore - COST:4 [ATK:4/HP:4]
    // - Race: Elemental, Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Rush</b>. <b>Deathrattle:</b> Go
    //       <b>Dormant</b>. Cast a Fire spell
    //       to revive Thori'belore!
    //       <i>(Revives 2 times.)</i>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [RLK_605] Blazing Power - COST:2
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Give a minion +1/+1.
    //       Repeat for each damaged
    //       friendly character.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [RLK_607] Disruptive Spellbreaker - COST:5 [ATK:4/HP:5]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // --------------------------------------------------------
    // Text: At the end of your turn, your
    //       opponent discards a spell.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [RLK_608] Asvedon, the Grandshield - COST:3 [ATK:3/HP:3]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Cast a copy
    //       of the last spell your opponent played.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [RLK_609] Sunfury Champion - COST:1 [ATK:1/HP:3]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // --------------------------------------------------------
    // Text: After you cast a Fire
    //       spell, deal 1 damage
    //       to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [RLK_960] Embers of Strength - COST:2
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Summon two 1/2
    //       Guards with <b>Taunt</b>.
    //       <b>Manathirst (6):</b> Give
    //       them +1/+2.
    // --------------------------------------------------------
    // GameTag:
    // - MANATHIRST = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
}

void ReturnOfTheLichKingCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [RLK_600e] Overheated - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: +4/+2.
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [RLK_600t] Flamberge - COST:4
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [RLK_601e] Stalwart Stand - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Stats Doubled.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [RLK_604a] Thori'belore - COST:4 [ATK:4/HP:4]
    // - Race: Elemental, Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Rush</b>. <b>Deathrattle:</b> Go
    //       <b>Dormant</b>. Cast a Fire spell
    //       to revive Thori'belore!
    //       <i>(Revives once.)</i>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [RLK_604b] Thori'belore - COST:4 [ATK:4/HP:4]
    // - Race: Elemental, Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [RLK_604t] Phoenix Egg - COST:21 [ATK:0/HP:1]
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Dormant</b>
    //       Cast a Fire spell to
    //       revive Thori'belore!
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - UNTOUCHABLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [RLK_604t2] Phoenix Egg - COST:21 [ATK:0/HP:1]
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Dormant</b>
    //       Cast a Fire spell to
    //       revive Thori'belore!
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - UNTOUCHABLE = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [RLK_605e] On Fire! - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [RLK_607e] Broken Spell - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Storing {0}.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [RLK_960e] Empowered Embers - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: +1/+2.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [RLK_960t] Emberbound Guard - COST:1 [ATK:1/HP:2]
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
}

void ReturnOfTheLichKingCardsGen::AddDemonHunter(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------ SPELL - DEMONHUNTER
    // [RLK_206] Mark of Scorn - COST:2
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: Draw a card. If it's not a
    //       minion, deal 3 damage to
    //       the lowest Health enemy.
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [RLK_207] Fierce Outsider - COST:1 [ATK:2/HP:1]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Outcast:</b> Your next <b>Outcast</b> card costs (1) less.
    // --------------------------------------------------------
    // GameTag:
    // - OUTCAST = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [RLK_208] Fel'dorei Warband - COST:4
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 4 damage.
    //       If your deck has no minions, summon four 1/1 Illidari with
    //       <b>Rush</b>.
    // --------------------------------------------------------
    // RefTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [RLK_209] Unleash Fel - COST:1
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Deal 1 damage
    //       to all enemies. <b>Manathirst (4):</b> With
    //       <b>Lifesteal</b>.
    // --------------------------------------------------------
    // GameTag:
    // - MANATHIRST = 1
    // --------------------------------------------------------
    // RefTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [RLK_210] Wretched Exile - COST:2 [ATK:2/HP:3]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // --------------------------------------------------------
    // Text: After you play an <b>Outcast</b>
    //       card, add a random <b>Outcast</b>
    //       card to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - OUTCAST = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [RLK_211] Deal with a Devil - COST:5
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Summon two 3/3 Felfiends with <b>Lifesteal</b>.
    //       If your deck has no minions, summon another.
    // --------------------------------------------------------
    // RefTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [RLK_212] Brutal Annihilan - COST:9 [ATK:9/HP:9]
    // - Race: Demon, Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Taunt</b>, <b>Rush</b>
    //       After this minion survives
    //       damage, deal that amount
    //       to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // - TAUNT = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [RLK_213] Vengeful Walloper - COST:7 [ATK:5/HP:5]
    // - Race: Demon, Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Rush</b>. Costs (1) less for each <b>Outcast</b> card you've
    // played this game.
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------
    // RefTag:
    // - OUTCAST = 1
    // --------------------------------------------------------

    // ----------------------------------- WEAPON - DEMONHUNTER
    // [RLK_214] Souleater's Scythe - COST:4
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Start of Game:</b> Consume
    //       3 different minions in your
    //       deck. Leave behind Souls
    //       that <b>Discover</b> them.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - START_OF_GAME = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [RLK_215] Felerin, the Forgotten - COST:4 [ATK:3/HP:3]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a random
    //       <b>Outcast</b> card to the left and
    //       right sides of your hand.
    //       They cost (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - OUTCAST = 1
    // --------------------------------------------------------
}

void ReturnOfTheLichKingCardsGen::AddDemonHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [RLK_207e] Introverted - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Your next <b>Outcast</b> card costs (1) less.
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEMONHUNTER
    // [RLK_211t] Felfiend - COST:3 [ATK:3/HP:3]
    // - Race: Demon, Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEMONHUNTER
    // [RLK_214t] Bound Soul - COST:1
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Discover</b> a minion consumed by Souleater's Scythe.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [RLK_Prologue_Illidan_004pe1] Demon Claws - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Your hero has +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEMONHUNTER
    // [RLK_Prologue_Sylvanas_003e1] Defensive Position - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Your hero has +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
}

void ReturnOfTheLichKingCardsGen::AddDeathKnight(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- WEAPON - DEATHKNIGHT
    // [RLK_012] Soulbreaker - COST:3
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: After your hero attacks and kills a minion, gain 2 <b>Corpses</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEATHKNIGHT
    // [RLK_035] Corpse Explosion - COST:5
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Detonate a <b>Corpse</b> to deal 1 damage to all minions. If any
    // are still alive, repeat this.
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEATHKNIGHT
    // [RLK_051] Vampiric Blood - COST:2
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give your hero +5 Health.
    //       Spend 3 <b>Corpses</b> to gain
    //       5 more and draw a card.
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEATHKNIGHT
    // [RLK_116] Necrotic Mortician - COST:2 [ATK:2/HP:3]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If a friendly Undead died after your
    //       last turn, <b>Discover</b> an Unholy Rune card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEATHKNIGHT
    // [RLK_120] Meat Grinder - COST:3 [ATK:3/HP:4]
    // - Race: Mechanical, Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Shred a random minion in your deck to gain 3
    // <b>Corpses.</b>
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEATHKNIGHT
    // [RLK_121] Acolyte of Death - COST:3 [ATK:3/HP:4]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: After a friendly Undead dies, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEATHKNIGHT
    // [RLK_225] Blightfang - COST:3 [ATK:3/HP:3]
    // - Race: Beast, Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Infect all enemy
    //       minions. When they die,
    //       you summon a 2/2
    //       Zombie with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEATHKNIGHT
    // [RLK_506] Boneguard Commander - COST:8 [ATK:8/HP:8]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Raise up to
    //       6 <b>Corpses</b> as 1/2 Risen Footmen with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEATHKNIGHT
    // [RLK_706] Alexandros Mograine - COST:7 [ATK:7/HP:7]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> For the rest of the game, deal 3 damage to your
    // opponent at the end of your turns.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEATHKNIGHT
    // [RLK_741] Soulstealer - COST:8 [ATK:5/HP:5]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy all other
    //       minions. Gain 1 <b>Corpse</b> for
    //       each enemy destroyed.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void ReturnOfTheLichKingCardsGen::AddDeathKnightNonCollect(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- MINION - DEATHKNIGHT
    // [RLK_008t] Risen Ghoul - COST:2 [ATK:2/HP:2]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <i>Doesn't leave a <b>Corpse</b>.</i>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEATHKNIGHT
    // [RLK_025e] Glacial Advance - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: The next spell you cast this turn costs (2) less.
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEATHKNIGHT
    // [RLK_025o] Glacial Advance - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: The next spell you cast this turn costs (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_SILENCED = 1
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEATHKNIGHT
    // [RLK_039t] Grain Crate - COST:1
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Casts When Drawn</b>
    //       Summon a 2/2 Undead Peasant.
    // --------------------------------------------------------
    // GameTag:
    // - TOPDECK = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEATHKNIGHT
    // [RLK_048e] Anti-Magic Shell - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: +1/+1. Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEATHKNIGHT
    // [RLK_061t] Risen Footman - COST:1 [ATK:1/HP:2]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <i>Doesn't leave a <b>Corpse</b>.</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEATHKNIGHT
    // [RLK_066e] Winter's Gift - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Increased Health.
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEATHKNIGHT
    // [RLK_077t] Possessed Fighter - COST:1 [ATK:1/HP:1]
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Reborn</b>
    // --------------------------------------------------------
    // GameTag:
    // - REBORN = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEATHKNIGHT
    // [RLK_085e] Bonestorm - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEATHKNIGHT
    // [RLK_085t] Risen Golem - COST:1 [ATK:1/HP:1]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <i>Doesn't leave a <b>Corpse</b>.</i>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEATHKNIGHT
    // [RLK_225e] Plagued - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 2/2 Zombie with <b>Taunt</b> for your
    // opponent.
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEATHKNIGHT
    // [RLK_226t] Risen Ymirjar - COST:3 [ATK:3/HP:3]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <i>Doesn't leave a <b>Corpse</b>.</i>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEATHKNIGHT
    // [RLK_705t] Shambling Zombie - COST:1 [ATK:1/HP:1]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Reborn</b>
    // --------------------------------------------------------
    // GameTag:
    // - REBORN = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEATHKNIGHT
    // [RLK_706e3] Mograine's Migraine - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: For the rest of the game, deal 3 damage to your opponent at the end
    // of your turns.
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEATHKNIGHT
    // [RLK_707e] Grave Mark - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEATHKNIGHT
    // [RLK_707e2] Grave Force - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: +3 Attack.
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEATHKNIGHT
    // [RLK_715e] Runeforged - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEATHKNIGHT
    // [RLK_753e] Dug Up - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: +1/+2.
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEATHKNIGHT
    // [RLK_907t] Rime Elemental - COST:2 [ATK:2/HP:1]
    // - Race: Elemental, Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 2 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEATHKNIGHT
    // [RLK_958e] Thrown a Bone - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEATHKNIGHT
    // [RLK_Prologue_025] Frost Strike - COST:2
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: Deal 3 damage
    //       to a minion. If that
    //       kills it, <b>Discover</b> a
    //       Frost Rune card.
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEATHKNIGHT
    // [RLK_Prologue_056] Unholy Frenzy - COST:3
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: Choose an enemy minion.
    //       Your minions attack it.
    //       Resummon any that die.
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEATHKNIGHT
    // [RLK_Prologue_066] Hematurge - COST:2 [ATK:2/HP:3]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Spend a
    //       <b>Corpse</b> to <b>Discover</b> a
    //       Blood Rune card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ----------------------------------- WEAPON - DEATHKNIGHT
    // [RLK_Prologue_Frostmourne_001] Frostmourne - COST:7
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon every minion killed by this weapon.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEATHKNIGHT
    // [RLK_Prologue_Frostmourne_001s] The Lich King's Blade - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Casts When Drawn</b>
    //       Equip Frostmourne.
    // --------------------------------------------------------
    // GameTag:
    // - TOPDECK = 1
    // --------------------------------------------------------

    // ----------------------------------- WEAPON - DEATHKNIGHT
    // [RLK_Prologue_RLK_012] Soulbreaker - COST:3
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: After your hero attacks and kills a minion, gain 2 <b>Corpses</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEATHKNIGHT
    // [RLK_Prologue_RLK_025e] Glacial Advance - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: The next spell you cast this turn costs (2) less.
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEATHKNIGHT
    // [RLK_Prologue_RLK_025o] Glacial Advance - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: The next spell you cast this turn costs (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_SILENCED = 1
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEATHKNIGHT
    // [RLK_Prologue_RLK_035] Corpse Explosion - COST:5
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Detonate a <b>Corpse</b> to deal 1 damage to all minions. If any
    // are still alive, repeat this.
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEATHKNIGHT
    // [RLK_Prologue_RLK_051] Vampiric Blood - COST:2
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give your hero +5 Health.
    //       Spend 3 <b>Corpses</b> to gain
    //       5 more and draw a card.
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEATHKNIGHT
    // [RLK_Prologue_RLK_120] Meat Grinder - COST:3 [ATK:3/HP:4]
    // - Race: Mechanical, Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Shred a random minion in your deck to gain 3
    // <b>Corpses.</b>
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEATHKNIGHT
    // [RLK_Prologue_RLK_506] Boneguard Commander - COST:8 [ATK:8/HP:8]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Raise up to
    //       6 <b>Corpses</b> as 1/2 Risen Footmen with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEATHKNIGHT
    // [RLK_Prologue_RLK_707e] Grave Mark - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEATHKNIGHT
    // [RLK_Prologue_RLK_707e2] Grave Force - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: +3 Attack.
    // --------------------------------------------------------

    // ----------------------------------- MINION - DEATHKNIGHT
    // [RLK_Prologue_RLK_741] Soulstealer - COST:8 [ATK:5/HP:5]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy all other
    //       minions. Gain 1 <b>Corpse</b> for
    //       each enemy destroyed.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------ ENCHANTMENT - DEATHKNIGHT
    // [RLK_Prologue_RLK_753e] Dug Up - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: +1/+2.
    // --------------------------------------------------------

    // ------------------------------------ SPELL - DEATHKNIGHT
    // [RLK_Prologue_TheScourge_003s] The Scourge - COST:9
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Fill your board with random Undead.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
}

void ReturnOfTheLichKingCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - NEUTRAL
    // [RLK_029] Shatterskin Gargoyle - COST:6 [ATK:4/HP:6]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Deal 4 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_070] Infected Peasant - COST:2 [ATK:2/HP:1]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 2/2 Undead Peasant.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_104] Street Sweeper - COST:4 [ATK:2/HP:2]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 2 damage to all other minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_113] Brittleskin Zombie - COST:3 [ATK:4/HP:3]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> If it's your opponent's turn, deal 3 damage to
    // them.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_117] Incorporeal Corporal - COST:2 [ATK:5/HP:5]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: After this minion attacks,
    //       destroy it.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_119] Drakkari Embalmer - COST:3 [ATK:3/HP:4]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly Undead <b>Reborn</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - REBORN = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_123] Bone Flinger - COST:2 [ATK:2/HP:3]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If a friendly
    //       Undead died after your last
    //       turn, deal 2 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_218] Silvermoon Arcanist - COST:3 [ATK:2/HP:2]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Spell Damage +2</b>
    //       <b>Battlecry:</b> Your spells can’t
    //       target heroes this turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_219] Sunfury Clergy - COST:3 [ATK:2/HP:4]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 3 Health
    //       to all friendly characters.
    //       <b>Manathirst (6):</b> Restore
    //       6 Health instead.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - MANATHIRST = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_220] Tenacious San'layn - COST:5 [ATK:4/HP:6]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Lifesteal</b>
    //       Whenever this attacks,
    //       deal 2 damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - LIFESTEAL = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_221] Crystal Broker - COST:3 [ATK:3/HP:2]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Manathirst (5):</b> Summon a
    //       random 3-Cost minion.
    //       <b>Manathirst (10):</b> Summon an
    //       8-Cost minion instead.
    // --------------------------------------------------------
    // GameTag:
    // - MANATHIRST = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_222] Astalor Bloodsworn - COST:2 [ATK:2/HP:2]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add Astalor, the Protector to your hand.
    // <b>Manathirst (4):</b> Deal 2 damage.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - MANATHIRST = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_518] Silvermoon Sentinel - COST:3 [ATK:2/HP:5]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Manathirst (8):</b> Gain +2/+2 and <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - MANATHIRST = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [RLK_590] The Sunwell - COST:9
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Fill your hand with random spells. Costs (1) less for each other
    // card in your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_591] Bonelord Frostwhisper - COST:6 [ATK:6/HP:6]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> For the rest of the game, your first card each
    // turn costs (0). You die in 3 turns.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_592] Invincible - COST:8 [ATK:5/HP:5]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Reborn</b>
    //       <b>Battlecry and Deathrattle:</b>
    //       Give a random friendly Undead
    //       +5/+5 and <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - DEATHRATTLE = 1
    // - REBORN = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_593] Lor'themar Theron - COST:7 [ATK:7/HP:7]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Double the stats of all minions in your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_653] Infectious Ghoul - COST:5 [ATK:5/HP:4]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give a
    //       random friendly minion
    //       "<b>Deathrattle:</b> Summon an
    //       Infectious Ghoul."
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_677] Sanctum Spellbender - COST:4 [ATK:3/HP:6]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // --------------------------------------------------------
    // Text: Whenever your opponent
    //       targets another minion with
    //       a spell, redirect it to this.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_824] Arms Dealer - COST:1 [ATK:1/HP:2]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: After you summon an Undead, give it +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_830] Flesh Behemoth - COST:9 [ATK:4/HP:8]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Draw another
    //       Undead and summon
    //       a copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_831] Plaguespreader - COST:4 [ATK:4/HP:4]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Transform a random minion in your opponent's
    // hand into a Plaguespreader.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_833] Foul Egg - COST:1 [ATK:0/HP:2]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 3/3 Undead Chicken.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_834] Nerubian Vizier - COST:3 [ATK:2/HP:4]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a spell.
    //       If a friendly Undead died
    //       after your last turn,
    //       it costs (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_867] Vrykul Necrolyte - COST:2 [ATK:2/HP:2]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly
    //       minion "<b>Deathrattle:</b>
    //       Summon a 2/2 Zombie
    //       with <b>Rush</b>."
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DEATH_KNIGHT = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_900] Scourge Rager - COST:3 [ATK:5/HP:4]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Reborn</b>
    //       <b>Battlecry:</b> Die.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - REBORN = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_914] Umbral Geist - COST:2 [ATK:3/HP:1]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a random
    //       Shadow spell to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_915] Amber Whelp - COST:3 [ATK:3/HP:3]
    // - Race: Dragon, Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon, deal 3 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_926] Bloodied Knight - COST:3 [ATK:4/HP:5]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       deal 2 damage to
    //       your hero.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_950] Translocation Instructor - COST:5 [ATK:4/HP:4]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose an
    //       enemy minion. Swap it
    //       with a random one
    //       in their deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_951] Coroner - COST:2 [ATK:2/HP:2]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Freeze</b>
    //       an enemy minion.
    //       <b>Manathirst (6):</b>
    //       <b>Silence</b> it first.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - MANATHIRST = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // - SILENCE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_952] Enchanter - COST:3 [ATK:3/HP:3]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // --------------------------------------------------------
    // Text: Enemy minions take double damage during your turn.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_955] Silvermoon Armorer - COST:4 [ATK:4/HP:4]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    //       <b>Manathirst (7):</b> Gain +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - MANATHIRST = 1
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_957] Banshee - COST:1 [ATK:2/HP:1]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give a random friendly Undead +2/+1.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_970] Hawkstrider Rancher - COST:3 [ATK:2/HP:5]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Epic
    // --------------------------------------------------------
    // Text: After you play a minion,
    //       give it +1/+1 and
    //       "<b>Deathrattle:</b> Summon a
    //       1/1 Hawkstrider."
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
}

void ReturnOfTheLichKingCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - NEUTRAL
    // [RLK_018t] Rampaging Zombie - COST:2 [ATK:2/HP:2]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_070t] Undead Peasant - COST:2 [ATK:2/HP:2]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [RLK_218e] Insane Arcanity - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Can't be targeted by spells this turn.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [RLK_218e2] Arcane Insanity - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Can't be targeted by spells this turn.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [RLK_218e3] Insane Arcane Power - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Your spells can’t target heroes this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_222t1] Astalor, the Protector - COST:5 [ATK:5/HP:5]
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add Astalor, the Flamebringer to your hand.
    // <b>Manathirst (7):</b> Gain 5 Armor.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - MANATHIRST = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_222t2] Astalor, the Flamebringer - COST:8 [ATK:8/HP:8]
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 8 damage
    //       randomly split between all
    //       enemies. <b>Manathirst (10):</b>
    //       Deal 8 more.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - MANATHIRST = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [RLK_518e] Silvermoon's Might - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [RLK_591e] Lich Death Counter - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Your hero dies in 3 turns.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [RLK_591e2] Lich's Deathcurse - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Costs (0).
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [RLK_592e] Invincible's Reins - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: +5/+5.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [RLK_593e] Superior Strategy - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Doubled Attack and Health.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [RLK_653e] Infected - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon an Infectious Ghoul.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [RLK_824e] Undead Fortitude - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [RLK_826e] Silvermoon Farstrider Spellpower - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_833t] Foul Fowl - COST:3 [ATK:3/HP:3]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [RLK_834e] Nerubian Vision - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Costs (2) less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [RLK_867e] It's Necro-Lit - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 2/2 Zombie with <b>Rush</b>.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [RLK_955e] Supplied - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [RLK_957e] Banshee's Wail - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: +2/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [RLK_970e] Hawkriding - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: +1/+1. <b>Deathrattle:</b> Summon a 1/1 Hawkstrider.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_970t] Hawkstrider - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [RLK_COIN1] The Coin - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Gain 1 Mana Crystal this turn only.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [RLK_COIN2] The Coin - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Gain 1 Mana Crystal this turn only.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_Prologue_218] Silvermoon Arcanist - COST:3 [ATK:2/HP:2]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Spell Damage +2</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_Prologue_219] Sunfury Clergy - COST:3 [ATK:2/HP:4]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 3 Health
    //       to all friendly characters.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_Prologue_518] Silvermoon Sentinel - COST:3 [ATK:2/HP:5]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_Prologue_InnerGate_003t] Inner Gate of Quel'Thalas - COST:5
    // [ATK:0/HP:10]
    // - Faction: Horde, Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Sylvanas is <b>Immune</b>. <b>Deathrattle:</b> Deal 20 damage to
    // Sylvanas.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AURA = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_Prologue_OuterGate_003t] Elfgate of Silvermoon - COST:5
    // [ATK:0/HP:15]
    // - Faction: Horde, Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: Sylvanas is <b>Immune</b>. <b>Deathrattle:</b> Summon the  Inner
    // Gate of Quel'Thalas. 
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AURA = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_Prologue_RLK_018t] Rampaging Zombie - COST:2 [ATK:2/HP:2]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Rush</b>
    // --------------------------------------------------------
    // GameTag:
    // - RUSH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_Prologue_RLK_070] Infected Peasant - COST:2 [ATK:2/HP:1]
    // - Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 2/2 Undead Peasant.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_Prologue_RLK_070t] Undead Peasant - COST:2 [ATK:2/HP:2]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_Prologue_RLK_113] Brittleskin Zombie - COST:3 [ATK:4/HP:3]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> If it's your opponent's turn, deal 3 damage to
    // them.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_Prologue_RLK_653] Infectious Ghoul - COST:5 [ATK:5/HP:4]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give a
    //       random friendly minion
    //       "<b>Deathrattle:</b> Summon an
    //       Infectious Ghoul."
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [RLK_Prologue_RLK_653e] Infected - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon an Infectious Ghoul.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [RLK_Prologue_RLK_826e] Silvermoon Farstrider Spellpower - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_Prologue_RLK_830] Flesh Behemoth - COST:9 [ATK:4/HP:8]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Draw another
    //       Undead and summon
    //       a copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [RLK_Prologue_RLK_957] Banshee - COST:1 [ATK:2/HP:1]
    // - Race: Undead, Set: RETURN_OF_THE_LICH_KING, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give a random friendly Undead +2/+1.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [RLK_Prologue_RLK_957e] Banshee's Wail - COST:0
    // - Set: RETURN_OF_THE_LICH_KING
    // --------------------------------------------------------
    // Text: +2/+1.
    // --------------------------------------------------------
}

void ReturnOfTheLichKingCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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

    AddDeathKnight(cards);
    AddDeathKnightNonCollect(cards);

    AddNeutral(cards);
    AddNeutralNonCollect(cards);
}
}  // namespace RosettaStone::PlayMode
