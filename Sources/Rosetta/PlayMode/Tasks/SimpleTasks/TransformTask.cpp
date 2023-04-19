// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/TransformTask.hpp>

#include <utility>

namespace RosettaStone::PlayMode::SimpleTasks
{
TransformTask::TransformTask(EntityType entityType, std::string cardID)
    : ITask(entityType), m_cardID(std::move(cardID))
{
    // Do nothing
}

TaskStatus TransformTask::Impl(Player* player)
{
    const auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (const auto& playable : playables)
    {
        Card* card = Cards::FindCardByID(m_cardID);

        auto* minion = dynamic_cast<Minion*>(playable);

        if (!minion)
        {
            return TaskStatus::STOP;
        }

        Generic::TransformMinion(minion->player, minion, card);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> TransformTask::CloneImpl()
{
    return std::make_unique<TransformTask>(m_entityType, m_cardID);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
