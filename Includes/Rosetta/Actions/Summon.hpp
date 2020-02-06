// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_SUMMON_HPP
#define ROSETTASTONE_SUMMON_HPP

#include <Rosetta/Models/Minion.hpp>

namespace RosettaStone::Generic
{
//! Summons an minion on battlefield.
//! \param minion An minion to summon.
//! \param fieldPos The position of minion to summon.
//! \param summoner The summoner of minion.
void Summon(Minion* minion, int fieldPos, Entity* summoner);

//! Summons an minion that has reborn on battlefield.
//! \param minion An minion to summon.
void SummonReborn(Minion* minion);
}  // namespace RosettaStone::Generic

#endif  // ROSETTASTONE_SUMMON_HPP
