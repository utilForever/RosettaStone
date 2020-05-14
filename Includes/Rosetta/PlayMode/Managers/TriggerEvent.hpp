// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYMODE_TRIGGER_EVENT_HPP
#define ROSETTASTONE_PLAYMODE_TRIGGER_EVENT_HPP

#include <Rosetta/PlayMode/Managers/TriggerEventHandler.hpp>

#include <memory>
#include <vector>

namespace RosettaStone::PlayMode
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
    //! Adds a trigger event handler.
    //! \param handler A trigger event handler to add.
    void AddHandler(const TriggerEventHandler& handler);

    //! Removes a trigger event handler.
    //! \param handler A trigger event handler to remove.
    void RemoveHandler(const TriggerEventHandler& handler);

    //! Operator overloading: operator().
    //! \param entity The argument of functor.
    void operator()(Entity* entity);

    //! Operator overloading: operator+=.
    //! \param handler A trigger event handler to add.
    TriggerEvent& operator+=(const TriggerEventHandler& handler);

    //! Operator overloading: operator-=.
    //! \param handler A trigger event handler to remove.
    TriggerEvent& operator-=(const TriggerEventHandler& handler);

 private:
    //! Notifies a list of trigger handlers to run.
    //! \param entity The argument of functor.
    void NotifyHandlers(Entity* entity);

    std::vector<std::unique_ptr<TriggerEventHandler>> m_handlers;
    bool m_isNotifying = false;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_TRIGGER_EVENT_HPP