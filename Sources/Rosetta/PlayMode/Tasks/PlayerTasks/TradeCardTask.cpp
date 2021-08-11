// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/Models/Player.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/TradeCardTask.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>

namespace RosettaStone::PlayMode::PlayerTasks
{
TradeCardTask::TradeCardTask(Entity* source) : ITask(source, nullptr)
{
    // Do nothing
}

TaskStatus TradeCardTask::Impl(Player* player)
{
    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> TradeCardTask::CloneImpl()
{
    return std::make_unique<TradeCardTask>(m_source);
}

bool TradeCardTask::CanTradeCard() const
{
    if (auto playable = dynamic_cast<Playable*>(m_source);
        !playable || !playable->HasTradeable())
    {
        return false;
    }

    // The player can also drag it into their deck to spend 1 mana
    if (m_player->GetRemainingMana() < 1)
    {
        return false;
    }

    // You can't trade a Tradeable card if your deck is empty
    if (m_player->GetDeckZone()->IsEmpty())
    {
        return false;
    }

    return true;
}
}  // namespace RosettaStone::PlayMode::PlayerTasks
