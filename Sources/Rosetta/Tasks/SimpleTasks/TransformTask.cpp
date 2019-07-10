// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/TransformTask.hpp>

#include <utility>

namespace RosettaStone::SimpleTasks
{
TransformTask::TransformTask(EntityType entityType, std::string cardID)
    : ITask(entityType), m_cardID(std::move(cardID))
{
    // Do nothing
}

TaskID TransformTask::GetTaskID() const
{
    return TaskID::TRANSFORM;
}

TaskStatus TransformTask::Impl(Player& player)
{
    auto entities =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& entity : entities)
    {
        Card* card = Cards::FindCardByID(m_cardID);

        auto* minion = dynamic_cast<Minion*>(entity);
        if (minion == nullptr)
        {
            return TaskStatus::STOP;
        }

        Generic::TransformMinion(*minion->owner, minion, card);
    }

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::SimpleTasks
