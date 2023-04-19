// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/Common/Utils.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/RandomTask.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::PlayMode::SimpleTasks
{
RandomTask::RandomTask(EntityType entityType, int amount)
    : ITask(entityType), m_amount(amount)
{
    // Do nothing
}

TaskStatus RandomTask::Impl(Player* player)
{
    auto& stackPlayables = player->game->taskStack.playables;
    const auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    if (playables.empty())
    {
        return TaskStatus::STOP;
    }

    if (static_cast<int>(playables.size()) < m_amount)
    {
        stackPlayables = playables;
        return TaskStatus::COMPLETE;
    }

    if (m_amount == 1)
    {
        const auto idx = Random::get<std::size_t>(0, playables.size() - 1);
        stackPlayables = std::vector<Playable*>{ playables.at(idx) };
    }
    else
    {
        stackPlayables = ChooseNElements(playables, m_amount);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> RandomTask::CloneImpl()
{
    return std::make_unique<RandomTask>(m_entityType, m_amount);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
