// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Tasks/SimpleTasks/ChangeUnidentifiedTask.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::SimpleTasks
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
}  // namespace RosettaStone::SimpleTasks
