// This code is based on Sabberstone project.
// Copyright (c) 2017-2021 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2021 Chris Ohk

#include <Rosetta/PlayMode/CardSets/KaraCardsGen.hpp>
#include <Rosetta/PlayMode/Enchants/Effects.hpp>
#include <Rosetta/PlayMode/Enchants/OngoingEnchant.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks.hpp>

using namespace RosettaStone::PlayMode::SimpleTasks;

namespace RosettaStone::PlayMode
{
using PlayReqs = std::map<PlayReq, int>;
using EffectList = std::vector<std::shared_ptr<IEffect>>;

void KaraCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void KaraCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void KaraCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - DRUID
    // [KAR_065] Menagerie Warden - COST:5 [ATK:4/HP:4]
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a friendly Beast.
    //       Summon a copy of it.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_WITH_RACE = 20
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonCopyTask>(EntityType::TARGET));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_TARGET_IF_AVAILABLE, 0 },
                  { PlayReq::REQ_FRIENDLY_TARGET, 0 },
                  { PlayReq::REQ_MINION_TARGET, 0 },
                  { PlayReq::REQ_TARGET_WITH_RACE, 20 } };
    cards.emplace("KAR_065", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [KAR_075] Moonglade Portal - COST:6
    // - Set: Kara, Rarity: Rare
    // --------------------------------------------------------
    // Text: Restore 6 Health. Summon a random 6-Cost minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [KAR_300] Enchanted Raven - COST:1 [ATK:2/HP:2]
    // - Race: Beast, Set: Kara, Rarity: Common
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("KAR_300", cardDef);
}

void KaraCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void KaraCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- SPELL - HUNTER
    // [KAR_004] Cat Trick - COST:2
    // - Set: Kara, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After your opponent casts a spell,
    //       summon a 4/2 Panther with <b>Stealth</b>.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [KAR_005] Kindly Grandmother - COST:2 [ATK:1/HP:1]
    // - Race: Beast, Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 3/2 Big Bad Wolf.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [KAR_006] Cloaked Huntress - COST:3 [ATK:3/HP:4]
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: Your <b>Secrets</b> cost (0).
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
}

void KaraCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- MINION - HUNTER
    // [KAR_004a] Cat in a Hat (*) - COST:3 [ATK:4/HP:2]
    // - Race: Beast, Faction: Horde, Set: Kara
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [KAR_005a] Big Bad Wolf (*) - COST:2 [ATK:3/HP:2]
    // - Race: Beast, Set: Kara
    // --------------------------------------------------------
}

void KaraCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ MINION - MAGE
    // [KAR_009] Babbling Book - COST:1 [ATK:1/HP:1]
    // - Set: Kara, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a random Mage spell to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomCardTask>(CardType::SPELL, CardClass::MAGE));
    cardDef.power.AddPowerTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cards.emplace("KAR_009", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [KAR_076] Firelands Portal - COST:7
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 5 damage. Summon a random 5-Cost minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [KAR_092] Medivh's Valet - COST:2 [ATK:2/HP:3]
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a <b>Secret</b>,
    //       deal 3 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_FRIENDLY_SECRETS = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
}

void KaraCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void KaraCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - PALADIN
    // [KAR_010] Nightbane Templar - COST:3 [ATK:2/HP:3]
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       summon two 1/1 Whelps.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [KAR_057] Ivory Knight - COST:6 [ATK:4/HP:4]
    // - Set: Kara, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a spell.
    //       Restore Health to your hero equal to its Cost.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [KAR_077] Silvermoon Portal - COST:4
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion +2/+2.
    //       Summon a random 2-Cost minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
}

void KaraCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - PALADIN
    // [KAR_010a] Whelp (*) - COST:1 [ATK:1/HP:1]
    // - Race: Dragon, Set: Kara
    // --------------------------------------------------------
}

void KaraCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- SPELL - PRIEST
    // [KAR_013] Purify - COST:2
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Silence</b> a friendly minion. Draw a card.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - SILENCE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [KAR_035] Priest of the Feast - COST:4 [ATK:3/HP:6]
    // - Faction: Neutral, Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever you cast a spell,
    //       restore 3 Health to your hero.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [KAR_204] Onyx Bishop - COST:5 [ATK:3/HP:4]
    // - Set: Kara, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a friendly minion
    //       that died this game.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void KaraCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void KaraCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - ROGUE
    // [KAR_069] Swashburglar - COST:1 [ATK:1/HP:1]
    // - Race: Pirate, Faction: Neutral, Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a random card
    //       from another class to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<RandomCardTask>(EntityType::ENEMY_HERO));
    cardDef.power.AddPowerTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cards.emplace("KAR_069", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [KAR_070] Ethereal Peddler - COST:5 [ATK:5/HP:6]
    // - Set: Kara, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding any non-Rogue
    //       class cards, reduce their Cost by (2).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [KAR_094] Deadly Fork - COST:3 [ATK:3/HP:2]
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a 3/2 weapon to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
}

void KaraCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- WEAPON - ROGUE
    // [KAR_094a] Sharp Fork (*) - COST:3 [ATK:3/HP:0]
    // - Set: Kara
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // --------------------------------------------------------
}

void KaraCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- MINION - SHAMAN
    // [KAR_021] Wicked Witchdoctor - COST:4 [ATK:3/HP:4]
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever you cast a spell, summon a random basic Totem.
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - SHAMAN
    // [KAR_063] Spirit Claws - COST:2 [ATK:1/HP:0]
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: Has +2 Attack while you have <b>Spell Damage</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 3
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [KAR_073] Maelstrom Portal - COST:2
    // - Set: Kara, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 1 damage to all enemy minions.
    //       Summon a random 1-Cost minion.
    // --------------------------------------------------------
}

void KaraCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void KaraCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- SPELL - WARLOCK
    // [KAR_025] Kara Kazham! - COST:5
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: Summon a 1/1 Candle, 2/2 Broom, and 3/3 Teapot.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [KAR_089] Malchezaar's Imp - COST:1 [ATK:1/HP:3]
    // - Race: Demon, Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever you discard a card, draw a card.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [KAR_205] Silverware Golem - COST:3 [ATK:3/HP:3]
    // - Set: Kara, Rarity: Rare
    // --------------------------------------------------------
    // Text: If you discard this minion, summon it.
    // --------------------------------------------------------
    // GameTag:
    // - InvisibleDeathrattle = 1
    // --------------------------------------------------------
}

void KaraCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - WARLOCK
    // [KAR_025a] Candle (*) - COST:1 [ATK:1/HP:1]
    // - Set: Kara
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [KAR_025b] Broom (*) - COST:2 [ATK:2/HP:2]
    // - Set: Kara
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [KAR_025c] Teapot (*) - COST:3 [ATK:3/HP:3]
    // - Set: Kara
    // --------------------------------------------------------
}

void KaraCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- SPELL - WARRIOR
    // [KAR_026] Protect the King! - COST:3
    // - Set: Kara, Rarity: Rare
    // --------------------------------------------------------
    // Text: For each enemy minion,
    //       summon a 1/1 Pawn with <b>Taunt</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_ENEMY_MINIONS = 1
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [KAR_028] Fool's Bane - COST:5 [ATK:3/HP:0]
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: Unlimited attacks each turn. Can't attack heroes.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 4
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [KAR_091] Ironforge Portal - COST:5
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: Gain 4 Armor. Summon a random 4-Cost minion.
    // --------------------------------------------------------
}

void KaraCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - WARRIOR
    // [KAR_026t] Pawn (*) - COST:1 [ATK:1/HP:1]
    // - Set: Kara
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
}

void KaraCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_011] Pompous Thespian - COST:2 [ATK:3/HP:2]
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_029] Runic Egg - COST:1 [ATK:0/HP:2]
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_030a] Pantry Spider - COST:3 [ATK:1/HP:3]
    // - Race: Beast, Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 1/3 Spider.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_033] Book Wyrm - COST:6 [ATK:3/HP:6]
    // - Race: Dragon, Set: Kara, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       destroy an enemy minion with 3 or less Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NONSELF_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_MAX_ATTACK = 3
    // - REQ_TARGET_IF_AVAILABLE_AND_DRAGON_IN_HAND = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_036] Arcane Anomaly - COST:1 [ATK:2/HP:1]
    // - Race: Elemental, Faction: Neutral, Set: Kara, Rarity: common
    // --------------------------------------------------------
    // Text: Whenever you cast a spell,
    //       give this minion +1 Health.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "KAR_036e", EntityType::SOURCE) };
    cards.emplace("KAR_036", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_037] Avian Watcher - COST:5 [ATK:3/HP:6]
    // - Set: Kara, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a <b>Secret</b>,
    //       gain +1/+1 and <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // - SECRET = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_041] Moat Lurker - COST:6 [ATK:3/HP:3]
    // - Set: Kara, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Destroy a minion.
    //       <b>Deathrattle:</b> Resummon it.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_044] Moroes - COST:3 [ATK:1/HP:1]
    // - Set: Kara, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //       At the end of your turn, summon a 1/1 Steward.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - STEALTH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_061] The Curator - COST:7 [ATK:4/HP:6]
    // - Race: Mechanical, Set: Kara, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Taunt</b> <b>Battlecry:</b> Draw a Beast,
    //       Dragon, and Murloc from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_062] Netherspite Historian - COST:2 [ATK:1/HP:3]
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       <b>Discover</b> a Dragon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DISCOVER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_095] Zoobot - COST:3 [ATK:3/HP:3]
    // - Race: Mechanical, Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a random friendly Beast,
    //       Dragon, and Murloc +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_096] Prince Malchezaar - COST:5 [ATK:5/HP:6]
    // - Race: Demon, Set: Kara, Rarity: Legendary
    // --------------------------------------------------------
    // Text: When the game starts,
    //       add 5 extra <b>Legendary</b> minions to your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_097] Medivh, the Guardian - COST:8 [ATK:7/HP:7]
    // - Set: Kara, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Equip Atiesh, Greatstaff of the Guardian.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_114] Barnes - COST:4 [ATK:3/HP:4]
    // - Set: Kara, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 1/1 copy of
    //       a random minion in your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_702] Menagerie Magician - COST:5 [ATK:4/HP:4]
    // - Faction: Neutral, Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a random friendly Beast,
    //       Dragon, and Murloc +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_710] Arcanosmith - COST:4 [ATK:3/HP:2]
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 0/5 minion with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_711] Arcane Giant - COST:12 [ATK:8/HP:8]
    // - Set: Kara, Rarity: Epic
    // --------------------------------------------------------
    // Text: Costs (1) less for each spell you've cast this game.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_712] Violet Illusionist - COST:3 [ATK:4/HP:3]
    // - Set: Kara, Rarity: Common
    // --------------------------------------------------------
    // Text: During your turn, your hero is <b>Immune</b>.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------
}

void KaraCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_030] Cellar Spider (*) - COST:3 [ATK:1/HP:3]
    // - Race: Beast, Set: Kara
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [KAR_036e] Eating (*) - COST:0
    // - Set: Kara
    // --------------------------------------------------------
    // Text: Increased Health.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_shared<OngoingEnchant>(EffectList{ Effects::HealthN(1) }));
    cards.emplace("KAR_036e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [KAR_037t] Secrets of Karazhan (*) - COST:0
    // - Set: Kara
    // --------------------------------------------------------
    // Text: +1/+1 and <b>Taunt</b>.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [KAR_041e] Moat Lurker (*) - COST:0
    // - Set: Kara
    // --------------------------------------------------------
    // Text: Destroyed {0}.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_044a] Steward (*) - COST:1 [ATK:1/HP:1]
    // - Faction: neutral, Set: Kara
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [KAR_077e] Silver Might (*) - COST:0
    // - Set: Kara
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [KAR_095e] Well Fed (*) - COST:0
    // - Set: Kara
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - NEUTRAL
    // [KAR_097t] Atiesh (*) - COST:3 [ATK:1/HP:0]
    // - Set: Kara
    // --------------------------------------------------------
    // Text: After you cast a spell,
    //       summon a random minion of that Cost.
    //       Lose 1 Durability.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DURABILITY = 3
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [KAR_114e] Incredible Impression (*) - COST:0
    // - Set: Kara
    // --------------------------------------------------------
    // Text: Attack and Health set to 1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [KAR_702e] A Simple Trick (*) - COST:0
    // - Set: Kara
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [KAR_710m] Animated Shield (*) - COST:2 [ATK:0/HP:5]
    // - Set: Kara
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------
}

void KaraCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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