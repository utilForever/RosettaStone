/*************************************************************************
> File Name: Tasks.h
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Task Unit for GameAgent
> Created Time: 2018/05/20
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_TASKS_H
#define HEARTHSTONEPP_TASKS_H

#include <Enums/CardEnums.h>
#include <Managers/Player.h>
#include <Tasks/MetaData.h>
#include <Tasks/TaskMeta.h>

#include <functional>

namespace Hearthstonepp
{
// Interface of Tasks.
// Method `Run` call virtual method `Impl` and return GameStatus TaskMeta
class ITask
{
 public:
    template <typename T>
    static inline constexpr bool isTask =
        std::is_convertible_v<std::decay_t<T>, ITask>;

    MetaData Run(Player& player1, Player& player2);
    MetaData Run(Player& player1, Player& player2, TaskMeta& meta);

    virtual TaskID GetTaskID() const;

 private:
    virtual MetaData Impl(Player& player1, Player& player2) = 0;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_TASKS_H
