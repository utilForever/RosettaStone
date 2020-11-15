// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/CardSets/DarkmoonFaireCardsGen.hpp>

namespace RosettaStone::PlayMode
{
void DarkmoonFaireCardsGen::AddHeroes(std::map<std::string, CardDef>& cards)
{
}

void DarkmoonFaireCardsGen::AddHeroPowers(std::map<std::string, CardDef>& cards)
{
}

void DarkmoonFaireCardsGen::AddDruid(std::map<std::string, CardDef>& cards)
{
}

void DarkmoonFaireCardsGen::AddDruidNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void DarkmoonFaireCardsGen::AddHunter(std::map<std::string, CardDef>& cards)
{
}

void DarkmoonFaireCardsGen::AddHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void DarkmoonFaireCardsGen::AddMage(std::map<std::string, CardDef>& cards)
{
}

void DarkmoonFaireCardsGen::AddMageNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void DarkmoonFaireCardsGen::AddPaladin(std::map<std::string, CardDef>& cards)
{
}

void DarkmoonFaireCardsGen::AddPaladinNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void DarkmoonFaireCardsGen::AddPriest(std::map<std::string, CardDef>& cards)
{
}

void DarkmoonFaireCardsGen::AddPriestNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void DarkmoonFaireCardsGen::AddRogue(std::map<std::string, CardDef>& cards)
{
}

void DarkmoonFaireCardsGen::AddRogueNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void DarkmoonFaireCardsGen::AddShaman(std::map<std::string, CardDef>& cards)
{
}

void DarkmoonFaireCardsGen::AddShamanNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void DarkmoonFaireCardsGen::AddWarlock(std::map<std::string, CardDef>& cards)
{
}

void DarkmoonFaireCardsGen::AddWarlockNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void DarkmoonFaireCardsGen::AddWarrior(std::map<std::string, CardDef>& cards)
{
}

void DarkmoonFaireCardsGen::AddWarriorNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void DarkmoonFaireCardsGen::AddDemonHunter(
    std::map<std::string, CardDef>& cards)
{
}

void DarkmoonFaireCardsGen::AddDemonHunterNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void DarkmoonFaireCardsGen::AddNeutral(std::map<std::string, CardDef>& cards)
{
}

void DarkmoonFaireCardsGen::AddNeutralNonCollect(
    std::map<std::string, CardDef>& cards)
{
}

void DarkmoonFaireCardsGen::AddAll(std::map<std::string, CardDef>& cards)
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