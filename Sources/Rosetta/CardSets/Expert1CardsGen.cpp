// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/CardSets/Expert1CardsGen.hpp>
#include <Rosetta/Tasks/SimpleTasks/DamageTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/SetGameTagTask.hpp>

using namespace RosettaStone::SimpleTasks;

namespace RosettaStone
{
void Expert1CardsGen::AddHeroes(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddHeroPowers(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddDruid(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddDruidNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddHunter(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddHunterNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddMage(std::map<std::string, Power>& cards)
{
    Power power;

    // ------------------------------------------- SPELL - MAGE
    // [CS2_028] Blizzard - COST:6
    // - Faction: Neutral, Set: Expert1, Rarity: Rare
    // --------------------------------------------------------
    // Text: Deal $2 damage to all enemy minions and <b>Freeze</b> them.
    // --------------------------------------------------------
    // GameTag:
    // - FREEZE = 1
    // --------------------------------------------------------
    power.ClearData();
    power.AddPowerTask(new DamageTask(EntityType::ENEMY_FIELD, 2));
    power.AddPowerTask(
        new SetGameTagTask(EntityType::ENEMY_FIELD, GameTag::FROZEN, 1));
    cards.emplace("CS2_028", power);
}

void Expert1CardsGen::AddMageNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddPaladin(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddPaladinNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddPriest(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddPriestNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddRogue(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddRogueNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddShaman(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddShamanNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddWarlock(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddWarlockNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddWarrior(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddWarriorNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddNeutral(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddNeutralNonCollect(std::map<std::string, Power>& cards)
{
    (void)cards;
}

void Expert1CardsGen::AddAll(std::map<std::string, Power>& cards)
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
