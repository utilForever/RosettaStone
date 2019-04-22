// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/PlayCard.hpp>
#include <Rosetta/Actions/Targeting.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/PlayerTasks/HeroPowerTask.hpp>

namespace RosettaStone::SimpleTasks
{
HeroPowerTask::HeroPowerTask(Entity* target) : ITask(nullptr, target)
{
    // Do nothing
}

TaskID HeroPowerTask::GetTaskID() const
{
    return TaskID::HERO_POWER;
}

TaskStatus HeroPowerTask::Impl(Player& player)
{
    HeroPower* power = player.GetHero()->heroPower;

    if (!Generic::IsPlayableByPlayer(player, power) ||
        !Generic::IsPlayableByCardReq(power) ||
        !Generic::IsValidTarget(power, m_target))
    {
        return TaskStatus::STOP;
    }

    // Spend mana to play cards
    if (power->GetCost() > 0)
    {
        int tempUsed = std::min(player.GetTemporaryMana(), power->GetCost());
        player.SetTemporaryMana(player.GetTemporaryMana() - tempUsed);
        player.SetUsedMana(player.GetUsedMana() + power->GetCost() - tempUsed);
    }

    // Process power tasks
    for (auto& powerTask : power->card.power.GetPowerTask())
    {
        powerTask->SetSource(power);
        powerTask->SetTarget(m_target);
        powerTask->Run(player);
    }

    power->SetExhausted(true);

    player.GetGame()->ProcessDestroyAndUpdateAura();

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::SimpleTasks
