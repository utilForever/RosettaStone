// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_TASK_QUEUE_HPP
#define ROSETTASTONE_PLAYMODE_TASK_QUEUE_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

#include <queue>
#include <stack>

namespace RosettaStone::PlayMode
{
//!
//! \brief TaskQueue class.
//!
//! This class stores several tasks into stack to run in order.
//!
class TaskQueue
{
 public:
    //! Default constructor.
    TaskQueue() = default;

    //! Returns the current queue.
    //! \return The current queue.
    std::queue<std::unique_ptr<ITask>>& GetCurrentQueue();

    //! Returns flag that indicates task queue is empty.
    //! \return Flag that indicates task queue is empty.
    bool IsEmpty();

    //! Starts the event.
    void StartEvent();

    //! Ends the event.
    void EndEvent();

    //! Enqueues the task.
    //! \param task The task to enqueue.
    void Enqueue(std::unique_ptr<ITask> task);

    //! Processes the task.
    //! \return The result of task processing.
    TaskStatus Process();

 private:
    std::stack<std::queue<std::unique_ptr<ITask>>> m_eventStack;
    std::queue<std::unique_ptr<ITask>> m_baseQueue;

    bool m_eventFlag = false;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_TASK_QUEUE_HPP
