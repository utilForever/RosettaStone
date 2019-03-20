// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_TARGETING_HPP
#define ROSETTASTONE_TARGETING_HPP

#include <Rosetta/Models/Entity.hpp>

namespace RosettaStone::Generic
{
bool IsValidTarget(Entity* source, Entity* target);
}  // namespace RosettaStone::Generic

#endif  // ROSETTASTONE_TARGETING_HPP
