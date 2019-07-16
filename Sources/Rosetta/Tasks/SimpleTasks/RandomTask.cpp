// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/RandomTask.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::SimpleTasks
{
RandomTask::RandomTask(EntityType entityType, int num)
    : ITask(entityType), m_num(num)
{
    // Do nothing
}

TaskID RandomTask::GetTaskID() const
{
    return TaskID::RANDOM;
}

ITask* RandomTask::CloneImpl()
{
    return new RandomTask(m_entityType, m_num);
}

TaskStatus RandomTask::Impl(Player& player)
{
    auto entities =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    player.GetGame()->taskStack.entities.clear();

    for (int i = 0; i < m_num && !entities.empty(); ++i)
    {
        const auto idx = Random::get<std::size_t>(0, entities.size() - 1);

        Entity* entity = entities.at(idx);
        entities.erase(entities.begin() + idx);
        player.GetGame()->taskStack.entities.emplace_back(entity);
    }

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::SimpleTasks
