// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/PowerTasks/DiscardTask.h>

#include <random>

namespace Hearthstonepp::PowerTask
{
DiscardTask::DiscardTask(EntityType entityType) : m_entityType(entityType)
{
    // Do nothing
}

TaskID DiscardTask::GetTaskID() const
{
    return TaskID::DISCARD;
}

MetaData DiscardTask::Impl(Player& player)
{
    if (m_entityType == +EntityType::HAND)
    {
        if (player.hand.empty())
        {
            return MetaData::DISCARD_MY_HAND_SUCCESS;
        }

        std::random_device rd;
        // ReSharper disable once CppLocalVariableMayBeConst
        // NOTE: 'const' occurs compile error on Linux and macOS
        std::uniform_int_distribution<size_t> dist(0, player.hand.size() - 1);

        const size_t discardIdx = dist(rd);

        // Card Hand Index Verification
        if (discardIdx >= player.hand.size())
        {
            return MetaData::DISCARD_IDX_OUT_OF_RANGE;
        }

        player.hand.erase(player.hand.begin() + discardIdx);
        return MetaData::DISCARD_MY_HAND_SUCCESS;
    }

    return MetaData::INVALID;
}
}  // namespace Hearthstonepp::PowerTask