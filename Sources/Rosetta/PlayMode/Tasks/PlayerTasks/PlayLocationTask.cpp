// This code is based on Sabberstone project.
// Copyright (c) 2017-2021 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2021 Chris Ohk

#include <Rosetta/PlayMode/Models/Location.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/PlayLocationTask.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>

#include <stdexcept>

namespace RosettaStone::PlayMode::PlayerTasks
{
PlayLocationTask::PlayLocationTask(Entity* source, Playable* target)
    : ITask(source, target)
{
    // Do nothing
}

TaskStatus PlayLocationTask::Impl(Player* player)
{
    const auto location = dynamic_cast<Location*>(m_source);

    if (!location)
    {
        throw std::invalid_argument("PlayLocationTask - It's not a location");
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> PlayLocationTask::CloneImpl()
{
    return std::make_unique<PlayLocationTask>(m_source, m_target);
}

bool PlayLocationTask::IsPlayableByCardReq() const
{
    if (!m_source->card->IsPlayableByLocationReq(m_player))
    {
        return false;
    }

    if (m_source->card->mustHaveToTargetToPlayLocation &&
        !HasAnyValidPlayTargets())
    {
        return false;
    }

    return true;
}

bool PlayLocationTask::HasAnyValidPlayTargets() const
{
    bool friendlyMinions = false, enemyMinions = false;
    bool hero = false, enemyHero = false;

    switch (m_source->card->locationTargetingType)
    {
        case TargetingType::NONE:
            return false;
        case TargetingType::ALL:
            friendlyMinions = true;
            enemyMinions = true;
            hero = true;
            enemyHero = true;
            break;
        case TargetingType::CHARACTERS_EXCEPT_HERO:
            friendlyMinions = true;
            enemyMinions = true;
            enemyHero = true;
            break;
        case TargetingType::FRIENDLY_CHARACTERS:
            friendlyMinions = true;
            hero = true;
            break;
        case TargetingType::ENEMY_CHARACTERS:
            enemyMinions = true;
            enemyHero = true;
            break;
        case TargetingType::ALL_MINIONS:
            friendlyMinions = true;
            enemyMinions = true;
            break;
        case TargetingType::FRIENDLY_MINIONS:
            friendlyMinions = true;
            break;
        case TargetingType::ENEMY_MINIONS:
            enemyMinions = true;
            break;
        case TargetingType::HEROES:
            hero = true;
            enemyHero = true;
            break;
    }

    if (friendlyMinions)
    {
        for (const auto& minion : m_player->GetFieldZone()->GetMinions())
        {
            if (TargetingRequirements(minion))
            {
                return true;
            }
        }
    }

    if (enemyMinions)
    {
        for (const auto& minion :
             m_player->opponent->GetFieldZone()->GetMinions())
        {
            if (TargetingRequirements(minion))
            {
                return true;
            }
        }
    }

    if (hero && TargetingRequirements(m_player->GetHero()))
    {
        return true;
    }

    if (enemyHero && TargetingRequirements(m_player->opponent->GetHero()))
    {
        return true;
    }

    return false;
}

bool PlayLocationTask::TargetingRequirements(Character* target) const
{
    return m_source->card->TargetingRequirements(m_player, target);
}
}  // namespace RosettaStone::PlayMode::PlayerTasks
