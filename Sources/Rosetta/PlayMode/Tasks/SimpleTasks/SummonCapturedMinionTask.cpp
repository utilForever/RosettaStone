// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/Actions/Summon.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Enchantment.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SummonCapturedMinionTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SummonTask.hpp>

#include <stdexcept>

namespace RosettaStone::PlayMode::SimpleTasks
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
    int alternateCount = 0;
    const int summonPos = SummonTask::GetPosition(
        m_source, SummonSide::DEATHRATTLE, m_target, alternateCount);

    Generic::Summon(minion, summonPos, m_source);

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> SummonCapturedMinionTask::CloneImpl()
{
    return std::make_unique<SummonCapturedMinionTask>();
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
