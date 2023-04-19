// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/RandomEntourageTask.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::PlayMode::SimpleTasks
{
RandomEntourageTask::RandomEntourageTask(int count, bool isOpponent)
    : m_count(count), m_isOpponent(isOpponent)
{
    // Do nothing
}

TaskStatus RandomEntourageTask::Impl(Player* player)
{
    std::vector<Playable*> list;

    if (!m_source || m_source->card->entourages.empty())
    {
        return TaskStatus::STOP;
    }

    if (m_count > static_cast<int>(m_source->card->entourages.size()))
    {
        return TaskStatus::STOP;
    }

    for (int i = 0; i < m_count; ++i)
    {
        const auto idx =
            Random::get<std::size_t>(0, m_source->card->entourages.size() - 1);
        const auto entourageCard =
            Cards::FindCardByID(m_source->card->entourages[idx]);

        Playable* entouragePlayable =
            Entity::GetFromCard(player, entourageCard);
        list.emplace_back(entouragePlayable);
    }

    player->game->taskStack.playables = list;

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> RandomEntourageTask::CloneImpl()
{
    return std::make_unique<RandomEntourageTask>(m_count, m_isOpponent);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
