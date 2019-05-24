// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/CardSets/HoFCardsGen.hpp>
#include <Rosetta/Tasks/SimpleTasks/ControlTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DiscardTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DrawOpTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/DrawTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/RandomTask.hpp>

using namespace RosettaStone::SimpleTasks;

namespace RosettaStone
{
void HoFCardsGen::AddHeroes(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddHeroPowers(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddDruid(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddDruidNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddHunter(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddHunterNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddMage(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddMageNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddPaladin(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddPaladinNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddPriest(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddPriestNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddRogue(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddRogueNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddShaman(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddShamanNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddWarlock(std::map<std::string, Power>& cards)
{
    Power power;

    // --------------------------------------- MINION - WARLOCK
    // [EX1_310] Doomguard - COST:5 [ATK:5/HP:7]
    // - Race: Demon, Set: HoF, Rarity: Rare
    // --------------------------------------------------------
    // Text: <b>Charge</b>. <b>Battlecry:</b> Discard two random cards.
    // --------------------------------------------------------
    // GameTag:
    // - CHARGE = 1
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new RandomTask(EntityType::HAND, 2));
    power.AddPowerTask(new DiscardTask(EntityType::STACK));
    cards.emplace("EX1_310", power);
}

void HoFCardsGen::AddWarlockNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddWarrior(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddWarriorNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddNeutral(std::map<std::string, Power>& cards)
{
    Power power;

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_016] Sylvanas Windrunner - COST:6 [ATK:5/HP:5]
    // - Set: HoF, Rarity: Legendary
    // --------------------------------------------------------
    // Text: <b>Deathrattle:</b> Take
    //       control of a random
    //       enemy minion.
    // --------------------------------------------------------
    // GameTag:
    // - ELITE = 1
    // - DEATHRATTLE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddDeathrattleTask(new RandomTask(EntityType::ENEMY_MINIONS, 1));
    power.AddDeathrattleTask(new ControlTask(EntityType::STACK));
    cards.emplace("EX1_016", power);

    // --------------------------------------- MINION - NEUTRAL
    // [EX1_050] Coldlight Oracle - COST:3 [ATK:2/HP:2]
    // - Faction: Neutral, Set: Core, Rarity: Free
    // --------------------------------------------------------
    // Text: <b>Battlecry:</b> Each player draws 2 cards.
    // --------------------------------------------------------
    // GameTag:
    // - BATTLECRY = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DrawTask(2));
    power.AddPowerTask(new DrawOpTask(2));
    cards.emplace("EX1_050", power);
}

void HoFCardsGen::AddNeutralNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddAll(std::map<std::string, Power>& cards)
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
}  // namespace RosettaStone
