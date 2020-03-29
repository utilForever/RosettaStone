// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Summon.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Enchantment.hpp>
#include <Rosetta/Tasks/SimpleTasks/SummonCapturedMinionTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/SummonTask.hpp>

namespace RosettaStone::SimpleTasks
{
TaskStatus SummonCapturedMinionTask::Impl(Player* player)
{
    const auto enchantment = dynamic_cast<Enchantment*>(m_target);
    if (enchantment == nullptr)
    {
        throw std::invalid_argument(
            "SummonCapturedMinionTask::Impl() - target is not "
            "Enchantment!");
    }

    Card* card = enchantment->GetCapturedCard();
    if (card == nullptr)
    {
        throw std::invalid_argument(
            "SummonCapturedMinionTask::Impl() - Enchantment doesn't "
            "have any captured card!");
    }

    const auto minion =
        dynamic_cast<Minion*>(Entity::GetFromCard(player, card));
    const int summonPos =
        SummonTask::GetPosition(m_source, SummonSide::DEATHRATTLE);

    Generic::Summon(minion, summonPos, m_source);

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> SummonCapturedMinionTask::CloneImpl()
{
    return std::make_unique<SummonCapturedMinionTask>();
}
}  // namespace RosettaStone::SimpleTasks
