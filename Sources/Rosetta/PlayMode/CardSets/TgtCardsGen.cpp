// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/CardSets/TgtCardsGen.hpp>
#include <Rosetta/PlayMode/Cards/CardPowers.hpp>

namespace RosettaStone::PlayMode
{
void TgtCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void TgtCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------ HERO_POWER - SHAMAN
    // [AT_050t] Lightning Jolt (*) - COST:2
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Deal 2 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ------------------------------------- HERO_POWER - DRUID
    // [AT_132_DRUID] Dire Shapeshift (*) - COST:2
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Gain 2 Armor and +2 Attack this turn.
    // --------------------------------------------------------

    // ------------------------------------ HERO_POWER - HUNTER
    // [AT_132_HUNTER] Ballista Shot (*) - COST:2
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Deal 3 damage to the enemy hero.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_STEADY_SHOT = 0
    // - REQ_MINION_OR_ENEMY_HERO = 0
    // --------------------------------------------------------

    // -------------------------------------- HERO_POWER - MAGE
    // [AT_132_MAGE] Fireblast Rank 2 (*) - COST:2
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Deal 2 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ----------------------------------- HERO_POWER - PALADIN
    // [AT_132_PALADIN] The Silver Hand (*) - COST:2
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Summon two 1/1 Recruits.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------

    // ------------------------------------ HERO_POWER - PRIEST
    // [AT_132_PRIEST] Heal (*) - COST:2
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Restore 4 Health.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ------------------------------------- HERO_POWER - ROGUE
    // [AT_132_ROGUE] Poisoned Daggers (*) - COST:2
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Equip a 2/2 Weapon.
    // --------------------------------------------------------

    // ------------------------------------ HERO_POWER - SHAMAN
    // [AT_132_SHAMAN] Totemic Slam (*) - COST:2
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Summon a Totem of your choice.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------

    // ----------------------------------- HERO_POWER - WARLOCK
    // [AT_132_WARLOCK] Soul Tap (*) - COST:2
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Draw a card.
    // --------------------------------------------------------

    // ----------------------------------- HERO_POWER - WARRIOR
    // [AT_132_WARRIOR] Tank Up! (*) - COST:2
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: <b>Hero Power</b>
    //       Gain 4 Armor.
    // --------------------------------------------------------
}

void TgtCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ SPELL - DRUID
    // [AT_037] Living Roots - COST:1
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Deal 2 damage;
    //       or Summon two 1/1 Saplings.
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
    cardDef.property.chooseCardIDs = ChooseCardIDs{ "AT_037a", "AT_037b" };
    cards.emplace("AT_037", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [AT_038] Darnassus Aspirant - COST:2 [ATK:2/HP:3]
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain an empty Mana Crystal.
    //       <b>Deathrattle:</b> Lose a Mana Crystal.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [AT_039] Savage Combatant - COST:4 [ATK:5/HP:4]
    // - Race: Beast, Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Inspire:</b> Give your hero +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - INSPIRE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [AT_040] Wildwalker - COST:4 [ATK:4/HP:4]
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly Beast +3 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_WITH_RACE = 20
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [AT_041] Knight of the Wild - COST:7 [ATK:6/HP:6]
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you summon a Beast,
    //       reduce the Cost of this card by (1).
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [AT_042] Druid of the Saber - COST:2 [ATK:2/HP:1]
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Transform into a 2/1 with
    //       <b>Charge</b>; or a 3/2 with <b>Stealth</b>.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // - CHARGE = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [AT_043] Astral Communion - COST:4
    // - Set: Tgt, Rarity: Epic
    // --------------------------------------------------------
    // Text: Gain 10 Mana Crystals. Discard your hand.
    // --------------------------------------------------------
    // GameTag:
    // - 890 = 10
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [AT_044] Mulch - COST:3
    // - Set: Tgt, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy a minion.
    //       Add a random minion to your opponent's hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [AT_045] Aviana - COST:9 [ATK:5/HP:5]
    // - Set: Tgt, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Your minions cost (1).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AURA = 1
    // --------------------------------------------------------
}

void TgtCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------ SPELL - DRUID
    // [AT_037a] Living Roots (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: Deal 2 damage.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 2, true));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("AT_037a", cardDef);

    // ------------------------------------------ SPELL - DRUID
    // [AT_037b] Living Roots (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: Summon two 1/1 Saplings.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<SummonTask>("AT_037t", 2, SummonSide::SPELL));
    cardDef.property.playReqs =
        PlayReqs{ { PlayReq::REQ_NUM_MINION_SLOTS, 1 } };
    cards.emplace("AT_037b", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [AT_037t] Sapling (*) - COST:1 [ATK:1/HP:1]
    // - Set: Tgt
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("AT_037t", cardDef);

    // ------------------------------------ ENCHANTMENT - DRUID
    // [AT_039e] Savage (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [AT_040e] Kindred Spirit (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: +3 Health.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [AT_042a] Lion Form (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [AT_042b] Panther Form (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: +1/+1 and <b>Stealth</b>.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [AT_042t] Sabertooth Lion (*) - COST:2 [ATK:2/HP:1]
    // - Race: Beast, Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [AT_042t2] Sabertooth Panther (*) - COST:2 [ATK:3/HP:2]
    // - Race: Beast, Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - DRUID
    // [AT_132_DRUIDe] Dire Claws (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: +2 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("AT_132_DRUIDe"));
    cards.emplace("AT_132_DRUIDe", cardDef);

    // ----------------------------------------- MINION - DRUID
    // [OG_044c] Sabertooth Tiger (*) - COST:2 [ATK:3/HP:2]
    // - Race: Beast, Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Charge, Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // - CHARGE = 1
    // --------------------------------------------------------
}

void TgtCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - HUNTER
    // [AT_010] Ram Wrangler - COST:5 [ATK:3/HP:3]
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you have a Beast,
    //       summon a random Beast.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [AT_056] Powershot - COST:3
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal 2 damage to a minion and the minions next to it.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [AT_057] Stablemaster - COST:3 [ATK:4/HP:2]
    // - Set: Tgt, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly Beast
    //       <b>Immune</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_TARGET_WITH_RACE = 20
    // --------------------------------------------------------
    // RefTag:
    // - IMMUNE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [AT_058] King's Elekk - COST:2 [ATK:3/HP:2]
    // - Race: Beast, Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Reveal a minion in each deck.
    //       If yours costs more, draw it.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [AT_059] Brave Archer - COST:1 [ATK:2/HP:1]
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Inspire:</b> If your hand is empty,
    //       deal 2 damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - INSPIRE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [AT_060] Bear Trap - COST:2
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After your hero is attacked,
    //       summon a 3/3 Bear with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [AT_061] Lock and Load - COST:2
    // - Set: Tgt, Rarity: Epic
    // --------------------------------------------------------
    // Text: Each time you cast a spell this turn,
    //       add a random Hunter card to your hand.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<AddEnchantmentTask>("AT_061e", EntityType::PLAYER));
    cards.emplace("AT_061", cardDef);

    // ----------------------------------------- SPELL - HUNTER
    // [AT_062] Ball of Spiders - COST:6
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: Summon three 1/1 Webspinners.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_NUM_MINION_SLOTS = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [AT_063] Acidmaw - COST:7 [ATK:4/HP:2]
    // - Race: Beast, Set: Tgt, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever another minion takes damage, destroy it.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [AT_063t] Dreadscale - COST:3 [ATK:4/HP:2]
    // - Race: Beast, Set: Tgt, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       deal 1 damage to all other minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
}

void TgtCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [AT_057o] Groomed (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: <b>Immune</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [AT_061e] Lock and Load (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::CAST_SPELL));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomCardTask>(CardType::INVALID, CardClass::HUNTER),
        std::make_shared<AddStackToTask>(EntityType::HAND)
    };
    cards.emplace("AT_061e", cardDef);
}

void TgtCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------------- SPELL - MAGE
    // [AT_001] Flame Lance - COST:5
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 8 damage to a minion.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [AT_002] Effigy - COST:3
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When a friendly minion dies,
    //       summon a random minion with the same Cost.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [AT_003] Fallen Hero - COST:2 [ATK:3/HP:2]
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: Your Hero Power deals 1 extra damage.
    // --------------------------------------------------------
    // GameTag:
    // - HEROPOWER_DAMAGE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(std::make_shared<Aura>(
        AuraType::HERO,
        EffectList{ std::make_shared<Effect>(GameTag::HEROPOWER_DAMAGE,
                                             EffectOperator::ADD, 1) }));
    cards.emplace("AT_003", cardDef);

    // ------------------------------------------- SPELL - MAGE
    // [AT_004] Arcane Blast - COST:1
    // - Set: Tgt, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 2 damage to a minion.
    //       This spell gets double bonus from <b>Spell Damage</b>.
    // --------------------------------------------------------
    // GameTag:
    // - RECEIVES_DOUBLE_SPELLDAMAGE_BONUS = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [AT_005] Polymorph: Boar - COST:3
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: Transform a minion into a 4/2 Boar with <b>Charge</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [AT_006] Dalaran Aspirant - COST:4 [ATK:3/HP:5]
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Inspire:</b> Gain <b>Spell Damage +1</b>.
    // --------------------------------------------------------
    // GameTag:
    // - INSPIRE = 1
    // --------------------------------------------------------
    // RefTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [AT_007] Spellslinger - COST:3 [ATK:3/HP:4]
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a random spell to
    //       each player's hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [AT_008] Coldarra Drake - COST:6 [ATK:6/HP:6]
    // - Race: Dragon, Set: Tgt, Rarity: Epic
    // --------------------------------------------------------
    // Text: You can use your Hero Power any number of times.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::INSPIRE));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<SetGameTagTask>(
        EntityType::HERO_POWER, GameTag::EXHAUSTED, 0) };
    cards.emplace("AT_008", cardDef);

    // ------------------------------------------ MINION - MAGE
    // [AT_009] Rhonin - COST:8 [ATK:7/HP:7]
    // - Set: Tgt, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add 3 copies of Arcane Missiles
    //       to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
}

void TgtCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------- ENCHANTMENT - MAGE
    // [AT_006e] Power of Dalaran (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: Increased Spell Damage.
    // --------------------------------------------------------
}

void TgtCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - PALADIN
    // [AT_073] Competitive Spirit - COST:1
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When your turn starts,
    //       give your minions +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [AT_074] Seal of Champions - COST:3
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a minion +3 Attack and <b>Divine Shield</b>.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [AT_075] Warhorse Trainer - COST:3 [ATK:2/HP:4]
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: Your Silver Hand Recruits have +2 Attack and <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddAura(
        std::make_shared<Aura>(AuraType::FIELD_EXCEPT_SOURCE, "AT_075e"));
    {
        const auto aura = dynamic_cast<Aura*>(cardDef.power.GetAura());
        aura->condition = std::make_shared<SelfCondition>(
            SelfCondition::IsSilverHandRecruit());
    }
    cards.emplace("AT_075", cardDef);

    // --------------------------------------- MINION - PALADIN
    // [AT_076] Murloc Knight - COST:4 [ATK:3/HP:4]
    // - Race: Murloc, Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Inspire:</b> Summon a random Murloc.
    // --------------------------------------------------------
    // GameTag:
    // - INSPIRE = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - PALADIN
    // [AT_077] Argent Lance - COST:2 [ATK:2/HP:0]
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Reveal a minion in each deck.
    //       If yours costs more, +1 Durability.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [AT_078] Enter the Coliseum - COST:6
    // - Set: Tgt, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy all minions except each player's
    //       highest Attack minion.
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [AT_079] Mysterious Challenger - COST:6 [ATK:6/HP:6]
    // - Set: Tgt, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Put one of each <b>Secret</b>
    //       from your deck into the battlefield.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [AT_081] Eadric the Pure - COST:7 [ATK:3/HP:7]
    // - Set: Tgt, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Change all enemy minions' Attack to 1.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [AT_104] Tuskarr Jouster - COST:5 [ATK:5/HP:5]
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Reveal a minion in each deck.
    //       If yours costs more, restore 7 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void TgtCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [AT_074e2] Seal of Champions (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: +3 Attack and <b>Divine Shield</b>.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [AT_075e] Might of the Hostler (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: Warhorse Trainer is granting +2 Attack and <b>Taunt</b>.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("AT_075e"));
    cards.emplace("AT_075e", cardDef);

    // ---------------------------------- ENCHANTMENT - PALADIN
    // [AT_081e] Purified (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: Attack changed to 1.
    // --------------------------------------------------------
}

void TgtCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - PRIEST
    // [AT_011] Holy Champion - COST:4 [ATK:3/HP:5]
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever a character is healed, gain +2 Attack.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [AT_012] Spawn of Shadows - COST:4 [ATK:5/HP:4]
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Inspire:</b> Deal 4 damage to each hero.
    // --------------------------------------------------------
    // GameTag:
    // - INSPIRE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [AT_013] Power Word: Glory - COST:1
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: Choose a minion. Whenever it attacks,
    //       restore 4 Health to your hero.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [AT_014] Shadowfiend - COST:3 [ATK:3/HP:3]
    // - Set: Tgt, Rarity: Epic
    // --------------------------------------------------------
    // Text: Whenever you draw a card, reduce its Cost by (1).
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [AT_015] Convert - COST:2
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: Put a copy of an enemy minion into your hand.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_ENEMY_TARGET = 0
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [AT_016] Confuse - COST:2
    // - Set: Tgt, Rarity: Epic
    // --------------------------------------------------------
    // Text: Swap the Attack and Health of all minions.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [AT_018] Confessor Paletress - COST:7 [ATK:5/HP:4]
    // - Set: Tgt, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Inspire:</b> Summon a random <b>Legendary</b> minion.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - INSPIRE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [AT_055] Flash Heal - COST:1
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: Restore 5 Health.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<HealTask>(EntityType::TARGET, 5));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("AT_055", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [AT_116] Wyrmrest Agent - COST:2 [ATK:1/HP:4]
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       gain +1 Attack and <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
}

void TgtCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- ENCHANTMENT - PRIEST
    // [AT_014e] Shadowfiended (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: Costs (1) less.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [AT_016e] Confused (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: Swapped Attack and Health.
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [AT_116e] Bring it on! (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: +1 Attack and <b>Taunt</b>.
    // --------------------------------------------------------
}

void TgtCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------------- MINION - ROGUE
    // [AT_028] Shado-Pan Rider - COST:5 [ATK:3/HP:7]
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Gain +3 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [AT_029] Buccaneer - COST:1 [ATK:2/HP:1]
    // - Race: Pirate, Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever you equip a weapon, give it +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(
        std::make_shared<Trigger>(TriggerType::EQUIP_WEAPON));
    cardDef.power.GetTrigger()->triggerSource = TriggerSource::FRIENDLY;
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "AT_029e", EntityType::WEAPON) };
    cards.emplace("AT_029", cardDef);

    // ----------------------------------------- MINION - ROGUE
    // [AT_030] Undercity Valiant - COST:2 [ATK:3/HP:2]
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Deal 1 damage.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_FOR_COMBO = 0
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [AT_031] Cutpurse - COST:2 [ATK:2/HP:2]
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever this minion attacks a hero,
    //       add the Coin to your hand.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [AT_032] Shady Dealer - COST:3 [ATK:4/HP:3]
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you have a Pirate, gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [AT_033] Burgle - COST:3
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: Add 2 random cards to your hand
    //       <i>(from your opponent's class)</i>.
    // --------------------------------------------------------

    // ----------------------------------------- WEAPON - ROGUE
    // [AT_034] Poisoned Blade - COST:4 [ATK:1/HP:0]
    // - Set: Tgt, Rarity: Epic
    // --------------------------------------------------------
    // Text: Your Hero Power gives this weapon +1 Attack
    //       instead of replacing it.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 3
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [AT_035] Beneath the Grounds - COST:3
    // - Set: Tgt, Rarity: Epic
    // --------------------------------------------------------
    // Text: Shuffle 3 Ambushes into your opponent's deck.
    //       When drawn, you summon a 4/4 Nerubian.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [AT_036] Anub'arak - COST:9 [ATK:8/HP:4]
    // - Set: Tgt, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Return this to your hand
    //       and summon a 4/4 Nerubian.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - 542 = 1
    // --------------------------------------------------------
}

void TgtCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [AT_032e] Shady Deals (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [AT_034e] Laced (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [AT_035t] Nerubian Ambush! (*) - COST:3
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: Summon a 4/4 Nerubian for your opponent.
    //       Draw a card. Cast this when drawn.
    // --------------------------------------------------------
    // GameTag:
    // - TOPDECK = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [AT_036t] Nerubian (*) - COST:4 [ATK:4/HP:4]
    // - Set: Tgt
    // --------------------------------------------------------

    // ----------------------------------------- WEAPON - ROGUE
    // [AT_132_ROGUEt] Poisoned Dagger (*) - COST:1 [ATK:2/HP:0]
    // - Set: Tgt
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("AT_132_ROGUEt", cardDef);
}

void TgtCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - SHAMAN
    // [AT_046] Tuskarr Totemic - COST:3 [ATK:3/HP:2]
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a random basic Totem.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [AT_047] Draenei Totemcarver - COST:4 [ATK:4/HP:5]
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Gain +1/+1 for each friendly Totem.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<IncludeTask>(EntityType::MINIONS));
    cardDef.power.AddPowerTask(std::make_shared<FilterStackTask>(SelfCondList{
        std::make_shared<SelfCondition>(SelfCondition::IsRace(Race::TOTEM)) }));
    cardDef.power.AddPowerTask(std::make_shared<CountTask>(EntityType::STACK));
    cardDef.power.AddPowerTask(std::make_shared<AddEnchantmentTask>(
        "AT_047e", EntityType::SOURCE, true));
    cards.emplace("AT_047", cardDef);

    // ----------------------------------------- SPELL - SHAMAN
    // [AT_048] Healing Wave - COST:3
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: Restore 7 Health. Reveal a minion in each deck.
    //       If yours costs more, Restore 14 instead.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [AT_049] Thunder Bluff Valiant - COST:5 [ATK:3/HP:6]
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Inspire:</b> Give your Totems +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - INSPIRE = 1
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - SHAMAN
    // [AT_050] Charged Hammer - COST:4 [ATK:2/HP:0]
    // - Set: Tgt, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Your Hero Power
    //       becomes 'Deal 2 damage.'
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 4
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [AT_051] Elemental Destruction - COST:3
    // - Set: Tgt, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 4-5 damage to all minions.
    //       <b>Overload:</b> (5)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 5
    // - OVERLOAD_OWED = 5
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [AT_052] Totem Golem - COST:2 [ATK:3/HP:4]
    // - Race: Totem, Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 1
    // - OVERLOAD_OWED = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [AT_053] Ancestral Knowledge - COST:2
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: Draw 2 cards. <b>Overload:</b> (2)
    // --------------------------------------------------------
    // GameTag:
    // - OVERLOAD = 2
    // - OVERLOAD_OWED = 2
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [AT_054] The Mistcaller - COST:6 [ATK:4/HP:4]
    // - Set: Tgt, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give all minions in your hand
    //       and deck +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void TgtCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [AT_047e] Experienced (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(
        std::make_unique<Enchant>(Enchants::AddAttackHealthScriptTag));
    cards.emplace("AT_047e", cardDef);

    // ----------------------------------- ENCHANTMENT - SHAMAN
    // [AT_049e] Power of the Bluff (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [AT_132_SHAMANa] Healing Totem (*) - COST:0 [ATK:0/HP:2]
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: At the end of your turn, restore 1 Health to all friendly minions.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<HealTask>(
        EntityType::MINIONS, 1) };
    cards.emplace("AT_132_SHAMANa", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [AT_132_SHAMANb] Searing Totem (*) - COST:0 [ATK:1/HP:1]
    // - Set: Tgt
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("AT_132_SHAMANb", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [AT_132_SHAMANc] Stoneclaw Totem (*) - COST:0 [ATK:0/HP:2]
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("AT_132_SHAMANc", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [AT_132_SHAMANd] Wrath of Air Totem (*) - COST:0 [ATK:0/HP:2]
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("AT_132_SHAMANd", cardDef);

    // ---------------------------------------- MINION - SHAMAN
    // [AT_132_SHAMANe] Strength Totem (*) - COST:0 [ATK:0/HP:2]
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       give another friendly minion +1 Attack.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::TURN_END));
    cardDef.power.GetTrigger()->tasks = {
        std::make_shared<RandomTask>(EntityType::MINIONS_NOSOURCE, 1),
        std::make_shared<AddEnchantmentTask>("CS2_058e", EntityType::STACK)
    };
    cards.emplace("AT_132_SHAMANe", cardDef);
}

void TgtCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - WARLOCK
    // [AT_019] Dreadsteed - COST:4 [ATK:1/HP:1]
    // - Race: Demon, Set: Tgt, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> At the end of the turn,
    //       summon a Dreadsteed.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [AT_020] Fearsome Doomguard - COST:7 [ATK:6/HP:8]
    // - Race: Demon, Set: Tgt, Rarity: Common
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [AT_021] Tiny Knight of Evil - COST:2 [ATK:3/HP:2]
    // - Race: Demon, Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever you discard a card, gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddTrigger(std::make_shared<Trigger>(TriggerType::DISCARD));
    cardDef.power.GetTrigger()->tasks = { std::make_shared<AddEnchantmentTask>(
        "AT_021e", EntityType::SOURCE) };
    cards.emplace("AT_021", cardDef);

    // ---------------------------------------- SPELL - WARLOCK
    // [AT_022] Fist of Jaraxxus - COST:4
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: When you play or discard this,
    //       deal 4 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - InvisibleDeathrattle = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [AT_023] Void Crusher - COST:6 [ATK:5/HP:4]
    // - Race: Demon, Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Inspire:</b> Destroy a random minion for each player.
    // --------------------------------------------------------
    // GameTag:
    // - INSPIRE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [AT_024] Demonfuse - COST:2
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a Demon +3/+3.
    //       Give your opponent a Mana Crystal.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_WITH_RACE = 15
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [AT_025] Dark Bargain - COST:6
    // - Set: Tgt, Rarity: Epic
    // --------------------------------------------------------
    // Text: Destroy 2 random enemy minions.
    //       Discard 2 random cards.
    // --------------------------------------------------------
    // GameTag:
    // - 890 = 2
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINIMUM_ENEMY_MINIONS = 2
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [AT_026] Wrathguard - COST:2 [ATK:4/HP:3]
    // - Race: Demon, Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever this minion takes damage,
    //       also deal that amount to your hero.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [AT_027] Wilfred Fizzlebang - COST:6 [ATK:4/HP:4]
    // - Set: Tgt, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Cards you draw from your Hero Power cost (0).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
}

void TgtCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [AT_021e] Felrage (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(std::make_shared<OngoingEnchant>(
        std::vector<std::shared_ptr<IEffect>>{ Effects::AttackHealthN(1) }));
    cards.emplace("AT_021e", cardDef);

    // ---------------------------------- ENCHANTMENT - WARLOCK
    // [AT_027e] Master Summoner (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: Costs (0).
    // --------------------------------------------------------
}

void TgtCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - WARRIOR
    // [AT_064] Bash - COST:2
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 3 damage.
    //       Gain 3 Armor.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::TARGET, 3, true));
    cardDef.power.AddPowerTask(std::make_shared<ArmorTask>(3));
    cardDef.property.playReqs = PlayReqs{ { PlayReq::REQ_TARGET_TO_PLAY, 0 } };
    cards.emplace("AT_064", cardDef);

    // --------------------------------------- WEAPON - WARRIOR
    // [AT_065] King's Defender - COST:3 [ATK:3/HP:0]
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you have a minion
    //       with <b>Taunt</b>, gain +1 Durability.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [AT_066] Orgrimmar Aspirant - COST:3 [ATK:3/HP:3]
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Inspire:</b> Give your weapon +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - INSPIRE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [AT_067] Magnataur Alpha - COST:4 [ATK:5/HP:3]
    // - Set: Tgt, Rarity: Epic
    // --------------------------------------------------------
    // Text: Also damages the minions next to whomever he attacks.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [AT_068] Bolster - COST:2
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: Give your <b>Taunt</b> minions +2/+2.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [AT_069] Sparring Partner - COST:2 [ATK:3/HP:2]
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Give a minion <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [AT_071] Alexstrasza's Champion - COST:2 [ATK:2/HP:3]
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       gain +1 Attack and <b>Charge</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [AT_072] Varian Wrynn - COST:10 [ATK:7/HP:7]
    // - Set: Tgt, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Draw 3 cards.
    //       Put any minions you drew directly into the battlefield.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [AT_130] Sea Reaver - COST:6 [ATK:6/HP:7]
    // - Set: Tgt, Rarity: Epic
    // --------------------------------------------------------
    // Text: When you draw this, deal 1 damage to your minions.
    // --------------------------------------------------------
    // GameTag:
    // - TOPDECK = 1
    // --------------------------------------------------------
}

void TgtCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [AT_066e] Forges of Orgrimmar (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [AT_068e] Bolstered (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [AT_069e] Training Complete (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [AT_071e] Alexstrasza's Boon (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: +1 Attack and <b>Charge</b>.
    // --------------------------------------------------------
}

void TgtCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [AT_017] Twilight Guardian - COST:4 [ATK:2/HP:6]
    // - Race: Dragon, Set: Tgt, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       gain +1 Attack and <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_070] Skycap'n Kragg - COST:7 [ATK:4/HP:6]
    // - Race: Pirate, Set: Tgt, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Charrrrrge</b>
    //       Costs (1) less for each friendly Pirate.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CHARGE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_080] Garrison Commander - COST:2 [ATK:2/HP:3]
    // - Set: Tgt, Rarity: Epic
    // --------------------------------------------------------
    // Text: You can use your Hero Power twice a turn.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_082] Lowly Squire - COST:1 [ATK:1/HP:2]
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Inspire:</b> Gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - INSPIRE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_083] Dragonhawk Rider - COST:3 [ATK:3/HP:3]
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Inspire:</b> Gain <b>Windfury</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - INSPIRE = 1
    // --------------------------------------------------------
    // RefTag:
    // - WINDFURY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_084] Lance Carrier - COST:2 [ATK:1/HP:2]
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_085] Maiden of the Lake - COST:4 [ATK:2/HP:6]
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: Your Hero Power costs (1).
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_086] Saboteur - COST:3 [ATK:4/HP:3]
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Your opponent's Hero Power costs
    //       (5) more next turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_087] Argent Horserider - COST:3 [ATK:2/HP:1]
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    //       <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - DIVINE_SHIELD = 1
    // - CHARGE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_088] Mogor's Champion - COST:6 [ATK:8/HP:5]
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: 50% chance to attack the wrong enemy.
    // --------------------------------------------------------
    // GameTag:
    // - FORGETFUL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_089] Boneguard Lieutenant - COST:2 [ATK:3/HP:2]
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Inspire:</b> Gain +1 Health.
    // --------------------------------------------------------
    // GameTag:
    // - INSPIRE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_090] Mukla's Champion - COST:5 [ATK:4/HP:3]
    // - Race: Beast, Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Inspire:</b> Give your other minions +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - INSPIRE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_091] Tournament Medic - COST:4 [ATK:1/HP:8]
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Inspire:</b> Restore 2 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - INSPIRE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_092] Ice Rager - COST:3 [ATK:5/HP:2]
    // - Race: Elemental, Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(nullptr);
    cards.emplace("AT_092", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [AT_093] Frigid Snobold - COST:4 [ATK:2/HP:6]
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_094] Flame Juggler - COST:2 [ATK:2/HP:3]
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_095] Silent Knight - COST:3 [ATK:2/HP:2]
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //       <b>Divine Shield</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_096] Clockwork Knight - COST:5 [ATK:5/HP:5]
    // - Race: Mechanical, Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly Mech +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_FRIENDLY_TARGET = 0
    // - REQ_TARGET_WITH_RACE = 17
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_097] Tournament Attendee - COST:1 [ATK:2/HP:1]
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_098] Sideshow Spelleater - COST:6 [ATK:6/HP:5]
    // - Set: Tgt, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Copy your opponent's Hero Power.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_099] Kodorider - COST:6 [ATK:3/HP:5]
    // - Set: Tgt, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Inspire:</b> Summon a 3/5 War Kodo.
    // --------------------------------------------------------
    // GameTag:
    // - INSPIRE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_100] Silver Hand Regent - COST:3 [ATK:3/HP:3]
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Inspire:</b> Summon a 1/1 Silver Hand Recruit.
    // --------------------------------------------------------
    // GameTag:
    // - INSPIRE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_101] Pit Fighter - COST:5 [ATK:5/HP:6]
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_102] Captured Jormungar - COST:7 [ATK:5/HP:9]
    // - Race: Beast, Set: Tgt, Rarity: Common
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_103] North Sea Kraken - COST:9 [ATK:9/HP:7]
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 4 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_105] Injured Kvaldir - COST:1 [ATK:2/HP:4]
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage to this minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_106] Light's Champion - COST:3 [ATK:4/HP:3]
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Silence</b> a Demon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE = 0
    // - REQ_TARGET_WITH_RACE = 15
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
    // RefTag:
    // - SILENCE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_108] Armored Warhorse - COST:4 [ATK:5/HP:3]
    // - Race: Beast, Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Reveal a minion in each deck.
    //       If yours costs more, gain <b>Charge</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_109] Argent Watchman - COST:2 [ATK:2/HP:4]
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: Can't attack.
    //       <b>Inspire:</b> Can attack as normal this turn.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_ATTACK = 1
    // - INSPIRE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_110] Coliseum Manager - COST:3 [ATK:2/HP:5]
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Inspire:</b> Return this minion to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - INSPIRE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_111] Refreshment Vendor - COST:4 [ATK:3/HP:5]
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 4 Health to each hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_112] Master Jouster - COST:6 [ATK:5/HP:6]
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Reveal a minion in each deck.
    //       If yours costs more, gain <b>Taunt</b>
    //       and <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_113] Recruiter - COST:5 [ATK:5/HP:4]
    // - Set: Tgt, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Inspire:</b> Add a 2/2 Squire to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - INSPIRE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_114] Evil Heckler - COST:4 [ATK:5/HP:4]
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_115] Fencing Coach - COST:3 [ATK:2/HP:2]
    // - Set: Tgt, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> The next time you use your
    //       Hero Power, it costs (2) less.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_117] Master of Ceremonies - COST:3 [ATK:4/HP:2]
    // - Set: Tgt, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you have a minion
    //       with <b>Spell Damage</b>, gain +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_118] Grand Crusader - COST:6 [ATK:5/HP:5]
    // - Set: Tgt, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a random Paladin card
    //       to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_119] Kvaldir Raider - COST:5 [ATK:4/HP:4]
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Inspire:</b> Gain +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - INSPIRE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_120] Frost Giant - COST:10 [ATK:8/HP:8]
    // - Set: Tgt, Rarity: Epic
    // --------------------------------------------------------
    // Text: Costs (1) less for each time you used your
    //       Hero Power this game.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_121] Crowd Favorite - COST:4 [ATK:4/HP:4]
    // - Set: Tgt, Rarity: Epic
    // --------------------------------------------------------
    // Text: Whenever you play a card with <b>Battlecry</b>,
    //       gain +1/+1.
    // --------------------------------------------------------
    // RefTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_122] Gormok the Impaler - COST:4 [ATK:4/HP:4]
    // - Set: Tgt, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you have at least 4 other
    //       minions, deal 4 damage.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_IF_AVAILABLE_AND_MINIMUM_FRIENDLY_MINIONS = 4
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_123] Chillmaw - COST:7 [ATK:6/HP:6]
    // - Race: Dragon, Set: Tgt, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> If you're holding a Dragon,
    //       deal 3 damage to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_124] Bolf Ramshield - COST:6 [ATK:3/HP:9]
    // - Set: Tgt, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever your hero takes damage,
    //       this minion takes it instead.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_125] Icehowl - COST:9 [ATK:10/HP:10]
    // - Set: Tgt, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    //       Can't attack heroes.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CHARGE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_127] Nexus-Champion Saraad - COST:5 [ATK:4/HP:5]
    // - Set: Tgt, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Inspire:</b> Add a random spell to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - INSPIRE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_128] The Skeleton Knight - COST:6 [ATK:7/HP:4]
    // - Set: Tgt, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Reveal a minion in each deck.
    //       If yours costs more, return this to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_129] Fjola Lightbane - COST:3 [ATK:3/HP:4]
    // - Set: Tgt, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever <b>you</b> target this minion with a spell,
    //       gain <b>Divine Shield.</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_131] Eydis Darkbane - COST:3 [ATK:3/HP:4]
    // - Set: Tgt, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever <b>you</b> target this minion with a spell,
    //       deal 3 damage to a random enemy.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_132] Justicar Trueheart - COST:6 [ATK:6/HP:3]
    // - Set: Tgt, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Replace your starting Hero Power
    //       with a better one.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_133] Gadgetzan Jouster - COST:1 [ATK:1/HP:2]
    // - Set: Tgt, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Reveal a minion in each deck.
    //       If yours costs more, gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void TgtCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [AT_005t] Boar (*) - COST:3 [ATK:4/HP:2]
    // - Race: Beast, Set: Tgt
    // --------------------------------------------------------
    // Text: <b>Charge</b>
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AT_011e] Light's Blessing (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AT_013e] Power Word: Glory (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: When this attacks, restore 4 Health to the hero
    //       of the player who buffed it.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AT_017e] Twilight's Embrace (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: +1 Attack and <b>Taunt</b>.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AT_019e] Dreadsteed (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: Summon a Dreadsteed at the end of the turn.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AT_024e] Dark Fusion (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: +3/+3.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AT_028e] Chi Lance (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: +3 Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AT_029e] Extra Stabby (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: +1 Attack
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddEnchant(Enchants::GetEnchantFromText("AT_029e"));
    cards.emplace("AT_029e", cardDef);

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AT_041e] Call of the Wild (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: Cost reduced.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AT_045e] Empowering Mist (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AT_045ee] Mistcaller Deck Ench (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AT_065e] King's Defender (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: +1 Durability.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AT_073e] Competitive Spirit (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AT_077e] Extra Poke (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: +1 Durability.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AT_082e] Training (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AT_083e] Dragonhawkery (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: <b>Windfury</b> this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AT_084e] Equipped (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AT_086e] Villainy (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: Your Hero Power costs (5) more this turn.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AT_089e] Boneguarded (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: Increased Health.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AT_090e] Might of the Monkey (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AT_096e] Wound Up (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [AT_099t] War Kodo (*) - COST:5 [ATK:3/HP:5]
    // - Race: Beast, Set: Tgt
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AT_109e] Inspired (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: Can attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AT_115e] Fencing Practice (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: Your Hero Power costs (2) less.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AT_117e] Ceremony (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AT_119e] Inspired (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AT_121e] Huge Ego (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [AT_133e] Victory! (*) - COST:0
    // - Set: Tgt
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------
}

void TgtCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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
