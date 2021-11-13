// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_ATTACK_HPP
#define ROSETTASTONE_PLAYMODE_ATTACK_HPP

#include <Rosetta/PlayMode/Models/Player.hpp>

namespace RosettaStone::PlayMode::Generic
{
//! Source character attacks target character.
//! \param player An owner of source character.
//! \param source A pointer to source character.
//! \param target A pointer to target character.
//! \param skipPrePhase The flag indicates whether it skips pre-phase.
void Attack(const Player* player, Character* source, Character* target,
            bool skipPrePhase);
}  // namespace RosettaStone::PlayMode::Generic

#endif  // ROSETTASTONE_PLAYMODE_ATTACK_HPP
