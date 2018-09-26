#ifndef HEARTHSTONEPP_TASK_WRAPPER_H
#define HEARTHSTONEPP_TASK_WRAPPER_H

#include <Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
//!
//! \brief DoBothPlayer class.
//!
//! This class represents the task that applies to both players.
//!
class DoBothPlayer : public ITask
{
 public:
    //! Constructs task with given \p task (move constructor).
    //! \param task The task that applies to both players.
    DoBothPlayer(ITask&& task);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player1 The first player.
    //! \param player2 The second player.
    //! \return The result of task processing.
    MetaData Impl(Player& player1, Player& player2) override;

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
    //! Constructs task with given \p task (move constructor).
    //! \param task The task that is infinite-loop until completes.
    //! \param condition The condition under which the task completes.
    DoUntil(ITask&& task, std::function<bool(const TaskMeta&)>&& condition);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player1 The first player.
    //! \param player2 The second player.
    //! \return The result of task processing.
    MetaData Impl(Player& player1, Player& player2) override;

    ITask& m_task;
    std::function<bool(const TaskMeta&)> m_condition;
};
}  // namespace Hearthstonepp::BasicTasks
#endif  // HEARTHSTONEPP_WRAPPER_H
