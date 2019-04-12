// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_TRIGGER_HPP
#define ROSETTASTONE_TRIGGER_HPP

#include <Rosetta/Enums/TriggerEnums.hpp>

namespace RosettaStone
{
//!
//! \brief Trigger class.
//!
//! This class represents triggered effects that are effects that activate in
//! response to specific events.
//!
class Trigger
{
 public:
    //! Constructs trigger with given \p type.
    //! \param type The trigger type.
    Trigger(TriggerType type);

 private:
    TriggerType m_triggerType = TriggerType::NONE;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_EFFECT_HPP
