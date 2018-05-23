/*************************************************************************
> File Name: BasicTask.h
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implementation of Basic Task
> Created Time: 2018/05/20
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_BASICTASK_H
#define HEARTHSTONEPP_BASICTASK_H

#include <Tasks/TaskAgent.h>
#include <Tasks/TaskMeta.h>

#include <functional>

namespace Hearthstonepp
{
    namespace BasicTask
    {
        std::function<TaskMeta()>
        RequireMethod(TaskID request, BYTE userID, TaskAgent& agent);

        Task DoBothUser(Task&& task);

        Task DoUntil(Task&& task, std::function<bool(const TaskMeta&)>&& condition);

        TaskMeta RawUserSetting(User& current, User& opponent);
        Task UserSettingTask();

        TaskMeta RawSwapUser(User& current, User& opponent);
        Task SwapUserTask();

        TaskMeta RawShuffle(User& user);
        Task ShuffleTask();

        TaskMeta RawDraw(User& user, size_t num);
        Task DrawTask(size_t num);
    }
}

#endif //HEARTHSTONEPP_BASICTASK_H
