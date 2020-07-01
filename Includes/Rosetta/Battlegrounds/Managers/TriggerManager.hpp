// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_TRIGGER_MANAGER_HPP
#define ROSETTASTONE_BATTLEGROUNDS_TRIGGER_MANAGER_HPP

#include <Rosetta/Battlegrounds/Managers/TriggerEvent.hpp>

namespace RosettaStone::Battlegrounds
{
class Minion;

//!
//! \brief TriggerManager class.
//!
//! This class monitors trigger and invokes method when a trigger is activated.
//!
class TriggerManager
{
 public:
    //! Callback for trigger when minion is dead.
    //! \param sender An entity that is the source of trigger.
    void OnDeathTrigger(Minion& sender);

    TriggerEvent deathTrigger;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_TRIGGER_MANAGER_HPP
