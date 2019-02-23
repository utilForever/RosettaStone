// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Commons/Constants.hpp>
#include <hspp/Commons/Utils.hpp>
#include <hspp/Policies/Policy.hpp>
#include <hspp/Tasks/PlayerTasks/MulliganTask.hpp>
#include <hspp/Tasks/SimpleTasks/DrawTask.hpp>

#include <algorithm>

using namespace Hearthstonepp::SimpleTasks;

namespace Hearthstonepp::PlayerTasks
{
TaskID MulliganTask::GetTaskID() const
{
    return TaskID::MULLIGAN;
}

TaskStatus MulliganTask::Impl(Player& player)
{
    TaskMeta result = player.GetPolicy().Require(player, TaskID::MULLIGAN);
    if (!result.HasObjects())
    {
        return TaskStatus::MULLIGAN_INVALID_REQUIRE;
    }

    SizedPtr<std::size_t>& index = result.GetObject<SizedPtr<std::size_t>>();
    if (index.size() == 0)
    {
        return TaskStatus::MULLIGAN_SUCCESS;
    }

    // Sort decreasing order
    std::sort(index.begin(), index.end(), std::greater<std::size_t>());

    // Verify range
    if (index[0] >= NUM_DRAW_CARDS_AT_START_SECOND)
    {
        return TaskStatus::MULLIGAN_INDEX_OUT_OF_RANGE;
    }

    // Verify duplicated element
    for (std::size_t i = 1; i < index.size(); ++i)
    {
        if (index[i] == index[i - 1])
        {
            return TaskStatus::MULLIGAN_DUPLICATED_INDEX;
        }
    }

    auto& deck = player.GetDeck();
    auto& hand = player.GetHand();

    // Rollback to deck
    for (std::size_t idx : index)
    {
        deck.AddCard(*hand.GetCard(index[idx]));
        hand.RemoveCard(*hand.GetCard(index[idx]));
    }

    deck.Shuffle();
    const TaskStatus statusDraw = DrawTask(index.size()).Run(player);

    if (statusDraw == TaskStatus::DRAW_SUCCESS)
    {
        return TaskStatus::MULLIGAN_SUCCESS;
    }

    return statusDraw;
}
}  // namespace Hearthstonepp::PlayerTasks