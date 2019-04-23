// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_TARGETING_HPP
#define ROSETTASTONE_TARGETING_HPP

#include <Rosetta/Models/Character.hpp>
#include <Rosetta/Models/Entity.hpp>

namespace RosettaStone::Generic
{
//! Determines a source needs a target.
//! \param source A source entity.
//! \return true if a source needs a target, false otherwise.
bool IsSourceNeedsTarget(Entity* source);

//! Determines whether the specified character is a valid target.
//! \param source A source entity.
//! \param target The specified target.
//! \return true if the specified target is valid, false otherwise.
bool IsValidTarget(Entity* source, Entity* target);

//! Gets the valid play targets.
//! This method defaults to targeting in the context of spells/hero powers
//! \param source A source entity.
//! \return A list of valid play targets.
std::vector<Character*> GetValidTargets(Entity* source);

//! Calculates if a target is valid by testing the game state for each hardcoded
//! requirement.
//! \param source A source entity.
//! \param target The proposed target.
//! \return true if the proposed target is valid, false otherwise.
bool CheckRequirements(Entity* source, Character* target);
}  // namespace RosettaStone::Generic

#endif  // ROSETTASTONE_TARGETING_HPP
