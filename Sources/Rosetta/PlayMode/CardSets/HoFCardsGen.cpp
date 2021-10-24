// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/Auras/AdaptiveCostEffect.hpp>
#include <Rosetta/PlayMode/Auras/AdaptiveEffect.hpp>
#include <Rosetta/PlayMode/CardSets/HoFCardsGen.hpp>
#include <Rosetta/PlayMode/Enchants/Enchants.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

using namespace RosettaStone::PlayMode::SimpleTasks;

namespace RosettaStone::PlayMode
{
using PlayReqs = std::map<PlayReq, int>;
using ChooseCardIDs = std::vector<std::string>;
using Entourages = std::vector<std::string>;
using TaskList = std::vector<std::shared_ptr<ITask>>;
using EntityTypeList = std::vector<EntityType>;
using SelfCondList = std::vector<std::shared_ptr<SelfCondition>>;
using RelaCondList = std::vector<std::shared_ptr<RelaCondition>>;
using EffectList = std::vector<std::shared_ptr<IEffect>>;

void HoFCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
    (void)cards;
}

void HoFCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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
