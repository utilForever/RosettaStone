// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/PlayCard.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/WeaponTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
WeaponTask::WeaponTask(std::string cardID, bool isOpponent)
    : m_cardID(std::move(cardID)), m_isOpponent(isOpponent)
{
    // Do nothing
}

TaskStatus WeaponTask::Impl(Player* player)
{
    Card* weaponCard = Cards::FindCardByID(m_cardID);
    if (weaponCard->id.empty())
    {
        return TaskStatus::STOP;
    }

    Player* owner = m_isOpponent ? player->opponent : player;

    const auto weapon =
        dynamic_cast<Weapon*>(Entity::GetFromCard(owner, weaponCard));
    Generic::PlayWeapon(owner, weapon, nullptr);

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> WeaponTask::CloneImpl()
{
    return std::make_unique<WeaponTask>(m_cardID, m_isOpponent);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
