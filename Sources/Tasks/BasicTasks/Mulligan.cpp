/*************************************************************************
> File Name: Mulligan.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implement MulliganTask
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Commons/Constants.h>
#include <Tasks/BasicTasks/Draw.h>
#include <Tasks/BasicTasks/Mulligan.h>
#include <Tasks/BasicTasks/Shuffle.h>

#include <algorithm>

namespace Hearthstonepp::BasicTasks
{
MulliganTask::MulliganTask(TaskAgent& agent)
    : m_agent(agent), m_requirement(Requirement(TaskID::MULLIGAN, agent))
{
    // Do  Nothing
}

TaskID MulliganTask::GetTaskID() const
{
    return TaskID::MULLIGAN;
}

MetaData MulliganTask::Impl(Player& player1, Player& player2) const
{
    // Get Mulligan Input from Interface
    TaskMeta serialized;
    m_requirement.Interact(player1.id, serialized);

    using RequireTaskMeta = FlatData::ResponseMulligan;
    const auto& buffer = serialized.GetConstBuffer();
    auto req = flatbuffers::GetRoot<RequireTaskMeta>(buffer.get());

    if (req == nullptr)
    {
        return MetaData::MULLIGAN_FLATBUFFER_NULLPTR;
    }

    const BYTE* data = req->mulligan()->data();
    size_t read = req->mulligan()->size();

    // Copy data from input
    BYTE index[NUM_BEGIN_DRAW] = {
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
    // Range verification
    if (index[0] >= NUM_BEGIN_DRAW)
    {
        return MetaData::MULLIGAN_INDEX_OUT_OF_RANGE;
    }

    // Duplicated Element Verification
    for (size_t i = 1; i < read; ++i)
    {
        if (index[i] == index[i - 1])
        {
            return MetaData::MULLIGAN_DUPLICATED_INDEX;
        }
    }

    std::vector<Entity*>& deck = player1.cards;
    std::vector<Entity*>& hand = player1.hand;

    // Rollback to Deck
    for (size_t i = 0; i < read; ++i)
    {
        deck.emplace_back(hand[index[i]]);
        hand.erase(hand.begin() + index[i]);
    }

    MetaData statusShuffle = ShuffleTask().Run(player1, player2);
    MetaData statusDraw = DrawTask(read, m_agent).Run(player1, player2);

    if (statusShuffle == MetaData::SHUFFLE_SUCCESS &&
        statusDraw == MetaData::DRAW_SUCCESS)
    {
        return MetaData::MULLIGAN_SUCCESS;
    }
    else
    {
        return statusDraw;
    }
}
}  // namespace Hearthstonepp::BasicTasks