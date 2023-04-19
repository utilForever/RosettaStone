// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/CardSets/GangsCardsGen.hpp>
#include <Rosetta/PlayMode/Cards/CardPowers.hpp>

namespace RosettaStone::PlayMode
{
void GangsCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void GangsCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void GangsCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- MINION - DRUID
    // [CFM_308] Kun the Forgotten King - COST:10 [ATK:7/HP:7]
    // - Set: GANGS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Gain 10 Armor;
    //       or Refresh your Mana Crystals.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [CFM_343] Jade Behemoth - COST:6 [ATK:3/HP:6]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Summon a {1}/{0} <b>Jade Golem</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [CFM_602] Jade Idol - COST:1
    // - Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Choose One -</b> Summon a {1}/{0} <b>Jade Golem</b>;
    //       or Shuffle 3 copies of this card into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - CHOOSE_ONE = 1
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [CFM_614] Mark of the Lotus - COST:1
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: Give your minions +1/+1.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [CFM_616] Pilfered Power - COST:3
    // - Set: GANGS, Rarity: Epic
    // --------------------------------------------------------
    // Text: Gain an empty Mana Crystal for each friendly minion.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [CFM_617] Celestial Dreamer - COST:3 [ATK:3/HP:3]
    // - Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a minion
    //       with 5 or more Attack, gain +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [CFM_713] Jade Blossom - COST:3
    // - Set: GANGS, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Summon a {1}/{0} <b>Jade Golem</b>.
    //       Gain an empty Mana Crystal.
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [CFM_811] Lunar Visions - COST:5
    // - Set: GANGS, Rarity: Epic
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Draw 2 cards. Minions drawn cost (2) less.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - DRUID
    // [CFM_816] Virmen Sensei - COST:5 [ATK:4/HP:5]
    // - Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly Beast +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void GangsCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ SPELL - DRUID
    // [CFM_308a] Forgotten Armor - COST:10
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Gain 10 Armor.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [CFM_308b] Forgotten Mana - COST:10
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Refresh your Mana Crystals.
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [CFM_602a] Cut from Jade - COST:1
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Summon a {1}/{0} <b>Jade Golem</b>.
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - DRUID
    // [CFM_602b] Jade Stash - COST:1
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Shuffle 3 Jade Idols into your deck.
    // --------------------------------------------------------
}

void GangsCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- SPELL - HUNTER
    // [CFM_026] Hidden Cache - COST:2
    // - Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After your opponent plays a minion,
    //       give a random minion in your hand +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [CFM_315] Alleycat - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 1/1 Cat.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [CFM_316] Rat Pack - COST:3 [ATK:2/HP:2]
    // - Race: Beast, Set: GANGS, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a number of 1/1 Rats
    //       equal to this minion's Attack.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [CFM_333] Knuckles - COST:5 [ATK:3/HP:7]
    // - Race: Beast, Set: GANGS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After this attacks a minion,
    //       it also hits the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - FINISH_ATTACK_SPELL_ON_DAMAGE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - HUNTER
    // [CFM_334] Smuggler's Crate - COST:1
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: Give a random Beast in your hand +2/+2.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [CFM_335] Dispatch Kodo - COST:4 [ATK:2/HP:4]
    // - Race: Beast, Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal damage equal to
    //       this minion's Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [CFM_336] Shaky Zipgunner - COST:3 [ATK:3/HP:3]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give a random minion
    //       in your hand +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - HUNTER
    // [CFM_337] Piranha Launcher - COST:5
    // - Set: GANGS, Rarity: Epic
    // --------------------------------------------------------
    // Text: After your hero attacks, summon a 1/1 Piranha.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [CFM_338] Trogg Beastrager - COST:2 [ATK:3/HP:2]
    // - Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a random Beast
    //       in your hand +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void GangsCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- ENCHANTMENT - HUNTER
    // [CFM_026e] Smuggling - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: +2/+2 from Hidden Cache.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [CFM_315t] Tabbycat - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: GANGS
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [CFM_316t] Rat - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: GANGS
    // --------------------------------------------------------

    // ---------------------------------------- MINION - HUNTER
    // [CFM_337t] Piranha - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: GANGS
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - HUNTER
    // [CFM_338e] Smuggling - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: +1/+1 from Trogg Beastrager.
    // --------------------------------------------------------
}

void GangsCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------- SPELL - MAGE
    // [CFM_021] Freezing Potion - COST:0
    // - Set: GANGS, Rarity: Common
    // - Spell School: Frost
    // --------------------------------------------------------
    // Text: <b>Freeze</b> an enemy.
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [CFM_065] Volcanic Potion - COST:3
    // - Set: GANGS, Rarity: Rare
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Deal 2 damage to all minions.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [CFM_066] Kabal Lackey - COST:1 [ATK:2/HP:1]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> The next <b>Secret</b>
    //       you play this turn costs (0).
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [CFM_620] Potion of Polymorph - COST:3
    // - Set: GANGS, Rarity: Rare
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: <b>Secret:</b> After your opponent plays a minion,
    //       transform it into a 1/1 Sheep.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // ------------------------------------------- SPELL - MAGE
    // [CFM_623] Greater Arcane Missiles - COST:7
    // - Set: GANGS, Rarity: Epic
    // - Spell School: Arcane
    // --------------------------------------------------------
    // Text: Shoot three missiles at random enemies
    //       that deal 3 damage each.
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [CFM_660] Manic Soulcaster - COST:3 [ATK:3/HP:4]
    // - Set: GANGS, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a friendly minion.
    //       Shuffle a copy into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [CFM_671] Cryomancer - COST:5 [ATK:5/HP:5]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If an enemy is <b>Frozen</b>,
    //       gain +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [CFM_687] Inkmaster Solia - COST:7 [ATK:5/HP:5]
    // - Set: GANGS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck has no duplicates,
    //       the next spell you cast this turn costs (0).
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ MINION - MAGE
    // [CFM_760] Kabal Crystal Runner - COST:6 [ATK:5/HP:5]
    // - Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: Costs (2) less for each <b>Secret</b>
    //       you've played this game.
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------
}

void GangsCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------- ENCHANTMENT - MAGE
    // [CFM_687e] Free Spell - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: The next spell you cast this turn costs (0).
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_SILENCED = 1
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
}

void GangsCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - PALADIN
    // [CFM_062] Grimestreet Protector - COST:7 [ATK:6/HP:6]
    // - Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Give adjacent minions
    //       <b>Divine Shield</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------
    // RefTag:
    // - DIVINE_SHIELD = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [CFM_305] Smuggler's Run - COST:1
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: Give all minions in your hand +1/+1.
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [CFM_639] Grimestreet Enforcer - COST:5 [ATK:4/HP:4]
    // - Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       give all minions in your hand +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [CFM_650] Grimscale Chum - COST:1 [ATK:2/HP:1]
    // - Race: Murloc, Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a random Murloc
    //       in your hand +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [CFM_753] Grimestreet Outfitter - COST:2 [ATK:1/HP:1]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give all minions
    //       in your hand +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [CFM_759] Meanstreet Marshal - COST:1 [ATK:1/HP:2]
    // - Set: GANGS, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> If this minion has 2 or
    //       more Attack, draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [CFM_800] Getaway Kodo - COST:1
    // - Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When a friendly minion dies,
    //       return it to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - PALADIN
    // [CFM_815] Wickerflame Burnbristle - COST:3 [ATK:2/HP:2]
    // - Set: GANGS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Divine Shield, Taunt, Lifesteal</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DIVINE_SHIELD = 1
    // - LIFESTEAL = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - PALADIN
    // [CFM_905] Small-Time Recruits - COST:3
    // - Set: GANGS, Rarity: Epic
    // --------------------------------------------------------
    // Text: Draw three 1-Cost minions from your deck.
    // --------------------------------------------------------
}

void GangsCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------- ENCHANTMENT - PALADIN
    // [CFM_305e] Smuggling - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: +1/+1 from Smuggler's Run.
    // --------------------------------------------------------
}

void GangsCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- MINION - PRIEST
    // [CFM_020] Raza the Chained - COST:5 [ATK:5/HP:5]
    // - Set: GANGS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck has no duplicates,
    //       your Hero Power costs (0) this game.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [CFM_603] Potion of Madness - COST:1
    // - Set: GANGS, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Gain control of an enemy minion with 2
    //       or less Attack until end of turn.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [CFM_604] Greater Healing Potion - COST:4
    // - Set: GANGS, Rarity: Rare
    // - Spell School: Holy
    // --------------------------------------------------------
    // Text: Restore 12 Health to a friendly character.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [CFM_605] Drakonid Operative - COST:5 [ATK:5/HP:6]
    // - Race: Dragon, Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you're holding a Dragon,
    //       <b>Discover</b> a copy of a card
    //       in your opponent's deck.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(std::make_shared<ConditionTask>(
        EntityType::SOURCE, SelfCondList{ std::make_shared<SelfCondition>(
                                SelfCondition::IsHoldingRace(Race::DRAGON)) }));
    cardDef.power.AddPowerTask(std::make_shared<FlagTask>(
        true,
        TaskList{ std::make_shared<DiscoverTask>(DiscoverType::ENEMY_DECK) }));
    cards.emplace("CFM_605", cardDef);

    // ---------------------------------------- MINION - PRIEST
    // [CFM_606] Mana Geode - COST:2 [ATK:2/HP:3]
    // - Race: Elemental, Set: GANGS, Rarity: Epic
    // --------------------------------------------------------
    // Text: Whenever this minion is healed, summon a 2/2 Crystal.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [CFM_626] Kabal Talonpriest - COST:3 [ATK:3/HP:4]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a friendly minion +3 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [CFM_657] Kabal Songstealer - COST:5 [ATK:5/HP:5]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Silence</b> a minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SILENCE = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [CFM_661] Pint-Size Potion - COST:1
    // - Set: GANGS, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Give all enemy minions -3 Attack this turn only.
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - PRIEST
    // [CFM_662] Dragonfire Potion - COST:6
    // - Set: GANGS, Rarity: Epic
    // - Spell School: Fire
    // --------------------------------------------------------
    // Text: Deal 5 damage to all minions except Dragons.
    // --------------------------------------------------------
}

void GangsCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- ENCHANTMENT - PRIEST
    // [CFM_603e] Madness Potion - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: This minion has switched controllers this turn.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - PRIEST
    // [CFM_606t] Crystal - COST:2 [ATK:2/HP:2]
    // - Race: Elemental, Set: GANGS
    // --------------------------------------------------------

    // ----------------------------------- ENCHANTMENT - PRIEST
    // [CFM_661e] Shrunk - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: -3 Attack this turn.
    // --------------------------------------------------------
    // GameTag:
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------
}

void GangsCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- MINION - ROGUE
    // [CFM_342] Luckydo Buccaneer - COST:6 [ATK:5/HP:5]
    // - Race: Pirate, Set: GANGS, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your weapon has at least
    //       3 Attack, gain +4/+4.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [CFM_630] Counterfeit Coin - COST:0
    // - Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: Gain 1 Mana Crystal this turn only.
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [CFM_634] Lotus Assassin - COST:5 [ATK:5/HP:5]
    // - Set: GANGS, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Stealth</b>.
    //       Whenever this attacks and kills a minion,
    //       gain <b>Stealth</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [CFM_636] Shadow Rager - COST:3 [ATK:5/HP:1]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ------------------------------------------ SPELL - ROGUE
    // [CFM_690] Jade Shuriken - COST:2
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: Deal 2 damage.
    //       <b>Combo:</b> Summon a {1}/{0} <b>Jade Golem</b>.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------
    // RefTag:
    // - CHOOSE_ONE = 1
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [CFM_691] Jade Swarmer - COST:2 [ATK:1/HP:1]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //       <b>Deathrattle:</b> Summon a {1}/{0} <b>Jade Golem</b>.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // - STEALTH = 1
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [CFM_693] Gadgetzan Ferryman - COST:2 [ATK:2/HP:3]
    // - Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Combo:</b> Return a friendly minion to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - COMBO = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [CFM_694] Shadow Sensei - COST:4 [ATK:4/HP:4]
    // - Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a <b>Stealthed</b> minion +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // ----------------------------------------- MINION - ROGUE
    // [CFM_781] Shaku, the Collector - COST:3 [ATK:2/HP:3]
    // - Set: GANGS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Stealth</b>. Whenever this attacks,
    //       add a random card to your hand
    //       <i>(from your opponent's class).</i>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - STEALTH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
}

void GangsCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------ ENCHANTMENT - ROGUE
    // [CFM_342e] Looted Blade - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: +4/+4.
    // --------------------------------------------------------

    // ------------------------------------ ENCHANTMENT - ROGUE
    // [CFM_694e] Trained - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------
}

void GangsCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- MINION - SHAMAN
    // [CFM_061] Jinyu Waterspeaker - COST:4 [ATK:3/HP:6]
    // - Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 6 Health.
    //       <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - OVERLOAD = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [CFM_310] Call in the Finishers - COST:4
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: Summon four 1/1 Murlocs.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [CFM_312] Jade Chieftain - COST:7 [ATK:5/HP:5]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a {1}/{0} <b>Jade Golem</b>.
    //       Give it <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [CFM_313] Finders Keepers - COST:1
    // - Set: GANGS, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Discover</b> a card with <b>Overload</b>.
    //       <b>Overload:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // - OVERLOAD = 1
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [CFM_324] White Eyes - COST:5 [ATK:5/HP:5]
    // - Set: GANGS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Deathrattle:</b> Shuffle 'The Storm Guardian'
    //       into your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [CFM_696] Devolve - COST:2
    // - Set: GANGS, Rarity: Rare
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Transform all enemy minions into random ones
    //       that cost (1) less.
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [CFM_697] Lotus Illusionist - COST:4 [ATK:3/HP:5]
    // - Set: GANGS, Rarity: Epic
    // --------------------------------------------------------
    // Text: After this minion attacks a hero,
    //       transform it into a random 6-Cost minion.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ----------------------------------------- SPELL - SHAMAN
    // [CFM_707] Jade Lightning - COST:4
    // - Set: GANGS, Rarity: Common
    // - Spell School: Nature
    // --------------------------------------------------------
    // Text: Deal 4 damage. Summon a {1}/{0} <b>Jade Golem</b>.
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // ---------------------------------------- WEAPON - SHAMAN
    // [CFM_717] Jade Claws - COST:2
    // - Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a {1}/{0} <b>Jade Golem</b>.
    //       <b><b>Overload</b>:</b> (1)
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - OVERLOAD = 1
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------
}

void GangsCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- MINION - SHAMAN
    // [CFM_310t] Murloc Razorgill - COST:1 [ATK:1/HP:1]
    // - Race: Murloc, Set: GANGS
    // --------------------------------------------------------

    // ---------------------------------------- MINION - SHAMAN
    // [CFM_324t] The Storm Guardian - COST:5 [ATK:10/HP:10]
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TAUNT = 1
    // --------------------------------------------------------
}

void GangsCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // ---------------------------------------- SPELL - WARLOCK
    // [CFM_094] Felfire Potion - COST:6
    // - Set: GANGS, Rarity: Rare
    // - Spell School: Fel
    // --------------------------------------------------------
    // Text: Deal 5 damage to all characters.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [CFM_608] Blastcrystal Potion - COST:4
    // - Set: GANGS, Rarity: Common
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Destroy a minion and one of your Mana Crystals.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [CFM_610] Crystalweaver - COST:4 [ATK:5/HP:4]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your Demons +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARLOCK
    // [CFM_611] Bloodfury Potion - COST:3
    // - Set: GANGS, Rarity: Rare
    // - Spell School: Shadow
    // --------------------------------------------------------
    // Text: Give a minion +3 Attack.
    //       If it's a Demon, also give it +3 Health.
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [CFM_663] Kabal Trafficker - COST:6 [ATK:6/HP:6]
    // - Set: GANGS, Rarity: Epic
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       add a random Demon to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [CFM_699] Seadevil Stinger - COST:4 [ATK:4/HP:2]
    // - Race: Murloc, Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> The next Murloc you play
    //       this turn costs Health instead of Mana.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [CFM_750] Krul the Unshackled - COST:9 [ATK:7/HP:9]
    // - Race: Demon, Set: GANGS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck has no duplicates,
    //       summon all Demons from your hand. 
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARLOCK
    // [CFM_751] Abyssal Enforcer - COST:7 [ATK:6/HP:6]
    // - Race: Demon, Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 3 damage to all other characters.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddPowerTask(
        std::make_shared<DamageTask>(EntityType::ALL_NOSOURCE, 3));
    cards.emplace("CFM_751", cardDef);

    // --------------------------------------- MINION - WARLOCK
    // [CFM_900] Unlicensed Apothecary - COST:3 [ATK:5/HP:5]
    // - Race: Demon, Set: GANGS, Rarity: Epic
    // --------------------------------------------------------
    // Text: After you summon a minion, deal 5 damage to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------
}

void GangsCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void GangsCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - WARRIOR
    // [CFM_300] Public Defender - COST:2 [ATK:0/HP:7]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- WEAPON - WARRIOR
    // [CFM_631] Brass Knuckles - COST:4
    // - Set: GANGS, Rarity: Epic
    // --------------------------------------------------------
    // Text: After your hero attacks,
    //       give a random minion in your hand +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [CFM_643] Hobart Grapplehammer - COST:2 [ATK:2/HP:2]
    // - Set: GANGS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give all weapons in your hand
    //       and deck +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [CFM_716] Sleep with the Fishes - COST:2
    // - Set: GANGS, Rarity: Epic
    // --------------------------------------------------------
    // Text: Deal 3 damage to all damaged minions.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [CFM_752] Stolen Goods - COST:2
    // - Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: Give a random <b>Taunt</b> minion in your hand +3/+3.
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [CFM_754] Grimy Gadgeteer - COST:4 [ATK:4/HP:3]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       give a random minion in your hand +2/+2.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [CFM_755] Grimestreet Pawnbroker - COST:3 [ATK:3/HP:3]
    // - Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a random weapon
    //       in your hand +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - WARRIOR
    // [CFM_756] Alley Armorsmith - COST:5 [ATK:2/HP:7]
    // - Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       Whenever this minion deals damage,
    //       gain that much Armor.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - WARRIOR
    // [CFM_940] I Know a Guy - COST:1
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Discover</b> a <b>Taunt</b> minion.
    // --------------------------------------------------------
    // GameTag:
    // - DISCOVER = 1
    // --------------------------------------------------------
    // RefTag:
    // - TAUNT = 1
    // --------------------------------------------------------
}

void GangsCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [CFM_643e] Smuggling - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: +1 Attack from Hobart Grapplehammer.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - WARRIOR
    // [CFM_643e2] Smuggling - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: +1 Attack from Hobart Grapplehammer.
    // --------------------------------------------------------
}

void GangsCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    CardDef cardDef;

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_025] Wind-up Burglebot - COST:6 [ATK:5/HP:5]
    // - Race: Mechanical, Set: GANGS, Rarity: Epic
    // --------------------------------------------------------
    // Text: Whenever this attacks a minion and survives,
    //       draw a card.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_039] Street Trickster - COST:3 [ATK:0/HP:7]
    // - Race: Demon, Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Spell Damage +1</b>
    // --------------------------------------------------------
    // GameTag:
    // - SPELLPOWER = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_060] Red Mana Wyrm - COST:5 [ATK:2/HP:6]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever you cast a spell, gain +2 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_063] Kooky Chemist - COST:4 [ATK:4/HP:4]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Swap the Attack
    //       and Health of a minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_064] Blubber Baron - COST:3 [ATK:1/HP:1]
    // - Set: GANGS, Rarity: Epic
    // --------------------------------------------------------
    // Text: Whenever you summon a <b>Battlecry</b> minion
    //       while this is in your hand, gain +1/+1.
    // --------------------------------------------------------
    // RefTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_067] Hozen Healer - COST:4 [ATK:2/HP:6]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry</b>: Restore a minion to full Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_095] Weasel Tunneler - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: GANGS, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Shuffle this minion
    //       into your opponent's deck.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_120] Mistress of Mixtures - COST:1 [ATK:2/HP:2]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Restore 4 Health to each hero.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    cardDef.ClearData();
    cardDef.power.AddDeathrattleTask(
        std::make_shared<HealTask>(EntityType::HERO, 4));
    cardDef.power.AddDeathrattleTask(
        std::make_shared<HealTask>(EntityType::ENEMY_HERO, 4));
    cards.emplace("CFM_120", cardDef);

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_321] Grimestreet Informant - COST:2 [ATK:1/HP:1]
    // - Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a Hunter,
    //       Paladin, or Warrior card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - GRIMY_GOONS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_325] Small-Time Buccaneer - COST:1 [ATK:1/HP:1]
    // - Race: Pirate, Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: Has +2 Attack while you have a weapon equipped.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_328] Fight Promoter - COST:6 [ATK:4/HP:4]
    // - Set: GANGS, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If you control a minion with 6
    //       or more Health, draw two cards.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_341] Sergeant Sally - COST:3 [ATK:1/HP:1]
    // - Set: GANGS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal damage equal to
    //       this minion's Attack to all enemy minions.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_344] Finja, the Flying Star - COST:5 [ATK:2/HP:4]
    // - Race: Murloc, Set: GANGS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Stealth</b>
    //       Whenever this attacks and kills a minion,
    //       summon 2 Murlocs from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - STEALTH = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_609] Fel Orc Soulfiend - COST:3 [ATK:3/HP:7]
    // - Set: GANGS, Rarity: Epic
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       deal 2 damage to this minion.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_619] Kabal Chemist - COST:4 [ATK:3/HP:3]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Add a random Potion to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - KABAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_621] Kazakus - COST:4 [ATK:3/HP:3]
    // - Set: GANGS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your deck has no duplicates,
    //       create a custom spell.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - KABAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_637] Patches the Pirate - COST:1 [ATK:1/HP:1]
    // - Race: Pirate, Set: GANGS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you play a Pirate,
    //       summon this minion from your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_646] Backstreet Leper - COST:3 [ATK:3/HP:1]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 2 damage to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_647] Blowgill Sniper - COST:2 [ATK:2/HP:1]
    // - Race: Murloc, Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 1 damage.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_648] Big-Time Racketeer - COST:6 [ATK:1/HP:1]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a 6/6 Ogre.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_649] Kabal Courier - COST:3 [ATK:2/HP:2]
    // - Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a Mage,
    //       Priest, or Warlock card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - KABAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_651] Naga Corsair - COST:4 [ATK:5/HP:4]
    // - Race: Pirate, Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give your weapon +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_652] Second-Rate Bruiser - COST:5 [ATK:4/HP:5]
    // - Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       Costs (2) less if your opponent has
    //       at least three minions.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_653] Hired Gun - COST:3 [ATK:4/HP:3]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_654] Friendly Bartender - COST:2 [ATK:2/HP:3]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: At the end of your turn,
    //       restore 1 Health to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_655] Toxic Sewer Ooze - COST:3 [ATK:4/HP:3]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Remove 1 Durability
    //       from your opponent's weapon.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_656] Streetwise Investigator - COST:5 [ATK:4/HP:6]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Enemy minions lose <b>Stealth</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_658] Backroom Bouncer - COST:4 [ATK:4/HP:4]
    // - Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: Whenever a friendly minion dies, gain +1 Attack.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_659] Gadgetzan Socialite - COST:2 [ATK:2/HP:2]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Restore 2 Health.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_665] Worgen Greaser - COST:4 [ATK:6/HP:4]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_666] Grook Fu Master - COST:5 [ATK:3/HP:5]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Windfury</b>
    // --------------------------------------------------------
    // GameTag:
    // - WINDFURY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_667] Bomb Squad - COST:5 [ATK:2/HP:2]
    // - Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Deal 5 damage to an enemy minion.
    //       <b>Deathrattle:</b> Deal 5 damage to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_668] Doppelgangster - COST:5 [ATK:2/HP:2]
    // - Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon 2 copies of this minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_669] Burgly Bully - COST:5 [ATK:4/HP:6]
    // - Set: GANGS, Rarity: Epic
    // --------------------------------------------------------
    // Text: Whenever your opponent casts a spell,
    //       add a Coin to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_670] Mayor Noggenfogger - COST:9 [ATK:5/HP:4]
    // - Set: GANGS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: All targets are chosen randomly.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_672] Madam Goya - COST:6 [ATK:4/HP:3]
    // - Set: GANGS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a friendly minion.
    //       Swap it with a minion in your deck.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_685] Don Han'Cho - COST:7 [ATK:5/HP:6]
    // - Set: GANGS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a random minion
    //       in your hand +5/+5.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - GRIMY_GOONS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_688] Spiked Hogrider - COST:5 [ATK:5/HP:5]
    // - Race: Quilboar, Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If an enemy minion has <b>Taunt</b>,
    //       gain <b>Charge</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_715] Jade Spirit - COST:4 [ATK:2/HP:3]
    // - Race: Elemental, Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon a {1}/{0} <b>Jade Golem</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - JADE_GOLEM = 1
    // - JADE_LOTUS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_790] Dirty Rat - COST:2 [ATK:2/HP:6]
    // - Set: GANGS, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    //       <b>Battlecry:</b> Your opponent summons
    //       a random minion from their hand.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_806] Wrathion - COST:6 [ATK:4/HP:5]
    // - Set: GANGS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Taunt</b>.
    //       <b>Battlecry:</b> Draw cards until you draw one
    //       that isn't a Dragon.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_807] Auctionmaster Beardo - COST:3 [ATK:3/HP:4]
    // - Set: GANGS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: After you cast a spell, refresh your Hero Power.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_808] Genzo, the Shark - COST:4 [ATK:5/HP:4]
    // - Set: GANGS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Whenever this attacks,
    //       both players draw until they have 3 cards.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_809] Tanaris Hogchopper - COST:4 [ATK:4/HP:4]
    // - Race: Quilboar, Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your opponent's hand is empty,
    //       gain <b>Charge</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_810] Leatherclad Hogleader - COST:6 [ATK:6/HP:6]
    // - Race: Quilboar, Set: GANGS, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> If your opponent has 6 or
    //       more cards in hand, gain <b>Charge</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - CHARGE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_851] Daring Reporter - COST:4 [ATK:3/HP:3]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever your opponent draws a card, gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_852] Lotus Agents - COST:5 [ATK:5/HP:3]
    // - Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Discover</b> a Druid,
    //       Rogue, or Shaman card.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - DISCOVER = 1
    // - JADE_LOTUS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_853] Grimestreet Smuggler - COST:3 [ATK:2/HP:4]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Give a random minion
    //       in your hand +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // - GRIMY_GOONS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_854] Ancient of Blossoms - COST:6 [ATK:3/HP:8]
    // - Set: GANGS, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_855] Defias Cleaner - COST:6 [ATK:5/HP:7]
    // - Set: GANGS, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> <b>Silence</b> a minion
    //       with <b>Deathrattle</b>.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // - SILENCE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_902] Aya Blackpaw - COST:6 [ATK:5/HP:3]
    // - Set: GANGS, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry and Deathrattle:</b>
    //       Summon a {1}/{0} <b>Jade Golem</b>.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // - DEATHRATTLE = 1
    // - JADE_GOLEM = 1
    // - JADE_LOTUS = 1
    // --------------------------------------------------------
}

void GangsCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_020e] Raza Enchant - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Your <b>Hero Power</b> costs (0).
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_060e] Mana Heist - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_063e] Kooky Chemistry - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Attack and Health have been swapped by Kooky Chemist.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_064e] Size Increase - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_325e] Equipped - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: +2 Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_334e] Smuggling - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: +2/+2 from Smuggler's Crate.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_336e] Smuggling - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: +2/+2 from Shaky Zipgunner.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_610e] Serrated Shadows - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_611e] Demonic Draught - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: +3 Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_611e2] Demonic Draught - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: +3/+3.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_614e] Savage Mark - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: +1/+1.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_617e] Visions of Hypnos - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_621_m2] Kabal Demon - COST:5 [ATK:5/HP:5]
    // - Race: Demon, Set: GANGS
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_621_m3] Kabal Demon - COST:8 [ATK:8/HP:8]
    // - Race: Demon, Set: GANGS
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_621_m4] Kabal Demon - COST:2 [ATK:2/HP:2]
    // - Race: Demon, Set: GANGS
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_621_m5] Sheep - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: GANGS
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_621e] Goldthorn - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: +2 Health.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_621e2] Goldthorn - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: +4 Health.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_621e3] Goldthorn - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: +6 Health.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t] Kazakus Potion - COST:1
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: {0}
    //       {1}
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t10] Netherbloom - COST:1
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Summon a 2/2 Demon.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t11] Lesser Potion - COST:1
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Create a 1-Cost spell.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t12] Greater Potion - COST:5
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Create a 5-Cost spell.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t13] Superior Potion - COST:10
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Create a 10-Cost spell.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t14] Kazakus Potion - COST:5
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: {0}
    //       {1}
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t15] Kazakus Potion - COST:10
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: {0}
    //       {1}
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t16] Heart of Fire - COST:5
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Deal 5 damage.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t17] Stonescale Oil - COST:5
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Gain 7 Armor.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t18] Felbloom - COST:5
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Deal 4 damage to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t19] Icecap - COST:5
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: <b>Freeze</b> 2 random enemy minions.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t2] Heart of Fire - COST:1
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Deal 3 damage.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t20] Netherbloom - COST:5
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Summon a 5/5 Demon.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t21] Mystic Wool - COST:5
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Transform a random enemy minion into a 1/1 Sheep.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t22] Kingsblood - COST:5
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Draw 2 cards.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t23] Shadow Oil - COST:5
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Add 2 random Demons to your hand.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t24] Goldthorn - COST:5
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Give your minions +4 Health.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t25] Heart of Fire - COST:10
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Deal 8 damage.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t26] Stonescale Oil - COST:10
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Gain 10 Armor.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t27] Icecap - COST:10
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: <b>Freeze</b> 3 random enemy minions.
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t28] Netherbloom - COST:10
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Summon an 8/8 Demon.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t29] Mystic Wool - COST:10
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Transform all minions into 1/1 Sheep.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t3] Stonescale Oil - COST:1
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Gain 4 Armor.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t30] Kingsblood - COST:10
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Draw 3 cards.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t31] Shadow Oil - COST:10
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Add 3 random Demons to your hand.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t32] Goldthorn - COST:10
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Give your minions +6 Health.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t33] Felbloom - COST:10
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Deal 6 damage to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t37] Ichor of Undeath - COST:1
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Summon a friendly minion that died this game.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t38] Ichor of Undeath - COST:5
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Summon 2 friendly minions that died this game.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t39] Ichor of Undeath - COST:10
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Summon 3 friendly minions that died this game.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t4] Felbloom - COST:1
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Deal 2 damage to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - AFFECTED_BY_SPELL_POWER = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t5] Icecap - COST:1
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: <b>Freeze</b> a random enemy minion.
    // --------------------------------------------------------
    // RefTag:
    // - FREEZE = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t6] Goldthorn - COST:1
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Give your minions +2 Health.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t8] Kingsblood - COST:1
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Draw a card.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [CFM_621t9] Shadow Oil - COST:1
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Add a random Demon to your hand.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_626e] Fortitude - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: +3 Health.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_631e] Smuggling - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Increased stats from Brass Knuckles.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_639e] Smuggling - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Increased stats from Grimestreet Enforcer.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_648t] "Little Friend" - COST:6 [ATK:6/HP:6]
    // - Set: GANGS
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_650e] Smuggling - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: +1/+1 from Grimscale Chum.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_651e] Extra Sharp - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: +1 Attack.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_658e] Cut Off - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Increased Attack.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_668t] Doppelgangster - COST:5 [ATK:2/HP:2]
    // - Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon 2 copies of this minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_668t2] Doppelgangster - COST:5 [ATK:2/HP:2]
    // - Set: GANGS, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon 2 copies of this minion.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_671e] We All Scream - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_685e] Smuggling - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: +5/+5 from Don Han'Cho.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_699e] Seadevil Enchant - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_SILENCED = 1
    // - TAG_ONE_TURN_EFFECT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t01] Jade Golem - COST:1 [ATK:1/HP:1]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t02] Jade Golem - COST:2 [ATK:2/HP:2]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t03] Jade Golem - COST:3 [ATK:3/HP:3]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t04] Jade Golem - COST:4 [ATK:4/HP:4]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t05] Jade Golem - COST:5 [ATK:5/HP:5]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t06] Jade Golem - COST:6 [ATK:6/HP:6]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t07] Jade Golem - COST:7 [ATK:7/HP:7]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t08] Jade Golem - COST:8 [ATK:8/HP:8]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t09] Jade Golem - COST:9 [ATK:9/HP:9]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t10] Jade Golem - COST:10 [ATK:10/HP:10]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t11] Jade Golem - COST:10 [ATK:11/HP:11]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t12] Jade Golem - COST:10 [ATK:12/HP:12]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t13] Jade Golem - COST:10 [ATK:13/HP:13]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t14] Jade Golem - COST:10 [ATK:14/HP:14]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t15] Jade Golem - COST:10 [ATK:15/HP:15]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t16] Jade Golem - COST:10 [ATK:16/HP:16]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t17] Jade Golem - COST:10 [ATK:17/HP:17]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t18] Jade Golem - COST:10 [ATK:18/HP:18]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t19] Jade Golem - COST:10 [ATK:19/HP:19]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t20] Jade Golem - COST:10 [ATK:20/HP:20]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t21] Jade Golem - COST:10 [ATK:21/HP:21]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t22] Jade Golem - COST:10 [ATK:22/HP:22]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t23] Jade Golem - COST:10 [ATK:23/HP:23]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t24] Jade Golem - COST:10 [ATK:24/HP:24]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t25] Jade Golem - COST:10 [ATK:25/HP:25]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t26] Jade Golem - COST:10 [ATK:26/HP:26]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t27] Jade Golem - COST:10 [ATK:27/HP:27]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t28] Jade Golem - COST:10 [ATK:28/HP:28]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t29] Jade Golem - COST:10 [ATK:29/HP:29]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [CFM_712_t30] Jade Golem - COST:10 [ATK:30/HP:30]
    // - Set: GANGS
    // --------------------------------------------------------
    // RefTag:
    // - JADE_GOLEM = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_752e] Smuggling - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: +3/+3 from Stolen Goods.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_753e] Smuggling - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: +1/+1 from Grimestreet Outfitter.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_754e] Smuggling - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Increased stats from Grimy Gadgeteer.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_755e] Smuggling - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: +1/+1 from Grimestreet Pawnbroker.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_816e] Get Big - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: +2/+2.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_851e] The Scoop - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [CFM_853e] Smuggling - COST:0
    // - Set: GANGS
    // --------------------------------------------------------
    // Text: +1/+1 from Grimestreet Smuggler.
    // --------------------------------------------------------
}

void GangsCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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