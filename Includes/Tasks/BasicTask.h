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

namespace Hearthstonepp::BasicTask
{
constexpr size_t NUM_ADD = 0;
constexpr size_t NUM_SUB = 1;
constexpr size_t NUM_SYNC = 2;

constexpr size_t MANA_TOTAL = 0;
constexpr size_t MANA_EXIST = 1;

// Write RequireTaskMeta to main channel of `agent`
// and wait for receiving meta data from side channel.
std::function<TaskMeta()> RequireMethod(TaskID request, BYTE userID, TaskAgent& agent);

// Call task both current user and opponent user
Task DoBothUser(Task&& task);

// Call task recursively until the condition satisfied
Task DoUntil(Task&& task, std::function<bool(const TaskMeta&)>&& condition);

// Return UserSettingTaskMeta, Set user id as order
TaskMeta RawUserSetting(User& current, User& opponent);
Task UserSettingTask();

// Return TaskMeta with TaskID::SWAP, Swap user
TaskMeta RawSwapUser(User& current, User& opponent);
Task SwapUserTask();

// Return TaskMeta with TaskID::SHUFFLE, Shuffle deck of `user`
TaskMeta RawShuffle(User& user);
// Call RawShuffle with current user
Task ShuffleTask();

// Return DrawTaskMeta, Draw `num` cards from deck of `user`
TaskMeta RawDraw(User& user, size_t num);
// Call RawDraw with current user
Task DrawTask(size_t num);

// Return ModifyManaTaskMeta, Modify `manaMode` with operator `numMode` and
// `object`
TaskMeta RawModifyMana(User& user, size_t numMode, size_t manaMode,
                       BYTE object);
// Call RawModifyMana with current user
Task ModifyManaTask(size_t numMode, size_t manaMode, BYTE object);
// Call RawModifyMana with current user and `object` by reference
Task ModifyManaByRef(size_t numMode, size_t manaMode, const BYTE& object);

// Return ModifyHealthTaskMeta, Substract health of `card` with `damage`,
// if Minion Exhausted, delete `card` from field of `user`
TaskMeta RawModifyHealth(User& user, Card* card, BYTE damage);
// Call RawModifyHealth with current user
Task ModifyHealthTask(Card* card, BYTE damage);

// Return BriefTaskMeta, Brief Current Game
TaskMeta RawBrief(const User& current, const User& opponent);
Task BriefTask();

// Call RequireMethod with TaskID::SELECT_MENU and return result
Task SelectMenuTask(TaskAgent& agent);

// Call RequireMethod with TaskID::SELECT_CARD and return result
Task SelectCardTask(TaskAgent& agent);

// Call RequireMethod with TaskID::SELECT_TARGET and return result
Task SelectTargetTask(TaskAgent& agent);

// Return TaskMetaVector(mulligan, shuffle, draw), Mulligan with `meta` as
// RequireMulliganTaskMeta
TaskMeta RawMulligan(User& current, std::function<TaskMeta()>&& meta);
Task MulliganTask(TaskAgent& agent);

//Return SummonMinionTaskMeta, Summon `current`.hand[`cardIndex`] at `position`
TaskMeta RawSummonMinion(User&current, size_t cardIndex, size_t position);
Task SummonMinionTask(size_t cardIndex, size_t position);

// Return CombatTaskMeta, Combat `current`.field[`src`] with `opponent`.field[`dst`]
TaskMeta RawCombat(User& curent, User& opponent, size_t src, size_t dst);
Task CombatTask(size_t src, size_t dst);

TaskMeta RawGameEnd(User& current, User& opponent);
Task GameEndTask();
}  // namespace Hearthstonepp::BasicTask

#endif  // HEARTHSTONEPP_BASICTASK_H
