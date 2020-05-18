// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYMODE_TRIGGER_EVENT_HANDLER_HPP
#define ROSETTASTONE_PLAYMODE_TRIGGER_EVENT_HANDLER_HPP

#include <functional>

namespace RosettaStone::PlayMode
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

    //! Default constructor.
    TriggerEventHandler();

    //! Constructs trigger event handler with given \p func.
    //! \param func A functor to run.
    explicit TriggerEventHandler(Func func);

    //! Default destructor.
    ~TriggerEventHandler() noexcept = default;

    //! Default copy constructor.
    TriggerEventHandler(const TriggerEventHandler& handler) = default;

    //! Default move constructor.
    TriggerEventHandler(TriggerEventHandler&& handler) noexcept = default;

    //! Copy assignment operator.
    //! \param handler A trigger event handler to assign.
    TriggerEventHandler& operator=(const TriggerEventHandler& handler);

    //! Move assignment operator.
    //! \param handler A trigger event handler to assign.
    TriggerEventHandler& operator=(TriggerEventHandler&& handler) noexcept;

    //! Operator overloading: operator().
    //! \param entity The argument of functor.
    void operator()(Entity* entity) const;

    //! Operator overloading: operator==.
    //! \param handler A trigger event handler to check equality.
    bool operator==(const TriggerEventHandler& handler) const;

    //! Operator overloading: operator!=.
    bool operator!=(std::nullptr_t) const;

    int id;
    static int counter;
    bool toBeRemoved = false;

 private:
    Func m_func;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_TRIGGER_EVENT_HANDLER_HPP