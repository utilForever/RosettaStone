// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_TASK_WRAPPER_HPP
#define HEARTHSTONEPP_TASK_WRAPPER_HPP

#include <hspp/Tasks/Tasks.hpp>

#include <functional>

namespace Hearthstonepp
{
//!
//! \brief DoBothPlayer class.
//!
//! This class represents the task that applies to both players.
//!
class DoBothPlayer : public ITask
{
 public:
    //! Constructs task with given \p task.
    //! \param task The task that applies to both players.
    DoBothPlayer(ITask&& task);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    MetaData Impl(Player& player) override;

    ITask& m_task;
};

//!
//! \brief DoUntil class.
//!
//! This class represents the task that is infinite-loop until completes.
//!
class DoUntil : public ITask
{
 public:
    //! Constructs task with given \p task and \p condition.
    //! \param task The task that is infinite-loop until completes.
    //! \param condition The condition under which the task completes.
    DoUntil(ITask&& task, std::function<bool(MetaData)>&& condition);

   //! Constructs task with given \p task and \p id.
   //! \param task The task that is infinite-loop until completes.
   //! \param id The condition whether returned TaskMeta::status is equal to id.
    DoUntil(ITask&& task, MetaData id);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    MetaData Impl(Player& player) override;

    ITask& m_task;
    std::function<bool(MetaData)> m_condition;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_TASK_WRAPPER_HPP
