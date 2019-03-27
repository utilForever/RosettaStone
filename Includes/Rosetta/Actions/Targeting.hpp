// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_TARGETING_HPP
#define ROSETTASTONE_TARGETING_HPP

#include <Rosetta/Models/Entity.hpp>

namespace RosettaStone::Generic
{
//! Checks the target is valid.
//! \param source A source entity.
//! \param target A target entity.
//! \return true if the target is valid, false otherwise.
bool IsValidTarget(Entity* source, Entity* target);
}  // namespace RosettaStone::Generic

#endif  // ROSETTASTONE_TARGETING_HPP
