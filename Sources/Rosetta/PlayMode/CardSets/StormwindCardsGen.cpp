// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/StormwindCardsGen.hpp>

namespace RosettaStone::PlayMode
{
void StormwindCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddDruidNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddPriestNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddRogueNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddShamanNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddDemonHunter(std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddDemonHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void StormwindCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    // --------------------------------------- MINION - NEUTRAL
    // [SW_079] Flightmaster Dungar - COST:3 [ATK:3/HP:3]
    // - Set: STORMWIND, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Choose a flightpath and go <b>Dormant.</b>
    //       Awaken with a bonus when you complete it!
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
}

void StormwindCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_079e4] Westfall Flight - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Dormant</b>. Summon a 2/2 Adventurer in 1 turn.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_079e5] Ironforge Flight - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Dormant</b>.
    //       Restore 10 health to your hero in 3 turns.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_079e6] Plaguelands Flight - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: <b>Dormant</b>. Deal 12 damage randomly split
    //       to enemies in 5 turns.
    // --------------------------------------------------------
    // GameTag:
    // - TRIGGER_VISUAL = 1
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [SW_079t] Westfall - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: In 1 turn, summon a 2/2 Adventurer with
    //       a random bonus effect.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [SW_079t2] Ironforge - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: In 3 turns, restore 10 Health to your hero.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_079t2e] Ironforge Flight - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: In 3 turns, restore 10 Health to your hero.
    // --------------------------------------------------------

    // ---------------------------------------- SPELL - NEUTRAL
    // [SW_079t3] Eastern Plaguelands - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: In 5 turns, deal 12 damage randomly split among enemies.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_079t3e] Plaguelands Flight - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: In 5 turns, deal 12 damage randomly split among enemies.
    // --------------------------------------------------------

    // ---------------------------------- ENCHANTMENT - NEUTRAL
    // [SW_079te] Westfall Flight - COST:0
    // - Set: STORMWIND
    // --------------------------------------------------------
    // Text: Next turn, summon a 2/2 Adventurer.
    // --------------------------------------------------------
}

void StormwindCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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

    AddNeutral(cards);
    AddNeutralNonCollect(cards);
}
}  // namespace RosettaStone::PlayMode