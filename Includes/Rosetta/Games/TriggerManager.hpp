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
class Player;

//!
//! \brief TriggerManager class.
//!
//! This class monitors trigger and invokes method when a trigger is activated.
//!
class TriggerManager
{
 public:
    void OnStartTurnTrigger(Player* player, Entity* sender);

    void OnEndTurnTrigger(Player* player, Entity* sender);

    void OnHealTrigger(Player* player, Entity* sender);

    std::function<void(Player*, Entity*)> startTurnTrigger;
    std::function<void(Player*, Entity*)> endTurnTrigger;
    std::function<void(Player*, Entity*)> healTrigger;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_TRIGGER_MANAGER_HPP
