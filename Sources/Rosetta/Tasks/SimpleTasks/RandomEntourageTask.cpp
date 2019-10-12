// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/RandomEntourageTask.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::SimpleTasks
{
RandomEntourageTask::RandomEntourageTask(int count, bool isOpponent)
    : m_count(count), m_isOpponent(isOpponent)
{
    // Do nothing
}

TaskStatus RandomEntourageTask::Impl(Player& player)
{
    (void)m_isOpponent;

    if (m_source == nullptr || m_source->card->entourages.empty())
    {
        return TaskStatus::STOP;
    }

    if (m_count > static_cast<int>(m_source->card->entourages.size()))
    {
        return TaskStatus::STOP;
    }

    player.GetGame()->taskStack.entities.clear();

    for (int i = 0; i < m_count; ++i)
    {
        const auto idx =
            Random::get<std::size_t>(0, m_source->card->entourages.size() - 1);
        const auto entourageCard =
            Cards::GetInstance().FindCardByID(m_source->card->entourages[idx]);

        Entity* entourageEntity = Entity::GetFromCard(player, entourageCard);
        player.GetGame()->taskStack.entities.emplace_back(entourageEntity);
    }

    return TaskStatus::COMPLETE;
}

ITask* RandomEntourageTask::CloneImpl()
{
    return new RandomEntourageTask(m_count, m_isOpponent);
}
}  // namespace RosettaStone::SimpleTasks
