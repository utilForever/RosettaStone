// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/CardSets/GvgCardsGen.hpp>

using namespace RosettaStone::SimpleTasks;

namespace RosettaStone
{
using PlayReqs = std::map<PlayReq, int>;
using ChooseCardIDs = std::vector<std::string>;
using Entourages = std::vector<std::string>;
using TaskList = std::vector<std::shared_ptr<ITask>>;
using EntityTypeList = std::vector<EntityType>;
using SelfCondList = std::vector<std::shared_ptr<SelfCondition>>;
using EffectList = std::vector<std::shared_ptr<IEffect>>;

void GvgCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
}

void GvgCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
}

void GvgCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
}

void GvgCardsGen::AddDruidNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GvgCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
}

void GvgCardsGen::AddHunterNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GvgCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
}

void GvgCardsGen::AddMageNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GvgCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
}

void GvgCardsGen::AddPaladinNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GvgCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
}

void GvgCardsGen::AddPriestNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GvgCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
}

void GvgCardsGen::AddRogueNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GvgCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
}

void GvgCardsGen::AddShamanNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GvgCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
}

void GvgCardsGen::AddWarlockNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GvgCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
}

void GvgCardsGen::AddWarriorNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GvgCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
}

void GvgCardsGen::AddNeutralNonCollect(std::map<std::string, CardDef>& cards)
{
}

void GvgCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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
