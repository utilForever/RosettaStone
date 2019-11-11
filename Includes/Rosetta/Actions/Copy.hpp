// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_COPY_HPP
#define ROSETTASTONE_COPY_HPP

#include <Rosetta/Enums/CardEnums.hpp>
#include <Rosetta/Models/Playable.hpp>

namespace RosettaStone::Generic
{
//! Copies the entity to target zone.
//! \param player The owner of source entity.
//! \param source The source entity to copy.
//! \param targetZone The target zone to copy.
//! \param deathrattle The flag to indicate whether copy operation via
//! deathrattle power.
Playable* Copy(Player* player, Playable* source, ZoneType targetZone,
               bool deathrattle = false);
}  // namespace RosettaStone::Generic

#endif  // ROSETTASTONE_COPY_HPP
