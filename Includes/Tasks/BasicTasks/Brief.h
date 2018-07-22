/*************************************************************************
> File Name: Brief.h
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implement Brief Task, Return GameStatus Immediately to GameInterface
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_BRIEF_H
#define HEARTHSTONEPP_BRIEF_H

#include <Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
// Briefing Game Status.
// TaskAgent send GameStatus to GameInterface immediately when meet BriefTask
class BriefTask : public ITask
{
 public:
    TaskID GetTaskID() const override;

 private:
    MetaData Impl(Player& player1, Player& player2) const override;
};
}  // namespace Hearthstonepp::BasicTasks

#endif  // HEARTHSTONEPP_BRIEF_H
