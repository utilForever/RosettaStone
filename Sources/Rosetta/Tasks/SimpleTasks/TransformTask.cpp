// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/TransformTask.hpp>

namespace RosettaStone::SimpleTasks
{
TransformTask::TransformTask(EntityType entityType, std::string cardID)
    : ITask(entityType), m_cardID(cardID)
{
    // Do nothing
}

TaskID TransformTask::GetTaskID() const
{
    return TaskID::TRANSFORM;
}

TaskStatus TransformTask::Impl(Player& player)
{
    Card card = Cards::GetInstance().FindCardByID(m_cardID);

    auto entities =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& entity : entities)
    {
        auto* minion = dynamic_cast<Minion*>(entity);
        if (minion == nullptr)
        {
            return TaskStatus::STOP;
        }

        Generic::TransformMinion(minion->GetOwner(), minion, card);
    }

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::SimpleTasks
