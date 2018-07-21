/*************************************************************************
> File Name: Draw.h
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose:
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_DRAW_H
#define HEARTHSTONEPP_DRAW_H

#include <Tasks/TaskAgent.h>
#include <Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
class DrawTask : public ITask
{
 public:
    DrawTask(size_t num, TaskAgent& agent);
    TaskID GetTaskID() const override;

 private:
    size_t m_num;
    TaskAgent& m_agent;

    MetaData Impl(Player& player1, Player& player2) const override;
};

class DrawCardTask : public ITask
{
 public:
    DrawCardTask(Card* card);
    TaskID GetTaskID() const override;

 private:
    Entity* m_entity;
    MetaData Impl(Player& player1, Player& player2) const override;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_DRAW_H
