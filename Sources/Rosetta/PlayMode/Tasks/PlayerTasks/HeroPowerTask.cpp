// This code is based on Sabberstone project.
// Copyright (c) 2017-2021 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2024 Chris Ohk

#include <Rosetta/PlayMode/Actions/PlayCard.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/HeroPowerTask.hpp>

namespace RosettaStone::PlayMode::PlayerTasks
{
HeroPowerTask::HeroPowerTask(Playable* target) : ITask(nullptr, target)
{
    // Do nothing
}

Character* HeroPowerTask::ResolveTarget(const Player* player, Character* target)
{
    // NOTE: 'Steady Shot' (HERO_05bp) and 'Ballista Shot' (HERO_05bp2) can
    // target by some cards e.g. Steamwheedle Sniper, Dwarven Sharpshooter
    if (const HeroPower& power = player->GetHeroPower();
        power.card->id == "HERO_05bp" || power.card->id == "HERO_05bp2")
    {
        if (const auto& auraEffects = player->playerAuraEffects;
            auraEffects.GetValue(GameTag::CAN_TARGET_MINION_BY_HERO_POWER) == 1)
        {
            // Do nothing
        }
        else
        {
            return player->opponent->GetHero();
        }
    }

    return target;
}

bool HeroPowerTask::CanPlay(const Player* player, Character* target)
{
    HeroPower& power = player->GetHeroPower();

    return power.IsPlayableByPlayer() && power.IsPlayableByCardReq() &&
           power.IsValidPlayTarget(ResolveTarget(player, target)) &&
           !power.IsExhausted();
}

TaskStatus HeroPowerTask::Impl(Player* player)
{
    HeroPower& power = player->GetHeroPower();

    m_target = ResolveTarget(player, dynamic_cast<Character*>(m_target));

    if (!CanPlay(player, dynamic_cast<Character*>(m_target)))
    {
        return TaskStatus::STOP;
    }

    // Spend mana to play cards
    if (power.GetCost() > 0)
    {
        const int tempUsed =
            std::min(player->GetTemporaryMana(), power.GetCost());
        player->SetTemporaryMana(player->GetTemporaryMana() - tempUsed);
        player->SetUsedMana(player->GetUsedMana() + power.GetCost() - tempUsed);
    }

    // Process target trigger
    if (m_target)
    {
        player->game->currentEventData =
            std::make_unique<EventMetaData>(&power, m_target);

        Trigger::ValidateTriggers(player->game, &power, SequenceType::TARGET);
        player->game->taskQueue.StartEvent();
        player->game->triggerManager.OnTargetTrigger(&power);
        player->game->ProcessTasks();
        player->game->taskQueue.EndEvent();
    }

    // Process power tasks
    player->game->taskQueue.StartEvent();
    power.ActivateTask(PowerType::POWER, dynamic_cast<Character*>(m_target));
    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();

    player->game->ProcessDestroyAndUpdateAura();

    player->GetHeroPower().SetExhausted(true);

    // Process inspire trigger
    player->game->taskQueue.StartEvent();
    player->game->triggerManager.OnInspireTrigger(player);
    player->game->ProcessTasks();
    player->game->taskQueue.EndEvent();

    player->game->ProcessDestroyAndUpdateAura();

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> HeroPowerTask::CloneImpl()
{
    return std::make_unique<HeroPowerTask>(m_target);
}
}  // namespace RosettaStone::PlayMode::PlayerTasks
