// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/CastSpell.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/CastSpellStackTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
CastSpellStackTask::CastSpellStackTask(bool removeFromZone)
    : m_removeFromZone(removeFromZone)
{
    // Do nothing
}

TaskStatus CastSpellStackTask::Impl(Player* player)
{
    const auto stack = player->game->taskStack;

    for (auto& playable : stack.playables)
    {
        if (m_removeFromZone)
        {
            playable->zone->Remove(playable);
        }

        Generic::CastSpell(player, dynamic_cast<Spell*>(playable), nullptr, -1);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> CastSpellStackTask::CloneImpl()
{
    return std::make_unique<CastSpellStackTask>(m_removeFromZone);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
