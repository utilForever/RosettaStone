// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_TRIGGERS_HPP
#define ROSETTASTONE_TRIGGERS_HPP

#include <Rosetta/Triggers/Trigger.hpp>

#include <string>

namespace RosettaStone
{
//!
//! \brief Triggers class.
//!
//! This class includes utility methods for trigger.
//!
class Triggers
{
 public:
    //! Trigger for enrage.
    //! \param enchantmentID The card ID of enchantment.
    static Trigger EnrageTrigger(std::string&& enchantmentID);
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_TRIGGERS_HPP