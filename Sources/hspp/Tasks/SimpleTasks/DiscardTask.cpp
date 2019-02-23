// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Tasks/SimpleTasks/DiscardTask.hpp>

#include <random>

namespace Hearthstonepp::SimpleTasks
{
DiscardTask::DiscardTask(EntityType entityType) : ITask(entityType)
{
    // Do nothing
}

TaskID DiscardTask::GetTaskID() const
{
    return TaskID::DISCARD;
}

TaskStatus DiscardTask::Impl(Player& player)
{
    if (m_entityType == +EntityType::HAND)
    {
        if (player.GetHand().IsEmpty())
        {
            return TaskStatus::DISCARD_MY_HAND_SUCCESS;
        }

        std::random_device rd;
        // ReSharper disable once CppLocalVariableMayBeConst
        // NOTE: 'const' occurs compile error on Linux and macOS
        std::uniform_int_distribution<std::size_t> dist(
            0, player.GetHand().GetNumOfCards() - 1);

        const std::size_t discardIdx = dist(rd);

        // Card Hand Index Verification
        if (discardIdx >= player.GetHand().GetNumOfCards())
        {
            return TaskStatus::DISCARD_IDX_OUT_OF_RANGE;
        }

        player.GetHand().RemoveCard(*player.GetHand().GetCard(discardIdx));
        return TaskStatus::DISCARD_MY_HAND_SUCCESS;
    }

    return TaskStatus::INVALID;
}
}  // namespace Hearthstonepp::SimpleTasks