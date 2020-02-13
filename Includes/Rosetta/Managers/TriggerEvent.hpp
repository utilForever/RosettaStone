// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_TRIGGER_EVENT_HPP
#define ROSETTASTONE_TRIGGER_EVENT_HPP

#include <Rosetta/Managers/TriggerEventHandler.hpp>

#include <memory>
#include <vector>

namespace RosettaStone
{
class Entity;

//!
//! \brief TriggerEvent class.
//!
//! This is an event class for trigger.
//!
class TriggerEvent
{
 public:
    void AddHandler(const TriggerEventHandler& handler);
    void RemoveHandler(const TriggerEventHandler& handler);

    void operator()(Entity* entity) const;

    TriggerEvent& operator+=(const TriggerEventHandler& handler);
    TriggerEvent& operator-=(const TriggerEventHandler& handler);

 private:
    void NotifyHandlers(Entity* entity) const;

    std::vector<std::unique_ptr<TriggerEventHandler>> m_handlers;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_TRIGGER_EVENT_HPP