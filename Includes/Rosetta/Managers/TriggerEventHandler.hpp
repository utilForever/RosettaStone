// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_TRIGGER_EVENT_HANDLER_HPP
#define ROSETTASTONE_TRIGGER_EVENT_HANDLER_HPP

#include <functional>

namespace RosettaStone
{
class Entity;

//!
//! \brief TriggerEventHandler class.
//!
//! This is an event handler class for trigger.
//!
class TriggerEventHandler
{
 public:
    using Func = std::function<void(Entity*)>;

    TriggerEventHandler();
    TriggerEventHandler(const Func& func);

    void operator()();

    bool operator==(const TriggerEventHandler& handler);
    bool operator!=(std::nullptr_t);

    int id;
    static int counter;

 private:
    Func m_func;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_TRIGGER_EVENT_HANDLER_HPP