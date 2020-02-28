// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/AddLackeyTask.hpp>
#include <Rosetta/Zones/HandZone.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::SimpleTasks
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
        const auto idx = Random::get<std::size_t>(0, lackeys.size() - 1);
        const auto lackey = Entity::GetFromCard(
            player, lackeys.at(idx), std::nullopt, player->GetHandZone());
        Generic::AddCardToHand(player, lackey);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> AddLackeyTask::CloneImpl()
{
    return std::make_unique<AddLackeyTask>(m_amount);
}
}  // namespace RosettaStone::SimpleTasks
