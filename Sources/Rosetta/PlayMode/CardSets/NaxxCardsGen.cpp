// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/NaxxCardsGen.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks.hpp>

using namespace RosettaStone::PlayMode::SimpleTasks;

namespace RosettaStone::PlayMode
{
using TagValues = std::vector<TagValue>;

void NaxxCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void NaxxCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void NaxxCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------ SPELL - DRUID
    // [FP1_019] Poison Seeds - COST:4
    // - Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: Destroy all minions and summon 2/2 Treants
    //       to replace them.
    // --------------------------------------------------------
}

void NaxxCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- MINION - DRUID
    // [FP1_019t] Treant (*) - COST:1 [ATK:2/HP:2]
    // - Set: Naxx
    // --------------------------------------------------------
}

void NaxxCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    Power power;

    // ---------------------------------------- MINION - HUNTER
    // [FP1_011] Webspinner - COST:1 [ATK:1/HP:1]
    // - Race: Beast, Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Add a random Beast card
    //       to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(std::make_shared<RandomMinionTask>(TagValues{
        { GameTag::CARDRACE, static_cast<int>(Race::BEAST), RelaSign::EQ } }));
    power.AddDeathrattleTask(
        std::make_shared<AddStackToTask>(EntityType::HAND));
    cards.emplace("FP1_011", CardDef(power));
}

void NaxxCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void NaxxCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    // ------------------------------------------- SPELL - MAGE
    // [FP1_018] Duplicate - COST:3
    // - Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When a friendly minion dies,
    //       put 2 copies of it into your hand.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
}

void NaxxCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void NaxxCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- SPELL - PALADIN
    // [FP1_020] Avenge - COST:1
    // - Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Secret:</b> When one of your minions dies,
    //       give a random friendly minion +3/+2.
    // --------------------------------------------------------
    // GameTag:
    // - SECRET = 1
    // --------------------------------------------------------
}

void NaxxCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------- ENCHANTMENT - PALADIN
    // [FP1_020e] Vengeance (*) - COST:0
    // - Set: Naxx
    // --------------------------------------------------------
    // Text: +3/+2.
    // --------------------------------------------------------
}

void NaxxCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    // ---------------------------------------- MINION - PRIEST
    // [FP1_023] Dark Cultist - COST:3 [ATK:3/HP:4]
    // - Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Give a random friendly minion
    //       +3 Health.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
}

void NaxxCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------- ENCHANTMENT - PRIEST
    // [FP1_023e] Power of the Ziggurat (*) - COST:0
    // - Set: Naxx
    // --------------------------------------------------------
    // Text: +3 Health.
    // --------------------------------------------------------
}

void NaxxCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- MINION - ROGUE
    // [FP1_026] Anub'ar Ambusher - COST:4 [ATK:5/HP:5]
    // - Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Return a random friendly minion
    //       to your hand.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
}

void NaxxCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void NaxxCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    // ----------------------------------------- SPELL - SHAMAN
    // [FP1_025] Reincarnate - COST:2
    // - Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: Destroy a minion,
    //       then return it to life with full Health.
    // --------------------------------------------------------
    // PlayReq:
    // - REQ_TARGET_TO_PLAY = 0
    // - REQ_MINION_TARGET = 0
    // --------------------------------------------------------
}

void NaxxCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void NaxxCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - WARLOCK
    // [FP1_022] Voidcaller - COST:4 [ATK:3/HP:4]
    // - Race: Demon, Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Put a random Demon
    //       from your hand into the battlefield.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
}

void NaxxCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void NaxxCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- WEAPON - WARRIOR
    // [FP1_021] Death's Bite - COST:4 [ATK:4/HP:0]
    // - Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Deal 1 damage to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - DURABILITY = 2
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
}

void NaxxCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
    // Do nothing
}

void NaxxCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - NEUTRAL
    // [FP1_001] Zombie Chow - COST:1 [ATK:2/HP:3]
    // - Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Restore 5 Health to the enemy hero.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_002] Haunted Creeper - COST:2 [ATK:1/HP:2]
    // - Race: Beast, Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon two 1/1 Spectral Spiders.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_003] Echoing Ooze - COST:2 [ATK:1/HP:2]
    // - Set: Naxx, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Summon an exact copy
    //       of this minion at the end of the turn.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_004] Mad Scientist - COST:2 [ATK:2/HP:2]
    // - Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Put a <b>Secret</b>
    //       from your deck into the battlefield.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    // RefTag:
    // - SECRET = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_005] Shade of Naxxramas - COST:3 [ATK:2/HP:2]
    // - Set: Naxx, Rarity: Epic
    // --------------------------------------------------------
    // Text: <b>Stealth.</b>
    //       At the start of your turn, gain +1/+1.
    // --------------------------------------------------------
    // GameTag:
    // - STEALTH = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_007] Nerubian Egg - COST:2 [ATK:0/HP:2]
    // - Set: Naxx, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Summon a 4/4 Nerubian.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_008] Spectral Knight - COST:5 [ATK:4/HP:6]
    // - Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: Can't be targeted by spells or Hero Powers.
    // --------------------------------------------------------
    // GameTag:
    // - CANT_BE_TARGETED_BY_SPELLS = 1
    // - CANT_BE_TARGETED_BY_HERO_POWERS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_009] Deathlord - COST:3 [ATK:2/HP:8]
    // - Set: Naxx, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt. Deathrattle:</b> Your opponent
    //       puts a minion from their deck into the battlefield.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_010] Maexxna - COST:6 [ATK:2/HP:8]
    // - Race: Beast, Set: Naxx, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Poisonous</b>
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - POISONOUS = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_012] Sludge Belcher - COST:5 [ATK:3/HP:5]
    // - Set: Naxx, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Taunt Deathrattle:</b> Summon a 1/2 Slime
    //       with <b>Taunt</b>.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_013] Kel'Thuzad - COST:8 [ATK:6/HP:8]
    // - Set: Naxx, Rarity: Legendary
    // --------------------------------------------------------
    // Text: At the end of each turn,
    //       summon all friendly minions that died this turn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_014] Stalagg - COST:5 [ATK:7/HP:4]
    // - Set: Naxx, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> If Feugen also died this game,
    //       summon Thaddius.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_015] Feugen - COST:5 [ATK:4/HP:7]
    // - Set: Naxx, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> If Stalagg also died this game,
    //       summon Thaddius.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_016] Wailing Soul - COST:4 [ATK:3/HP:5]
    // - Set: Naxx, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Battlecry: Silence</b> your other minions.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    // RefTag:
    // - SILENCE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_017] Nerub'ar Weblord - COST:2 [ATK:1/HP:4]
    // - Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: Minions with <b>Battlecry</b> cost (2) more.
    // --------------------------------------------------------
    // GameTag:
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_024] Unstable Ghoul - COST:2 [ATK:1/HP:3]
    // - Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Taunt</b>. <b>Deathrattle:</b> Deal 1 damage
    //       to all minions.
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_027] Stoneskin Gargoyle - COST:3 [ATK:1/HP:4]
    // - Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: At the start of your turn,
    //       restore this minion to full Health.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_028] Undertaker - COST:1 [ATK:1/HP:2]
    // - Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: Whenever you summon a minion with <b>Deathrattle</b>,
    //       gain +1 Attack.
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_029] Dancing Swords - COST:3 [ATK:4/HP:4]
    // - Set: Naxx, Rarity: Common
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Your opponent draws a card.
    // --------------------------------------------------------
    // GameTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_030] Loatheb - COST:5 [ATK:5/HP:5]
    // - Set: Naxx, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Enemy spells cost (5) more next turn.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_031] Baron Rivendare - COST:4 [ATK:1/HP:7]
    // - Set: Naxx, Rarity: Legendary
    // --------------------------------------------------------
    // Text: Your minions trigger their <b>Deathrattles</b> twice.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - AURA = 1
    // --------------------------------------------------------
    // RefTag:
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
}

void NaxxCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - NEUTRAL
    // [FP1_002t] Spectral Spider (*) - COST:1 [ATK:1/HP:1]
    // - Set: Naxx
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [FP1_005e] Consume (*) - COST:0
    // - Set: Naxx
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_006] Deathcharger (*) - COST:1 [ATK:2/HP:3]
    // - Set: Naxx
    // --------------------------------------------------------
    // Text: <b>Charge. Deathrattle:</b> Deal 3 damage to your hero.
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_007t] Nerubian (*) - COST:4 [ATK:4/HP:4]
    // - Set: Naxx
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_012t] Slime (*) - COST:1 [ATK:1/HP:2]
    // - Set: Naxx
    // --------------------------------------------------------
    // Text: <b>Taunt</b>
    // --------------------------------------------------------
    // GameTag:
    // - TAUNT = 1
    // --------------------------------------------------------

    // --------------------------------------- MINION - NEUTRAL
    // [FP1_014t] Thaddius (*) - COST:10 [ATK:11/HP:11]
    // - Set: Naxx
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [FP1_028e] Darkness Calls (*) - COST:0
    // - Set: Naxx
    // --------------------------------------------------------
    // Text: Increased stats.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [FP1_030e] Necrotic Aura (*) - COST:0
    // - Set: Naxx
    // --------------------------------------------------------
    // Text: Your spells cost (5) more this turn.
    // --------------------------------------------------------
}

void NaxxCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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