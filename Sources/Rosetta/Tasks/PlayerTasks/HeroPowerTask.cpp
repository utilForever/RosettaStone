// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/PlayCard.hpp>
#include <Rosetta/Actions/Targeting.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/PlayerTasks/HeroPowerTask.hpp>

namespace RosettaStone::PlayerTasks
{
HeroPowerTask::HeroPowerTask(Entity* target) : ITask(nullptr, target)
{
    // Do nothing
}

TaskStatus HeroPowerTask::Impl(Player* player)
{
    HeroPower& power = player.GetHeroPower();

    if (!Generic::IsPlayableByPlayer(player, &power) ||
        !Generic::IsPlayableByCardReq(&power) ||
        !Generic::IsValidTarget(&power, m_target))
    {
        return TaskStatus::STOP;
    }

    if (power.IsExhausted())
    {
        return TaskStatus::STOP;
    }

    // Spend mana to play cards
    if (power.GetCost() > 0)
    {
        const int tempUsed = std::min(player.GetTemporaryMana(), power.GetCost());
        player.SetTemporaryMana(player.GetTemporaryMana() - tempUsed);
        player.SetUsedMana(player.GetUsedMana() + power.GetCost() - tempUsed);
    }

    // Process target trigger
    if (m_target != nullptr)
    {
        Trigger::ValidateTriggers(player.GetGame(), &power,
                                  SequenceType::TARGET);
        player.GetGame()->taskQueue.StartEvent();
        player.GetGame()->triggerManager.OnTargetTrigger(&player, &power);
        player.GetGame()->ProcessTasks();
        player.GetGame()->taskQueue.EndEvent();
    }

    // Process power tasks
    player.GetGame()->taskQueue.StartEvent();
    power.ActivateTask(PowerType::POWER, m_target);
    player.GetGame()->ProcessTasks();
    player.GetGame()->taskQueue.EndEvent();

    player.GetGame()->ProcessDestroyAndUpdateAura();

    power.SetExhausted(true);

    return TaskStatus::COMPLETE;
}

ITask* HeroPowerTask::CloneImpl()
{
    return new HeroPowerTask(m_target);
}
}  // namespace RosettaStone::PlayerTasks
