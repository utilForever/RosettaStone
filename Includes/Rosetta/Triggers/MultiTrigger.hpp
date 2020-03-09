// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_MULTI_TRIGGER_HPP
#define ROSETTASTONE_MULTI_TRIGGER_HPP

#include <Rosetta/Triggers/Trigger.hpp>

namespace RosettaStone
{
//!
//! \brief MultiTrigger class.
//!
//! This class stores a list of trigger to support in a turn based cards.
//! e.g. Dragon Soul, Chenvaala.
//!
class MultiTrigger : public Trigger
{
 public:
    //! Constructs multi trigger with given \p triggers.
    //! \param triggers A list of trigger.
    MultiTrigger(std::vector<std::shared_ptr<Trigger>> triggers);

 private:
    std::vector<std::shared_ptr<Trigger>> m_triggers;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_MULTI_TRIGGER_HPP
