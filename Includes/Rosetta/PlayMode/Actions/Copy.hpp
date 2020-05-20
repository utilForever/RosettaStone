// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_COPY_HPP
#define ROSETTASTONE_PLAYMODE_COPY_HPP

#include <Rosetta/Common/Enums/CardEnums.hpp>
#include <Rosetta/PlayMode/Models/Playable.hpp>

namespace RosettaStone::PlayMode::Generic
{
//! Copies the entity to target zone.
//! \param player The owner of source entity.
//! \param source The source entity to copy.
//! \param targetZone The target zone to copy.
//! \param deathrattle The flag to indicate whether copy operation via
//! deathrattle power.
Playable* Copy(Player* player, Playable* source, ZoneType targetZone,
               bool deathrattle = false);
}  // namespace RosettaStone::PlayMode::Generic

#endif  // ROSETTASTONE_PLAYMODE_COPY_HPP
