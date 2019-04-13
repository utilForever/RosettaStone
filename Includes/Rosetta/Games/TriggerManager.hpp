// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_TRIGGER_MANAGER_HPP
#define ROSETTASTONE_TRIGGER_MANAGER_HPP

#include <functional>

namespace RosettaStone
{
class Entity;

//!
//! \brief TriggerManager class.
//!
//! This class monitors trigger and invokes method when a trigger is activated.
//!
class TriggerManager
{
 public:
    void OnStartTurnTrigger(Entity* sender);

    std::function<void(Entity*)> startTurnTrigger;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_TRIGGER_MANAGER_HPP
