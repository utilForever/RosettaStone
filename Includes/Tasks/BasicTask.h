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
        constexpr size_t NUM_ADD = 0;
        constexpr size_t NUM_SUB = 1;
        constexpr size_t NUM_SYNC = 2;

        constexpr size_t MANA_TOTAL = 0;
        constexpr size_t MANA_EXIST = 1;

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

        TaskMeta RawModifyMana(User& user, size_t numMode, size_t manaMode, BYTE object);
        Task ModifyManaTask(size_t numMode, size_t manaMode, BYTE object);
        Task ModifyManaByRef(size_t numMode, size_t manaMode, const BYTE& object);

        TaskMeta RawModifyHealth(User& user, Card* card, BYTE damage);
        Task ModifyHealthTask(Card* card, BYTE damage);

        TaskMeta RawBrief(const User& current, const User& opponent);
        Task BriefTask();

        Task SelectMenuTask(TaskAgent& agent);

        Task SelectCardTask(TaskAgent& agent);

        Task SelectTargetTask(TaskAgent& agent);

        TaskMeta RawMulligan(User& current, std::function<TaskMeta()>&& meta);
        Task MulliganTask(TaskAgent& agent);

        TaskMeta RawGameEnd(User& current, User& opponent);
        Task GameEndTask();
    }
}

#endif //HEARTHSTONEPP_BASICTASK_H
