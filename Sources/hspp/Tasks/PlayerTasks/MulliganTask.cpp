// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Commons/Constants.hpp>
#include <hspp/Commons/Utils.hpp>
#include <hspp/Tasks/PlayerTasks/MulliganTask.hpp>
#include <hspp/Tasks/SimpleTasks/DrawTask.hpp>
#include <hspp/Tasks/SimpleTasks/ShuffleTask.hpp>

#include <algorithm>

using namespace Hearthstonepp::SimpleTasks;

namespace Hearthstonepp::PlayerTasks
{
MulliganTask::MulliganTask()
{
    // Do nothing
}

TaskID MulliganTask::GetTaskID() const
{
    return TaskID::MULLIGAN;
}

MetaData MulliganTask::Impl(Player& player)
{
    TaskMeta result = player.GetPolicy().Require(player, TaskID::MULLIGAN);
    if (!result.HasObjects())
    {
        return MetaData::MULLIGAN_FLATBUFFER_NULLPTR;
    }

    Box<size_t>& index = result.GetObject<Box<size_t>>();
    if (index.size() == 0) 
    {
        return MetaData::MULLIGAN_SUCCESS;
    }

    // Sort decreasing order
    std::sort(index.begin(), index.end(), std::greater<size_t>());

    // Verify range
    if (index[0] >= NUM_DRAW_CARDS_AT_START_SECOND)
    {
        return MetaData::MULLIGAN_INDEX_OUT_OF_RANGE;
    }

    // Verify duplicated element
    for (size_t i = 1; i < index.size(); ++i)
    {
        if (index[i] == index[i - 1])
        {
            return MetaData::MULLIGAN_DUPLICATED_INDEX;
        }
    }

    std::vector<Entity*>& deck = player.GetDeck();
    std::vector<Entity*>& hand = player.GetHand();

    // Rollback to deck
    for (size_t idx : index) {
        deck.emplace_back(hand[idx]);
        hand.erase(hand.begin() + idx);
    }

    const MetaData statusShuffle = ShuffleTask().Run(player);
    const MetaData statusDraw = DrawTask(index.size()).Run(player);

    if (statusShuffle == MetaData::SHUFFLE_SUCCESS &&
        statusDraw == MetaData::DRAW_SUCCESS)
    {
        return MetaData::MULLIGAN_SUCCESS;
    }

    return statusDraw;
}
}  // namespace Hearthstonepp::PlayerTasks