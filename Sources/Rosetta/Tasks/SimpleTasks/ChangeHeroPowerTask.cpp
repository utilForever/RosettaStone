// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/ChangeHeroPowerTask.hpp>

namespace RosettaStone::SimpleTasks
{
ChangeHeroPowerTask::ChangeHeroPowerTask(const std::string& cardID)
{
    m_card = Cards::FindCardByID(cardID);
}

TaskStatus ChangeHeroPowerTask::Impl(Player* player)
{
    delete player->GetHero()->heroPower;
    player->GetHero()->heroPower =
        dynamic_cast<HeroPower*>(Entity::GetFromCard(player, m_card));

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> ChangeHeroPowerTask::CloneImpl()
{
    return std::make_unique<ChangeHeroPowerTask>(m_card->id);
}
}  // namespace RosettaStone::SimpleTasks
