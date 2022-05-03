//// This code is based on Sabberstone project.
//// Copyright (c) 2017-2021 SabberStone Team, darkfriend77 & rnilva
//// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
//// Copyright (c) 2017-2021 Chris Ohk
//
//#include <Rosetta/PlayMode/CardSets/LoECardsGen.hpp>
//#include <Rosetta/PlayMode/Tasks/SimpleTasks.hpp>
//
//using namespace RosettaStone::PlayMode::SimpleTasks;
//
//namespace RosettaStone::PlayMode
//{
//void LoECardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
//{
//    // Do nothing
//}
//
//void LoECardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
//{
//    // Do nothing
//}
//
//void LoECardsGen::AddDruid(std::map<std::string, CardDef>& cards)
//{
//    // ----------------------------------------- MINION - DRUID
//    // [LOE_050] Mounted Raptor - COST:3 [ATK:3/HP:2]
//    // - Race: Beast, Set: LoE, Rarity: Common
//    // --------------------------------------------------------
//    // Text: <b>Deathrattle:</b> Summon a random 1-Cost minion.
//    // --------------------------------------------------------
//    // GameTag:
//    // - DEATHRATTLE = 1
//    // --------------------------------------------------------
//
//    // ----------------------------------------- MINION - DRUID
//    // [LOE_051] Jungle Moonkin - COST:4 [ATK:4/HP:4]
//    // - Race: Beast, Set: LoE, Rarity: Rare
//    // --------------------------------------------------------
//    // Text: Both players have <b>Spell Damage +2</b>.
//    // --------------------------------------------------------
//    // GameTag:
//    // - SPELLPOWER = 2
//    // --------------------------------------------------------
//
//    // ------------------------------------------ SPELL - DRUID
//    // [LOE_115] Raven Idol - COST:1
//    // - Set: LoE, Rarity: Common
//    // --------------------------------------------------------
//    // Text: <b>Choose One -</b>
//    //       <b>Discover</b> a minion; or <b>Discover</b> a spell.
//    // --------------------------------------------------------
//    // GameTag:
//    // - DISCOVER = 1
//    // - CHOOSE_ONE = 1
//    // - USE_DISCOVER_VISUALS = 1
//    // --------------------------------------------------------
//}
//
//void LoECardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
//{
//    // ------------------------------------------ SPELL - DRUID
//    // [LOE_115a] Break Free (*) - COST:1
//    // - Set: LoE
//    // --------------------------------------------------------
//    // Text: <b>Discover</b> a minion.
//    // --------------------------------------------------------
//    // GameTag:
//    // - DISCOVER = 1
//    // - USE_DISCOVER_VISUALS = 1
//    // --------------------------------------------------------
//
//    // ------------------------------------------ SPELL - DRUID
//    // [LOE_115b] Awakened (*) - COST:1
//    // - Set: LoE
//    // --------------------------------------------------------
//    // Text: <b>Discover</b> a spell.
//    // --------------------------------------------------------
//    // GameTag:
//    // - DISCOVER = 1
//    // - USE_DISCOVER_VISUALS = 1
//    // --------------------------------------------------------
//}
//
//void LoECardsGen::AddHunter(std::map<std::string, CardDef>& cards)
//{
//    // ---------------------------------------- MINION - HUNTER
//    // [LOE_020] Desert Camel - COST:3 [ATK:2/HP:4]
//    // - Race: Beast, Set: LoE, Rarity: Common
//    // --------------------------------------------------------
//    // Text: <b>Battlecry:</b> Put a 1-Cost minion from each deck
//    //       into the battlefield.
//    // --------------------------------------------------------
//    // GameTag:
//    // - BATTLECRY = 1
//    // --------------------------------------------------------
//
//    // ----------------------------------------- SPELL - HUNTER
//    // [LOE_021] Dart Trap - COST:2
//    // - Set: LoE, Rarity: Common
//    // --------------------------------------------------------
//    // Text: <b>Secret:</b> After an opposing Hero Power is used,
//    //       deal 5 damage to a random enemy.
//    // --------------------------------------------------------
//    // GameTag:
//    // - SECRET = 1
//    // --------------------------------------------------------
//
//    // ----------------------------------------- SPELL - HUNTER
//    // [LOE_105] Explorer's Hat - COST:2
//    // - Set: LoE, Rarity: Rare
//    // --------------------------------------------------------
//    // Text: Give a minion +1/+1 and "<b>Deathrattle:</b>
//    //       Add an Explorer's Hat to your hand."
//    // --------------------------------------------------------
//    // PlayReq:
//    // - REQ_TARGET_TO_PLAY = 0
//    // - REQ_MINION_TARGET = 0
//    // --------------------------------------------------------
//    // RefTag:
//    // - DEATHRATTLE = 1
//    // --------------------------------------------------------
//}
//
//void LoECardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
//{
//    // ----------------------------------- ENCHANTMENT - HUNTER
//    // [LOE_105e] Explorer's Hat (*) - COST:0
//    // - Set: LoE
//    // --------------------------------------------------------
//    // Text: +1/+1. <b>Deathrattle:</b>
//    //       Add an Explorer's Hat to your hand.
//    // --------------------------------------------------------
//}
//
//void LoECardsGen::AddMage(std::map<std::string, CardDef>& cards)
//{
//    CardDef cardDef;
//
//    // ------------------------------------------- SPELL - MAGE
//    // [LOE_002] Forgotten Torch - COST:3
//    // - Set: LoE, Rarity: Common
//    // --------------------------------------------------------
//    // Text: Deal 3 damage. Shuffle a 'Roaring Torch'
//    //       into your deck that deals 6 damage.
//    // --------------------------------------------------------
//    // PlayReq:
//    // - REQ_TARGET_TO_PLAY = 0
//    // --------------------------------------------------------
//
//    // ------------------------------------------ MINION - MAGE
//    // [LOE_003] Ethereal Conjurer - COST:5 [ATK:6/HP:3]
//    // - Set: LoE Rarity: Common
//    // --------------------------------------------------------
//    // Text: <b>Battlecry: Discover</b> a spell.
//    // --------------------------------------------------------
//    // GameTag:
//    // - BATTLECRY = 1
//    // - DISCOVER = 1
//    // - USE_DISCOVER_VISUALS = 1
//    // --------------------------------------------------------
//    cardDef.ClearData();
//    cardDef.power.AddPowerTask(std::make_shared<DiscoverTask>(DiscoverType::SPELL));
//    cards.emplace("LOE_003", CardDef(power));
//
//    // ------------------------------------------ MINION - MAGE
//    // [LOE_119] Animated Armor - COST:4 [ATK:4/HP:4]
//    // - Set: LoE, Rarity: Rare
//    // --------------------------------------------------------
//    // Text: Your hero can only take 1 damage at a time.
//    // --------------------------------------------------------
//}
//
//void LoECardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
//{
//    // ------------------------------------------- SPELL - MAGE
//    // [LOE_002t] Roaring Torch (*) - COST:3
//    // - Set: LoE
//    // --------------------------------------------------------
//    // Text: Deal 6 damage.
//    // --------------------------------------------------------
//    // PlayReq:
//    // - REQ_TARGET_TO_PLAY = 0
//    // --------------------------------------------------------
//}
//
//void LoECardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
//{
//    // --------------------------------------- MINION - PALADIN
//    // [LOE_017] Keeper of Uldaman - COST:4 [ATK:3/HP:4]
//    // - Set: LoE, Rarity: Common
//    // --------------------------------------------------------
//    // Text: <b>Battlecry:</b> Set a minion's Attack and Health to 3.
//    // --------------------------------------------------------
//    // GameTag:
//    // - BATTLECRY = 1
//    // --------------------------------------------------------
//    // PlayReq:
//    // - REQ_TARGET_IF_AVAILABLE = 0
//    // - REQ_MINION_TARGET = 0
//    // --------------------------------------------------------
//
//    // ---------------------------------------- SPELL - PALADIN
//    // [LOE_026] Anyfin Can Happen - COST:10
//    // - Set: LoE, Rarity: Rare
//    // --------------------------------------------------------
//    // Text: Summon 7 Murlocs that died this game.
//    // --------------------------------------------------------
//
//    // ---------------------------------------- SPELL - PALADIN
//    // [LOE_027] Sacred Trial - COST:1
//    // - Set: LoE, Rarity: Common
//    // --------------------------------------------------------
//    // Text: <b>Secret:</b> After your opponent has at least
//    //       3 minions and plays another, destroy it.
//    // --------------------------------------------------------
//    // GameTag:
//    // - SECRET = 1
//    // --------------------------------------------------------
//}
//
//void LoECardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
//{
//    // ---------------------------------- ENCHANTMENT - PALADIN
//    // [LOE_017e] Watched (*) - COST:0
//    // - Set: LoE
//    // --------------------------------------------------------
//    // Text: Stats changed to 3/3.
//    // --------------------------------------------------------
//}
//
//void LoECardsGen::AddPriest(std::map<std::string, CardDef>& cards)
//{
//    // ---------------------------------------- MINION - PRIEST
//    // [LOE_006] Museum Curator - COST:2 [ATK:1/HP:2]
//    // - Set: LoE, Rarity: Common
//    // --------------------------------------------------------
//    // Text: <b>Battlecry: Discover</b> a <b>Deathrattle</b> card.
//    // --------------------------------------------------------
//    // GameTag:
//    // - BATTLECRY = 1
//    // - DISCOVER = 1
//    // - USE_DISCOVER_VISUALS = 1
//    // --------------------------------------------------------
//    // RefTag:
//    // - DEATHRATTLE = 1
//    // --------------------------------------------------------
//
//    // ----------------------------------------- SPELL - PRIEST
//    // [LOE_104] Entomb - COST:6
//    // - Set: LoE, Rarity: Common
//    // --------------------------------------------------------
//    // Text: Choose an enemy minion. Shuffle it into your deck.
//    // --------------------------------------------------------
//    // PlayReq:
//    // - REQ_TARGET_TO_PLAY = 0
//    // - REQ_MINION_TARGET = 0
//    // - REQ_ENEMY_TARGET = 0
//    // --------------------------------------------------------
//
//    // ----------------------------------------- SPELL - PRIEST
//    // [LOE_111] Excavated Evil - COST:5
//    // - Set: LoE, Rarity: Rare
//    // --------------------------------------------------------
//    // Text: Deal 3 damage to all minions.
//    //       Shuffle this card into your opponent's deck.
//    // --------------------------------------------------------
//}
//
//void LoECardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
//{
//    // Do nothing
//}
//
//void LoECardsGen::AddRogue(std::map<std::string, CardDef>& cards)
//{
//    CardDef cardDef;
//
//    // ----------------------------------------- MINION - ROGUE
//    // [LOE_010] Pit Snake - COST:1 [ATK:2/HP:1]
//    // - Race: Beast, Set: LoE, Rarity: Common
//    // --------------------------------------------------------
//    // Text: <b>Poisonous</b>
//    // --------------------------------------------------------
//    // GameTag:
//    // - POISONOUS = 1
//    // --------------------------------------------------------
//
//    // ----------------------------------------- MINION - ROGUE
//    // [LOE_012] Tomb Pillager - COST:4 [ATK:5/HP:4]
//    // - Set: LoE, Rarity: Common
//    // --------------------------------------------------------
//    // Text: <b>Deathrattle:</b> Add a Coin to your hand.
//    // --------------------------------------------------------
//    // GameTag:
//    // - DEATHRATTLE = 1
//    // --------------------------------------------------------
//    cardDef.ClearData();
//    cardDef.power.AddDeathrattleTask(
//        std::make_shared<AddCardTask>(EntityType::HAND, "GAME_005"));
//    cards.emplace("LOE_012", CardDef(power));
//
//    // ----------------------------------------- MINION - ROGUE
//    // [LOE_019] Unearthed Raptor - COST:3 [ATK:3/HP:4]
//    // - Set: LoE, Rarity: Rare
//    // --------------------------------------------------------
//    // Text: <b>Battlecry:</b> Choose a friendly minion.
//    //       Gain a copy of its <b>Deathrattle</b>.
//    // --------------------------------------------------------
//    // GameTag:
//    // - BATTLECRY = 1
//    // --------------------------------------------------------
//    // PlayReq:
//    // - REQ_TARGET_IF_AVAILABLE = 0
//    // - REQ_FRIENDLY_TARGET = 0
//    // - REQ_TARGET_WITH_DEATHRATTLE = 0
//    // --------------------------------------------------------
//    // RefTag:
//    // - DEATHRATTLE = 1
//    // --------------------------------------------------------
//}
//
//void LoECardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
//{
//    // ------------------------------------ ENCHANTMENT - ROGUE
//    // [LOE_019e] Unearthed Raptor (*) - COST:0
//    // - Set: LoE
//    // --------------------------------------------------------
//    // Text: Copied Deathrattle from {0}.
//    // --------------------------------------------------------
//}
//
//void LoECardsGen::AddShaman(std::map<std::string, CardDef>& cards)
//{
//    // ---------------------------------------- MINION - SHAMAN
//    // [LOE_016] Rumbling Elemental - COST:4 [ATK:2/HP:6]
//    // - Race: Elemental, Set: LoE, Rarity: Common
//    // --------------------------------------------------------
//    // Text: After you play a <b>Battlecry</b> minion,
//    //       deal 2 damage to a random enemy.
//    // --------------------------------------------------------
//    // RefTag:
//    // - BATTLECRY = 1
//    // --------------------------------------------------------
//
//    // ---------------------------------------- MINION - SHAMAN
//    // [LOE_018] Tunnel Trogg - COST:1 [ATK:1/HP:3]
//    // - Set: LoE, Rarity: Common
//    // --------------------------------------------------------
//    // Text: Whenever you <b>Overload</b>,
//    //       gain +1 Attack per locked Mana Crystal.
//    // --------------------------------------------------------
//    // RefTag:
//    // - OVERLOAD = 1
//    // --------------------------------------------------------
//
//    // ----------------------------------------- SPELL - SHAMAN
//    // [LOE_113] Everyfin is Awesome - COST:7
//    // - Set: LoE, Rarity: Rare
//    // --------------------------------------------------------
//    // Text: Give your minions +2/+2.
//    //       Costs (1) less for each Murloc you control.
//    // --------------------------------------------------------
//}
//
//void LoECardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
//{
//    // ----------------------------------- ENCHANTMENT - SHAMAN
//    // [LOE_018e] Trogg No Stupid (*) - COST:0
//    // - Set: LoE
//    // --------------------------------------------------------
//    // Text: Increased Attack.
//    // --------------------------------------------------------
//}
//
//void LoECardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
//{
//    // ---------------------------------------- SPELL - WARLOCK
//    // [LOE_007] Curse of Rafaam - COST:2
//    // - Set: LoE, Rarity: common
//    // --------------------------------------------------------
//    // Text: Give your opponent a 'Cursed!' card.
//    //       While they hold it, they take 2 damage on their turn.
//    // --------------------------------------------------------
//
//    // --------------------------------------- MINION - WARLOCK
//    // [LOE_023] Dark Peddler - COST:2 [ATK:2/HP:2]
//    // - Set: LoE, Rarity: Common
//    // --------------------------------------------------------
//    // Text: <b>Battlecry: Discover</b> a 1-Cost card.
//    // --------------------------------------------------------
//    // GameTag:
//    // - BATTLECRY = 1
//    // - DISCOVER = 1
//    // - USE_DISCOVER_VISUALS = 1
//    // --------------------------------------------------------
//
//    // --------------------------------------- MINION - WARLOCK
//    // [LOE_116] Reliquary Seeker - COST:1 [ATK:1/HP:1]
//    // - Set: LoE, Rarity: Rare
//    // --------------------------------------------------------
//    // Text: <b>Battlecry:</b> If you have 6 other minions,
//    //       gain +4/+4.
//    // --------------------------------------------------------
//    // GameTag:
//    // - BATTLECRY = 1
//    // --------------------------------------------------------
//}
//
//void LoECardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
//{
//    // ---------------------------------- ENCHANTMENT - WARLOCK
//    // [LOE_009e] Sinister Power (*) - COST:0
//    // - Set: LoE
//    // --------------------------------------------------------
//    // Text: +4/+4.
//    // --------------------------------------------------------
//
//    // ---------------------------------------- SPELL - WARLOCK
//    // [LOE_007t] Cursed! (*) - COST:2
//    // - Set: LoE
//    // --------------------------------------------------------
//    // Text: While this is in your hand,
//    //       take 2 damage at the start of your turn.
//    // --------------------------------------------------------
//    // GameTag:
//    // - ImmuneToSpellpower = 1
//    // - EVIL_GLOW = 1
//    // --------------------------------------------------------
//}
//
//void LoECardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
//{
//    // --------------------------------------- MINION - WARRIOR
//    // [LOE_009] Obsidian Destroyer - COST:7 [ATK:7/HP:7]
//    // - Set: LoE, Rarity: Common
//    // --------------------------------------------------------
//    // Text: At the end of your turn,
//    //       summon a 1/1 Scarab with <b>Taunt</b>.
//    // --------------------------------------------------------
//    // RefTag:
//    // - TAUNT = 1
//    // --------------------------------------------------------
//
//    // --------------------------------------- MINION - WARRIOR
//    // [LOE_022] Fierce Monkey - COST:3 [ATK:3/HP:4]
//    // - Race: Beast, Set: LoE, Rarity: Common
//    // --------------------------------------------------------
//    // Text: <b>Taunt</b>
//    // --------------------------------------------------------
//    // GameTag:
//    // - TAUNT = 1
//    // --------------------------------------------------------
//
//    // --------------------------------------- WEAPON - WARRIOR
//    // [LOE_118] Cursed Blade - COST:1 [ATK:2/HP:0]
//    // - Set: LoE, Rarity: Rare
//    // --------------------------------------------------------
//    // Text: Double all damage dealt to your hero.
//    // --------------------------------------------------------
//    // GameTag:
//    // - DURABILITY = 3
//    // --------------------------------------------------------
//}
//
//void LoECardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
//{
//    // --------------------------------------- MINION - WARRIOR
//    // [LOE_009t] Scarab (*) - COST:1 [ATK:1/HP:1]
//    // - Race: Beast, Set: LoE
//    // --------------------------------------------------------
//    // Text: <b>Taunt</b>
//    // --------------------------------------------------------
//    // GameTag:
//    // - TAUNT = 1
//    // --------------------------------------------------------
//
//    // ---------------------------------- ENCHANTMENT - WARRIOR
//    // [LOE_118e] Cursed Blade (*) - COST:0
//    // - Set: LoE
//    // --------------------------------------------------------
//    // Text: Double all damage dealt to your hero.
//    // --------------------------------------------------------
//}
//
//void LoECardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
//{
//    CardDef cardDef;
//
//    // --------------------------------------- MINION - NEUTRAL
//    // [LOE_011] Reno Jackson - COST:6 [ATK:4/HP:6]
//    // - Set: LoE, Rarity: Legendary
//    // --------------------------------------------------------
//    // Text: <b>Battlecry:</b> If your deck has no duplicates,
//    //       fully heal your hero.
//    // --------------------------------------------------------
//    // GameTag:
//    // - ELITE = 1
//    // - BATTLECRY = 1
//    // - AFFECTED_BY_HEALING_DOES_DAMAGE = 1
//    // --------------------------------------------------------
//
//    // --------------------------------------- MINION - NEUTRAL
//    // [LOE_029] Jeweled Scarab - COST:2 [ATK:1/HP:1]
//    // - Race: Beast, Set: LoE, Rarity: Common
//    // --------------------------------------------------------
//    // Text: <b>Battlecry: Discover</b> a 3-Cost card.
//    // --------------------------------------------------------
//    // GameTag:
//    // - BATTLECRY = 1
//    // - DISCOVER = 1
//    // - USE_DISCOVER_VISUALS = 1
//    // --------------------------------------------------------
//
//    // --------------------------------------- MINION - NEUTRAL
//    // [LOE_038] Naga Sea Witch - COST:8 [ATK:5/HP:5]
//    // - Set: LoE, Rarity: Epic
//    // --------------------------------------------------------
//    // Text: Your cards cost (5).
//    // --------------------------------------------------------
//    // GameTag:
//    // - AURA = 1
//    // --------------------------------------------------------
//
//    // --------------------------------------- MINION - NEUTRAL
//    // [LOE_039] Gorillabot A-3 - COST:3 [ATK:3/HP:4]
//    // - Race: Mechanical, Set: LoE, Rarity: Common
//    // --------------------------------------------------------
//    // Text: <b>Battlecry:</b> If you control another Mech,
//    //       <b>Discover</b> a Mech.
//    // --------------------------------------------------------
//    // GameTag:
//    // - BATTLECRY = 1
//    // - DISCOVER = 1
//    // - USE_DISCOVER_VISUALS = 1
//    // --------------------------------------------------------
//
//    // --------------------------------------- MINION - NEUTRAL
//    // [LOE_046] Huge Toad - COST:2 [ATK:3/HP:2]
//    // - Race: Beast, Set: LoE, Rarity: Common
//    // --------------------------------------------------------
//    // Text: <b>Deathrattle:</b> Deal 1 damage to a random enemy.
//    // --------------------------------------------------------
//    // GameTag:
//    // - DEATHRATTLE = 1
//    // --------------------------------------------------------
//
//    // --------------------------------------- MINION - NEUTRAL
//    // [LOE_047] Tomb Spider - COST:4 [ATK:3/HP:3]
//    // - Race: Beast, Set: LoE, Rarity: Common
//    // --------------------------------------------------------
//    // Text: <b>Battlecry: Discover</b> a Beast.
//    // --------------------------------------------------------
//    // GameTag:
//    // - BATTLECRY = 1
//    // - DISCOVER = 1
//    // - USE_DISCOVER_VISUALS = 1
//    // --------------------------------------------------------
//
//    // --------------------------------------- MINION - NEUTRAL
//    // [LOE_053] Djinni of Zephyrs - COST:5 [ATK:4/HP:6]
//    // - Race: Elemental, Set: LoE, Rarity: Epic
//    // --------------------------------------------------------
//    // Text: After you cast a spell on another friendly minion,
//    //       cast a copy of it on this one.
//    // --------------------------------------------------------
//    // GameTag:
//    // - 1059 = 1
//    // --------------------------------------------------------
//
//    // --------------------------------------- MINION - NEUTRAL
//    // [LOE_061] Anubisath Sentinel - COST:5 [ATK:4/HP:4]
//    // - Set: LoE, Rarity: Common
//    // --------------------------------------------------------
//    // Text: <b>Deathrattle:</b> Give a random friendly minion +3/+3.
//    // --------------------------------------------------------
//    // GameTag:
//    // - DEATHRATTLE = 1
//    // --------------------------------------------------------
//
//    // --------------------------------------- MINION - NEUTRAL
//    // [LOE_073] Fossilized Devilsaur - COST:8 [ATK:8/HP:8]
//    // - Set: LoE, Rarity: Common
//    // --------------------------------------------------------
//    // Text: <b>Battlecry:</b> If you control a Beast,
//    //       gain <b>Taunt</b>.
//    // --------------------------------------------------------
//    // GameTag:
//    // - BATTLECRY = 1
//    // --------------------------------------------------------
//    // RefTag:
//    // - TAUNT = 1
//    // --------------------------------------------------------
//
//    // --------------------------------------- MINION - NEUTRAL
//    // [LOE_076] Sir Finley Mrrgglton - COST:1 [ATK:1/HP:3]
//    // - Race: Murloc, Set: LoE, Rarity: Legendary
//    // --------------------------------------------------------
//    // Text: <b>Battlecry: Discover</b> a new basic Hero Power.
//    // --------------------------------------------------------
//    // Entourage: DS1h_292, CS2_056, CS2_101, CS1h_001, CS2_049,
//    //            CS2_102, CS2_083b, CS2_034, CS2_017
//    // --------------------------------------------------------
//    // GameTag:
//    // - ELITE = 1
//    // - BATTLECRY = 1
//    // - DISCOVER = 1
//    // - USE_DISCOVER_VISUALS = 1
//    // --------------------------------------------------------
//
//    // --------------------------------------- MINION - NEUTRAL
//    // [LOE_077] Brann Bronzebeard - COST:3 [ATK:2/HP:4]
//    // - Set: LoE, Rarity: Legendary
//    // --------------------------------------------------------
//    // Text: Your <b>Battlecries</b> trigger twice.
//    // --------------------------------------------------------
//    // GameTag:
//    // - ELITE = 1
//    // - AURA = 1
//    // - 1429 = 58400
//    // - TECH_LEVEL = 5
//    // - IS_BACON_POOL_MINION = 1
//    // --------------------------------------------------------
//    // RefTag:
//    // - BATTLECRY = 1
//    // --------------------------------------------------------
//
//    // --------------------------------------- MINION - NEUTRAL
//    // [LOE_079] Elise Starseeker - COST:4 [ATK:3/HP:5]
//    // - Set: LoE, Rarity: Legendary
//    // --------------------------------------------------------
//    // Text: <b>Battlecry:</b> Shuffle the
//    //       'Map to the Golden Monkey' into your deck.
//    // --------------------------------------------------------
//    // GameTag:
//    // - ELITE = 1
//    // - BATTLECRY = 1
//    // --------------------------------------------------------
//    // PlayReq:
//    // - REQ_FRIENDLY_TARGET = 0
//    // - REQ_MINION_TARGET = 0
//    // --------------------------------------------------------
//
//    // --------------------------------------- MINION - NEUTRAL
//    // [LOE_086] Summoning Stone - COST:5 [ATK:0/HP:6]
//    // - Set: LoE, Rarity: Rare
//    // --------------------------------------------------------
//    // Text: Whenever you cast a spell,
//    //       summon a random minion of the same Cost.
//    // --------------------------------------------------------
//
//    // --------------------------------------- MINION - NEUTRAL
//    // [LOE_089] Wobbling Runts - COST:6 [ATK:2/HP:6]
//    // - Set: LoE, Rarity: Rare
//    // --------------------------------------------------------
//    // Text: <b>Deathrattle:</b> Summon three 2/2 Runts.
//    // --------------------------------------------------------
//    // GameTag:
//    // - DEATHRATTLE = 1
//    // --------------------------------------------------------
//
//    // --------------------------------------- MINION - NEUTRAL
//    // [LOE_092] Arch-Thief Rafaam - COST:9 [ATK:7/HP:8]
//    // - Set: LoE, Rarity: Legendary
//    // --------------------------------------------------------
//    // Text: <b>Battlecry: Discover</b> a powerful Artifact.
//    // --------------------------------------------------------
//    // GameTag:
//    // - ELITE = 1
//    // - BATTLECRY = 1
//    // - DISCOVER = 1
//    // - USE_DISCOVER_VISUALS = 1
//    // --------------------------------------------------------
//
//    // --------------------------------------- MINION - NEUTRAL
//    // [LOE_107] Eerie Statue - COST:4 [ATK:7/HP:7]
//    // - Set: LoE, Rarity: Rare
//    // --------------------------------------------------------
//    // Text: Can't attack unless it's the only minion
//    //       in the battlefield.
//    // --------------------------------------------------------
//
//    // --------------------------------------- MINION - NEUTRAL
//    // [LOE_110] Ancient Shade - COST:4 [ATK:7/HP:4]
//    // - Set: LoE, Rarity: Rare
//    // --------------------------------------------------------
//    // Text: <b>Battlecry:</b> Shuffle an 'Ancient Curse'
//    //       into your deck that deals 7 damage to you when drawn.
//    // --------------------------------------------------------
//    // GameTag:
//    // - BATTLECRY = 1
//    // --------------------------------------------------------
//
//	// --------------------------------------- MINION - NEUTRAL
//	// [LOEA10_3] Murloc Tinyfin - COST:0 [ATK:1/HP:1] 
//	// - Race: Murloc, Set: LoE, Rarity: Common
//	// --------------------------------------------------------
//    cardDef.ClearData();
//    cardDef.power.AddPowerTask(nullptr);
//    cards.emplace("LOEA10_3", CardDef(power));
//}
//
//void LoECardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
//{
//    // ---------------------------------------- SPELL - NEUTRAL
//    // [LOE_008] Eye of Hakkar (*) - COST:1
//    // - Set: LoE
//    // --------------------------------------------------------
//    // Text: Take a secret from your opponent's deck and
//    //       put it into the battlefield.
//    // --------------------------------------------------------
//    // PlayReq:
//    // - REQ_MINION_TARGET = 0
//    // --------------------------------------------------------
//
//    // ---------------------------------------- SPELL - NEUTRAL
//    // [LOE_008H] Eye of Hakkar (*) - COST:1
//    // - Set: LoE
//    // --------------------------------------------------------
//    // Text: Take a secret from your opponent's deck and
//    //       put it into the battlefield.
//    // --------------------------------------------------------
//
//    // --------------------------------------- MINION - NEUTRAL
//    // [LOE_016t] Rock (*) - COST:1 [ATK:0/HP:6]
//    // - Set: LoE
//    // --------------------------------------------------------
//    // Text: <b>Taunt</b>
//    // --------------------------------------------------------
//    // GameTag:
//    // - TAUNT = 1
//    // --------------------------------------------------------
//
//    // ---------------------------------------- SPELL - NEUTRAL
//    // [LOE_019t] Map to the Golden Monkey (*) - COST:2
//    // - Set: LoE
//    // --------------------------------------------------------
//    // Text: Shuffle the Golden Monkey into your deck. Draw a card.
//    // --------------------------------------------------------
//
//    // --------------------------------------- MINION - NEUTRAL
//    // [LOE_019t2] Golden Monkey (*) - COST:4 [ATK:6/HP:6]
//    // - Set: LoE
//    // --------------------------------------------------------
//    // Text: <b>Taunt</b>
//    //       <b>Battlecry:</b> Replace your hand and deck
//    //       with <b>Legendary</b> minions.
//    // --------------------------------------------------------
//    // GameTag:
//    // - TAUNT = 1
//    // - BATTLECRY = 1
//    // --------------------------------------------------------
//
//    // --------------------------------------- MINION - NEUTRAL
//    // [LOE_024t] Rolling Boulder (*) - COST:4 [ATK:0/HP:4]
//    // - Set: LoE
//    // --------------------------------------------------------
//    // Text: At the end of your turn, destroy the minion to the left.
//    // --------------------------------------------------------
//
//    // ---------------------------------- ENCHANTMENT - NEUTRAL
//    // [LOE_030e] Hollow (*) - COST:0
//    // - Set: LoE
//    // --------------------------------------------------------
//    // Text: Stats copied.
//    // --------------------------------------------------------
//
//    // ---------------------------------- ENCHANTMENT - NEUTRAL
//    // [LOE_038e] Seawitching (*) - COST:0
//    // - Set: LoE
//    // --------------------------------------------------------
//    // Text: Costs (5).
//    // --------------------------------------------------------
//
//    // ---------------------------------- ENCHANTMENT - NEUTRAL
//    // [LOE_061e] Power of the Titans (*) - COST:0
//    // - Set: LoE
//    // --------------------------------------------------------
//    // Text: +3/+3.
//    // --------------------------------------------------------
//
//    // ---------------------------------- ENCHANTMENT - NEUTRAL
//    // [LOE_073e] Fossilized (*) - COST:0
//    // - Set: LoE
//    // --------------------------------------------------------
//    // Text: Has <b>Taunt</b>.
//    // --------------------------------------------------------
//
//    // ---------------------------------- ENCHANTMENT - NEUTRAL
//    // [LOE_077e] Bronzebeard Battlecry (*) - COST:0
//    // - Set: LoE
//    // --------------------------------------------------------
//    // Text: Your <b>Battlecries</b> trigger twice.
//    // --------------------------------------------------------
//
//    // --------------------------------------- MINION - NEUTRAL
//    // [LOE_089t] Rascally Runt (*) - COST:2 [ATK:2/HP:2]
//    // - Set: LoE
//    // --------------------------------------------------------
//
//    // --------------------------------------- MINION - NEUTRAL
//    // [LOE_089t2] Wily Runt (*) - COST:2 [ATK:2/HP:2]
//    // - Set: LoE
//    // --------------------------------------------------------
//
//    // --------------------------------------- MINION - NEUTRAL
//    // [LOE_089t3] Grumbly Runt (*) - COST:2 [ATK:2/HP:2]
//    // - Set: LoE
//    // --------------------------------------------------------
//
//    // ---------------------------------------- SPELL - NEUTRAL
//    // [LOE_110t] Ancient Curse (*) - COST:4
//    // - Set: LoE
//    // --------------------------------------------------------
//    // Text: <b>Casts When Drawn</b>
//    //       You take 7 damage.
//    // --------------------------------------------------------
//    // GameTag:
//    // - ImmuneToSpellpower = 1
//    // - TOPDECK = 1
//    // --------------------------------------------------------
//    // RefTag:
//    // - CASTSWHENDRAWN = 1
//    // --------------------------------------------------------
//
//    // ---------------------------------- ENCHANTMENT - NEUTRAL
//    // [LOE_113e] Mrglllraawrrrglrur! (*) - COST:0
//    // - Set: LoE
//    // --------------------------------------------------------
//    // Text: +2/+2.
//    // --------------------------------------------------------
//}
//
//void LoECardsGen::AddAll(std::map<std::string, CardDef>& cards)
//{
//    AddHeroes(cards);
//    AddHeroPowers(cards);
//
//    AddDruid(cards);
//    AddDruidNonCollect(cards);
//
//    AddHunter(cards);
//    AddHunterNonCollect(cards);
//
//    AddMage(cards);
//    AddMageNonCollect(cards);
//
//    AddPaladin(cards);
//    AddPaladinNonCollect(cards);
//
//    AddPriest(cards);
//    AddPriestNonCollect(cards);
//
//    AddRogue(cards);
//    AddRogueNonCollect(cards);
//
//    AddShaman(cards);
//    AddShamanNonCollect(cards);
//
//    AddWarlock(cards);
//    AddWarlockNonCollect(cards);
//
//    AddWarrior(cards);
//    AddWarriorNonCollect(cards);
//
//    AddNeutral(cards);
//    AddNeutralNonCollect(cards);
//}
//}  // namespace RosettaStone::PlayMode