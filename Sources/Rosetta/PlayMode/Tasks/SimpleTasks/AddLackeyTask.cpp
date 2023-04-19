// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/AddLackeyTask.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::PlayMode::SimpleTasks
{
AddLackeyTask::AddLackeyTask(int amount) : m_amount(amount)
{
    // Do nothing
}

TaskStatus AddLackeyTask::Impl(Player* player)
{
    auto lackeys = Cards::GetLackeys();

    std::vector<Playable*> cards;

    for (int i = 0; i < m_amount && !player->GetHandZone()->IsFull(); ++i)
    {
        const auto lackey = Entity::GetFromCard(
            player, *Random::get(lackeys), std::nullopt, player->GetHandZone());
        Generic::AddCardToHand(player, lackey);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> AddLackeyTask::CloneImpl()
{
    return std::make_unique<AddLackeyTask>(m_amount);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
