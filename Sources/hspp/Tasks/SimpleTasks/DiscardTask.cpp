// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Tasks/SimpleTasks/DiscardTask.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

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
        auto& hand = player.GetHand();
        if (hand.IsEmpty())
        {
            return TaskStatus::DISCARD_MY_HAND_SUCCESS;
        }

        auto idx = Random::get<std::size_t>(0, hand.GetNumOfCards() - 1);
        hand.RemoveCard(*hand.GetCard(idx));
        return TaskStatus::DISCARD_MY_HAND_SUCCESS;
    }

    return TaskStatus::INVALID;
}
}  // namespace Hearthstonepp::SimpleTasks