// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Commons/Constants.h>
#include <hspp/Tasks/BasicTasks/DrawTask.h>
#include <hspp/Tasks/BasicTasks/MulliganTask.h>
#include <hspp/Tasks/BasicTasks/ShuffleTask.h>

#include <algorithm>

namespace Hearthstonepp::BasicTasks
{
MulliganTask::MulliganTask(TaskAgent& agent)
    : m_agent(agent), m_requirement(Requirement(TaskID::MULLIGAN, agent))
{
    // Do nothing
}

TaskID MulliganTask::GetTaskID() const
{
    return TaskID::MULLIGAN;
}

MetaData MulliganTask::Impl(Player& player1, Player& player2)
{
    TaskMeta serialized;

    // Get mulligan input from Interface
    m_requirement.Interact(player1.id, serialized);

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

    std::vector<Entity*>& deck = player1.cards;
    std::vector<Entity*>& hand = player1.hand;

    // Rollback to deck
    for (size_t i = 0; i < read; ++i)
    {
        deck.emplace_back(hand[index[i]]);
        hand.erase(hand.begin() + index[i]);
    }

    const MetaData statusShuffle = ShuffleTask().Run(player1, player2);
    const MetaData statusDraw = DrawTask(player1, read).Run(player1, player2);

    if (statusShuffle == MetaData::SHUFFLE_SUCCESS &&
        statusDraw == MetaData::DRAW_SUCCESS)
    {
        return MetaData::MULLIGAN_SUCCESS;
    }

    return statusDraw;
}
}  // namespace Hearthstonepp::BasicTasks