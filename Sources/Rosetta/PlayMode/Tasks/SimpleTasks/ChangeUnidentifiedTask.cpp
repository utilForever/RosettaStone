// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ChangeUnidentifiedTask.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::PlayMode::SimpleTasks
{
TaskStatus ChangeUnidentifiedTask::Impl(Player* player)
{
    const auto idx =
        Random::get<std::size_t>(0, m_source->card->entourages.size() - 1);

    Generic::ChangeEntity(player, dynamic_cast<Playable*>(m_source),
                          Cards::FindCardByID(m_source->card->entourages[idx]),
                          false);

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> ChangeUnidentifiedTask::CloneImpl()
{
    return std::make_unique<ChangeUnidentifiedTask>();
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
