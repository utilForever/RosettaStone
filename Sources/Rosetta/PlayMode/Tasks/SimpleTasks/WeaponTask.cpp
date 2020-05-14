// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/Actions/PlayCard.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/WeaponTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
WeaponTask::WeaponTask(std::string cardID) : m_cardID(std::move(cardID))
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

    if (player->GetHero()->HasWeapon())
    {
        player->GetWeapon().Destroy();
    }

    const auto weapon =
        dynamic_cast<Weapon*>(Entity::GetFromCard(player, weaponCard));
    Generic::PlayWeapon(player, weapon, nullptr);

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> WeaponTask::CloneImpl()
{
    return std::make_unique<WeaponTask>(m_cardID);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
