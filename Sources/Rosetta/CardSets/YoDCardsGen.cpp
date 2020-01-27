// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/CardSets/YoDCardsGen.hpp>

namespace RosettaStone
{
void YoDCardsGen::AddHeroes(PowersType& powers, PlayReqsType& playReqs,
                            EntouragesType& entourages)
{
}

void YoDCardsGen::AddHeroPowers(PowersType& powers, PlayReqsType& playReqs,
                                EntouragesType& entourages)
{
}

void YoDCardsGen::AddDruid(PowersType& powers, PlayReqsType& playReqs,
                           EntouragesType& entourages)
{
}

void YoDCardsGen::AddDruidNonCollect(PowersType& powers, PlayReqsType& playReqs,
                                     EntouragesType& entourages)
{
}

void YoDCardsGen::AddHunter(PowersType& powers, PlayReqsType& playReqs,
                            EntouragesType& entourages)
{
}

void YoDCardsGen::AddHunterNonCollect(PowersType& powers,
                                      PlayReqsType& playReqs,
                                      EntouragesType& entourages)
{
}

void YoDCardsGen::AddMage(PowersType& powers, PlayReqsType& playReqs,
                          EntouragesType& entourages)
{
}

void YoDCardsGen::AddMageNonCollect(PowersType& powers, PlayReqsType& playReqs,
                                    EntouragesType& entourages)
{
}

void YoDCardsGen::AddPaladin(PowersType& powers, PlayReqsType& playReqs,
                             EntouragesType& entourages)
{
}

void YoDCardsGen::AddPaladinNonCollect(PowersType& powers,
                                       PlayReqsType& playReqs,
                                       EntouragesType& entourages)
{
}

void YoDCardsGen::AddPriest(PowersType& powers, PlayReqsType& playReqs,
                            EntouragesType& entourages)
{
}

void YoDCardsGen::AddPriestNonCollect(PowersType& powers,
                                      PlayReqsType& playReqs,
                                      EntouragesType& entourages)
{
}

void YoDCardsGen::AddRogue(PowersType& powers, PlayReqsType& playReqs,
                           EntouragesType& entourages)
{
}

void YoDCardsGen::AddRogueNonCollect(PowersType& powers, PlayReqsType& playReqs,
                                     EntouragesType& entourages)
{
}

void YoDCardsGen::AddShaman(PowersType& powers, PlayReqsType& playReqs,
                            EntouragesType& entourages)
{
}

void YoDCardsGen::AddShamanNonCollect(PowersType& powers,
                                      PlayReqsType& playReqs,
                                      EntouragesType& entourages)
{
}

void YoDCardsGen::AddWarlock(PowersType& powers, PlayReqsType& playReqs,
                             EntouragesType& entourages)
{
}

void YoDCardsGen::AddWarlockNonCollect(PowersType& powers,
                                       PlayReqsType& playReqs,
                                       EntouragesType& entourages)
{
}

void YoDCardsGen::AddWarrior(PowersType& powers, PlayReqsType& playReqs,
                             EntouragesType& entourages)
{
}

void YoDCardsGen::AddWarriorNonCollect(PowersType& powers,
                                       PlayReqsType& playReqs,
                                       EntouragesType& entourages)
{
}

void YoDCardsGen::AddNeutral(PowersType& powers, PlayReqsType& playReqs,
                             EntouragesType& entourages)
{
}

void YoDCardsGen::AddNeutralNonCollect(PowersType& powers,
                                       PlayReqsType& playReqs,
                                       EntouragesType& entourages)
{
}

void YoDCardsGen::AddAll(PowersType& powers, PlayReqsType& playReqs,
                         EntouragesType& entourages)
{
    AddHeroes(powers, playReqs, entourages);
    AddHeroPowers(powers, playReqs, entourages);

    AddDruid(powers, playReqs, entourages);
    AddDruidNonCollect(powers, playReqs, entourages);

    AddHunter(powers, playReqs, entourages);
    AddHunterNonCollect(powers, playReqs, entourages);

    AddMage(powers, playReqs, entourages);
    AddMageNonCollect(powers, playReqs, entourages);

    AddPaladin(powers, playReqs, entourages);
    AddPaladinNonCollect(powers, playReqs, entourages);

    AddPriest(powers, playReqs, entourages);
    AddPriestNonCollect(powers, playReqs, entourages);

    AddRogue(powers, playReqs, entourages);
    AddRogueNonCollect(powers, playReqs, entourages);

    AddShaman(powers, playReqs, entourages);
    AddShamanNonCollect(powers, playReqs, entourages);

    AddWarlock(powers, playReqs, entourages);
    AddWarlockNonCollect(powers, playReqs, entourages);

    AddWarrior(powers, playReqs, entourages);
    AddWarriorNonCollect(powers, playReqs, entourages);

    AddNeutral(powers, playReqs, entourages);
    AddNeutralNonCollect(powers, playReqs, entourages);
}
}  // namespace RosettaStone
