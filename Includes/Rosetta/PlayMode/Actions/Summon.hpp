// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_SUMMON_HPP
#define ROSETTASTONE_PLAYMODE_SUMMON_HPP

#include <Rosetta/PlayMode/Models/Minion.hpp>

namespace RosettaStone::PlayMode::Generic
{
//! Summons an minion on battlefield.
//! \param minion An minion to summon.
//! \param fieldPos The position of minion to summon.
//! \param summoner The summoner of minion.
void Summon(Minion* minion, int fieldPos, Entity* summoner);

//! Summons an minion that has reborn on battlefield.
//! \param minion An minion to summon.
void SummonReborn(Minion* minion);

//! Summons appendage minions for Colossal on battlefield.
//! \param appendages Appendage minions to summon.
//! \param fieldPos The position of minion to summon.
//! \param summoner The summoner of minion.
void SummonAppendages(
    const std::vector<std::tuple<std::string, SummonSide>>& appendages,
    Entity* summoner);
}  // namespace RosettaStone::PlayMode::Generic

#endif  // ROSETTASTONE_PLAYMODE_SUMMON_HPP
