// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Commons/Constants.hpp>
#include <hspp/Tasks/PlayerTasks/MulliganTask.hpp>
#include <hspp/Tasks/SimpleTasks/DrawTask.hpp>
#include <hspp/Tasks/SimpleTasks/ShuffleTask.hpp>

#include <algorithm>

using namespace Hearthstonepp::SimpleTasks;

namespace Hearthstonepp::PlayerTasks
{
MulliganTask::MulliganTask(TaskAgent& agent)
    : m_requirement(Requirement(TaskID::MULLIGAN, agent))
{
    // Do nothing
}

TaskID MulliganTask::GetTaskID() const
{
    return TaskID::MULLIGAN;
}

MetaData MulliganTask::Impl(Player& player)
{
    TaskMeta serialized;

    // Get mulligan input from Interface
    m_requirement.Interact(player.GetID(), serialized);

    using RequireTaskMeta = FlatData::ResponseMulligan;
    const auto& buffer = serialized.GetBuffer();
    const auto req = flatbuffers::GetRoot<RequireTaskMeta>(buffer.get());

    if (req == nullptr)
    {
        return MetaData::MULLIGAN_FLATBUFFER_NULLPTR;
    }

    const BYTE* data = req->mulligan()->data();
    const size_t read = req->mulligan()->size();

    // Copy data from input
    BYTE index[NUM_DRAW_CARDS_AT_START_SECOND] = {
        0,
    };
    std::copy(data, data + read, index);

    // None of cards are selected
    if (read == 0)
    {
        return MetaData::MULLIGAN_SUCCESS;
    }

    // Sort decreasing order
    std::sort(index, index + read, [](BYTE a, BYTE b) { return a > b; });

    // Verify range
    if (index[0] >= NUM_DRAW_CARDS_AT_START_SECOND)
    {
        return MetaData::MULLIGAN_INDEX_OUT_OF_RANGE;
    }

    // Verify duplicated element
    for (size_t i = 1; i < read; ++i)
    {
        if (index[i] == index[i - 1])
        {
            return MetaData::MULLIGAN_DUPLICATED_INDEX;
        }
    }

    auto& deck = player.GetDeck();
    auto& hand = player.GetHand();

    // Rollback to deck
    for (size_t i = 0; i < read; ++i)
    {
        deck.AddCard(*hand.GetCard(index[i]));
        hand.RemoveCard(*hand.GetCard(index[i]));
    }

    const MetaData statusShuffle = ShuffleTask().Run(player);
    const MetaData statusDraw = DrawTask(read).Run(player);

    if (statusShuffle == MetaData::SHUFFLE_SUCCESS &&
        statusDraw == MetaData::DRAW_SUCCESS)
    {
        return MetaData::MULLIGAN_SUCCESS;
    }

    return statusDraw;
}
}  // namespace Hearthstonepp::PlayerTasks