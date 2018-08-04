/*************************************************************************
> File Name: Wrapper.h
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Task Wrapper for some utilities
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_WRAPPER_H
#define HEARTHSTONEPP_WRAPPER_H

#include <Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
class DoBothPlayer : public ITask
{
 public:
    DoBothPlayer(const ITask& task);
    TaskID GetTaskID() const override;

 private:
    const ITask& m_task;
    MetaData Impl(Player& player1, Player& player2) override;
};

class DoUntil : public ITask
{
 public:
    DoUntil(const ITask& task,
            std::function<bool(const TaskMeta&)>&& condition);
    TaskID GetTaskID() const override;

 private:
    const ITask& m_task;
    std::function<bool(const TaskMeta&)> m_condition;

    MetaData Impl(Player& player1, Player& player2) override;
};
}  // namespace Hearthstonepp::BasicTasks
#endif  // HEARTHSTONEPP_WRAPPER_H
