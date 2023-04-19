// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/AddPoisonTask.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::PlayMode::SimpleTasks
{
AddPoisonTask::AddPoisonTask(int amount) : m_amount(amount)
{
    // Do nothing
}

TaskStatus AddPoisonTask::Impl(Player* player)
{
    auto poisons = Cards::GetPoisons();

    std::vector<Playable*> cards;

    for (int i = 0; i < m_amount && !player->GetHandZone()->IsFull(); ++i)
    {
        const auto poison = Entity::GetFromCard(
            player, *Random::get(poisons), std::nullopt, player->GetHandZone());
        Generic::AddCardToHand(player, poison);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> AddPoisonTask::CloneImpl()
{
    return std::make_unique<AddPoisonTask>(m_amount);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
