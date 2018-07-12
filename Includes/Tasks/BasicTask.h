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

#include <Syncs/Player.h>
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
std::function<TaskMeta()> RequireMethod(TaskID request, BYTE playerID,
                                        TaskAgent& agent);

// Call task both current player and opponent player
Task DoBothPlayer(Task&& task);

// Call task recursively until the condition satisfied
Task DoUntil(Task&& task, std::function<bool(const TaskMeta&)>&& condition);

// Return PlayerSettingTaskMeta, Set player id as order
TaskMeta PlayerSetting(Player& current, Player& opponent);
Task PlayerSettingTask();

// Return TaskMeta with TaskID::SWAP, Swap player
TaskMeta SwapPlayer(Player& current, Player& opponent);
Task SwapPlayerTask();

// Return TaskMeta with TaskID::SHUFFLE, Shuffle deck of `player`
TaskMeta Shuffle(Player& player);
// Call Shuffle with current player
Task ShuffleTask();

// Return DrawTaskMeta, Draw `num` cards from deck of `player`
TaskMeta Draw(Player& player, size_t num);
// Call Draw with current player
Task DrawTask(size_t num);
// Return DrawTaskMeta, Draw specific card
TaskMeta Draw(Player& player, Card* card);
// Call Draw with current player
Task DrawTask(Card* card);

// Return ModifyManaTaskMeta, Modify `manaMode` with operator `numMode` and
// `object`
TaskMeta ModifyMana(Player& player, size_t numMode, size_t manaMode,
                    BYTE object);
// Call ModifyMana with current player
Task ModifyManaTask(size_t numMode, size_t manaMode, BYTE object);
// Call ModifyMana with current player and `object` by reference
Task ModifyManaByRef(size_t numMode, size_t manaMode, const BYTE& object);

// Return ModifyHealthTaskMeta, Subtract health of `card` with `damage`,
// if Minion Exhausted, delete `card` from field of `player`
TaskMeta ModifyHealth(Player& player, Card* card, BYTE damage);
// Call ModifyHealth with current player
Task ModifyHealthTask(Card* card, BYTE damage);

// Return BriefTaskMeta, Brief Current Game
TaskMeta Brief(const Player& current, const Player& opponent);
Task BriefTask();

// Call RequireMethod with TaskID::SELECT_MENU and return result
Task SelectMenuTask(TaskAgent& agent);

// Call RequireMethod with TaskID::SELECT_CARD and return result
Task SelectCardTask(TaskAgent& agent);

// Call RequireMethod with TaskID::SELECT_TARGET and return result
Task SelectTargetTask(TaskAgent& agent);

// Return TaskMetaVector(mulligan, shuffle, draw), Mulligan with `meta` as
// RequireMulliganTaskMeta
TaskMeta Mulligan(Player& current, std::function<TaskMeta()>&& meta);
Task MulliganTask(TaskAgent& agent);

// Return SummonMinionTaskMeta, Summon `player`.hand[`cardIndex`] at `position`
TaskMeta PlayCard(Player& player, size_t cardIndex, size_t position);
Task PlayCardTask(Player& player, size_t cardIndex, int position = -1);

TaskMeta PlayMinion(Player& player, Card* card, size_t position);
TaskMeta PlayWeapon(Player& player, Card* card);

// Return CombatTaskMeta, Combat `current`.field[`src`] with
// `opponent`.field[`dst`]
TaskMeta Combat(Player& curent, Player& opponent, size_t src, size_t dst);
Task CombatTask(size_t src, size_t dst);

TaskMeta GameEnd(Player& current, Player& opponent);
Task GameEndTask();
}  // namespace Hearthstonepp::BasicTask

#endif  // HEARTHSTONEPP_BASICTASK_H
